#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double foo(double x)
{
	return log(2.*x + 1.);
}
int main(void)
{
	//La lambda s'ha de calcular a priori analítciament.
	//La funció ha de satisfer les condicions del teorema 2.2.2 
	// per verificar que la funció convergeix a l'interval desitjat
	// a l'interval s'ha de satisfer que x=g(x)!!
	int i,n;
	double x0,p,eps,x1,lambda;
	printf("\n\n      MÈTODE DEL PUNT FIX\n");
	printf("x0=");
	scanf("%lf",&x0);
	printf("eps=");
	scanf("%lf",&eps);
	printf("lambda=");
	scanf("%lf",&lambda);

	x1=foo(x0);
	n=ceil((log(eps*(1-lambda)/fabs(x0-x1)))/(log(lambda)));
	printf("Nombre estimat d'iteracions n=%d\n",n);
	for(i=0;i<n;i++)
	{
		x1=foo(x0);
		printf("x%d = %.10lf\n",i+1,x1);
		x0=x1;
	}
	return 0;
}