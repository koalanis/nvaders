#include "GameLevel.h"
#include "GameRunner.h"
#include "Level.h"
#include "PlayerShip.h"

#include "EnemyCruiser.h"
#include "EnemyDestroyer.h"
#include "EnemyMissle.h"
#include "GameObject.h"
#include "PlayerMissle.h"
#include "Projectile.h"
#include "Ship.h"
#include <list>
#include <memory>
#include <algorithm>

GameLevel::GameLevel(GameRunner *gr) : Level(gr) {}

GameLevel::~GameLevel() {
  this->cleanup();
}

void GameLevel::draw() {
  this->gameRunner->setColor(1);
  mvprintw(1, 0, this->gameRunner->scenes.border.c_str());
  mvprintw(0, 0, "Points: %i.   'q' to quit.  Ticks:%i\n", this->score, this->gameRunner->ticksPassed);
  if (!this->lose) {
    this->gameRunner->setColor(this->player->getColor());
    mvaddch(1 + this->player->getYPos(), this->player->getXPos(),
            this->player->getASCII());
  }
  for (std::list<std::shared_ptr<GameObject>>::iterator i = this->gameObjects.begin();
       i != this->gameObjects.end(); ++i) {
    this->gameRunner->setColor((*i)->getColor());
    mvaddch(1 + (*i)->getYPos(), (*i)->getXPos(), (*i)->getASCII());
  }
}

void GameLevel::update(int ch) {

  // check if user quit game
  if (ch == 'q') {
    this->gameRunner->kill();
  }

  int playerHeight = 0;
  int enemyHeight = 0;
  int ticksPassed = this->gameRunner->ticksPassed;

  // update bullets first
  for (std::list<std::shared_ptr<Projectile>>::iterator i = this->bullets.begin();
       i != this->bullets.end(); ++i) {
    if ((*i)->getASCII() == '|')
      (*i)->update(ch);
    else {
      if (ticksPassed % 2 == 0) {
        (*i)->update(ch);
      }
    }
  }

  // update player movement
  this->player->update(ch);
  playerHeight = this->player->getYPos();

  // update hoardObjects movement
  if (ticksPassed % 50 == 0) {
    for (std::list<std::shared_ptr<EnemyShip>>::iterator i = this->hoardObjects.begin();
         i != this->hoardObjects.end(); ++i) {
      if ((*i)->getYPos() > enemyHeight)
        enemyHeight = (*i)->getYPos();
      if (((*i)->getXPos() == 1 && EnemyShip::velocity < 0) ||
          ((*i)->getXPos() == 27 && EnemyShip::velocity > 0))
        EnemyShip::shiftDown = true;
    }

    if (EnemyShip::shiftDown) {
      for (std::list<std::shared_ptr<EnemyShip>>::iterator i = this->hoardObjects.begin();
           i != this->hoardObjects.end(); ++i) {
        (*i)->setYPos((*i)->getYPos() + 1);
      }
      EnemyShip::velocity *= -1;
      EnemyShip::shiftDown = false;
    } else {
      for (std::list<std::shared_ptr<EnemyShip>>::iterator i = this->hoardObjects.begin();
           i != this->hoardObjects.end(); ++i) {
        (*i)->update(ch);
      }
    }
  }


  // handle player bullet ship bullet spawning
  if (this->player->fire() && ch == ' ') {
    std::shared_ptr<Projectile> temp = std::make_shared<PlayerMissle> (this->player->getXPos(), this->player->getYPos() - 1);
    temp->isAlive = true;
    this->bullets.push_back(temp);
    this->gameObjects.push_back(temp);
  }


  // handle enemy bullet spawning
  for (std::list<std::shared_ptr<EnemyShip>>::iterator i = this->hoardObjects.begin();
       i != this->hoardObjects.end(); ++i) {
    if ((*i)->fire()) {
      if ((*i)->getASCII() == 'W') {
        std::shared_ptr<Projectile> temp = std::make_shared<EnemyMissle>((*i)->getXPos(), (*i)->getYPos() + 1, '!');
        temp->isAlive = true;
        this->bullets.push_back(temp);
        this->gameObjects.push_back(temp);
      } else {
        std::shared_ptr<Projectile> temp = std::make_shared<EnemyMissle>((*i)->getXPos(), (*i)->getYPos() + 1, '*');
        temp->isAlive = true;
        this->bullets.push_back(temp);
        this->gameObjects.push_back(temp);
      }
    }
  }


  // handle bullet logic
  for (std::list<std::shared_ptr<Projectile>>::iterator i = this->bullets.begin();
       i != this->bullets.end(); ++i) {
    for (std::list<std::shared_ptr<EnemyShip>>::iterator j = this->hoardObjects.begin();
         j != this->hoardObjects.end(); ++j) {
      
      // if playership bullet hits enemy ship
      if ((*i)->getASCII() == '|') {
        if ((*i)->getXPos() == (*j)->getXPos() &&
            (*i)->getYPos() == (*j)->getYPos()) {
          (*j)->isAlive = false;
          (*i)->isAlive = false;
          this->score += 1;
          PlayerMissle::instances--;
        }
      } else {
        // if enemy bullet hits enemy ship
        if ((*i)->getXPos() == (*j)->getXPos() &&
            (*i)->getYPos() == (*j)->getYPos()) {
          (*i)->isAlive = false;
        }
      }
    }

    // if enemy bullet hits player ship
    if ((*i)->getASCII() != '|') {
      if ((*i)->getXPos() == this->player->getXPos() &&
          (*i)->getYPos() == this->player->getYPos()) {
        this->player->isAlive = false;
        (*i)->isAlive = false;
        this->lose = true;
      }
    }


    // if bullet goes out of bounds
    if ((*i)->getYPos() < 0 ||
        (*i)->getYPos() > this->gameRunner->maxHeight - 1) {
      if ((*i)->getASCII() == '|')
        PlayerMissle::instances--;
      (*i)->isAlive = false;
    }
  }

  // cull out dead objects
  this->gameObjects.erase(
    std::remove_if(
      this->gameObjects.begin(),
      this->gameObjects.end(),
      [](std::shared_ptr<GameObject> g){ return !g->isAlive;}
    ), this->gameObjects.end()
  );

  this->hoardObjects.erase(
    std::remove_if(
      this->hoardObjects.begin(),
      this->hoardObjects.end(),
      [](std::shared_ptr<EnemyShip> g){ return !g->isAlive;}
    ),
    this->hoardObjects.end()
  );

  this->bullets.erase(
    std::remove_if(
      this->bullets.begin(),
      this->bullets.end(),
      [](std::shared_ptr<Projectile> g){ return !g->isAlive;}
    ), this->bullets.end()
  );

  // handle endgame logic
  // check if game over
  if (!this->lose) {
    if (this->player->isAlive == false) {
      this->lose = true;
    }
  }

  if (playerHeight == enemyHeight) {
    this->lose = true;
    this->done = true;
  } else {
    // if (this->score == 1) {
    //   this->win = true;
    //   this->done = true;
    // }

    if(this->player->isAlive && this->hoardObjects.empty()) {
      this->win = true;
      this->done = true;
    }
  }
}

bool GameLevel::isLevelComplete() { return this->win || this->lose; }

void createPlayer(GameLevel *gr) {
  gr->player = std::make_shared<PlayerShip>(15, 27);
  std::shared_ptr<GameObject> p = gr->player;
  gr->gameObjects.push_back(p);
}

void createEnemy(GameLevel *gr) {
  for (size_t i = 0; i < 11; i++) {
    if (i % 2 == 0) {
      std::shared_ptr<EnemyShip> temp = std::make_shared<EnemyCruiser>(9 + i, 3);
      gr->gameObjects.push_back(temp);
      gr->hoardObjects.push_back(temp);
    } else {
      std::shared_ptr<EnemyShip> temp = std::make_shared<EnemyDestroyer>(9 + i, 3);      
      gr->gameObjects.push_back(temp);
      gr->hoardObjects.push_back(temp);
    }
  }

  for (size_t i = 0; i < 11; i++) {
    if (i % 2 == 0) {
      std::shared_ptr<EnemyShip> temp = std::make_shared<EnemyDestroyer>(9 + i, 2);
      gr->gameObjects.push_back(temp);
      gr->hoardObjects.push_back(temp);
    } else {
      std::shared_ptr<EnemyShip> temp = std::make_shared<EnemyCruiser>(9 + i, 2);
      gr->gameObjects.push_back(temp);
      gr->hoardObjects.push_back(temp);
    }
  }
}

void GameLevel::init() {

  this->score = 0;
  this->start = true;
  this->lose = false;
  this->win = false;
  createPlayer(this);
  createEnemy(this);
}

void GameLevel::cleanup() {
  this->bullets.clear();
  this->hoardObjects.clear();
  this->gameObjects.clear();
  this->bullets.clear();
}
