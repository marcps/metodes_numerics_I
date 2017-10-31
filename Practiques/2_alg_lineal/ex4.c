/*Marc Pascual i Solé */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


void sist_tridiag(double *A,double *Ai,double *As,double *B,double *y, int n)
{
  //INPUT: A,Ai,As,B,y(null),n
  //OUTPUT: y.
  int i,j,k;
  double mult,l;
  //Resol el sistema Ay = b, treballant només amb vectors
  //A és el vector diagonal de la matriu tridiagonal, As és la diagonal superior , Ai la inferior
  //dim(A)=dim(B)=n
  //dim(Ai)=dim(As)=n-1
  //dim(y)=n
  //
  for (k=0;k<=n-2;k++)//Fem eliminació gaussiana
    {  
      mult=Ai[k]/A[k]; //multiplicador

      Ai[k]=mult;
      A[k+1]=A[k+1]-mult*As[k];
      //As[k+1]=As[k+1]-mult*A[k]; -> NO CAL! pq la matriu és tridiagonal!
      B[k+1]=B[k+1]-B[k]*mult;
    }
  //resolem
  y[n-1]=B[n-1]/A[n-1];
  
  for (k=n-2; k>=0; k--)
    {
      y[k]=(B[k]-As[k]*y[k+1])/A[k];
    }
}

//*******************************************************
//Aquestes funcions s'han de modificar segons el problema
double p(double x)
{
  return -2.0/x;
}
double q(double x)
{
  return 2.0/(x*x);
}
double r(double x)
{
  return sin(log(x))/(x*x);
}
//*******************************************************

int main()
{
  //Programa que resol: y''=py'+qy , a<x<b, y(a)=alpha, y(b)=beta
  //INPUT: p(x), q(x), a,b, y(a), y(b)
  
  double *A, *Ai, *As, *B, *y;
  int n,i,k,j;
  double y0,yn,a,b,h,x1,x2,l;
  
  //es demanen els valors de frontera
  printf("Nombre de passes (n): ");
  scanf("%d", &n);
  printf("Inici interval (a): ");
  scanf("%lf", &a);
  printf("Final interval (b): ");
  scanf("%lf", &b);
  printf("Valor y0=y(a)= ");
  scanf("%lf", &y0);
  printf("Valor yn=y(b)= ");
  scanf("%lf", &yn);
  
  h = (b-a)/n; //es calcula el pas h.

  A = (double *)malloc(n*sizeof(double));
  Ai = (double *)malloc((n-1)*sizeof(double));
  As = (double *)malloc((n-1)*sizeof(double));
  B = (double *)malloc(n*sizeof(double));
  y = (double *)malloc(n*sizeof(double));
  
  B[n-1] = -h*h*r(b)+(1-h*p(b)/2.)*yn;
  A[n-1] = 2.+h*h*q(b);
  B[0]= -h*h*r(a)+(1+h*p(a)/2.)*y0;

  for (i=0;i<=n-2;i++)
    {
      l=i*1.;
      x1=a+(l+1)*h;//Es defineix la x a cada loop
      x2=a+(l+2)*h; //Aquesta x es pel vector diagonal inferior, que va decalat

      if (i!=0) //ja definida
		{
	  		B[i]=-h*h*r(x1);
		}
      A[i]=2.+h*h*q(x1);
      Ai[i]=-1.-h*p(x2)/2.;
      As[i]=-1.+h*p(x1)/2.;
    }
  
  //una vegada definits els vectors es procedeix a resoldre l'equació
  
  sist_tridiag(A,Ai,As,B,y,n);

  printf("\n\nSOLUCIONS:\n");
  
  for (k=0;k<=n-1;k++)
    {
      printf("y[%d]=%lf\n",k,y[k]);
    }
    
  free(A);
  free(Ai);
  free(As);
  free(B);
  free(y);
  return 0;
}
