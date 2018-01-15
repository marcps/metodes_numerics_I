#include <stdio.h>
#include <math.h>
#include <stdlib.h>


void dif_div(int n, double x[n-1],double y[n-1][n-1])
{
  //INPUT: Matriu nxn amb la primera columna completa (dades del problema)
  //OUTPUT: Es completa la matriu de manera que a cada columna hi haurà un element menys
  //Fins que a l'última columna hi hagi un element
  int i,j;
  
  for (j=1;j<n;j++)
    {
      for(i=0;i<n-j;i++)
	{
	  y[i][j]=(y[i+1][j-1]-y[i][j-1])/(x[i+j]-x[i]);
	  printf("%d %d: %.8lf\n",i,j,y[i][j]);
	}
    }
}

double horner(int n, double p, double x[n], double y[n][n] )
{
  //INPUT: una x per avaluar el polinomi interpolador en un punt
  //       una matriu nxn que se li ha aplicat el mètode de diferències dividides:
  //OUTPUT: S'avalua el polinomi interpolador a un punt donat x.
  double temp;
  int i;
  temp=y[0][n-1];
  for(i=n-2;i>=0;i--)
    {
      temp=temp*(p-x[i])+y[0][i];
    }
  return temp;
}


int main(void)
{
  int n,nint,i,j;
  printf("Number of observations: " );
  scanf("%d",&n);
  double h,a,b,temp,T1,T2,z,q,extrap,z0,z1,z2,min,max,C1,arrel,prec=0.000001;
  double x[n-1],y[n-1][n-1],p,result;

  //El meu NIUB és 16677043
  printf("\n\nEscriure les abcisses de suport:\n");
  for(i=0;i<n;i++)
    {
      printf("x%d=",i);
      scanf("%lf",&x[i]);
    }
  printf("\nEscriure les corresponents ordenades de suport:\n");
  for(i=0;i<n;i++)
    {
      printf("f(x%d)=",i);
      scanf("%lf",&y[i][0]);
    }
  
  dif_div(n,x,y);
  
  printf("\n\nEscriure el punt on es desitja saber el valor del polinomi: ");
  scanf("%lf",&p);
  
  //Una vegada sabem el punt, podrem aplicar horner:
  result=horner(n,p,x,y);
  printf("\nEl resultat de P(%.3lf)= %.8lf\n ", p,result);

  //################################### 2N APARTAT ###########################

  printf("\n    INTEGRACIÓ PER TRAPEZIS\n\n");
  //N=100
  nint=100;
  a=0.;
  b=7.;
  //Calculem el pas
  
  h=(b-a)/(double)nint;
  
  temp=0.0;
  for(i=1;i<nint;i++)
    {
      z=a+(double)i*h;
      temp += horner(n,z,x,y);
    }
  
  T1=(h/2.)*(horner(n,a,x,y)+horner(n,b,x,y)+2.*temp);
  printf("n=%d -> T(f,a,b)=%.8lf\n\n",nint,T1);

  //N=200
  nint=200;
  a=0.;
  b=7.;
  //Calculem el pas
  
  h=(b-a)/(double)nint;
  
  temp=0.0;
  for(i=1;i<nint;i++)
    {
      z=a+(double)i*h;
      temp += horner(n,z,x,y);
    }
  
  T2=(h/2.)*(horner(n,a,x,y)+horner(n,b,x,y)+2.*temp);
  printf("n=%d -> T(f,a,b)=%.8lf\n\n",nint,T2);

  //Pas d'extrapolació:
  q=0.5;
  temp=pow(q,2)-1.;
  extrap=T1+((T1-T2)/temp);
  printf("extrapolació = %.8lf\n",extrap);

  //############################## APARTAT 3 ###########################
  //avaluem el polinomi en 701 punts equiespaiats
  a=0.;
  b=7.;
  h=1/100.0;
  //trobem el màxim i el mínim
  temp=0.0;
  min=0.0;
  max=0.0;
  for(i=0;i<=700;i++)
    {
      z1=a+(double)i*h;
      temp=horner(n,z1,x,y);
      if(temp<min)
	{
	  min=temp;
	}
      if(temp>max)
	{
	  max=temp;
	}
    }
  printf("\n\nminim %.8lf\n",min);
  printf("\n\nmaxim %.8lf\n",max);
  C1=(min+max)/2.;

  z1=min;
  z2=max;
  for(i=0;i<700;i++)//Fins un màxim d'iteracions, per evitar bucles eterns
    {
      z2= z1 - (((horner(n,z1,x,y)-C1)*(z1-z0))/((horner(n,z1,x,y)-C1)-(horner(n,z0,x,y)-C1)));
      printf("·Iteració %d = %lf\n",i+1,z2);
      if(fabs(z2-z1)<prec)
	{
	  arrel=z2;
	}
      else
	{
	  z0=z1;
	  z1=z2;
	}
    }
  printf("arrel=%.8lf\n",arrel);
  





  
  return 0;


}
