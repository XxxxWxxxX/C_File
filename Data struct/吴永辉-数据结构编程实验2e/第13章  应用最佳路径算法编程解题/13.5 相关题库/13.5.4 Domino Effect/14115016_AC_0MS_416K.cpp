#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#define MAX 600                     //The upper limit of the number of vertices
#define INF 0x7FFFFFFF                //Infinity
using namespace std;
int n,m;                            // the number of vertices n, the number of edges m
int edge[MAX][MAX],visit[MAX],dist[MAX];// adjacency matrix edge[ ][ ], visited mark visit[ ], the length of the shortes paths dist[ ]
void dijkstra(int u0)        // calculating single-source shortes paths from u0
{
    int i,j,v;
    for(i=1; i<=n; i++) dist[i] = edge[u0][i] ;     //Initialization
    visit[u0] = 1;                          //u0: visited mark
    for(j=0; j<n-1; j++)
    {
        int min = INF;  
        for(i=1; i<=n; i++)   
        {
            if(!visit[i] && min > dist[i]) { min = dist[i]; v = i; }
        }
        visit[v] = 1;                      // visited mark
        for(i=1; i<=n; i++)                 // adjust distances
        {
          if(!visit[i] && edge[v][i]<INF && edge[v][i]+dist[v]<dist[i])
dist[i]=edge[v][i]+ dist[v];
        }
    }
}
int main()
{
    int i,j,a,b,c,tt = 1;
    while(scanf("%d%d",&n,&m))   //numbers of vertices and rows
    {
        if(n==0 && m==0) break;
        for(i=1; i<=n; i++)                //Initialize edge[ ][ ] 
            for(j=1; j<=n; j++)
            {
                if(i == j) edge[i][j] = 0; 
                else edge[i][j] = INF;
            }
        for(i=0; i<m; i++)           //Construct edge[ ][ ]
        {
            scanf("%d%d%d",&a,&b,&c);
            edge[a][b] = c; edge[b][a] = c;
        }
        memset(visit,0,sizeof(visit));  
        dijkstra(1);               // calculating single-source shortes paths from vertex 1
                double max1 = -10000000;    
        int index;
        for(i=1; i<=n; i++)      //Case 1: the last domino which falls is a key domino index
        {
            if(max1 < dist[i])  { max1 = dist[i]*1.0; index = i; }
        }
        
        double max2 = -10000000;
        int index1,index2;
        for(i=1; i<=n; i++)            // Case 2: Enumerate every edge (i, j) (i<j), the last domino falls between key domino index1 and key domino index2, and the time that all dominos fall is max2.
            for(j=1; j<=n; j++)
            {
                if(edge[i][j] != INF && i < j)
                {
                    if(max2 < (dist[i]+dist[j]+edge[i][j])/2.0)
                    {
                        max2 = (dist[i]+dist[j]+edge[i][j])/2.0;
                        index1 = i; index2 = j;
                    }
                }
            }
            
        printf("System #%d\n",tt++);    // the number of the test case
        if(max1 >= max2)             // if case 1, else case2 
            printf("The last domino falls after %.1f seconds, at key domino %d.\n",max1,index);
        else printf("The last domino falls after %.1f seconds, between key dominoes %d and %d.\n",max2,index1,index2);
        printf("\n");
    }
    return 0;
}
