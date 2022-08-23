#include "BombManagerScript.hpp"

#include "../../../engine/Scene.hpp"
#include "../../../engine/components/SpriteC.hpp"

#include "BombScript.hpp"

BombManagerScript::BombManagerScript(const Texture &levelTexture,
                                     int tileSize,
                                     bool displayOnRight)
    : levelTexture(levelTexture), tileSize(tileSize),
      displayOnRight(displayOnRight) {}

void BombManagerScript::placeBomb(const Point &bombPosition) {
  if (numberOfPlacedBombs >= maxPlacedBombs)
    return;

  numberOfPlacedBombs++;

  // bomb
  createEntity().addScript(std::make_shared<BombScript>(
    levelTexture, tileSize, bombPosition, explosionSize, this));
}
void BombManagerScript::onBombDestroy() { numberOfPlacedBombs--; }
void BombManagerScript::addBomb() {
  maxPlacedBombs++;

  int scale = tileSize / 16;

  SDL_Point size{11 * scale, 9 * scale};
  Point position = Point(2 * tileSize + scale * 9 * (maxPlacedBombs - 1), 100);
  if (displayOnRight)
    position.x = Scene::SCENE_SIZE - position.x - size.x;

  // badge
  createEntity()
    .addTransform(position, size, 0, 10000)
    // Only animation player support z index
    .addAnimationPlayer(
      AnimationPlayerC(levelTexture, SDL_Point{16, 16})
        .addAnimation(Animation("main", false).addFrame({0, 1}, 1))
        .setAnimation("main")
        .startAnimation());
}
void BombManagerScript::makeBiggerExplosions() {
  explosionSize++;

  int scale = tileSize / 16;

  SDL_Point size{11 * scale, 9 * scale};
  Point position =
    Point(2 * tileSize + scale * 9 * (explosionSize - 2), size.y);
  if (displayOnRight)
    position.x = Scene::SCENE_SIZE - position.x - size.x;

  // badge
  createEntity()
    .addTransform(position, size, 0, 10000)
    // Only animation player support z index
    .addAnimationPlayer(
      AnimationPlayerC(levelTexture, SDL_Point{16, 16})
        .addAnimation(Animation("main", false).addFrame({1, 1}, 1))
        .setAnimation("main")
        .startAnimation());
}