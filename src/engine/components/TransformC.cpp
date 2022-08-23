#include "TransformC.hpp"

// region Point
Point::Point() : x(0), y(0) {}
Point::Point(float x, float y) : x(x), y(y) {}

void Point::operator+=(const Point &point) {
  x += point.x;
  y += point.y;
}
bool Point::operator==(const Point &point) {
  return x == point.x && y == point.y;
}
bool Point::operator!=(const Point &point) { return !(*this == point); }
Point Point::operator-(const Point &point) {
  return Point(x - point.x, y - point.y);
}

Point Point::normalize(float size) {
  float magnitude = sqrt(x * x + y * y);
  return Point((x / magnitude) * size, (y / magnitude) * size);
}
// endregion

// region TransformC
TransformC::TransformC(const Point &position,
                       const SDL_Point &size,
                       double angle,
                       int zIndex)
    : position(position), size(size), angle(angle), zIndex(zIndex) {}

void TransformC::updatePosition(Uint32 delta) {
  float multiplier = delta;

  position.x += moveDirection.x * multiplier;
  position.y += moveDirection.y * multiplier;
  moveDirection = {0, 0};

  position.x += speed.x * multiplier;
  position.y += speed.y * multiplier;
}
void TransformC::move(const Point &position) {
  this->position = position;
  moveDirection = {0, 0};
}
void TransformC::moveRelative(const Point &direction) {
  moveDirection += direction;
}
void TransformC::setSpeed(const Point &speed) { this->speed = speed; }
void TransformC::setZIndex(int zIndex) { this->zIndex = zIndex; }

Point TransformC::getPosition() const { return position; }
SDL_Point TransformC::getSize() const { return size; }
int TransformC::getZIndex() const { return zIndex; }
Point TransformC::getSpeed() const { return speed; }
double TransformC::getAngle() const { return angle; }
// endregion