#include "ExplosionNodeScript.hpp"

ExplosionNodeScript::ExplosionNodeScript(
  std::function<void(Entity &, const SDL_Point &)> onDestroy,
  const SDL_Point &offset)
    : onDestroy(onDestroy), offset(offset) {}

void ExplosionNodeScript::onCollision(const std::string &myColliderName,
                                      const std::string &collidedWithName,
                                      Entity collidedWith) {
  if (collidedWithName == "wall") {
    onDestroy(*entity.get(), offset);
  }
}