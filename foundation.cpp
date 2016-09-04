#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include	<iostream>
#include 	<stdio.h>
#include 	<stdlib.h>

#include 	<fstream>
#include	<cmath>
#include	<cstdlib>
#include	"foundation.h"

#define PI 3.141592653589793
#define X 0
#define Y 1
#define Z 2

using namespace std;
unsigned int num_points = 8;
	unsigned int window_width;
	unsigned int window_height;
	double center[3] = {0.0, 0.0, 0.0};
	double up[3];

	double phi = 30.0;
	double theta = 30.0;

	int mouse_old_x, mouse_old_y;
	bool motion_p;
	
	double eye[3];
void initGL(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
void mouse_motion(int x, int y)
{
	int dx, dy;
	dx = x - mouse_old_x;
	dy = y - mouse_old_y;
	if (motion_p) {
		phi -= dx * 0.2;
		theta += dy * 0.2;
	}
	mouse_old_x = x;
	mouse_old_y = y;
	glutPostRedisplay();
}

void mouse_button(int button, int state, int x, int y)
{
	if ((state == GLUT_DOWN) && (button == GLUT_LEFT_BUTTON))
		motion_p = true;
	else if (state == GLUT_UP)
		motion_p = false;
	mouse_old_x = x;
	mouse_old_y = y;
}


// ���e�����p�̍s���`�D���f�����E�B���h�E��t�ɕ\������D
// ���e�����p�̍s���`�D���f�����E�B���h�E��t�ɕ\������D
void defineViewMatrix(double phi, double theta)
// double phi, theta; ���ʊp�Ƌp.
{
	unsigned int i, j;
	double c, s, xy_dist;
	double x_axis[3], y_axis[3], z_axis[3], vec[3];
	double left, right, bottom, top, farVal, nearVal, margin;
	double dx, dy, d_aspect, w_aspect, d;

	// ���_�̐ݒ�D
	eye[Z] = sin(theta * PI / 180.0);
	xy_dist = cos(theta * PI / 180.0);
	c = cos(phi * PI / 180.0);
	s = sin(phi * PI / 180.0);
	eye[X] = xy_dist * c;
	eye[Y] = xy_dist * s;
	up[X] = - c * eye[Z];
	up[Y] = - s * eye[Z];
	up[Z] = s * eye[Y] + c * eye[X];
	normVec(up);

	// ���_�����_�Ƃ�����W�n�̒�`�D
	for (i = 0; i < 3; i++)
		z_axis[i] = eye[i] - center[i];
	normVec(z_axis);
	cross(up, z_axis, x_axis);
	normVec(x_axis);
	cross(z_axis, x_axis, y_axis);

	// left, right, bottom, top, nearVal, farVal�̌���D
	left = bottom = farVal = 10000.0;
	right = top = nearVal = -10000.0;
	for (i = 0; i < num_points; i++) {
		for (j = 0; j < 3; j++)
			vec[j] = point[i][j] - eye[j];		
		if (dot(x_axis, vec) < left)
			left = dot(x_axis, vec);
		if (dot(x_axis, vec) > right)
			right = dot(x_axis, vec);
		if (dot(y_axis, vec) < bottom)
			bottom = dot(y_axis, vec);
		if (dot(y_axis, vec) > top)
			top = dot(y_axis, vec);
		if (dot(z_axis, vec) < farVal)
			farVal = dot(z_axis, vec);
		if (dot(z_axis, vec) > nearVal)
			nearVal = dot(z_axis, vec);
	}

	// �}�`�̎��͂�5%�قǗ]�T��^����D
	margin = (right - left) * 0.05;
	left -= margin;
	right += margin;
	margin = (top - bottom) * 0.05;
	bottom -= margin;
	top += margin;
	margin = (nearVal - farVal) * 0.05;
	farVal -= margin;
	nearVal += margin;

	// �\���͈͂̃A�X�y�N�g��ƃE�B���h�E�̃A�X�y�N�g��̔�r�D
	dx = right - left;
	dy = top - bottom;
	d_aspect = dy / dx;
	w_aspect = (double)window_height / (double)window_width;

	// �E�B���h�E���\���͈͂����c���D�\���͈͂��c�ɍL����D
	if (w_aspect > d_aspect) {
		d = (dy * (w_aspect / d_aspect - 1.0)) * 0.5;
		bottom -= d;
		top += d;

		// �E�B���h�E���\���͈͂��������D�\���͈͂����ɍL����D
	} else {
		d = (dx * (d_aspect / w_aspect - 1.0)) * 0.5;
		left -= d;
		right += d;
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left, right, bottom, top, - nearVal, - farVal);
	glViewport(0, 0, window_width, window_height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[X], eye[Y], eye[Z], center[X], center[Y], center[Z], up[X], up[Y], up[Z]); 
}

void display(void)
{	

	// �����e�̒�`�D
	defineViewMatrix(phi, theta);

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3dv(point[0]);
	glVertex3dv(point[1]);

	glVertex3dv(point[1]);
	glVertex3dv(point[2]);

	glVertex3dv(point[2]);
	glVertex3dv(point[3]);
	
	glVertex3dv(point[3]);
	glVertex3dv(point[0]);

	glVertex3dv(point[4]);
	glVertex3dv(point[5]);

	glVertex3dv(point[5]);
	glVertex3dv(point[6]);

	glVertex3dv(point[6]);
	glVertex3dv(point[7]);
	
	glVertex3dv(point[7]);
	glVertex3dv(point[4]);

	glVertex3dv(point[0]);
	glVertex3dv(point[4]);

	glVertex3dv(point[1]);
	glVertex3dv(point[5]);

	glVertex3dv(point[2]);
	glVertex3dv(point[6]);
	
	glVertex3dv(point[3]);
	glVertex3dv(point[7]);

	glEnd();
	glFlush();
}

// 2�{�̃x�N�g��vec0��vec1�̓��ρD
double dot(double vec0[], double vec1[])
// double vec0[];
// double vec1[];
{
	return(vec0[X] * vec1[X] + vec0[Y] * vec1[Y] + vec0[Z] * vec1[Z]);
}

// 2�{�̃x�N�g��vec0��vec1�̊O�ρD
void cross(double vec0[], double vec1[], double vec2[])
// double vec0[];
// double vec1[];
// double vec2[]; vec0�~vec1.
{
	vec2[X] = vec0[Y] * vec1[Z] - vec0[Z] * vec1[Y];
	vec2[Y] = vec0[Z] * vec1[X] - vec0[X] * vec1[Z];
	vec2[Z] = vec0[X] * vec1[Y] - vec0[Y] * vec1[X];
}

// �x�N�g���̐��K���D
void normVec(double vec[])
// double vec[]; ���ӁI���̃x�N�g���͔j��I�ɕύX�����D
{
	double norm;
	norm = sqrt(vec[X] * vec[X] + vec[Y] * vec[Y] + vec[Z] * vec[Z]);
	vec[X] /= norm;
	vec[Y] /= norm;
	vec[Z] /= norm;
}


void resize(int width, int height)
{

	// �E�B���h�E�T�C�Y�̎擾�D
	window_width = width;
	window_height = height;
}