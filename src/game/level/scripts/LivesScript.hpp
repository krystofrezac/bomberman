#ifndef BOMBERMAN_LIVESSCRIPT_H
#define BOMBERMAN_LIVESSCRIPT_H

#include "../../../engine/components/AnimationPlayerC.hpp"
#include "../../../engine/components/ScriptC.hpp"

/**
 * Class for managing and displaying player lives
 */
class LivesScript : public Script {
private:
  Texture playerTexture;
  int tileSize;
  bool onRight;

  int lives = 3;
  Entity hearts[3];

  void onConstruct() override;

public:
  LivesScript(const Texture &playerTexture, int tileSize, bool onRight);

  void removeLive();
  int livesRemaining() const;
};

#endif // BOMBERMAN_LIVESSCRIPT_H
