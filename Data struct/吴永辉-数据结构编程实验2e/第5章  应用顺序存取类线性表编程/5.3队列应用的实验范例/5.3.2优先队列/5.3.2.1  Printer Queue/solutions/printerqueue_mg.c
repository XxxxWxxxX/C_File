/* NWERC 2006
 * Sample solution to Printer Queue
 * By Mikael Goldmann
 */
#include<stdio.h>

int main()
{
  int i, T, hd, n, pos, q[200], nprio[10], tm;
  for (scanf("%d",&T); T; --T){
    for (i=0, scanf("%d %d",&n,&pos); i<10; ++i) nprio[i]=0;    
    for (i=0; i<n && scanf("%d",q+i); ++i) nprio[q[i]]++;
    for (i=9, tm=0, hd=0; i; --i) {
      while(nprio[i]-->0) {
	while (q[hd] != i) hd=(hd+1)%n;		    
	q[hd]=0;
	++tm;
	if (hd==pos) printf("%d\n", tm);
      }
    }
  }
  return 0;  
}

