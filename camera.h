#ifndef _CAMERA_H_
#define _CAMERA_H_

#define M_PI_DIV_180 0.017453

float abssum(float a, float b);

typedef struct {
	/* position and heading(direction) */
	float x, y, z, r, q;
	/* velocity */
	float vx, vy, vz, vr, vq;
	/* acceleration (deceleration), velocity decrement */
	float a, b;

} t_camera;

void camera_init(t_camera* camera);
void camera_accel(t_camera* camera);
void camera_inert(t_camera* camera);
void camera_move(t_camera* camera, float f, float u, float r);
void camera_rotate(t_camera* camera, float h, float v);
void camera_check(t_camera* camera);


#endif

