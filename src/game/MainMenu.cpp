#include "MainMenu.hpp"

#include "MultiBeforeMenu.hpp"
#include "SingleBeforeMenu.hpp"

#include "scripts/ButtonScript.hpp"

MainMenu::MainMenu(const Window &window,
                   const Renderer &renderer,
                   SceneManager &sceneManager)
    : Scene(window, renderer, sceneManager, {0xff, 0xff, 0xff}) {
  Texture titleTexture(renderer, "assets/menus/title.bmp");
  int titleScale = SCENE_SIZE / 225 / 2;

  // title
  createEntity()
    .addSprite(titleTexture)
    .addTransform(Point(SCENE_SIZE / 2 - 225 * titleScale / 2, 1000),
                  SDL_Point{225 * titleScale, 30 * titleScale});

  Texture loadGameButtonTexture(
    renderer, "assets/menus/buttons.bmp", 0xac, 0x32, 0x32);
  int scale = SCENE_SIZE / 100 / 2;

  // single player button
  createEntity().addScript(std::make_shared<ButtonScript>(
    [&]() { handleSinglePlayer(); },
    SDL_Point{SCENE_SIZE / 2 - 100 * scale / 2, 2500},
    SDL_Point{100 * scale, 23 * scale},
    loadGameButtonTexture,
    SDL_Point{100, 23},
    SDL_Point{0, 0},
    SDL_Point{1, 0},
    SDL_Point{2, 0}));

  // multi player button
  createEntity().addScript(std::make_shared<ButtonScript>(
    [&]() { handleMultiPlayer(); },
    SDL_Point{SCENE_SIZE / 2 - 100 * scale / 2, 4000},
    SDL_Point{100 * scale, 23 * scale},
    loadGameButtonTexture,
    SDL_Point{100, 23},
    SDL_Point{0, 1},
    SDL_Point{1, 1},
    SDL_Point{2, 1}));

  // exit button
  createEntity().addScript(std::make_shared<ButtonScript>(
    [&]() { handleExit(); },
    SDL_Point{SCENE_SIZE / 2 - 100 * scale / 2, 5500},
    SDL_Point{100 * scale, 23 * scale},
    loadGameButtonTexture,
    SDL_Point{100, 23},
    SDL_Point{0, 7},
    SDL_Point{1, 7},
    SDL_Point{2, 7}));
}

void MainMenu::handleSinglePlayer() {
  std::shared_ptr<SingleBeforeMenu> singleBeforeMenu =
    std::make_shared<SingleBeforeMenu>(
      getWindow(), getRenderer(), getSceneManager());
  getSceneManager().setScene(singleBeforeMenu);
}
void MainMenu::handleMultiPlayer() {
  std::shared_ptr<MultiBeforeMenu> multiBeforeMenu =
    std::make_shared<MultiBeforeMenu>(
      getWindow(), getRenderer(), getSceneManager());
  getSceneManager().setScene(multiBeforeMenu);
}
void MainMenu::handleExit() { getSceneManager().stop(); }