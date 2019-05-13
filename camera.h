#ifndef CAMERA_H
#define CAMERA_H
#include "ray.h"

typedef struct camera {
	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 u,v,w;
	float lens_radius;
}camera;

void camera_position(camera *cam, vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist);
vec3 random_in_unit_disk();
RAY camera_get_ray(camera *cam, float s, float t);

#endif /*CAMERA_H*/