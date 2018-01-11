#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double horner(int n, double a[n+1], double x)
{
	double temp;
	int i;
	temp=0.0;
	for(i=n;i>0;i--)
	{
		temp += a[i];
		temp = temp*x;
	}
	return temp+a[0];
}
//Derivada del polinomi de grau n
double deriHorner(int n, double a[n+1], double x)
{
	double temp;
	int i;
	temp=0.;
	for(i=n;i>1;i--) //n-1 vegades
	{
		temp += (double)i*a[i];
		temp = temp*x;
	}
	return temp+a[1];
}

double newton(int n,double a[n+1], double x0, double prec, int imax)
{
	int i;
	double x2,x1;

	x1=x0;
	printf("iteració %d = %lf\n",0,x1);
	for(i=0;i<imax;i++)
	{
		x2=x1-(horner(n,a,x1)/deriHorner(n,a,x1));
		printf("iteració %d = %lf\n",i+1,x2);
		if(fabs(x2-x1)<prec)
		{
			return x2;
		}
		else
		{
			x1=x2;
		}
	}
}

double secant(int n, double a[n+1], double x0, double x1, double prec, int imax)
{
	int i;
	double z0,z1,z2;

	z0=x0;
	z1=x1;

	for(i=0;i<imax;i++)
	{
		z2= z1 - ((horner(n,a,z1)*(z1-z0))/(horner(n,a,z1) - horner(n,a,z0)));
		printf("iteració %d = %lf\n",i+1,z2);
		if(fabs(z2-z1)<prec)
		{
			return z2;
		}
		else
		{
			z0=z1;
			z1=z2;
		}
	}
}



//3er apartat
int main(void)
{
	int n,i,comptador,N_MAX=10;
	printf("Grau del polinomi real. n=");
	scanf("%d",&n);
	double a[n+1],cota,h,ai,bi,prec,x0,arrel;

	printf("precisió=");
	scanf("%lf",&prec);

	printf("Coeficients del polinomi real\n");
	for(i=0;i<=n;i++)
	{
		printf("a%d=",i);
		scanf("%lf",&a[i]);
	}

	//Cota
	cota=0.0;
	for(i=0;i<n;i++)
	{
		cota += fabs(a[i]/a[n]);
	}
	if(cota<1.0)
	{
		cota=1.0;
	}
	//per donar una mica de marge
	cota+=1.0;

	//Pas predeterminada
	h=(2.*cota)/(double)N_MAX;
	//--------------------------------------

	printf("\ncota = %lf\n",cota);////////////////////////
	// ----------------------------- NEWTON ------------------------------
	printf("\n\n     NEWTON\n");
	comptador=1;
	for(i=0;i<N_MAX;i++)
	{
		//Es defineix l'interval 
		ai=cota - (double)i*h;
		bi=cota - ((double)i+1.)*h;


		if((horner(n,a,ai)*horner(n,a,bi))<0.00)
		{
			//si es satisfà aquesta condició pel teorema de boltzman, hi
			//haurà una arrel
			//Punt inicial x0
			x0=(ai+bi)/2.0;
			//S'aplica Newton i la Secant
			arrel=newton(n,a,x0,prec,1000);
			printf("arrel(%d)=%.10lf\n",comptador,arrel);
			comptador+=1;
		}

	}
	//---------------------------------------------------------------------

	//---------------------------- SECANT ---------------------------------
	printf("\n\n     SECANT\n");
	comptador=1;
	for(i=0;i<N_MAX;i++)
	{
		//Es defineix l'interval 
		ai=cota - (double)i*h;
		bi=cota - ((double)i+1.)*h;

		if((horner(n,a,ai)*horner(n,a,bi))<0.0)
		{
			//S'aplica la Secant
			arrel=secant(n,a,ai,bi,prec,1000);
			printf("arrel(%d)=%.10lf\n",comptador,arrel);
			comptador+=1;
		}

	}
	return 0;
}