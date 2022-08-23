#ifndef BOMBERMAN_SINGLEBEFOREMENU_H
#define BOMBERMAN_SINGLEBEFOREMENU_H

#include "../engine/Scene.hpp"

class SingleBeforeMenu : public Scene {
private:
  /**
   * Callback for load game button
   * If save file exists load save level else load the first leve
   */
  void handleLoad();
  /**
   * Callback for new game button
   * Load first level and save it to save file
   */
  void handleNewGame();
  /**
   * Callback for main menu button
   * Load main menu scene
   */
  void handleMainMenu();

public:
  SingleBeforeMenu(const Window &window,
                   const Renderer &renderer,
                   SceneManager &sceneManager);
};

#endif // BOMBERMAN_SINGLEBEFOREMENU_H
