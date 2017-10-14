/*Marc Pascual i Solé - Universitat de Barcelona*/

/*Programa que calcula la solució de Ax = b
 mitjançant el càlcul de la matriu triangular
i per substitució trivial després.
Aquest programa no pot contenir zeros en la diagonal*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>



int main()
{
  int n,i,j,k;
  printf("Ordre de la matriu: ");
  scanf("%d",&n);
  double A[n][n+1], x[n];
  double m,sum;
  clock_t init,finit;

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
  for(j=0;j<=n;j++)
    {
      for(i=0;i<=n-1;i++)
	{
	  if(i>j)
	    {
	      m = A[i][j]/A[j][j];
	      for(k=0;k<=n;k++)
		{
		  A[i][k] = A[i][k]-m*A[j][k];
		}
	    }
	}
    }
  x[n-1] = A[n-1][n-1]/A[n-1][n];
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
  //S'imprimeix la solució
  printf("\n\nLa solució és: \n");
  for (i=0;i<=n-1;i++)
    {
      printf("x%d = %lf\n",i,x[i]);
    }
  
  return 0;
}
