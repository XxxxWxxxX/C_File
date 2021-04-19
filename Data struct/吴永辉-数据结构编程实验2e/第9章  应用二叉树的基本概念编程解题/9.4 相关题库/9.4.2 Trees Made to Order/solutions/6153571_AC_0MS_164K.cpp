#include<iostream>
using namespace std;
int t[20];
int sum[20];
void init()
{
	int i,j;
	t[0]=1;
	t[1]=1;
	for(i=2;i<=19;i++)
	{
		t[i]=0;
		for(j=0;j<i;j++) 
			t[i]+=t[j]*t[i-1-j];
	}
	sum[1]=1;
	for(i=2;i<=19;i++) sum[i]=sum[i-1]+t[i];
}
void printout(int x,int num)
{
	if(x==1) {printf("X");return ;}
	if(x==2) 
	{
		if(num==1) printf("X(X)");
		else printf("(X)X");
		return ;
	}
	int i,re=0;
	for(i=0;i<x-1;i++)
	{
		if(re+t[i]*t[x-1-i]>=num) break;
		re+=t[i]*t[x-1-i];
	}
	if(i==0)
	{
		printf("X(");
		printout(x-1-i,num-re);
		printf(")");
		return ;
	}
	if(x-i-1==0)
	{
		printf("(");
		printout(i,num-re);
		printf(")X");
		return ;
	}
	int t1,t2;
	t1=(num-re-1)/t[x-1-i]+1;
	t2=(num-re)%t[x-1-i];
	printf("(");
	printout(i,t1);
	printf(")X(");
	printout(x-1-i,t2);
	printf(")");
}
int main()
{
	int n,i;
	init();
	while(scanf("%d",&n))
	{
		if(n==0) break;
		for(i=1;;i++)if(sum[i]>=n) break;
		printout(i,n-sum[i-1]);
		printf("\n");
	}
	return 0;
}


