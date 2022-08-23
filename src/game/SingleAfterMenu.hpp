#ifndef BOMBERMAN_SINGLEAFTERMENU_H
#define BOMBERMAN_SINGLEAFTERMENU_H

#include "../engine/Scene.hpp"

class SingleAfterMenu : public Scene {
private:
  void handleNextLevel();
  void handlePlayAgain();
  void handleMainMenu();

  void readSavedLevel();

public:
  enum State { WON, LOST };

  SingleAfterMenu(const Window &window, const Renderer &renderer,
                  SceneManager &sceneManager, State state);
};

#endif // BOMBERMAN_SINGLEAFTERMENU_H
