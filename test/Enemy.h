#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

class Enemy{
	public:
		Enemy(xCoord, yCoord);
		bool load_enemy();
		setxCoord(int);

	private:
		int xCoord;
		int yCoord;

#endif
