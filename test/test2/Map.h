#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "Global_Constants.h"

using namespace std;

class Map : public Global_Constants{
	public:
		Map();
		Map(string);
		bool load_bricks();
		void get_coordinates();
		void render_Bricks(int);
		bool isBrick_down(int, int);
		bool isBrick_up(int, int);
		bool isBrick_right(int, int);
		bool isBrick_left(int, int);
		int space_brick_down(int, int);
		int space_brick_up(int, int);
		// Brick Rendering
		SDL_Rect BrickLocation;
		LTexture Brick;
	private:
		vector<vector<int> > BrickCoordinates;
		string file;
};

#endif

Map::Map() {}

Map::Map(string f)
{
	file = f;
	//if (!load_bricks())
		//throw invalid_argument("Could not load bricks");
	get_coordinates();
	//render_Bricks(0);
}

bool Map::load_bricks()
{
	bool success = true;
	//Load sprite sheet texture
	if( !Brick.loadFromFile("brick.png", "green" ) )
	{
		cout << "failed to load " << file << endl;
		success = false;
	}
	else
	{
		BrickLocation.x = 0;	
		BrickLocation.y = 0;
		BrickLocation.w = 32;
		BrickLocation.h = 32;
	}
	return success;
}
void Map::get_coordinates()
{
	ifstream map_file;
	map_file.open(file.c_str());
	vector<int> temp;
	int num;
	while (!map_file.eof()) {
		map_file >> num;
		if (num != 2)
			temp.push_back(num);
		else {
			BrickCoordinates.push_back(temp);
			temp.clear();
		}
	}
}
void Map::render_Bricks(int gMapLocation_x)
{
	//Render current Map Frame
	SDL_Rect* currentMap = &BrickLocation;
	int location[2];
	location[X] = 0;
	location[Y] = 0;
	
	for (int i = 0; i < BrickCoordinates.size(); i++) {
		location[Y] = i*32;
		for (int j = 0; j < BrickCoordinates[i].size(); j++) {
				//cout << "xloc is " << location[X] << " yloc is " << location[Y] << " BrickCoordinates[i][j] " << BrickCoordinates[i][j] << " i is " << i << " j is " << j << endl;
				location[X] = j*32;
				if (BrickCoordinates[i][j] == 1) {
					currentMap = &BrickLocation;
				//	cout << "RENDERED: xloc is " << location[X] << " yloc is " << location[Y] << endl;
					Brick.render( location[X] - gMapLocation_x, location[Y], currentMap );
				}	
		}
		location[Y] = i*32;
	}
	//cout << "size i = " << BrickCoordinates.size() << "size j = " << BrickCoordinates[1].size() << endl;
	
}

bool Map::isBrick_down(int xloc, int yloc)
{
	int x_coord = xloc/BRICK_HEIGHT;
	int x_remainder = xloc % BRICK_HEIGHT;
	int y_coord = (yloc + LEP_HEIGHT- 3) / BRICK_HEIGHT;
	int y_remainder = (yloc + LEP_HEIGHT) % BRICK_HEIGHT;

	if (BrickCoordinates[y_coord][x_coord] == 1 && x_remainder < LEP_WIDTH- 5) {
		return true;
	}
	else {
		if (x_remainder > BRICK_WIDTH- LEP_WIDTH+ 5) {
			if (BrickCoordinates[y_coord][x_coord+1] == 1) {
				return true;
			}
		}
	}
	return false;
}

bool Map::isBrick_up(int xloc, int yloc)
{
	int x_coord = xloc/BRICK_HEIGHT;
	int x_remainder = xloc % BRICK_HEIGHT;
	int y_coord = (yloc + 4) / BRICK_HEIGHT;
	int y_remainder = (yloc) % BRICK_HEIGHT;

	if (BrickCoordinates[y_coord][x_coord] == 1 && x_remainder < LEP_WIDTH- 5) {
		return true;
	}
	else {
		if (x_remainder > BRICK_WIDTH- LEP_WIDTH+ 5) {
			if (BrickCoordinates[y_coord][x_coord+1] == 1) {
				return true;
			}
		}
	}
	return false;
}

bool Map::isBrick_right(int xloc, int yloc)
{
	int x_coord = (xloc + LEP_WIDTH+ 2) / BRICK_HEIGHT;
	int x_remainder = (xloc + LEP_WIDTH) % BRICK_HEIGHT;
	int y_coord = (yloc) / BRICK_HEIGHT;
	int y_remainder = (yloc) % BRICK_HEIGHT;
	if (BrickCoordinates[y_coord][x_coord] == 1) {
		return true;
	}
	else if (BrickCoordinates[y_coord + 1][x_coord] == 1)
		return true;
	else {
			return false;
	}
}

bool Map::isBrick_left(int xloc, int yloc)
{
	int x_coord = (xloc) / BRICK_HEIGHT;
	int x_remainder = (xloc) % BRICK_HEIGHT;
	int y_coord = (yloc) / BRICK_HEIGHT;
	int y_remainder = (yloc) % BRICK_HEIGHT;
	if (BrickCoordinates[y_coord][x_coord] == 1) {
		return true;
	}
	else if (BrickCoordinates[y_coord + 1][x_coord] == 1)
		return true;
	else {
			return false;
	}
}

int Map::space_brick_down(int xloc, int yloc) 
{
	int brick_space = 0;
	do					
	{
	++brick_space;
	if (brick_space + yloc + LEP_HEIGHT== SCREEN_HEIGHT) 
		break;
	} while (!isBrick_down(xloc, yloc + brick_space) ); 
	
	return brick_space;
}

int Map::space_brick_up(int xloc, int yloc)
{
	int brick_space = 0;
	do					
	{
	++brick_space;
	if (yloc - brick_space == 0) 
		break;
	} while (!isBrick_up(xloc, yloc - brick_space) ); 
	
	return brick_space;
}
