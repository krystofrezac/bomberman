#ifndef BOMBERMAN_PLAYERSCRIPT_H
#define BOMBERMAN_PLAYERSCRIPT_H

#include "../../../engine/Texture.hpp"

#include "../../../engine/components/AnimationPlayerC.hpp"
#include "../../../engine/components/ColliderManagerC.hpp"
#include "../../../engine/components/ScriptC.hpp"
#include "../../../engine/components/TransformC.hpp"

#include "BombManagerScript.hpp"
#include "LivesScript.hpp"

class PlayerScript : public Script {
public:
  enum ControlsType { WASD, ARROWS };

private:
  float SPEED = 1.5; // cannot be const because it's not int
  static const int ANIMATION_SPEED = 200;
  static constexpr int MASS = 100;
  static const int IMMORTAL_TIMEOUT = 5000;
 static const int Z_INDEX=2;

  Texture levelTexture;
  Texture playerTexture;
  int tileSize;
  SDL_Point startPosition;
  ControlsType controlsType;
  std::function<void()> onDie;
  // top right down left
  SDL_Keycode controls[5];

  Collider collider;
  std::shared_ptr<LivesScript> liveScript;
  std::shared_ptr<BombManagerScript> bombManagerScript;

  enum State { IDLE, UP, DOWN, LEFT, RIGHT, DEAD };
  State state = IDLE;

  bool immortal = false;
  SDL_Keycode lastKey = SDLK_LEFT;

  void onConstruct() override;
  void onEvent(const SDL_Event &event) override;
  void onCollision(const std::string &myColliderName,
                   const std::string &collidedWithName,
                   Entity collidedWith) override;
  void onTimer() override;

  void handleKeyDown(const SDL_Keycode keycode);
  void handleKeyUp(const SDL_Keycode keycode);

  void placeBomb();

  void generatePlayerAnimations() const;
  Animation generateHitAnimation(const Animation &original,
                                 const std::string &name) const;
  Animation generateIdleAnimation(const Animation &original,
                                  const std::string &name) const;

public:
  PlayerScript(const Texture &levelTexture,
               const Texture &playerTexture,
               int tileSize,
               SDL_Point startPosition,
               ControlsType controlsType,
               const std::function<void()> onDie);
};

#endif // BOMBERMAN_PLAYERSCRIPT_H
