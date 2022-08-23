#include "PotatoEnemyScript.hpp"

#include "../LevelScene.hpp"

PotatoEnemyScript::PotatoEnemyScript(const Texture &enemyTexture,
                                     int tileSize,
                                     const SDL_Point &startPosition,
                                     const std::function<void()> onDie)
    : enemyTexture(enemyTexture), tileSize(tileSize),
      startPosition(startPosition), onDie(onDie) {}

void PotatoEnemyScript::onConstruct() {
  int scale = tileSize / 16;

  Collider wallCollider("enemy-potato",
                        {8 * scale, 4 * scale},
                        {2 * scale, 13 * scale},
                        LevelScene::ENEMY_WALL_LAYER |
                          LevelScene::ENEMY_PLAYER_LAYER |
                          LevelScene::EXPLOSION_ENEMY_LAYER,
                        false);

  entity
    ->addTransform(
      // tile corner - base offset
      Point(startPosition.x * tileSize + 2 * scale,
            startPosition.y * tileSize - 8 * scale),
      SDL_Point{12 * scale, 18 * scale})
    .addColliderManager(ColliderManagerC(MASS)
                          .addCollider(wallCollider)
                          // radar
                          .addCollider("radar-enemy-potato",
                                       {5 * tileSize, 5 * tileSize},
                                       {-2 * tileSize, -2 * tileSize},
                                       LevelScene::ENEMY_PLAYER_LAYER,
                                       true))
    .addAnimationPlayer(AnimationPlayerC(enemyTexture, {16, 24})
                          .addAnimation(Animation("down", true)
                                          .addFrame({0, 1}, ANIMATION_SPEED)
                                          .addFrame({1, 1}, ANIMATION_SPEED)
                                          .addFrame({2, 1}, ANIMATION_SPEED)
                                          .addFrame({3, 1}, ANIMATION_SPEED)
                                          .addFrame({4, 1}, ANIMATION_SPEED)
                                          .addFrame({5, 1}, ANIMATION_SPEED)
                                          .addFrame({6, 1}, ANIMATION_SPEED)
                                          .addFrame({7, 1}, ANIMATION_SPEED)
                                          .addFrame({8, 1}, ANIMATION_SPEED))
                          .addAnimation(Animation("up", true)
                                          .addFrame({9, 1}, ANIMATION_SPEED)
                                          .addFrame({10, 1}, ANIMATION_SPEED)
                                          .addFrame({11, 1}, ANIMATION_SPEED)
                                          .addFrame({12, 1}, ANIMATION_SPEED)
                                          .addFrame({13, 1}, ANIMATION_SPEED)
                                          .addFrame({14, 1}, ANIMATION_SPEED)
                                          .addFrame({15, 1}, ANIMATION_SPEED)
                                          .addFrame({16, 1}, ANIMATION_SPEED)
                                          .addFrame({17, 1}, ANIMATION_SPEED))
                          .addAnimation(Animation("left", true)
                                          .addFrame({18, 1}, ANIMATION_SPEED)
                                          .addFrame({19, 1}, ANIMATION_SPEED)
                                          .addFrame({20, 1}, ANIMATION_SPEED)
                                          .addFrame({21, 1}, ANIMATION_SPEED)
                                          .addFrame({22, 1}, ANIMATION_SPEED)
                                          .addFrame({23, 1}, ANIMATION_SPEED)
                                          .addFrame({24, 1}, ANIMATION_SPEED)
                                          .addFrame({25, 1}, ANIMATION_SPEED)
                                          .addFrame({26, 1}, ANIMATION_SPEED))
                          .addAnimation(Animation("right", true)
                                          .addFrame({16, 1}, ANIMATION_SPEED)
                                          .addFrame({17, 1}, ANIMATION_SPEED)
                                          .addFrame({18, 1}, ANIMATION_SPEED)
                                          .addFrame({19, 1}, ANIMATION_SPEED)
                                          .addFrame({20, 1}, ANIMATION_SPEED)
                                          .addFrame({21, 1}, ANIMATION_SPEED)
                                          .addFrame({22, 1}, ANIMATION_SPEED)
                                          .addFrame({23, 1}, ANIMATION_SPEED)
                                          .addFrame({24, 1}, ANIMATION_SPEED))
                          .setAnimation("down")
                          .startAnimation())
    .addTimer();
}
void PotatoEnemyScript::onCollision(const std::string &myColliderName,
                                    const std::string &collidedWithName,
                                    Entity collidedWith) {
  if (myColliderName == "radar-enemy-potato" && collidedWithName == "player") {
    Point playerPosition = collidedWith.getTransform().getPosition();
    Point direction =
      (playerPosition - entity->getTransform().getPosition()).normalize(SPEED);

    entity->getTransform().setSpeed(direction);
    entity->getTimer().setTimeout(STOP_FOLLOWING_AFTER).start();
  }
  if (myColliderName == "enemy-potato" &&
      (collidedWithName == "player" || collidedWithName == "explosion")) {
    destroy = true;
    onDie();
  }
}
void PotatoEnemyScript::onTimer() {
  entity->getTransform().setSpeed(Point(0, 0));
}
void PotatoEnemyScript::onUpdate() {
  if (destroy)
    entity->destroy();
}