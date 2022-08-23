#include "Scene.hpp"

#include "processors/CollisionProcessor.hpp"
#include "processors/ScriptProcessor.hpp"
#include "processors/SpriteProcessor.hpp"
#include "processors/TimerProcessor.hpp"
#include "processors/TransformProcessor.hpp"

#include "iostream"

// region Public methods
void Scene::start() {
  onStart();
  running = true;
  while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      handleEvent(event);
    }

    Uint32 delta = calculateDelta();

    onRender(delta);
    render(delta);
  }
}
void Scene::stop() { running = false; }
// endregion

// region Protected methods
Scene::Scene(const Window &window,
             const Renderer &renderer,
             SceneManager &sceneManger,
             const SDL_Color &backgroundColor)
    : window(window), renderer(renderer), sceneManger(sceneManger),
      backgroundColor(backgroundColor) {

  ScriptProcessor::observeScriptComponentConstruct(registry);

  SDL_RenderSetLogicalSize(renderer.getSDLRenderer(), SCENE_SIZE, SCENE_SIZE);
}

void Scene::onStart() {}
void Scene::onRender(Uint32 delta) {}
void Scene::onEvent(const SDL_Event &event) {}

Entity Scene::createEntity() {
  // shallow copy is enough
  return Entity(&registry);
}

Window Scene::getWindow() { return window; }
Renderer Scene::getRenderer() { return renderer; }
SceneManager &Scene::getSceneManager() { return sceneManger; }
// endregion

// region Private methods
void Scene::render(Uint32 delta) {
  SDL_SetRenderDrawColor(renderer.getSDLRenderer(),
                         backgroundColor.r,
                         backgroundColor.g,
                         backgroundColor.b,
                         backgroundColor.a);
  SDL_RenderClear(renderer.getSDLRenderer());

  // region processors
  TimerProcessor::process(registry, delta);
  ScriptProcessor::update(registry);
  TransformProcessor::process(registry, delta);
  CollisionProcessor::process(registry);
  SpriteProcessor::process(registry, renderer, delta);
  // endregion

  // When closing do not render 1 frame from all scenes
  SDL_RenderPresent(renderer.getSDLRenderer());
}

Uint32 fpsTime = 0;
size_t frames = 0;

Uint32 Scene::calculateDelta() {
  Uint32 tickTime = SDL_GetTicks();

  Uint32 delta;
  if (firstDelta) {
    delta = 0;
    firstDelta = false;
  } else
    delta = tickTime - lastTick;

  lastTick = tickTime;

  fpsTime += delta;
  frames++;
  if (fpsTime > 1000) {
    // TODO remove
    std::cout << "FPS:" << frames / (fpsTime / 1000) << std::endl;
    fpsTime = 0;
    frames = 0;
  }

  return delta;
}

void Scene::handleEvent(const SDL_Event &event) {
  if (event.type == SDL_QUIT)
    sceneManger.stop();

  ScriptProcessor::propagateEvent(registry, event);
  onEvent(event);
}
// endregion