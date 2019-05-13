#ifndef VEC3_H
#define VEC3_H
#include <math.h>

typedef struct vec3 {
	float p[3];
}vec3;

vec3 vec3_add(vec3 v1, vec3 v2);
vec3 vec3_minus(vec3 v1, vec3 v2);
float vec3_length(vec3 v1);
float vec3_sqrt_length(vec3 v1);
vec3 vec3_divide_num(vec3 v1, float num);
vec3 vec3_unit_vec(vec3 v1);
float vec3_dot(vec3 v1, vec3 v2);
vec3 vec3_cross(vec3 v1, vec3 v2);
vec3 vec3_multiply_num(vec3 v1, float num);

#endif /*VEC3_H*/
