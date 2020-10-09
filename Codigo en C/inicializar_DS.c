#include "inicializar_DS.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


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
