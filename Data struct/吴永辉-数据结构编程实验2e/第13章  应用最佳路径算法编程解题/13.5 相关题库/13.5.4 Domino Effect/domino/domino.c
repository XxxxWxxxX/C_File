/* Solution: DOMINO */

#include <stdio.h>
#include <stdlib.h>

#define MAX_GRAPH_SIZE 500

FILE *inp;

int m,n;
int graph[MAX_GRAPH_SIZE][MAX_GRAPH_SIZE];
int time[MAX_GRAPH_SIZE];
int caseno = 1;

int min(int a, int b) { return a>b?b:a; }
int max(int a, int b) { return a<b?b:a; }

void solve_case()
{
  int ch,i,j,m1,m2,solnum;
  double tim,maxtim;
  
  /* 1. Compute for each key stone the time until the stone falls down */

  for(i=1;i<n;i++) time[i] = -1;
  time[0] = 0; ch = 1;
  while(ch)
    {
      ch = 0;
      for(i=1;i<n;i++)
	for(j=0;j<n;j++)
	  if(graph[j][i] >= 0 && time[j] >= 0 &&
	     (time[i] < 0 || time[j] + graph[j][i] < time[i]))
	    {
	      time[i] = time[j] + graph[j][i];
	      ch = 1;
	    }
    }

  /* 2. Check for the maximum among these times */

  maxtim = -1; solnum = 0;
  for(i=0;i<n;i++)
    {
      if(time[i] >= 0 && (double) time[i] >= maxtim) 
	if(time[i] > maxtim)
	  { maxtim = (double) time[i]; m1 = i; m2 = -1; solnum = 1; }
	else solnum++;
      if(time[i] == -1) 
	printf("*** INPUT ERROR: graph is not connected!\n");
    }

  /* 3. Check whether the last stone falls on a row between two key stones */

  for(i=0;i<n;i++)
    for(j=i;j<n;j++)
      if(time[i] >= 0 && time[j] >= 0 && graph[i][j] >= 0)
	{
	  tim = 0.5*(graph[i][j] - abs(time[i]-time[j])) +
	    (double) max(time[i],time[j]);
	  if(tim == maxtim && tim > time[i] && tim > time[j]) solnum++;
	  if(tim > maxtim)
	    { maxtim = tim; m1 = i; m2 = j; solnum = 1; }
	}

  /* 4. Output the solution */

  printf("System #%d\n",caseno++);
  if(solnum != 1)
    printf("*** INPUT ERROR: Output is ambiguous.\n");
  printf("The last domino falls after %.1f seconds, ",maxtim);
  if(m2 < 0)
    printf("at key domino %d.\n\n",m1+1);
  else
    printf("between key dominoes %d and %d.\n\n",m1+1,m2+1);
}

void skip_line() { while(getc(inp) >= ' '); }

int read_case()
{
  int i,j,v1,v2,w;

  fscanf(inp,"%d %d",&n,&m); skip_line();
  if(n == 0 && m == 0) return 0;
  for(i=0;i<n;i++)
    for(j=0;j<n;j++) graph[i][j] = -1;
  for(i=0;i<m;i++)
    {
      fscanf(inp,"%d %d %d",&v1,&v2,&w); skip_line();
      v1--; v2--;
      graph[v1][v2] = graph[v2][v1] = w;
    }
  return 1;
}

int main()
{
  inp = fopen("domino.in","r");
  while(read_case()) solve_case();
  fclose(inp);
  return 0;
}

