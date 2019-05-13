#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include "ray.h"
#include "hitable.h"
#include "camera.h"



float hit_sphere(const vec3 *center, float radius, const RAY *r) {
	vec3 oc = vec3_minus(r->A, *center);
	float a = vec3_dot(r->B, r->B);
	float b = 2.0 * vec3_dot(oc,r->B);
	float c = vec3_dot(oc, oc) - (radius*radius);
	float discriminant = b*b - 4*a*c;
	if (discriminant < 0) {
		return -1.0;
	}
	else {
		return (-b - sqrt(discriminant) ) / (2.0*a);
	}
}



/*vec3 color(const RAY *r) {
	vec3 v = {0,0,-1};
	vec3 vc = {1,0,0}; //color red
	float t = hit_sphere(&v, 0.5, r);
	if (t > 0.0) {
		vec3 N = vec3_unit_vec(vec3_minus(point_at_parameter(r, t),v));
		vec3 vv = {0.5*(N.p[0]+1), 0.5*(N.p[1]+1), 0.5*(N.p[2]+1)};
		return vv;
	}
		
	vec3 unit_direction = vec3_unit_vec(r->B);
	t = 0.5*(unit_direction.p[1] + 1.0);
	vec3 v1 = {1.0, 1.0, 1.0}; 
	vec3 v2 = {0.5, 0.7, 1.0};
	return vec3_add( vec3_multiply_num(v1, 1.0-t), vec3_multiply_num(v2, t));
}
*/

//world_hit(sphere *s, int nums, const RAY *r, float t_min, float t_max, hit_record *hit);

/*
vec3 color(const RAY *r, sphere *spheres, int nums) {
	hit_record rec;
	if(world_hit(spheres, nums, r, 0.0, FLT_MAX, &rec)) {
		//vec3 N = vec3_unit_vec(vec3_minus(point_at_parameter(r, t),v));
		//vec3 vv = {0.5*(N.p[0]+1), 0.5*(N.p[1]+1), 0.5*(N.p[2]+1)};
		vec3 v = {0.5*(rec.normal.p[0]+1), 0.5*(rec.normal.p[1]+1), 0.5*(rec.normal.p[2]+1)};
		return v;
	}
	else {
		vec3 unit_direction = vec3_unit_vec(r->B);
		float t = 0.5*(unit_direction.p[1] + 1.0);
		vec3 v1 = {1.0, 1.0, 1.0}; 
		vec3 v2 = {0.5, 0.7, 1.0};
		return vec3_add( vec3_multiply_num(v1, 1.0-t), vec3_multiply_num(v2, t));
	}
}
*/		

vec3 color(const RAY *r, sphere *spheres, int nums) {
	hit_record rec;
	if(world_hit(spheres, nums, r, 0.001, FLT_MAX, &rec)) {
		vec3 target = vec3_add(rec.p,vec3_add(rec.normal,random_in_unit_sphere()));
		
		//color(&r, world, sizeof(world) / sizeof(struct sphere))
		RAY rr = {rec.p,vec3_minus(target,rec.p)};
		return vec3_multiply_num(color(&rr,spheres,nums),0.5);
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
	int nx = 200;
	int ny = 100;
	int ns = 100;
	srand((unsigned int)time(NULL));
	fprintf(out,"P3\n%d %d\n255\n",nx,ny);
	vec3 lower_left_corner = {-2.0, -1.0, -1.0};
	vec3 horizontal = {4.0, 0.0, 0.0};
	vec3 vertical = {0.0, 2.0, 0.0};
	vec3 origin = {0.0, 0.0, 0.0};
	
	sphere world[] = {
    { .center.p[0] = 0, .center.p[1] = 0, .center.p[2] = -1, .radius = 0.5},
    { .center.p[0] = 0, .center.p[1] = -100.5, .center.p[2] = -1, .radius = 100}
	};

camera cam = {origin, lower_left_corner, horizontal, vertical};

	printf("%f %f \n", world[0].center.p[1], world[1].center.p[1]);
	printf("%d",sizeof(world) / sizeof(struct sphere));
	
	for (int j = ny-1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			vec3 col = {0,0,0};
			for(int s = 0; s < ns; s++)
			{
			float u = (float)(i + (float)rand()/(float)(RAND_MAX/1)) / (float)(nx);
			float v = (float)(j + (float)rand()/(float)(RAND_MAX/1)) / (float)(ny);
			//RAY r = {origin, vec3_add(lower_left_corner, vec3_add(vec3_multiply_num(horizontal,u), vec3_multiply_num(vertical,v)))};
			RAY r = camera_get_ray(&cam, u, v);
			col = vec3_add(col,color(&r, world, sizeof(world) / sizeof(struct sphere)));
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
