#ifndef _Ship_h
#define _Ship_h

#include "GameObject.h"

class Ship: public GameObject
{

public:
	char _ammo;

public:
	Ship(int x,int y, char spr, char ammo_spr);
	virtual ~Ship();
	virtual bool fire() = 0;

};


#endif
