#include "Receptor.h"
#include 	"mt19937ar.h"
#include 	<time.h>

time_t t2;
struct tm timeObject2;

Receptor::Receptor(void)
{
	time(&t2);
	localtime_s(&timeObject2,&t2);
	init_genrand((unsigned long)time(NULL));
	
	for(int i=0; i<REC_NUM; i++){

		key_ver[i][0] = genrand_real2() *2 - 1;	
		key_ver[i][1] = genrand_real2() *2 - 1;	
		key_ver[i][2] = -0.9;	

		ver[i][0][0] = key_ver[i][0] + 0.005; 
		ver[i][0][1] = key_ver[i][1] + 0.005; 
		ver[i][0][2] = -1;

		ver[i][1][0] = key_ver[i][0] - 0.005; 
		ver[i][1][1] = key_ver[i][1] + 0.005; 
		ver[i][1][2] = -1;

		ver[i][2][0] = key_ver[i][0] - 0.005; 
		ver[i][2][1] = key_ver[i][1] - 0.005; 
		ver[i][2][2] = -1;

		ver[i][3][0] = key_ver[i][0] + 0.005; 
		ver[i][3][1] = key_ver[i][1] - 0.005; 
		ver[i][3][2] = -1;

		rec_color[i][0] = 0;
		rec_color[i][1] = 0.5;
		rec_color[i][2] = 0,7;
	}
	
}

void Receptor::rec_move(void){
	for(int i=0; i<REC_NUM; i++){

		ud = NDrand(0.0,1.0) ;
		rl = NDrand(0.0,1.0) ;
		//zz = NDrand(0.0,1.0) ;

	
			key_ver[i][0] += (int)rl * 0.001;
			key_ver[i][1] += (int)ud * 0.001;
			//key_ver[i][2] += (int)zz * 0.001;

			ver[i][0][0] = key_ver[i][0] + 0.005; 
			ver[i][0][1] = key_ver[i][1] + 0.005; 
			//ver[i][0][2] = -1;

			ver[i][1][0] = key_ver[i][0] - 0.005; 
			ver[i][1][1] = key_ver[i][1] + 0.005; 
			//ver[i][1][2] = -1;

			ver[i][2][0] = key_ver[i][0] - 0.005; 
			ver[i][2][1] = key_ver[i][1] - 0.005; 
			//ver[i][2][2] = -1;

			ver[i][3][0] = key_ver[i][0] + 0.005; 
			ver[i][3][1] = key_ver[i][1] - 0.005; 
			//ver[i][3][2] = -1;

			if(key_ver[i][0] > 1) key_ver[i][0] -= key_ver[i][0] - 1;
			if(key_ver[i][0] < -1) key_ver[i][0] -= key_ver[i][0]+1;
			if(key_ver[i][1] > 1) key_ver[i][1] -= key_ver[i][1]-1;
			if(key_ver[i][1] < -1) key_ver[i][1] -= key_ver[i][1]+1;
			/*if(key_ver[i][2] > 1) key_ver[i][2] -= key_ver[i][2]-1;
			if(key_ver[i][2] < -1) key_ver[i][2] -= key_ver[i][2]+1;*/


	}
}


Receptor::~Receptor(void)
{
}
