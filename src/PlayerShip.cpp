#include "PlayerShip.hpp"
#include "GameRunner.hpp"
#include "PlayerMissle.hpp"
#include <iostream>

PlayerShip::PlayerShip(int x, int y) : Ship(x, y, '^', '|') {
  this->_color = 4;
}

PlayerShip::~PlayerShip() {}

void PlayerShip::update(int cmd) {
  switch (cmd) {
  case KEY_LEFT:
    this->_x--;
    break;
  case KEY_RIGHT:
    this->_x++;
    break;
  default:
    break;
  }
}

bool PlayerShip::canUpdate(GameRunner *gr, int cmd) {
  auto width = gr->maxWidth;
  bool b = false;
  switch (cmd) {
  case KEY_LEFT:
    b = this->getXPos() > 1;
    break;
  case KEY_RIGHT:
    b = this->getXPos() < width - 1;
    break;
  default:
    break;
  }

  return b;
}

bool PlayerShip::fire() {
  if (PlayerMissle::instances < 5) {
    return true;
  }
  return false;
}
