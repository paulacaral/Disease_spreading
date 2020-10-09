#include "visualizacion_DS.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


double Visual_Frame0(double p_j, int N_I, int N_R, int N_S, double* x_I, double* x_R, double* x_S)
{
	char filename_I_inicial[255];
	char filename_S_inicial[255];
	char filename_R_inicial[255];
	
	FILE* fp_inf_inicial;
	FILE* fp_sus_inicial;
	FILE* fp_rec_inicial;
		
	sprintf(filename_I_inicial, "C:\\Users\\Paula\\Documents\\Facultad\\Fisica Computacional\\Final\\Codigo\\P %.2f\\INF_P%.2f_000.txt",p_j,p_j);
	sprintf(filename_S_inicial, "C:\\Users\\Paula\\Documents\\Facultad\\Fisica Computacional\\Final\\Codigo\\P %.2f\\SUS_P%.2f_000.txt",p_j,p_j);
	sprintf(filename_R_inicial, "C:\\Users\\Paula\\Documents\\Facultad\\Fisica Computacional\\Final\\Codigo\\P %.2f\\REC_P%.2f_000.txt",p_j,p_j);

	fp_inf_inicial = fopen(filename_I_inicial, "w");
	fp_sus_inicial = fopen(filename_S_inicial, "w");
	fp_rec_inicial = fopen(filename_R_inicial, "w");
	
	// Guardo el frame inicial
	for(int i=0; i<2*(N_I); i++)
	{
		fprintf(fp_inf_inicial,"%lf\t",x_I[i]);
	}

	for(int i=0; i<2*(N_S); i++)
	{
		fprintf(fp_sus_inicial,"%lf\t",x_S[i]);
	}
	
	for(int i=0; i<2*(N_R); i++)
	{
		fprintf(fp_rec_inicial,"%lf\t",x_R[i]);
	}
	
	fclose(fp_inf_inicial);
	fclose(fp_sus_inicial);
	fclose(fp_rec_inicial);
	
	return 0;
}

		
double Visual_Frames(double p_j, int N_I, int N_R, int N_S, double* x_I, double* x_R, double* x_S, int l)
{		
	char filename_I[255];
	char filename_S[255];
	char filename_R[255];

	FILE* fp_inf;
	FILE* fp_sus;
	FILE* fp_rec;
	
	if(l<10)
	{
		sprintf(filename_I, "C:\\Users\\Paula\\Documents\\Facultad\\Fisica Computacional\\Final\\Codigo\\P %.2f\\INF_P%.2f_%03d.txt",p_j, p_j, l);
		sprintf(filename_S, "C:\\Users\\Paula\\Documents\\Facultad\\Fisica Computacional\\Final\\Codigo\\P %.2f\\SUS_P%.2f_%03d.txt",p_j, p_j, l);
		sprintf(filename_R, "C:\\Users\\Paula\\Documents\\Facultad\\Fisica Computacional\\Final\\Codigo\\P %.2f\\REC_P%.2f_%03d.txt",p_j, p_j, l);
	}
	
	if(l>=10 && l<100)
	{
		sprintf(filename_I, "C:\\Users\\Paula\\Documents\\Facultad\\Fisica Computacional\\Final\\Codigo\\P %.2f\\INF_P%.2f_0%i.txt",p_j, p_j, l);
		sprintf(filename_S, "C:\\Users\\Paula\\Documents\\Facultad\\Fisica Computacional\\Final\\Codigo\\P %.2f\\SUS_P%.2f_0%i.txt",p_j, p_j, l);
		sprintf(filename_R, "C:\\Users\\Paula\\Documents\\Facultad\\Fisica Computacional\\Final\\Codigo\\P %.2f\\REC_P%.2f_0%i.txt",p_j, p_j, l);
	}
	
	if(100<=l)
	{
		sprintf(filename_I, "C:\\Users\\Paula\\Documents\\Facultad\\Fisica Computacional\\Final\\Codigo\\P %.2f\\INF_P%.2f_%i.txt",p_j, p_j, l);
		sprintf(filename_S, "C:\\Users\\Paula\\Documents\\Facultad\\Fisica Computacional\\Final\\Codigo\\P %.2f\\SUS_P%.2f_%i.txt",p_j, p_j, l);
		sprintf(filename_R, "C:\\Users\\Paula\\Documents\\Facultad\\Fisica Computacional\\Final\\Codigo\\P %.2f\\REC_P%.2f_%i.txt",p_j, p_j, l);
	}

	fp_inf = fopen(filename_I, "w");
	fp_sus = fopen(filename_S, "w");
	fp_rec = fopen(filename_R, "w");
	
	for(int i=0; i<2*(N_I); i++)
	{
		//printf("x_I[%i] = %lf\n", i, x_I[i]);
		fprintf(fp_inf,"%lf\t",x_I[i]);
	}
		
	for(int i=0; i<2*(N_S); i++)
	{
		//printf("x_S[%i] = %lf\n", i, x_S[i]);
		fprintf(fp_sus,"%lf\t",x_S[i]);
	}
	
	for(int i=0; i<2*(N_R); i++)
	{
		//printf("x_R[%i] = %lf\n", i, x_R[i]);
		fprintf(fp_rec,"%lf\t",x_R[i]);
	}
	
	fclose(fp_inf);
	fclose(fp_sus);
	fclose(fp_rec);
	
	return 0;
}			