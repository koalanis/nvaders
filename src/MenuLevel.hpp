#ifndef _MENULEVEL_H_
#define _MENULEVEL_H_

#include "Level.hpp"
#include <string>

struct MenuLevel : public Level {
  std::string mask;

  bool start;
  bool quit;

  MenuLevel(GameRunner *);
  virtual ~MenuLevel();

  virtual bool isLevelComplete();
  virtual void update(int);
  virtual void draw();
  virtual void init();
  virtual void cleanup();
};

#endif
