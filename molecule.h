#pragma once
#define MOL_NUM 500
#include	"Receptor.h"
#include 	"mt19937ar.h"
class molecule
{

	
public:
	double  ud,rl,zz;
	int mol_num;
	double points[MOL_NUM][4];
	double rec_color[REC_NUM][3];
	double color[MOL_NUM][3];

	molecule(int num);
	//~show_molecule(void);
	void cal_location(Receptor);
	void cal_bind(double*);
};

class molecule_1 : public molecule{

public:
	///コンストラクタ
	molecule_1(int num) : molecule(num){
		mol_num = num;
		//分子の初期位置を設定
		for(int i=0; i<num; i++){
			points[i][0] = (genrand_real2()-0.5)*2;
			points[i][1] = (genrand_real2()-0.5)*2;
			points[i][2] = (genrand_real2()-0.5)*2;
			points[i][3] = 0;
			////分子の初期状態の色
			color[i][0] = 0;
			color[i][1] = 0.5;
			color[i][2] = 0.5;
		}
		
		
	};
	void cal_location(void);
	///INPUT で活性化するかを判定
	void cal_active(void);

};


double NDrand(double myu, double sigma);