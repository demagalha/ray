#include "vec3.h"

vec3 vec3_add(vec3 v1, vec3 v2) {
	vec3 v = {v1.p[0]+v2.p[0], v1.p[1]+v2.p[1], v1.p[2]+v2.p[2]};
	return v;
}

vec3 vec3_minus(vec3 v1, vec3 v2) {
	vec3 v = {v1.p[0]-v2.p[0], v1.p[1]-v2.p[1], v1.p[2]-v2.p[2]};
	return v;
}

float vec3_length(vec3 v1) {
	return sqrtf(v1.p[0]*v1.p[0] + v1.p[1]*v1.p[1] + v1.p[2]*v1.p[2]);
}

float vec3_sqrt_length(vec3 v1) {
	return v1.p[0]*v1.p[0] + v1.p[1]*v1.p[1] + v1.p[2]*v1.p[2];
}

vec3 vec3_divide_num(vec3 v1,float num) {
	vec3 v = {v1.p[0]/num, v1.p[1]/num, v1.p[2]/num};
	return v;
}

vec3 vec3_unit_vec(vec3 v1) {
	vec3 v = vec3_divide_num(v1,vec3_length(v1));
	return v;
}
	
float vec3_dot(vec3 v1, vec3 v2) {
	return v1.p[0]*v2.p[0] + v1.p[1]*v2.p[1] + v1.p[2]*v2.p[2];
}

vec3 vec3_cross(vec3 v1, vec3 v2) {
	vec3 v = {v1.p[1]*v2.p[2] - v1.p[2]*v2.p[1], v1.p[2]*v2.p[0] - v1.p[0]*v2.p[2],
			  v1.p[0]*v2.p[1] - v1.p[1]*v2.p[0]};
	return v;
}

vec3 vec3_multiply_num(vec3 v1, float num) {
	vec3 v = {v1.p[0]*num, v1.p[1]*num, v1.p[2]*num};
	return v;
}


