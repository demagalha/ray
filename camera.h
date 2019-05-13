#ifndef CAMERA_H
#define CAMERA_H
#include "ray.h"

typedef struct camera {
	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
}camera;

RAY camera_get_ray(camera *cam, float u, float v);

#endif /*CAMERA_H*/