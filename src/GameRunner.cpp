#include "GameRunner.hpp"
#include "GameLevel.hpp"
#include "MenuLevel.hpp"

#include "GameLostLevel.hpp"
#include "GameWonLevel.hpp"

int GAME_MODE = 1;
int END_MODE = 2;

void goToEndState(GameRunner *gr, bool lost, int score);
void goToWinState(GameRunner *gr, int score);
void goToLoseState(GameRunner *gr, int score);
void goToPlayState(GameRunner *gr);
void setupColors();
void goToNextLevel(GameRunner* gr);


bool inPlayMode(GameRunner* gr);

void cleanup(GameRunner *gr) {

  for (std::vector<Level *>::iterator i = gr->levels.begin();
       i != gr->levels.end(); ++i) {
    delete *i;
  }

  for (std::vector<Level *>::iterator i = gr->endgame.begin();
       i != gr->endgame.end(); ++i) {
    delete *i;
  }
}

void createLevels(GameRunner *gr) {
  gr->levels.push_back(new MenuLevel(gr));
  gr->levels.push_back(new GameLevel(gr));
  gr->levels.push_back(new GameLevel(gr,2));
  gr->levels.push_back(new GameLevel(gr,3));
  gr->levels.push_back(new GameLevel(gr,4));
  gr->levels.push_back(new GameLevel(gr,5));
  gr->levels.push_back(new GameWonLevel(gr));
  gr->levels.push_back(new GameLostLevel(gr));

  gr->gameWonLevelIndex = gr->levels.size()-2; 
  gr->gameLostLevelIndex = gr->levels.size()-1;
}

GameRunner::GameRunner() {}

GameRunner::~GameRunner() {}

void GameRunner::setColor(int c) { attron(COLOR_PAIR(c)); }

void GameRunner::start() {

  this->score = 0;
  srand(time(NULL));       /// seed to some random number based on time
  if (initscr() == NULL) { /// init the screen, defaults to stdscr
    endwin();
    fprintf(stderr, "Error initialising ncurses.\n");
    exit(EXIT_FAILURE);
  }

  if (has_colors() == FALSE) {
    endwin();
    printf("Your terminal does not support color\n");
    exit(EXIT_FAILURE);
  }

  start_color(); /* Start color 			*/

  setupColors();

  this->maxWidth = this->scenes.maxSizeCols;
  this->maxHeight = this->scenes.maxSizeCols;
  this->ticksPassed = 0;
  this->quit = false;

  createLevels(this);

  this->currentLevel = this->levels.begin();
  this->lastLevel = this->levels.end();

  Level *menu = *(this->currentLevel);
  if (menu)
    menu->init();

  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, false);
  curs_set(0);

  const int delay = 100;
  timeout(delay);

  int ch = 0;

  int elapsedTime;

  int currentMode = GAME_MODE;

  while (!this->quit) {
    // reset background color

    attron(COLOR_PAIR(1));
    ch = getch();
    /// erase the screen (after getch())
    erase();

    /// user has a keypress
    if (ch != ERR) {
      /// this is to delay until the next tick
      elapsedTime = getElapsedTime();
      if (elapsedTime < delay) {
        nsleep(delay - elapsedTime);
      }
    }
    this->ticksPassed += 1;
    if (ch == 'z') {
      this->quit = true;
      continue;
    } 

    if( this->currentLevelIndex == gameWonLevelIndex ||
      this->currentLevelIndex == gameLostLevelIndex) {
        Level *level = this->levels[this->currentLevelIndex];
        if (level->isLevelComplete()) {
          level->cleanup();
          nsleep(100);
          goToPlayState(this);
        } else {
          level->update(ch);
          level->draw();
        }
    } else if (this->currentLevelIndex == this->menuLevelIndex) {
        Level *level = this->levels[this->currentLevelIndex];
        if (level->isLevelComplete()) {
          level->cleanup();
          nsleep(100);
          goToNextLevel(this);
        } else {
          level->update(ch);
          level->draw(); 
        }
    } else {
      Level *level = this->levels[this->currentLevelIndex];
      if (level->isLevelComplete()) {
        nsleep(100);
        auto lose = level->lose;
        level->cleanup();
        if (lose) {
          goToLoseState(this, this->score);
        } else {
          goToNextLevel(this);
        }
      } else {
        level->update(ch);
        level->draw();
      }
    }
    

    // refresh the screen after adding everything
    /// move cursor to 0,0
    /// looks prettier if os doesn't allow
    /// invisible cursors
    refresh();
    move(0, 0);
  }

  endwin();
  cleanup(this);
}

void goToLoseState(GameRunner *gr, int score) {
  gr->currentLevelIndex = gr->gameLostLevelIndex;
  Level *level = (gr->levels[gr->currentLevelIndex]);
  level->init();
  level->score = score;
}

void goToWinState(GameRunner *gr, int score) {
  gr->currentLevel = gr->endgame.begin();
  Level *level = (*gr->currentLevel);
  level->init();
  level->score = score;
}

void goToPlayState(GameRunner *gr) {
  gr->currentLevelIndex = 0;
  Level *level = (gr->levels[gr->currentLevelIndex]);
  level->init();
  gr->score = 0;
  // TODO(koalanis): add save high score here
}


void setupColors() {

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

  init_pair(6, COLOR_RED, COLOR_BLACK);
  // attron(COLOR_PAIR(6));

  init_pair(7, COLOR_GREEN, COLOR_BLACK);
  // attron(COLOR_PAIR(6));
}


void goToNextLevel(GameRunner* gr) {
  gr->currentLevelIndex++;
  Level *nextLevel = gr->levels[gr->currentLevelIndex];
  nextLevel->init();
}


void GameRunner::kill() { this->quit = true; }
