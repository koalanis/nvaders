#ifndef _PlayerShip_h
#define _PlayerShip_h

#include "Ship.h"
#include <ncurses.h>


class PlayerShip: public Ship
{
public:
	PlayerShip(int x, int y);
	virtual ~PlayerShip();

	virtual bool fire();
	virtual void update(int);


};

#endif
