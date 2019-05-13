#include "camera.h"



RAY camera_get_ray(camera *cam, float u, float v) {
	RAY r = {cam->origin, vec3_add(cam->lower_left_corner,vec3_multiply_num(cam->horizontal,u))};
	RAY r2 = {r.A, vec3_add(r.B,vec3_minus(vec3_multiply_num(cam->vertical,v),cam->origin))};
	return r2;
}
