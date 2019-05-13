#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include "ray.h"
#include "hitable.h"
#include "camera.h"


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
