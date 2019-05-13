#include "material.h"

int lambertian_scatter(material *mat, RAY r_in, struct hit_record *rec, vec3 *attenuation, RAY *scattered) {
  vec3 target = vec3_add(rec->p,vec3_add(rec->normal,random_in_unit_sphere()));
  *scattered = (RAY) {rec->p, vec3_minus(target, rec->p) };
  *attenuation = mat->albedo;
  return 1;
}

vec3 reflect(vec3 v, vec3 n) {
  /* v - 2 * dot(v, n) * n */
  vec3 v_ = vec3_minus(v, vec3_multiply_num(n, 2 * vec3_dot(v, n)));
  return v_;
}

int metal_scatter(material *mat, RAY r_in, struct hit_record *rec, vec3 *attenuation, RAY *scattered) {
  vec3 reflected = reflect(vec3_unit_vec(r_in.B), rec->normal);
  *scattered = (RAY) { rec->p, reflected };
  *attenuation = mat->albedo;
  return vec3_dot(scattered->B, rec->normal) > 0;
}

int refract(vec3 v, vec3 n, float ni_over_nt, vec3 *refracted) {
	vec3 uv = vec3_unit_vec(v);
	float dt = vec3_dot(uv,n);
	float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);
	if (discriminant > 0) {
		*refracted = vec3_minus(vec3_multiply_num(vec3_minus(uv, vec3_multiply_num(n, dt)),ni_over_nt),
          vec3_multiply_num(n, sqrtf(discriminant)));
	return 1;
	}
	else
		return 0;
}

float schlick(float cosine, float ref_idx) {
	float r0 = (1-ref_idx) / (1+ref_idx);
	r0 = r0*r0;
	return r0 + (1-r0)*pow((1 - cosine),5);
}

int dielectric_scatter(material *mat, RAY r_in, hit_record *rec, vec3 *attenuation, RAY *scattered) {
  vec3 outward_normal;
  vec3 reflected = reflect(r_in.B, rec->normal);
  float ni_over_nt;
  *attenuation = (vec3) {1.0, 1.0, 1.0 };
  vec3 refracted;
  float reflect_prob;
  float cosine;

  if (vec3_dot(r_in.B, rec->normal) > 0) {
    outward_normal = vec3_multiply_num(rec->normal, -1);
    ni_over_nt = mat->ref_idx;
    cosine = mat->ref_idx * vec3_dot(r_in.B, rec->normal)/vec3_length(r_in.B);
  } else {
    outward_normal = rec->normal;
    ni_over_nt = 1.0 / mat->ref_idx;
    cosine = - vec3_dot(r_in.B, rec->normal)/vec3_length(r_in.B);
  }
  if (refract(r_in.B, outward_normal, ni_over_nt, &refracted)) {
    reflect_prob = schlick(cosine, mat->ref_idx);
  } else {
    reflect_prob = 1.0;
  }
  if (((float)rand()/(float)(RAND_MAX/1)) < reflect_prob) {
    *scattered = (RAY) { rec->p, reflected };
  } else {
    *scattered = (RAY) { rec->p, refracted };
  }
  return 1;
}

