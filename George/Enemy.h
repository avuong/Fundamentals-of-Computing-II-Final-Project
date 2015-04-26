#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "Global_Constants.h"
using namespace std;

class Enemy : public Global_Constants{
	public:
		Enemy();
		virtual bool load_enemy();
		virtual bool check_right();
		virtual bool check_left();
		virtual bool check_up();
		virtual void setxCoord(int);
		virtual void render_enemy(bool);

};

#endif

Enemy::Enemy()
{}

bool Enemy::load_enemy() {}

bool Enemy::check_right() {}

bool Enemy::check_left() {}

bool Enemy::check_up() {}

void Enemy::setxCoord(int x) 
{
	
}

void Enemy::render_enemy(bool is) {}