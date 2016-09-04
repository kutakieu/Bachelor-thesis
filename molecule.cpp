#include	<cmath>
#include	<windows.h>
#include	<iostream>
#include	<GL/gl.h>
#include	<GL/glut.h>
#include 	"mt19937ar.h"
#include	"molecule.h"
#include	"Receptor.h"

#define REC_NUM 25
	double key_ver[REC_NUM*2];		////////////////��e�̂̕��q������������W	2�s2��ł͂Ȃ�1�s�ŕ\�����B
	double rec_color[REC_NUM][3];

molecule::molecule(int num)
{
	mol_num = num;
		//���q�̏����ʒu��ݒ�
	for(int i=0; i<num; i++){
		points[i][0] = (genrand_real2()-0.5)*2;
		points[i][1] = (genrand_real2()-0.5)*2;
		points[i][2] = (genrand_real2()-0.5)*2;
		points[i][3] = -1;
		color[i][0] = 0;
		color[i][1] = 0.5;
		color[i][2] = 0.5;
	}

	for(int j=0; j<REC_NUM; j++){
		rec_color[j][0] = 0.0;
		rec_color[j][1] = 0.5;
		rec_color[j][2] = 0.2;
	}

}

void molecule::cal_location(Receptor key){
	////�܂���e�̂̐F��������
	for(int j=0; j<REC_NUM; j++){
					
		rec_color[j][0] = 0.0;	

	}

	
	for(int i=0; i<mol_num; i++){
		/////////�������Ă����ꍇ�������邩�𔻒�
		if(points[i][3] != -1 && genrand_real2() > 0.999){
				points[i][3] = -1;
		}

		
		//////�������Ă��Ȃ����K���h���g�U������
		if(points[i][3] == -1){
			ud = NDrand(0.0,1.0) ;
			rl = NDrand(0.0,1.0) ;
			zz = NDrand(0.0,1.0) ;

			points[i][0] += (int)rl * 0.001;
			points[i][1] += (int)ud * 0.001;
			points[i][2] += (int)zz * 0.001;

			if(points[i][0] > 1) points[i][0] -= points[i][0] - 1;
			if(points[i][0] < -1) points[i][0] -= points[i][0]+1;
			if(points[i][1] > 1) points[i][1] -= points[i][1]-1;
			if(points[i][1] < -1) points[i][1] -= points[i][1]+1;
			if(points[i][2] > 1) points[i][2] -= points[i][2]-1;
			if(points[i][2] < -1) points[i][2] -= points[i][2]+1;
		}
				
		//////�e��e�̂ƃ��K���h�̋������͂���
		if(points[i][2] <= -0.8){

			for(int j=0; j<REC_NUM; j++){
					
				if(sqrt(((points[i][0]-key.key_ver[j][0]) * (points[i][0]-key.key_ver[j][0]) + (points[i][1] - key.key_ver[j][1]) * (points[i][1] - key.key_ver[j][1]) + (points[i][2]-key.key_ver[j][2]) * (points[i][2]-key.key_ver[j][2]))) < 0.005){
					
					points[i][3] = j;			////��������Ԃ������ʁi�O�ȏ�Ŋ����j�A���ǂ̎�e�̂Ɍ������Ă��邩�����x��
					rec_color[j][0] = 1.0;		/////���K���h������������e�̂̐F��ς���

					/////��e�̂Ɍ����������K���h�̈ʒu����e�̂̐�[�Ɉړ�
					points[i][0] = key.key_ver[j][0] ;
					points[i][1] = key.key_ver[j][1] ;
					points[i][2] = key.key_ver[j][2];

					/*���ꂾ�ƐF�͊��Ȃ������B�B�B�����œn�����N���X�̃����o�ϐ��͕ς����Ȃ��H
					key.rec_color[j][0] = 1.0;
					key.rec_color[j][2] = 0.0;
					*/

					/////�����������K���h�̐F��ς���B
					color[i][0] = 1.0;
					color[i][2] = 1.0;
				}
			}
		}
	}

	
}


void molecule::cal_bind(double *key){
	for(int i=0; i<mol_num; i++){
		if(points[i][2] <= -0.8){
			for(int j=0; j<REC_NUM*2; j++){
				if(points[i][3] = sqrt(((points[i][0]-key[j])*(points[i][0]-key[j]) + (points[i][1] - key[j+=1]) * (points[i][1] - key[j]) + (points[i][2]-0.9) * (points[i][2]-0.9))) < 0.1){
					points[i][0] = key[j];
					points[i][1] = key[j+1];
					points[i][2] = 0.9;
				}
			}
		}
	}

}

void molecule_1::cal_location(void){

	/*double  ud = NDrand(0.0,1.0) ;
	double rl = NDrand(0.0,1.0) ;*/

	for(int i=0; i<mol_num; i++){

		ud = NDrand(0.0,1.0) ;
		rl = NDrand(0.0,1.0) ;
		zz = NDrand(0.0,1.0) ;

		points[i][0] += (int)rl * 0.001;
		points[i][1] += (int)ud * 0.001;
		points[i][2] += (int)zz * 0.001;

		if(points[i][0] > 1) points[i][0] -= points[i][0] - 1;
		if(points[i][0] < -1) points[i][0] -= points[i][0]+1;
		if(points[i][1] > 1) points[i][1] -= points[i][1]-1;
		if(points[i][1] < -1) points[i][1] -= points[i][1]+1;
		if(points[i][2] > 1) points[i][2] -= points[i][2]-1;
		if(points[i][2] < -1) points[i][2] -= points[i][2]+1;

	}
}


void molecule_1::cal_active(void){

	for(int i=0; i<mol_num; i++){

		if(genrand_real2() > 0.999) points[i][3] = 1;
		if(genrand_real2() > 0.999) points[i][3] = 0;
	}
}




