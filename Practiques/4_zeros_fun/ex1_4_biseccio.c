#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double foo(double x)
{
	return x*x -4.;
}

int main(void)
{
	int i,n_max;
	double a,b,a1,b1,p,tol;

	printf("a=");
	scanf("%lf",&a);
	printf("b=");
	scanf("%lf",&b);
	if(foo(a)*foo(b)>0)
	{
		printf("La funció no canvia de signe en l'interval [a,b]\n");
		return 1;
	}
	printf("precisio=");
	scanf("%lf",&tol);

	//S'estimen el nombre de passes necessaris per arribar a la precisió desitjada
	n_max=(int)log((b-a)/tol)/(log(2.)) + 1;

	a1=a;
	b1=b;
	for(i=0;i<n_max;i++)
	{
		p=(a1+b1)/2.;
		if((foo(a1)*foo(p))<=0.)
		{
			b1=p;
		}
		else
		{
			a1=p;
		}

	}
	
	printf("ARREL = %lf\n",p );
	return 0;
}