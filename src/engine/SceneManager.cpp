#include "SceneManager.hpp"

void SceneManager::start() {
  while (true) {
    if (!scene)
      return;

    // Destructing of prevScene can start
    prevScene = nullptr;
    scene->start();
  }
}
void SceneManager::setScene(const std::shared_ptr<Scene> scene) {
  // Prevent destructing scene before frame cycle is finished
  prevScene = this->scene;

  if (prevScene) {
    prevScene->stop();
  }

  this->scene = scene;
}
void SceneManager::stop() {
  prevScene = scene;
  scene->stop();
  scene = nullptr;
}