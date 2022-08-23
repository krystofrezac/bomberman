#include "SpriteC.hpp"

// region public methods
SpriteC::SpriteC(const Texture &texture) : texture(texture) {
  SDL_Point size = calculateTextureSize();
  crop = {0, 0, size.x, size.y};
}
SpriteC::SpriteC(const Texture &texture, const SDL_Rect &crop)
    : texture(texture), crop(crop) {}
SpriteC::SpriteC(const Texture &texture,
                 const SDL_Point &spriteSheetCellSize,
                 const SDL_Point &spriteSheetPosition)
    : texture(texture) {
  crop = {spriteSheetPosition.x * spriteSheetCellSize.x,
          spriteSheetPosition.y * spriteSheetCellSize.y,
          spriteSheetCellSize.x,
          spriteSheetCellSize.y};
}

SDL_Texture *SpriteC::getSDLTexture() const { return texture.getSDLTexture(); }
SDL_Rect SpriteC::getCrop() const { return crop; }
// endregion

// region private methods
SDL_Point SpriteC::calculateTextureSize() const {
  SDL_Point size;
  SDL_QueryTexture(texture.getSDLTexture(), nullptr, nullptr, &size.x, &size.y);
  return size;
}
// endregion