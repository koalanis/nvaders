#ifndef _GameObject_H
#define _GameObject_H

class GameObject
{

public:
	GameObject(int x, int y, char spr);

	virtual ~GameObject();

	virtual void update(int cmd) = 0;

	char getASCII();

	void setXPos(const int x);

	void setYPos(const int y);

	int getXPos();

	int getYPos();

public:
	int _x;
	int _y;
	char _sprite;
	bool isAlive;
};


#endif
