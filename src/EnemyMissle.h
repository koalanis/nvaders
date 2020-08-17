#ifndef _EnemyMissle_h
#define _EnemyMissle_h

#include "Projectile.h"

class EnemyMissle: public Projectile
{

public:
	EnemyMissle(int x, int y, char ammo);
	virtual void update(int);
};


#endif
