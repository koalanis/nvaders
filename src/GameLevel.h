#ifndef _GAMELEVEL_H_
#define _GAMELEVEL_H_

#include<string>
#include "Level.h"

class GameRunner;

struct GameLevel : public Level
{
  std::string mask;

  bool start;
  bool quit;
  
  GameLevel(GameRunner*);
  virtual ~GameLevel();

  virtual bool isLevelComplete();
  virtual void update(int);
  virtual void draw();
  virtual void init();

};

#endif

