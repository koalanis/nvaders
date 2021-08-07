#include "EnemyMissle.hpp"

EnemyMissle::EnemyMissle(int x, int y, char bullet) : Projectile(x, y, bullet) {
  this->velocity = 1;
}

void EnemyMissle::update(int ch) { this->_y += this->velocity; }
