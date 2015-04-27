#include "Enemy.h"
//#include "globalConstants.h"
#include <stdexcept>
#include <iostream>
using namespace std;
//Enemy animation right
const int ENEMY_WALKING_FRAMES = 4;
SDL_Rect gRightEnemy[ENEMY_WALKING_FRAMES];
LTexture gRightEnemyTexture;

//Enemy animation left
SDL_Rect gLeftEnemy[ENEMY_WALKING_FRAMES];
LTexture gLeftEnemyTexture;

Enemy::Enemy(int xLocation, int yLocation)
{
	if (!load_enemy())
		throw invalid_argument("Could not load enemy");
	get_coordinates();
	render_enemy();

	cout << "calling constructor\n";

	xCoord = xLocation;
	yCoord = yLocation; 
	
}

bool Enemy::load_enemy()
{
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
}

Enemy::setxCoord(int xLocation){

	xCoord = xLocation;

}

Enemy::render(){
	SDL_Rect* enemyCurrentClip = &gRightEnemy[enemy_frame_right];
	gRightEnemyTexture.render(enemy_xcoord, enemy_ycoord, enemyCurrentClip);
}

