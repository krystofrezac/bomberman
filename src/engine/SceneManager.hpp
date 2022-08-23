#ifndef BOMBERMAN_SCENEMANAGER_H
#define BOMBERMAN_SCENEMANAGER_H

#include "Scene.hpp"

// Because of weird include dependency
class Scene;

/**
 * Switches scenes
 * Important for closing whole app at once
 */
class SceneManager {
private:
  std::shared_ptr<Scene> prevScene;
  std::shared_ptr<Scene> scene;

public:
  /**
   * Start rendering scenes
   * Call only once after first scene is set
   * Loops until stop is called
   */
  void start();
  /**
   * Set scene that should be run next
   * @param scene
   */
  void setScene(const std::shared_ptr<Scene> scene);
  /**
   * Stop rendering all scenes
   */
  void stop();
};

#endif // BOMBERMAN_SCENEMANAGER_H
