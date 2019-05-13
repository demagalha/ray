#ifndef RAY_H
#define RAY_H
#include "vec3.h"

typedef struct ray {
	vec3 A;
	vec3 B;
}RAY;

vec3 point_at_parameter(const RAY *r, float t);

#endif /*RAY_H*/
