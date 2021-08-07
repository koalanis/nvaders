#ifndef _GAMELEVEL_H_
#define _GAMELEVEL_H_

#include <list>
#include <memory>
#include <string>

#include "Level.hpp"

class GameRunner;
class PlayerShip;
class GameObject;
class EnemyShip;
class Projectile;

struct GameLevel : public Level {

  bool start;
  bool quit;
  bool win;
  bool done;

  int command;

  int rowsOfEnemies;

  std::shared_ptr<PlayerShip> player;
  std::list<std::shared_ptr<GameObject>> gameObjects;
  std::list<std::shared_ptr<EnemyShip>> hoardObjects;
  std::list<std::shared_ptr<Projectile>> bullets;

  GameLevel(GameRunner *, int);
  GameLevel(GameRunner *);

  virtual ~GameLevel();

  virtual bool isLevelComplete();
  virtual void update(int);
  virtual void draw();
  virtual void init();
  virtual void cleanup();
};

#endif
