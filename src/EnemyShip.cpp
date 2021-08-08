#include "EnemyShip.hpp"
#include "EnemyMissle.hpp"
#include <stdlib.h> /* srand, rand */

int EnemyShip::velocity = 1;
bool EnemyShip::shiftDown = false;
EnemyShip::EnemyShip(int x, int y, char spr, char ammo)
    : Ship(x, y, spr, ammo) {}

EnemyShip::~EnemyShip() {}

void EnemyShip::update(int cmd) {
  if (EnemyShip::shiftDown == false)
    this->_x += EnemyShip::velocity;
}

bool EnemyShip::fire() {
  if (this->getASCII() == 'W') {
    return rand() % 10000 <= 150;
  } else {
    return rand() % 10000 <= 75;
  }
}
