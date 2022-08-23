#ifndef BOMBERMAN_TIMERC_H
#define BOMBERMAN_TIMERC_H

#include <SDL2/SDL.h>

class TimerC {
private:
  Uint32 timeout;
  Uint32 tickedTime = 0;
  bool running;

public:
  TimerC &setTimeout(Uint32 timeout);
  TimerC &start();

  void tick(Uint32 delta);
  bool isDone();
};

#endif // BOMBERMAN_TIMERC_H
