#include<iostream>
using namespace std;
int temp[25];
int sum[25];
void chushihua()
{
	int i,j;
	temp[0]=1;
	temp[1]=1;
	for(i=2;i<=19;i++)
	{
		temp[i]=0;
		for(j=0;j<i;j++) 
			temp[i]+=temp[j]*temp[i-1-j];
	}
	sum[1]=1;
	for(i=2;i<=19;i++)
		sum[i]=sum[i-1]+temp[i];
}
void putout(int x,int num)
{	
	int i,re=0,t1,t2;
	if(x==1) {printf("X");return ;}
	if(x==2) {
		if(num==1) printf("X(X)");
		else printf("(X)X");
		return;
	}
	for(i=0;i<x-1;i++){
		if(re+temp[i]*temp[x-1-i]>=num)
			break;
		re+=temp[i]*temp[x-1-i];
	}
	if(i==0){
		printf("X(");
		putout(x-1-i,num-re);
		printf(")");
		return ;
	}
	if(x-i-1==0){
		printf("(");
		putout(i,num-re);
		printf(")X");
		return ;
	} 
	t1=(num-re-1)/temp[x-1-i]+1;
	t2=(num-re)%temp[x-1-i];
	printf("(");
	putout(i,t1);
	printf(")X(");
	putout(x-1-i,t2);
	printf(")");
}
int main()
{
	int n,i;
	chushihua();
	while(scanf("%d",&n))
	{
		if(n==0) 
			break;
		for(i=1;;i++)
			if(sum[i]>=n) 
				break;
		putout(i,n-sum[i-1]);
		printf("\n");
	}
	return 0;
}

