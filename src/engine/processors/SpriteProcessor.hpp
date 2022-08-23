#ifndef BOMBERMAN_SPRITEPROCESSOR_H
#define BOMBERMAN_SPRITEPROCESSOR_H

#include "../../vendor/entt.hpp"
#include "../Renderer.hpp"

/**
 * Sprite processor\n
 * Process sprite components
 */
class SpriteProcessor {
public:
  /**
   * Render sprites
   * @param registry Registry
   * @param renderer Renderer to which render sprites
   * @param delta Time between frames
   */
  static void process(entt::registry &registry, const Renderer &renderer,
                      Uint32 delta);
};

#endif // BOMBERMAN_SPRITEPROCESSOR_H
