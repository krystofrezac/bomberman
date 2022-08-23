#ifndef BOMBERMAN_WINDOW_H
#define BOMBERMAN_WINDOW_H

#include <memory>
#include <string>

#include <SDL2/SDL.h>

/**
 * Wrapper around SDL_Window
 */
class Window {
private:
  std::shared_ptr<SDL_Window> window;

public:
  /**
   * @param title Window title
   * @param x X position
   * @param y Y position
   * @param w Width
   * @param h Height
   * @param flags Flags
   */
  Window(const std::string &title, int x, int y, int w, int h, Uint32 flags);

  /**
   * @return Raw SDL window
   */
  SDL_Window* getSDLWindow() const;
};

#endif // BOMBERMAN_WINDOW_H
