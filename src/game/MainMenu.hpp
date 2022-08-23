#ifndef BOMBERMAN_MAINMENU_H
#define BOMBERMAN_MAINMENU_H

#include "../engine/Scene.hpp"

class MainMenu : public Scene {
private:
  /**
   * Callback for single player button
   * Open SingleBeforeMenu
   */
  void handleSinglePlayer();
  /**
   * Callback for multi player button
   * Open MultiBeforeMenu
   */
  void handleMultiPlayer();
  /**
   * Callback for exit button
   * Exit the application
   */
  void handleExit();

public:
  MainMenu(const Window &window,
           const Renderer &renderer,
           SceneManager &sceneManager);
};

#endif // BOMBERMAN_MAINMENU_H
