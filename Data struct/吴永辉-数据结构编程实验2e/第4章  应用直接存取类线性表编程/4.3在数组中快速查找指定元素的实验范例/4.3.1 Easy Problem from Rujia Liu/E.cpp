#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
using namespace std;
const int MAXX=1000050;
vector<int> v[MAXX];
int main()
{
	int n,m;
	while (scanf("%d%d",&n,&m)==2)
	{
		for (int i=1;i<MAXX;i++) v[i].clear();
		for (int i=1;i<=n;i++)
		{
			int x;
			scanf("%d",&x);
			v[x].push_back(i);
		}
		for (int i=1;i<=m;i++)
		{
			int k,x;
			scanf("%d%d",&k,&x);
			int ans=0;
			if (v[x].size()<k) ans=0;
				else ans=v[x][k-1];
			printf("%d\n",ans);
		}
	}
	return 0;
}
