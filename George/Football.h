#ifndef FOOTBALL_H
#define FOOTBALL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "Global_Constants.h"

using namespace std;

class Football : public Global_Constants {
	public:
		Football(int, int, int, int);
		~Football();
		virtual bool load_enemy();
		virtual bool check_right(int, int);
		virtual bool check_left(int, int);
		virtual bool check_up(int, int);
		virtual void setxCoord(int);
		virtual void render_enemy(bool);
      LTexture gRightEnemyTexture;
		SDL_Rect gRightEnemy[5];
		LTexture gLeftEnemyTexture;
		SDL_Rect gLeftEnemy[5];
	private:
		int f_x;
		int f_y;
		int f_h;
		int f_w;
};

#endif


static int right_frame = 0;
static int left_frame = 0;

// Call Football constructor and inherit from Enemy
Football::Football(int xf, int yf, int wf, int hf)
{
	if (!load_enemy())
		throw invalid_argument("Failed to Load football");
	f_x = xf;
	f_y = yf;
	f_h = hf;
	f_w = wf;
	//gRightEnemy = new SDL_Rect[5];
	//gLeftEnemy = new SDL_Rect[5];
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

void Football::render_enemy(bool render_right)
{
	cout << right_frame << endl;
	if (right_frame > 16) right_frame = 0;
	if (left_frame > 16) left_frame = 0;
	if (render_right) {
		SDL_Rect* currentEnemy = &gRightEnemy[right_frame % 4];
		gRightEnemyTexture.render(200, 200, currentEnemy);
		++right_frame;
	}
	else {
		SDL_Rect* currentEnemy = &gLeftEnemy[left_frame % 4];
		gLeftEnemyTexture.render( 100, 100, currentEnemy);
		++left_frame;
	}
}	


