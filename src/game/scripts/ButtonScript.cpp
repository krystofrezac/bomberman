#include "ButtonScript.hpp"

ButtonScript::ButtonScript(std::function<void()> onClick,
                           const SDL_Point &position,
                           const SDL_Point &size,
                           const Texture &texture,
                           const SDL_Point &cellSize,
                           const SDL_Point &normalState,
                           const SDL_Point &hoverState,
                           const SDL_Point &pressState)
    : onClick(onClick), position(position), size(size), texture(texture),
      cellSize(cellSize), normalState(normalState), hoverState(hoverState),
      pressState(pressState) {}

void ButtonScript::onConstruct() {
  entity->addTransform(Point(position.x, position.y), size)
    .addAnimationPlayer(
      AnimationPlayerC(texture, cellSize)
        .addAnimation(Animation("normal", false).addFrame(normalState, 1))
        .addAnimation(Animation("hover", false).addFrame(hoverState, 1))
        .addAnimation(Animation("press", false).addFrame(pressState, 1))
        .setAnimation("normal")
        .startAnimation());
}

void ButtonScript::onEvent(const SDL_Event &event) {
  AnimationPlayerC &animationPlayerC = entity->getAnimationPlayer();

  if (event.type == SDL_MOUSEMOTION) {
    if (pointInArea({position.x, position.y, size.x, size.y},
                    {event.motion.x, event.motion.y})) {
      if (state == NORMAL) {
        state = HOVER;
        animationPlayerC.setAnimation("hover").startAnimation();
      }
    } else if (state == HOVER) {
      state = NORMAL;
      animationPlayerC.setAnimation("normal").startAnimation();
    }
  }
  if (event.type == SDL_MOUSEBUTTONDOWN && state == HOVER &&
      pointInArea({position.x, position.y, size.x, size.y},
                  {event.motion.x, event.motion.y})) {
    state = PRESS;
    animationPlayerC.setAnimation("press").startAnimation();
  }
  if (event.type == SDL_MOUSEBUTTONUP && state == PRESS) {
    if (pointInArea({position.x, position.y, size.x, size.y},
                    {event.motion.x, event.motion.y}))
      onClick();
    else {
      state = HOVER;
      animationPlayerC.setAnimation("normal").startAnimation();
    }
  }
}

bool ButtonScript::pointInArea(SDL_Rect area, SDL_Point point) {
  return point.x > area.x && point.x < area.x + area.w && point.y > area.y &&
         point.y < area.y + area.h;
}