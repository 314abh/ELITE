/* -- shapes.c
 *
 * Structs and methods related to shapes.
 */

#include "shapes.h"

#include <math.h>

// Vec2 new_point(float x, float y) { return (Vec2){x, y}; }
// Line new_line(Vec2 a, Vec2 b) { return (Line){a, b}; }

Vec2 point_add(Vec2 a, Vec2 b) { return point_new(a.x + b.x, a.y + b.y); }
Vec2 point_sub(Vec2 a, Vec2 b) { return point_new(a.x - b.x, a.y - b.y); }
float point_dot(Vec2 a, Vec2 b) { return a.x * b.x + a.y * b.y; }

Vec2 rotate_point(Vec2 p, Vec2 pivot, float radians) {
  float x1 = p.x, y1 = p.y;
  float x2 = pivot.x, y2 = pivot.y;
  float delta_x = x1 - x2, delta_y = y1 - y2;

  float s = sinf(radians);
  float c = cosf(radians);

  return point_new(x2 + delta_x * c - delta_y * s,
                   y2 + delta_y * c + delta_x * s);
}

Vec2* rotate_points(Vec2* points, size_t points_count, Vec2 pivot, float radians) {
  for (size_t i = 0; i < points_count; ++i) {
    points[i] = rotate_point(points[i], pivot, radians);
  }

  return points;
}

Vec2 mid_point(Vec2 a, Vec2 b) {
  return point_new((a.x + b.x) / 2, (a.y + b.y) / 2);
}

float line_length(Line l) {
  float delta_x = l.a.x - l.b.x;
  float delta_y = l.a.y - l.b.y;

  float m2 = powf(delta_x, 2.0f) + powf(delta_y, 2.0f);
  return sqrtf(m2);
}
