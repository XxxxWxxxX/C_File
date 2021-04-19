#include <stdio.h>
/* by Vit Stradal */
/* direct method */

int main()
{
	int c;
	int q;
	q= 1;
	while( (c= getchar()) != -1 )
	{
		if(c == '"')
		{
			printf("%s", q?"``":"''");
			q= !q;
		}
		else 
		{
			printf("%c", c);
		}
	
	}
	return 0;
}	/* main */
