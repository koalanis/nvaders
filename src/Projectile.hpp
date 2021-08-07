#ifndef _Projectile_h
#define _Projectile_h

#include "GameObject.hpp"

class Projectile : public GameObject {

public:
  int velocity;

public:
  Projectile(int x, int y, char spr);
  virtual ~Projectile();
  virtual void update(int) = 0;
};

#endif
