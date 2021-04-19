#include<iostream>
using namespace std;
#include<algorithm>

int h[]={1,1,2,5,14,42,132,429,1430,4862,16796,58786,208012,742900,2674440,9694845,35357670,129644790,477638700,1767263190};
int nIndex[]={1,2,4,9,23,65,197,626,2056,6918,23714,82500,290512,1033412,3707852,13402697,48760367,178405157,656043857};
const int hLength=sizeof(h)/sizeof(int);
const int nIndexLength=sizeof(nIndex)/sizeof(int);

void output(int n,int nodes)
{
     if(0==n)
       return;
     if(1==n)
     {
       cout<<"X";
       return;
     }
     int rest=n-nIndex[nodes-1];
     int left=0,right=nodes-1;
     while(rest-h[left]*h[right]>=0)
     {
           rest-=h[left]*h[right];
           ++left;
           --right;
     }
     int leftIndex=rest/h[right]+nIndex[left-1],rightIndex=rest%h[right]+nIndex[right-1];
     if(left!=0)
     {
        cout<<"(";
        output(leftIndex,left);
        cout<<")";
     }
     cout<<"X";
     if(right!=0)
     {
         cout<<"(";
         output(rightIndex,right);
         cout<<")";
     }
}

int main()
{
    int n,myNodes;
    while(cin>>n&&n!=0)
    {
         myNodes=upper_bound(nIndex,nIndex+nIndexLength,n)-nIndex;
         output(n,myNodes);
         cout<<endl;
    }
    return 0;
}