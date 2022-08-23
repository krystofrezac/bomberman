#ifndef BOMBERMAN_POWERUPSCRIPT_H
#define BOMBERMAN_POWERUPSCRIPT_H

#include "../../../engine/components/ScriptC.hpp"

class PowerUpScript : public Script {
private:
  void onCollision(const std::string &myColliderName,
                   const std::string &collidedWithName,
                   Entity collidedWith) override;
};

#endif // BOMBERMAN_POWERUPSCRIPT_H
