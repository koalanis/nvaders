#include "GameWonLevel.hpp"
#include "GameRunner.hpp"
#include "Level.hpp"

GameWonLevel::GameWonLevel(GameRunner *gr) : Level(gr) {
  this->start = false;
  this->quit = false;
  this->score = score;
}

GameWonLevel::~GameWonLevel() {}

void GameWonLevel::draw() {
  mvprintw(1, 0, this->gameRunner->scenes.win.c_str());
}

void GameWonLevel::update(int ch) {
  if (ch == 'p') {
    this->start = true;
  }

  if (ch == 'q') {
    this->gameRunner->kill();
  }
}

bool GameWonLevel::isLevelComplete() { return this->start; }

void GameWonLevel::init() { this->start = false; }

void GameWonLevel::cleanup() { this->start = false; }