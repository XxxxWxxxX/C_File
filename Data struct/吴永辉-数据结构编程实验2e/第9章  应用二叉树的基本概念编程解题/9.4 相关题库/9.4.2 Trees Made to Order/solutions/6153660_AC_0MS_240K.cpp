#include<iostream>
using namespace std;
long p[19]={0,1,3,8,22,64,196,625,2055,6917,23713,82499,290511,
          1033411,3707851,13402696,48760366,178405156,656043856};
long q[19]={0,1,2,5,14,42,132,429,1430,4862,16796,58786,208012,
          742900,2674440,9694845,35357670,129644790,477638700};
void dfs(long n)
{
	 long i;
     if(n==1)
	 {
		 cout<<'X';
		 return ;
	 }
     for(i=1;p[i]<n;i++) ;
     if(n-p[i-1]<=q[i-1])
     {
         cout<<"X(";
         dfs(n-q[i-1]);
         cout<<')';
     }
     else if(n>p[i]-q[i-1])
     {
         cout<<'(';
         dfs(n-q[i]);
         cout<<")X";
     }
     else
     {
         long s=p[i-1]+q[i-1],j;
         for(j=1;n>s+q[j]*q[i-1-j];j++)
			s+=q[j]*q[i-1-j];
         long l=j,r=i-j-1,m=(n-s-1)/q[r],k=(n-s-1)%q[r];
         cout<<'(';
         dfs(m+p[l-1]+1);
         cout<<")X(";
         dfs(k+p[r-1]+1);
         cout<<')';
     }
}     

int main()
{ 
    long n;
    while(cin>>n && n!=0)
    {
        dfs(n);
        cout<<endl;
    }
    return 0;
}
