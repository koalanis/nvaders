#include "GameRunner.h"
#include "MenuLevel.h"
#include "GameLevel.h"

void cleanup(GameRunner* gr)
{

  // all objects that are create and destroyed will be pointers in these lists
  // I use other lists for a more efficient update algortitm but all allocated
  // addresses are restored

  for(std::list<GameObject*>::iterator i = gr->gameObjects.begin(); i != gr->gameObjects.end(); ++i)
  {
      delete *i;
  }

  for(std::list<GameObject*>::iterator i = gr->deadObjects.begin(); i != gr->deadObjects.end(); ++i){
    delete *i;
  }

  for(std::list<Level*>::iterator i = gr->levels.begin(); i != gr->levels.end(); ++i){
    delete *i;
  }
}

void createLevels(GameRunner* gr)
{
    gr->levels.push_back(new MenuLevel(gr));
    gr->levels.push_back(new GameLevel(gr));
    
}

bool shouldLoopRun(GameRunner* gr)
{
  return !gr->quit && !gr->win && !gr->lose;
}

GameRunner::GameRunner()
{
}

GameRunner::~GameRunner()
{
 
}

void GameRunner::start()
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
  this->quit = false;
  this->lose = false;
  this->win = false;

  createLevels(this);

  this->currentLevel = this->levels.begin();
  this->lastLevel = this->levels.end();


  Level* menu = *(this->currentLevel);
  if(menu)
    menu->init();

  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, false);
  curs_set(0);

  const int delay = 100;
  timeout(delay);

  int ch = 0;
  this->quit = false;

  

  int elapsedTime;

  while(!this->quit)
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
    if(ch == 'z' || this->currentLevel == this->lastLevel)
    {
        this->quit = true;
    }
    else
    {

      Level* level = *(this->currentLevel);
      if(level->isLevelComplete())
      {
        this->currentLevel++;
        Level* nextLevel = *(this->currentLevel);
        nextLevel->init();
      }
      else {
        level->update(ch);
        level->draw();
      }
    }

    refresh(); // refresh the screen after adding everything
    move(0,0); /// move cursor to 0,0 (looks prettier if os doesn't allow invisible cursors)
  }

  cleanup(this);
  endwin();

}

void GameRunner::kill()
{
  this->quit = true;
}
