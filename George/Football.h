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
		virtual bool check_right(int, int);
		virtual bool check_left(int, int);
		virtual bool check_up(int, int);
		virtual void setxCoord(int);
		virtual void render_enemy(int);
		void check_bricks();
      LTexture gRightEnemyTexture;
		SDL_Rect gRightEnemy[5];
		LTexture gLeftEnemyTexture;
		SDL_Rect gLeftEnemy[5];
	private:
		int f_x;
		int f_y;
		int f_h;
		int f_w;
		Map level1;
		Map level2;
		Map * mapPtr;
		int level;
		int right_step;
		int left_step;
		bool render_right = true;
};

#endif


static int right_frame = 0;
static int left_frame = 0;


Football::Football() {}

// Call Football constructor and inherit from Enemy
Football::Football(int xf, int yf, int num_map)
	: level1(gfile1), level2(gfile2)
{
	cout << "here\n";
	right_step = 2;
	left_step = 2;
	level = num_map;
	f_x = BRICK_WIDTH * xf;
	f_y = SCREEN_HEIGHT - yf*BRICK_HEIGHT - FOOTBALL_HEIGHT;
		cout << "here332\n";
	cout << "here22\n";
	if (level == 1)
		mapPtr = &level1;
	else
		mapPtr = &level2;
	check_bricks();
	if (!load_enemy())
		throw invalid_argument("Failed to Load football");
	if (mapPtr->get_BrickLocation(f_x,f_y + FOOTBALL_HEIGHT) == 0 || !render_right) {
		cout << "For " << xf << " and " << yf << endl;
		cout << "For " << f_x << " and " << f_y << endl;
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

bool Football::check_right(int mario_x, int mario_y) 
{

	if (f_x - (mario_x + LEP_WIDTH) < 2 && mario_y + LEP_HEIGHT > f_y ) {
		return true;
	}
	else {
		return false;
	}
}	

bool Football::check_left(int mario_x, int mario_y) 
{
	if (f_x - mario_x < 2 && mario_y + LEP_HEIGHT > f_y)
		return true;
	else {
		return false;
	}
}

bool Football::check_up(int mario_x, int mario_y) 
{
	if (f_x - (mario_x + LEP_WIDTH) < 2 && f_x - mario_x < 2 && mario_y + LEP_HEIGHT < f_y )
		return true;
	else {
		return false;
	}
}

void Football::setxCoord(int x) 
{
	f_x = x;
}

void Football::render_enemy(int gMapLocation_x)
{
	check_bricks();
	if (right_frame > 16) right_frame = 0;
	if (left_frame > 16) left_frame = 0;
	if (render_right) {
		f_x += right_step;
		SDL_Rect* currentEnemy = &gRightEnemy[right_frame % 4];
		gRightEnemyTexture.render(f_x - gMapLocation_x, f_y, currentEnemy);
		++right_frame;
	}
	else {
		f_x -= left_step;
		SDL_Rect* currentEnemy = &gLeftEnemy[left_frame % 4];
		gLeftEnemyTexture.render( f_x - gMapLocation_x, f_y, currentEnemy);
		++left_frame;
	}
}	

void Football::check_bricks()
{
	//cout << mapPtr->get_BrickLocation(f_x + right_step + FOOTBALL_WIDTH,f_y + FOOTBALL_HEIGHT) << endl;
	// Check if brick on enemy bottom right
	if (mapPtr->get_BrickLocation(f_x + right_step + FOOTBALL_WIDTH,f_y + FOOTBALL_HEIGHT) == 0) {
		//cout << "1\n";
		render_right = false;
		return;
	}
	// Check if brick on enemy bottom left
	if (mapPtr->get_BrickLocation(f_x - left_step,f_y + FOOTBALL_HEIGHT) == 0) {
		//cout << "2\n";
		render_right = true;
		return;
	}
	// Check if brick on enemy right up
	if (mapPtr->get_BrickLocation(f_x + right_step + FOOTBALL_WIDTH,f_y) == 1) {
		//		cout << "3\n";
		render_right = false;
		return;
	}	
	// Check if brick on enemy left up
	if (mapPtr->get_BrickLocation(f_x - left_step,f_y) == 1) {
		//cout << "4\n";
		render_right = true;
		return;
	}
	// Check if brick on enemy right midlevel
	if (mapPtr->get_BrickLocation(f_x + right_step + FOOTBALL_WIDTH,f_y + BRICK_HEIGHT) == 1) {
		//cout << "5\n";
		render_right = false;
		return;
	}	
	// Check if brick on enemy left midlevel
	if (mapPtr->get_BrickLocation(f_x - left_step,f_y + BRICK_HEIGHT) == 1) {
		//cout << "6\n";
		render_right = true;
		return;
	}
}
