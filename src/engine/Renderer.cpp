#include "Renderer.hpp"

Renderer::Renderer(const Window &window) {
  auto deleter = [](SDL_Renderer *renderer) { SDL_DestroyRenderer(renderer); };
  renderer.reset(
    SDL_CreateRenderer(window.getSDLWindow(), -1, SDL_RENDERER_ACCELERATED),
    deleter);
}

SDL_Renderer *Renderer::getSDLRenderer() const { return renderer.get(); }