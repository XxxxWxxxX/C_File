#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
using namespace std;
#define MAXN 10000       // The upper limit of the number of vertices
int set[MAXN];            // the root of the subtree containing vertex i is set[i]
int n, ans;                  //n: the number of sentences, ans: the maximum number of sentences which can be made true in a valid truth assignment for the document
void init(int n)             // set up 2*n sets with one vertex
{
	for(int i=1;i<=n*2;i++) set[i]=i;
}
int find(int a)             // find the representative of the set containing a
{
	int root=a;           // find the root root from a
	int temp;
	while(set[root]!=root) root=set[root];
	while(set[a]!=root)    // representative for all vertices on the path from a to root is root
	{
	   temp=a; a=set[a]; set[temp]=root;
	}
	return root;
}
bool unions(int a,int b)               // if a and b belong to a same set, then return false; else the two sets containing a and b are combined and return true
{
	int x=find(a);int y=find(b);        // find representatives for sets containing a and b
	if(x==y) return false;             // if a and b belong to a same set, then return false
	set[x]=y;                 // the two sets containing a and b are combined and return true
	return true;
}
char str[50];
int d; 
bool jud(int i, int j)        // Determine whether i and j belong to a same union-find set or not
{
    return find(i)==find(j);
}
int opt[MAXN], cnt[MAXN];           // cnt[i]: the size of the subtree with root i, opt[i]: the root of the subtree for the opposite set, vis[i]: visited mark
bool vis[MAXN];
void solve( )                         //Calculate and output the maximum number of sentences which can be made true in a valid truth assignment for the document 
{
   memset(cnt, 0, sizeof(cnt)); 
   for(int i=1; i<=n; i++) 
   {
     cnt[find(i)]++;  
     opt[find(i)]=find(i+n);    
opt[find(i+n)]=find(i);
   }
   int ans=0;  
   memset(vis, 0, sizeof(vis));  
   for(int i=1; i<=n; i++)   
   {
     if(vis[find(i)]||vis[find(i+n)]) continue;  
     ans+=max(cnt[find(i)],cnt[find(i+n)]);  
     vis[find(i)]=vis[find(i+n)]=1; 
   }
   printf("%d\n", ans);                   // Output
}
int main( )
{
    while(~scanf("%d", &n)&& n)     // the number of sentences
    {
        bool flag=0; 
        init(n);                    // set up 2*n sets with one vertex
        for(int i=1; i<=n; i++)         //Input
        {
            scanf("%s", str);         //Input ‘Sentence’
            scanf("%d", &d);  
            scanf("%s", str);         //Input ‘is’
            scanf("%s", str);  
            if (flag) continue;   
            if (strcmp(str,"false.")==0) //false
            {
// if i and d belong to a same union-find set or i+n and d+n belong to a same union-find set,
// else combine union-find sets containing i and d+n, union-find sets containing i+n and d
                if (jud(i, d) || jud(i+n, d+n)) flag=1; 
                    else unions(i, d+n),unions(i+n, d);
            }
            else                    //true
            {
                  if(jud(i,d+n) || jud(i+n,d)) flag=1;
                 else unions(i,d),unions(i+n,d+n);
            }
        }
         if (flag) printf("Inconsistent\n");    
          else solve( );
    }
    return 0;
}

