#include <stdio.h>
#include <stdlib.h>

int t1,t2,i,j,k,h,m;

char *x[] = {
"WET","0",
"UTC","0",
"GMT","0",
"BST","+1",
"IST","+1",
"WEST","+1",
"CET","+1",
"CEST","+2",
"EET","+2",
"EEST","+3",
"MSK","+3",
"MSD","+4",
"AST","-4",
"ADT","-3",
"NST","-3.5",
"NDT","-2.5",
"EST","-5",
"EDT","-4",
"CST","-6",
"CDT","-5",
"MST","-7",
"MDT","-6",
"PST","-8",
"PDT","-7",
"HST","-10",
"AKST","-9",
"AKDT","-8",
"AEST","+10",
"AEDT","+11",
"ACST","+9.5",
"ACDT","+10.5",
"AWST","+8",
"",""};

main(){
   static int w, ap;
   for (i=0;*x[i];i+=2) w++;
   printf("200\n",w);
   for (i=0;i<200;i++) {
      h = random()%12;
      m = random()%60;
      ap = random()%2;
      t1 = random()%w;
      t2 = random()%w;
      if (1 == random()%10) {
         h = 0; m = 0;
      }
      if (1 == random()%5) m = 30;
      if (1 == random()%5) m = 0;
      if (h == 0 && m == 0) {
         if (ap) printf("midnight");
         else printf("noon");
      } else{
          printf("%d:%02d",h,m);
          if (ap) printf(" a.m.");
          else printf(" p.m.");
      }
      printf(" %s %s\n",x[2*t1],x[2*t2]);
   }
}
