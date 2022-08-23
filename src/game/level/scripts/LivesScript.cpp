#include "LivesScript.hpp"

#include "../../../engine/Scene.hpp"

LivesScript::LivesScript(const Texture &playerTexture,
                         int tileSize,
                         bool onRight)
    : playerTexture(playerTexture), tileSize(tileSize), onRight(onRight) {}

void LivesScript::onConstruct() {
  int scale = tileSize / 16;

  for (size_t i = 0; i < 3; i++) {

    Point position = Point(i * 14 * scale, 100);
    if (onRight) {
      position.x = Scene::SCENE_SIZE - position.x - 10 * scale;
    }

    // heart
    hearts[i] =
      createEntity()
        .addTransform(position, SDL_Point{12 * scale, 18 * scale}, 0, 10000)
        .addAnimationPlayer(
          AnimationPlayerC(playerTexture, SDL_Point{18, 26})
            .addAnimation(Animation("full", true).addFrame({19, 0}, 1))
            .addAnimation(Animation("empty", false).addFrame({19, 1}, 1))
            .setAnimation("full")
            .startAnimation());
  }
}

void LivesScript::removeLive() {
  if (lives <= 0)
    return;

  Entity heart = hearts[lives - 1];
  heart.getAnimationPlayer().setAnimation("empty");

  lives--;
}
int LivesScript::livesRemaining() const { return lives; }