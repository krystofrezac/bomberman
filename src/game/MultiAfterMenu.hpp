#ifndef BOMBERMAN_MULTIAFTERMENU_H
#define BOMBERMAN_MULTIAFTERMENU_H

#include "../engine/Scene.hpp"

class MultiAfterMenu : public Scene {
private:
  void handleMainMenu();

public:
  enum State { PLAYER1, PLAYER2, DRAW };

  MultiAfterMenu(const Window &window,
                 const Renderer &renderer,
                 SceneManager &sceneManager,
                 State state);
};

#endif // BOMBERMAN_MULTIAFTERMENU_H
