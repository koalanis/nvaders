
#ifndef _GAMELOSTLEVEL_H_
#define _GAMELOSTLEVEL_H_

#include "Level.hpp"
#include <string>

class GameRunner;

struct GameLostLevel : public Level {
  std::string mask;
  bool start;
  bool quit;
  int score;

  GameLostLevel(GameRunner *);
  virtual ~GameLostLevel();

  virtual bool isLevelComplete();
  virtual void update(int);
  virtual void draw();
  virtual void init();
  virtual void cleanup();
};

#endif // _GAMELOSTLEVEL_H_
