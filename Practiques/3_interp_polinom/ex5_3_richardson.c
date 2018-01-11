/*#################################################################################
#---------------------------------------------------------------------------------#
#EXERCICI 5 - Richardson: Marc Pascual i Solé - Universitat de Barcelona    	  # 
#---------------------------------------------------------------------------------#
#Programa que calcula la derivada d'una funció en un punt usant el mètode de Rich-#
# ardson, fent servir una matriu. Primer de tot, calcula la primera columna de la #
# matriu T fent servir la fòrmula de derivació centrada f' = [ f(a+h)-f(a-h) ]/2h #
# amb una h progressivament més petita decrementada un factor donat "q".          #
# Després, es calculen les demès columnes a partir de la primera amb el mètode de #
# Richardson Tij = Ti-1,j-1 + [ Ti-1,j-1 - Ti,j-1]/[ q^2*j - 1 ].                 #
# Finalment, s'imprimeixen els resultats.                                         #
###################################################################################*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//Nombre màxim de passes de Richardson
#define N 4

double foo(double x)
{
	return exp(x);
}

int main(void)
{
	int i,j;
	double T[N+1][N+1];
	double h,q,a,temp,x;

	printf("\nEXTRAPOLACIÓ DE RICHARDSON\n\n");

	printf("a=");
	scanf("%lf",&a);
	printf("h0=");
	scanf("%lf",&h);
	printf("q=");
	scanf("%lf",&q);


	for(i=0;i<N;i++)
	{
		//x és un múltiple de h
		x=pow(q,i)*h;
		T[i][0]=(foo(a+x)-foo(a-x))/(2.*x);
	}
	for(j=1;j<N;j++)
	{
		for(i=0;i<N;i++)
		{
			if(i>=j)
			{
				temp=pow(q,2*j)-1.;
				T[i][j]=T[i-1][j-1]+((T[i-1][j-1]-T[i][j-1])/temp);
			}
			
		}
	}
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			if(i>=j)
			{
				printf("%.10lf ",T[i][j]);	
			}
		}
		printf("\n");
	}
	return 0;
}