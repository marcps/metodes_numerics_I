/*################################################################################
#------------------------------------------------------------------------------  #
#EXERCICI 1 - Zeros de Funcions: Marc Pascual i Solé - Universitat de Barcelona  #
#--------------------------------------------------------------------------------#
# Programa que troba els zeros d'un polinomi de grau arbitrari n, de la forma:   #
				           a0 + a1x + ... + an*x^n                               #
# Amb el mètode de Newton i de la Secant.                                        #
# Primer demana el gracu, la precisió i els coeficients ai del problema, després #
# En calcula una cota i es treballarà a l'interval [-cota-1, cota+1]. Tot seguit #
# la variable N_MAX dividirà l'interval en blocs més petits i es buscaran canvis #
# de signe en dits subintervals. Una vegada s'sen troba un, es procedeix a calcul#
# ar les arrels amb el mètode de Newton i amb el mètode de la Secant. S'imprimiran
# les iteracions de cada arrel i finalment l'arrel buscada.					     #
##################################################################################
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>


double horner(int n, double a[n+1], double x)
{
/*Calcula el valor del polinomi  a0 + a1x + ... + an*x^n  en un punt arbitrari x*/
	double temp;
	int i;
	temp=0.0;
	for(i=n;i>0;i--) //n vegades
	{
		temp += a[i];
		temp = temp*x;
	}
	return temp+a[0];
}
//Derivada del polinomi de grau n
double deriHorner(int n, double a[n+1], double x)
{
/*Calcula el valor de la derivada del polinomi  a0 + a1x + ... + an*x^n a un punt x*/
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

int newton(int n,double a[n+1], double *x0, double prec, int imax)
{
/*Calcula l'arrel del polinomi  a0 + a1x + ... + an*x^n amb el mètode de Newton
    Retorna un 0 si ha convergit i canvia el valor del punter. Si no convergeix, retorna un 1*/
	int i;
	double z2,z1;

	z1=*x0;
	printf("iteració %d = %lf\n",0,z1);
	for(i=0;i<imax;i++)
	{
		z2=z1-(horner(n,a,z1)/deriHorner(n,a,z1));
		printf("Iteració %d = %lf\n",i+1,z2);
		if(fabs(z2-z1)<prec)
		{
			//Guarda l'adreça de x2 al punter
			*x0=z2;
			return 0;
		}
		else
		{
			z1=z2;
		}
	}
	return 1;
}

int secant(int n, double a[n+1], double *x0, double *x1, double prec, int imax)
{
/*Calcula l'arrel del polinomi  a0 + a1x + ... + an*x^n fent servir el mètode de la secant
   Retorna un 1 i canvia el punter *x1 si convergeix. Retorna un 1 si no ho fa.*/
	//IMPORTANT: Retornarà el valor de la arrel al punter X1!!!
	//IMPORTANT: el punter X0 romandrà invariant!

	int i;
	double z0,z1,z2;

	z0=*x0;
	z1=*x1;

	for(i=0;i<imax;i++)//Fins un màxim d'iteracions, per evitar bucles eterns
	{
		z2= z1 - ((horner(n,a,z1)*(z1-z0))/(horner(n,a,z1)-horner(n,a,z0)));
		printf("·Iteració %d = %lf\n",i+1,z2);

		if(fabs(z2-z1)<prec)
		{
			*x1=z2;
			return 0;
		}
		else
		{
			z0=z1;
			z1=z2;
		}
	}
	return 1;
}


/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PROGRAMA PRINCIPAL =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

int main(void)
{
	//Variable que divideix la cota en N_MAX blocs
	int N_MAX=10;

	int n,i,comptador,arrel;
	printf("[i]Grau del polinomi real. n=");
	scanf("%d",&n);
	double a[n+1],cota,h,ai,bi,prec,temp1,temp2;
	double* x0 = &temp1,*x1=&temp2;

	printf("[i]precisió=");
	scanf("%lf",&prec);

	printf("Coeficients del polinomi real\n");
	for(i=0;i<=n;i++)
	{
		printf("[i] a%d=",i);
		scanf("%lf",&a[i]);
	}

	//------------------ Cota -----------------
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

	//Pas predeterminat. La influència de N_MAX és notable en el càlcul d'arrels
	h=(2.*cota)/(double)N_MAX;
	//-----------------------------------------

	printf("\ncota inicial = %lf\n",cota);

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
			*x0=(ai+bi)/2.0;
			//S'aplica Newton, i el punter x0 canviarà de adreça si el mètode
			// convergeix!
			arrel=newton(n,a,x0,prec,1000);

			if(arrel==0)
			{
				printf("ARREL(%d)=%.10lf\n\n",comptador,*x0);	
			}
			else
			{
				printf("Newton no ha convergit!\n");
				return 1;
			}	
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
		ai=cota-(double)i*h;
		bi=cota -((double)i+1.)*h;

		if((horner(n,a,ai)*horner(n,a,bi))<0.0)
		{
			x0=&ai;
			x1=&bi;
			//S'aplica la Secant
			arrel=secant(n,a,x0,x1,prec,1000);
			if(arrel==0)
			{
				printf("arrel(%d)=%.10lf\n",comptador,*x1);	
			}
			else
			{
				printf("Secant NO ha convergit!\n");
				return 2;
			}
			
			comptador+=1;
		}

	}
	//--------------------------------------------------------------------
	return 0;
}