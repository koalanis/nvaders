#include "PlayerShip.h"
#include <iostream>
#include "PlayerMissle.h"

PlayerShip::PlayerShip(int x, int y) : Ship(x,y,'^','|')
{
}

PlayerShip::~PlayerShip()
{
}

void PlayerShip::update(int cmd)
{
	switch (cmd) {
		case KEY_LEFT:
			if(this->_x > 1)
				this->_x--;
			break;
		case KEY_RIGHT:
			if(this->_x < 27)
				this->_x++;
				break;
		default:
			break;
	}
}

bool PlayerShip::fire()
{
	if(PlayerMissle::instances < 5)
	{
		return true;
	}
	return false;
}
