/*#################################################################################
#---------------------------------------------------------------------------------#
#EXERCICI 2 - Interpolació: Marc Pascual i Solé - Universitat de Barcelona    	  # 
#---------------------------------------------------------------------------------#
#Programa que demana els punts de suport {(xi,fi)} diferents 2 a 2 per una n      #
# donada, i en calcula                                                            #
# les diferències dividides a dits punts. Ho fa definint un vector de n components#
# i una matriu nxn on la 1a columna seran les ordenades de suport fi's. Una vegada#
# hagi completat la matriu amb els coeficients, demana un punt per avaluar el     #
# polinomi																		  #
###################################################################################*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void dif_div(int n, double x[n-1],double y[n-1][n-1])
{
	//INPUT: Matriu nxn amb la primera columna completa (dades del problema)
	//OUTPUT: Es completa la matriu de manera que a cada columna hi haurà un element menys
	//Fins que a l'última columna hi hagi un element
	int i,j;

	for (j=1;j<n;j++)
	{
		for(i=0;i<n-j;i++)
		{
			y[i][j]=(y[i+1][j-1]-y[i][j-1])/(x[i+j]-x[i]);
			printf("%d %d: %lf\n",i,j,y[i][j]);
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
	int n,i,j;
	printf("Number of observations: " );
	scanf("%d",&n);
	double x[n-1],y[n-1][n-1],p,result;
 
	printf("\n\nEscriure les abcisses de suport:\n");
 	for(i=0;i<n;i++)
 		{
 			printf("x%d=",i);
 			scanf("%lf",&x[i]);
 		}
 	printf("\nEscriure les corresponents ordenades de suport:\n");
 	for(i=0;i<n;i++)
 	{
 		printf("f(x%d)=",i);
 		scanf("%lf",&y[i][0]);
 	}

 	dif_div(n,x,y);

 	printf("\n\nEscriure el punt on es desitja saber el valor del polinomi: ");
 	scanf("%lf",&p);

 	//Una vegada sabem el punt, podrem aplicar horner:
 	result=horner(n,p,x,y);
 	printf("\nEl resultat de P(%.3lf)= %.10lf\n ", p,result);

 	return 0;





}