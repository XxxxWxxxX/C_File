#include <stdio.h>

const int MaxN = 500000000;

int n, i, j, k;
long long a[200];

void go(int x, long long n)
{
    int i;

    if (x==0) return;
    for (i=0; i<x; i++)
        if (a[i]*a[x-i-1]<n) n -= a[i] * a[x - i - 1]; else 
        {
            if (i)
            {
                printf("(");
                go(i, (n-1)/a[x-i-1]+1);
                printf(")");
            }
            printf("X");
            if (x-i-1) { printf("("); go(x-i-1, (n-1)%a[x-i-1]+1); printf(")"); }
            break;
        }
}

int main()
{
    a[1] = 1; a[0] = 1;
    for (i=2; a[i-1]<MaxN; i++)
    {
        a[i] = 0;
        for (j=0; j<i; j++) a[i] += a[j] * a[i - j - 1];
    }
    while (1)
    {
        scanf("%d", &n);
        if (n==0) break;
        for (i=1; a[i]<n; i++) n -= a[i];
        go(i, n);
        printf("\n");
    }
}


