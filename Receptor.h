#pragma once
#define REC_NUM 25

class Receptor
{
	double ud, rl, zz ;

public:

	double key_ver[REC_NUM][3];		////////////////受容体の分子が結合する座標	2行2列ではなく1行で表した。
	double ver[REC_NUM][4][3];			////受容体の頂点以外の X 座標
	//double ver_y[REC_NUM][4];			////受容体の頂点以外の Y 座標
	double rec_color[REC_NUM][3];


	Receptor(void);
	~Receptor(void);
	void rec_move(void);
};

