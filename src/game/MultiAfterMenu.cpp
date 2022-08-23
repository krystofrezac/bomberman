#include "MultiAfterMenu.hpp"

#include "MainMenu.hpp"

#include "scripts/ButtonScript.hpp"

MultiAfterMenu::MultiAfterMenu(const Window &window,
                               const Renderer &renderer,
                               SceneManager &sceneManager,
                               State state)
    : Scene(window, renderer, sceneManager, {0xff, 0xff, 0xff}) {
  int scale = SCENE_SIZE / 100 / 2;
  Texture textsTexture(renderer, "assets/menus/texts.bmp", 0xac, 0x32, 0x32);

  int statusSheetY = 2;
  if (state == PLAYER2)
    statusSheetY = 3;

  // status text
  createEntity()
    .addSprite(textsTexture, {100, 14}, {0, statusSheetY})
    .addTransform(Point(SCENE_SIZE / 2 - 100 * scale / 2, 1000),
                  {100 * scale, 14 * scale});

  Texture buttonsTexture(
    renderer, "assets/menus/buttons.bmp", 0xac, 0x32, 0x32);

  // main menu button
  createEntity().addScript(std::make_shared<ButtonScript>(
    [&]() { handleMainMenu(); },
    SDL_Point{SCENE_SIZE / 2 - 100 * scale / 2, 2500},
    SDL_Point{100 * scale, 23 * scale},
    buttonsTexture,
    SDL_Point{100, 23},
    SDL_Point{0, 6},
    SDL_Point{1, 6},
    SDL_Point{2, 6}));
}

void MultiAfterMenu::handleMainMenu() {
  std::shared_ptr<MainMenu> mainMenu =
    std::make_shared<MainMenu>(getWindow(), getRenderer(), getSceneManager());
  getSceneManager().setScene(mainMenu);
}
