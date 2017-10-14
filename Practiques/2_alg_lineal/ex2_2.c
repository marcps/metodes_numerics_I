/*Marc Pascual i Solé - Universitat de Barcelona*/

/*Programa que calcula la solució de Ax = b
 mitjançant el càlcul de la matriu triangular
i per substitució trivial després.
Aquest programa no pot contenir zeros en la diagonal*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

void gaussian_elim(int n, double A[n][n+1])
{
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
	     //******* tolerància ***************
	     if(A[j][j]<=tol)
	       {
		while(A[j][j]<=tol)
		  {
		   //Es canviara la fila i per la j:
		   for (k=j;k<=n;k++)
		     {
		      temp=A[j][k];
		      A[j][k]=A[j+1][k];
		      A[j+1][k]=temp;
		     }
		  }
	       }
	     //*********************************
	     
	     if (A[j][j]>tol)
	       {
		m = A[i][j]/A[j][j];
		for(k=0;k<=n;k++)
		  {
		    A[i][k] = A[i][k]-m*A[j][k];
		  }
	       }
	    }
	}
    }
}


void backwards_subs(int n, double x[n],double A[n][n+1])
{
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
/*************************************************************/
/**************** PROGRAMA PRINCIPAL *************************/
/*************************************************************/

int main()
{
  int n,i,j,k;
  printf("Ordre de la matriu: ");
  scanf("%d",&n);
  
  double A[n][n+1], x[n];
  double m,sum;

  //Es demanen les components de la matriu Extesa
  printf("Escriure els components de la matriu extesa:\n");
  for (i=0;i<=n-1;i++)
    {
      for (j=0;j<=n;j++)
	{
	  printf("A[%d][%d]: ",i+1,j+1);
	  scanf("%lf",&A[i][j]);
	}
    }

  //Es calcula la matriu triangular
  gaussian_elim(n, A);
  //Es calcula el vector per substitució endarrera
  backwards_subs(n,x,A);
  
  //Finalment s'imprimeix la solució
  printf("\n\nLa solució és: \n");
  for (i=0;i<=n-1;i++)
    {
      printf("x%d = %lf\n",i,x[i]);
    }
  
  return 0;

}
