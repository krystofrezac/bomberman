#ifndef BOMBERMAN_TIMERPROCESSOR_H
#define BOMBERMAN_TIMERPROCESSOR_H

#include "../../vendor/entt.hpp"
#include <SDL2/SDL.h>

class TimerProcessor {
public:
  static void process(entt::registry &registry, Uint32 delta);
};

#endif // BOMBERMAN_TIMERPROCESSOR_H
