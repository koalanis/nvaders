#ifndef _LEVEL_H_
#define _LEVEL_H_

struct GameRunner;
class Level {
public:
  GameRunner *gameRunner;

  int score;
  bool lose = false;

  Level(GameRunner *gameRunner);
  virtual ~Level();

  virtual bool isLevelComplete() = 0;
  virtual void update(int) = 0;
  virtual void draw() = 0;
  virtual void init() = 0;
  virtual void cleanup() = 0;
};

#endif
