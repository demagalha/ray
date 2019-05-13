#ifndef MATERIAL_H
#define MATERIAL_H
#include <stdlib.h>
#include "ray.h"
#include "hitable.h"

typedef struct material {
	vec3 albedo;
	float ref_idx;
	int (*scatter) (struct material *mat, RAY r, struct hit_record *rec, vec3 *attenuation, RAY *scattered);
}material;

int lambertian_scatter(material *mat, RAY r_in, struct hit_record *rec, vec3 *attenuation, RAY *scattered);
vec3 reflect(vec3 v, vec3 n);
int metal_scatter(material *mat, RAY r_in, struct hit_record *rec, vec3 *attenuation, RAY *scattered);
int dielectric_scatter(material *mat, RAY r_in, struct hit_record *rec, vec3 *attenuation, RAY *scattered);
int refract(vec3 v, vec3 n, float ni_over_nt, vec3 *refracted);
float schlick(float cosine, float ref_idx);


#endif /*MATERIAL_H*/
