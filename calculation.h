#pragma once
#include "Receptor.h"
#include "molecule.h"
#include 	"mt19937ar.h"
#include 	<time.h>
#define STEP 8
#define T_MAX 10 

class calculation
{
public:

	double dt ;				//delta time
	double t_end ;		//Time end of simulation

	double Kon ;
	double Koff ;
	double I;
	double N[STEP];				//the number of molecules
	double p_plus[STEP];			//activate ratio
	double p_minus[STEP] ;		//inhibite ratio
	double Non[STEP];				//the number of activated molecules
	double x[STEP];					//activated ratio
	double Non_past[STEP];
	double integral_x[STEP];
	double average_integral_x[STEP];
	double average_sigma_x[STEP];
	double active_ratio;
	int counter;
	int  t_interval ;

		char parameter_name[64];
		char result_name[64];
		char directory_name[64];
		char rawdata_name[64];
		char full_path_parameter[128];
		char full_path_rawdata[128];

	calculation(void);
	~calculation(void);
	void signal_cascade(molecule S1, Receptor R);
};

