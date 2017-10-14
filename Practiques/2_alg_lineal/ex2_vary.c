/*Marc Pascual i Solé - Universitat de Barcelona*/

/*Programa que calcula la solució de Ax = b
 On la matriu A i el vector b es generen aleatoriament*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


void gaussian_elim(int n, double **A)
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
		 //while(A[j][j]<=tol)
		  // {
		    
		   //Es canviara la fila i per la j:
		   for (k=j;k<=n;k++)
		     {
		      temp=A[j][k];
		      A[j][k]=A[j+1][k];
		      A[j+1][k]=temp;
		      // }
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


void backwards_subs(int n, double *x,double **A)
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


int main()
{
  double **A,*x,t;
  int i,j,n;
  clock_t init, finit;

  srand(time(NULL));

  printf("Ordre de la matriu quadrada: ");
  scanf("%d",&n);
  //S'aloca la memoria per la matriu A
  A = (double **)malloc( n *sizeof(double) );
  if (A==NULL)
    {
      printf("Not enough memory!");
      return 2;
    }
  for (i=0;i<=n-1;i++)
    {
      A[i] = (double *)malloc((n+1)*sizeof(double));
      if (A[i]==NULL)
	{
	  printf("Not enough memory!");
	  return 3;
	}
        
    }
  //S'aloca la memoria pel vector b i x

  x=(double *)malloc(n*sizeof(double));
  if(x==NULL)
    {
      printf("Not enough memory!");
      return 4;
    }

  //Es crea la matriu aleatoria
  for (i=0;i<=n-1;i++)
    {
      for (j=0;j<=n;j++)
	{
	  A[i][j]=((double)rand())/RAND_MAX;
	}
    }


  /*********/
  init=clock();
  // es fa l'eliminació gaussiana
  gaussian_elim(n, A);
  //Es resol l'equació per substitució endarrera
  backwards_subs(n,x,A);
  finit=clock();
  /**********/
  
  t = (double)(finit-init)/CLOCKS_PER_SEC;
  
  //Finalment, s'imprimeix el resultat:
  printf("\n\nLa solució és: \n");
  for (i=0;i<=n-1;i++)
    {
      printf("x%d = %lf\n",i,x[i]);
    }
  //I també s'imprimeix el temps de computació
  printf("\n\ntemps d'execució total=%+8.2f\ntemps d'execució per element=%8.2f",t,t/n*n);
  
}

  
