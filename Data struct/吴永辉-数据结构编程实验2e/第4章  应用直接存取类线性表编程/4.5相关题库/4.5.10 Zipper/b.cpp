


// team 14
#include <iostream>
#include <fstream>
#include <math.h>
#include <sstream>
#include <ext/hash_set>
#include <algorithm>
#include <vector>
#define fi(n) for(int i=0; i<(n); ++i)
#define fj(n) for(int j=0; j<(n); ++j)
#define fk(n) for(int k=0; k<(n); ++k)
#define sz size()
#define pb push_back

using namespace std;

string s,t,m;

int cache[201][201];

bool canform(int a, int b){
  if(cache[a][b]!=-1) return cache[a][b];
  if(a==s.sz && b==t.sz) return 1;
  bool cando=0;
  if(a!=s.sz && s[a]==m[a+b]) cando|=canform(a+1,b);
  if(b!=t.sz && t[b]==m[a+b]) cando|=canform(a,b+1);
  return cache[a][b]=cando;
}

int main() {
  ifstream cin("b.in",ios::in);
  int n; cin>>n;
  fi(n) {
    fj(201) fk(201) cache[j][k]=-1;
    cin>>s>>t>>m;
    bool isgood=(s.sz+t.sz==m.sz);
    if(isgood) isgood &= canform(0,0);
    cout << "Data set "<<i+1<<": "<<(isgood?"yes":"no")<<endl;
  }
}
