#pragma once
#define REC_NUM 25

class Receptor
{
	double ud, rl, zz ;

public:

	double key_ver[REC_NUM][3];		////////////////��e�̂̕��q������������W	2�s2��ł͂Ȃ�1�s�ŕ\�����B
	double ver[REC_NUM][4][3];			////��e�̂̒��_�ȊO�� X ���W
	//double ver_y[REC_NUM][4];			////��e�̂̒��_�ȊO�� Y ���W
	double rec_color[REC_NUM][3];


	Receptor(void);
	~Receptor(void);
	void rec_move(void);
};

