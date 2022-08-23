#include "CollisionProcessor.hpp"

#include "../components/ScriptC.hpp"

// region Public methods
void CollisionProcessor::process(entt::registry &registry) {
  auto view = registry.view<ColliderManagerC, TransformC>();

  for (auto heavyEntity : view) {
    const ColliderManagerC &heavyColliderManagerC =
      registry.get<ColliderManagerC>(heavyEntity);

    for (auto lightEntity : view) {
      if (heavyEntity == lightEntity)
        continue;

      const ColliderManagerC &lightColliderManagerC =
        registry.get<ColliderManagerC>(lightEntity);

      // entities must be in correct order
      if (heavyColliderManagerC.getMass() < lightColliderManagerC.getMass())
        continue;

      TransformC &heavyTransformC = registry.get<TransformC>(heavyEntity);
      TransformC &lightTransformC = registry.get<TransformC>(lightEntity);

      bool collided = false;
      std::string heavyName;
      std::string lightName;

      for (const auto &heavyCollider : heavyColliderManagerC.getColliders()) {
        for (const auto &lightCollider : lightColliderManagerC.getColliders()) {
          if (handleCollision(heavyCollider,
                              heavyTransformC,
                              lightCollider,
                              lightTransformC)) {
            collided = true;
            heavyName = heavyCollider.name;
            lightName = lightCollider.name;
            break;
          }
        }
        if (collided)
          break;
      }

      if (!collided)
        continue;

      // Call script method ONCE
      if (registry.all_of<ScriptC>(heavyEntity)) {
        ScriptC &script = registry.get<ScriptC>(heavyEntity);
        script.getScript()->onCollision(
          heavyName, lightName, Entity(&registry, lightEntity));
      }
      if (registry.all_of<ScriptC>(lightEntity)) {
        ScriptC &script = registry.get<ScriptC>(lightEntity);
        script.getScript()->onCollision(
          lightName, heavyName, Entity(&registry, heavyEntity));
      }
    }
  }
}
// endregion

// region Private methods
bool CollisionProcessor::handleCollision(const Collider &heavyCollider,
                                         TransformC &heavyTransformC,
                                         const Collider &lightCollider,
                                         TransformC &lightTransformC) {
  if ((heavyCollider.collisionMask & lightCollider.collisionMask) == 0)
    return false;

  const SDL_Rect &heavyBoundary =
    calculateBoundary(heavyCollider, heavyTransformC);
  const SDL_Rect &lightBoundary =
    calculateBoundary(lightCollider, lightTransformC);

  if (!(heavyBoundary.x < lightBoundary.x + lightBoundary.w &&
        heavyBoundary.x + heavyBoundary.w > lightBoundary.x &&
        heavyBoundary.y < lightBoundary.y + lightBoundary.h &&
        heavyBoundary.h + heavyBoundary.y > lightBoundary.y))
    return false;

  if (heavyCollider.isVirtual || lightCollider.isVirtual)
    return true;

  // distances to each side of heavy collider
  float leftDistance = lightBoundary.x + lightBoundary.w - heavyBoundary.x;
  float rightDistance = heavyBoundary.x + heavyBoundary.w - lightBoundary.x;
  float upDistance = lightBoundary.y + lightBoundary.h - heavyBoundary.y;
  float downDistance = heavyBoundary.y + heavyBoundary.h - lightBoundary.y;

  // choose the smallest distance
  Direction direction = LEFT;
  float distance = leftDistance;

  if (rightDistance < distance) {
    direction = RIGHT;
    distance = rightDistance;
  }
  if (upDistance < distance) {
    direction = UP;
    distance = upDistance;
  }
  if (downDistance < distance) {
    direction = DOWN;
    distance = downDistance;
  }

  moveEntityOutsideBoundary(
    direction, lightTransformC, lightBoundary, heavyBoundary);
  return true;
}

SDL_Rect CollisionProcessor::calculateBoundary(const Collider &collider,
                                               const TransformC &transformC) {
  const Point &position = transformC.getPosition();
  const SDL_Point &colliderSize = collider.size;
  const SDL_Point &offset = collider.offset;
  SDL_Rect boundary = {(int)position.x + offset.x,
                       (int)position.y + offset.y,
                       colliderSize.x,
                       colliderSize.y};
  return boundary;
}

void CollisionProcessor::moveEntityOutsideBoundary(
  const Direction direction,
  TransformC &lightTransform,
  const SDL_Rect &lightBoundary,
  const SDL_Rect &heavyBoundary) {
  const Point &position = lightTransform.getPosition();
  Point newPosition;

  switch (direction) {
  case UP:
    newPosition = {position.x,
                   position.y + heavyBoundary.y - lightBoundary.y -
                     lightBoundary.h};
    break;
  case DOWN:
    newPosition = {position.x,
                   position.y - lightBoundary.y + heavyBoundary.y +
                     heavyBoundary.h};
    break;
  case LEFT:
    newPosition = {position.x + heavyBoundary.x - lightBoundary.x -
                     lightBoundary.w,
                   position.y};
    break;
  case RIGHT:
    newPosition = {position.x - lightBoundary.x + heavyBoundary.x +
                     heavyBoundary.w,
                   position.y};
    break;
  }
  lightTransform.move(newPosition);
}
// endregion