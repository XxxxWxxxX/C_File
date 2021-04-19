/* Solution: VILLA */

#include <stdio.h>
#include <stdlib.h>

#define MAX_ROOMS 10
#define QUEUE_LEN 11000
#define CODENUM (1<<MAX_ROOMS)*MAX_ROOMS

typedef struct 
{
  int exnum,lightnum;
  int exit[MAX_ROOMS];
  int light[MAX_ROOMS];
} room;

FILE *inp;
int n,goal;
int queue[QUEUE_LEN],qhead,qtail;
short sit[CODENUM],back[CODENUM];
room r[MAX_ROOMS];
int caseno = 1;

/* Queue management */

void qinit() { qhead = qtail = 0; }

int qempty() { return qhead == qtail; }

void qpush(int pos, short dist, short bck)
{
  if(sit[pos] != -1)
    {
      /* printf("*** INPUT ERROR: multiple solutions!\n"); */
      return;
    }
  sit[pos] = dist;
  back[pos] = bck;
  queue[qtail] = pos;
  qtail = (qtail+1)%QUEUE_LEN;
  if(qtail == qhead)
    {
      printf("*** ERROR: Queue size too small!\n");
    }
}

int qpop()
{
  int tmp;

  if(qhead == qtail) return -1;
  tmp = queue[qhead];
  qhead = (qhead+1)%QUEUE_LEN;
  return tmp;
}

/* Converter for integer<->situation */

int situation2int(int pos, int *light)
{
  int b,code,i;
  
  for(code=i=0,b=1;i<n;i++,b<<=1)
    if(light[i]) code += b;
  return code*n+pos;
}

void int2situation(int code, int *pos, int *light)
{
  int i;

  *pos = code%n;
  code /= n;
  for(i=0;i<n;i++,code>>=1)
    light[i] = code & 1;
}
 
void print_sol(int code)
{
  if(back[code] == -1) return;
  if(back[code] < n) /* movement */
    {
      print_sol(n*(code/n)+back[code]);
      printf("- Move to room %d.\n",code%n+1);
    }
  else /* switch light */
    {
      print_sol(((code/n)^(1<<(back[code]-n)))*n+code%n);
      printf("- Switch %s light in room %d.\n",
	     (code/n)&(1<<(back[code]-n))?"on":"off",back[code]-n+1);
    }
}

/* We solve the problem by brute force. By breadth-first search we
   enumerate all possible cases */

void solve_case()
{
  int i;
  int light[MAX_ROOMS],pos,code,dist;

  for(i=0;i<(1<<n)*n;i++) sit[i] = -1;
  pos = 0; light[0] = 1;
  for(i=1;i<n;i++) light[i] = 0;
  code = situation2int(pos,light);
  dist = 0;
  qinit();
  qpush(code,dist,-1);
  while(!qempty())
    {
      code = qpop(); dist = sit[code];
      int2situation(code,&pos,light);

      /* compute successors */

      /* a) move into another room */

      for(i=0;i<r[pos].exnum;i++)
	if(light[r[pos].exit[i]]) /* enter only rooms that have light */
	  {
	    code = situation2int(r[pos].exit[i],light);
	    qpush(code,dist+1,pos);
	  }

      /* b) turn on/off lights */

      for(i=0;i<r[pos].lightnum;i++)
	if(r[pos].light[i] != pos) /* do not turn off light in current room */
	{
	  light[r[pos].light[i]] = 1-light[r[pos].light[i]];
	  code = situation2int(pos,light);
	  qpush(code,dist+1,n+r[pos].light[i]);
	  light[r[pos].light[i]] = 1-light[r[pos].light[i]];
	}
    }

  /* output the solution */

  printf("Villa #%d\n",caseno++);
  for(i=0;i<n-1;i++) light[i] = 0;
  light[n-1] = 1;
  code = situation2int(n-1,light);
  if(sit[code] == -1)
    printf("The problem cannot be solved.\n\n");
  else
    {
      printf("The problem can be solved in %d steps:\n",sit[code]);
      print_sol(code);
      printf("\n");
    }
}

/* read in the data */

void skip_line() { while(getc(inp) >= ' '); }

int comp_int(const void *a, const void *b) 
{ 
  return *((const int *)a)-*((const int *)b);
}

int read_case()
{
  int i,d,s,a,b;

  fscanf(inp,"%d %d %d",&n,&d,&s); skip_line();
  if(n == 0) return 0;
  for(i=0;i<n;i++)
    r[i].exnum = r[i].lightnum = 0;
  for(i=0;i<d;i++)
    {
      fscanf(inp,"%d %d",&a,&b); skip_line();
      r[a-1].exit[r[a-1].exnum++] = b-1;
      r[b-1].exit[r[b-1].exnum++] = a-1;
    }
  for(i=0;i<s;i++)
    {
      fscanf(inp,"%d %d",&a,&b); skip_line();
      r[a-1].light[r[a-1].lightnum++] = b-1;
    }
  /* This is completely unnecessary, but gives nicer (= ordered) output
     later */
  for(i=0;i<n;i++)
    {
      qsort(r[i].exit,r[i].exnum,sizeof(int),comp_int);
      qsort(r[i].light,r[i].lightnum,sizeof(int),comp_int);
    }
  return 1;
}

int main()
{
  inp = fopen("villa.in","r");
  while(read_case()) solve_case();
  fclose(inp);
  return 0;
}

