#include "Window.hpp"

Window::Window(
  const std::string &title, int x, int y, int w, int h, Uint32 flags) {
  auto deleter = [](SDL_Window *window) { SDL_DestroyWindow(window); };
  window.reset(SDL_CreateWindow(title.c_str(), x, y, w, h, flags), deleter);
}

SDL_Window *Window::getSDLWindow() const { return window.get(); }