/* EXERCICI 4 - Mètodes Numèrics 1 - Marc Pascual i Solé NIUB: 16677043*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Estudi de convergència de dues sèries*/

float serie_1(int num, int ff)
/*S'haurà d'específicar el nombre fins on es volen sumar els termes mitjançant la variable ff*/
{
  int i;
  float result;
  result = 1.;
  if (ff==1)
    /*ho sumarem de i=1,....,num*/
    {
      for (i==2;i<=num;i++)
	{
	  result += (1.0/i);
	}
      return result;
    }
  if (ff==-1)
    /*ho sumarem de i=num,.....,1*/
    {
      for (i==num;i>=2;i--)
	{
	  result += 1.0/i;
	}
      return result;
    }
}


int main()
{
  float result;
  int num;

  /*1a serie*/
  num = 1000;/* 1000 vegades*/
  result = serie_1(num,1);
  printf("Resultat per 1000 iteracions: %f\n", result);

  num = 10000000; /*10000000 iteracions*/
  result = serie_1(num,1);
  printf("Resultat per 10000000 iteracions: %f\n", result);

  /*Ara es farà la sèrie inversa*/
  result = serie_1(num,-1);
  printf("Resultat per 10000000 iteracions (inversa): %f\n", result);

}
