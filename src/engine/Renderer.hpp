#ifndef BOMBERMAN_RENDERER_H
#define BOMBERMAN_RENDERER_H

#include "Window.hpp"

/**
 * Wrapper around SDL_Renderer
 */
class Renderer {
private:
  std::shared_ptr<SDL_Renderer> renderer;

public:
  /**
   * @param window Window to use in renderer creation
   */
  Renderer(const Window &window);

  /**
   * @return Raw SDL renderer
   */
  SDL_Renderer* getSDLRenderer() const;
};

#endif // BOMBERMAN_RENDERER_H
