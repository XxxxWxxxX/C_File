/* my solution to the domino Problem */


#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) ((a) >= (b) ? (a) : (b))
#define MIN(a,b) ((a) <= (b) ? (a) : (b))
#define MAX_GRAPH 100


/* Globals */

FILE *inp;
int m,n,l,found;
int graph[MAX_GRAPH][MAX_GRAPH];
int time[MAX_GRAPH];
int caseno=1;
int last[2][MAX_GRAPH];

void solve_case()
{
  int i,j;
  double lastfall = 0.0;
  double between; /* hold falling time of inbetween stones */
  int solnum;

  
  /*init*/
  for(i=0; i<n; i++) {
    time[i] = -1;
    last[0][i] = -1;
    last[1][i] = -1;
  }
  time[0] = 0;
  last[0][0] = 0; /* he is the first to fall */

  /* looking for last key stone(s) */
  i=0;
  while (i<n) {
    for(j=i+1; j<n; j++) {
	if (graph[i][j] > -1) {
	  if ((time[i] > -1) && \
	      ((time[j] > time[i]+graph[i][j]) || time[j] == -1)) {
	    time[j] = time[i]+graph[i][j];
	    i = -1;
	    break;
	  } else if ((time[j] > -1) && \
		     ((time[i] > time[j]+graph[i][j]) || time[i] == -1)) {
	    time[i] = time[j]+graph[i][j];
	    i = -1;
	    break;
	  }
	}
      }
    i++;
  }
  lastfall = 0.0;
  for(i=0; i<n; i++) {
    lastfall = MAX(lastfall, (double)time[i]);
  }

  /* collect the solutions */
  solnum = 0;
/*  printf("lastfall = %.1f\n", lastfall); */
  for (i=0; i<n; i++) {
/*    printf("Stone #%d at %d\n", i+1, time[i]); */
    if ((double) time[i] == lastfall) {
      solnum++;
      last[0][solnum-1] = i;
      last[1][solnum-1] = -1;
/*      printf(" last: %d at %.1f\n", i+1,lastfall); */
    } else if (time[i] == -1) {
      printf("Graph not fully connected !\n");
    }
  }
  
  /* cheking for even later stone(s) between key stones */
  for(i=0; i<n; i++) {
    for(j=i+1; j<n; j++) {
      if (graph[i][j] > -1) {
	between = (graph[i][j] - abs(time[i]-time[j]))/2.0 + \
	            MAX(time[i], time[j]);
	if (between > lastfall) { 
	  solnum = 1;
	  lastfall = between;
	  last[0][solnum-1] = i;
	  last[1][solnum-1] = j;
	} else if (between == lastfall) {
	  l=found=0;
	  while ((l<solnum) && !found) {
	    found = (((last[0][l] == j) && (last[1][l] == -1)) || \
		     ((last[0][l] == i) && (last[1][l] == -1)));
	    l++;
	  }
	  if (!found) {
	    last[0][solnum] = i;
	    last[1][solnum] = j;
	    solnum++;
	  }
	}
      }
    }
  }
  
  /* print the result */
/*  printf("Domino System #%i (%i solutions)\n",caseno++,solnum); */
  for (i=0; i<solnum; i++) {
     if (last[1][i] <= -1 ) {
      printf("#%i The last stone falls after %.1f seconds, ", caseno, lastfall);
      printf("at key stone %i.\n",last[0][i]+1);
    } else {
      printf("#%i The last stone falls after %.1f seconds, ", caseno, lastfall);
      printf("between key stones %i and %i.\n", last[0][i]+1, last[1][i]+1);
      printf("#%i The last stone falls after %.1f seconds, ", caseno, lastfall);
      printf("between key stones %i and %i.\n", last[1][i]+1, last[0][i]+1);
    }
  }
  caseno++;
}

/* the following is taken from your solution */

void skip_line() { while(getc(inp) >= ' '); }

int read_case()
{
  int i,j,v1,v2,w;

  fscanf(inp,"%d %d",&n,&m); skip_line();
  if(n == 0 && m == 0) return 0;
  for(i=0;i<n;i++)
    for(j=i;j<n;j++) graph[i][j] = -1;
  for(i=0;i<m;i++)
    {
      fscanf(inp,"%d %d %d",&v1,&v2,&w); skip_line();
      v1--; v2--;
      graph[MIN(v1,v2)][MAX(v1,v2)] = w;
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

