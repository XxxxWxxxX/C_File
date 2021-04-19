#include <stdio.h>

main(){
   int i,j,n;
   for (n=1;n<=1000000;n *= 10) {
      for (i=0;i<1000000;i++) {
         if (i%n == n-1) printf("%c",'b');
         else printf("%c",'a');
      }
      printf("\n");
   }
   printf(".\n");
}
