#include <stdlib.h>
#include "camera.h"


void camera_position(camera *cam, vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist) {
	cam->lens_radius = aperture/2;
	float theta = vfov*M_PI/180;
	float half_height = tan(theta/2);
	float half_width = aspect*half_height;
	cam->origin = lookfrom;
	cam->w = vec3_unit_vec(vec3_minus(lookfrom,lookat));
	cam->u = vec3_unit_vec(vec3_cross(vup,cam->w));
	cam->v = vec3_cross(cam->w,cam->u);
	cam->lower_left_corner =vec3_minus(vec3_minus(vec3_minus(cam->origin,
	vec3_multiply_num( cam->u, half_width * focus_dist)),
    vec3_multiply_num( cam->v, half_height * focus_dist)),vec3_multiply_num( cam->w, focus_dist));
	cam->horizontal = vec3_multiply_num(cam->u,2*half_width*focus_dist);
	cam->vertical = vec3_multiply_num(cam->v,2*half_height*focus_dist);
}

vec3 random_in_unit_disk() {
  vec3 p;
  do {
    p = vec3_minus(vec3_multiply_num((vec3) {(float)rand()/(float)(RAND_MAX/1), (float)rand()/(float)(RAND_MAX/1),0}, 2.0),
          (vec3) {1, 1, 0});
  } while (vec3_dot(p, p) >= 1.0);
  return p;
}

RAY camera_get_ray(camera *cam, float s, float t) {
	vec3 rd = vec3_multiply_num(random_in_unit_disk(),cam->lens_radius);
	vec3 offset = vec3_add(vec3_multiply_num(cam->u, rd.p[0]),vec3_multiply_num(cam->v,rd.p[1]));
	RAY r = { vec3_add(cam->origin, offset), vec3_minus(vec3_minus(vec3_add(cam->lower_left_corner,
                            vec3_add(vec3_multiply_num(cam->horizontal, s),
                              vec3_multiply_num(cam->vertical, t))),
                          cam->origin),offset)};
	return r;
}