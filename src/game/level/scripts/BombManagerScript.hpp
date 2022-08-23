#ifndef BOMBERMAN_BOMBMANAGERSCRIPT_H
#define BOMBERMAN_BOMBMANAGERSCRIPT_H

#include "../../../engine/Texture.hpp"

#include "../../../engine/components/ScriptC.hpp"
#include "../../../engine/components/TransformC.hpp"

/**
 * Logic for managing and displaying information about player bombs
 */
class BombManagerScript : public Script {
private:
  Texture levelTexture;
  int tileSize;
  bool displayOnRight;

  int explosionSize = 2;
  int maxPlacedBombs = 1;
  int numberOfPlacedBombs = 0;

public:
  BombManagerScript(const Texture &levelTexture,
                    int tileSize,
                    bool displayOnRight);

  /**
   * Place bomb on position
   * @param bombPosition
   */
  void placeBomb(const Point &bombPosition);
  /**
   * Called when bomb disappears from scene
   */
  void onBombDestroy();
  /**
   * Add one bomb to player
   */
  void addBomb();
  /**
   * Make bomb explosion bigger
   */
  void makeBiggerExplosions();
};

#endif // BOMBERMAN_BOMBMANAGERSCRIPT_H
