/* -- shapes.h
 *
 * Structs and methods to build vertices and shapes.
 */

#ifndef ELITE_SHAPES_H
#define ELITE_SHAPES_H

typedef struct Point {
  float x, y;
} Point;

typedef struct Line {
  Point a, b;
} Line;

typedef struct Circle {
  float radius;
  Point center;
} Circle;

typedef struct Triangle {
  Point vertices[3];
} Triangle;

#define new_point(x, y) ((Point){(x), (y)})
#define new_line(a, b) ((Line){(a), (b)})

// Primitive coordinates arithmetic
Point point_add(Point a, Point b);
Point point_sub(Point a, Point b);
float point_dot(Point a, Point b);
Point point_cross(Point a, Point b);

// Translations
Point rotate_point(Point p, Point pivot, float radians);

// Scalars
float line_length(Line l);

// Triangle functions
Point triangle_centroid(Triangle t);
Point triangle_orthocenter(Triangle t);
Point triangle_circumcenter(Triangle t);

#endif /* ELITE_SHAPES_H */
