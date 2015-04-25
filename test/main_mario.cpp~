/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <iostream>
#include "LTexture.h"
#include "Map.h"
//#include "globalConstants.h"

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 480;
const int X = 0;
const int Y = 1;
const int BRICK_HEIGHT = 32;
const int BRICK_WIDTH = 32;
const int LEP_HEIGHT = 45;
const int LEP_WIDTH = 27;

//Key press surfaces constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

const int ENEMY_WALKING_FRAMES = 4;
SDL_Rect gRightEnemy[ENEMY_WALKING_FRAMES];
LTexture gRightEnemyTexture;

SDL_Rect gLeftEnemy[ENEMY_WALKING_FRAMES];
LTexture gLeftEnemyTexture;

//Texture wrapper class


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//Walking animation right
const int WALKING_ANIMATION_FRAMES = 5;
SDL_Rect gRightSprite[ WALKING_ANIMATION_FRAMES ];
LTexture gRightSpriteTexture;

//Walking animation left
SDL_Rect gLeftSprite[ WALKING_ANIMATION_FRAMES ];
LTexture gLeftSpriteTexture;


// Map rendering
SDL_Rect gMapLocation;
LTexture gMap;

// Brick Rendering
string gfile1 = "bricks";
string gfile2 = "bricks2";
Map level_one(gfile1);
Map level_two(gfile2);
Map * levelPtr = &level_one;

//Pot of Gold Rendering
SDL_Rect gGoldLocation;
LTexture gGold;

//Level 2 Transition
SDL_Rect gtransition_level2;
LTexture gtransl2;

//Shamrock Rendering
SDL_Rect gShamrockLocation;
LTexture gShamrock;


string backgroundName = "background.png";
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	
	//Loading success flag
	bool success = true;

	//Load sprite sheet texture going right
	if( !gRightSpriteTexture.loadFromFile( "right_lep.png", "white" ) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
		//Set sprite clips
		gRightSprite[ 0 ].x = 0;
		gRightSprite[ 0 ].y = 0;
		gRightSprite[ 0 ].w =  27;
		gRightSprite[ 0 ].h = 43;

		gRightSprite[ 1 ].x =  27;
		gRightSprite[ 1 ].y =  0;
		gRightSprite[ 1 ].w =  27;
		gRightSprite[ 1 ].h = 43;
		
		gRightSprite[ 2 ].x = 54;
		gRightSprite[ 2 ].y = 0;
		gRightSprite[ 2 ].w =  27;
		gRightSprite[ 2 ].h = 43;

		gRightSprite[ 3 ].x = 81;
		gRightSprite[ 3 ].y = 0;
		gRightSprite[ 3 ].w = 27;
		gRightSprite[ 3 ].h = 43;

		gRightSprite[ 4 ].x = 108;
		gRightSprite[ 4 ].y = 0;
		gRightSprite[ 4 ].w = 27;
		gRightSprite[ 4 ].h = 43;
	}


	//Load sprite sheet texture going left
	if( !gLeftSpriteTexture.loadFromFile( "left_lep.png", "white" ) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
		//Set sprite clips
		gLeftSprite[ 0 ].x = 108;
		gLeftSprite[ 0 ].y = 0;
		gLeftSprite[ 0 ].w =  27;
		gLeftSprite[ 0 ].h = 43;

		gLeftSprite[ 1 ].x =  81;
		gLeftSprite[ 1 ].y =  0;
		gLeftSprite[ 1 ].w =  27;
		gLeftSprite[ 1 ].h = 43;
		
		gLeftSprite[ 2 ].x = 54;
		gLeftSprite[ 2 ].y = 0;
		gLeftSprite[ 2 ].w =  27;
		gLeftSprite[ 2 ].h = 43;

		gLeftSprite[ 3 ].x = 27;
		gLeftSprite[ 3 ].y = 0;
		gLeftSprite[ 3 ].w = 27;
		gLeftSprite[ 3 ].h = 43;

		gLeftSprite[ 4 ].x = 27;
		gLeftSprite[ 4 ].y = 0;
		gLeftSprite[ 4 ].w = 27;
		gLeftSprite[ 4 ].h = 43;
	}

if( !gRightEnemyTexture.loadFromFile( "football_right.png", "white") )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
		//Set sprite clips
		gRightEnemy[ 0 ].x = 2;
		gRightEnemy[ 0 ].y = 0;
		gRightEnemy[ 0 ].w = 34;
		gRightEnemy[ 0 ].h = 51;

		gRightEnemy[ 1 ].x =  53;
		gRightEnemy[ 1 ].y =  0;
		gRightEnemy[ 1 ].w =  87 - 53;
		gRightEnemy[ 1 ].h = 51;
		
		gRightEnemy[ 2 ].x = 100;
		gRightEnemy[ 2 ].y = 0;
		gRightEnemy[ 2 ].w = 134 - 100;
		gRightEnemy[ 2 ].h = 51;

		gRightEnemy[ 3 ].x = 152;
		gRightEnemy[ 3 ].y = 0;
		gRightEnemy[ 3 ].w = 185 - 152;
		gRightEnemy[ 3 ].h = 51;
	}

	if( !gLeftEnemyTexture.loadFromFile( "football_left.png", "white") )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
		//Set sprite clips
		gLeftEnemy[ 0 ].x = 7;
		gLeftEnemy[ 0 ].y = 0;
		gLeftEnemy[ 0 ].w =  41-7;
		gLeftEnemy[ 0 ].h = 50;

		gLeftEnemy[ 1 ].x =  54;
		gLeftEnemy[ 1 ].y =  0;
		gLeftEnemy[ 1 ].w =  89 - 54;
		gLeftEnemy[ 1 ].h = 50;
		
		gLeftEnemy[ 2 ].x = 103;
		gLeftEnemy[ 2 ].y = 0;
		gLeftEnemy[ 2 ].w = 138 - 103;
		gLeftEnemy[ 2 ].h = 50;

		gLeftEnemy[ 3 ].x = 152;
		gLeftEnemy[ 3 ].y = 0;
		gLeftEnemy[ 3 ].w = 186 - 152;
		gLeftEnemy[ 3 ].h = 50;
	}

	//Load sprite sheet texture
	if( !gMap.loadFromFile( backgroundName.c_str(), "white" ) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
		gMapLocation.x = 0;	
		gMapLocation.y = 0;
		gMapLocation.w = SCREEN_WIDTH;
		gMapLocation.h = SCREEN_HEIGHT;
	}	
	//Load sprite sheet texture
	if( !gGold.loadFromFile( "gold.png", "white" ) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
		gGoldLocation.x = 0;	
		gGoldLocation.y = 0;
		gGoldLocation.w = 200;
		gGoldLocation.h = 200;
	}

	if( !gShamrock.loadFromFile( "shamrock.png", "white" ) ) 
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
		gShamrockLocation.x = 0;	
		gShamrockLocation.y = 0;
		gShamrockLocation.w = 48;
		gShamrockLocation.h = 48;
	}
	//Load transition
	if( !gtransl2.loadFromFile( "level2.png", "green" ) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
		gtransition_level2.x = 0;	
		gtransition_level2.y = 0;
		gtransition_level2.w = 500;
		gtransition_level2.h = 500;
	}
	
	return success;
}

void close()
{
	//Free loaded images
	gRightSpriteTexture.free();
	gLeftSpriteTexture.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


int isPotCollide(int potLocX, int spriteX, int potLocY, int spriteY)
{
	if( spriteX - potLocX >= 1500 && spriteX - potLocX <= 1580 && spriteY >= 369)
		return 1;
	else
		return 0;
}
int main( int argc, char* args[] )
{
	levelPtr->get_coordinates();
	usleep(10000);
	int render_mario_yloc = 480-(2*BRICK_HEIGHT)-(LEP_HEIGHT);
	int render_mario_xloc = SCREEN_WIDTH/2;
	int mario_xcoord = SCREEN_WIDTH/2;
	int mario_ycoord = 480-(2*BRICK_HEIGHT)-(LEP_HEIGHT);
	bool jumping = false;
	bool mario_down = false;
	int jump_height = 0;
	int max_jump_height = 150;
	int mario_yVel= 0;
	int didShamrockCollide = 0;
	int enemy_xcoord = SCREEN_WIDTH/2 + 50;
	int enemy_ycoord = 480-(2*BRICK_HEIGHT)-(LEP_HEIGHT)-7;
	int enemy_frame_right = 0;
	int enemyDead = 0;
	int marioDead = 0;
	int moveRight = 1;
	int moveLeft = 0;
	int movementCount = 0;
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		if (!levelPtr->load_bricks() )
		{
			printf("failed to load bricks map\n");
		}
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Current animation frame
			int frame_right = 0;
			int frame_left = 0;
			bool mario_right = true;

			//Current enemy animation frame
			//int enemy_frame_right = 0;
			//int enemy_frame_left = 0;
			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}
            const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
				if( currentKeyStates[ SDL_SCANCODE_UP ] )
				{	
					if(levelPtr->isBrick_down(mario_xcoord, mario_ycoord)){
						//mario_ycoord -= max_jump_height;
					if (!jumping)
					{
  						jumping = true;
  						mario_yVel = 0;
					}
					}
					
				}
				else if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
				{
				}
				else if( currentKeyStates[ SDL_SCANCODE_LEFT ])
				{
					if ( gMapLocation.x > 2  && !levelPtr->isBrick_left(mario_xcoord, mario_ycoord) ) {
						//if(isBrick(mario_xcoord, mario_ycoord) ) {
							frame_left++;
							gMapLocation.x -= 5;	
							mario_xcoord -= 5;
							mario_right = false;
						//}
					}
				}
				else if( currentKeyStates[ SDL_SCANCODE_RIGHT ])
				{
					if ( gMapLocation.x <  2000 - 500 && !levelPtr->isBrick_right(mario_xcoord, mario_ycoord) ) {
						//if (isBrick(mario_xcoord, mario_ycoord)) {
							frame_right++;
							gMapLocation.x += 5;		
							mario_xcoord += 5;
							mario_right = true;
						//}
					}
					
				}
				if (jumping == true)
				{
					if (!levelPtr->isBrick_up(mario_xcoord, mario_ycoord)) {
						int brick_space_up = levelPtr->space_brick_up(mario_xcoord, mario_ycoord);
						if (brick_space_up > 6)
							mario_yVel -= 6;
						else
							mario_yVel -= brick_space_up;
					mario_ycoord = mario_ycoord + mario_yVel;
					}
					else {
						mario_yVel = -60;
						jumping = false;
					}
					if (mario_yVel == -60)
					{
						mario_yVel = 0;
						//mario_yVel += 60;
						jumping = false;
					}
				}
				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render current Map Frame
				SDL_Rect* currentMap = &gMapLocation;
				gMap.render( 0, 0, currentMap );
	
				// Render Bricks on map
				levelPtr->render_Bricks(gMapLocation.x);
				
				//Render pot of Gold
				SDL_Rect* potOfGold = &gGoldLocation;
				gGold.render(1670- gMapLocation.x, 330, potOfGold);

				//Render shamrock
				if(!(mario_xcoord > 1205 && mario_xcoord < 1250 && (mario_ycoord + 27) == 431) && didShamrockCollide == 0 ){
					SDL_Rect * shamrock = &gShamrockLocation;
					gShamrock.render(1228 - gMapLocation.x, 395, shamrock);
				} //render only if mario doesn't collide

				if(mario_xcoord > 1205 && mario_xcoord < 1250 && (mario_ycoord + 27) == 433)
						didShamrockCollide = 1;
				//cout<< "Pot loc x: " << 1670- gMapLocation.x <<endl;
				//cout<<"mario x " << mario_xcoord<< " mario y "<< mario_ycoord +27 <<endl;
				

				if (!levelPtr->isBrick_down(mario_xcoord, mario_ycoord)) {
					int brick_space_down = levelPtr->space_brick_down(mario_xcoord, mario_ycoord);
					if (brick_space_down > 20)
						mario_ycoord += 20;
					else
						mario_ycoord += brick_space_down;
				}
				if (mario_right) {
					SDL_Rect* currentClip = &gRightSprite[ frame_right / 5 ];
					gRightSpriteTexture.render( render_mario_xloc, mario_ycoord, currentClip );
				}
				else {
					SDL_Rect* currentClipLeft = &gLeftSprite[ frame_left / 5 ];
					gLeftSpriteTexture.render( render_mario_xloc , mario_ycoord, currentClipLeft );
				}


				//Movement of enemy
				//*******************************************
				if(moveRight==1){
					enemy_xcoord++;
					SDL_Rect* enemyCurrentClip = &gRightEnemy[enemy_frame_right];
					gRightEnemyTexture.render(enemy_xcoord - gMapLocation.x, enemy_ycoord, enemyCurrentClip);
					if(movementCount==70){
						moveRight = 0;
						moveLeft = 1;
						movementCount = 0;
					}
				}
	
				if(moveLeft==1){
					enemy_xcoord--;
					SDL_Rect* enemyCurrentClip = &gLeftEnemy[enemy_frame_right];
					gLeftEnemyTexture.render(enemy_xcoord - gMapLocation.x, enemy_ycoord, enemyCurrentClip);
					if(movementCount==70){
						moveRight = 1;
						moveLeft = 0;
						movementCount = 0;
					}
				}

				movementCount++;
				cout<< mario_ycoord+ 40 << " " <<enemy_ycoord<<endl;
				//COLLISION IN THE WORKS for football player
				//********************************************************************************
				if((mario_ycoord+ 40 - enemy_ycoord > 0  && enemy_xcoord - (mario_xcoord + 23) < 0 && enemy_xcoord - (mario_xcoord + 23) > -38) && !((enemy_ycoord - mario_ycoord) < 3)|| (mario_ycoord + 40 - enemy_ycoord > 0 && (enemy_xcoord + 46) - (mario_xcoord) > 0 && enemy_xcoord - (mario_xcoord + 23) < -46)&& !((enemy_ycoord - mario_ycoord) < 3)){
				cout<< "attacked from top: kill"<<endl;
				enemyDead = 1;
				}

				if(mario_right){
					if(enemy_xcoord - (mario_xcoord + 23) < 0 && enemy_xcoord - (mario_xcoord + 23) > -38 && (enemy_ycoord - mario_ycoord) < 3){
						cout<< "Mario has collided while facing right :DIES" <<endl;
						marioDead = 1;
					}
				}
				else{
					if((enemy_xcoord + 46) - (mario_xcoord) > 0 && enemy_xcoord - (mario_xcoord + 23) < -46 && (enemy_ycoord - mario_ycoord) < 3){
					cout<< "mario collides facing left:DIES"<<endl;
					marioDead = 1;
					}
				}

				if(enemyDead==1 && enemy_ycoord < 500){
					enemy_ycoord+=7; //make the enemy fall off the screen
				}
				
				if(marioDead==1 && mario_ycoord < 500){
					mario_ycoord+=7;
				}

				//***************************************************************************************
				//cout<< "mario x " << mario_xcoord + 23 << " football x " << enemy_xcoord <<endl; 

				enemy_frame_right++;
				if(enemy_frame_right == 3) enemy_frame_right = 0 ;				
				//if(enemy_xcoord < SCREEN_WIDTH/2 + 200) 
				//	enemy_xcoord++;
				//if(enemy_xcoord == SCREEN_WIDTH/2)
				//	enemy_xcoord--;
				//Update screen
				SDL_RenderPresent( gRenderer );

				//Go to next frame
				//++frame;

				//Cycle animation
				if( frame_right / 5 >= WALKING_ANIMATION_FRAMES )
				{
					frame_right = 0;
				}
				//Cycle animation
				if( frame_left / 5 >= WALKING_ANIMATION_FRAMES )
				{
					frame_left = 0;
				}

				// Transisiton to next level. NEED TO KNOW EXACT POINT OF gMapLocation.x
				// ************************************************************
				if (isPotCollide(1670- gMapLocation.x, mario_xcoord, 330, mario_ycoord + 27)) {
					if (levelPtr == &level_one) {
						gMapLocation.x = 0;
						mario_xcoord = SCREEN_WIDTH/2;
						mario_ycoord = 480-(2*BRICK_HEIGHT)-(LEP_HEIGHT);
						levelPtr = &level_two;
						if (!levelPtr->load_bricks() ) quit = true;
					}
				//****************************************************************
					else {
						quit = true;
					}
					if (!quit) {
						//Render current Map Frame
						SDL_Rect* l2 = &gtransition_level2;
						gtransl2.render( 0, 0, l2 );
						//Update screen
						SDL_RenderPresent( gRenderer );
						do {
							SDL_PollEvent(&e);
						}
						while( e.type == SDL_KEYUP );
					}
				}
				if (SCREEN_HEIGHT - mario_ycoord <= 46) quit = true;
			}
		}
	}
	
	//Free resources and close SDL
	close();

	return 0;
}
