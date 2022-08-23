#ifndef BOMBERMAN_ANIMATIONPLAYERC_H
#define BOMBERMAN_ANIMATIONPLAYERC_H

#include "../Texture.hpp"

#include <map>
#include <vector>

/**
 * Sprite position and duration of frame in animation
 */
struct Frame {
  SDL_Point position;
  unsigned int duration;

  /**
   * @param position Position in sprite sheet
   * @param duration Duration until next sprite is rendered
   */
  Frame(SDL_Point position, unsigned int duration);
};

/**
 * Sequence of frames
 */
class Animation {
private:
  std::vector<Frame> frames;
  std::string name;
  bool loop;
  size_t currentFrame = 0;

public:
  Animation() = default;
  /**
   * @param name Name of animation
   * @param loop If animation should repeat when it gets to the last sprite
   */
  Animation(const std::string &name, bool loop);

  /**
   * Add frame
   * @param position Sprite sheet position
   * @param duration Duration until next sprite is rendered
   * @return
   */
  Animation &addFrame(const SDL_Point &position, unsigned int duration);
  /**
   * Switch to next frame in animation
   */
  void nextFrame();
  /**
   * Set frame by frame index
   * @param frameIndex Index of frame in animation
   */
  void setFrame(size_t frameIndex);

  /**
   * @return Name of animation
   */
  const std::string getName() const;
  /**
   * @return Current frame do render
   */
  Frame getCurrentFrame() const;
  std::vector<Frame> getFrames() const;
};

/**
 * Component for automatically switching sprites to create animation\n
 * Contains multiple animations between which you can switch using api
 */
class AnimationPlayerC {
private:
  Texture texture;
  SDL_Point spriteSheetCellSize;
  std::map<const std::string, Animation> animations;
  Animation runningAnimation;
  Uint32 timeAtFrame = 0;
  bool running = false;

public:
  /**
   * @param texture Sprite sheet texture - needs to contain all animation frames
   * @param spriteSheetCellSize Size of one sprite sheet "cell"/frame
   */
  AnimationPlayerC(const Texture &texture,
                   const SDL_Point &spriteSheetCellSize);

  /**
   * Add animation to player so you can use it later
   * @param animation
   * @return Reference to self
   */
  AnimationPlayerC &addAnimation(const Animation &animation);

  /**
   * Set animation that you want to render
   * @param name
   * @return Reference to self
   */
  AnimationPlayerC &setAnimation(const std::string &name);
  /**
   * Start playing animation that was set by `setAnimation`
   * @return Reference to self
   */
  AnimationPlayerC &startAnimation();
  /**
   * Freeze animation on current frame
   * @return Reference to self
   */
  AnimationPlayerC &stopAnimation();
  /**
   * Set frame of animation that was set by `setAnimation`
   * @param frameIndex
   */
  void setFrame(size_t frameIndex);
  /**
   * Inform animation player about time change
   * @param delta Time between frames
   */
  void tick(Uint32 delta);

  /**
   * @return Raw sprite sheet texture
   */
  SDL_Texture *getSDLTexture() const;
  /**
   * @return Crop to get current frame
   */
  SDL_Rect getCrop() const;
};

#endif // BOMBERMAN_ANIMATIONPLAYERC_H
