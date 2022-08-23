#ifndef BOMBERMAN_EXPLOSIONNODEXSCRIPT_H
#define BOMBERMAN_EXPLOSIONNODEXSCRIPT_H

#include "../../../engine/components/ScriptC.hpp"

class ExplosionNodeScript : public Script {
private:
  std::function<void(Entity &, const SDL_Point &)> onDestroy;
  const SDL_Point offset;

 void onCollision(const std::string &myColliderName, const std::string &collidedWithName, Entity collidedWith) override;

public:
  ExplosionNodeScript(
    std::function<void(Entity &, const SDL_Point &)> onDestroy,
    const SDL_Point &offset);
};

#endif // BOMBERMAN_EXPLOSIONNODEXSCRIPT_H
