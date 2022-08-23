#ifndef BOMBERMAN_COLLIDERMANAGER_H
#define BOMBERMAN_COLLIDERMANAGER_H

#include <vector>

#include <SDL2/SDL.h>
#include <string>

class Collider {
public:
  std::string name;
  SDL_Point size;
  SDL_Point offset;
  int collisionMask;
  bool isVirtual;

  /**
   * Initialize with default values
   */
  Collider() = default;
  /**
   * @param name Name that will be passed to script on collision
   * @param size Size
   * @param offset Offset from entity TransformC position
   * @param collisionMask Collision mask
   * @param isVirtual If true doesn't act as physical body, when you only need
   * to call onCollision
   */
  Collider(const std::string &name,
           const SDL_Point &size,
           const SDL_Point &offset,
           int collisionMask,
           bool isVirtual);
};

class ColliderManagerC {
  std::vector<Collider> colliders;
  int mass;

public:
  /**
   * @param mass Entity with lower mass will be moved and the other one will
   */
  ColliderManagerC(int mass);

  /**
   * Add collider
   * @param collider Collider to add
   * @return reference to self
   */
  ColliderManagerC &addCollider(const Collider &collider);
  /**
   * Add collider
   * @param size Size of collider
   * @param offset Offset from TransformC position
   * stay at same position
   * @param collisionMask If two collision masks are 0 after 'and', they can not
   * collider with each other
   * @param isVirtual If virtual no 'physics' is calculated and only event is
   * emitted
   * @return reference to self
   */
  ColliderManagerC &addCollider(const std::string &name,
                                const SDL_Point &size,
                                const SDL_Point &offset,
                                int collisionMask,
                                bool isVirtual);

  std::vector<Collider> getColliders() const;
  int getMass() const;
};

#endif // BOMBERMAN_COLLIDERMANAGER_H
