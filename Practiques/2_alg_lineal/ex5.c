/*Marc Pascual i Solé - Universitat de Barcelona*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void printing(double **A, int n)
{
	int i,j;
	printf("\n");
	for (i=0;i<=n-1;i++)
	{
		for (j=0;j<=n-1;j++)
		{
			printf("%lf  ",A[i][j]);
		}
		printf("\n");
	}
}
void printing_v(double *A, int n)
{
	int i;
	printf("\n");
	for (i=0;i<=n-1;i++)
	{
		printf("%lf  ",A[i]);
	}
	printf("\n");
}

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



void backwards_subs_triang_inf(int n, double *x,double **A, double *b)
{
	int i,j;
	double temp;
	x[0]=b[0];

	for(i=1;i<=n-1;i++)
	{
		temp=0.0;
		for(j=0;j<=i-1;j++)
		{
			temp=temp+x[j]*A[i][j];//ALERTA
		}
		x[i] = b[i]-temp;//Pq la matriu es triangular inferior
	}
}
void backwards_subs_triang_sup(int n, double *x,double **A, double *b)
{
	//ATENCIÓ. Es fan els càlculs a partir de la matriu A
	//Factoritzada LDLt en ella mateixa!
	int i,j;
	double temp;
	x[n-1]=b[n-1];

	for(i=n-2;i>=0;i--)
	{
		temp=0.0;
		for(j=n-1;j>=i+1;j--)
		{
			temp=temp+x[j]*A[i][j];//ALERTA
		}
		x[i] = b[i]-temp;//Pq la matriu es triangular superior
	}
}


void fact_LDL(double **A,int n)
{
  //INPUT: Matriu A (nxn)
  int i,j,k;
  double d1,tempSum;
  //+++++++++++++++++++++++++++++
  if (A==NULL)
    {
      printf("Error in memory!");
    }
  //+++++++++++++++++++++++++++++

  d1 = A[0][0];
  for (i=1;i<=n-1;i++)
    {
      A[i][0]=A[i][0]/d1;
      A[0][i]=A[i][0];//!!!!!!!!!!!!
    }
  //********************************************
  for (j=1;j<=n-2;j++)
    {
      tempSum=0.0;
      for (k=0;k<=j-1;k++)
	     {
	       tempSum = tempSum+(A[j][k]*A[j][k]*A[k][k]);
	     }
      A[j][j]=A[j][j]-tempSum;

      for(i=j+1;i<=n-1;i++)
      	{
      	  tempSum=0.0;
      	  for(k=0;k<=j-1;k++)
      	    {
      	      tempSum = tempSum+A[i][k]*A[k][k]*A[j][k];
      	   	}
  	       A[i][j]=(A[i][j]-tempSum)/A[j][j];
  	       A[j][i]=A[i][j];//!!!!!!!!!!!!!!!!!!!!!!
  	   }
    }
  //*******************************************
  tempSum=0.0;
  for (k=0;k<=n-2;k++)
    {
      tempSum = tempSum+A[n-1][k]*A[n-1][k]*A[k][k];
    }
  A[n-1][n-1]=A[n-1][n-1]-tempSum;
}

int main()
{
  int i,j,k,n,m;
  double **A,**C,*b,*bt,*x,*y,*r;
  double temp; //variable temporal
  printf("Nombre de files de la matriu A i dimensió del vector b: ");
  scanf("%d",&m);
  printf("Nombre de columnes de la matriu A: ");
  scanf("%d",&n);

  //Es defineixen els punters de les matrius+++++++++++++++++++
  b=(double *)malloc((m+1)*sizeof(double));
  bt=(double *)malloc((n+1)*sizeof(double));
  x=(double *)malloc((n+1)*sizeof(double));
  y=(double *)malloc((n+1)*sizeof(double));
  r=(double *)malloc((m+1)*sizeof(double));//Vector residu
  A=(double **)malloc((m+1)*sizeof(double));
  C=(double **)malloc((n+1)*sizeof(double));
  if (A==NULL||C==NULL||b==NULL||bt==NULL||x==NULL||y==NULL||r==NULL) 
    {
      printf("Error in Memory!");
      return 2;
    }
  for (i=0;i<=m-1;i++)
    {
       A[i]=(double *)malloc(n*sizeof(double));
       if (A[i]==NULL)
        {
          printf("Error in Memory!");
          return 3;
        }
    }
    for (i=0;i<=n-1;i++)
    {
        C[i]=(double *)malloc((n+1)*sizeof(double));
        if (C[i]==NULL)
        { 
          printf("Error in Memory!");
          return 4;
        }
    }
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //++++++++++++++++++++++++++ INPUT: A, b +++++++++++++++++++
  for (i=0;i<=m-1;i++)
  {
    for(j=0;j<=n-1;j++)
    {
      printf("A[%d][%d]: ",i+1,j+1);
      scanf("%lf",&A[i][j]);
    }

  }
  for (i=0;i<=m-1;i++)
  {
    printf("b[%d]: ",i+1);
    scanf("%lf",&b[i]);
  }
  //S'inicialitzen els vectors x(solució) i y(solució intermitja)
  for(i=0;i<=n-1;i++)
  {
  	x[i]=0.0;
  	y[i]=0.0;
  }
  printing_v(x,n);
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  //es calcula la matriu C=A^t*A
  //Calcul de producte de matrius At(nxm)*A(mxn)=C(nxn)
  for (i=0;i<=n-1;i++)
    {
      for(j=0;j<=n-1;j++)
      {
        temp=0.0;
        for(k=0;k<=m-1;k++)
        {
            temp=temp+A[k][i]*A[k][j];
        }
        C[i][j]=temp;
      }
    }
    printf("\nMatriu reduida:\n");
    printing(C,n);/////////////////////////////////////////////////////////
  //+++++++++++++++++++++++++++++++++++++++++++++
  //Càclul de At*b+++++++++++++++++++++++++++++++++
  for (i=0;i<=n-1;i++)
    {
      temp=0.0;

      for(k=0;k<=m-1;k++)
      	{
        	temp=temp+A[k][i]*b[k];
      	}
      bt[i]=temp;
    }
  printf("\nVector reduit bt:\n");
  printing_v(bt,n);///////////////////////////////////////////////////////

  //+++++++++++++++++++++++++++++++++++++++++++++++
  //FACTORITZACIO de At*A = LDLt
  fact_LDL(C,n);
  printf("\nMatriu Factoritzada LDLt: \n");
  printing(C,n);//////////////////////////////////////////////////////////
  
  //RESOLUCIO DEL SISTEMA
  //Es resol el sistema de 3 sistemes
  //Ly=b
  backwards_subs_triang_inf(n,y,C,bt); //es pot fer per substisució endarrera pq la matriu és simetrica
  printf("\nPrimera Solució Ly=b: \n");
  printing_v(y,n);
  //Dz=y. Aqui Z s'aconsegueix redefinint y
  for (i=0;i<=n-1;i++)
    {
      y[i]=y[i]*C[i][i];
    }
  printf("\nSegona solució Dy=z:\n");
  printing_v(y,n);


  //Ltx=z
  backwards_subs_triang_sup(n,x,C,y);


  //s'imprimeizen les solucions
  printf("\n\n              SOLUCIONS\n");
  for (i=0;i<=n-1;i++)
    {
      printf("x[%d]=%.15e\n",i,x[i]);
    }
  //***********************************************************************
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
      temp=temp+x[i]*x[i];
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
