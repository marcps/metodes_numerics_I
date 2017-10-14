/* EXERCICI 1 - Mètodes Numèrics 1 - Marc Pascual i Solé NIUB: 16677043*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

/* suposarem que les operacions elementals són +,-,x,% */

void suma(signed int x)
{
  int X_MAX;
  while (x < x+1)
    {
      /*Sumem 1 fins que hi hagi overflow*/
      x = x + 1;
      if (x+1<x)
	  {
	    X_MAX = x;
	    printf("The Maximum represented integer number is %d \n",X_MAX);
	  }
    }
}

void resta(signed int y)
{
  int Y_MIN;
  while (abs(y) < abs(y-1))
    {
      y -= 1;
      if(abs(y) > abs(y-1))
	{
	  Y_MIN = y;
	  printf("The Minimum represented integer number is: %d \n", Y_MIN);
	}
    }
}

/*Funció que serveix per veure què passa quan es surt de rang*/
int factorial(int x)
{
  int i;
  int result;
  result = 1;
  for (i=1; i<=x; i++)
    {
      result *= i;
    }
  return result;
}


int main()
{
  signed int a;
  int b,x,n;
  a=1;
  suma(a);
  resta(-a);
  /*Constants de la llibreria limits.h*/
  printf("Constant INT_MIN:%d\nConstant INT_MAX: %d\n",INT_MIN, INT_MAX);
  /*Calculs Aritmètics fora del rang*/
  b = factorial(300);
  printf("%d\n",b);

  /*Trobarem la n tal que Zmod(n) sigui el rang de representació*/
  x=1;
  n=1;
  while (x<2*x)
    {
      x *= 2;
      if (x>2*x){printf("El rang de representació és Z(mod(2^%d))\n",n+1);}
      n += 1;
    }
  return 0;
}
