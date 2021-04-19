#include <stdio.h>
#include <stdlib.h>

#define N_SETS 10
#define MAX_COMP 5000
#define QPLINK 20

void gen(void)
{
  int n_com = rand () % MAX_COMP + 1;
  int n_link = (rand () % 5 + 1) * n_com;
  int i;
 
  printf ("%d\n", n_com);
  for (i = 0; i < n_link; i++)
    {
      int nq = rand () % QPLINK;

      while (nq--)
	printf ("q %d %d\n", rand () % n_com + 1, rand () % n_com + 1);
      printf ("c %d %d\n", rand () % n_com + 1, rand () % n_com + 1);
    }
}

int main(void)
{
  int i;

  for (i = 0; i < N_SETS; i++)
    gen ();
  printf ("%d\n", 0);

  return 0;
}
