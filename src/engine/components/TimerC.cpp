#include "TimerC.hpp"

TimerC &TimerC::setTimeout(Uint32 timeout) {
  this->timeout = timeout;
  return *this;
}
TimerC &TimerC::start() {
  running = true;
  tickedTime = 0;
  return *this;
}

void TimerC::tick(Uint32 delta) {
  if (running)
    tickedTime += delta;
}
bool TimerC::isDone() {
  if (tickedTime < timeout || !running)
    return false;

  running = false;
  return true;
}