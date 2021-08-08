#include "GameLostLevel.hpp"
#include "GameRunner.hpp"
#include "Level.hpp"
#include <string>

GameLostLevel::GameLostLevel(GameRunner *gr) : Level(gr) {
  this->start = false;
  this->quit = false;
  this->score = score;
}

GameLostLevel::~GameLostLevel() {}

void GameLostLevel::draw() {

  mvprintw(1, 0, this->gameRunner->scenes.lose.c_str(), this->gameRunner->score);
}

void GameLostLevel::update(int ch) {
  if (ch == 'p') {
    this->start = true;
  }

  if (ch == 'q') {
    this->gameRunner->kill();
  }
}

bool GameLostLevel::isLevelComplete() { return this->start; }

void GameLostLevel::init() { this->start = false; }

void GameLostLevel::cleanup() { this->start = false; }