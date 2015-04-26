#include "Enemy.h"

Enemy::Enemy(int x, int y, int w, int h)
{
	xCoord = x;	
	yCoord = y;
	width = w;
	height = h;
}

bool Enemy::load_enemy() {}

bool Enemy::check_right() {}

bool Enemy::check_left() {}

bool Enemy::check_up() {}

void Enemy::setxCoord(int x) 
{
	xCoord = x;
}


