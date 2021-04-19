#include <stdio.h>

#define MN 10000

int n, i;
int con, ncon;

struct vertex
{
  struct vertex *father;
  int size;
};


struct vertex v[MN];

char buf[100];

struct vertex *find (int i)
{
  struct vertex *pv = v + i, *av, *rv;

  for (av = pv; av->father; av = av->father)
    continue;
  rv = av;

  for (av = pv; av != rv; av = pv)
    {
      pv = av->father;
      av->father = rv;
    }

  return rv;
}

void join(struct vertex *v1, struct vertex *v2)
{
  if (v1 == v2)
    return;

  if (v1->size < v2->size)
    v1->father = v2;
  else
    v2->father = v1;
}

int main(void)
{
  char c[2];
  int f, t;

  gets (buf);
  while (1)
    {
      sscanf (buf, "%d", &n);
      if (n == 0)
	return 0;

      for (i = 0; i < n; i++)
	{
	  v[i].father = NULL;
	  v[i].size = 1;
	}
      con = ncon = 0;

      while (1)
	{
	  gets (buf);
	  if (*buf == 'c')
	    {
	      sscanf (buf, "%s %d %d", c, &f, &t);
	      join (find (f - 1), find (t - 1));
	    }
	  else if (*buf == 'q')
	    {
	      sscanf (buf, "%s %d %d", c, &f, &t);
	      if (find (f - 1) == find (t - 1))
		con++;
	      else
		ncon++;
	    }
	  else
	    {
	      printf ("%d, %d\n", con, ncon);
	      break;
	    }
	}
    }
}
