/**/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//funció que resol un sistema d'equacions Ax=b.
//A(nxn) es una matriu triangular superior
void backwards_subs(int n, double *x,double **A, double *b)
{
  int i,j;
  double sum;
  x[n-1] = b[n-1]/A[n-1][n-1];
  //Es calcula la resta del vector
  for(i=n-2;i>=0;i--)
    {
      sum=0.;
      for(j=i+1;j<=n-1;j++)
        {
          sum += A[i][j]*x[j];
        }
  
      x[i]=(b[i]-sum)/A[i][i];//pq la matriu es triangular superior
    }  

}


void fact_LDL(double **A,int n)
{
  int i,j,k;
  double d1,tempSum;
  if (A==NULL)
    {
      printf("Error in memory!");
    }
  
  d1 = A[0][0];
  for (i=1;i<=n-1;i++)
    {
      A[i][0]=A[i][0]/d1;
    }
  //********************************************
  for (j=1;j<=n-2;j++)
    {
      tempSum=0;
      for (k=0;k<=j-1;k++)
	     {
	       tempSum += (A[j][k])*(A[j][k])*A[k][k];
	     }
      A[j][j]=A[j][j]-tempSum;
      tempSum=0.;
      
      for(i=j+1;i<=n-1;i++)
      	{
      	  for(k=0;k<=j-1)
      	    {
      	      tempSum=A[i][k]*A[k][k]*A[j][k];
      	   }
  	       A[i][j]=(A[i][j]-tempSum)/A[j][j];
  	   }
    }
  //*******************************************
  tempSum=0.;
  for (k=0;k<=n-2)
    {
      tempSum+=A[n-1][k]*A[n-1][k]*A[k][k];
    }
  A[n-1][n-1]=A[n-1][n-1]-tempSum;
}

int main()
{
  int i,j,k,n,m;
  double **A,**C,*b,*bt,*x,*y,*r;
  double temp; //variable temporal
  printf("Nombre de files de la matriu A: ");
  scanf("%d",m);
  printf("Nombre de columnes de la matriu A: ");
  scanf("%d",n);

  //Es defineixen els punters de les matrius+++++++++++++++++++
  b=(double *)malloc(m*sizeof(double));
  bt=(double *)malloc(n*sizeof(double));
  x=(double *)malloc(n*sizeof(double));
  y=(double *)malloc(n*sizeof(double));
  r=(double *)malloc(m*sizeof(double));//Vector residu
  A=(double **)malloc(m*sizeof(double));
  C=(double **)malloc(n*sizeof(double));
  if (A==NULL||C==NULL||b==NULL||bt==NULL||x==NULL||y==NULL||r==NULL) 
    {
      return 2;
    }
  for (i=0;i<m-1)
    {
        A[i]=(double *)malloc(n*sizeof(double));
        if (A[i]==NULL)return 3;
    }
    for (i=0;i<n-1)
    {
        C[i]=(double *)malloc(n*sizeof(double));
        if (C[i]==NULL)return 4;
    }
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //++++++++++++++++++++++++++ INPUT: A, b +++++++++++++++++++
  for (i=0;i<=m-1;i++)
  {
    for(j=0;j<=n-1;j++)
    {
      printf("A[%d][%d]: ",i,j);
      scanf("%lf",&A[i][j]);
    }

  }
  for (i=0;i<=m-1;i++)
  {
      printf("b[%d]: ",i);
      scanf("%lf",&b[i]);
  }
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


  //es calcula la matriu C=A*A^t
  //Calcul de producte de matrius At(nxm)*A(mxn)=C(nxn)
  for (i=0;i<=n-1)
    {
      for(j=0;j<=n-1)
      {
        temp=0;
        for(k=0;k<=m-1)
        {
            temp=temp+A[k][i]*A[k][j];
        }
        C[i][j]=temp;
      }
    }
  //+++++++++++++++++++++++++++++++++++++++++++++
  //Càclul de At*b+++++++++++++++++++++++++++++++++
  for (i=0;i<=n-1;i++)
    {
      temp=0.;

      for(k=0;k<=m-1;k++)
      {
        temp=temp+A[k][i]*b[i];
      }
      bt[i]=temp;
    }
  //+++++++++++++++++++++++++++++++++++++++++++++++
  //FACTORITZACIO de At*A = LDLt
  fact_LDL(C,n);

  //RESOLUCIO DEL SISTEMA
  //Es resol el sistema de 3 sistemes
  //Ly=b
  backwards_subs(n,y,A,bt); //es pot fer per substisució endarrera pq la matriu és simetrica
  //Dz=y. Aqui Z s'aconsegueix redefinint y
  for (i=0;i<=n-1;i++)
    {
      y[i]=y[i]*A[i][i];
    }
  //Ltx=z
  backwards_subs(n,x,A,y);

  //s'imprimeizen les solucions
  printf("\n\nSOLUCIONS\n")
  for (i=0;i<=n-1;i++)
    {
      printf("x[%d]=%.15e\n",i,x[i]);
    }
  //CALCUL DEL RESIDU
  //Ax-b=r
  for (i=0;i<=m-1;i++)
    {
      temp=0.;
      for (j=0;j<=n-1;j++)
        {
          temp=temp+A[i][j]*x[j];
        }
      r[i]=temp;
    }
  temp=0.;
  //NORMA DE r
  for (i=0;i<=m-1;m++)
    {
      temp=temp+x[i]*x[i]
    }
  printf("\nRESIDU en norma 2 de la solucio r^2: %.15e\n",temp);
  free(A);
  free(C);
  free(b);
  free(bt);
  free(x);
  free(y);
  free(r);

  return 0;
}
