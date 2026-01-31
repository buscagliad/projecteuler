#ifdef PROBLEM_DESCRIPTION

A well constructed Su Doku puzzle has a unique solution and can be solved by logic, although it may be necessary to employ "guess and test" methods in order to eliminate options (there is much contested opinion over this). The complexity of the search determines the difficulty of the puzzle; the example above is considered easy because it can be solved by straight forward direct deduction.

The 6K text file, sudoku.txt (right click and 'Save Link/Target As...'), contains fifty different Su Doku puzzles ranging in difficulty, but all with unique solutions (the first puzzle in the file is the example above).

By solving all fifty puzzles find the sum of the 3-digit numbers found in the top left corner of each solution grid; for example, 483 is the 3-digit number found in the top left corner of the solution grid above.

Grid 00
483921657
967345821
251876493
548132976
729564138
136798245
372689514
814253769
695417382

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>

typedef	enum {
	cellEmpty,	/* cell has no value */
	cellActive,	/* this state indicates the cell is being actively
				processed */
	cellFixed,	/* cell has fixed value from start */
	cellFound	/* value for this cell has been determined */
	} cellState;

typedef	enum {
	sInvalid,
	sEmpty,
	sValid,
	sComplete} sState;

const char *STATE[] = {
	"Empty",
	"Active",
	"Fixed",
	"Found" };

#define	CELL_ARRAY_NUM	9
#define	ROW_NUM		9
#define	COL_NUM		9
#define	CELL_ARRAY_SIZE (CELL_ARRAY_NUM)
#define ROW_SIZE	(ROW_NUM)
#define	COL_SIZE	(COL_NUM)


typedef struct {
	char		value;		/* if 0, cell is empty */
	bool		notValues[CELL_ARRAY_SIZE+1]; // pv[n] is false if n is possible
	} cellType;

#define	DEBUG_OFF     0x0000
#define	DEBUG_INPUT	  0x0001
#define	DEBUG_CHECK   0x0002
#define	DEBUG_CELL	  0x0004
#define	DEBUG_BLOCK	  0x0008
#define DEBUG_INIT	  0x0010
#define DEBUG_PROCESS 0x0020

#define DEBUG_ALL	  0xFFFF

int		g_debug = DEBUG_OFF; // DEBUG_CELL | DEBUG_BLOCK;
#define IFDEBUG(dbg)		if (g_debug & dbg)
#define BLOCK(cr) ((cr) < 3 ? 0 : (cr) < 6 ? 3 : 6)

int     gPuzzleNumber = 0;

typedef	struct soduko {
	cellType	cell[ROW_SIZE][COL_SIZE];
	bool		complete;
	} sodukoType;


int upperThree(sodukoType &s)
{
	return 100*s.cell[0][0].value + 10*s.cell[0][1].value + s.cell[0][2].value ;
}


/* cell - init, set, get */

void	cellInit(cellType *cell, int value)
{
	cell->value = value;
	for (int i = 0; i <= 9; i++) cell->notValues[i] = false;
	//cell->nvc = 0;
}

int	cellSet(cellType *cell, int value)
{
	int	i;
	for (i= 1; i <= 9; i++)
	    if (i != value  && cell->notValues[i]) return 0;
	if (cell->notValues[value])
	{
	    printf("Invalid cell state - %d value not possible\n", value);
	    return -1;
	}
	cell->value = value;
	return value;
}

int	cellGet(cellType *cell)
{
	return cell->value;
}


#define	MAX_FILE_LINE	256



bool   setNotValueCell(sodukoType &s, int cr, int cc)
{
	int thatCell;
	int thisCell = s.cell[cr][cc].value;
	// set row && col for invalid numbers
	for (int i = 0; i < 9; i++)
	{
		// check for all row elements
	    if (i != cr)
	    {
			thatCell = s.cell[i][cc].value;
			if (thatCell != 0)
			{
				s.cell[cr][cc].notValues[thatCell] = true;
				IFDEBUG(DEBUG_CHECK) printf("[%d,%d]::setNotValueCell--ROW: [%i,%i]=%i\n", cr, cc, i, cc, thatCell);
				if (thisCell == thatCell)
				{
					IFDEBUG(DEBUG_CHECK) printf("setNotValueCell--ROW INVALID: thisCell: (%i,%i)=%i  "
						"rowCell: (%i,%i)=%i\n",
						cr, cc, thisCell,
						i, cc, thatCell);
					return false;
				}
			}
		}
		
		// check for all col elements
		/*
		 * Check each column element for duplication,
		 * of course, exclude the columne containing this
		 * element
		 */
	    if (i != cc)
	    {
			thatCell = s.cell[cr][i].value; //sodukoGetValue(s, cr, i);
			if (thatCell != 0)
			{
				s.cell[cr][cc].notValues[thatCell] = true;
				IFDEBUG(DEBUG_CHECK) printf("[%d,%d]::setNotValueCell--COL: [%i,%i]=%i\n",  cr, cc, cr, i, thatCell);
				if (thisCell == thatCell)
				{
					IFDEBUG(DEBUG_CHECK) printf("setNotValueCell--COL INVALID: thisCell: (%i,%i)=%i  "
						"colCell: (%i,%i)=%i\n",
						cr, cc, thisCell,
						cr,  i, thatCell);
					return false;
				}
			}
		}
	}

	/*
	 * Now check for duplication within the element's
	 * block (again - avoid checking itself)
	 */
	IFDEBUG(DEBUG_BLOCK)
	{
		printf("setNotValueCell--Row: %i  Col: %i -- BLOCK START:: Row: %i Col: %i\n",
				cr, cc, BLOCK(cr), BLOCK(cc));
	}
	for (int c = BLOCK(cc); c < BLOCK(cc) + 3; c++)
	{
	    for (int r = BLOCK(cr); r < BLOCK(cr) + 3; r++)
	    {
	        if (c == cc && r == cr) continue;
	        thatCell = s.cell[r][c].value; // sodukoGetValue(s, r, c);
		    if (thatCell != 0)
		    {
				s.cell[cr][cc].notValues[thatCell] = true;
				IFDEBUG(DEBUG_CHECK) printf("[%d,%d]::setNotValueCell--BLOCK: [%i,%i]=%i\n", cr, cc, r, c, thatCell);
				if (thisCell == thatCell)
				{
					IFDEBUG(DEBUG_CHECK) printf("setNotValueCell--BLOCK INVALID: thisCell: (%i,%i)=%i  "
						"rowCell: (%i,%i)=%i\n",
						cr, cc, thisCell,
						 r,  c, thatCell);
					return false;
				}
			}
	    }
	}

	return true;
}
	

/*
 * setNotValues will set the notValues array to mark each value
 * that the cell CANNOT be
 */
bool	setNotValues(sodukoType &s)
{
	for (int r = 0; r < 9; r++)
	{
		for (int c = 0; c < 9; c++)
		{
			if (!setNotValueCell(s, r, c)) return false;
		}
	}
	return true;
}



bool   setValueCell(sodukoType &s, int cr, int cc, int thisCell)
{
	s.cell[cr][cc].value = thisCell;
	// set 'thisCell' as an invalid value for its relatives
	for (int i = 0; i < 9; i++)
	{
		// set for all row elements
	    if (i != cr)
	    {
			s.cell[i][cc].notValues[thisCell] = true;
		}
		
		// set for all col elements
		/*
		 * Check each column element for duplication,
		 * of course, exclude the columne containing this
		 * element
		 */
	    if (i != cc)
	    {
			s.cell[cr][i].notValues[thisCell] = true; //sodukoGetValue(s, cr, i);
		}
	}

	/*
	 * Now check for duplication within the element's
	 * block (again - avoid checking itself)
	 */
	for (int c = BLOCK(cc); c < BLOCK(cc) + 3; c++)
	{
	    for (int r = BLOCK(cr); r < BLOCK(cr) + 3; r++)
	    {
	        if (c == cc && r == cr) continue;
	        s.cell[r][c].notValues[thisCell] = true; // sodukoGetValue(s, r, c);
	    }
	}

	return true;
}
	

/* file format:
 * all values single digits packed (no spaces), 0 indicates empty cell
 */
int	getValues(FILE *f, sodukoType &s)
{
	static	char	fileLine[MAX_FILE_LINE];
	gPuzzleNumber++;
	if (!f) return -1;
	fgets(fileLine, MAX_FILE_LINE, f);
	for (int row = 0; row < ROW_NUM; row++)
	{
		for (int col = 0; col < COL_NUM; col++)
		{
			int c = fgetc(f) - '0';
			cellInit(&(s.cell[row][col]), c);
			IFDEBUG(DEBUG_INIT) printf("R: %i  C: %i   V: %i\n", row, col, c);
		}
		fgetc(f); // get eol
	}
	setNotValues(s);
	s.complete = false;
	return 1;

}

int	sodukoGetValue(sodukoType &s, int row, int col)
{
	return s.cell[row][col].value;

}

int	sodukoGetNextNotValue(sodukoType &s, int row, int col, int &index)
{
	cellType	*thisCell = &(s.cell[row][col]);
	while (index <= 9 && thisCell->notValues[index]) index++;
	if (index > 9) return 0;
	return index++;
}


FILE *sodukoInit(const char	*fName)
{
	FILE	*f = fopen(fName, "r");
	if (!f) return NULL;
	IFDEBUG(DEBUG_INIT) printf("opening file %s\n", fName);

	return f;
}

/*
             111111111122222222223333333
   0123456789012345678901234567890123456
     0   1   2   3   4   5   6   7   8
 0 +===+===+===++===+===+===+===+===+===+
 1 [   |   |   ||   |   |   |   |   |   | 0
 2 +---+---+---++---+---+---+---+---+---+
 3 [   |   |   ||   |   |   |   |   |   | 1
 4 +---+---+---++---+---+---+---+---+---+
 5 [   |   |   ||   |   |   |   |   |   | 2
 6 +===+===+===++===+===+===+===+===+===+
 7 [   |   |   ||   |   |   |   |   |   | 3
 8 +---+---+---++---+---+---+---+---+---+
 9 [   |   |   ||   |   |   |   |   |   | 4
10 +---+---+---++---+---+---+---+---+---+
11 [   |   |   ||   |   |   |   |   |   | 5
12 +===+===+===++===+===+===+===+===+===+
13 [   |   |   ||   |   |   |   |   |   | 6
14 +---+---+---++---+---+---+---+---+---+
15 [   |   |   ||   |   |   |   |   |   | 7
16 +---+---+---++---+---+---+---+---+---+
17 [   |   |   ||   |   |   |   |   |   | 8
18 +===+===+===++===+===+===+===+===+===+
*/

void	sodukoDump(sodukoType &s)
{
	int	r;
	int	c;
	const char	*draw;
	char	endch;
	printf("Puzzle Number: %d\n", gPuzzleNumber);
	printf("    0   1   2   3   4   5   6   7   8\n");

	for (r = 0; r <= 9; r++)
	{
        if (r == 0 || r == 3 || r == 6 || r == 9)
	    {
	        draw = "+===";
	        endch = '+';
	    }
	    else
	    {
	        draw = "+---";
	        endch = '+';
	    }

        printf("  %s", draw);
	    for (c = 1; c < 9; c++)
	    {
                printf("%s", draw);
	    }
	    printf("%c\n", endch);

	    if (r != 9)
	    {
			printf("%d ", r);
			for (c = 0; c < 9; c++)
			{
				int	v = sodukoGetValue(s, r, c);
				if (v) printf("| %i ", v);
				else printf("|   ");
			}
			printf("|\n");
	    }
	}
	printf("First three nums: %d\n", upperThree(s));
	fflush(stdout);
}
void	sodukoDumpInvalid(sodukoType &s)
{
	int		r;
	int		c;
	int		nvIndex = 0;

	for (r = 0; r < 9; r++)
	{
		for (c = 0; c < 9; c++)
	    {
		    int	v = sodukoGetValue(s, r, c);
		    nvIndex = 1;
		    int nv = sodukoGetNextNotValue(s, r, c, nvIndex);
		    printf("[%i,%i] = %i", r, c, v);
		    if (nv) printf(" - NV: %i", nv);
		    else printf(" - NO INVALID CELLS");
		    while ((nv = sodukoGetNextNotValue(s, r, c, nvIndex)))
		    	printf(", %i", nv);
		    printf("\n");
	    }
	}
}




bool zerovec(bool *v)
{
	bool rv = false;
	for (int k = 1; k <= 9; k++) rv |= v[k];
	return rv;
}


/*
 * Check each cell in the soduko game for validity
 */
 #define NO_GUESS_AVAILABLE 100
bool	getPossibles(sodukoType &s, int &mr, int &mc, int *mi, int &emptyCells)
{
	int	r;
	int	c;
	int min = NO_GUESS_AVAILABLE;
	
	emptyCells = 0;

	for (r = 0; r < 9; r++)
	{
	    for (c = 0; c < 9; c++)
	    {
		    if (s.cell[r][c].value == 0)
			{
				emptyCells++;
				int mm = 0;
				for (int k = 1; k <= 9; k++) 
					if (!(s.cell[r][c].notValues[k])) mm++;
				if (mm == 0) continue;
				if (mm < min)
				{
					min = mm;
					mr = r;
					mc = c;
				}
			}
	    }
	}
	if (min == NO_GUESS_AVAILABLE) return false;
	
	for (int k = 1; k <= 9; k++) if ( !s.cell[mr][mc].notValues[k] ) *mi++ = k;
	*mi = 0;

	return true;
}


sodukoType solve(sodukoType s)
{
	int values[10];
	int *pv;
	int r, c;
	int numEmptyCells = 0;
		
	if (!getPossibles(s, r, c, values, numEmptyCells))
	{
		if (numEmptyCells == 0)
		{
			printf("SOLUTION!!!!\n");
			s.complete = true;
		}
		else
		{
			//printf("RETURNING at %d,%d with %d empty cells\n", r, c, numEmptyCells);
		}
		return s;
	}
	pv = values;
	//printf("getMinCell:: ");
	//for (int k = 0; pv[k]; k++) printf(" %d", pv[k]);
	//printf("\n");
	sodukoType ssave = s;
	while(!s.complete && *pv)
	{
		s = ssave;
		//printf("SETTING [%d,%d] to %d\n", r, c, *pv);
		setValueCell(s, r, c, *pv);
		pv++;
		s = solve(s);
	}
	return s;
}

int	main(int argc, char *argv[])
{
	const char *fname = "p096_sudoku.txt";
	sodukoType	s;
	int			i;
	FILE 		*f;

	IFDEBUG(DEBUG_INIT)
	{
		for (i = 0; i < argc; i++)
			printf("argv[%i] = %s\n", i, argv[i]);
	}

	if ( (f = sodukoInit(fname)) == NULL)
	{
	     printf("ERROR - cannot open file %s\n", fname);
	     return 1;
	}

	getValues(f, s);
	int sum = 0;
	while (!feof(f)) {
		sodukoType ss = solve(s);
		sodukoDump(ss);
		sum += upperThree(ss);
		getValues(f, s);
	}
	printf("Sum of first digits is %d\n", sum);
	return 0;

}
