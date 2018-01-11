/*#################################################################################
#---------------------------------------------------------------------------------#
#EXERCICI 3-Interpolació de Hermite: Marc Pascual i Solé-Universitat de Barcelona #   	  
#---------------------------------------------------------------------------------#
#Programa que calcula el polinomi interpolador de Hermite, en el cas especial on  #
# es donen per cada abicssa de suport, el valor de la funció i el de la seva deri-#
# vada.                                                                           #
###################################################################################*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define NPUNTS 5000

void dif_div_hermite(int n, double x[n-1],double y[n-1][n-1])
{

	int i,j;

	//ACLARACIÓ: Només a la primera iteració s'haurà d'aplicar realment Hermite
	//           Després es proseguiran les diferències dividides!
	//j=1 - PRIMERA ITERAIÓ amb HERMITE
	for(i=0;i<n-1;i++)
	{
		if(i%2==0)
		{
			y[i][1]=y[i+1][0];//Aquests valors contenen les primeres derivades
		}
		else
		{
			y[i][1]=(y[i+1][0]-y[i-1][0])/(x[i+1]-x[i-1]);
		}
	}
    //RESTA D'ITERACIONS - Diferències Dividides per construcció del problema
	for (j=2;j<n;j++)
	{
		for(i=0;i<n-j;i++)
		{
			y[i][j]=(y[i+1][j-1]-y[i][j-1])/(x[i+j]-x[i]);
			printf("(%d,%d): %lf\n",i,j,y[i][j]);
		}
	}
}

double horner(int n, double p, double x[n], double y[n][n] )
{
	//INPUT: una x per avaluar el polinomi interpolador en un punt
	//       una matriu nxn que se li ha aplicat el mètode de diferències dividides:
	//OUTPUT: S'avalua el polinomi interpolador a un punt donat x.
	double temp;
	int i;
    temp=y[0][n-1];
    for(i=n-2;i>=0;i--)
    {
    	temp=temp*(p-x[i])+y[0][i];
    }
    return temp;
}

int main()
{
	//Programa que llegeix triplets de dades xi fi f'i i resol el problema de la
	// interpolació de Hermite
	FILE *fp;
	int i,j,n;
	printf("Nombre de punts DIFERENTS: " );
	scanf("%d",&n);
	//En realitat hi ha el doble de punts (cadascun ve també amb el valor de la derivada!)
	n=2*n;
	double x[n-1],y[n-1][n-1];
	double a,b,h,tempx,tempy;

	// --------------------------------- USER INPUT ----------------------------------------
	printf("\n\nEscriure les abcisses de suport:\n");
 	for(i=0;i<n;i++)
 		{
 			if(i%2==0)
 			{
 				printf("x%d=",i/2);
 				scanf("%lf",&x[i]);
 			}
 			else
 			{
 				x[i]=x[i-1];
 			}
 		}
 	printf("\nEscriure les corresponents ordenades de suport:\n");

 	for(i=0;i<n;i++)
 	{
 		if(i%2==0)
 		{
 			printf("f(x%d)=",i/2);
 			scanf("%lf",&y[i][0]);
 		}
 		else
 		{
 			printf("f'(x%d)=",(i-1)/2);
 			scanf("%lf",&y[i][0]);
 		}
 	}
 	//----------------------------------------------------------------------------------------

 	//----------------------------------------------------------------------------------------
 	//Una vegada s'ha demanat tot L'INPUT, es passarà a fer diferències dividides:
 	dif_div_hermite(n,x,y);

 	//############################### STD OUTPUT #################################

 	printf("\n\n\n            MATRIU de HERMITE\n");
 	for(i=0;i<n;i++)
 	{
 		for(j=0;j<n-i;j++)
 		{
 			printf("%lf  ",y[i][j]);
 		}
 		printf("\n");
 	}
 	//############################################################################


 	//################################ FILE OUTPUT ###############################
 	// Finalment s'escriuran els resultats en un fitxer
 	fp=fopen("res_ex3_3.dat","w");
 	a=x[0];
 	b=x[n-1];
 	h=(b-a)/(double)NPUNTS; //pas
	fprintf(fp,"#X    Y\n");
	for (i=0;i<=NPUNTS;i++)
	{
		tempx=a+h*(double)i; //X's
		tempy=horner(n,tempx,x,y);//y's
		fprintf(fp,"%.15lf %.15lf\n",tempx,tempy);

	}
	fclose(fp);
 	//##############################################################################

 	return 0;
}