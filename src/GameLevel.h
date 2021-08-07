#ifndef _GAMELEVEL_H_
#define _GAMELEVEL_H_

#include<string>
#include <list>
#include <memory>

#include "Level.h"


class GameRunner;
class PlayerShip;
class GameObject;
class EnemyShip;
class Projectile;


struct GameLevel : public Level
{

  bool start;
  bool quit;
  bool win;
  bool lose;
  bool done;
  int score;
  std::shared_ptr<PlayerShip> player;
  std::list< std::shared_ptr<GameObject> > gameObjects;
  std::list< std::shared_ptr<EnemyShip>> hoardObjects;
  std::list< std::shared_ptr<Projectile> > bullets;

  GameLevel(GameRunner*);
  virtual ~GameLevel();

  virtual bool isLevelComplete();
  virtual void update(int);
  virtual void draw();
  virtual void init();
  virtual void cleanup();

};

#endif

