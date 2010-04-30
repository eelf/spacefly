#define M_PI_DIV_180 0.017453

float abssum(float a, float b) {
	if (a >= 0.0 && a + b < 0 ||
		a < 0.0 && a - b > 0.0) return 0.0;
	return a >= 0 ? a + b : a - b;
}

class Camera {
	/* position and heading(direction) */
	public: float camx,camy,camz,camr,camq;
	/* velocity */
	float cavx,cavy,cavz,cavr,cavq;
	/* acceleration (deceleration), velocity decrement */
	float a, b;
	/* instant rotation switch (90 degree) */
	int c, v;

	Camera() {
		init();
	}
	void init() {
		camx = 0.0;
		camy = 0.0;
		camz = 0.0;
		camq = 0.0;
		camr = 0.0;
		cavx = 0.0;
		cavy = 0.0;
		cavz = 0.0;
		cavq = 0.0;
		cavr = 0.0;
		a = -0.0004;
		b = -0.005;
		v = 0;
		c = 0;
	}
	void switchview(int cc) {
		if (cc)	{
		v++;
		switch(v & 0x3) {
		case 0: camq =   0.0; break;
		case 1: camq =  90.0; break;
		case 2: camq = 180.0; break;
		case 3: camq = 270.0; break;
		}
		} else {
		c++;
		switch (c & 0x3) {
		case 0: camr =   0.0; break;
		case 1: camr =  90.0; break;
		case 2: camr = 180.0; break;
		case 3: camr = 270.0; break;
		}
		}
	}
	void accel() {
		cavx = abssum(cavx, a);
		cavy = abssum(cavy, a);
		cavz = abssum(cavz, a);
		cavq = abssum(cavq, b);
		cavr = abssum(cavr, b);
	}
	void inert() {
		camx += cavx;
		camy += cavy;
		camz += cavz;
		camq += cavq;
		camr += cavr;
		accel();
		checkCam();
	}
	// forward upward right
	void move(float f, float u, float r) {
		float sinr = float(sin(camr * M_PI_DIV_180));
		float cosr = float(cos(camr * M_PI_DIV_180));
		
		float cosq = float(cos(camq * M_PI_DIV_180));
		float sinq = float(sin(camq * M_PI_DIV_180));
		
		cavy += (-f * sinr            + u * cosr) * 0.01;
		cavx += ( f * sinq + r * cosq + u * sinr * sinq) * 0.01;
		cavz += (-f * cosq + r * sinq - u * sinr * cosq) * 0.01;
		
	}
	// horisontal vertical
	void rotate(float h, float v) {
		cavq += h * 0.2;
		cavr += v * 0.2;
	}
	void checkCam() {
		if (this->camx < -10.0f) this->camx = -10.0f;
		if (this->camx > 10.0f) this->camx = 10.0f;
		if (this->camz < -10.0f) this->camz = -10.0f;
		if (this->camz > 10.0f) this->camz = 10.0f;
		if (this->camy < -10.0f) this->camy = -10.0f;
		if (this->camy > 1.0f) this->camy = 1.0f;
		if (this->camq < 0.0f) this->camq = 360.0f;
		if (this->camq > 360.0f) this->camq = 0.0f;
		if (this->camr < 0.0f) this->camr = 360.0f;
		if (this->camr > 360.0f) this->camr = 0.0f;

		if (this->cavx < -1.0f) this->cavx = -1.0f;
		if (this->cavx >  1.0f) this->cavx =  1.0f;
		if (this->cavy < -1.0f) this->cavy = -1.0f;
		if (this->cavy >  1.0f) this->cavy =  1.0f;
		if (this->cavz < -1.0f) this->cavz = -1.0f;
		if (this->cavz >  1.0f) this->cavz =  1.0f;
		if (this->cavq < -1.0f) this->cavq = -1.0f;
		if (this->cavq >  1.0f) this->cavq =  1.0f;
		if (this->cavr < -1.0f) this->cavr = -1.0f;
		if (this->cavr >  1.0f) this->cavr =  1.0f;
	}
};
