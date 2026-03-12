#ifndef VECTORS_H
#define VECTORS_H

#include <stddef.h>

typedef float Mat2[4];
typedef struct Vec2 {
  float x, y;
} Vec2;

typedef float Mat3[9];
typedef struct Vec3 {
  float x, y, z;
} Vec3;

typedef float Mat4[16];
typedef struct Vec4 {
  float x, y, z, w;
} Vec4;

// vec3

Vec3 vec3_new(const float x, const float y, const float z);

Vec3 vec3_add(Vec3 a, Vec3 b);
Vec3 vec3_sub(Vec3 a, Vec3 b);
float vec3_dot(Vec3 a, Vec3 b);
Vec3 vec3_cross(Vec3 a, Vec3 b);

float vec3_len(Vec3 v);
float vec3_len_sq(Vec3 v);
Vec3 vec3_normalized(Vec3 v);

// vec4

Vec4 vec4_new(const float x, const float y, const float z, const float w);

Vec4 vec4_add(Vec4 a, Vec4 b);
Vec4 vec4_sub(Vec4 a, Vec4 b);
float vec4_dot(Vec4 a, Vec4 b);
// Vec4 vec4_cross(Vec4 a, Vec4 b);

float vec4_len(Vec4 v);
float vec4_len_sq(Vec4 v);
Vec4 vec4_normalized(Vec4 v);

// mat3

void mat3_cpy(Mat3 c, Mat3 a);
void mat3_identity(Mat3 m);

float mat3_det(Mat3 m);
float mat3_trace(Mat3 m);
void mat3_inv(Mat3 c, Mat3 a);
void mat3_transpose(Mat3 c, Mat3 a);

void mat3_add(Mat3 c, Mat3 a, Mat3 b);
void mat3_sub(Mat3 c, Mat3 a, Mat3 b);
void mat3_dot(Mat3 c, Mat3 a, Mat3 b);

void mat3_translate(Mat3 m, Vec2 t);
void mat3_rotate(Mat3 m, Vec2 axis, float angle);
void mat3_scale(Mat3 m, Vec2 s);

// mat4

void mat4_cpy(Mat4 c, Mat4 a);
void mat4_identity(Mat4 m);

float mat4_det(Mat4 m);
float mat4_trace(Mat4 m);
void mat4_inv(Mat4 c, Mat4 a);
void mat4_transpose(Mat4 c, Mat4 a);

void mat4_add(Mat4 c, Mat4 a, Mat4 b);
void mat4_sub(Mat4 c, Mat4 a, Mat4 b);
void mat4_dot(Mat4 c, Mat4 a, Mat4 b);

void mat4_translate(Mat4 m, Vec3 t);
void mat4_rotate(Mat4 m, Vec3 axis, float angle);
void mat4_scale(Mat4 m, Vec3 s);

#endif // VECTORS_H
