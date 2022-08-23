#include "ColliderManagerC.hpp"

// region ColliderManagerC
ColliderManagerC::ColliderManagerC(int mass) : mass(mass) {}

ColliderManagerC &ColliderManagerC::addCollider(const Collider &collider) {
  colliders.push_back(collider);
  return *this;
}
ColliderManagerC &ColliderManagerC::addCollider(const std::string &name,
                                                const SDL_Point &size,
                                                const SDL_Point &offset,
                                                int collisionMask,
                                                bool isVirtual) {
  Collider collider(name, size, offset, collisionMask, isVirtual);
  colliders.push_back(collider);
  return *this;
}

std::vector<Collider> ColliderManagerC::getColliders() const {
  return colliders;
}
int ColliderManagerC::getMass() const { return mass; }
// endregion

// region Collider
Collider::Collider(const std::string &name,
                   const SDL_Point &size,
                   const SDL_Point &offset,
                   int collisionMask,
                   bool isVirtual)
    : name(name), size(size), offset(offset), collisionMask(collisionMask),
      isVirtual(isVirtual) {}
// endregion