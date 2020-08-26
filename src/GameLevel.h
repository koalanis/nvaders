#ifndef _GAMELEVEL_H_
#define _GAMELEVEL_H_

#include<string>
#include <list>

#include "Level.h"


class GameRunner;
class PlayerShip;
class GameObject;
class EnemyShip;
class Projectile;


struct GameLevel : public Level
{
  std::string mask;

  bool start;
  bool quit;
  bool win;
  bool lose;
  bool done;
  int score;
  PlayerShip* player;
  std::list<GameObject*> gameObjects;
  std::list<EnemyShip*> hoardObjects;
  std::list<Projectile*> bullets;
  std::list<GameObject*> deadObjects;


  GameLevel(GameRunner*);
  virtual ~GameLevel();

  virtual bool isLevelComplete();
  virtual void update(int);
  virtual void draw();
  virtual void init();
  virtual void cleanup();

};

#endif

