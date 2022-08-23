#include "LevelScene.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

#include "../../engine/Texture.hpp"

#include "../../engine/components/ColliderManagerC.hpp"
#include "../../engine/components/ScriptC.hpp"
#include "../../engine/components/SpriteC.hpp"
#include "../../engine/components/TimerC.hpp"
#include "../../engine/components/TransformC.hpp"

#include "../MainMenu.hpp"

#include "scripts/BalloonEnemyScript.hpp"
#include "scripts/PotatoEnemyScript.hpp"
#include "scripts/PowerUpScript.hpp"

#include "LevelSaves.hpp"

// region public methods
LevelScene::LevelScene(const Window &window,
                       const Renderer &renderer,
                       SceneManager &sceneManager,
                       int levelNumber)
    : Scene(window, renderer, sceneManager, {0, 0, 0, 0}),
      playerTexture(renderer, "assets/player.bmp", 0x40, 0x90, 0x38),
      enemyTexture(renderer, "assets/enemy.bmp", 0x76, 0x42, 0x8a),
      levelNumber(levelNumber) {}
// endregion

// region private methods
// Outside constructor because getFileName is pure virtual method
void LevelScene::onStart() {
  std::ifstream levelFile(getFileName(levelNumber));
  if (!levelFile)
    throw std::invalid_argument("Save file cannot be opened, " +
                                getFileName(levelNumber));

  std::string line;

  if (!getline(levelFile, line))
    throw std::invalid_argument("Invalid format");

  std::string mapTheme = line;
  levelTexture =
    Texture(getRenderer(), "assets/maps/" + mapTheme + ".bmp", 0xd7, 0x0, 0xff);

  std::stringstream lineStream;
  while (getline(levelFile, line)) {
    lineStream = std::stringstream(line);

    std::string objectName = "";
    int x = 0, y = 0;
    lineStream >> objectName >> x >> y;
    x++;
    y++;

    // cannot use switch because c++ is awesome
    if (objectName == "player") {
      std::string controls;
      if (!(lineStream >> controls))
        throw std::invalid_argument("Invalid format - missing player controls");

      generatePlayer(SDL_Point{x, y}, controls);
    } else if (objectName == "wall")
      generateTile(SDL_Point{x, y}, WALL);
    else if (objectName == "empty")
      generateTile(SDL_Point{x, y}, EMPTY);
    else if (objectName == "enemy-balloon") {
      std::string direction;
      if (!(lineStream >> direction))
        throw std::invalid_argument(
          "Invalid format - missing enemy-balloon direction");
      generateBalloonEnemy(SDL_Point{x, y}, direction);
    } else if (objectName == "enemy-potato") {
      std::string direction;
      generatePotatoEnemy(SDL_Point{x, y});
    } else if (objectName == "powerup-more-bombs") {
      generateMoreBombsPowerUp(SDL_Point{x, y});
    } else if (objectName == "powerup-bigger-bombs") {
      generateBiggerBombsPowerUp(SDL_Point{x, y});
    }
  }

  levelFile.close();

  generateMapBorders();
}
void LevelScene::onEvent(const SDL_Event &event) {
  // on escape key press load main menu
  if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
    std::shared_ptr<MainMenu> mainMenu =
      std::make_shared<MainMenu>(getWindow(), getRenderer(), getSceneManager());
    getSceneManager().setScene(mainMenu);
  }
}

void LevelScene::generatePlayer(SDL_Point position,
                                const std::string &controls) {
  PlayerScript::ControlsType controlsType = PlayerScript::WASD;
  if (controls == "arrows")
    controlsType = PlayerScript::ARROWS;

  createEntity().addScript(std::make_shared<PlayerScript>(
    levelTexture,
    playerTexture,
    tileSize,
    position,
    controlsType,
    [controlsType, this]() { onPlayerDie(controlsType); }));
}
void LevelScene::generateBalloonEnemy(SDL_Point position,
                                      const std::string &direction) {
  numberOfEnemies++;

  BalloonEnemyScript::Direction startDirection = BalloonEnemyScript::DOWN;
  if (direction == "up")
    startDirection = BalloonEnemyScript::UP;
  if (direction == "left")
    startDirection = BalloonEnemyScript::LEFT;
  if (direction == "right")
    startDirection = BalloonEnemyScript::RIGHT;

  createEntity().addScript(std::make_shared<BalloonEnemyScript>(
    enemyTexture, tileSize, position, startDirection, [&]() {
      numberOfEnemies--;
    }));
}
void LevelScene::generatePotatoEnemy(SDL_Point position) {
  numberOfEnemies++;
  createEntity().addScript(std::make_shared<PotatoEnemyScript>(
    enemyTexture, tileSize, position, [&]() { numberOfEnemies--; }));
}
void LevelScene::generateMoreBombsPowerUp(SDL_Point position) {
  int scale = tileSize / 16;
  SDL_Point size = {11 * scale, 9 * scale};
  createEntity()
    .addTransform(Point(position.x * tileSize + 4 * scale,
                        position.y * tileSize + 5.5 * scale),
                  size)
    .addSprite(levelTexture, SDL_Point{16, 16}, SDL_Point{0, 1})
    .addColliderManager(ColliderManagerC(0).addCollider(
      "powerup-more-bombs", size, {0, 0}, Layers::PLAYER_POWERUP_LAYER, true))
    .addScript(std::make_shared<PowerUpScript>());
}
void LevelScene::generateBiggerBombsPowerUp(SDL_Point position) {
  int scale = tileSize / 16;
  SDL_Point size = {11 * scale, 9 * scale};

  createEntity()
    .addTransform(Point(position.x * tileSize + 4 * scale,
                        position.y * tileSize + 5.5 * scale),
                  size)
    .addSprite(levelTexture, SDL_Point{16, 16}, SDL_Point{1, 1})
    .addColliderManager(ColliderManagerC(0).addCollider(
      "powerup-bigger-bombs", size, {0, 0}, Layers::PLAYER_POWERUP_LAYER, true))
    .addScript(std::make_shared<PowerUpScript>());
}
void LevelScene::generateTile(SDL_Point position, Tiles tile) {
  Entity entity = createEntity().addTransform(
    Point(tileSize * position.x, tileSize * position.y),
    SDL_Point{tileSize, tileSize});

  if (tile == WALL) {
    entity.addSprite(levelTexture, SDL_Point{16, 16}, SDL_Point{1, 0})
      .addColliderManager(ColliderManagerC(WALL_MASS).addCollider(
        "wall",
        SDL_Point{tileSize, tileSize},
        SDL_Point{0, 0},
        Layers::PLAYER_WALL_LAYER | Layers::ENEMY_WALL_LAYER |
          Layers::EXPLOSION_WALL_LAYER,
        false));
  } else if (tile == EMPTY)
    entity.addSprite(levelTexture, SDL_Point{16, 16}, SDL_Point{0, 0});
}
void LevelScene::generateMapBorders() {
  char wallMask = Layers::PLAYER_WALL_LAYER | Layers::ENEMY_WALL_LAYER |
                  Layers::EXPLOSION_WALL_LAYER;

  // border collider
  createEntity()
    .addTransform(Point{0, 0}, SDL_Point{SCENE_SIZE, SCENE_SIZE})
    .addColliderManager(ColliderManagerC(WALL_MASS)
                          .addCollider("wall",
                                       SDL_Point{tileSize, SCENE_SIZE},
                                       SDL_Point{0, 0},
                                       wallMask,
                                       false)
                          .addCollider("wall",
                                       SDL_Point{tileSize, SCENE_SIZE},
                                       SDL_Point{SCENE_SIZE - tileSize, 0},
                                       wallMask,
                                       false)
                          .addCollider("wall",
                                       SDL_Point{SCENE_SIZE, tileSize},
                                       SDL_Point{0, 0},
                                       wallMask,
                                       false)
                          .addCollider("wall",
                                       SDL_Point{SCENE_SIZE, tileSize},
                                       SDL_Point{0, SCENE_SIZE - tileSize},
                                       wallMask,
                                       false));

  // border sprites
  // top
  for (int x = 0; x < 15; x++) {
    SDL_Point sprite = {1, 2};
    if (x == 0)
      sprite = {0, 2};
    else if (x == 14)
      sprite = {2, 2};

    createEntity()
      .addTransform(Point{x * tileSize + 0.f, 0}, SDL_Point{tileSize, tileSize})
      .addSprite(levelTexture, SDL_Point{16, 16}, sprite);
  }

  // bottom
  for (int x = 0; x < 15; x++) {
    SDL_Point sprite = {1, 4};
    if (x == 0)
      sprite = {0, 4};
    else if (x == 14)
      sprite = {2, 4};

    createEntity()
      .addTransform(Point{x * tileSize + 0.f, 14 * tileSize + 0.f},
                    SDL_Point{tileSize, tileSize})
      .addSprite(levelTexture, SDL_Point{16, 16}, sprite);
  }

  // left
  for (int y = 1; y < 14; y++) {
    createEntity()
      .addTransform(Point{0, y * tileSize + 0.f}, SDL_Point{tileSize, tileSize})
      .addSprite(levelTexture, SDL_Point{16, 16}, {0, 3});
  }

  // right
  for (int y = 1; y < 14; y++) {
    createEntity()
      .addTransform(Point{14 * tileSize + 0.f, y * tileSize + 0.f},
                    SDL_Point{tileSize, tileSize})
      .addSprite(levelTexture, SDL_Point{16, 16}, {2, 3});
  }
}
// endregion