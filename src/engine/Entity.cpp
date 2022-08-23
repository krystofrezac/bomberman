#include "Entity.hpp"

#include "components/SpriteC.hpp"
#include "components/TransformC.hpp"

Entity::Entity() {}
Entity::Entity(entt::registry *registry) : registry(registry) {
  entity = registry->create();
}
Entity::Entity(entt::registry *registry, entt::entity entity)
    : registry(registry), entity(entity) {}
bool Entity::operator==(const Entity &entity) {
  return this->entity == entity.getRawEntity();
}

void Entity::destroy() { registry->destroy(entity); }

entt::entity Entity::getRawEntity() const { return entity; }

Entity &Entity::addScript(const std::shared_ptr<Script> script) {
  registry->emplace<ScriptC>(entity, script);
  return *this;
}

Entity &Entity::addSprite(const Texture &texture) {
  registry->emplace<SpriteC>(entity, texture);
  return *this;
}
Entity &Entity::addSprite(const Texture &texture, const SDL_Rect &crop) {
  registry->emplace<SpriteC>(entity, texture, crop);
  return *this;
}
Entity &Entity::addSprite(const Texture &texture,
                          const SDL_Point &spriteSheetCellSize,
                          const SDL_Point &spriteSheetPosition) {
  registry->emplace<SpriteC>(
    entity, texture, spriteSheetCellSize, spriteSheetPosition);
  return *this;
}

Entity &Entity::addTransform(const Point &position,
                             const SDL_Point &size,
                             double angle,
                             int zIndex) {
  registry->emplace<TransformC>(entity, position, size, angle, zIndex);
  return *this;
}
TransformC &Entity::getTransform() const {
  return registry->get<TransformC>(entity);
}

Entity &Entity::addAnimationPlayer(const AnimationPlayerC &animationPlayerC) {
  registry->emplace<AnimationPlayerC>(entity, animationPlayerC);
  return *this;
}
Entity &Entity::addAnimationPlayer(const Texture &texture,
                                   const SDL_Point &spriteSheetCellSize) {
  registry->emplace<AnimationPlayerC>(entity, texture, spriteSheetCellSize);
  return *this;
}
AnimationPlayerC &Entity::getAnimationPlayer() const {
  return registry->get<AnimationPlayerC>(entity);
}

Entity &Entity::addColliderManager(const ColliderManagerC &colliderManagerC) {
  registry->emplace<ColliderManagerC>(entity, colliderManagerC);
  return *this;
}

Entity &Entity::addTimer() {
  registry->emplace<TimerC>(entity);
  return *this;
}
Entity &Entity::addTimer(const TimerC &timerC) {
  registry->emplace<TimerC>(entity, timerC);
  return *this;
}
TimerC &Entity::getTimer() const { return registry->get<TimerC>(entity); }