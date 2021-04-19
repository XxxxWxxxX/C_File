/*

1995-96 ACM International Collegiate Programming Contest
Southwestern European Regional Contest
ETH Zurich, Switzerland
December 9, 1995


Problem: SpreadSheet

Idea:			Manuel Bleichenbacher, Head Judge
Implementation:	Rolf Strebel, ETH Zurich

Source file: spreadsheet.c / spreadsheet.p
Input file: spreadsheet.in
Output file: spreadsheet.out

*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define BUFSIZE 4096
#define TRAP

typedef struct EntryDesc *Entry;
typedef struct EntryDesc {
  int is_val;
  int val;
  Entry *e;
} EntryDesc;

#define T(i,j) (*(tab+i+j*row))
Entry tab;
int row, col;
FILE *fin, *fout;

char *parse_cell (char *str, int *row, int *col)
{
#define dif ((int)('Z' - 'A' + 1))
  int r, c;

  r = 0; 
  while (isalpha(*str)) {
    r = r*dif + (toupper(*str) - 'A' + 1);
    str++;
  }
  c = 0;
  while (isdigit(*str)) {
    c = 10*c + (*str - '0');
    str++;
  }
  *row = c - 1; *col = r - 1;
  return (str);
}
  
int main (int argc, char **argv)
{
  char buf[BUFSIZE+1];
  int nof, r, c;
  int i, j, k;
  int val;
  Entry *e;
  char *str;
  int chg;

  if ((fin = fopen("spreadsheet.in","r")) == NULL) exit (1);
  if ((fout = fopen("spreadsheet.out","w")) == NULL) exit (1);

  fscanf (fin, "%i", &nof);
  while (nof-- > 0) {
    fscanf (fin, "%i %i", &col, &row);
    tab = (Entry) malloc(row*col*sizeof(EntryDesc));
    for (i = 0; i < row; i++) {
      for (j = 0; j < col; j++) {
       fscanf (fin, "%s", buf);
       str = buf;
       if (str[0] == '=') {
         e = (Entry *) malloc (strlen(str)*sizeof(Entry));
         for (k = 0; *str++; k++) {
           str = parse_cell(str, &r, &c);
           e[k] = &T(r,c);
         }
         e[k] = NULL;
         T(i,j).is_val = 0;
         T(i,j).e = e;
       } else {
         T(i,j).is_val = 1;
         T(i,j).val = atoi(str);
       }
      }
    }
    for (chg = 1; chg; ) {
      chg = 0;
      for (i = 0; i < row; i++) {
       for (j = 0; j < col; j++) {
         if (!(T(i,j).is_val)) {
           for (val = 0, k = 0; ; k++) {
             if (T(i,j).e[k] == NULL) {
               T(i,j).is_val = 1;
               T(i,j).val = val;
               chg = 1;
               break;
             } else if (T(i,j).e[k]->is_val) {
               val += T(i,j).e[k]->val;
             } else {
               break;
             }
           }
         }
       }
      }
    }
    for (i = 0; i < row; i++) {
      for (j = 0; j < col; j++) {
       fprintf (fout, "%i", T(i,j).val);
       if (j < col-1) fprintf (fout, " ");
      }
      fprintf (fout, "\n");
    }
  }

  fclose (fin);
  fclose (fout);
  return (0);
}






