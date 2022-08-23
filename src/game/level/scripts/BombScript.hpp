#ifndef BOMBERMAN_BOMBSCRIPT_H
#define BOMBERMAN_BOMBSCRIPT_H

#include "../../../engine/Texture.hpp"

#include "../../../engine/components/AnimationPlayerC.hpp"
#include "../../../engine/components/ScriptC.hpp"
#include "../../../engine/components/TransformC.hpp"
#include "BombManagerScript.hpp"

class BombScript : public Script {
private:
  static const int IDLE_TIME = 2000;
  static const int UNSTABLE_TIME = 500;
  static const int SPREAD_SPEED = 75;
  static const int THICKENING_SPEED = 150;
  static constexpr int BOMB_Z_INDEX = -1;
  static constexpr int EXPLOSION_Z_INDEX = 10;

  Texture levelTexture;
  int tileSize;
  Point bombPosition;
  int explosionSize;
  BombManagerScript *bombManager;

  int renderedRange = 0;
  std::vector<Entity> nodes;

  bool spreadingUp = true;
  bool spreadingDown = true;
  bool spreadingRight = true;
  bool spreadingLeft = true;

  enum TimerState { SPREADING, THICKENING, REMOVING };
  TimerState timerState = SPREADING;

  void onConstruct() override;
  void onTimer() override;

  void createExplosionNode(SDL_Point offset, double angle, bool endNode);

  void deleteNode(Entity &nodeEntity, const SDL_Point &offset);

public:
  BombScript(const Texture &levelTexture,
             int tileSize,
             Point bombPosition,
             int explosionSize,
             BombManagerScript *bombManagerScript);
};

#endif // BOMBERMAN_BOMBSCRIPT_H
