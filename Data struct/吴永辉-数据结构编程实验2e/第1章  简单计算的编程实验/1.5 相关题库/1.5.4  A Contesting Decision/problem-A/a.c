#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char winner[80];
int probs=0,points=0;

main()
{
	char line[1024];
	char *name;
	char *ts,*tt;
	int teams;
	int i,j;

	fscanf(stdin,"%d\n",&teams);
	for (i=0 ; i<teams ; i++) {
		int tp=0,pts=0;	
		fgets(line,sizeof(line),stdin);
		name=strtok(line," \n");
		for (j=0 ; j<4 ; j++) {
			int s,t;
			ts=strtok(NULL," \n");
			s = atoi(ts);
			tt=strtok(NULL," \n");
			t = atoi(tt);

			if (t != 0) {
				tp++;
				pts += t + 20*(s-1);
			}
		}

		if (tp > probs || (tp == probs && pts < points)) {
			probs = tp;
			points = pts;
			strcpy(winner,name);
		}
	}

	printf("%s %d %d\n",winner,probs,points);
}

