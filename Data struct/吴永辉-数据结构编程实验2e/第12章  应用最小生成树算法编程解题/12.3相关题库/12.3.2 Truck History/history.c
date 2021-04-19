/*
 *	Solution to Trucks history - using array for each distance (faster)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 2000
#define CODELEN 7

struct pos {
    	int l;
	int p;
};

int n;
char codes[MAXN][CODELEN+3];
char d[MAXN][MAXN];
char got[MAXN];

int en[CODELEN+1];
int eout[CODELEN+1][MAXN];

struct pos cp[MAXN];

inline void remove_arr(int l, int p1)
{
	eout[l][p1] = eout[l][--en[l]];
	cp[eout[l][p1]].p = p1;
}

/* Find minimum spanning tree */
int min_tree(void)
{
	int i, j, k, dist, to;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
			dist = 0;
			for (k = 0; k < 7; k++)
				dist += codes[i][k] != codes[j][k];
			d[i][j] = dist;
		}
	for (i = 1; i <= CODELEN; i++)
	    	en[i] = 0;
	for (i = 0; i < n; i++)
	    	cp[i].l = CODELEN+1;
	
	dist = 0;
	memset(got, 0, n);
	eout[0][en[0]++] = 0;
	cp[0].p = cp[0].l = 0;
	while (1) {
		for (i = 0; i <= CODELEN && !en[i]; i++);
		if (i > CODELEN)
		   	return dist;
		to = eout[i][0];
		remove_arr(i, 0);
		got[to] = 1;
		dist += i;
		for (i = 0; i < n; i++)
			if (!got[i] && cp[i].l > d[to][i]) {
			    	eout[d[to][i]][en[d[to][i]]++] = i;
				if (cp[i].l < CODELEN+1)
				    	remove_arr(cp[i].l, cp[i].p);
				cp[i].l = d[to][i];
				cp[i].p = en[d[to][i]]-1;
			}
			    	
	}
	return 0;
}

int main(void)
{
	int i;
	char buf[256];

	while (1) {
		gets(buf);
		sscanf(buf, "%d", &n);
		if (!n)
			break;
		for (i = 0; i < n; i++) {
			gets(codes[i]);
			codes[i][8] = 0;
		}
		printf("The highest possible quality is 1/%d.\n", min_tree());
	}
	return 0;
}
