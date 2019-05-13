#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include "ray.h"
#include "hitable.h"
#include "camera.h"
#include "material.h"

vec3 color(const RAY *r, sphere *spheres, int nums, int depth) {
	hit_record rec;
	if(world_hit(spheres, nums, r, 0.001, FLT_MAX, &rec)) {
		RAY scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat->scatter(rec.mat, *r, &rec, &attenuation, &scattered)) {
			return vec3_multiply_vec(attenuation, color(&scattered, spheres, nums, depth+1));
		}
		else {
			return (vec3) {0,0,0};
		}
		
	}
	else {
		vec3 unit_direction = vec3_unit_vec(r->B);
		float t = 0.5*(unit_direction.p[1] + 1.0);
		vec3 v1 = {1.0, 1.0, 1.0}; 
		vec3 v2 = {0.5, 0.7, 1.0};
		return vec3_add( vec3_multiply_num(v1, 1.0-t), vec3_multiply_num(v2, t));
	}
}
	
int main()
{
	FILE *out;
	out = fopen("img.ppm","w");
	int nx = 500;
	int ny = 500;
	int ns = 100;
	srand((unsigned int)time(NULL));
	fprintf(out,"P3\n%d %d\n255\n",nx,ny);
	
	
	struct material material_1 = { .albedo.p[0] = 0.1, .albedo.p[1] = 0.2, .albedo.p[2] = 0.5, .scatter = lambertian_scatter };
	struct material material_2 = { .albedo.p[0] = 0.8, .albedo.p[1] = 0.8, .albedo.p[2] = 0.0, .scatter = lambertian_scatter };
	struct material material_3 = { .albedo.p[0] = 0.8, .albedo.p[1] = 0.6, .albedo.p[2] = 0.2, .scatter = metal_scatter };
	struct material material_4 = { .ref_idx = 1.5, .scatter = dielectric_scatter };
	
	
	
	sphere world[] = {
    { .center.p[0] = 0, .center.p[1] = 0, .center.p[2] = -1, .radius = 0.5, .mat = & material_1},
    { .center.p[0] = 0, .center.p[1] = -100.5, .center.p[2] = -1, .radius = 100, .mat = & material_2},
	{.center.p[0] = 1, .center.p[1] = 0, .center.p[2] = -1, .radius = 0.5, .mat = & material_3},
	{.center.p[0] = -1, .center.p[1] = 0, .center.p[2] = -1, .radius = 0.5, .mat = & material_4},
	{.center.p[0] = -1, .center.p[1] = 0, .center.p[2] = -1, .radius = -0.45, .mat = & material_4}
	};
	



	sphere mundo[500];
	struct material material_m1 = { .albedo.p[0] = 0.5, .albedo.p[1] = 0.5, .albedo.p[2] = 0.5, .scatter = lambertian_scatter };
	
	mundo[0] = (sphere){ .center.p[0] = 0, .center.p[1] = -1000, .center.p[2] = 0, .radius = 1000, .mat = & material_m1};
	int i = 1;
	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			float choose_mat = 	(float)rand()/(float)(RAND_MAX/1);
			vec3 center = {a + 0.9*((float)rand()/(float)(RAND_MAX/1)), 0.2, b + 0.9*((float)rand()/(float)(RAND_MAX/1))};
			if ( vec3_length(vec3_minus(center, (vec3) {4,0.2,0})) > 0.9 ) {
				if (choose_mat < 0.8) { //difuse
				struct material r_material = (material){ .albedo.p[0] = ((float)rand()/(float)(RAND_MAX/1)) * ((float)rand()/(float)(RAND_MAX/1)), .albedo.p[1] = ((float)rand()/(float)(RAND_MAX/1)) * ((float)rand()/(float)(RAND_MAX/1)), .albedo.p[2] = ((float)rand()/(float)(RAND_MAX/1)) * ((float)rand()/(float)(RAND_MAX/1)), .scatter = lambertian_scatter};
				mundo[i++] = (sphere) {.center.p[0] = center.p[0], .center.p[1] = center.p[1], .center.p[2] = center.p[2], .radius = 0.2, .mat = & r_material};
				}
				else if (choose_mat < 0.95) { //metal
				struct material r2_material = (material){ .albedo.p[0] = 0.5*(1+((float)rand()/(float)(RAND_MAX/1))), .albedo.p[1] = 0.5*(1+((float)rand()/(float)(RAND_MAX/1))) , .albedo.p[2] = 0.5*(1+((float)rand()/(float)(RAND_MAX/1))), .scatter = metal_scatter};
				mundo[i++] = (sphere) {.center.p[0] = center.p[0], .center.p[1] = center.p[1], .center.p[2] = center.p[2], .radius = 0.2, .mat = & r2_material};
				}
				else { //glass
				struct material die_material = (material){ .ref_idx = 1.5, .scatter = dielectric_scatter };
				mundo[i++] = (sphere) {.center.p[0] = center.p[0], .center.p[1] = center.p[1], .center.p[2] = center.p[2], .radius = 0.2, .mat = & die_material};
				}
			}
		}
	}
	
	struct material dieletric_material = { .ref_idx = 1.5, .scatter = dielectric_scatter };
	struct material lamb_material = { .albedo.p[0] = 0.4, .albedo.p[1] = 0.2, .albedo.p[2] = 0.1, .scatter = lambertian_scatter};
	struct material mat_material = { .albedo.p[0] = 0.7, .albedo.p[1] = 0.6, .albedo.p[2] = 0.5, .scatter = metal_scatter};
	
	mundo[i++] = (sphere) {.center.p[0] = 0, .center.p[1] =1, .center.p[2] = 0, .radius = 1.0, .mat = & dieletric_material};
	mundo[i++] = (sphere) {.center.p[0] = -4, .center.p[1] =1, .center.p[2] = 0, .radius = 1.0, .mat = & lamb_material};
	mundo[i++] = (sphere) {.center.p[0] = 4, .center.p[1] =1, .center.p[2] = 0, .radius = 1.0, .mat = & mat_material};
	int numm = i;


camera cam;

vec3 lookfrom = {12,2,3}; vec3 lookat = {0,0,0}; vec3 vup = {0,1,0}; float vfov = 20;
float dist_to_focus = 10.0; 
float aperture = 0.1;
camera_position(&cam, lookfrom,lookat,vup, vfov, (float)nx/(float)ny, aperture, dist_to_focus);
	
	for (int j = ny-1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			vec3 col = {0,0,0};
			for(int s = 0; s < ns; s++)
			{
			float u = (float)(i + (float)rand()/(float)(RAND_MAX/1)) / (float)(nx);
			float v = (float)(j + (float)rand()/(float)(RAND_MAX/1)) / (float)(ny);
			RAY r = camera_get_ray(&cam, u, v);
			col = vec3_add(col,color(&r,mundo, numm,0));
			}
			col = vec3_divide_num(col, (float)ns);
			col.p[0] = sqrtf(col.p[0]); col.p[1] = sqrtf(col.p[1]); col.p[2] = sqrtf(col.p[2]);
			int ir = (int)(255.99*col.p[0]);
			int ig = (int)(255.99*col.p[1]);
			int ib = (int)(255.99*col.p[2]);
			fprintf(out,"%d %d %d\n",ir,ig,ib);
		}
	}
	fclose(out);
	
	
	
	return 0;
	
}
