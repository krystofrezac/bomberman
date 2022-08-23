#ifndef BOMBERMAN_SCENE_H
#define BOMBERMAN_SCENE_H

#include <SDL2/SDL.h>

#include "Entity.hpp"
#include "Renderer.hpp"
#include "SceneManager.hpp"

// Because of weird include dependency
class SceneManager;

class Scene {
private:
  Window window;
  Renderer renderer;
  SceneManager &sceneManger;
  SDL_Color backgroundColor;
  Uint32 lastTick;
  bool running = false;
  bool firstDelta = true;

  void render(Uint32 delta);
  Uint32 calculateDelta();
  void handleEvent(const SDL_Event &event);

protected:
  /**
   * Scene registry
   */
  entt::registry registry;

  /**
   * @param window Window to use for rendering
   * @param renderer Renderer to use for rendering
   * @param backgroundColor Background color of scene
   */
  Scene(const Window &window,
        const Renderer &renderer,
        SceneManager &sceneManger,
        const SDL_Color &backgroundColor);

  /**
   * Called at start before render loop starts
   */
  virtual void onStart();
  /** Called before each rendering
   * @param delta Time between frames
   */
  virtual void onRender(Uint32 delta);
  /** Called for each event
   * @param event
   */
  virtual void onEvent(const SDL_Event &event);

  /**
   * Create new entity
   * @return created entity
   */
  Entity createEntity();

  /**
   * @return Window
   */
  Window getWindow();
  /**
   * @return Renderer
   */
  Renderer getRenderer();

  /**
   * @return Scene manager
   */
  SceneManager &getSceneManager();

public:
  /**
   * Size of scene in both directions
   */
  static const int SCENE_SIZE = 10000;

  /**
   * Start rendering scene
   */
  void start();

  /**
   * Stop rendering scene
   */
  void stop();
};

#endif // BOMBERMAN_SCENE_H
