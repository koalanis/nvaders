#include "MenuLevel.h"
#include "Level.h"
#include "GameRunner.h"


MenuLevel::MenuLevel(GameRunner* gr) : Level(gr) 
{
  this->start = false;
  this->quit= false;

}


MenuLevel::~MenuLevel() {}


void MenuLevel::draw() 
{
  mvprintw(1,0,  this->gameRunner->scenes.menu.c_str());
}

void MenuLevel::update(int ch) {
  if(ch == 'p') {
    this->start = true;
  }

  if(ch == 'q') {
    this->gameRunner->kill();
  }
}

bool MenuLevel::isLevelComplete() 
{
  return this->start;
}


void MenuLevel::init()
{
  this->start = false;
}

void MenuLevel::cleanup()
{
  this->start = false;
}