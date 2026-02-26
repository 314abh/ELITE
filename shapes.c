/* -- shapes.c
 *
 * Structs and methods related to shapes.
 */

#include "shapes.h"

#include <math.h>

// Point new_point(float x, float y) { return (Point){x, y}; }
// Line new_line(Point a, Point b) { return (Line){a, b}; }

Point point_add(Point a, Point b) { return new_point(a.x + b.x, a.y + b.y); }
Point point_sub(Point a, Point b) { return new_point(a.x - b.x, a.y - b.y); }
float point_dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }

Point rotate_point(Point p, Point pivot, float radians) {
  float x1 = p.x, y1 = p.y;
  float x2 = pivot.x, y2 = pivot.y;
  float delta_x = x1 - x2, delta_y = y1 - y2;

  float s = sinf(radians);
  float c = cosf(radians);

  return new_point(x2 + delta_x * c - delta_y * s,
                   y2 + delta_y * c + delta_x * s);
}

Point mid_point(Point a, Point b) {
  return new_point((a.x + b.x) / 2, (a.y + b.y) / 2);
}

float line_length(Line l) {
  float delta_x = l.a.x - l.b.x;
  float delta_y = l.a.y - l.b.y;

  float m2 = powf(delta_x, 2.0f) + powf(delta_y, 2.0f);
  return sqrtf(m2);
}
