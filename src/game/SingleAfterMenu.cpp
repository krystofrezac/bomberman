#include "SingleAfterMenu.hpp"

#include "scripts/ButtonScript.hpp"

#include "level/LevelSaves.hpp"
#include "level/SingleLevelScene.hpp"

#include "MainMenu.hpp"

SingleAfterMenu::SingleAfterMenu(const Window &window,
                                 const Renderer &renderer,
                                 SceneManager &sceneManager,
                                 State state)
    : Scene(window, renderer, sceneManager, {0xFF, 0xFF, 0xFF}) {
  int scale = SCENE_SIZE / 100 / 2;

  Texture textsTexture(renderer, "assets/menus/texts.bmp", 0xac, 0x32, 0x32);

  int statusSheetY = 0;
  if (state == LOST)
    statusSheetY = 1;

  // status text
  createEntity()
    .addSprite(textsTexture, SDL_Point{100, 14}, SDL_Point{0, statusSheetY})
    .addTransform(Point(SCENE_SIZE / 2 - 70 * scale / 2, 1000),
                  SDL_Point{100 * scale, 14 * scale});

  Texture buttonsTexture(
    renderer, "assets/menus/buttons.bmp", 0xac, 0x32, 0x32);

  bool showNextLevel =
    state == WON && LevelSaves::levelExist(LevelSaves::getSavedLevel() + 1);
  if (showNextLevel) {
    // next level button
    createEntity().addScript(std::make_shared<ButtonScript>(
      [&]() { handleNextLevel(); },
      SDL_Point{SCENE_SIZE / 2 - 100 * scale / 2, 2000},
      SDL_Point{100 * scale, 23 * scale},
      buttonsTexture,
      SDL_Point{100, 23},
      SDL_Point{0, 4},
      SDL_Point{1, 4},
      SDL_Point{2, 4}));
  }

  int playAgainButtonY = 3500;
  if (!showNextLevel)
    playAgainButtonY = 2000;

  // play again button
  createEntity().addScript(std::make_shared<ButtonScript>(
    [&]() { handlePlayAgain(); },
    SDL_Point{SCENE_SIZE / 2 - 100 * scale / 2, playAgainButtonY},
    SDL_Point{100 * scale, 23 * scale},
    buttonsTexture,
    SDL_Point{100, 23},
    SDL_Point{0, 5},
    SDL_Point{1, 5},
    SDL_Point{2, 5}));

  // main menu button
  createEntity().addScript(std::make_shared<ButtonScript>(
    [&]() { handleMainMenu(); },
    SDL_Point{SCENE_SIZE / 2 - 100 * scale / 2, playAgainButtonY + 1500},
    SDL_Point{100 * scale, 23 * scale},
    buttonsTexture,
    SDL_Point{100, 23},
    SDL_Point{0, 6},
    SDL_Point{1, 6},
    SDL_Point{2, 6}));
}

void SingleAfterMenu::handleNextLevel() {
  int levelNumber = LevelSaves::getSavedLevel() + 1;
  LevelSaves::saveLevel(levelNumber);

  std::shared_ptr<SingleLevelScene> levelScene =
    std::make_shared<SingleLevelScene>(
      getWindow(), getRenderer(), getSceneManager(), levelNumber);

  getSceneManager().setScene(levelScene);
}
void SingleAfterMenu::handlePlayAgain() {
  std::shared_ptr<SingleLevelScene> levelScene =
    std::make_shared<SingleLevelScene>(getWindow(),
                                       getRenderer(),
                                       getSceneManager(),
                                       LevelSaves::getSavedLevel());

  getSceneManager().setScene(levelScene);
}
void SingleAfterMenu::handleMainMenu() {
  int nextLevelNumber = LevelSaves::getSavedLevel() + 1;
  if (LevelSaves::levelExist(nextLevelNumber))
    LevelSaves::saveLevel(nextLevelNumber);

  std::shared_ptr<MainMenu> scene =
    std::make_shared<MainMenu>(getWindow(), getRenderer(), getSceneManager());

  getSceneManager().setScene(scene);
}