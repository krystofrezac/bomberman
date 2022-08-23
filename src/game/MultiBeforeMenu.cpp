#include "MultiBeforeMenu.hpp"

#include "MainMenu.hpp"
#include "level/MultiLevelScene.hpp"

#include "scripts/ButtonScript.hpp"

MultiBeforeMenu::MultiBeforeMenu(const Window &window,
                                 const Renderer &renderer,
                                 SceneManager &sceneManager)
    : Scene(window, renderer, sceneManager, {0xff, 0xff, 0xff}) {
  int scale = SCENE_SIZE / 100 / 2;

  Texture buttonsTexture(
    renderer, "assets/menus/buttons.bmp", 0xac, 0x32, 0x32);

  // map 1 button
  createEntity().addScript(std::make_shared<ButtonScript>(
    [&]() { loadMap(0); },
    SDL_Point{SCENE_SIZE / 2 - 100 * scale / 2, 1000},
    SDL_Point{100 * scale, 23 * scale},
    buttonsTexture,
    SDL_Point{100, 23},
    SDL_Point{0, 8},
    SDL_Point{1, 8},
    SDL_Point{2, 8}));

  // map 2 button
  createEntity().addScript(std::make_shared<ButtonScript>(
    [&]() { loadMap(1); },
    SDL_Point{SCENE_SIZE / 2 - 100 * scale / 2, 2500},
    SDL_Point{100 * scale, 23 * scale},
    buttonsTexture,
    SDL_Point{100, 23},
    SDL_Point{0, 9},
    SDL_Point{1, 9},
    SDL_Point{2, 9}));

  // main menu button
  createEntity().addScript(std::make_shared<ButtonScript>(
    [&]() { handleMainMenu(); },
    SDL_Point{SCENE_SIZE / 2 - 100 * scale / 2, 4000},
    SDL_Point{100 * scale, 23 * scale},
    buttonsTexture,
    SDL_Point{100, 23},
    SDL_Point{0, 6},
    SDL_Point{1, 6},
    SDL_Point{2, 6}));
}

void MultiBeforeMenu::loadMap(int levelNumber) {
  std::shared_ptr<MultiLevelScene> levelScene =
    std::make_shared<MultiLevelScene>(
      getWindow(), getRenderer(), getSceneManager(), levelNumber);
  getSceneManager().setScene(levelScene);
}
void MultiBeforeMenu::handleMainMenu() {
  std::shared_ptr<MainMenu> scene =
    std::make_shared<MainMenu>(getWindow(), getRenderer(), getSceneManager());

  getSceneManager().setScene(scene);
}