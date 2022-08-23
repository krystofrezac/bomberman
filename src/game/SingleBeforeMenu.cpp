#include "SingleBeforeMenu.hpp"

#include "level/LevelSaves.hpp"
#include "level/SingleLevelScene.hpp"

#include "scripts/ButtonScript.hpp"

#include "MainMenu.hpp"

SingleBeforeMenu::SingleBeforeMenu(const Window &window,
                                   const Renderer &renderer,
                                   SceneManager &sceneManager)
    : Scene(window, renderer, sceneManager, {0xff, 0xff, 0xff}) {
  int scale = SCENE_SIZE / 100 / 2;

  Texture buttonsTexture(
    renderer, "assets/menus/buttons.bmp", 0xac, 0x32, 0x32);

  // load game button
  createEntity().addScript(std::make_shared<ButtonScript>(
    [&]() { handleLoad(); },
    SDL_Point{SCENE_SIZE / 2 - 100 * scale / 2, 1000},
    SDL_Point{100 * scale, 23 * scale},
    buttonsTexture,
    SDL_Point{100, 23},
    SDL_Point{0, 2},
    SDL_Point{1, 2},
    SDL_Point{2, 2}));

  // new game button
  createEntity().addScript(std::make_shared<ButtonScript>(
    [&]() { handleNewGame(); },
    SDL_Point{SCENE_SIZE / 2 - 100 * scale / 2, 2500},
    SDL_Point{100 * scale, 23 * scale},
    buttonsTexture,
    SDL_Point{100, 23},
    SDL_Point{0, 3},
    SDL_Point{1, 3},
    SDL_Point{2, 3}));

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

void SingleBeforeMenu::handleLoad() {
  std::shared_ptr<SingleLevelScene> levelScene =
    std::make_shared<SingleLevelScene>(getWindow(),
                                       getRenderer(),
                                       getSceneManager(),
                                       LevelSaves::getSavedLevel());
  getSceneManager().setScene(levelScene);
}
void SingleBeforeMenu::handleNewGame() {
  const SDL_MessageBoxButtonData buttons[] = {
    {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Continue"},
    {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "cancel"},
  };

  const SDL_MessageBoxData messageBoxData = {
    SDL_MESSAGEBOX_WARNING,
    nullptr,
    "",
    "Older save file will be rewritten! Do you really want to continue?",
    SDL_arraysize(buttons),
    buttons,
    nullptr};

  int buttonId;
  // error or continue button
  if (SDL_ShowMessageBox(&messageBoxData, &buttonId) < 0 || buttonId == 0) {
    LevelSaves::saveLevel(0);

    std::shared_ptr<SingleLevelScene> levelScene =
      std::make_shared<SingleLevelScene>(
        getWindow(), getRenderer(), getSceneManager(), 0);
    getSceneManager().setScene(levelScene);
  }
}
void SingleBeforeMenu::handleMainMenu() {
  std::shared_ptr<MainMenu> mainMenu =
    std::make_shared<MainMenu>(getWindow(), getRenderer(), getSceneManager());
  getSceneManager().setScene(mainMenu);
}