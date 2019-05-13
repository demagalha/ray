#include "vec3.h"
#include "ray.h"

vec3 point_at_parameter(const RAY *r, float t) {
	vec3 v = vec3_add(r->A, vec3_multiply_num(r->B, t));
	return v;
}
