/*Marc Pascual i Solé - Universitat de Barcelona*/
//Factorització LU de matrius d'ordre arbitrari
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Funció que factoritza una matriu A de la forma A=LU.
//La matriu A queda modificada amb els objectes rellevants de les matrius finals
// L i U
void factor(int n, double **A)
{
  int i,j,k;
  double m;

  for (j=0;j<=n-1;j++)
    {
      for (i=0;i<=n-1;i++)
	{
	  if (i>j)
	    {
	      m = A[i][j]/A[j][j];
	      A[i][j] = m;

	      for (k=j+1;k<=n-1;k++)
		{
		  A[i][k] = A[i][k]-m*A[j][k];
		}
	    }
	}
    }
}
int main()
{
  int n,i,j,k;
  double **A ;
  printf("Escriure l'ordre de la matriu: ");
  scanf("%d",&n);
  A = (double **)malloc(n*sizeof(double));

  if (A==NULL)return 2;

  for (i=0;i<=n-1;i++)
    {
      A[i] = (double *)malloc(n*sizeof(double));
      if (A[i]==NULL) {
	return 4;
      }
    }
  
  //Es demana la matriu A
  
  printf("\n\n Definició de la matriu:\n");
  for (i=0;i<=n-1;i++)
    {
      for (j=0;j<=n-1;j++)
	{
	  printf("A[%d][%d]:",i,j);
	  scanf("%lf", &A[i][j]);
	}
      printf("\n");
    }
  
  //Es Factoritza la matriu
  factor(n,A);
  //S'imprimeixen les matrius LU:
  printf("      U\n");
  for (i=0;i<=n-1;i++)
    {
      for (j=0;j<=n-1;j++)
	{
	  if(i>j) {
	    printf("0.00   ");
	  }
	  if(i<=j)
	    {
	      printf("%3.2f   ",A[i][j]);
	    }
	}
      printf("\n");
    }
  
  ///Matriu L
  printf("\n\n       L\n");
  for (i=0;i<n;i++)
    {
      for(j=0;j<=n-1;j++)
	{
	  if(i==j){
	    printf("1.00   ");
	  }
	  if(i<j)
	    {
	      printf("0.00   ");
	    }
	  if(i>j)
	    {
	      printf("%3.2f   ",A[i][j]);
	    }
	}
      printf("\n");
    }
  printf("\n");
  
  //Exercici Opcional
  //Multipliquem les matrius L*U i haurem de recuperar A
  
  return 0;
}
