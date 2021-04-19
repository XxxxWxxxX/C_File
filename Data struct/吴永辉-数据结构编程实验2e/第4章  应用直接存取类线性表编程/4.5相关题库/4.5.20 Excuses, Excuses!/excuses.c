#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
FILE *inp, *outp;

typedef struct
{ char excuse[71];
	int  incidents;
} excuse_t;

excuse_t excuses[20];
char     keywords[20][21];
int      num_excuses, num_keywords, set_num;

int find_incidents(int k, int e)
{ int i, j, num_found=0;
	char build_word[71];

	for (i=0; excuses[e].excuse[i] != 0; )
	{ if (isalpha(excuses[e].excuse[i]))
		{ for (j=0; isalpha(excuses[e].excuse[i]); )
			{ build_word[j]=tolower(excuses[e].excuse[i]);
				j++; i++;
				build_word[j]=0;
			}
			if (!strcmp(build_word, keywords[k]))
			{ num_found++; }
		}
		else { i++; }
	}
  return(num_found);
}

void read_set(void)
{ int i,j;
	char *c;

	for (i=0; i<20; i++)
	{ excuses[i].excuse[0] = 0;
		excuses[i].incidents = 0;
		keywords[i][0] = 0;
	}
	fscanf(inp, "%d %d", &num_keywords, &num_excuses);
	fscanf(inp, "\n");
	for (i=0; i<num_keywords; i++)
	{ fscanf(inp, "%s", &(keywords[i]));
		fscanf(inp, "\n");
	}
	for (i=0; i<num_excuses; i++)
	{ fgets(excuses[i].excuse, 80, inp);
		fscanf(inp, "\n");
		for (j=0; j<strlen(excuses[i].excuse); j++)
		{ if (excuses[i].excuse[j] == '\n')
			{ excuses[i].excuse[j]=0; }
		}
	}
}

void rate_excuses(void)
{ int k, e;

	for (e=0; e<num_excuses; e++)
	{ for (k=0; k<num_keywords; k++)
		{ excuses[e].incidents += find_incidents(k, e); }
	}
}

void print_worst(void)
{ int i, worst=0;

	for (i=0; i<num_excuses; i++)
	{ if (worst < excuses[i].incidents)
		{ worst = excuses[i].incidents; }
	}

	fprintf(outp, "Excuse Set #%1d\n", set_num);
	for (i=0; i<num_excuses; i++)
	{ if (worst == excuses[i].incidents)
		{ fprintf(outp, "%s\n", excuses[i].excuse); }
	}
	fprintf(outp,"\n");
}

void main(void)
{	int  top, size, count;

	inp=fopen("excuses.in","r");
	outp=fopen("excuses.out","w");
	set_num=0;
	while (!feof(inp))
	{ set_num++;
		read_set();
		rate_excuses();
		print_worst();
	}
	fclose(inp);
	fclose(outp);
}