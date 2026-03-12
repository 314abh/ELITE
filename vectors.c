#include "vectors.h"
#include <math.h>

// vec3
Vec3 vec3_new(const float x, const float y, const float z) {
  return (Vec3){x, y, z};
}

Vec3 vec3_add(Vec3 a, Vec3 b) {
  return vec3_new(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3 vec3_sub(Vec3 a, Vec3 b) {
  return vec3_new(a.x - b.x, a.y - b.y, a.z - b.z);
}

float vec3_dot(Vec3 a, Vec3 b) {
  return (a.x * b.x + a.y * b.y + a.z * b.z);
}

Vec3 vec3_cross(Vec3 a, Vec3 b) {
  const float x = a.y * b.z - a.z * b.y;
  const float y = a.z * b.x - a.x * b.z;
  const float z = a.x * b.y - a.y * b.x;
  return vec3_new(x, y, z);
}

float vec3_len(Vec3 v) {
  return sqrtf(vec3_len_sq(v));
}

float vec3_len_sq(Vec3 v) {
  return (v.x * v.x + v.y * v.y + v.z * v.z);
}

Vec3 vec3_normalized(Vec3 v) {
  return vec3_new(v.x / v.z, v.y / v.z, v.z / v.z);
}

// vec4


Vec4 vec4_new(const float x, const float y, const float z, const float w) {
  return (Vec4){x, y, z, w};
}

Vec4 vec4_add(Vec4 a, Vec4 b) {
  return vec4_new(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

Vec4 vec4_sub(Vec4 a, Vec4 b) {
  return vec4_new(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

float vec4_dot(Vec4 a, Vec4 b) {
  return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

float vec4_len(Vec4 v) {
  return sqrtf(vec4_len_sq(v));
}

float vec4_len_sq(Vec4 v) {
  return (v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

Vec4 vec4_normalized(Vec4 v) {
  return vec4_new(v.x / v.w, v.y / v.w, v.z / v.w, v.w / v.w);
}
