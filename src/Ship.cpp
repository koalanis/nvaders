#include "Ship.h"

Ship::Ship(int x, int y, char spr, char ammo) : GameObject(x,y,spr)
{
	this->isAlive = true;
	this->_ammo = ammo;
}

Ship::~Ship()
{}
