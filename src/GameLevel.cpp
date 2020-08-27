#include "GameLevel.h"
#include "Level.h"
#include "GameRunner.h"
#include "PlayerShip.h"

#include "GameObject.h"
#include "Ship.h"
#include "Projectile.h"
#include "PlayerMissle.h"
#include "EnemyMissle.h"
#include "EnemyCruiser.h"
#include "EnemyDestroyer.h"
#include <list>


GameLevel::GameLevel(GameRunner* gr) : Level(gr) 
{
}

GameLevel::~GameLevel() 
{}

void GameLevel::draw() 
{
  this->gameRunner->setColor(1);
  mvprintw(1,0,  this->gameRunner->scenes.border.c_str());
  mvprintw(0, 0, "Points: %i.   'q' to quit.\n", this->score);
  if(!this->lose)
  {
    this->gameRunner->setColor(this->player->getColor());
    mvaddch(1+this->player->getYPos(), this->player->getXPos(), this->player->getASCII());
  }
  for (std::list<GameObject*>::iterator i = this->gameObjects.begin(); i != this->gameObjects.end(); ++i)
  {
    this->gameRunner->setColor((*i)->getColor());
    mvaddch(1+(*i)->getYPos(), (*i)->getXPos(), (*i)->getASCII());
  }

}

void GameLevel::update(int ch)
{

  if(ch == 'q') 
  {
    this->gameRunner->kill();
  }

  int playerHeight = 0;
	int enemyHeight = 0;
  int ticksPassed = this->gameRunner->ticksPassed;
  //update bullets first
	for (std::list<Projectile*>::iterator i = this->bullets.begin(); i != this->bullets.end(); ++i)
	{  if((*i)->getASCII() == '|')
		    (*i)->update(ch);
    else
    {
      if(ticksPassed%2==0)
      {
        (*i)->update(ch);
      }
    }
	}

	//update player
	this->player->update(ch);
	playerHeight =this->player->getYPos();
	//update hoardObjects

  if(ticksPassed%20==0)
  {
    for (std::list<EnemyShip*>::iterator i = this->hoardObjects.begin(); i != this->hoardObjects.end(); ++i)
  	{
  		if((*i)->getYPos()>enemyHeight)
  			enemyHeight = (*i)->getYPos();
  		if(((*i)->getXPos()==1 && EnemyShip::velocity<0) ||( (*i)->getXPos()==27 && EnemyShip::velocity>0))
  			EnemyShip::shiftDown = true;
  	}

  	if(EnemyShip::shiftDown)
  	{
  		for (std::list<EnemyShip*>::iterator i = this->hoardObjects.begin(); i != this->hoardObjects.end(); ++i)
  		{
  				(*i)->setYPos((*i)->getYPos()+1);
  		}
  		EnemyShip::velocity*=-1;
  		EnemyShip::shiftDown = false;
  	}
  	else
  	{
  		for (std::list<EnemyShip*>::iterator i = this->hoardObjects.begin(); i != this->hoardObjects.end(); ++i)
  		{
  				(*i)->update(ch);
  		}
  	}
  }

  if(this->player->fire() && ch == ' ')
  {
    PlayerMissle* temp = new PlayerMissle(this->player->getXPos(), this->player->getYPos()-1);
    temp->isAlive = true;
    this->bullets.push_back(temp);
    this->gameObjects.push_back(temp);
  }

  for(std::list<EnemyShip*>::iterator i = this->hoardObjects.begin(); i != this->hoardObjects.end(); ++i)
  {
    if((*i)->fire())
    {
      if((*i)->getASCII()=='W')
      {
        EnemyMissle* temp = new EnemyMissle((*i)->getXPos(), (*i)->getYPos()+1, '!');
        temp->isAlive = true;
        this->bullets.push_back(temp);
        this->gameObjects.push_back(temp);
      }
      else
      {
        EnemyMissle* temp = new EnemyMissle((*i)->getXPos(), (*i)->getYPos()+1, '*');
        temp->isAlive = true;
        this->bullets.push_back(temp);
        this->gameObjects.push_back(temp);
      }
    }
  }

  for (std::list<Projectile*>::iterator i = this->bullets.begin(); i != this->bullets.end(); ++i)
  {
      for (std::list<EnemyShip*>::iterator j = this->hoardObjects.begin(); j != this->hoardObjects.end(); ++j)
      {
        if((*i)->getASCII() == '|')
        {
          if((*i)->getXPos() == (*j)->getXPos() && (*i)->getYPos() == (*j)->getYPos())
          {
            (*j)->isAlive = false;
            (*i)->isAlive = false;
            this->score += 1;
            PlayerMissle::instances--;
          }
        }
        else
        {
          if((*i)->getXPos() == (*j)->getXPos() && (*i)->getYPos() == (*j)->getYPos())
          {
            (*i)->isAlive = false;
          }
        }
      }
    if((*i)->getASCII() != '|')
    {
      if((*i)->getXPos() == this->player->getXPos() && (*i)->getYPos() == this->player->getYPos())
      {
        this->player->isAlive = false;
        (*i)->isAlive = false;
        this->lose = true;
      }
    }

    if((*i)->getYPos() < 0 || (*i)->getYPos() > this->gameRunner->maxHeight-1)
    {
      if((*i)->getASCII()=='|')
        PlayerMissle::instances--;
      (*i)->isAlive = false;
    }
  }


	std::list<EnemyShip*> enemyTemp;
	std::list<Projectile*> bulletTemp;
	std::list<GameObject*> temp;

  for (std::list<GameObject*>::iterator i = this->gameObjects.begin(); i != this->gameObjects.end(); ++i)
  {
    if((*i)->isAlive == false)
    {
      this->deadObjects.push_back(*i);
    }
    else
    {
      temp.push_back(*i);
    }
  }
  this->gameObjects = temp;
	for (std::list<GameObject*>::iterator i = this->gameObjects.begin(); i != this->gameObjects.end(); ++i)
	{
			if((*i)->getASCII() == 'W'|| (*i)->getASCII() == 'u')
			{
				enemyTemp.push_back((EnemyShip*)*i);
	    }
	}
  this->hoardObjects = enemyTemp;

  for (std::list<GameObject*>::iterator i = this->gameObjects.begin(); i != this->gameObjects.end(); ++i)
  {
      if((*i)->getASCII() == '*'|| (*i)->getASCII() == '!'||(*i)->getASCII() == '|')
      {
        bulletTemp.push_back((Projectile*)*i);
      }
  }

  if(!this->lose)
  {
    if(this->player->isAlive == false)
    {
        this->lose = true;
    }
  }
  this->bullets = bulletTemp;
  this->gameObjects = temp;

  if(playerHeight == enemyHeight)
  {
    this->lose = true;
    this->done = true;
  }
  else 
  {
    if(this->score == 1)
    {
    this->win = true;
    this->done = true;
    }
  }
}

bool GameLevel::isLevelComplete() 
{
  return this->win || this->lose;
}

void createPlayer(GameLevel* gr)
{
    gr->player = new PlayerShip(15, 27);
    gr->gameObjects.push_back(gr->player);
}

void createEnemy(GameLevel* gr) 
{
    for (size_t i = 0; i < 1; i++)
    {
      if(i%2==0)
      {
        EnemyCruiser* temp = new EnemyCruiser(9+i, 3);
        gr->gameObjects.push_back(temp);
        gr->hoardObjects.push_back(temp);
      }
      else
      {
        EnemyDestroyer* temp = new EnemyDestroyer(9+i, 3);
        gr->gameObjects.push_back(temp);
        gr->hoardObjects.push_back(temp);
      }
    }

    for (size_t i = 0; i < 0; i++)
    {
      if(i%2==0)
      {
        EnemyDestroyer* temp = new EnemyDestroyer(9+i, 2);
        gr->gameObjects.push_back(temp);
        gr->hoardObjects.push_back(temp);
      }
      else
      {
        EnemyCruiser* temp = new EnemyCruiser(9+i, 2);
        gr->gameObjects.push_back(temp);
        gr->hoardObjects.push_back(temp);

      }
    }
}

void GameLevel::init()
{
  
  this->score  = 0;
  this->start = true;
  this->lose = false;
  this->win = false;
  createPlayer(this);
  createEnemy(this);
}

void GameLevel::cleanup()
{

  for(std::list<GameObject*>::iterator i = this->gameObjects.begin(); i != this->gameObjects.end(); ++i)
  {
      delete *i;
  }

  for(std::list<GameObject*>::iterator i = this->deadObjects.begin(); i != this->deadObjects.end(); ++i){
    delete *i;
  }

}
