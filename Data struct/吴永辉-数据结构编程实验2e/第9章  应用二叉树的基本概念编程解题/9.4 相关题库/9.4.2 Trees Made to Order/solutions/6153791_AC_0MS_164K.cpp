#include <iostream>
using namespace std;

const int Catlan[] = {1,1,2,5,14,42,132,
					  429,1430,4862,16796,58786,
					  208012,742900,2674440,9694845,
					  35357670,129644790,477638700};

int count(int& N)
{
	int t = 1;	
	while(N >Catlan[t])
	{
		N -= Catlan[t];
		++t;
	}
	return t;
}

void Build(int all, int m)
{
     int Right = all-1;
	 int Left = 0;
	 int k;
     while(m > Catlan[Right]*Catlan[Left])
	 {
		 m -= Catlan[Right]*Catlan[Left];
		 --Right;
		 ++Left;
	 } 

     if(Left>0)
     {
		 printf("(");
		 k = m/Catlan[Right];
		 if(m%Catlan[Right]!=0) k++;
		 Build(Left,k);
		 printf(")");
	 }  

     printf("X");

     if(Right>0)
     {
		 printf("(");
		 k = (m-1)%Catlan[Right]+1;
         Build(Right,k);
         printf(")");
     }       
}

int main()
{
	while(true)
	{
		int N;
		scanf("%d",&N);
		if(N==0)break;

		int NodeNumber = count(N);
		Build(NodeNumber,N);
		printf("\n");
	}
	return 0;
}
