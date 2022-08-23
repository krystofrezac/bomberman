#ifndef BOMBERMAN_MULTIBEFOREMENU_H
#define BOMBERMAN_MULTIBEFOREMENU_H

#include "../engine/Scene.hpp"

class MultiBeforeMenu : public Scene {
private:
  void loadMap(int levelNumber);
  void handleMainMenu();

public:
  MultiBeforeMenu(const Window &window, const Renderer &renderer,
                  SceneManager &sceneManager );
};

#endif // BOMBERMAN_MULTIBEFOREMENU_H
