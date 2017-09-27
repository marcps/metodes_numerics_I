/* EXERCICI 2 - Mètodes Numèrics 1 - Marc Pascual i Solé NIUB: 16677043*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*Errors de representació entre 1/8 i 8 considerant el valor d'una variable double com el real */

float error(double a, float a_aprox, int f)
/*f és simplement una variable que tria si es vol l'error relatiu o absolut*/
{
  float err_abs, err_rel;
  err_abs = fabs(a-a_aprox);
  err_rel = (err_abs)/a_aprox;
  if (f == 1)
    {
     return err_abs;
    }
  if (f==-1)
    {
      return err_rel;
    }
}

int main ()
{
  float x;
  double x_real;
  int i;
  /*interval 1/8 - 8*/
  x = 1.0/8.0;
  x_real = 1.0/8.0;

  for (i=1;i<=1000;i++)
    {
      printf("Valor x=%e , error absolut=%e, error relatiu=%e\n",x, error(x_real,x, 1), error(x_real,x,-1));
      x = 1.0/8.0 + (63.0*i)/8000.0;
      x_real = 1.0/8.0 + (63.0*i)/8000.0;
    }
  return 0;
}
