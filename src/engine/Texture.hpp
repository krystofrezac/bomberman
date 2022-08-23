#ifndef BOMBERMAN_TEXTURE_H
#define BOMBERMAN_TEXTURE_H

#include "Renderer.hpp"

class Texture {
private:
  std::shared_ptr<SDL_Texture> texture;

public:
  Texture();
  /**
   * @param renderer
   * @param filename File where texture is stored
   */
  Texture(const Renderer &renderer, const std::string &filename);
  /**
   *
   * @param renderer
   * @param filename File where texture is stored
   * @param r Red color to use as key
   * @param g Green color to use as key
   * @param b Blue color to use as key
   */
  Texture(const Renderer &renderer,
          const std::string &filename,
          Uint8 r,
          Uint8 g,
          Uint8 b);

  /**
   * @return Underlying SDL texture
   */
  SDL_Texture *getSDLTexture() const;
};

#endif // BOMBERMAN_TEXTURE_H
