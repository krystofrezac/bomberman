#include "PowerUpScript.hpp"

void PowerUpScript::onCollision(const std::string &myColliderName,
                                const std::string &collidedWithName,
                                Entity collidedWith) {
  entity->destroy();
}