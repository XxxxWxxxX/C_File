/*

1995-96 ACM International Collegiate Programming Contest
Southwestern European Regional Contest
ETH Zurich, Switzerland
December 9, 1995


Problem: SpreadSheet

Idea and Implementation:	Manuel Bleichenbacher, Head Judge

This program creates random spreadsheets. The number of
columns and rows are passed as arguments and the final
spreadsheet is written to standard output.

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef enum { FALSE = 0, TRUE = 1 } bool;

typedef struct {
	int		value;
	bool	used;
	int		sumIndex;
} CELL;

CELL*	_sCell;
#define	sCell(x,y)	_sCell[(y)*sMaxX+(x)]

#define cMaxIndex	500010
int*	sSumIndices;
int		sIndex;
int		sMisses;
int		sMaxX, sMaxY;

static char sCellNameBuf [7];



char* CellName ( int x, int y );
void RandomCell ( int* x, int* y );
void InsertFormula();
void printCell ( int x, int y, bool cr );
void SRand(int seed);
int Rand();


void SRand(int seed)
{
	srand(seed);
}

int Rand()
{
	return rand() & 0x7fff;
}


char* CellName ( int x, int y )
{
	char* p = sCellNameBuf;
	
	assert( x >= 1 && x < sMaxX );
	assert( y >= 1 && y < sMaxY );
	
	if (x > 702) {
		*p++ = (x - 703) / 676 + 'A';
		x = (x - 703 ) % 676 + 27;
	}
	if (x > 26) {
		*p++ = (x - 27) / 26 + 'A';
		x = (x - 27) % 26 + 1;
	}
	*p++ = x - 1 + 'A';
	sprintf(p, "%d", y);
	return sCellNameBuf;
}


void RandomCell(int* x, int* y)
{
	*x = Rand() % (sMaxX - 1) + 1;
	*y = Rand() % (sMaxY - 1) + 1;
	
	assert( *x >= 1 && *x < sMaxX );
	assert( *y >= 1 && *y < sMaxY );
}


void InsertFormula()
{
	int x, y, xr, yr;
	int i, n;
	
	RandomCell( &xr, &yr );
		
	if ( sCell(xr,yr).used ) {	/* replacing cell where some formulas depend upon */
		sMisses++;				/* with a new formula could introduce cycles */
		return;
	}
	sCell(xr,yr).used = TRUE;
	
	n = ( Rand() & 0x7 ) + 1;		/* 1 <= n <= 8 */
	
	assert( n >= 1 && n <= 8 );
	
	if ( sIndex + 2 * n + 1 > cMaxIndex )
		n = ( cMaxIndex - sIndex - 1 ) / 2;
	assert( sIndex + 2 * n + 1 <= cMaxIndex );
	
	sCell(xr,yr).sumIndex = sIndex;
	for (i = 0; i < n; i++ ) {
		while (TRUE) {
			RandomCell( &x, &y );
			if (x != xr || y != yr)
				break;
		}
		sCell(x,y).used = TRUE;
		sSumIndices[ sIndex++ ] = x;
		sSumIndices[ sIndex++ ] = y;
	}
	sSumIndices[ sIndex++ ] = 0;
}


void printCell ( int x, int y, bool cr )
{
	char	ch = ' ';
	int		i;
	
	if (cr)
		ch = '\n';
	
	if ( sCell(x,y).sumIndex == -1 ) {	/* simple value */
		printf("%d%c", sCell(x,y).value, ch );
	} else {
		i = sCell(x,y).sumIndex;
		printf("=%s", CellName( sSumIndices[i], sSumIndices[i+1] ) );
		i += 2;
		while ( sSumIndices[i] != 0 ) {
			printf("+%s", CellName( sSumIndices[i], sSumIndices[i+1] ) );
			i += 2;
		}
		printf("%c", ch );
	}
}

int main(int argc, char* argv[])
{
	int x, y;
	
	assert( argc == 3 );
	sMaxX = atoi(argv[1]);
	sMaxY = atoi(argv[2]);
	
	_sCell = (CELL*) malloc( sMaxX * sMaxY * sizeof(CELL) );
	assert( _sCell != 0 );
	sSumIndices = (int*) malloc( cMaxIndex * sizeof(int) );
	assert( sSumIndices != 0 );
	
	for (x = 1; x < sMaxX; x++)
		for (y = 1; y < sMaxY; y++) {
			sCell(x,y).value = Rand() + Rand();
			sCell(x,y).used = FALSE;
			sCell(x,y).sumIndex = -1;
		}
	
	sIndex = 0;
	sMisses = 0;
	while ( sIndex <= cMaxIndex - 3 && sMisses < sMaxX * sMaxY )
		InsertFormula(); 
		
	printf ("%d %d\n", sMaxX-1, sMaxY-1 );
	for (y = 1; y < sMaxY; y++)
		for (x = 1; x < sMaxX; x++)
			printCell( x, y, x == sMaxX - 1 );
		
	free(_sCell);
	free(sSumIndices);
	
	return 0;
}

