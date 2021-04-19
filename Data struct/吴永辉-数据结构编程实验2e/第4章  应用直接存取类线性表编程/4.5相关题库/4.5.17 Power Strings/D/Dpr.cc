#include <stdio.h>
#include <string.h>
#include <assert.h>

int gcd(int a, int b) {
   if (b == 0) return a;
   return gcd(b,a%b);
}

int main () {
  char s[1000100];  int f[200], lens, g, gg;
  while (1) {
    fgets(s,1000099,stdin);
    if (strlen(s) < 2) {
      printf("Line too short!\n");
      return 0;
    }
    if (strlen(s) > 1000001) {
      printf("Line too long!\n");
      return 0;
    }
    s[strlen(s)-1] = 0;
    lens = strlen(s);
    if ((lens == 1) && (s[0] == '.')) 
      break;
    for (int i = 0; i < 200; i++) f[i] = 0;
    for (int i = 0; i < lens; i++) {
      f[s[i]]++;
    }
    g = lens;
    for (int i = 0; i < 200; i++) 
      if (f[i]) g = gcd(g,f[i]);
    g = lens/g;
    for (; g > 0; g--) {
      if ((lens%g)) continue;
      for(int a = 0; a < lens; a=a+g)
	for (int b = 0; b < g; b++)
	  if (s[a+b] != s[b]) goto C;
      break;
    C:;
    }
    if (g == 0) g = lens;
    printf("%d\n",lens/g);
  }
  return 0;
}
