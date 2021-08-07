#include "PlayerMissle.hpp"

int PlayerMissle::instances = 0;

PlayerMissle::PlayerMissle(int x, int y) : Projectile(x, y, '|') {
  this->velocity = -1;
  PlayerMissle::instances += 1;
  this->_color = 6;
}

PlayerMissle::~PlayerMissle() { PlayerMissle::instances -= 1; }

void PlayerMissle::update(int ch) { this->_y += this->velocity; }

bool PlayerMissle::isCollision(const GameObject &obj) const { return true; }
