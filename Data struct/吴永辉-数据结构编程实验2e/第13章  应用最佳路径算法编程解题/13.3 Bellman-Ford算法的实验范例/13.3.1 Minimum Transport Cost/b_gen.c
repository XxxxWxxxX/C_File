#include <stdio.h>
#include <stdlib.h>

#define POCET_ZADANI 10
#define POCET_OTAZEK_V_ZADANI (N*10)



int
main()
{
  int N; 
   
  int zad;
  int i,j;

  /* nahodne ale deterministycky */
  srand(0);

  for(zad=POCET_ZADANI; zad--;)
  {
    N = rand() % 30 + 5;
   printf("%i\n", N);
    for(i=N;i--;)
    {
      for(j=N;j--;)
      {
        if( i == j)
        {
          printf("0 ");
        }
        else
        {
          printf("%i ", rand()%40 + 1);
        }
      }
      printf("\n");
    }
    for(i=N;i--;)
    {
      printf("%i ", rand()%40 + 1);
    }
    printf("\n");
    for(i=POCET_OTAZEK_V_ZADANI;i--;)
    {
      printf("%i %i\n", (rand()%N) + 1, (rand()%N) + 1);
    }
    printf("-1 -1\n");
  }/* zad */
  printf("0\n");
  return 0;
} /* mail */


 
