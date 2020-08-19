#include "GameRunner.h"

GameRunner::GameRunner()
{
  init();
}

GameRunner::~GameRunner()
{
  cleanup();
  endwin();
}

// all objects that are create and destroyed will be pointers in these lists
// I use other lists for a more efficient update algortitm but all allocated
// addresses are restored
void GameRunner::cleanup()
{

  for(std::list<GameObject*>::iterator i = this->gameObjects.begin(); i != this->gameObjects.end(); ++i)
  {
      delete *i;
  }

  for(std::list<GameObject*>::iterator i = this->deadObjects.begin(); i != this->deadObjects.end(); ++i)
  {
    delete *i;
  }
}

void GameRunner::init()
{
    srand (time(NULL)); /// seed to some random number based on time
    if ( initscr() == NULL ) { /// init the screen, defaults to stdscr
        endwin();
        fprintf(stderr, "Error initialising ncurses.\n");
        exit(EXIT_FAILURE);
    }

    if(has_colors() == FALSE)
    {	
      endwin();
      printf("Your terminal does not support color\n");
      exit(EXIT_FAILURE);
    }

    start_color();			/* Start color 			*/
    init_pair(1, COLOR_RED, COLOR_BLACK);

    attron(COLOR_PAIR(1));

    this->maxWidth =  30;
    this->maxHeight = 29;

    this->ticksPassed = 0;
    this->score  = 0;
    this->quit = 0;
    this->win = 0;

    this->player = new PlayerShip(15, 27);
    this->gameObjects.push_back(player);
    // for (size_t i = 0; i < 11; i++)
    // {
    //   if(i%2==0)
    //   {
    //     EnemyCruiser* temp = new EnemyCruiser(9+i, 3);
    //     this->gameObjects.push_back(temp);
    //     this->hoardObjects.push_back(temp);
    //   }
    //   else
    //   {
    //     EnemyDestroyer* temp = new EnemyDestroyer(9+i, 3);
    //     this->gameObjects.push_back(temp);
    //     this->hoardObjects.push_back(temp);
    //   }
    // }

    // for (size_t i = 0; i < 11; i++)
    // {
    //   if(i%2==0)
    //   {
    //     EnemyDestroyer* temp = new EnemyDestroyer(9+i, 2);
    //     this->gameObjects.push_back(temp);
    //     this->hoardObjects.push_back(temp);
    //   }
    //   else
    //   {
    //     EnemyCruiser* temp = new EnemyCruiser(9+i, 2);
    //     this->gameObjects.push_back(temp);
    //     this->hoardObjects.push_back(temp);

    //   }
    // }
}

void GameRunner::update(int ch)
{
  int playerHeight = 0;
	int enemyHeight = 0;

  //update bullets first
	for (std::list<Projectile*>::iterator i = this->bullets.begin(); i != this->bullets.end(); ++i)
	{  if((*i)->getASCII() == '|')
		    (*i)->update(ch);
    else
    {
      if(this->ticksPassed%2==0)
      {
        (*i)->update(ch);
      }
    }
	}

	//update player
	this->player->update(ch);
	playerHeight =this->player->getYPos();
	//update hoardObjects

  if(this->ticksPassed%20==0)
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

    if((*i)->getYPos() < 0 || (*i)->getYPos() > this->maxHeight-1)
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



  if(!lose)
  {
    if(this->player->isAlive == false)
    {
        this->quit = true;
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
    if(this->score == 22)
    {
    this->win = true;
    this->done = true;
    }
  }
}

void GameRunner::run()
{
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, false);
  curs_set(0);

  const int delay = 100;
  timeout(delay);

  int ch = 0;
  this->quit = false;

  //set up game stages
  Scenes scenes;



  // GameState* gameState = new GameState();
  int elapsedTime;


  while(!this->quit && !this->win && !this->lose)
  {
    ch = getch();
    erase(); /// erase the screen (after getch())
    if ( ch != ERR) { /// user has a keypress
        /// this is to delay until the next tick
        elapsedTime = getElapsedTime();
        if (elapsedTime < delay){
            nsleep(delay-elapsedTime);}
    }
    this->ticksPassed+=1;
    if(ch == 'q')
    {
        this->quit = true;
    }
    else
    {
        update(ch);
        mvprintw(1,0,scenes.border.c_str());
        mvprintw(0, 0, "Points: %i.   'q' to quit.\n", this->score);

        draw();
    }

    refresh(); // refresh the screen after adding everything
    move(0,0); /// move cursor to 0,0 (looks prettier if os doesn't allow invisible cursors)
  }
}

void GameRunner::draw()
{
  if(!this->lose)
  {
    mvaddch(1+this->player->getYPos(), this->player->getXPos(), this->player->getASCII());
  }
  for (std::list<GameObject*>::iterator i = this->gameObjects.begin(); i != this->gameObjects.end(); ++i)
  {
    mvaddch(1+(*i)->getYPos(), (*i)->getXPos(), (*i)->getASCII());
  }
}
