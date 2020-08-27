#include "GameRunner.h"
#include "MenuLevel.h"
#include "GameLevel.h"

void cleanup(GameRunner* gr)
{

  for(std::list<Level*>::iterator i = gr->levels.begin(); i != gr->levels.end(); ++i){
    delete *i;
  }
}

void createLevels(GameRunner* gr)
{
    gr->levels.push_back(new MenuLevel(gr));
    gr->levels.push_back(new GameLevel(gr));
    
}

GameRunner::GameRunner()
{
}

GameRunner::~GameRunner()
{
 
}


void GameRunner::setColor(int c)
{
  attron(COLOR_PAIR(c));
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

  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  attron(COLOR_PAIR(1));
  
  init_pair(2, COLOR_CYAN, COLOR_BLACK);
  // attron(COLOR_PAIR(2));

  init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
  // attron(COLOR_PAIR(3));

  init_pair(4, COLOR_BLUE, COLOR_BLACK);
  // attron(COLOR_PAIR(4));

  init_pair(5, COLOR_YELLOW, COLOR_BLACK);
  // attron(COLOR_PAIR(5));

  init_pair(6, COLOR_GREEN, COLOR_BLACK);
  // attron(COLOR_PAIR(6));

  init_pair(6, COLOR_RED, COLOR_BLACK);
  // attron(COLOR_PAIR(6));


  this->maxWidth =  30;
  this->maxHeight = 29;
  this->ticksPassed = 0;
  this->quit = false;
  
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
        level->cleanup();
        nsleep(100);
        this->currentLevel++;
        if(this->currentLevel == this->lastLevel) 
        {
          this->currentLevel = this->levels.begin();
          (*(this->currentLevel))->init();
        } 
        else 
        {
          Level* nextLevel = *(this->currentLevel);
          nextLevel->init();
        }
      }
      else {
        level->update(ch);
        level->draw();
      }
    }

    refresh(); // refresh the screen after adding everything
    move(0,0); /// move cursor to 0,0 (looks prettier if os doesn't allow invisible cursors)
  }

  endwin();
  cleanup(this);
}

void GameRunner::kill()
{
  this->quit = true;
}
