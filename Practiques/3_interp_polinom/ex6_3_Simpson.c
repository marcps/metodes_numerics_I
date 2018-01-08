#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double foo(double x)
{
	return 1./(1.+x);
}

int main (void)
{
	int i,j,n;
	double h,a,b,temp,x,T;

	printf("\n    INTEGRACIÓ PER SIMPSON\n\n");
	printf("n=");
	scanf("%d",&n);
	printf("a=");
	scanf("%lf",&a);
	printf("b=");
	scanf("%lf",&b);
	//Calculem el pas

	h=(b-a)/(double)n;
 	
	temp=0.0;
	for(i=1;i<n;i++)
	{	
		x=a+(double)i*h;

		if(i%2==0)
		{
			temp += 2.*foo(x);
		}
		else
		{
			temp += 4.*foo(x);
		}
	}

	T=(h/3.)*(foo(a)+foo(b)+temp);
	printf("S(f,a,b)=%.10lf\n\n",T);
}