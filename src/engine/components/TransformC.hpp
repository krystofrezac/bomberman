#ifndef BOMBERMAN_TRANSFORMC_H
#define BOMBERMAN_TRANSFORMC_H

#include <SDL2/SDL.h>

/**
 * Structure to hold 2d float vector
 */
struct Point {
  float x;
  float y;

  Point();
  Point(float x, float y);

  void operator+=(const Point &point);
  bool operator==(const Point &point);
  bool operator!=(const Point &point);
  Point operator-(const Point &point);

  /**
   * Change dimensions so magnitude of vector is `size`
   * @param size
   * @return
   */
  Point normalize(float size);
};

/**
 * Transform component\n
 * Defines entity position and size in scene
 */
class TransformC {
private:
  Point position;
  SDL_Point size;
  double angle;
  int zIndex;
  Point moveDirection = {0, 0};
  Point speed = {0, 0};

public:
  /**
   * @param position Position
   * @param size Size
   * @param angle Rotation angle in degrees
   * @param zIndex Z index
   */
  TransformC(const Point &position,
             const SDL_Point &size,
             double angle = 0,
             int zIndex = 0);

  /**
   * Update position based on speed and move
   * @param delta Time between frames
   */
  void updatePosition(Uint32 delta);
  /**
   * Move to position
   * @param position
   */
  void move(const Point &position);
  /**
   * Change position relative of current position
   * @param direction Relative change
   */
  void moveRelative(const Point &direction);
  /**
   * Set speed and direction
   * @param speed Speed vector
   */
  void setSpeed(const Point &speed);
  /**
   * Set z index
   * @param zIndex Z index
   */
  void setZIndex(int zIndex);

  /**
   * @return Current position
   */
  Point getPosition() const;
  /**
   * @return Size
   */
  SDL_Point getSize() const;
  /**
   * @return Z index
   */
  int getZIndex() const;
  /**
   * @return Speed
   */
  Point getSpeed() const;
  /**
   * @return Rotation angle
   */
  double getAngle() const;
};

#endif // BOMBERMAN_TRANSFORMC_H
