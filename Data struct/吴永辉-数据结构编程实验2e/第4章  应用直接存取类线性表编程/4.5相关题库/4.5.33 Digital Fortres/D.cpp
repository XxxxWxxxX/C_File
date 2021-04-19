/* 
	Author : Leon 
	Problem : Problem D
*/

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;


string str;

int judge(int x){
	int v = int(sqrt(x)+1e-8);
	if (v*v==x) return v;
	else return 0;
}

int main(){
	
	int N;
	scanf("%d\n",&N);
	
	for (int i=1;i<=N;i++){
		getline(cin,str);
		int x=judge(str.length());
		if (x){
			for (int i=0;i<x;i++)
				for (int j=0;j<x;j++)
					putchar(str[i+x*j]);
			puts("");
		}
		else puts("INVALID");
	}
	
	return 0;
}