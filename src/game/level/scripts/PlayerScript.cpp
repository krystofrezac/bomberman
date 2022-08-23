#include "PlayerScript.hpp"

#include "../LevelScene.hpp"
#include "BombScript.hpp"

PlayerScript::PlayerScript(const Texture &levelTexture,
                           const Texture &playerTexture,
                           int tileSize,
                           SDL_Point startPosition,
                           ControlsType controlsType,
                           const std::function<void()> onDie)
    : levelTexture(levelTexture), playerTexture(playerTexture),
      tileSize(tileSize), startPosition(startPosition),
      controlsType(controlsType), onDie(onDie) {
  if (controlsType == WASD) {
    controls[0] = SDLK_w;
    controls[1] = SDLK_d;
    controls[2] = SDLK_s;
    controls[3] = SDLK_a;
    controls[4] = SDLK_SPACE;
  } else {
    controls[0] = SDLK_UP;
    controls[1] = SDLK_RIGHT;
    controls[2] = SDLK_DOWN;
    controls[3] = SDLK_LEFT;
    controls[4] = SDLK_RETURN;
  }
}

void PlayerScript::onConstruct() {
  generatePlayerAnimations();

  int scale = tileSize / 16;

  collider = Collider(
    "player",
    SDL_Point{11 * scale, 5 * scale},
    SDL_Point{0, 13 * scale},
    LevelScene::PLAYER_POWERUP_LAYER | LevelScene::PLAYER_WALL_LAYER |
      LevelScene::ENEMY_PLAYER_LAYER | LevelScene::EXPLOSION_PLAYER_LAYER,
    false);

  entity
    ->addTransform(
      // corner - offset of collider + sprite padding to move to center of tile
      Point(startPosition.x * tileSize - collider.offset.x + 3 * scale,
            startPosition.y * tileSize - collider.offset.y + 5.5 * scale),
      SDL_Point{12 * scale, 18 * scale},
      0,
      Z_INDEX)
    .addColliderManager(ColliderManagerC(MASS).addCollider(collider))
    .addTimer();

  // lives
  liveScript = std::make_shared<LivesScript>(
    playerTexture, tileSize, controlsType == ARROWS);
  createEntity().addScript(liveScript);

  // bomb manager
  bombManagerScript = std::make_shared<BombManagerScript>(
    levelTexture, tileSize, controlsType == ARROWS);
  createEntity().addScript(bombManagerScript);
}
void PlayerScript::onEvent(const SDL_Event &event) {
  if (event.type == SDL_KEYDOWN)
    handleKeyDown(event.key.keysym.sym);
  if (event.type == SDL_KEYUP)
    handleKeyUp(event.key.keysym.sym);
}
void PlayerScript::onCollision(const std::string &myColliderName,
                               const std::string &collidedWithName,
                               Entity collidedWith) {
  // if name starts with enemy
  if (collidedWithName.rfind("enemy", 0) == 0 ||
      collidedWithName == "explosion") {
    if (immortal || state == DEAD)
      return;

    if (!immortal)
      liveScript->removeLive();

    immortal = true;

    if (liveScript->livesRemaining() == 0) {
      handleKeyUp(lastKey);

      state = DEAD;

      entity->getAnimationPlayer().setAnimation("dead").startAnimation();

      entity->getTimer().setTimeout(5000).start();
    } else {
      if (state == IDLE)
        handleKeyUp(lastKey);
      else
        handleKeyDown(lastKey);

      entity->getTimer().setTimeout(IMMORTAL_TIMEOUT).start();
    }
  }
  if (collidedWithName == "powerup-more-bombs") {
    bombManagerScript->addBomb();
  }
  if (collidedWithName == "powerup-bigger-bombs") {
    bombManagerScript->makeBiggerExplosions();
  }
}
void PlayerScript::onTimer() {
  if (state == DEAD) {
    onDie();

    return;
  }

  immortal = false;

  if (state == IDLE)
    handleKeyUp(lastKey);
  else
    handleKeyDown(lastKey);
}

void PlayerScript::handleKeyDown(const SDL_Keycode keycode) {
  if (state == DEAD)
    return;
  TransformC &transformC = entity->getTransform();
  AnimationPlayerC &animationPlayerC = entity->getAnimationPlayer();

  // cannot use switch because c++ is amazing ;)
  if (keycode == controls[0]) {
    lastKey = keycode;
    state = UP;
    transformC.setSpeed({0, -SPEED});
    if (immortal)
      animationPlayerC.setAnimation("upImmortal");
    else
      animationPlayerC.setAnimation("up");
    animationPlayerC.startAnimation();
  } else if (keycode == controls[1]) {
    lastKey = keycode;
    state = RIGHT;
    transformC.setSpeed({SPEED, 0});
    if (immortal)
      animationPlayerC.setAnimation("rightImmortal");
    else
      animationPlayerC.setAnimation("right");
    animationPlayerC.startAnimation();
  } else if (keycode == controls[2]) {
    lastKey = keycode;
    state = DOWN;
    transformC.setSpeed({0, SPEED});
    if (immortal)
      animationPlayerC.setAnimation("downImmortal");
    else
      animationPlayerC.setAnimation("down");
    animationPlayerC.startAnimation();
  } else if (keycode == controls[3]) {
    lastKey = keycode;
    state = LEFT;
    transformC.setSpeed({-SPEED, 0});
    if (immortal)
      animationPlayerC.setAnimation("leftImmortal");
    else
      animationPlayerC.setAnimation("left");
    animationPlayerC.startAnimation();
  } else if (keycode == controls[4]) {
    placeBomb();
  }
}
void PlayerScript::handleKeyUp(const SDL_Keycode keycode) {
  if (state == DEAD)
    return;

  if (!((keycode == controls[0] && state == UP) ||
        (keycode == controls[2] && state == DOWN) ||
        (keycode == controls[3] && state == LEFT) ||
        (keycode == controls[1] && state == RIGHT) || state == IDLE))
    return;
  state = IDLE;

  entity->getTransform().setSpeed({0, 0});

  AnimationPlayerC &animationPlayerC = entity->getAnimationPlayer();

  if (keycode == controls[0])
    animationPlayerC.setAnimation("upIdle");
  else if (keycode == controls[3])
    animationPlayerC.setAnimation("leftIdle");
  else if (keycode == controls[1])
    animationPlayerC.setAnimation("rightIdle");
  else
    animationPlayerC.setAnimation("downIdle");

  if (immortal)
    animationPlayerC.startAnimation();
  else {
    animationPlayerC.setFrame(0);
    animationPlayerC.stopAnimation();
  }
}

void PlayerScript::placeBomb() {
  Point playerPosition = entity->getTransform().getPosition();

  Point bombPosition(
    playerPosition.x + collider.offset.x + collider.size.x / 2 -
      (int)(playerPosition.x + collider.offset.x + collider.size.x / 2) %
        tileSize,
    playerPosition.y + collider.offset.y + collider.size.y / 2 -
      (int)(playerPosition.y + collider.offset.y + collider.size.y / 2) %
        tileSize);

  bombManagerScript->placeBomb(bombPosition);
}

void PlayerScript::generatePlayerAnimations() const {
  int row = 0;
  if (controlsType == ARROWS)
    row = 1;

  Animation leftAnimation = Animation("left", true)
                              .addFrame({0, row}, ANIMATION_SPEED)
                              .addFrame({1, row}, ANIMATION_SPEED)
                              .addFrame({0, row}, ANIMATION_SPEED)
                              .addFrame({2, row}, ANIMATION_SPEED);

  Animation rightAnimation = Animation("right", true)
                               .addFrame({9, row}, ANIMATION_SPEED)
                               .addFrame({10, row}, ANIMATION_SPEED)
                               .addFrame({9, row}, ANIMATION_SPEED)
                               .addFrame({11, row}, ANIMATION_SPEED);

  Animation upAnimation = Animation("up", true)
                            .addFrame({4, row}, ANIMATION_SPEED)
                            .addFrame({5, row}, ANIMATION_SPEED)
                            .addFrame({4, row}, ANIMATION_SPEED)
                            .addFrame({3, row}, ANIMATION_SPEED);

  Animation downAnimation = Animation("down", true)
                              .addFrame({7, row}, ANIMATION_SPEED)
                              .addFrame({8, row}, ANIMATION_SPEED)
                              .addFrame({7, row}, ANIMATION_SPEED)
                              .addFrame({6, row}, ANIMATION_SPEED);

  entity->addAnimationPlayer(
    AnimationPlayerC(playerTexture, SDL_Point{18, 26})
      .addAnimation(leftAnimation)
      .addAnimation(rightAnimation)
      .addAnimation(upAnimation)
      .addAnimation(downAnimation)
      .addAnimation(generateHitAnimation(leftAnimation, "leftImmortal"))
      .addAnimation(generateHitAnimation(rightAnimation, "rightImmortal"))
      .addAnimation(generateHitAnimation(upAnimation, "upImmortal"))
      .addAnimation(generateHitAnimation(downAnimation, "downImmortal"))
      .addAnimation(generateIdleAnimation(leftAnimation, "leftIdle"))
      .addAnimation(generateIdleAnimation(rightAnimation, "rightIdle"))
      .addAnimation(generateIdleAnimation(upAnimation, "upIdle"))
      .addAnimation(generateIdleAnimation(downAnimation, "downIdle"))
      .addAnimation(Animation("dead", false)
                      .addFrame({12, row}, ANIMATION_SPEED)
                      .addFrame({13, row}, ANIMATION_SPEED)
                      .addFrame({14, row}, ANIMATION_SPEED)
                      .addFrame({15, row}, ANIMATION_SPEED)
                      .addFrame({16, row}, ANIMATION_SPEED)
                      .addFrame({17, row}, ANIMATION_SPEED))
      .setAnimation("down"));
}
Animation PlayerScript::generateHitAnimation(const Animation &original,
                                             const std::string &name) const {
  int row = 0;
  if (controlsType == ARROWS)
    row = 1;
  Animation animation(name, true);
  for (const Frame &frame : original.getFrames()) {
    animation.addFrame(frame.position, ANIMATION_SPEED);
    animation.addFrame(SDL_Point{18, row}, ANIMATION_SPEED);
  }
  return animation;
}
Animation PlayerScript::generateIdleAnimation(const Animation &original,
                                              const std::string &name) const {
  int row = 0;
  if (controlsType == ARROWS)
    row = 1;
  Animation animation =
    Animation(name, true)
      .addFrame(original.getFrames()[0].position, ANIMATION_SPEED)
      .addFrame(SDL_Point{18, row}, ANIMATION_SPEED);
  return animation;
}