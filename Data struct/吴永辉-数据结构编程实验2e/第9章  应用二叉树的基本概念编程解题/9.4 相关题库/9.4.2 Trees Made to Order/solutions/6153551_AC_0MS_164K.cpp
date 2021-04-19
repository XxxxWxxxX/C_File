#include <stdio.h>
#include <string>
using namespace std;
int m;
long long way[19], n;
void work(int nod, long long pos) {
	if (nod == 1)
		printf("X");
	else {
		int l = 0;
		for (; pos >= way[l] * way[nod - l - 1]; ++l)
			pos -= way[l] * way[nod - l - 1];
		if (l > 0) {
			printf("(");
			work(l, pos / way[nod - l - 1]);
			printf(")");
		}
		printf("X");
		if (nod - l - 1 > 0) {
			printf("(");
			work(nod - l - 1, pos % way[nod - l - 1]);
			printf(")");
		}
	}
}
int main() {
	memset(way, 0, sizeof(way));
	way[0] = 1; way[1] = 1;
	for (int i = 2; i < 19; ++i)
		for (int j = 0; j <= i - 1; ++j)
			way[i] += way[j] * way[i - j - 1];
	while (scanf("%d", &m), m > 0) {
		n = m;
		int i = 0;
		for (; n >= way[i]; ++i)
			n -= way[i];
		work(i, (long long)n);
		printf("\n");
	}
	return 0;
}


