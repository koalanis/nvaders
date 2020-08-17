#ifndef _PlayerMissle_h
#define _PlayerMissle_h

#include "Projectile.h"

class PlayerMissle: public Projectile
{

public:
  static int instances;

public:
	PlayerMissle(int x, int y);
  virtual ~PlayerMissle();
	virtual void update(int);
  virtual bool isCollision(const GameObject& obj) const;
};


#endif
