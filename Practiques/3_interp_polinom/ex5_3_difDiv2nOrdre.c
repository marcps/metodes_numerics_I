#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N_MAX 10

double foo(double x)
{
	return exp(x);
}

int main(void)
{
	//Considerem inicialment una funció f(x) i un valor a
	double a,h,q,ddfp,x;
	int i;

	//Diferències centrades de 2n ordre:
	printf("\nDIFERÈNCIES DIVIDIDES DE 2n ORDRE\n\n");
	printf("a=");
	scanf("%lf",&a);
	printf("h0=");
	scanf("%lf",&h);
	printf("q=");
	scanf("%lf",&q);


	for(i=1;i<=N_MAX;i++)
	{
		h=h*q;
		ddfp=(foo(a+h)-2.*foo(a)+foo(a-h))/(h*h);
		printf("%.5lf   %.10lf\n",h,ddfp);
	}
	



	return 0;
}