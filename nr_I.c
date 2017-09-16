#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Power function*/
float power(float base, int exp)
{
    float result = 1;
    while(exp) { result *= base; exp--; }
    return result;
}

/* Problem Function */

float func(float x,int m, float c)
{

	float f1,a;
	int k;
	f1=1;
	for (k=1; k<= m; k++)
	{
		f1 *= (x-k);
	}
	a = power(x,m);
	return f1 + c*a;
}

float dfunc(float x, int m, float c)
{

	int i,j;
	float dfun,xm,resultat;

	resultat=0;
	dfun=1;

	for (i=1;i<=m;i++)
	{
		for(j=1;j<=m;j++)
		{
			if (j!=i)
				dfun *= x-j;
		}

		resultat += dfun;
		dfun=1;
	}
	xm = power(x,m-1);
	return resultat + (c*m*xm);
}

float newtonRaphson(float x0,int m, float c,int nIter){

	/* Variable Declaration*/
        float fx0,dfx0,x1;
	int i;

        for (i=1; i<=nIter; i++)
        {
                fx0 = func(x0,m,c);
                dfx0 = dfunc(x0,m,c);
                x1 = x0 - (fx0/dfx0);
                printf("Iteration %d : Value x= %f \n",i,x1);
		x0=x1;
        }
	return x1;
}








/*=-=-=-=-==-=-=-=-==-=-=-=-==-=-=-=-==-=-=-=-==-=-=-=-=*/
int main(){
	int m, niter;
	float x0, resultat, c;

	printf("Give a value for m: ");
	scanf("%d",&m);
	printf("Give a value for x0: ");
	scanf("%f",&x0);
	printf("Give a value for c: ");
        scanf("%f",&c);
	printf("Number of iterations: ");
        scanf("%d",&niter);


	resultat = newtonRaphson(x0,m,c,niter);
	printf("Larrel es: %f \n", resultat);
	return 0;
}
