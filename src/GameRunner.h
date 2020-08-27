#ifndef _GameRunner_h
#define _GameRunner_h
#include <ncurses.h>    /* the ncurses library */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <unistd.h> 	/* sleep */
#include "../timehelper.h"
#include "Scenes.h"
#include <list>
#include <string>


struct Level;

struct GameRunner
{

	int delay;
	int maxWidth;
	int maxHeight;
	int ticksPassed;
	Scenes scenes;
	bool quit;

	std::list<Level*> levels;
	std::list<Level*>::iterator currentLevel;
	std::list<Level*>::iterator lastLevel;


	GameRunner();
	~GameRunner();

	// void init();
	void start();

	void setColor(int);
	// bool shouldLoopRun();
	// void draw();
	// void update(int);
	void kill();
	// void loop();
	// void cleanup();

};

#endif
