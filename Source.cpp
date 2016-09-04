#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include	<iostream>
#include 	<stdio.h>
#include 	<stdlib.h>
#include 	<time.h>
#include 	<fstream>
#include	<cmath>
#include	<cstdlib>
#include 	"mt19937ar.h"
#include	"molecule.h"
#include	"Receptor.h"
#include	"Calculation.h"

#define PI 3.141592653589793
#define X 0
#define Y 1
#define Z 2
#define REC_NUM 25

using namespace std;
unsigned int num_points = 8;

int triangle[4][2] = {{0,1}, {1,2}, {2,3}, {3,0}};
double point[8][3]  = {{1.0, 1.0, -1.0}, {-1.0, 1.0, -1.0}, {-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0}, {1.0, 1.0, 1.0}, {-1.0, 1.0, 1.0}, {-1.0, -1.0, 1.0}, {1.0, -1.0, 1.0}};
	
unsigned int window_width;
	unsigned int window_height;
	double center[3] = {0.0, 0.0, 0.0};
	double up[3];

	double phi = 30.0;
	double theta = 30.0;

	int mouse_old_x, mouse_old_y;
	bool motion_p;
	
	double eye[3];

double Time = 0;
double dt = 0.0001;
molecule S1(MOL_NUM);

Receptor R;

calculation C;

time_t t1;
struct tm timeObject;

int num_quads = 6;



void idle(void);
void initGL(void);
void mouse_motion(int x, int y);
void mouse_button(int button, int state, int x, int y);
void mouse_button(int button, int state, int x, int y);
void defineViewMatrix(double phi, double theta);
double dot(double vec0[], double vec1[]);
void cross(double vec0[], double vec1[], double vec2[]);
void normVec(double vec[]);
void resize(int width, int height);




void display_mol(){

	C.signal_cascade(S1,R);
	
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
	//glFlush();

	/////////////////////////！！！！！！！！受容体描画部分！！！！！！！///////////////////////

	for(int i=0; i<REC_NUM; i++){
		//glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_TRIANGLES);
		glColor3d(S1.rec_color[i][0], R.rec_color[i][1], R.rec_color[i][2]);
			for(int j=0; j<4; j++){
				
				glVertex3dv(R.key_ver[i]);
				glVertex3dv(R.ver[i][triangle[j][0]]);
				glVertex3dv(R.ver[i][triangle[j][1]]);

			}

		glEnd();
		//glFlush();


		//glClear(GL_COLOR_BUFFER_BIT);			
		glBegin(GL_QUADS);
				glColor3d(1,1,1);
				glVertex3dv(R.ver[i][0]);
				glVertex3dv(R.ver[i][1]);
				glVertex3dv(R.ver[i][2]);
				glVertex3dv(R.ver[i][3]);
		glEnd();
		//glFlush();
	}

	/////////////////////////！！！！！！！！分子描画部分！！！！！！！///////////////////////
	//glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	
		for(int i=1; i<S1.mol_num; i++){
			glColor3d(S1.color[i][0],S1.color[i][1],S1.color[i][2]);
			glVertex3dv(S1.points[i]);

		}
	
	glEnd();
	glFlush();

	S1.cal_location(R);
	R.rec_move();

	Time += dt;

	if(Time > 500){

	for(int i=0;i<STEP;i++){
		C.integral_x[i] *= dt;
		C.average_integral_x[i] += C.integral_x[i];

		//sigma_integral_x[i] += (integral_x[i]*integral_x[i]);
		C.average_sigma_x[i] += (C.integral_x[i]*C.integral_x[i]);
	}
	
	ofstream fout;

	fout.open("result.csv",ios::out|ios::app);

	fout << "integral_x";

	for(int i=0;i<STEP;i++){
		C.average_integral_x[i] /= T_MAX;

		fout << "," << C.average_integral_x[i];
	}

	fout << ",\n" << "average_sigma_x";
	for(int i=0;i<STEP;i++){
		C.average_sigma_x[i] = sqrt(C.average_sigma_x[i] / T_MAX - C.average_integral_x[i]*C.average_integral_x[i]);

		fout << "," << C.average_sigma_x[i];
	}

	fout << ",\n " << "SN";
	for(int i=0;i<STEP;i++){
		fout << "," << C.average_integral_x[i] / C.average_sigma_x[i];
	}

	fout << ",\n " << "Noise";
	for(int i=0;i<STEP;i++){
		fout << "," << C.average_sigma_x[i] / C.average_integral_x[i];
	}

	fout.close();
	


	exit(0) ;
	}
}






int main(int argc, char *argv[])
{
	time(&t1);
	localtime_s(&timeObject,&t1);
	init_genrand((unsigned long)time(NULL));
	glutInitWindowPosition(128, 128); // ウィンドウの初期位置．
	glutInitWindowSize(768, 768); // ウィンドウサイズを定義．
	glutInit(&argc, argv);
	glutInitDisplayMode(/*GLUT_DOUBLE |*/ GLUT_RGBA);
	glutCreateWindow(argv[0]);
	//glutDisplayFunc(display);
	glutDisplayFunc(display_mol);

	glutReshapeFunc(resize);
	glutIdleFunc(idle);
	glutMouseFunc(mouse_button);
	glutMotionFunc(mouse_motion);
	initGL();
	glutMainLoop();



}



void idle(void){
	glutPostRedisplay();
}
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


// 投影処理用の行列定義．モデルをウィンドウ一杯に表示する．
// 投影処理用の行列定義．モデルをウィンドウ一杯に表示する．
void defineViewMatrix(double phi, double theta)
// double phi, theta; 方位角と仰角.
{
	unsigned int i, j;
	double c, s, xy_dist;
	double x_axis[3], y_axis[3], z_axis[3], vec[3];
	double left, right, bottom, top, farVal, nearVal, margin;
	double dx, dy, d_aspect, w_aspect, d;

	// 視点の設定．
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

	// 視点を原点とする座標系の定義．
	for (i = 0; i < 3; i++)
		z_axis[i] = eye[i] - center[i];
	normVec(z_axis);
	cross(up, z_axis, x_axis);
	normVec(x_axis);
	cross(z_axis, x_axis, y_axis);

	// left, right, bottom, top, nearVal, farValの決定．
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

	// 図形の周囲に5%ほど余裕を与える．
	margin = (right - left) * 0.05;
	left -= margin;
	right += margin;
	margin = (top - bottom) * 0.05;
	bottom -= margin;
	top += margin;
	margin = (nearVal - farVal) * 0.05;
	farVal -= margin;
	nearVal += margin;

	// 表示範囲のアスペクト比とウィンドウのアスペクト比の比較．
	dx = right - left;
	dy = top - bottom;
	d_aspect = dy / dx;
	w_aspect = (double)window_height / (double)window_width;

	// ウィンドウが表示範囲よりも縦長．表示範囲を縦に広げる．
	if (w_aspect > d_aspect) {
		d = (dy * (w_aspect / d_aspect - 1.0)) * 0.5;
		bottom -= d;
		top += d;

		// ウィンドウが表示範囲よりも横長．表示範囲を横に広げる．
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


// 2本のベクトルvec0とvec1の内積．
double dot(double vec0[], double vec1[])
// double vec0[];
// double vec1[];
{
	return(vec0[X] * vec1[X] + vec0[Y] * vec1[Y] + vec0[Z] * vec1[Z]);
}

// 2本のベクトルvec0とvec1の外積．
void cross(double vec0[], double vec1[], double vec2[])
// double vec0[];
// double vec1[];
// double vec2[]; vec0×vec1.
{
	vec2[X] = vec0[Y] * vec1[Z] - vec0[Z] * vec1[Y];
	vec2[Y] = vec0[Z] * vec1[X] - vec0[X] * vec1[Z];
	vec2[Z] = vec0[X] * vec1[Y] - vec0[Y] * vec1[X];
}

// ベクトルの正規化．
void normVec(double vec[])
// double vec[]; 注意！このベクトルは破壊的に変更される．
{
	double norm;
	norm = sqrt(vec[X] * vec[X] + vec[Y] * vec[Y] + vec[Z] * vec[Z]);
	vec[X] /= norm;
	vec[Y] /= norm;
	vec[Z] /= norm;
}


void resize(int width, int height)
{

	// ウィンドウサイズの取得．
	window_width = width;
	window_height = height;
}