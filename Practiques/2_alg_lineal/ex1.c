/* EXERCICI 1 - Mètodes Numèrics 1 - Marc Pascual i Solé 16677043*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* suposarem que les operacions elementals són +,-,x,% */

void suma(int x)
{
  int x_max;
  while (x < x+1)
    {
      /*Sumem 1 fins que hi hagi overflow*/
      x = x + 1;
      if (x+1<x)
	  {
	    x_max = x;
	    printf("The Maximum represented number is %d \n",X_MAX);
	  }
    }
}

void resta(int y)
{
  int Y_MIN;
  while (abs(y) < abs(y-1))
    {
      y -= y;
      if(abs(y) > abs(y-1))
	{
	  Y_MIN = y;
	  printf("The Minimum represented number is: %d \n", Y_MIN);
	}
    }
}

int main()
{
  int a;
  a=1;
  suma(a);
  resta(a);

  return 0;
}
