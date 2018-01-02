#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define NPUNTS 5000

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

double foo(double x)//Funció que es desitja interpolar
{
	return sin(x);
}

int main()
{
	FILE *fp;
	int n,i,j;
	printf("Nombre de passes: ");
	scanf("%d",&n);
	//Les matrius son (n+1)x(n+1)
	double x[n],y[n][n],a,b,h,tempx,tempy; 

	printf("Primer Punt de l'interval. a=");
	scanf("%lf",&a);
	printf("Punt final de l'interval. b=");
	scanf("%lf",&b);

	//Es dividirà l'interval segons Txevitxev
	//Es defineixen les x's
	for(i=0;i<=n;i++)
	{
		x[i]=(a+b)/2.0 + ((b-a)/2.0)*cos((2.0*(double)i-1.0)*M_PI/(2.0*(double)n));
		printf("%lf\n",x[i]);
	}
  	
  	//Es calculen les f(xi) corresponents:
	for(i=0;i<=n;i++)
	{
		y[i][0]=foo(x[i]);
		printf("%lf\n",y[i][0]);
	}

	//Una vegada tenim els punts de suport, es farà el mètode
	//De les diferències dividides
	dif_div(n+1,x,y);



	//Ara, s'escriurà un fitxer amb NPUNTS, per fer la gràfica amb GNUPLOT:
	fp=fopen("ex2_3_dades_txevitxev.res","w");

	h=(b-a)/(double)NPUNTS; //pas
	fprintf(fp,"#X    Y\n");
	for (i=0;i<=NPUNTS;i++)
	{
		tempx=a+h*(double)i; //X's
		tempy=horner(n,tempx,x,y);//y's
		fprintf(fp,"%.15lf %.15lf\n",tempx,tempy);

	}
	fclose(fp);


	return 0;
}