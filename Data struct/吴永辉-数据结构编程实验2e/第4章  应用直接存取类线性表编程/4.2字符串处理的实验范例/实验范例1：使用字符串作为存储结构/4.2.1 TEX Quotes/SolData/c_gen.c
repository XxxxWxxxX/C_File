#include <stdio.h>
#include <stdlib.h>

void print_radka()
{
	int i;
	for(i=30;i--;)
	{
		if(  rand() % 8 )
		{
			printf("%c", 'a' + rand() % ('z' - 'a'));
		}
		else
		{
			printf("\"");
		}
	}
	printf("\n");
}	/* print_radka */

void main()
{
	int i;
	for(i= 200;i--;)
	{
		print_radka();
	}
}	/* main */
