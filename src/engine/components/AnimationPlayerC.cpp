#include "AnimationPlayerC.hpp"

#include <stdexcept>

// region Frame
Frame::Frame(SDL_Point position, unsigned int duration)
    : position(position), duration(duration) {}
// endregion

// region Animation
Animation::Animation(const std::string &name, bool loop)
    : name(name), loop(loop) {}

Animation &Animation::addFrame(const SDL_Point &position,
                               unsigned int duration) {
  frames.push_back(Frame(position, duration));
  return *this;
}
void Animation::nextFrame() {
  if (currentFrame != frames.size() - 1 || loop)
    currentFrame++;

  if (currentFrame >= frames.size())
    currentFrame = 0;
}
void Animation::setFrame(size_t frameIndex) { currentFrame = frameIndex; }

const std::string Animation::getName() const { return name; }
Frame Animation::getCurrentFrame() const { return frames.at(currentFrame); }
std::vector<Frame> Animation::getFrames() const { return frames; }
// endregion

// region AnimationPlayerC
AnimationPlayerC::AnimationPlayerC(const Texture &texture,
                                   const SDL_Point &spriteSheetCellSize)
    : texture(texture), spriteSheetCellSize(spriteSheetCellSize) {}

AnimationPlayerC &AnimationPlayerC::addAnimation(const Animation &animation) {
  animations.insert({animation.getName(), animation});
  return *this;
}
AnimationPlayerC &AnimationPlayerC::setAnimation(const std::string &name) {
  auto found = animations.find(name);
  if (found == animations.end())
    throw std::invalid_argument("Invalid animation name");

  if (found->second.getName() == runningAnimation.getName())
    return *this;

  timeAtFrame = 0;
  runningAnimation = found->second;
  return *this;
}
AnimationPlayerC &AnimationPlayerC::startAnimation() {
  running = true;
  return *this;
}
AnimationPlayerC &AnimationPlayerC::stopAnimation() {
  running = false;
  return *this;
}
void AnimationPlayerC::setFrame(size_t frameIndex) {
  timeAtFrame = 0;
  runningAnimation.setFrame(frameIndex);
}
void AnimationPlayerC::tick(Uint32 delta) {
  if (!running)
    return;

  timeAtFrame += delta;

  while (timeAtFrame > runningAnimation.getCurrentFrame().duration) {
    timeAtFrame -= runningAnimation.getCurrentFrame().duration;
    runningAnimation.nextFrame();
  }
}

SDL_Texture *AnimationPlayerC::getSDLTexture() const {
  return texture.getSDLTexture();
}
SDL_Rect AnimationPlayerC::getCrop() const {
  Frame frame = runningAnimation.getCurrentFrame();
  return {frame.position.x * spriteSheetCellSize.x,
          frame.position.y * spriteSheetCellSize.y,
          spriteSheetCellSize.x,
          spriteSheetCellSize.y};
}
// endregion