#ifndef BOMBERMAN_SPRITE_H
#define BOMBERMAN_SPRITE_H

#include "../Texture.hpp"

/**
 * Sprite component\n
 * Render one static sprite
 */
class SpriteC {
private:
  Texture texture;
  SDL_Rect crop;
  SDL_Rect spriteSheet;

  SDL_Point calculateTextureSize() const;

public:
  /**
   * Render whole texture
   * @param texture Texture to render
   */
  SpriteC(const Texture &texture);
  /**
   * Render cropped texture
   * @param texture Texture to render
   * @param crop Crop to use
   */
  SpriteC(const Texture &texture, const SDL_Rect &crop);
  /**
   * Render sprite from sprite sheet
   * @param texture Texture of sprite sheet
   * @param spriteSheetCellSize Size of one sprite on sprite sheet
   * @param spriteSheetPosition Position of sprite on sprite sheet
   */
  SpriteC(const Texture &texture, const SDL_Point &spriteSheetCellSize,
          const SDL_Point &spriteSheetPosition);

  /**
   * @return Raw SDL texture
   */
  SDL_Texture *getSDLTexture() const;
  /**
   *
   * @return Crop to use on sprite
   */
  SDL_Rect getCrop() const;
};

#endif // BOMBERMAN_SPRITE_H
