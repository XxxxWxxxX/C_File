#include <iostream>
using namespace std;
int a[50];
void print(int n,int num)
{
if (n==0) return;
if (n==1)
{
         printf("X");
         return;
}
if (n==2)
{
         if (num==1)
                    cout <<"X(X)";
                    else cout <<"(X)X";
         return;
}

int i,s;
s=0;

	for(i=0;i<=n-1;i++)
	{
		if(s+a[i]*a[n-1-i]>=num) break;
		s+=a[i]*a[n-1-i];
	}
    if(i==0)
	{
		printf("X(");
		print(n-1-i,num-s);
       	printf(")");
		return ;
	}
	if(n-i-1==0)
	{
		printf("(");
		print(i,num-s);
		printf(")X");
		return ;
	}
	int t1,t2;
	t1=(num-s-1)/a[n-1-i]+1;
	t2=(num-s)%a[n-1-i];
	printf("(");
	print(i,t1);
	printf(")X(");
	print(n-1-i,t2);
	printf(")");
}
int main()
{
    int i,j,n;
    memset(a,0,sizeof(a));
    a[1]=1;a[0]=1;
    for (i=2;i<=20;i++)
        for (j=0;j<=i-1;j++)
            a[i]=a[i]+a[j]*a[i-1-j];

    cin >>n;
    while (n>0)
    {
          j=0;
          for (i=1;i<=20;i++)
          {
          j=j+a[i];
          if (j>=n) break;
          }
          print(i,n-(j-a[i]));
          cout <<endl;
          cin >>n;
    }
    return 0;
}