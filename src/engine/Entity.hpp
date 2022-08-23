#ifndef BOMBERMAN_ENTITY_H
#define BOMBERMAN_ENTITY_H

#include "components/AnimationPlayerC.hpp"
#include "components/ColliderManagerC.hpp"
#include "components/ScriptC.hpp"
#include "components/TimerC.hpp"

#include "Texture.hpp"
#include "components/TransformC.hpp"

// Because c++ deps
class Script;

/**
 * Helper class for creating entities and assigning them components
 */
class Entity {
private:
  entt::registry *registry;
  entt::entity entity;

public:
  /**
   * Create unusable entity
   */
  Entity();
  /**
   * Create new entity
   * @param registry Registry where entity will be created
   */
  Entity(entt::registry *registry);
  /**
   * Fill entity with existing entt data
   * @param registry Registry where entity will be created
   * @param entity Entt entity to use
   */
  Entity(entt::registry *registry, entt::entity entity);
  /**
   * Return true if both entities have same entt entity number
   * @param entity
   * @return
   */
  bool operator==(const Entity &entity);

  /**
   * Destroy
   */
  void destroy();

  /**
   * @return Underlying entt entity
   */
  entt::entity getRawEntity() const;

  /**
   * Add script component
   * For details look at ScriptC
   * @param script
   * @return Entity reference
   */
  Entity &addScript(const std::shared_ptr<Script> script);

  /**
   * Add sprite component
   * For details look at TextureC
   * @param texture
   * @return Entity reference
   */
  Entity &addSprite(const Texture &texture);
  /**
   * Add sprite component
   * For details look at TextureC
   * @param texture
   * @param crop
   * @return Entity reference
   */
  Entity &addSprite(const Texture &texture, const SDL_Rect &crop);
  /**
   * Add sprite component
   * For details look at TextureC
   * @param texture
   * @param spriteSheetCellSize
   * @param spriteSheetPosition
   * @return Entity reference
   */
  Entity &addSprite(const Texture &texture,
                    const SDL_Point &spriteSheetCellSize,
                    const SDL_Point &spriteSheetPosition);

  /**
   * Add transform component
   * For details look at TransformC
   * @param position
   * @param size
   * @param angle
   * @param zIndex
   * @return Entity reference
   */
  Entity &addTransform(const Point &position,
                       const SDL_Point &size,
                       double angle = 0,
                       int zIndex = 0);
  /**
   * @return Transform component
   */
  TransformC &getTransform() const;

  Entity &addAnimationPlayer(const AnimationPlayerC &animationPlayerC);
  /**
   * Add animation player component
   * For details look at AnimationPlayerC
   * @param texture
   * @param spriteSheetCellSize
   * @return Entity reference
   */
  Entity &addAnimationPlayer(const Texture &texture,
                             const SDL_Point &spriteSheetCellSize);
  /**
   * @return Animation player component
   */
  AnimationPlayerC &getAnimationPlayer() const;

  Entity &addColliderManager(const ColliderManagerC &colliderManagerC);

  /**
   * Add timer component
   * @return  Entity reference
   */
  Entity &addTimer();
  Entity &addTimer(const TimerC &timerC);
  /**
   * @return Timer component
   */
  TimerC &getTimer() const;
};

#endif // BOMBERMAN_ENTITY_H
