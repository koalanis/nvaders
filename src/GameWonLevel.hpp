
#ifndef _GAMEWONLEVEL_H_
#define _GAMEWONLEVEL_H_

#include "Level.hpp"
#include <string>

class GameRunner;

struct GameWonLevel : public Level {
  std::string mask;
  bool start;
  bool quit;
  int score;

  GameWonLevel(GameRunner *);
  virtual ~GameWonLevel();

  virtual bool isLevelComplete();
  virtual void update(int);
  virtual void draw();
  virtual void init();
  virtual void cleanup();
};

#endif // _GAMEWONLEVEL_H_
