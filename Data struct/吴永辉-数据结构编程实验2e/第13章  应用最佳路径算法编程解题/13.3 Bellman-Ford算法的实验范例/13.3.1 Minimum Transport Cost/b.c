/*
 *  mesta
 */

#include <stdio.h>
#include <values.h>

#define TWN_MX 270
#define INFTY (MAXINT/8)

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

typedef struct t_route
{
  int nexthop;
  int cost;
} t_route;

/*
 *  route[from][to].cost cena
 *                 .nexthop prez
 */
t_route route[TWN_MX][TWN_MX];

/*
 * cost[from][to] cena
 * cost[in][in] cena za pobyt
 */
int cost[TWN_MX][TWN_MX];

/*
 * pocet mest 
 */
int N;

/*
 * cost je vyplneno
 */
void
init_route()
{
  int i,j,k, l;
  int tmp_do_k, cur_do_k;

  /*
   * inicializace
   */
  for(i=N;i--;)
  for(j=N;j--;)
  {
    if(j == i)
    {
      route[i][i].cost = 0;
      route[i][i].nexthop = i;
      continue;
    }

    if( cost[i][j] >= 0 )
    {
      route[i][j].cost = cost[i][j];
      route[i][j].nexthop = j;
    }
    else
    {
      route[i][j].cost = INFTY;
      route[i][j].nexthop = -1;
    }
  }

  /* N iteraci */ 
  for(l=N-1;l--;) 
  {
    /* pro kazde mesto  */
    for(i=N;i--;)
    {
      /* koukni k sousedovi */
      /* updatni routovaci tabulku podle sousedu */
      for(j=N;j--;)
      {
        /* pouze sousedy */
        if( i == j || cost[i][j] <= 0 ) continue;  

        /* updadni pres vsechny polozky */
        for(k = N;k--;)
        {
          tmp_do_k = route[j][k].cost + cost[j][j] + cost[i][j];
          cur_do_k = route[i][k].cost;
          if( tmp_do_k < cur_do_k ||
              ( tmp_do_k == cur_do_k && route[i][k].nexthop > j))
          {
            route[i][k].cost = tmp_do_k;
            route[i][k].nexthop = j;
          }
        }
      }
    }
  }
} /* init_route */



int
read_zad()
{
  int i,j;
  scanf("%i", &N);

  if( N == 0 )
  {
    return 0;
  }

  for(i=0;i<N;i++)
  for(j=0;j<N;j++)
  {
    scanf("%i", &cost[i][j]);
  }
  for(i=0;i<N;i++)
  {
    scanf("%i", &cost[i][i]);
  }
  return 1;

} /* read_zad */

void
solve()
{
  int from, to, f, lastf;
  
  while(1)
  {
    scanf("%i %i", &from, &to);
    if( from == -1 )
    {
      return;
    }

    printf("From %i to %i :\n", from, to); 

    from--;
    to--;

    printf("Path: %i",from + 1);

    lastf = from;
    if(from != to )
    {
      
    for(
      f = route[from][to].nexthop;
      f != to;
      f = route[f][to].nexthop)
    {
      if(f == lastf)
      {
        printf("*");
        break;
      }
      printf("-->%i", f + 1);
      lastf= f;
    }
    printf("-->%i\n", f + 1);
    }
    else printf("\n");
    
    printf("Total cost : %i\n\n", route[from][to].cost);
    
  }
} /* solve */

void 
print_route_table()
{
  int i, j;
  for(j=0;j<N;j++)
  {
    printf("    %2i     ", j);
  }
  printf("\n");
  for(i=0;i<N;i++)
  {
    printf("%2i:",i);
    for(j=0;j<N;j++)
    {
      printf("%2i[%2i](%2i) ", route[i][j].cost, route[i][j].nexthop, cost[i][j]);
    }
    printf("\n");
  }
} /* print_route_table */


int
main()
{
  while(read_zad())
  {
    init_route();
    solve();
  }
  return 0;
} /* main */


 

