#ifndef _UTIL_H
#define _UTIL_H

#include <math.h>
#include <stdint.h>
#include "includes/3dMath.h"

#define RAD_TO_DEG(rad) ((rad) * 180.0f / M_PI)
#define DEG_TO_RAD(deg) ((deg) * M_PI / 180.0f)

typedef struct {
    float x;
    float y;
} vec2;

float squaref(float a);
float distance3d(vec3* a, vec3* b);
float distance2d(vec2* a, vec2* b);

void clampAngle(float* angle);

uint32_t randr(uint32_t max);
float randf(float max);

#define EPSILON 0.0001f
int intersectTriangle(vec3 origin, vec3 direction, vec3 vert0, vec3 vert1, vec3 vert2,
                      float* t, float* u, float* v);

#endif