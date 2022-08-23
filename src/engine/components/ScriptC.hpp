#ifndef BOMBERMAN_SCRIPTC_H
#define BOMBERMAN_SCRIPTC_H

#include "../../vendor/entt.hpp"
#include <SDL2/SDL.h>

#include "../Entity.hpp"

#include "../processors/ScriptProcessor.hpp"

// Because c++ deps
class Entity;

/**
 * Script\n
 * Provides api for custom scripts
 */
class Script {
  friend ScriptProcessor;

protected:
  /**
   * Up to date registry
   */
  entt::registry *registry;
  /**
   * Entity on which this script is used
   * Not pointer to be able to use dot (it looks nice)
   */
  std::shared_ptr<Entity> entity;

  Entity createEntity();

public:
  Script();

  /**
   * Called after registry and entity are set
   */
  virtual void onConstruct();
  /**
   * Called before every render
   */
  virtual void onUpdate();
  /**
   * Called on every SDL event
   * @param event SDL event
   */
  virtual void onEvent(const SDL_Event &event);
  /**
   * Called when timer is done
   */
  virtual void onTimer();
  /**
   * Called when collision occurs with associated entity
   * @param myColliderName Name of collider that is on this entity
   * @param name Name of the other collider that this entity collided
   * @param collidedWith Entity that this entity collided with
   */
  virtual void onCollision(const std::string &myColliderName,
                           const std::string &collidedWithName,
                           Entity collidedWith);
};

/**
 * Script component\n
 * Used for adding custom logic to entity
 */
class ScriptC {
private:
  std::shared_ptr<Script> script;

public:
  /**
   * @param script Script to use
   */
  ScriptC(const std::shared_ptr<Script> script);
  /**
   * @return Used script
   */
  std::shared_ptr<Script> getScript() const;
};

#endif // BOMBERMAN_SCRIPTC_H