#ifndef _GameRunner_h
#define _GameRunner_h
#include <ncurses.h>    /* the ncurses library */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <unistd.h> 	/* sleep */
#include "../timehelper.h"
#include "PlayerShip.h"
#include "Scenes.h"
#include "GameObject.h"
#include "Ship.h"
#include "Projectile.h"
#include "PlayerMissle.h"
#include "EnemyMissle.h"
#include "EnemyCruiser.h"
#include "EnemyDestroyer.h"
#include "MenuLevel.h"
#include "GameLevel.h"
#include <list>
#include <string>

using std::list;
using std::string;

struct Level;

struct GameRunner
{

int delay;
std::list<GameObject*> gameObjects;
std::list<EnemyShip*> hoardObjects;
std::list<Projectile*> bullets;
std::list<GameObject*> deadObjects;
PlayerShip* player;
int maxWidth;
int maxHeight;
int ticksPassed;
int score;
bool done;
Scenes scenes;
bool quit;
bool win;
bool lose;
std::list<Level*> levels;
std::list<Level*>::iterator currentLevel;
std::list<Level*>::iterator lastLevel;


	GameRunner();
	~GameRunner();

	// void init();
	void start();
	// bool shouldLoopRun();
	// void draw();
	// void update(int);
	void kill();
	// void loop();
	// void cleanup();

};

#endif
