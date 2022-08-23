#include "SpriteProcessor.hpp"

#include "../components/AnimationPlayerC.hpp"
#include "../components/SpriteC.hpp"
#include "../components/TransformC.hpp"

void SpriteProcessor::process(entt::registry &registry,
                              const Renderer &renderer,
                              Uint32 delta) {
  //  region Sprite
  auto spriteView = registry.view<SpriteC, TransformC>();
  for (auto entity : spriteView) {
    const SpriteC &spriteC = registry.get<SpriteC>(entity);
    const TransformC &transformC = registry.get<TransformC>(entity);

    SDL_Texture *texture = spriteC.getSDLTexture();
    const SDL_Rect &crop = spriteC.getCrop();
    const Point &position = transformC.getPosition();
    const SDL_Point &size = transformC.getSize();

    SDL_Rect dest = {(int)position.x, (int)position.y, size.x, size.y};
    SDL_RenderCopy(renderer.getSDLRenderer(), texture, &crop, &dest);
  }
  // endregion

  // sort so objects that are down on scene are rendered on top
  registry.sort<AnimationPlayerC>(
    [&registry](const entt::entity x, const entt::entity y) {
      if (!registry.all_of<TransformC>(x) || !registry.all_of<TransformC>(y))
        return false;

      const TransformC &xTransform = registry.get<TransformC>(x);
      const TransformC &yTransform = registry.get<TransformC>(y);

      if (xTransform.getZIndex() != yTransform.getZIndex())
        return xTransform.getZIndex() < yTransform.getZIndex();

      return xTransform.getPosition().y < yTransform.getPosition().y;
    });

  // region AnimationPlayer
  auto animationPlayerView = registry.view<AnimationPlayerC, TransformC>();
  for (auto entity : animationPlayerView) {
    AnimationPlayerC &animationPlayerC = registry.get<AnimationPlayerC>(entity);
    const TransformC &transformC = registry.get<TransformC>(entity);

    animationPlayerC.tick(delta);

    SDL_Texture *texture = animationPlayerC.getSDLTexture();
    const SDL_Rect &crop = animationPlayerC.getCrop();
    const Point &position = transformC.getPosition();
    const SDL_Point &size = transformC.getSize();
    double angle = transformC.getAngle();

    SDL_Rect dest = {(int)position.x, (int)position.y, size.x, size.y};
    SDL_RenderCopyEx(renderer.getSDLRenderer(),
                     texture,
                     &crop,
                     &dest,
                     angle,
                     nullptr,
                     SDL_FLIP_NONE);
  }
  // endregion
}