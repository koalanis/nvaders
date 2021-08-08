#include "GameObject.hpp"

GameObject::GameObject(int x, int y, char spr, int color = 1) {
  this->_x = x;
  this->_y = y;
  this->_sprite = spr;
  this->isAlive = true;
  this->_color = color;
}

GameObject::GameObject(int x, int y, char spr) {
  this->_x = x;
  this->_y = y;
  this->_sprite = spr;
  this->isAlive = true;
  this->_color = 1;
}

GameObject::~GameObject() {}

char GameObject::getASCII() { return this->_sprite; }

int GameObject::getColor() { return this->_color; }

void GameObject::setXPos(const int x) { this->_x = x; }

void GameObject::setYPos(const int y) { this->_y = y; }

int GameObject::getXPos() { return this->_x; }

int GameObject::getYPos() { return this->_y; }
