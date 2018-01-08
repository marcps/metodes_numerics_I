#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//Nombre màxim de passos de Richardson
#define N_MAX 5

double foo(double x)
{
	return 1./(1.+x);
}

int main (void)
{
	int i,j,n,k;
	double h,a,b,temp,x,T[N_MAX+1][N_MAX+1],q,q1;

	
	printf("\n    INTEGRACIÓ PER ROMBERG\n\n");
	printf("n=");
	scanf("%d",&n);
	printf("a=");
	scanf("%lf",&a);
	printf("b=");
	scanf("%lf",&b);
	printf("q=");
	scanf("%lf",&q);

	//Es fa el mètode dels trapezis amb un pas cada vegada més petit
	for(i=0;i<N_MAX;i++)
	{
		//Calculem el pas
		q1=pow(q,i);
		h=q1*((b-a)/(double)n);

		temp=0.0;
		for(k=1;k<(n/q1);k++)
		{
			x=a+(double)k*h;
			temp += foo(x);
		}

		T[i][0]=(h/2.)*(foo(a)+foo(b)+2.*temp);
	}
	//Mètode de Richardson
	for(j=1;j<N_MAX;j++)
	{
		for(i=0;i<N_MAX;i++)
		{
			if(i>=j)
			{
				temp=pow(q,2*j)-1.;
				T[i][j]=T[i-1][j-1]+((T[i-1][j-1]-T[i][j-1])/temp);
			}
			
		}
	}

	//S'imprimeixen els resultats:
	printf("\n\n        RESULTATS\n");
	for(i=0;i<N_MAX;i++)
	{
		for(j=0;j<N_MAX;j++)
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