//
//  main.cpp
//  SDL_test
//
//  Created by George Joseph Krug on 3/15/15.
//  Copyright (c) 2015 George Joseph Krug. All rights reserved.
//

#include <iostream>
//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

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

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Current displayed image
SDL_Surface* gCurrentSurface = NULL;
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


int main(int argc, const char * argv[]) {
	SDL_Rect Rect;
	int x_pos = 0;
	int y_pos = 0;
	// main loop flag
	bool quit = false;

	// Event handler
	SDL_Event e;

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
				while ( !quit ) {

					//Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
								break;
                    }
						  //User presses a key
                    if( e.type == SDL_KEYDOWN )
                    {
                        //Select surfaces based on key press
                        switch( e.key.keysym.sym )
                        {
                            case SDLK_UP:
									 	if ( y_pos > 1 )
                            		y_pos -= 10;
                            break;

                            case SDLK_DOWN:
                            	if ( y_pos < SCREEN_HEIGHT - 60 )
											y_pos += 10;
                            break;

                            case SDLK_LEFT:
                            	if ( x_pos > 1 )
											x_pos -= 10;
                            break;

                            case SDLK_RIGHT:
                            	if ( x_pos < SCREEN_WIDTH - 60 )
											x_pos += 10;
                            break;

                            default:
                            	break;
                        } // end switch
                    } // end if
					} // end while
							//Fill the surface white
           				 SDL_FillRect( gScreenSurface, NULL, SDL_MapRGB( gScreenSurface->format, 0xFF, 0xFF, 0xFF ) );
            			//Apply the image stretched
							Rect.x = x_pos;
							Rect.y = y_pos;
							Rect.w = SCREEN_WIDTH/10;
							Rect.h = SCREEN_HEIGHT/10;
							SDL_BlitScaled( gCurrentSurface, NULL, gScreenSurface, &Rect );
							//Update the surface
           	 			SDL_UpdateWindowSurface( gWindow );
							//Wait two seconds
            			//SDL_Delay( 2000 );
						
        		} // end while
			} // end else
    } // end else

    //Free resources and close SDL
    close();

    return 0;
}

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );

        }
    }

    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load default surface
    gCurrentSurface = loadSurface( "Mario.bmp" );
    if( gCurrentSurface == NULL )
    {
        printf( "Failed to load default image!\n" );
        success = false;
    }

    return success;
}

void close()
{
    //Deallocate surface
    SDL_FreeSurface( gCurrentSurface );
    gCurrentSurface = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

SDL_Surface* loadSurface( std::string path )
{
    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }

    return loadedSurface;
}
