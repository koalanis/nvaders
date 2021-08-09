#ifndef _GameRunner_h
#define _GameRunner_h
#include "../timehelper.h"
#include "Scenes.hpp"
#include <list>
#include <vector>
#include <ncurses.h> /* the ncurses library */
#include <stdlib.h>  /* srand, rand */
#include <string>
#include <time.h>   /* time */
#include <unistd.h> /* sleep */

struct Level;

struct GameRunner {

  int delay;
  int maxWidth;
  int maxHeight;
  int ticksPassed;
  Scenes scenes;
  bool quit;
  int score;

  int currentLevelIndex = 0;
  int menuLevelIndex = 0;
  int gameWonLevelIndex = 0;
  int gameLostLevelIndex = 0;

  std::vector<Level*> levels;
  std::vector<Level *> endgame;
  std::vector<Level *>::iterator currentLevel;
  std::vector<Level *>::iterator lastLevel;

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
