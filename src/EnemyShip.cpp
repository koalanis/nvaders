#include "EnemyShip.h"
#include <stdlib.h>     /* srand, rand */
#include "EnemyMissle.h"

int EnemyShip::velocity = 1;
bool EnemyShip::shiftDown = false;
EnemyShip::EnemyShip(int x, int y, char spr, char ammo) : Ship(x,y,spr,ammo)
{
}

EnemyShip::~EnemyShip()
{

}

void EnemyShip::update(int cmd)
{
  if(EnemyShip::shiftDown == false)
    this->_x+=EnemyShip::velocity;
}

bool EnemyShip::fire()
{
  if(this->getASCII() == 'W')
  {
    return rand()%1000 <= 150;

  }
  else
  {
    return rand()%1000 <= 75;
  }
}
