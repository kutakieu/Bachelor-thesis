#pragma once



	void defineViewMatrix(double phi, double theta);
	void display(void);

	void initGL(void);

	void display(void);

	void mouse_motion(int x, int y);
	void mouse_button(int button, int state, int x, int y);
	double dot(double vec0[], double vec1[]);
	void cross(double vec0[], double vec1[], double vec2[]);
	void normVec(double vec[]);
	void resize(int width, int height);