#include "BalloonEnemyScript.hpp"

#include "../LevelScene.hpp"

BalloonEnemyScript::BalloonEnemyScript(const Texture &enemyTexture,
                                       int tileSize,
                                       const SDL_Point &startPosition,
                                       Direction startDirection,
                                       const std::function<void()> onDie)
    : enemyTexture(enemyTexture), tileSize(tileSize),
      startPosition(startPosition), onDie(onDie) {
  // direction anti-clockwise rotated
  switch (startDirection) {
  case UP:
    direction = LEFT;
    break;
  case DOWN:
    direction = RIGHT;
    break;
  case LEFT:
    direction = DOWN;
    break;
  case RIGHT:
    direction = UP;
    break;
  }
}

void BalloonEnemyScript::onConstruct() {
  int scale = tileSize / 16;

  Collider wallCollider("",
                        SDL_Point{tileSize, tileSize},
                        SDL_Point{-2 * scale, 8 * scale},
                        LevelScene::ENEMY_WALL_LAYER,
                        false);

  entity
    ->addColliderManager(ColliderManagerC(MASS)
                           .addCollider(wallCollider)
                           .addCollider("enemy-balloon",
                                        SDL_Point{11 * scale, 6 * scale},
                                        SDL_Point{1 * scale, 12 * scale},
                                        LevelScene::ENEMY_PLAYER_LAYER |
                                          LevelScene::EXPLOSION_ENEMY_LAYER,
                                        false))
    .addTransform(
      // tile corner - collider offset
      Point(startPosition.x * tileSize - wallCollider.offset.x,
            startPosition.y * tileSize - wallCollider.offset.y),
      SDL_Point{12 * scale, 18 * scale})
    .addAnimationPlayer(AnimationPlayerC(enemyTexture, SDL_Point{16, 24})
                          .addAnimation(Animation("down", true)
                                          .addFrame({0, 0}, ANIMATION_SPEED)
                                          .addFrame({1, 0}, ANIMATION_SPEED)
                                          .addFrame({2, 0}, ANIMATION_SPEED)
                                          .addFrame({3, 0}, ANIMATION_SPEED))
                          .addAnimation(Animation("up", true)
                                          .addFrame({4, 0}, ANIMATION_SPEED)
                                          .addFrame({5, 0}, ANIMATION_SPEED)
                                          .addFrame({6, 0}, ANIMATION_SPEED)
                                          .addFrame({7, 0}, ANIMATION_SPEED))
                          .addAnimation(Animation("left", true)
                                          .addFrame({8, 0}, ANIMATION_SPEED)
                                          .addFrame({9, 0}, ANIMATION_SPEED)
                                          .addFrame({10, 0}, ANIMATION_SPEED)
                                          .addFrame({11, 0}, ANIMATION_SPEED))
                          .addAnimation(Animation("right", true)
                                          .addFrame({12, 0}, ANIMATION_SPEED)
                                          .addFrame({13, 0}, ANIMATION_SPEED)
                                          .addFrame({14, 0}, ANIMATION_SPEED)
                                          .addFrame({15, 0}, ANIMATION_SPEED)));

  changeDirection();
}
void BalloonEnemyScript::onUpdate() {
  if (destroy) {
    onDie();
    entity->destroy();
  }
}
void BalloonEnemyScript::onCollision(const std::string &myColliderName,
                                     const std::string &collidedWithName,
                                     Entity collidedWith) {
  if (collidedWithName == "player" || collidedWithName == "explosion") {
    destroy = true;
    return;
  }
  if (collidedWithName != "radar-enemy-potato")
    changeDirection();
}

void BalloonEnemyScript::changeDirection() {
  TransformC &transformC = entity->getTransform();
  AnimationPlayerC &animationPlayerC = entity->getAnimationPlayer();

  switch (direction) {
  case LEFT:
    transformC.setSpeed({0, -SPEED});
    animationPlayerC.setAnimation("up");
    direction = UP;
    break;
  case UP:
    transformC.setSpeed({SPEED, 0});
    animationPlayerC.setAnimation("right");
    direction = RIGHT;
    break;
  case RIGHT:
    transformC.setSpeed({0, SPEED});
    animationPlayerC.setAnimation("down");
    direction = DOWN;
    break;
  case DOWN:
    transformC.setSpeed({-SPEED, 0});
    animationPlayerC.setAnimation("left");
    direction = LEFT;
    break;
  }
  animationPlayerC.startAnimation();
}