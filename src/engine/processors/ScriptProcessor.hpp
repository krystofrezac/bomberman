#ifndef BOMBERMAN_SCRIPTPROCESSOR_H
#define BOMBERMAN_SCRIPTPROCESSOR_H

#include "../../vendor/entt.hpp"
#include <SDL2/SDL.h>

/**
 * Script processor\n
 * Process script components
 */
class ScriptProcessor {
private:
  static void onScriptComponentConstruct(entt::registry &registry,
                                         entt::entity entity);

public:
  /**
   * Initialize observing script component construction
   * @param registry Registry
   */
  static void observeScriptComponentConstruct(entt::registry &registry);
  /**
   * Call script component's onUpdate
   * @param registry Registry
   */
  static void update(entt::registry &registry);
  /**
   * Call script component's onEvent
   * @param registry Registry
   * @param event SDL event
   */
  static void propagateEvent(entt::registry &registry, const SDL_Event &event);
};

#endif // BOMBERMAN_SCRIPTPROCESSOR_H
