#ifndef BOMBERMAN_COLLISIONPROCESSOR_H
#define BOMBERMAN_COLLISIONPROCESSOR_H

#include "../../vendor/entt.hpp"
#include <SDL2/SDL.h>

#include "../components/ColliderManagerC.hpp"
#include "../components/TransformC.hpp"

class CollisionProcessor {
private:
  enum Direction { UP, DOWN, LEFT, RIGHT };

  /**
   * Check collision between two colliders
   * And move light entity if necessary
   * @return do they collide
   */
  static bool handleCollision(const Collider &heavyCollider,
                              TransformC &heavyTransformC,
                              const Collider &lightCollider,
                              TransformC &lightTransformC);

  /**
   * Calculate collider size and position relative to scene
   */
  static SDL_Rect calculateBoundary(const Collider &collider,
                                    const TransformC &transformC);

  /**
   * @param direction Direction where to teleport object
   * @param lightBoundary Boundary of object that will be teleported
   * @param heavyBoundary Boundary of object that will stay on the same position
   */
  static void moveEntityOutsideBoundary(const Direction direction,
                                        TransformC &lightTransformCparagraph,
                                        const SDL_Rect &lightBoundary,
                                        const SDL_Rect &heavyBoundary);

public:
  /**
   * Process collision based on elements positions
   * To function correctly it needs enough FPS
   *
   * \warning If two collider managers have same mass, event could be emitted
   * multiple times
   * @param registry
   */
  static void process(entt::registry &registry);
};

#endif // BOMBERMAN_COLLISIONPROCESSOR_H
