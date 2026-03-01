/* -- shapes.h
 *
 * Structs and methods to build vertices and shapes.
 */

#ifndef ELITE_SHAPES_H
#define ELITE_SHAPES_H

#include <stddef.h>

typedef struct Vec2 {
  float x, y;
} Vec2;

typedef struct Line {
  Vec2 a, b;
} Line;

typedef struct Circle {
  float radius;
  Vec2 center;
} Circle;

typedef struct Triangle {
  Vec2 vertices[3];
} Triangle;

#define point_new(x, y) ((Vec2){(x), (y)})
#define line_new(a, b) ((Line){(a), (b)})

// Primitive coordinates arithmetic
Vec2 point_add(Vec2 a, Vec2 b);
Vec2 point_sub(Vec2 a, Vec2 b);
float point_dot(Vec2 a, Vec2 b);
Vec2 point_cross(Vec2 a, Vec2 b);

// Translations
Vec2 rotate_point(Vec2 p, Vec2 pivot, float radians);
Vec2* rotate_points(Vec2* points, size_t points_count, Vec2 pivot, float radians);

// Scalars
float line_length(Line l);

// Triangle functions
Vec2 triangle_centroid(Triangle t);
Vec2 triangle_orthocenter(Triangle t);
Vec2 triangle_circumcenter(Triangle t);

#endif /* ELITE_SHAPES_H */
