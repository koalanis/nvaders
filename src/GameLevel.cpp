#include "GameLevel.h"
#include "Level.h"
#include "GameRunner.h"
#include "PlayerShip.h"


GameLevel::GameLevel(GameRunner* gr) : Level(gr) 
{
  this->start = false;
  this->quit= false;

}

GameLevel::~GameLevel() {}

void GameLevel::draw() 
{
  mvprintw(1,0,  this->gameRunner->scenes.border.c_str());
  mvprintw(0, 0, "Points: %i.   'q' to quit.\n", this->gameRunner->score);
  if(!this->gameRunner->lose)
  {
    mvaddch(1+this->gameRunner->player->getYPos(), this->gameRunner->player->getXPos(), this->gameRunner->player->getASCII());
  }
  for (std::list<GameObject*>::iterator i = this->gameRunner->gameObjects.begin(); i != this->gameRunner->gameObjects.end(); ++i)
  {
    mvaddch(1+(*i)->getYPos(), (*i)->getXPos(), (*i)->getASCII());
  }

}

void GameLevel::update(int ch)
{
  int playerHeight = 0;
	int enemyHeight = 0;

  //update bullets first
	for (std::list<Projectile*>::iterator i = this->gameRunner->bullets.begin(); i != this->gameRunner->bullets.end(); ++i)
	{  if((*i)->getASCII() == '|')
		    (*i)->update(ch);
    else
    {
      if(this->gameRunner->ticksPassed%2==0)
      {
        (*i)->update(ch);
      }
    }
	}

	//update player
	this->gameRunner->player->update(ch);
	playerHeight =this->gameRunner->player->getYPos();
	//update hoardObjects

  if(this->gameRunner->ticksPassed%20==0)
  {
    for (std::list<EnemyShip*>::iterator i = this->gameRunner->hoardObjects.begin(); i != this->gameRunner->hoardObjects.end(); ++i)
  	{
  		if((*i)->getYPos()>enemyHeight)
  			enemyHeight = (*i)->getYPos();
  		if(((*i)->getXPos()==1 && EnemyShip::velocity<0) ||( (*i)->getXPos()==27 && EnemyShip::velocity>0))
  			EnemyShip::shiftDown = true;
  	}

  	if(EnemyShip::shiftDown)
  	{
  		for (std::list<EnemyShip*>::iterator i = this->gameRunner->hoardObjects.begin(); i != this->gameRunner->hoardObjects.end(); ++i)
  		{
  				(*i)->setYPos((*i)->getYPos()+1);
  		}
  		EnemyShip::velocity*=-1;
  		EnemyShip::shiftDown = false;
  	}
  	else
  	{
  		for (std::list<EnemyShip*>::iterator i = this->gameRunner->hoardObjects.begin(); i != this->gameRunner->hoardObjects.end(); ++i)
  		{
  				(*i)->update(ch);
  		}
  	}
  }

  if(this->gameRunner->player->fire() && ch == ' ')
  {
    PlayerMissle* temp = new PlayerMissle(this->gameRunner->player->getXPos(), this->gameRunner->player->getYPos()-1);
    temp->isAlive = true;
    this->gameRunner->bullets.push_back(temp);
    this->gameRunner->gameObjects.push_back(temp);
  }

  for(std::list<EnemyShip*>::iterator i = this->gameRunner->hoardObjects.begin(); i != this->gameRunner->hoardObjects.end(); ++i)
  {
    if((*i)->fire())
    {
      if((*i)->getASCII()=='W')
      {
        EnemyMissle* temp = new EnemyMissle((*i)->getXPos(), (*i)->getYPos()+1, '!');
        temp->isAlive = true;
        this->gameRunner->bullets.push_back(temp);
        this->gameRunner->gameObjects.push_back(temp);
      }
      else
      {
        EnemyMissle* temp = new EnemyMissle((*i)->getXPos(), (*i)->getYPos()+1, '*');
        temp->isAlive = true;
        this->gameRunner->bullets.push_back(temp);
        this->gameRunner->gameObjects.push_back(temp);
      }
    }
  }

  for (std::list<Projectile*>::iterator i = this->gameRunner->bullets.begin(); i != this->gameRunner->bullets.end(); ++i)
  {
      for (std::list<EnemyShip*>::iterator j = this->gameRunner->hoardObjects.begin(); j != this->gameRunner->hoardObjects.end(); ++j)
      {
        if((*i)->getASCII() == '|')
        {
          if((*i)->getXPos() == (*j)->getXPos() && (*i)->getYPos() == (*j)->getYPos())
          {
            (*j)->isAlive = false;
            (*i)->isAlive = false;
            this->gameRunner->score += 1;
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
      if((*i)->getXPos() == this->gameRunner->player->getXPos() && (*i)->getYPos() == this->gameRunner->player->getYPos())
      {
        this->gameRunner->player->isAlive = false;
        (*i)->isAlive = false;
        this->gameRunner->lose = true;
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

  for (std::list<GameObject*>::iterator i = this->gameRunner->gameObjects.begin(); i != this->gameRunner->gameObjects.end(); ++i)
  {
    if((*i)->isAlive == false)
    {
      this->gameRunner->deadObjects.push_back(*i);
    }
    else
    {
      temp.push_back(*i);
    }
  }
  this->gameRunner->gameObjects = temp;
	for (std::list<GameObject*>::iterator i = this->gameRunner->gameObjects.begin(); i != this->gameRunner->gameObjects.end(); ++i)
	{
			if((*i)->getASCII() == 'W'|| (*i)->getASCII() == 'u')
			{
				enemyTemp.push_back((EnemyShip*)*i);
	    }
	}
  this->gameRunner->hoardObjects = enemyTemp;

  for (std::list<GameObject*>::iterator i = this->gameRunner->gameObjects.begin(); i != this->gameRunner->gameObjects.end(); ++i)
  {
      if((*i)->getASCII() == '*'|| (*i)->getASCII() == '!'||(*i)->getASCII() == '|')
      {
        bulletTemp.push_back((Projectile*)*i);
      }
  }

  if(!this->gameRunner->lose)
  {
    if(this->gameRunner->player->isAlive == false)
    {
        this->gameRunner->quit = true;
        this->gameRunner->lose = true;
    }
  }
  this->gameRunner->bullets = bulletTemp;
  this->gameRunner->gameObjects = temp;

  if(playerHeight == enemyHeight)
  {
    this->gameRunner->lose = true;
    this->gameRunner->done = true;
  }
  else 
  {
    if(this->gameRunner->score == 22)
    {
    this->gameRunner->win = true;
    this->gameRunner->done = true;
    }
  }
}

bool GameLevel::isLevelComplete() 
{
  return this->gameRunner->win || this->gameRunner->lose;
}

void createPlayer(GameRunner* gr)
{
    gr->player = new PlayerShip(15, 27);
    gr->gameObjects.push_back(gr->player);
}

void createEnemy(GameRunner* gr) 
{
    for (size_t i = 0; i < 11; i++)
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

    for (size_t i = 0; i < 11; i++)
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
    createPlayer(this->gameRunner);

}