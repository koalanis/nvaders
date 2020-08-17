#ifndef _EnemyShip_h
#define _EnemyShip_h

#include "Ship.h"

class EnemyShip: public Ship
{
public:
  static int velocity;
  static bool shiftDown;

public:
        EnemyShip(int x, int y, char spr, char ammo);
        virtual ~EnemyShip();

        virtual bool fire();
        virtual void update(int);


};

#endif
