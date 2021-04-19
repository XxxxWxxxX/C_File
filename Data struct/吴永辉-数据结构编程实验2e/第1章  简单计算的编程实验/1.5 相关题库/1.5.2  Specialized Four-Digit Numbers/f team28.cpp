//team 28
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <sstream>
using namespace std;
ifstream in ("f.in");
FILE * fin = fopen ("f.in", "r");
typedef long long lld;
#define cin in
int digit(int i){
  return i;
  /*
  string ret="";
  if (i<10&&i>=0)
    ret += ('0'+i);
  else
  if (i>=10&&i<=15)
    ret += ('A'+i-10);
  
  return ret;
  */
}
int b10(int i){
  
  int ret=0;
  while (i>0){
    ret = digit(i%10)+ret;
    i/=10;
  }
  //cout<<ret<<endl;
  return ret;
  
}
int b12(int i){
  int ret=0;
  while (i>0){
    ret = digit(i%12)+ret;
    i/=12;
  }
  //cout<<ret<<endl;
  return ret;
  
}
int b16(int i){
  int ret=0;
  while (i>0){
    ret = digit(i%16)+ret;
    i/=16;
  }
  //cout<<ret<<endl;
  return ret;

  
}
int main () {
  int i;
  for (i=2992;i<10000;i++){
    if (b10(i)==b12(i)&&b12(i)==b16(i))
      cout<<i<<endl;
  }
  return 0;
}
