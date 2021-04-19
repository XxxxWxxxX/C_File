/**************************************
"What Day Is It?" problem and code submitted
by Peter D. Mark for the ACM Pacific NW
Programming Contest on 15 November 1997.
**************************************/


#include <stdio.h>
#include <string.h>
#define GBASE 1
#define JBASE 6
#define JULIAN    0
#define GREGORIAN 1

/*************************************************************************
 * the janfirst function takes an integer argument that represents a year* 
 * and returns the day of the week of january first of that year (using  *
 * the encoding sunday = 0, monday = 1, ... , saturday = 6)              *
 * expressions are left unsimplified for understandability:              *
 * since 365 = 1 mod 7, the solution is to count the number of years     *
 * between the year 0 and the year Y, as well as the number of leap      *
 * years in that same range.                                             *
 *************************************************************************/

#define JANFIRSTJ(Y) ((JBASE + (Y-1) + (Y-1)/4) % 7)
#define JANFIRSTG(Y) ((GBASE + (Y-1) + (Y-1)/4 - (Y-1)/100 + (Y-1)/400) % 7)
#define JANFIRST(Y,S) ((S == GREGORIAN) ? JANFIRSTG(Y) : JANFIRSTJ(Y))

/*************************************************************************
 * the leap function takes an integer argument that represents a year    *
 * and returns a 0 if the year is not a leap year and a 1 if the year    *
 * is a leap year.                                                       *
 *************************************************************************/

#define LEAPJ(Y) ((Y % 4) == 0)
#define LEAPG(Y) ((((Y % 4) == 0) && ((Y % 100) != 0)) || ((Y % 400) == 0))
#define LEAP(Y) ((Y  > 1752) ? LEAPG(Y) : LEAPJ(Y))

/************************************************************************
 * find_mf takes the month and janfirst (weekday of 1/1/year) and computes 
 * the first day of the month, using the array lengths.  
 ************************************************************************/

int find_mf(int month, int janfirst, int year, int *lengths)
{
  int i, sum = janfirst;

  if (LEAP(year)) lengths[1] = 29;

  /* Special case: September 1752 had 19 days: 1, 2, 14, 15, ... , 30 */ 

  if (year == 1752)  lengths[8] = 19;

  for(i = 0; i < month; i++)
    sum += lengths[i];
  return sum % 7;   
}

/************************************************************************
 * call with : "a.out month day year"                        
 * where month is a number from 1 - 12 (1 = january, etc)
 *       day   is a number from 1 - 31 (day of month)
 *       year  is a number greater than 1752
 * output: prints weekday the date occurred.
 ************************************************************************/

void main()
{ 
  int   year, month, day, month_first, calendartype;
  char  *weekdays[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", 
                        "Thursday", "Friday", "Saturday"};
  int lengths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  /* month entered is between 1 and 12; change to zero-based (0 - 11) */

  while(1)
  {

  /*  convert input */
  if (!scanf("%d%d%d",&month,&day,&year)) return;   /* make month zero-based */
  month--;
  if (month==-1) return;

  /* determine calendar type */
  if (year > 1752) calendartype = GREGORIAN;
  else calendartype = JULIAN;

  /* error check month */
  if ((month < 0) || (month > 11))
    { printf("not a valid month\n"); return; }

  /* error check date */
  if (!((year == 1752) && (month == 8)))
  {
    if ((day > lengths[month]) || (day < 1))
      { printf("not a valid date\n"); return; }
  }
  else  /* handle transitional month 9/1752 as a special case */
  {
    if (((day > 2) && (day < 14)) || (day < 1) || (day > 30))
      { printf("not a valid date\n"); return; }
    if (day >= 14) day += 10;
  }

  /* get first of month */
  month_first = find_mf(month, JANFIRST(year, calendartype), year, lengths);

  /* print the answer  */
  printf("%s\n", weekdays[(month_first + day - 1) % 7]);
  }
}



