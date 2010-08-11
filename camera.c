#include <math.h>
#include "camera.h"

float abssum(float a, float b) {
	if (((a >= 0.0) && (a + b < 0)) ||
		((a < 0.0) && (a - b > 0.0))) return 0.0;
	return a >= 0 ? a + b : a - b;
}

void camera_init(t_camera* camera) {
	camera->x = 0.0;
	camera->y = 0.0;
	camera->z = -10.0;
	camera->r = 0.0;
	camera->q = 0.0;
	
	camera->vx = 0.0;
	camera->vy = 0.0;
	camera->vz = 0.0;
	camera->vr = 0.0;
	camera->vq = 0.0;

	camera->a = -0.000005;
	camera->b = -0.0005;
}

void camera_accel(t_camera* camera) {
	camera->vx = abssum(camera->vx, camera->a);
	camera->vy = abssum(camera->vy, camera->a);
	camera->vz = abssum(camera->vz, camera->a);
	
	camera->vq = abssum(camera->vq, camera->b);
	camera->vr = abssum(camera->vr, camera->b);
}
void camera_inert(t_camera* camera) {
	camera->x += camera->vx;
	camera->y += camera->vy;
	camera->z += camera->vz;
	camera->q += camera->vq;
	camera->r += camera->vr;
	camera_accel(camera);
	camera_check(camera);
}
// forward upward right
void camera_move(t_camera* camera, float f, float u, float r) {
	float sinr = sin(camera->r * M_PI_DIV_180);
	float cosr = cos(camera->r * M_PI_DIV_180);
	
	float cosq = cos(camera->q * M_PI_DIV_180);
	float sinq = sin(camera->q * M_PI_DIV_180);
	

	camera->vx += ( f * sinr * cosq) * 0.001;
	camera->vy += (0) * 0.001;
	camera->vz += ( f * cosr * cosq) * 0.001;
	
}
// horisontal vertical
void camera_rotate(t_camera* camera, float h, float v) {
	camera->vq += h * 0.02;
	camera->vr += v * 0.02;
}
void camera_check(t_camera* camera) {
	if (camera->x < -10.0f) camera->x = -10.0f;
	if (camera->x >  10.0f) camera->x = 10.0f;
	if (camera->z < -10.0f) camera->z = -10.0f;
	if (camera->z >  10.0f) camera->z = 10.0f;
	if (camera->y < -10.0f) camera->y = -10.0f;
	if (camera->y >   1.0f) camera->y = 1.0f;
	if (camera->q <   0.0f) camera->q = 360.0f;
	if (camera->q > 360.0f) camera->q = 0.0f;
	if (camera->r < -180.0f) camera->r =  180.0f;
	if (camera->r >  180.0f) camera->r = -180.0f;

	if (camera->vx < -1.0f) camera->vx = -1.0f;
	if (camera->vx >  1.0f) camera->vx =  1.0f;
	if (camera->vy < -1.0f) camera->vy = -1.0f;
	if (camera->vy >  1.0f) camera->vy =  1.0f;
	if (camera->vz < -1.0f) camera->vz = -1.0f;
	if (camera->vz >  1.0f) camera->vz =  1.0f;
	if (camera->vq < -1.0f) camera->vq = -1.0f;
	if (camera->vq >  1.0f) camera->vq =  1.0f;
	if (camera->vr < -1.0f) camera->vr = -1.0f;
	if (camera->vr >  1.0f) camera->vr =  1.0f;
}
	

