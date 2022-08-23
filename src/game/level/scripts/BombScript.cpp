#include "BombScript.hpp"

#include "../LevelScene.hpp"

#include "ExplosionNodeScript.hpp"

// region Public methods
BombScript::BombScript(const Texture &levelTexture,
                       int tileSize,
                       Point bombPosition,
                       int explosionSize,
                       BombManagerScript *bombManager)
    : levelTexture(levelTexture), tileSize(tileSize),
      bombPosition(bombPosition), explosionSize(explosionSize),
      bombManager(bombManager) {}
// endregion

// region Private methods
void BombScript::onConstruct() {
  entity
    ->addTransform(bombPosition, SDL_Point{tileSize, tileSize}, 0, BOMB_Z_INDEX)
    .addAnimationPlayer(AnimationPlayerC(levelTexture, SDL_Point{16, 16})
                          .addAnimation(Animation("spreading", false)
                                          .addFrame({4, 0}, IDLE_TIME)
                                          .addFrame({5, 0}, UNSTABLE_TIME)
                                          .addFrame({6, 0}, 1))
                          .addAnimation(Animation("thickening", false)
                                          .addFrame({6, 1}, THICKENING_SPEED)
                                          .addFrame({6, 2}, THICKENING_SPEED)
                                          .addFrame({6, 3}, THICKENING_SPEED)
                                          .addFrame({6, 4}, THICKENING_SPEED)
                                          .addFrame({6, 3}, THICKENING_SPEED)
                                          .addFrame({6, 2}, THICKENING_SPEED)
                                          .addFrame({6, 1}, THICKENING_SPEED))
                          .setAnimation("spreading")
                          .startAnimation())
    .addTimer(
      TimerC().setTimeout(IDLE_TIME + UNSTABLE_TIME + SPREAD_SPEED).start());
}
void BombScript::onTimer() {
  TimerC &timerC = entity->getTimer();
  if (timerState == SPREADING) {
    if (renderedRange == 0) {
      entity->addColliderManager(ColliderManagerC(0).addCollider(
        "explosion",
        SDL_Point{tileSize, tileSize},
        SDL_Point{0, 0},
        LevelScene::EXPLOSION_WALL_LAYER | LevelScene::EXPLOSION_PLAYER_LAYER |
          LevelScene::EXPLOSION_ENEMY_LAYER,
        true));
    }

    renderedRange++;

    if (spreadingRight)
      createExplosionNode(
        {renderedRange, 0}, 0, renderedRange == explosionSize);
    if (spreadingDown)
      createExplosionNode(
        {0, renderedRange}, 90, renderedRange == explosionSize);
    if (spreadingLeft)
      createExplosionNode(
        {-renderedRange, 0}, 180, renderedRange == explosionSize);
    if (spreadingUp)
      createExplosionNode(
        {0, -renderedRange}, -90, renderedRange == explosionSize);

    if (renderedRange == explosionSize)
      timerState = THICKENING;

    timerC.setTimeout(SPREAD_SPEED);
    timerC.start();
  } else if (timerState == THICKENING) {

    entity->getTransform().setZIndex(EXPLOSION_Z_INDEX);
    entity->getAnimationPlayer().setAnimation("thickening");

    for (Entity &node : nodes) {
      node.getAnimationPlayer().setAnimation("thickening");
    }

    timerState = REMOVING;
    timerC.setTimeout(7 * THICKENING_SPEED);
    timerC.start();
  } else if (timerState == REMOVING) {
    bombManager->onBombDestroy();

    for (Entity &node : nodes) {
      node.destroy();
    }

    entity->destroy();
  }
}

void BombScript::createExplosionNode(SDL_Point offset,
                                     double angle,
                                     bool endNode) {
  Entity explosionNode =
    createEntity()
      .addTransform(Point(bombPosition.x + offset.x * tileSize,
                          bombPosition.y + offset.y * tileSize),
                    SDL_Point{tileSize, tileSize},
                    angle,
                    EXPLOSION_Z_INDEX)
      .addColliderManager(ColliderManagerC(0).addCollider(
        "explosion",
        SDL_Point{tileSize, tileSize},
        SDL_Point{0, 0},
        LevelScene::EXPLOSION_WALL_LAYER | LevelScene::EXPLOSION_PLAYER_LAYER |
          LevelScene::EXPLOSION_ENEMY_LAYER,
        true))
      // call onDestroy callback when node touches wall
      .addScript(std::make_shared<ExplosionNodeScript>(
        [&](Entity &entityToDestroy, const SDL_Point &offset) {
          deleteNode(entityToDestroy, offset);
        },
        offset));

  AnimationPlayerC animationPlayerC(levelTexture, SDL_Point{16, 16});

  Animation spreadingAnimation =
    Animation("spreading", false).addFrame({8, 0}, SPREAD_SPEED);

  if (!endNode)
    spreadingAnimation.addFrame({7, 0}, 1);

  Animation thickeningAnimation("thickening", false);
  if (endNode) {
    thickeningAnimation.addFrame({8, 1}, THICKENING_SPEED)
      .addFrame({8, 2}, THICKENING_SPEED)
      .addFrame({8, 3}, THICKENING_SPEED)
      .addFrame({8, 4}, THICKENING_SPEED)
      .addFrame({8, 3}, THICKENING_SPEED)
      .addFrame({8, 2}, THICKENING_SPEED)
      .addFrame({8, 1}, THICKENING_SPEED);
  } else {
    thickeningAnimation.addFrame({7, 1}, THICKENING_SPEED)
      .addFrame({7, 2}, THICKENING_SPEED)
      .addFrame({7, 3}, THICKENING_SPEED)
      .addFrame({7, 4}, THICKENING_SPEED)
      .addFrame({7, 3}, THICKENING_SPEED)
      .addFrame({7, 2}, THICKENING_SPEED)
      .addFrame({7, 1}, THICKENING_SPEED);
  }
  animationPlayerC.addAnimation(spreadingAnimation)
    .addAnimation(thickeningAnimation)
    .setAnimation("spreading")
    .startAnimation();

  explosionNode.addAnimationPlayer(animationPlayerC);

  nodes.push_back(explosionNode);
}

void BombScript::deleteNode(Entity &nodeEntity, const SDL_Point &offset) {
  auto iterator = std::find(nodes.begin(), nodes.end(), nodeEntity);
  nodes.erase(iterator);

  if (offset.x < 0)
    spreadingLeft = false;
  if (offset.x > 0)
    spreadingRight = false;
  if (offset.y < 0)
    spreadingUp = false;
  if (offset.y > 0)
    spreadingDown = false;

  nodeEntity.destroy();
}
// endregion