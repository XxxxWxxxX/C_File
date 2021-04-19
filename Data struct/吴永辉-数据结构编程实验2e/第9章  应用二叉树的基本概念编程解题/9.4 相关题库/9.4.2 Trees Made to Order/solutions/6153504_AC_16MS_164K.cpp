#include <stdio.h>
#include <stdlib.h>

const int max_nodes = 20;

int num[ max_nodes];

void printTree( int n);

int main() 
{
	num[0] = num[1] = 1;
	for (int i = 2; i < max_nodes; i++)
	{
		num[i] = 0;
		for (int k = 0; k < i; k++) num[i] += num[k] * num[i - 1 - k];
	}

	while (true)
	{
		int n;
		scanf("%d", &n);
		if ( n == 0) break;
		printTree(n);
		printf("\n");
	}
}

void printTree( int id)
{
	int T_nodes = 0;
	
	int tmp = 0;
	while ( tmp < id)
	{
		++T_nodes;
		tmp += num[ T_nodes];
	}


	if ( T_nodes <= 1)
	{
		printf("X");
		return;
	}

	id = id - tmp + num[ T_nodes];

	int L_nodes = 0;
	tmp = num[ T_nodes - 1];
	while ( tmp < id)
	{
		++L_nodes;
		tmp = tmp + num[ L_nodes ] * num[ T_nodes - 1 - L_nodes];
	}

	int R_nodes = T_nodes - 1 - L_nodes;

	id = id - tmp + num[ L_nodes] * num[ R_nodes];
	
	int tmpL = id / num[ R_nodes];
	if ( id % num[ R_nodes] != 0) ++tmpL;
	int tmpR = id % num[ R_nodes];
	if ( tmpR == 0) tmpR = num[R_nodes];

	for (int i = 1; i < L_nodes; i++) tmpL += num[i];
	for (int i = 1; i < R_nodes; i++) tmpR += num[i];

	if ( L_nodes > 0) 
	{
		printf("(");
		printTree( tmpL);
		printf(")");
	}
	printf("X");
	if ( R_nodes > 0)
	{
		printf("(");
		printTree( tmpR);
		printf(")");
	}
}

