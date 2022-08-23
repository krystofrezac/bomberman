#ifndef BOMBERMAN_BALLOONENEMY_H
#define BOMBERMAN_BALLOONENEMY_H

#include "../../../engine/Texture.hpp"

#include "../../../engine/components/ScriptC.hpp"

class BalloonEnemyScript : public Script {
private:
  static const int ANIMATION_SPEED = 200;
  float SPEED = 0.5; // cannot be const because it's not int
  const int MASS = 10;

  bool destroy = false;

  Texture enemyTexture;
  int tileSize;
  const SDL_Point startPosition;
  const std::function<void()> onDie;

public:
  enum Direction { UP, RIGHT, DOWN, LEFT };

private:
  Direction direction;

  void onConstruct() override;
  void onUpdate() override;
  void onCollision(const std::string &myColliderName,
                   const std::string &collidedWithName,
                   Entity collidedWith) override;

  void changeDirection();

public:
  /**
   * @param enemyTexture
   * @param tileSize
   * @param startPosition starting tile coordinates
   */
  BalloonEnemyScript(const Texture &enemyTexture,
                     int tileSize,
                     const SDL_Point &startPosition,
                     Direction startDirection,
                     const std::function<void()> onDie);
};

#endif // BOMBERMAN_BALLOONENEMY_H
