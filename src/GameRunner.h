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

#include <list>
#include <string>

using std::list;
using std::string;


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
bool quit;
bool win;
bool lose;

	GameRunner();
	~GameRunner();

	void init();
	void run();
	void draw();
	void update(int);
	void cleanup();

};

#endif
