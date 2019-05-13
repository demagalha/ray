#ifndef HITABLE_H
#define HITABLE_H
#include <stdlib.h>
#include "ray.h"

typedef struct hit_record {
	float t;
	vec3 p;
	vec3 normal;
}hit_record;


typedef struct sphere {
	vec3 center;
	float radius;
}sphere;

int sphere_hit(sphere *s, const RAY *r, float t_min, float t_max, hit_record *hit);

int world_hit(sphere *spheres, int nums, const RAY *r, float t_min, float t_max, hit_record *hit);

vec3 random_in_unit_sphere();

#endif /*HITABLE_H*/