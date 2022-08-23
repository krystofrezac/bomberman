#ifndef BOMBERMAN_POTATOENEMYSCRIPT_H
#define BOMBERMAN_POTATOENEMYSCRIPT_H

#include "../../../engine/components/ScriptC.hpp"

class PotatoEnemyScript : public Script {
private:
  static const int ANIMATION_SPEED = 75;
  float SPEED = 1; // cannot be const because it's not int
  const int MASS = 10;
  const int STOP_FOLLOWING_AFTER = 1000;

 bool destroy = false;

  Texture enemyTexture;
  int tileSize;
  const SDL_Point startPosition;
  const std::function<void()> onDie;

  void onConstruct() override;
  void onCollision(const std::string &myColliderName,
                   const std::string &collidedWithName,
                   Entity collidedWith) override;
  void onTimer() override;
 void onUpdate() override;

public:
  PotatoEnemyScript(const Texture &enemyTexture,
                    int tileSize,
                    const SDL_Point &startPosition,
                    const std::function<void()> onDie);
};

#endif // BOMBERMAN_POTATOENEMYSCRIPT_H
