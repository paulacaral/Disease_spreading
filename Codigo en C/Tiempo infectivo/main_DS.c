/* gcc -Wall -O3 -o Disease_spreading.exe main_DS.c inicializar_DS.c visualizacion_DS.c -lm*/

#include "inicializar_DS.h"
#include "visualizacion_DS.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define PI 3.14159265

double randfrom(double min, double max);

int main(int argc, char *argv[]){

	int N, i, j, k, runs, N_I, N_R, N_S, N_frames, runs_max;
	double D, rho, d, lambda, P_contagio, rnd, mu, p_j, v_mod, r_theta, v_x, v_y;
	float r_x, r_y; 
  
	printf("\nDecime la probabilidad de un long jump\n");
	scanf("%lf", &p_j);
	printf("\nDecime la probabilidad de recuperarse\n");
	scanf("%lf", &mu);

	N = 1000;
	rho = 1;
	N_frames = 300;
	D = sqrt(N/rho);
	lambda = 0.1;
	//mu = 0.05;
	v_mod = 0.1;
	runs_max = 100;

	// Por cada run tendre un vector de valores de N_I (uno por cada frame). En N_I_tomean guardo los vectores de todos los runs.
	int *N_I_tomean = (int *) malloc(N_frames*runs_max*sizeof(int));
	// Luego de realizar el promedio entre runs, tendre un valor promedio de N_I por frame. Esto lo guardo en N_I_mean (y es lo que grafico).
	double *N_I_mean = (double *) malloc(N_frames*sizeof(double));
	int	runs_count = 0;

	for(runs = 0; runs<runs_max; runs++)
	{
		// Inicio las cantidades de individuos infectados, susceptibles y recuperados
		N_I = 10;
		N_R = 0;
		N_S = N-N_I-N_R;
		
		// Creo los vectores con las posiciones de cada tipo de individuo
		double *x_I = (double *) malloc(2*N_I*sizeof(double));
		double *x_S = (double *) malloc(2*N_S*sizeof(double));
		double *x_R = (double *) malloc(2*N_R*sizeof(double));
		
		// Creo el vector que va a contener, para un solo run, el valor de N_I en cada frame
		int *N_I_run = (int *) malloc(N_frames*sizeof(int));

	//----------------------------------------------------------------------------------------------//
		// Configuro posiciones iniciales de todos los individuos
		set_x(x_I, D, N_I);
		set_x(x_S, D, N_S);
		set_x(x_R, D, N_R);
		
		// N_I en el frame 0 es el N_I inicial, lo guardo en el vector
		N_I_run[0] = N_I;
		
		// Se guarda el primer frame para la visualizacion
		Visual_Frame0(p_j, mu, N_I, N_R, N_S, x_I, x_R, x_S);
		
		// Empiezan los frames - Avance temporal
		for(int l = 1; l < N_frames; l++)
		{	
			printf("Frame: %i\t \n",l);
			
			// Para cada individuo susceptible, miro cuantos infectados hay en un radio 1 desde su posicion (N_Ir)
			for(i=0; i<2*N_S; i=i+2)
			{
				int N_Ir = 0;
				for(j=0; j<2*N_I; j=j+2)
				{
					d = sqrt((x_S[i]-x_I[j])*(x_S[i]-x_I[j])+(x_S[i+1]-x_I[j+1])*(x_S[i+1]-x_I[j+1]));
					if(d<1)
					{
						N_Ir++;
					}
				}
				
				// Luego uso el metodo de MonteCarlo para decidir si se infectan o no con una probabilidad 1-(1-lambda)**N_Ir
				P_contagio = (double) 1- pow(1-lambda,N_Ir);
				rnd = (double)rand()/(double)RAND_MAX;
				if(P_contagio > rnd)
				{	
					// Si se infectan actualizo los vectores de susceptibles y de infectados
					int new_inf = i; // Me paro en la coordenada X del individuo
					
					// Actualizo vector de infectados
					N_I = N_I+1;
					x_I = (double *) realloc(x_I,2*N_I*sizeof(double));
					x_I[2*N_I-2] = x_S[new_inf];
					x_I[2*N_I-1] = x_S[new_inf+1];
					
					// Actualizo vector de susceptibles
					for(k=new_inf; k<2*N_S; k++)
					{
						x_S[k] = x_S[k+2];
					}
					N_S = N_S-1;
					x_S = (double *) realloc(x_S,2*N_S*sizeof(double));
				}	
			}
			
			// Ahora para cada individuo infectado, decido por MonteCarlo si se recupera o no con probabilidad mu
			for(i=0; i<2*N_I; i=i+2)
			{
				rnd = (double)rand()/(double)RAND_MAX;
				if(mu > rnd)
				{
					// Si se recuperan, actualizo los vectores de infectados y de recuperados
					int new_rec = i;
					
					// Actualizo vector de recuperados
					N_R = N_R+1;
					x_R = (double *) realloc(x_R,2*N_R*sizeof(double));
					x_R[2*N_R-2] = x_I[new_rec];
					x_R[2*N_R-1] = x_I[new_rec+1];
					
					// Actualizo vector de infectados
					for(k=new_rec; k<2*N_I; k++)
					{
						x_I[k] = x_I[k+2];
					}
					N_I = N_I-1;
					x_I	= (double *) realloc(x_I,2*N_I*sizeof(double));
				}
			}
			
			// Guardo la cantidad de infectados de este frame en el vector que corresponde
			N_I_run[l] = N_I;
			
			// Guardo los vectores de posicion para la visualizacion (me alcanza con guardarlos para un solo run)
			if(runs == 0) Visual_Frames(p_j, mu, N_I, N_R, N_S, x_I, x_R, x_S, l);
			
			// Una vez que se si son infectados, recuperados o susceptibles en este nuevo frame, modifico su posicion
			// Para todos los agentes:
			// Con prob p_j dan un salto de larga distancia y con prob (1-p_j) se mueven cerca con una cierta velocidad v
			
			// Miro los susceptibles
			for(i=0; i<2*N_S; i = i+2)
			{
				rnd = (double)rand()/(double)RAND_MAX;
				if (p_j > rnd) //salto largo
				{
					r_x = (float)rand()/(float)RAND_MAX;
					r_y = (float)rand()/(float)RAND_MAX;
					x_S[i] = r_x*D;
					x_S[i+1] = r_y*D;
				}
				else
				{
					r_theta = randfrom(-PI,PI); //random entre -pi y pi
					
					v_x = v_mod*cos(r_theta);
					v_y = v_mod*sin(r_theta);
					
					x_S[i] = x_S[i] + v_x;
					x_S[i+1] = x_S[i+1] + v_y;
					
				}
			}
			
			// Miro los infectados
			for(i=0; i<2*N_I; i = i+2)
			{
				rnd = (double)rand()/(double)RAND_MAX;
				if (p_j > rnd)
				{
					r_x = (float)rand()/(float)RAND_MAX;
					r_y = (float)rand()/(float)RAND_MAX;
					x_I[i] = r_x*D;
					x_I[i+1] = r_y*D;
				}
				else
				{
					r_theta = randfrom(-PI,PI); //random entre -pi y pi
					
					v_x = v_mod*cos(r_theta);
					v_y = v_mod*sin(r_theta);
					
					x_I[i] = x_I[i] + v_x;
					x_I[i+1] = x_I[i+1] + v_y;
					
				}
			}
			
			// Miro los recuperados
			for(i=0; i<2*N_R; i = i+2)
			{
				rnd = (double)rand()/(double)RAND_MAX;
				if (p_j > rnd)
				{
					r_x = (float)rand()/(float)RAND_MAX;
					r_y = (float)rand()/(float)RAND_MAX;
					x_R[i] = r_x*D;
					x_R[i+1] = r_y*D;
				}
				else
				{
					r_theta = randfrom(-PI,PI); //random entre -pi y pi
					
					v_x = v_mod*cos(r_theta);
					v_y = v_mod*sin(r_theta);
					
					x_R[i] = x_R[i] + v_x;
					x_R[i+1] = x_R[i+1] + v_y;
					
				}
			}
			
		}
		
		// Al terminar el run, libero los vectores de posicion
		free(x_I);
		free(x_S);
		free(x_R);
		
		// Guardo el vector de N_I de este run
		for(j=0;j<N_frames;j++)
		{
			N_I_tomean[runs_count+j] = N_I_run[j];
		}
		
		free(N_I_run);
		runs_count = runs_count + N_frames;
	}
	
	// Al terminar todos los runs, puedo promediar sobre los valores de N_I correspondientes a un mismo frame
	for(j=0; j<N_frames; j++)
	{
		int N_suma = 0;
		for(i=0; i<runs_max; i++)
		{
			N_suma = N_suma + N_I_tomean[j+i*N_frames];
		}
		N_I_mean[j] = (double) N_suma/runs_max;
	}
	
	
	// Guardo los valores promedio de N_I de cada frame
	char filename_Nmean[255];
	FILE* Nmean;
	
	sprintf(filename_Nmean, "C:\\Users\\Paula\\Documents\\Facultad\\Fisica Computacional\\Final\\Codigo\\P %.2f\\Mu %.2f\\N_I_mean_%.2f_mu%.2f.txt",p_j,mu,p_j,mu);
	Nmean = fopen(filename_Nmean, "w");
	
	for(int i=0; i<N_frames; i++)
	{
		fprintf(Nmean,"%f\t",N_I_mean[i]);
	}
	fclose(Nmean);
	
	free(N_I_tomean);
	free(N_I_mean);
	
	return 0;
}

/* generate a random floating point number from min to max */
double randfrom(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}  
  
