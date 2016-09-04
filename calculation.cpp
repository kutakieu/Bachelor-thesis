#include "calculation.h"
#include <Windows.h>
#include	<iostream>
#include 	<stdio.h>
#include 	<stdlib.h>
#include 	<time.h>
#include 	<fstream>
#include	<cmath>
#include	<cstdlib>
#include	<direct.h>
#include 	"mt19937ar.h"

using namespace std;

time_t t3;
struct tm timeObject3;

calculation::calculation(void)
{
	I = 0;
	dt = 0.0001;
	t_end = 500;
	t_interval = 1000;
	counter = 0;
	Kon = 0.01;
	Koff = 0.5;
	active_ratio = 0;
	for(int i=0; i<STEP; i++){
		N[i] = 100;				//the number of molecules
		p_plus[i] = 0;			//activate ratio
		p_minus[i] = 0 ;		//inhibite ratio
		Non[i] = 0;				//the number of activated molecules
		x[i] = 0;					//activated ratio
		Non_past[i] = 0;
		integral_x[i] = 0;
		average_integral_x[i] = 0;
		average_sigma_x[i] = 0;
	}

	sprintf_s(directory_name, sizeof(directory_name), "rawdata_");///////////////RAWDATA�p�̃f�B���N�g���̖��O�ݒ�

	if(_mkdir(directory_name) == 0)
		cout << "�f�B���N�g������܂����i����j" <<"\n";
	else
		cout << "�f�B���N�g����莸�s���܂����i��΁j" << "\n";

	time(&t3);
	localtime_s(&timeObject3,&t3);
	init_genrand((unsigned long)time(NULL));

	ofstream fout;

	fout.open("rawdata.csv", ios::out|ios::app);
	fout << "t(s)" << "," << "Input(t)" ;

	for(int i=0; i<STEP; i++)	fout << "," << "s_" << i+1 << "  " << N[i] ; 		
		
	fout << "\n";
	fout.close();
	
}

void calculation::signal_cascade(molecule S1, Receptor R){

	

	/////********�v�Z�J�n*******///////

			/////////////���������ׂ����̂�����������//////////////////
		//counter = 0;
		
		//////////////////////rawdata�o�͗p�̂��낢��/////////////////////////
		

		////rawdata_file�̖��O��ݒ�////////
		//sprintf_s(rawdata_name,  sizeof(rawdata_name), "rawdata.csv");

		////rawdata_file�̃t���p�X��ݒ�////////
		//sprintf_s(full_path_rawdata, sizeof(full_path_rawdata), "C:\\Users\\taku\\Desktop\\Receptor_3.0\\Receptor\\%s\\%s",directory_name, rawdata_name);
		
		////rawdata_file ���I�[�v�� & �����ݒ�//////////
		

		

		///////////////////////////////////////////////
		/////********���ԃ��[�v*******///////
		///////////////////////////////////////////////

	ofstream fout;

	fout.open("rawdata.csv", ios::out|ios::app);


			//if(counter > 2000000) I = 0;	//���������
			
			for(int k=0; k<REC_NUM; k++){
				if(S1.rec_color[k][0] == 1.0){
					I += 1;
				}
			}
			I /= REC_NUM;

			Non_past[0] = Non[0];

			p_plus[0] = I  * (N[0] - Non[0]) * dt ;		//�����ł�Kon�͂P�ł��邽�ߏȗ́A�ȉ���Kon��0.01

			p_minus[0] = Koff * Non[0] * dt;

			if(p_plus[0] > genrand_real2() ) Non[0]++;

			if(p_minus[0] > genrand_real2() ) Non[0]--;

			integral_x[0] += Non[0] / N[0];


			/*if(Time> 100){
			average_Non[0] += Non[0];
			sigma_Non[0] += (Non[0]*Non[0]);
			}*/
			//2step�ȍ~
			for(int j=1 ;j<STEP ;j++){

				Non_past[j] = Non[j];

				p_plus[j] = Kon * Non_past[j - 1] * (N[j] - Non[j]) * dt ;

				p_minus[j] = Koff * Non[j] * dt ;

				if(p_plus[j] > genrand_real2() ) Non[j]++;

				if(p_minus[j] > genrand_real2() ) Non[j]--;

				integral_x[j] += Non[j] / N[j];

				//LeaveCriticalSection(cs);

				/*if(Time > 100){
				average_Non[j] += Non[j];
				sigma_Non[j] += (Non[j] * Non[j]);
				}*/
			} //2Step�ȍ~�̌v�Z�I���
			

				////////////�e�X�e�b�v���v�Z������Arawdata��f���o���Ƃ���/////////////
			if(counter % t_interval == 0){
				
				fout << (counter / 1000) << "," <<  I  ;
				for(int i=0; i<STEP; i++){
				fout << "," << Non[i];
				}
				fout << "\n";
			}
		counter ++;
		 //////////////���ԃ��[�v�����܂�////////////////
		I = 0;
		
		fout.close();
}








calculation::~calculation(void)
{
}
