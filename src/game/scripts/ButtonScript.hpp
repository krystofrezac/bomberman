#ifndef BOMBERMAN_BUTTONSCRIPT_H
#define BOMBERMAN_BUTTONSCRIPT_H

#include "../../engine/Texture.hpp"
#include "../../engine/components/ScriptC.hpp"

/**
 * Button entity script
 * Initializes all necessary components
 */
class ButtonScript : public Script {
private:
  std::function<void()> onClick;
  SDL_Point position;
  SDL_Point size;
  Texture texture;
  SDL_Point cellSize;
  SDL_Point normalState;
  SDL_Point hoverState;
  SDL_Point pressState;

  enum State { NORMAL, HOVER, PRESS };
  State state = NORMAL;

  void onConstruct() override;
  void onEvent(const SDL_Event &event) override;

  static bool pointInArea(SDL_Rect area, SDL_Point point);

public:
  /**
   * @param onClick Callback when button is clicked
   * @param position Position in scene
   * @param size Size
   * @param texture Texture with sprites
   * @param cellSize Size of one sprite
   * @param normalState Position of normal state in sprite
   * @param hoverState Position of hover state in sprite
   * @param pressState Position of press state in sprite
   */
  ButtonScript(std::function<void()> onClick, const SDL_Point &position,
               const SDL_Point &size, const Texture &texture,
               const SDL_Point &cellSize, const SDL_Point &normalState,
               const SDL_Point &hoverState, const SDL_Point &pressState);
};

#endif // BOMBERMAN_BUTTONSCRIPT_H
