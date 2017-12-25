/*EXERCICI 1: Marc Pascual i Solé - Universitat de Barcelona 
Programa que troba els coeficients del polinomi interpolador p(x)=a0+...+an·x^n
Fent-ho de forma matricial X·a=y
On X és la matriu de punts abcisses de totes les potencies (0%n), y és el vector 
de punts ordenades de suport, i a és el vector de coeficients que volem trobar.*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void gaussian_elim(int n, double **A)
{
  //Funció que fa eliminació gaussiana Suposant que la matriu és n x (n+1) i regular
  int i,j,k;
  double tol,temp,m;
  tol = pow(10,-14);//tolerància = 10^-14
    
  //Es calcula la matriu triangular
  for(j=0;j<=n;j++)
    {
      for(i=0;i<=n-1;i++)
	    {
	      if(i>j)
	        {
	          m = A[i][j]/A[j][j];
	          A[i][j]=m;

	          for(k=j+1;k<=n;k++)
		        {
		          A[i][k] = A[i][k]-m*A[j][k];
		        }
	        }
	    }
    }
}

void backwards_subs(int n, double *x,double **A)
{
  //INPUT: A,n
  //OUTPUT: x
  int i,j;
  double sum;
  x[n-1] = A[n-1][n]/A[n-1][n-1];
  //Es calcula la resta del vector
  for(i=n-2;i>=0;i--)
    {
      sum=0.;
      for(j=i+1;j<=n-1;j++)
	    {
	      sum += A[i][j]*x[j];
	    }
      x[i]=(A[i][n]-sum)/A[i][i];//pq la matriu es triangular
    }  
}

matrix_init(int n, int m, double**A)
{
  int i;
  //n=row number, m=column number
  A=(double **)malloc(n*sizeof(double));
  if (A==NULL) fprintf(stderr, "Error de memoria");
  for (i=0;i<n;i++)
    {
      A[i]=(double *)malloc(m*sizeof(double));
      if (A[i]==NULL) fprintf(stderr, "Error de memoria");
    }
}



int main()
{
  int n,i,j,k;
  double temp, **A;

  printf("Nombre n de passes [n]: ");
  scanf("%d",n);

  //S'inicialitza la matriu A (n+1)x(n+2)
  matrix_init(n+1,n+2,A);

  //-------------- es llegeixen les dades:---------------------------------

  for (i=0;i<=n;i++) //n+1 vegades
    {
      printf("x[%d]=",i);
      scanf("%lf",temp);
      for (j=0;j<=n;j++)
		{
	  	  A[i][j]=pow(temp,j);
	  	  //La primera columna seran tot 1's
		}
    }

  printf("Vector f:\n\n");
  for (i=0;i<n;i++)
    {
      printf("f[%d]",i+1);
      scanf("%lf",A[i][n+1]); //Es llegeixen els valors de la última columna de la matriu ampliada
    }
  // --------------------------------------------------------------------------

  //---------------- S'aplica eliminació Gaussiana ----------------------------


  //

     
