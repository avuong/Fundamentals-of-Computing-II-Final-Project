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

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path, std::string color );

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

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
SDL_Rect gBrickLocation;
LTexture gBrick;
vector<vector<int> > gBrickCoordinates;


LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path, std::string color )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		if (color == "white") {
			//Color key image
			SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFF, 0xFF, 0xFF ) );
		}
		else if (color == "green") {
			SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xA4, 0xE0, 0xA0 ) );
		}
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

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
	//Load sprite sheet texture
	if( !gMap.loadFromFile( "background.png", "white" ) )
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
	if( !gBrick.loadFromFile( "brick.png", "green" ) )
	{
		
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
		gBrickLocation.x = 0;	
		gBrickLocation.y = 0;
		gBrickLocation.w = 32;
		gBrickLocation.h = 32;
	}
	
	return success;
}

void get_coordinates()
{
	ifstream map_file;
	string file = "bricks";
	map_file.open(file.c_str());
	vector<int> temp;
	int num;
	while (!map_file.eof()) {
		map_file >> num;
		if (num != 2)
			temp.push_back(num);
		else {
			gBrickCoordinates.push_back(temp);
			temp.clear();
		}
	}
	for (int i = 0; i < gBrickCoordinates.size(); i++) {
		for (int j = 0; j < gBrickCoordinates[i].size(); j++) {
			//cout << gBrickCoordinates[i][j] << ' ';
		}
		//cout << endl;
	}
}
void render_Bricks()
{
	//Render current Map Frame
	SDL_Rect* currentMap = &gBrickLocation;
	int location[2];
	location[X] = 0;
	location[Y] = 0;
	
	for (int i = 0; i < gBrickCoordinates.size(); i++) {
		location[Y] = i*32;
		for (int j = 0; j < gBrickCoordinates[i].size(); j++) {
				//cout << "xloc is " << location[X] << " yloc is " << location[Y] << " gBrickCoordinates[i][j] " << gBrickCoordinates[i][j] << " i is " << i << " j is " << j << endl;
				location[X] = j*32;
				if (gBrickCoordinates[i][j] == 1) {
					currentMap = &gBrickLocation;
				//	cout << "RENDERED: xloc is " << location[X] << " yloc is " << location[Y] << endl;
					gBrick.render( location[X] - gMapLocation.x, location[Y], currentMap );
				}	
		}
		location[Y] = i*32;
	}
	//cout << "size i = " << gBrickCoordinates.size() << "size j = " << gBrickCoordinates[1].size() << endl;
	
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

bool isBrick(int xloc, int yloc)
{
	int x_coord = xloc/BRICK_HEIGHT;
	int x_remainder = xloc % BRICK_HEIGHT;
	int y_coord = (yloc + LEP_HEIGHT) / BRICK_HEIGHT;
	int y_remainder = (yloc + LEP_HEIGHT) % BRICK_HEIGHT;

	if (gBrickCoordinates[y_coord][x_coord] == 1) {
		return true;
	}
	else {
		if (x_remainder > BRICK_WIDTH - LEP_WIDTH) {
			if (gBrickCoordinates[y_coord][x_coord+1] == 1) {
				return true;
			}
		}
	}
	return false;
}
int main( int argc, char* args[] )
{
	get_coordinates();
	usleep(10000);
	int render_mario_yloc = 480-(2*BRICK_HEIGHT)-(LEP_HEIGHT);
	int render_mario_xloc = SCREEN_WIDTH/2;
	int mario_xcoord = SCREEN_WIDTH/2;
	int mario_ycoord = 480-(2*BRICK_HEIGHT)-(LEP_HEIGHT);
	int mario_yvel = 0;
	int canMove = 1;
	//Start up SDL and create window

	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
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
					//User presses a key
				} //delete if need to
                  /*  if( e.type == SDL_KEYDOWN )
                    {
                        //Select surfaces based on key press
                        switch( e.key.keysym.sym )
                        {
                            case SDLK_SPACE:
				//if ( gMapLocation.y > 1 )
                            	mario_ycoord -= 70;	
                            break;

                            case SDLK_DOWN:
                            	if ( gMapLocation.y < SCREEN_HEIGHT - 60 )
											
                            break;

                            case SDLK_LEFT:
                            	if ( gMapLocation.x > 2 ) {
					if (isBrick(mario_xcoord, mario_ycoord) ) {
						frame_left++;
						gMapLocation.x -= 5;	
						mario_xcoord -= 5;
						mario_right = false;
					}
				}
                            break;

                            case SDLK_RIGHT:
                            	if ( gMapLocation.x <  2000 - 500 ) {
					if (isBrick(mario_xcoord, mario_ycoord)) {
						frame_right++;
						gMapLocation.x += 5;	
						mario_xcoord += 5;
						mario_right = true;
					}
				}
                            break;

                            default:
                            	break;
                        } // end switch
                    } // end if

 		if( e.type == SDL_KEYUP )
                    {
                        //Select surfaces based on key press
                        switch( e.key.keysym.sym )
                        {
                            case SDLK_SPACE:
				while (!isBrick(mario_xcoord, mario_ycoord))
                            		mario_ycoord += 1;	
                            break;
			}
		}
				} */
//Set texture based on current keystate
				const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
				if( currentKeyStates[ SDL_SCANCODE_UP ] )
				{	
					if(isBrick(mario_xcoord, mario_ycoord))
					mario_ycoord -= 70;	
				}
				else if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
				{
				}
				else if( currentKeyStates[ SDL_SCANCODE_LEFT ] && canMove==1)
				{
					if ( gMapLocation.x > 2 ) {
						//if(isBrick(mario_xcoord, mario_ycoord) ) {
							frame_left++;
							gMapLocation.x -= 5;	
							mario_xcoord -= 5;
							mario_right = false;
						//}
					}
				}
				else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] && canMove==1)
				{
					if ( gMapLocation.x <  2000 - 500 ) {
						//if (isBrick(mario_xcoord, mario_ycoord)) {
							frame_right++;
							gMapLocation.x += 5;		
							mario_xcoord += 5;
							mario_right = true;
						//}
					}
					
				}
				else if( currentKeyStates[ SDL_SCANCODE_SPACE ] ){
					if(isBrick(mario_xcoord, mario_ycoord))
					mario_ycoord -= 70;	

				}
				/*else if( currentKeyStates[ SDL_SCANCODE_SPACE ]  && currentKeyStates[ SDL_SCANCODE_RIGHT ]){
					if ( gMapLocation.x <  2000 - 500 ) {
						//if (isBrick(mario_xcoord, mario_ycoord)) {
							frame_right++;
							gMapLocation.x += 5;		
							mario_xcoord += 5;
							mario_right = true;
						//}
					}

					if(isBrick(mario_xcoord, mario_ycoord))
						mario_ycoord -= 70;
				}*/	
				else
				{

				}
				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render current Map Frame
				SDL_Rect* currentMap = &gMapLocation;
				gMap.render( 0, 0, currentMap );
	
				// Render Bricks on map
				render_Bricks();
				/*
				if (isBrick(mario_xcoord, mario_ycoord) ) {
					cout << "is Brick is TRUE at " << mario_xcoord << " " << mario_ycoord << endl;
				}
				else {
					cout << "is Brick is FALSE at " << mario_xcoord << " " << mario_ycoord << endl;
				}*/
				if (!isBrick(mario_xcoord, mario_ycoord) ) {
					mario_ycoord += 4;
					cout<< mario_ycoord <<endl;
					if(mario_ycoord > 375){
						canMove = 0;
					}
					/*
					int brick_space = 1;
					while (!isBrick(mario_xcoord, mario_ycoord + brick_space) )
						++brick_space;
					if (brick_space > 6)
						mario_ycoord += 6;
					else
						mario_ycoord += brick_space;
					*/
				}
				if (mario_right) {
					SDL_Rect* currentClip = &gRightSprite[ frame_right / 5 ];
					gRightSpriteTexture.render( render_mario_xloc, mario_ycoord, currentClip );
				}
				else {
					SDL_Rect* currentClipLeft = &gLeftSprite[ frame_left / 5 ];
					gLeftSpriteTexture.render( render_mario_xloc, mario_ycoord, currentClipLeft );
				}
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
				if ( SCREEN_HEIGHT - mario_ycoord <= 50)
					quit = true;
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
