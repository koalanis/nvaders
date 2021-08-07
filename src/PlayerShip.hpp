#ifndef _PlayerShip_h
#define _PlayerShip_h

#include "Ship.hpp"
#include <ncurses.h>

class GameRunner;

class PlayerShip : public Ship {
public:
  PlayerShip(int x, int y);
  virtual ~PlayerShip();

  virtual bool fire();
  bool canUpdate(GameRunner *, int);
  virtual void update(int);
};

#endif
