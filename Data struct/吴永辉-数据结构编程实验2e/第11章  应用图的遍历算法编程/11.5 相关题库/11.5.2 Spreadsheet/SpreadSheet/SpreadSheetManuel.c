/*

1995-96 ACM International Collegiate Programming Contest
Southwestern European Regional Contest
ETH Zurich, Switzerland
December 9, 1995


Problem: SpreadSheet

Idea and Implementation:	Manuel Bleichenbacher, Head Judge

Source file: spreadsheet.c / spreadsheet.p
Input file: spreadsheet.in
Output file: spreadsheet.out

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

int dummy;


typedef enum { FALSE, TRUE } bool;

int sX, sY;

typedef struct {
	int		value;
	bool	computed;
	int		sumIndex;
} CELL;

CELL*	_sCell;
#define	sCell(x,y)	_sCell[(y)*sX+(x)]
int*	sSumList;
int		sSumListSize = 0;
int		sIndex = 0;

int		sRecursiveDepth = 0;

char	sBuf[1024];


void growSumList(int n);
void readCell(FILE* fin, int x, int y);
char* readCellName(char* buf);
void computeCells();
int computeCell(int x, int y, int depth);

int main(int argc, char* argv[])
{
	FILE *fin, *fout;
	int x, y;
	int nSpreadSheets;
	
	fin = fopen("spreadsheet.in", "r");
	assert( fin != 0 );
	fout = fopen("spreadsheet.out", "w");
	assert( fout != 0 );
	
	dummy = fscanf(fin, "%d", &nSpreadSheets);
	assert( dummy == 1 );
	while (nSpreadSheets-- > 0) {
	
		dummy = fscanf(fin, "%d %d", &sX, &sY);
		assert( dummy == 2 );

		_sCell = (CELL*) malloc( (sX + 1) * (sY + 1) * sizeof(CELL) );
		assert( _sCell != 0 );

		for (y=1; y <= sY; y++)
			for (x=1; x <= sX; x++)
				readCell(fin, x, y);

		computeCells();

		for (y=1; y <= sY; y++)
			for (x=1; x <= sX; x++)
				if (x != sX)
					fprintf(fout, "%d ", sCell(x,y).value);
				else
					fprintf(fout, "%d\n", sCell(x,y).value);
	}
		
	fclose(fout);
	fclose(fin);
	
	free(_sCell);
	free(sSumList);
	
	/* printf ("Recursive depth = %d\n", sRecursiveDepth ); */
	return 0;
}


void readCell(FILE* fin, int x, int y)
{
	int v;
	char*	buf = sBuf;
	
	assert(x >= 1 && x <= sX);
	assert(y >= 1 && y <= sY);
	
	dummy = fscanf(fin, "%s", sBuf);
	assert( dummy == 1 );
		
	if (buf[0] == '=') {	/* formula */
		sCell(x,y).computed = FALSE;
		sCell(x,y).sumIndex = sIndex;
		buf = readCellName(buf + 1);
		while (buf[0] == '+')
			buf = readCellName(buf + 1);
		
		assert( *buf == '\0' );
		
		growSumList(sIndex+1);
		sSumList[sIndex++] = 0;
	
	} else {				/* value */
		dummy = sscanf(buf, "%d", &v);
		assert( dummy == 1 );
			
		sCell(x,y).value = v;
		sCell(x,y).computed = TRUE;
	}
}

char* readCellName( char* buf)
{
	int x, y;
	
	assert( buf != 0 );
	assert( *buf >= 'A' && *buf <= 'Z' );

	x = 0;
	while ( isupper(*buf) ) {
		x = x * 26 + *buf - 'A' + 1;
		buf++;
	}
	
	assert( *buf >= '0' && *buf <= '9' );
	
	dummy = sscanf(buf, "%d", &y);
	assert( dummy == 1 );
	
	while ( isdigit(*buf) )
		buf++;
	
	growSumList(sIndex + 2);
	sSumList[sIndex++] = x;
	sSumList[sIndex++] = y;
	
	return buf;
}


void computeCells()
{
	int x, y;
	for (x=1; x <= sX; x++)
		for (y=1; y <= sY; y++)
			computeCell(x, y, 0);
}


int computeCell(int x, int y, int depth)
{
	int i, s;
	
	if (depth > sRecursiveDepth)
		sRecursiveDepth++;
	
	assert(x >= 1 && x <= sX);
	assert(y >= 1 && y <= sY);
	
	if ( sCell(x,y).computed )
		return sCell(x,y).value;
		
	s = 0;
	i = sCell(x,y).sumIndex;
	
	assert( i >= 0 );
	assert( i < sIndex );
	
	while (sSumList[i] != 0) {
	
		assert( sSumList[i] >= 1 && sSumList[i] <= sX );
		assert( sSumList[i+1] >= 1 && sSumList[i+1] <= sY );
		
		s += computeCell(sSumList[i], sSumList[i+1], depth+1);
		i += 2;
		
		assert( i < sIndex );
	}
	
	sCell(x,y).value = s;
	sCell(x,y).computed = TRUE;
	return s;
}
	

void growSumList(int n)
{
	if (n <= sSumListSize)
		return;
		
	if (sSumListSize == 0) {
		if (n < 100)
			n = 100; 
		sSumList = (int*) malloc( n * sizeof(int) );
		sSumListSize = n;
	} else {
		sSumListSize = (int)( 1.5 * (float)sSumListSize );
		sSumList = (int*) realloc( sSumList, sSumListSize * sizeof(int) );
		assert( sSumList != 0);
	}
}
