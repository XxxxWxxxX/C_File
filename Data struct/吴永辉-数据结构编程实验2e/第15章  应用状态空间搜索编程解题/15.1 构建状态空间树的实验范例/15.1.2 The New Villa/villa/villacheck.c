/* Solution Checker: VILLA */

/* Note: One should use 'diff in out | fgrep -v -' first. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROOMS 10
#define QUEUE_LEN 11000
#define CODENUM (1<<MAX_ROOMS)*MAX_ROOMS

typedef struct 
{
  int exnum,lightnum;
  int exit[MAX_ROOMS];
  int light[MAX_ROOMS];
} room;

FILE *inpp;
int n,goal;
int queue[QUEUE_LEN],qhead,qtail;
short sit[CODENUM],back[CODENUM];
room r[MAX_ROOMS];
int caseno = 1;

/* read one line from stdin */

int line = 0,
  err = 0;

void readline(char *buf, int removeblanks)
{
  line++;
  
  if(feof(stdin))
   { 
      printf("line %2d\n *** WRONG ANSWER: inpput too short!\n",line); 
      exit(1);
    }
  if(!fgets(buf,1000,stdin)) strcpy(buf,"***EOF***");

  /* remove trailing blanks */
  if(removeblanks)
    while(*buf && buf[strlen(buf)-1] < 33) buf[strlen(buf)-1] = 0;
  else
    while(*buf && buf[strlen(buf)-1] < 32) buf[strlen(buf)-1] = 0;
}

/* Queue management */

void qinit() { qhead = qtail = 0; }

int qempty() { return qhead == qtail; }

void qpush(int pos, short dist, short bck)
{
  if(sit[pos] != -1)
    {
      /* printf("*** inppUT ERROR: multiple solutions!\n"); */
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
 
void check_sol(int len)
{
  int i,j,k,pos;
  int light[MAX_ROOMS];
  char inbuf[1000],outbuf[1000];

  light[0] = 1; pos = 0;
  for(i=1;i<n;i++) light[i] = 0;
  for(i=0;i<len;i++)
    {
      readline(inbuf,0);
      for(j=0;j<n;j++)
	{
	  sprintf(outbuf," - Move to room %d.",j+1);
	  if(!strcmp(inbuf,outbuf))
	    {
	      for(k=0;k<r[pos].exnum;k++)
		if(r[pos].exit[k] == j && light[j])
		  {
		    pos = j;
		    goto ok;
		  }
	      printf("line %2d > %s\n *** WRONG ANSWER: Illegal move!\n",
		     line,inbuf);
	      exit(1);
	    }
	}
      for(j=0;j<n;j++)
	{
	  sprintf(outbuf," - Switch on light in room %d.",j+1);
	  if(!strcmp(inbuf,outbuf))
	    {
	      for(k=0;k<r[pos].lightnum;k++)
		if(r[pos].light[k] == j && !light[j])
		  {
		    light[j] = 1;
		    goto ok;
		  }
	      printf("line %2d > %s\n *** WRONG ANSWER: Illegal light on!\n",
		     line,inbuf);
	      exit(1);
	    }
	  sprintf(outbuf," - Switch off light in room %d.",j+1);
	  if(!strcmp(inbuf,outbuf))
	    {
	      for(k=0;k<r[pos].lightnum;k++)
		if(r[pos].light[k] == j && light[j])
		  {
		    light[j] = 0;
		    goto ok;
		  }
	      printf("line %2d > %s\n *** WRONG ANSWER: Illegal light off!\n",
		     line,inbuf);
	      exit(1);
	    }
	}
      printf("line %2d > %s\n *** ???: Not a valid instruction!\n",
	     line,inbuf);
      err = 1;
    ok: ;
    }
  if(pos != n-1)
    {
      printf(" *** WRONG ANSWER: Not in Room %d!\n",n);
      exit(1);
    }
  if(!light[n-1])
    {
      printf(" *** WRONG ANSWER: No light in Room %d!\n",n);
      exit(1);
    }
  for(i=0;i<n-1;i++)
    if(light[i]) 
      {
	printf(" *** WRONG ANSWER: Still light in Room %d!\n",i+1);
	exit(1);
      }
}

/* We solve the problem by brute force. By breadth-first search we
   enumerate all possible cases */

void solve_case()
{
  int i;
  int light[MAX_ROOMS],pos,code,dist;
  char tmpbuf[1000],inbuf[1000],outbuf[1000];

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

  readline(inbuf,0);
  sprintf(outbuf,"Villa #%d",caseno++);
   if(strcmp(inbuf,outbuf))
    {
      printf("line %2d > %s\n        < %s\n",line,inbuf,outbuf);
      err = 1;
    }

  for(i=0;i<n-1;i++) light[i] = 0;
  light[n-1] = 1;
  code = situation2int(n-1,light);
  readline(inbuf,0);
  if(sit[code] == -1)
    {
      sprintf(outbuf,"The problem cannot be solved.");
      if(strcmp(inbuf,outbuf))
	{
	  printf("line %2d > %s\n        < %s\n",line,inbuf,outbuf);
	  err = 1;
	}
    }
  else
    {
      sprintf(outbuf,"The problem can be solved in %d steps:",sit[code]);
      if(strcmp(inbuf,outbuf))
	{
	  printf("line %2d > %s\n        < %s\n",line,inbuf,outbuf);
	  err = 1;
	}
      check_sol(sit[code]);
    }
  readline(inbuf,0);
  if(*inbuf)
    {
      printf("line %2d > %s\n        < \n",line,inbuf);
      err = 1;
    }
}

/* read in the data */

void skip_line() { while(getc(inpp) >= ' '); }

int comp_int(const void *a, const void *b) 
{ 
  return *((const int *)a)-*((const int *)b);
}

int read_case()
{
  int i,d,s,a,b;

  fscanf(inpp,"%d %d %d",&n,&d,&s); skip_line();
  if(n == 0) return 0;
  for(i=0;i<n;i++)
    r[i].exnum = r[i].lightnum = 0;
  for(i=0;i<d;i++)
    {
      fscanf(inpp,"%d %d",&a,&b); skip_line();
      r[a-1].exit[r[a-1].exnum++] = b-1;
      r[b-1].exit[r[b-1].exnum++] = a-1;
    }
  for(i=0;i<s;i++)
    {
      fscanf(inpp,"%d %d",&a,&b); skip_line();
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

int main(int argc, char **argv)
{
  char buf[1000];

  inpp = fopen(argv[1],"r");
  freopen(argv[2], "r", stdin);
  while(read_case()) solve_case();
  fclose(inpp);
  fgets(buf, 1000, stdin);
  while(!feof(stdin))
    {
      fgets(buf,1000,stdin);
      while(*buf && buf[strlen(buf)-1] < 32) buf[strlen(buf)-1] = 0;
      if(*buf)
	{
	  printf("line %2d > %s\n *** PRESENTATION ERROR: File too long\n",++line,buf);
	  err = 1;
	}
    }
  if(!err) printf(" *** CORRECT!\n");
  return err;
}


