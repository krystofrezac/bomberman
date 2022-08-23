#include "Texture.hpp"

#include <stdexcept>

// region Helper functions
std::shared_ptr<SDL_Surface> loadSurface(const std::string &filename) {
  return std::shared_ptr<SDL_Surface>(
    SDL_LoadBMP(filename.c_str()),
    [](SDL_Surface *surface) { SDL_FreeSurface(surface); });
}

std::shared_ptr<SDL_Texture>
createTexture(const Renderer &renderer,
              const std::shared_ptr<SDL_Surface> &surface) {
  return std::shared_ptr<SDL_Texture>(
    SDL_CreateTextureFromSurface(renderer.getSDLRenderer(), surface.get()),
    [](SDL_Texture *texture) { SDL_DestroyTexture(texture); });
}

std::invalid_argument getSurfaceError() {
  return std::invalid_argument("SDL could not load image. SDL_Error: " +
                               std::string(SDL_GetError()));
}

std::invalid_argument getTextureError() {
  return std::invalid_argument("Unable to create texture. SDL_Error: " +
                               std::string(SDL_GetError()));
}

// endregion

// region Methods
Texture::Texture() {}
Texture::Texture(const Renderer &renderer, const std::string &filename) {
  auto surface = loadSurface(filename);
  if (!surface)
    throw getSurfaceError();

  texture = createTexture(renderer, surface);
  if (!texture)
    throw getTextureError();
}
Texture::Texture(const Renderer &renderer,
                 const std::string &filename,
                 Uint8 r,
                 Uint8 g,
                 Uint8 b) {
  auto surface = loadSurface(filename);
  if (!surface)
    throw getSurfaceError();

  SDL_SetColorKey(
    surface.get(), SDL_TRUE, SDL_MapRGB(surface->format, r, g, b));

  texture = createTexture(renderer, surface);
  if (!texture)
    throw getTextureError();
}

SDL_Texture *Texture::getSDLTexture() const { return texture.get(); }
// endregion