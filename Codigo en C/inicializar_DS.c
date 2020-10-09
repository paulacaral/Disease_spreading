//#include "general.h"
#include "inicializar_DS.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//#include<math.h>


double set_x(double *x, double D, int N)
{
	int i;
	float r;
			
	for(i=0; i<2*N; i++)
	{
		r = (float)rand()/(float)RAND_MAX;
		x[i] = r*D;
	}
	return 0;
}

/*
double set_v(double *v, double T, int N)
{
	double sigma = sqrt(T);
	double VCM[3] = {0,0,0};
	int i,k;
	
	for(i = 0; i < 3*N; i++)
	{
		v[i] = gaussiana(0.0,sigma);
	}
	
	for(i=0; i < N; i++)
	{
		for(k=0;k<3; k++)
		{
			VCM[k] += v[3*i+k]/(double)N;
		}
	}
	
	for(i=0; i < N; i++)
	{
		for(k=0;k<3; k++)
		{
			v[3*i+k] -= VCM[k];
		}
	}
	return 0.0;
}*/