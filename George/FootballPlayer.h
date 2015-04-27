#ifndef FOOTBALLPLAYER_H
#define FOOTBALLPLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "Enemy.h"
//#include "Game.h"

using namespace std;

class FootballPlayer : public Enemy {
	public:
		FootballPlayer();
		~FootballPlayer();
		FootballPlayer(int, int, int);
		virtual bool load_enemy(string, string);
		virtual bool mario_die(int, int);
		virtual bool check_up(int, int, int);
		virtual void setxCoord(int);
		virtual void render_enemy(int);
	private:
		string playerpngLeft = "football_left.png";
		string playerpngRight = "football_right.png";
};

#endif


static int right_frame = 0;
static int left_frame = 0;


FootballPlayer::FootballPlayer() {}

// Call FootballPlayer constructor and inherit from Enemy
FootballPlayer::FootballPlayer(int xf, int yf, int num_map)
	: Enemy(xf, yf, num_map, 1)
{
	if (!load_enemy(playerpngLeft, playerpngRight))
		throw invalid_argument("Failed to Load FootballPlayer");
	if (Enemy::Enemy::mapPtr->get_BrickLocation(Enemy::enemy_xcoord,Enemy::enemy_ycoord + FootballPlayer_HEIGHT) == 0 || !Enemy::render_right) {
		cout << "For " << xf << " and " << yf << endl;
		cout << "For " << Enemy::enemy_xcoord << " and " << Enemy::enemy_ycoord << endl;
		if (!Enemy::render_right) cout << "cant render right\n";
		throw invalid_argument("Footaball player must be placed on a brick");
	}
}

FootballPlayer::~FootballPlayer()
{
	//delete [] gRightEnemy;
	//delete [] gLeftEnemy;
}
bool FootballPlayer::load_enemy(string left, string right)
{
	return Enemy::load_enemy(playerpngLeft, playerpngRight);
}

bool FootballPlayer::mario_die(int mario_xcoord, int mario_ycoord) 
{
if(!(Enemy::enemy_xcoord - (mario_xcoord+LEP_WIDTH) < 0 && (Enemy::enemy_xcoord+34) -(mario_xcoord +LEP_WIDTH) > -34 && (mario_ycoord +LEP_HEIGHT) > Enemy::enemy_ycoord && !((Enemy::enemy_ycoord - mario_ycoord) < 3))){
					if(Enemy::enemy_xcoord - (mario_xcoord+LEP_WIDTH) < 0 && (Enemy::enemy_xcoord+34) -(mario_xcoord +LEP_WIDTH) > -34 && (mario_ycoord +LEP_HEIGHT) > Enemy::enemy_ycoord){
						cout<< "Mario has collided while facing right :DIES" <<endl;
						return true;
					}
				}
return false;
}	

bool FootballPlayer::check_up(int mario_xcoord, int mario_ycoord, int yVel) 
{
	if (!Enemy::alive) return false;
	if(Enemy::enemy_xcoord - (mario_xcoord+LEP_WIDTH) < 0 && (Enemy::enemy_xcoord+34) -(mario_xcoord +LEP_WIDTH) > -34 && (mario_ycoord + LEP_HEIGHT) > Enemy::enemy_ycoord+10 && !((Enemy::enemy_ycoord - mario_ycoord) < 3)){
				cout<< "attacked from top: kill"<<endl;    
					Enemy::falling = true;
					Enemy::alive = false;
					return true;
				}
return false;
}

void FootballPlayer::setxCoord(int x) 
{
	Enemy::enemy_xcoord = x;
}

void FootballPlayer::render_enemy(int gMapLocation_x)
{
	check_bricks();
	if (right_frame > 16) right_frame = 0;
	if (left_frame > 16) left_frame = 0;
	if (Enemy::falling) {
		if (Enemy::enemy_ycoord + 10 + FootballPlayer_HEIGHT < SCREEN_HEIGHT) 
			Enemy::enemy_ycoord += 10;
		else
			return;
	}
	
	if (Enemy::render_right) {
		Enemy::enemy_xcoord += Enemy::right_step;
		SDL_Rect* currentEnemy = &Enemy::gRightEnemy[right_frame % 4];
		Enemy::gRightEnemyTexture.render(Enemy::enemy_xcoord - gMapLocation_x, Enemy::enemy_ycoord, currentEnemy);
		++right_frame;
	}
	else {
		Enemy::enemy_xcoord -= Enemy::left_step;
		SDL_Rect* currentEnemy = &Enemy::gLeftEnemy[left_frame % 4];
		Enemy::gLeftEnemyTexture.render( Enemy::enemy_xcoord - gMapLocation_x, Enemy::enemy_ycoord, currentEnemy);
		++left_frame;
	}
}	

