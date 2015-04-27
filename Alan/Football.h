#ifndef FOOTBALL_H
#define FOOTBALL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
//#include "Game.h"

using namespace std;

class Football : public Global_Constants {
	public:
		Football();
		Football(int, int, int);
		~Football();
		virtual bool load_enemy();
		virtual bool mario_die(int, int);
		virtual bool check_up(int, int);
		virtual void setxCoord(int);
		virtual void render_enemy(int);
		void check_bricks();
      LTexture gRightEnemyTexture;
		SDL_Rect gRightEnemy[5];
		LTexture gLeftEnemyTexture;
		SDL_Rect gLeftEnemy[5];
	protected:
		int enemy_xcoord;
		int enemy_ycoord;
		Map level1;
		Map level2;
		Map * mapPtr;
		int level;
		int right_step;
		int left_step;
		int enemy_yoriginal;
		int enemy_xoriginal;
		bool render_right = true;
		bool falling = false;
		bool alive = true;
};

#endif


static int right_frame = 0;
static int left_frame = 0;


Football::Football() {}

// Call Football constructor and inherit from Enemy
Football::Football(int xf, int yf, int num_map)
	: level1(gfile1), level2(gfile2)
{
	right_step = 2;
	left_step = 2;
	level = num_map;
	enemy_xcoord = BRICK_WIDTH * xf;
	enemy_ycoord = SCREEN_HEIGHT - yf*BRICK_HEIGHT - FOOTBALL_HEIGHT;
	enemy_xoriginal = enemy_xcoord;
	enemy_yoriginal = enemy_ycoord;
	if (level == 1)
		mapPtr = &level1;
	else
		mapPtr = &level2;
	check_bricks();
	if (!load_enemy())
		throw invalid_argument("Failed to Load football");
	if (mapPtr->get_BrickLocation(enemy_xcoord,enemy_ycoord + FOOTBALL_HEIGHT) == 0 || !render_right) {
		cout << "For " << xf << " and " << yf << endl;
		cout << "For " << enemy_xcoord << " and " << enemy_ycoord << endl;
		if (!render_right) cout << "cant render right\n";
		throw invalid_argument("Footaball player must be placed on a brick");
	}
}

Football::~Football()
{
	//delete [] gRightEnemy;
	//delete [] gLeftEnemy;
}
bool Football::load_enemy()
{
	bool success = true;
	//Load enemy sprite sheet texture going right
	if( !gRightEnemyTexture.loadFromFile( "football_right.png", "white" ) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
		//Set sprite clips
		gRightEnemy[ 0 ].x = 0;
		gRightEnemy[ 0 ].y = 0;
		gRightEnemy[ 0 ].w =  49;
		gRightEnemy[ 0 ].h = 51;

		gRightEnemy[ 1 ].x =  49;
		gRightEnemy[ 1 ].y =  0;
		gRightEnemy[ 1 ].w =  49;
		gRightEnemy[ 1 ].h = 51;
		
		gRightEnemy[ 2 ].x = 98;
		gRightEnemy[ 2 ].y = 0;
		gRightEnemy[ 2 ].w =  49;
		gRightEnemy[ 2 ].h = 51;

		gRightEnemy[ 3 ].x = 147;
		gRightEnemy[ 3 ].y = 0;
		gRightEnemy[ 3 ].w = 47;
		gRightEnemy[ 3 ].h = 51;
	}

	if( !gLeftEnemyTexture.loadFromFile( "football_left.png", "white" ) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
		//Set sprite clips
		gLeftEnemy[ 0 ].x = 0;
		gLeftEnemy[ 0 ].y = 0;
		gLeftEnemy[ 0 ].w =  47;
		gLeftEnemy[ 0 ].h = 50;

		gLeftEnemy[ 1 ].x =  47;
		gLeftEnemy[ 1 ].y =  0;
		gLeftEnemy[ 1 ].w =  47;
		gLeftEnemy[ 1 ].h = 50;
		
		gLeftEnemy[ 2 ].x = 94;
		gLeftEnemy[ 2 ].y = 0;
		gLeftEnemy[ 2 ].w =  47;
		gLeftEnemy[ 2 ].h = 50;

		gLeftEnemy[ 3 ].x = 141;
		gLeftEnemy[ 3 ].y = 0;
		gLeftEnemy[ 3 ].w = 45;
		gLeftEnemy[ 3 ].h = 50;
	}
	return success;
}

bool Football::mario_die(int mario_xcoord, int mario_ycoord) 
{

if(!(enemy_xcoord - (mario_xcoord+LEP_WIDTH) < 0 && (enemy_xcoord+34) -(mario_xcoord +LEP_WIDTH) > -34 && (mario_ycoord +LEP_HEIGHT) > enemy_ycoord && !((enemy_ycoord - mario_ycoord) < 3))){
					if(enemy_xcoord - (mario_xcoord+LEP_WIDTH) < 0 && (enemy_xcoord+34) -(mario_xcoord +LEP_WIDTH) > -34 && (mario_ycoord +LEP_HEIGHT) > enemy_ycoord){
						cout<< "Mario has collided while facing right :DIES" <<endl;
						return true;
					}
				}
return false;
}	

bool Football::check_up(int mario_xcoord, int mario_ycoord) 
{
	if (!alive) return false;
	if(enemy_xcoord - (mario_xcoord+LEP_WIDTH) < 0 && (enemy_xcoord+34) -(mario_xcoord +LEP_WIDTH) > -34 && (mario_ycoord + LEP_HEIGHT) > enemy_ycoord+10 && !((enemy_ycoord - mario_ycoord) < 3)){
				cout<< "attacked from top: kill"<<endl;    
					falling = true;
					alive = false;
					return true;
				}
return false;
}

void Football::setxCoord(int x) 
{
	enemy_xcoord = x;
}

void Football::render_enemy(int gMapLocation_x)
{
	check_bricks();
	if (right_frame > 16) right_frame = 0;
	if (left_frame > 16) left_frame = 0;
	if (falling) {
		if (enemy_ycoord + 10 + FOOTBALL_HEIGHT < SCREEN_HEIGHT) 
			enemy_ycoord += 10;
		else
			return;
	}
	
	if (render_right) {
		enemy_xcoord += right_step;
		SDL_Rect* currentEnemy = &gRightEnemy[right_frame % 4];
		gRightEnemyTexture.render(enemy_xcoord - gMapLocation_x, enemy_ycoord, currentEnemy);
		++right_frame;
	}
	else {
		enemy_xcoord -= left_step;
		SDL_Rect* currentEnemy = &gLeftEnemy[left_frame % 4];
		gLeftEnemyTexture.render( enemy_xcoord - gMapLocation_x, enemy_ycoord, currentEnemy);
		++left_frame;
	}
}	

void Football::check_bricks()
{
	//cout << mapPtr->get_BrickLocation(enemy_xcoord + right_step + FOOTBALL_WIDTH,enemy_ycoord + FOOTBALL_HEIGHT) << endl;
	// Check if brick on enemy bottom right
	if (mapPtr->get_BrickLocation(enemy_xcoord + right_step + FOOTBALL_WIDTH,enemy_ycoord + FOOTBALL_HEIGHT) == 0) {
		//cout << "1\n";
		render_right = false;
		return;
	}
	// Check if brick on enemy bottom left
	if (mapPtr->get_BrickLocation(enemy_xcoord - left_step,enemy_ycoord + FOOTBALL_HEIGHT) == 0) {
		//cout << "2\n";
		render_right = true;
		return;
	}
	// Check if brick on enemy right up
	if (mapPtr->get_BrickLocation(enemy_xcoord + right_step + FOOTBALL_WIDTH,enemy_ycoord) == 1) {
		//		cout << "3\n";
		render_right = false;
		return;
	}	
	// Check if brick on enemy left up
	if (mapPtr->get_BrickLocation(enemy_xcoord - left_step,enemy_ycoord) == 1) {
		//cout << "4\n";
		render_right = true;
		return;
	}
	// Check if brick on enemy right midlevel
	if (mapPtr->get_BrickLocation(enemy_xcoord + right_step + FOOTBALL_WIDTH,enemy_ycoord + BRICK_HEIGHT) == 1) {
		//cout << "5\n";
		render_right = false;
		return;
	}	
	// Check if brick on enemy left midlevel
	if (mapPtr->get_BrickLocation(enemy_xcoord - left_step,enemy_ycoord + BRICK_HEIGHT) == 1) {
		//cout << "6\n";
		render_right = true;
		return;
	}
}