#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double foo(double x)
{
	return exp(x)-2;
}

double deriFoo(double x)
{
	//Ha d'ésser la derivada de la funció foo(x)
	return exp(x);
}

int main(void)
{
	int i,n_max;
	double x0,xi,p,eps;

	printf("\n\n       MÈTODE DE NEWTON\n");
	printf("x0=");
	scanf("%lf",&x0);
	printf("precisio=");
	scanf("%lf",&eps);
	printf("n_max=");
	scanf("%d",&n_max);

	xi=x0;
	printf("\nIteracions:\n");
	for(i=0;i<n_max;i++)
	{
		p=xi-(foo(xi)/deriFoo(xi));
		printf("(%d):  %.10lf\n",i+1,p );
		if(fabs(p-xi)<eps)
		{
			printf("Resultat = %.10lf\n",p );
			return 0;
		}
		else
		{
			xi=p;
		}
	}
	printf("La funció no ha convergit\n");
	return 2;
}
	