#ifndef BOMBERMAN_MAINSCENE_H
#define BOMBERMAN_MAINSCENE_H

#include "../../engine/Renderer.hpp"
#include "../../engine/Scene.hpp"

#include "../../engine/components/AnimationPlayerC.hpp"

#include "../SingleAfterMenu.hpp"

#include "scripts/PlayerScript.hpp"

class LevelScene : public Scene {
private:
  Texture playerTexture;
  Texture enemyTexture;
  Texture levelTexture;
  int levelNumber;

  enum Tiles { EMPTY, WALL };

  int tileSize = SCENE_SIZE / 15;
  const int WALL_MASS = 1000;

  void onStart() override;
  void onEvent(const SDL_Event &event) override;

  void generatePlayer(SDL_Point position, const std::string &controls);
  void generateBalloonEnemy(SDL_Point position, const std::string &direction);
  void generatePotatoEnemy(SDL_Point position);
  void generateMoreBombsPowerUp(SDL_Point position);
  void generateBiggerBombsPowerUp(SDL_Point position);
  void generateTile(SDL_Point position, Tiles tile);
  void generateMapBorders();

protected:
  /**
   * Number of enemies alive
   */
  int numberOfEnemies = 0;

  /**
   * Get level filename
   * @param levelNumber
   * @return level filename
   */
  virtual std::string getFileName(int levelNumber) = 0;
  /**
   * Callback when player die
   * @param controlsType player controlType
   */
  virtual void onPlayerDie(PlayerScript::ControlsType controlsType) = 0;

public:
  /**
   * Collision masks
   */
  enum Layers {
    PLAYER_WALL_LAYER = 0b1,
    EXPLOSION_PLAYER_LAYER = 0b10,
    EXPLOSION_WALL_LAYER = 0b100,
    ENEMY_WALL_LAYER = 0b1000,
    PLAYER_POWERUP_LAYER = 0b10000,
    ENEMY_PLAYER_LAYER = 0b100000,
    EXPLOSION_ENEMY_LAYER = 0b1000000
  };
/**
 * @param window
 * @param renderer
 * @param sceneManger
 * @param levelNumber Number of level to load
 */
  LevelScene(const Window &window,
             const Renderer &renderer,
             SceneManager &sceneManger,
             int levelNumber);
};

#endif // BOMBERMAN_MAINSCENE_H
