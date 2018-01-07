#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double foo(double x)
{
	return sin(x);
}

int main (void)
{
	int i,j,n;
	double h,a,b,temp,x,T;

	printf("\n    INTEGRACIÓ PER TRAPEZIS\n\n");
	printf("n=");
	scanf("%d",&n);
	printf("a=");
	scanf("%lf",&a);
	printf("b=");
	scanf("%lf",&b);
	//Calculem el pas

	h=(b-a)/(double)n;

	temp=0.0;
	for(i=0;i<n;i++)
	{
		x=a+(double)i*h;
		temp += foo(x);
	}

	T=(h/2.)*(foo(a)+foo(b)+2.*temp);
	printf("T(f,a,b)=%.10lf\n\n",T);
}