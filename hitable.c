#include "hitable.h"

int sphere_hit(sphere *s, const RAY *r, float t_min, float t_max, hit_record *hit) {
	vec3 oc = vec3_minus(r->A, s->center);
	float a = vec3_dot(r->B, r->B);
	float b = vec3_dot(oc,r->B);
	float c = vec3_dot(oc, oc) - (s->radius*s->radius);
	float discriminant = b*b - a*c;
	
	if (discriminant > 0) {
		float temp = (-b - sqrtf(b*b-a*c))/a;
		if (temp < t_max && temp > t_min) {
			hit->t = temp;
			hit->p = point_at_parameter(r,hit->t);
			hit->normal = vec3_divide_num(vec3_minus(hit->p,s->center),s->radius);
			return 1;
		}
		temp = (-b + sqrtf(b*b-a*c))/a;
		if (temp < t_max && temp > t_min) {
			hit->t = temp;
			hit->p = point_at_parameter(r,hit->t);
			hit->normal = vec3_divide_num(vec3_minus(hit->p,s->center),s->radius);
			return 1;
		}
	}
	return 0;
}

int world_hit(sphere *spheres, int nums, const RAY *r, float t_min, float t_max, hit_record *hit) {
	hit_record temp;
	int hit_anything = 0;
	double closest_so_far = t_max;
	for (int i = 0; i < nums; i++) {
		if (sphere_hit(&spheres[i], r, t_min, closest_so_far, &temp)) {
			hit_anything = 1;
			closest_so_far = temp.t;
			*hit = temp;
		}
	}
	return hit_anything;
}

vec3 random_in_unit_sphere() {
	vec3 p;
	vec3 aux;
	vec3 aux2 = {1,1,1};
	do {
		aux.p[0] = (float)rand()/(float)(RAND_MAX/1);
		aux.p[1] = (float)rand()/(float)(RAND_MAX/1);
		aux.p[2] = (float)rand()/(float)(RAND_MAX/1);
		p = vec3_minus(vec3_multiply_num(aux,2.0),aux2);
	}while (vec3_sqrt_length(p) >= 1.0);
	return p;
}


