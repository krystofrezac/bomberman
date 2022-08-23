#ifndef BOMBERMAN_TRANSFORMPROCESSOR_H
#define BOMBERMAN_TRANSFORMPROCESSOR_H

#include "../../vendor/entt.hpp"
#include <SDL2/SDL.h>

class TransformProcessor {
public:
  static void process(entt::registry &registry, Uint32 delta);
};

#endif // BOMBERMAN_TRANSFORMPROCESSOR_H
