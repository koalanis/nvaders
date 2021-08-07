#include "EnemyDestroyer.hpp"
EnemyDestroyer::EnemyDestroyer(int x, int y) : EnemyShip(x, y, 'W', '!') {
  this->_color = 7;
}
