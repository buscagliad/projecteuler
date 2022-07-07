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
	sValid,
	sComplete} sState;



#define	CELL_ARRAY_NUM	9
#define	ROW_NUM		9
#define	COL_NUM		9
#define	CELL_ARRAY_SIZE (CELL_ARRAY_NUM)
#define ROW_SIZE	(ROW_NUM)
#define	COL_SIZE	(COL_NUM)


typedef struct cell {
	char		value;		/* if 0, cell is empty */
	cellState	state;
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

int		g_debug = DEBUG_OFF; //DEBUG_CHECK; // DEBUG_CELL | DEBUG_BLOCK;
#define IFDEBUG(dbg)		if (g_debug & dbg)
#define BLOCK(cr) ((cr) < 3 ? 0 : (cr) < 6 ? 3 : 6)


typedef	struct soduko {
	cellType	cell[ROW_SIZE][COL_SIZE];
	} sodukoType;



/* cell - init, set, get */

void	cellInit(cellType *cell, int value)
{
	cell->value = value;
	if (value) cell->state = cellFixed;
	else cell->state = cellEmpty;
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
	    printf("Invalid cell state - all values not possible\n");
	    return -1;
	}
	cell->state = cellFound;
	cell->value = value;
	return value;
}

int	cellGet(cellType *cell)
{
	return cell->value;
}


#define	MAX_FILE_LINE	256




/* file format:
 * all values single digits packed (no spaces), 0 indicates empty cell
 */
int	getValues(FILE *f, sodukoType &s)
{
	static	char	fileLine[MAX_FILE_LINE];

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
	return 1;

}

int	sodukoGetValue(sodukoType *s, int row, int col)
{
	return s->cell[row][col].value;

}

int	sodukoGetState(sodukoType *s, int row, int col)
{
	return s->cell[row][col].state;

}

int	sodukoGetNextNotValue(sodukoType *s, int row, int col)
{
	static	int	last_row = 0;
	static	int	last_col = 0;
	static	int index = 0;
	cellType	*thisCell = &(s->cell[row][col]);
	if (last_row != row  || last_col != col)
	{
		index = 0;
		last_row = row;
		last_col = col;
	}
	while (index < 9 && thisCell->notValues[index]) index++;
	if (index >= 9) return 0;
	return thisCell->notValues[index];

}

int	sodukoSetValue(sodukoType *s, int row, int col, int val)
{

	if (row < 1 || row > 9 ||
	    col < 1 || col > 9)
	{
	    printf("ERROR - setValue - bad row/col:  %i/%i\n", row, col);
	    return 0;
	}
	cellSet(&s->cell[row][col], val);
	return val;
}

sState	setNotValues(sodukoType *s);

int	sodukoInit(sodukoType *s, const char	*fName)
{
	FILE	*f = fopen(fName, "r");
	if (!f) return -1;
	IFDEBUG(DEBUG_INIT) printf("opening file %s\n", fName);

	getValues(f, *s);
	setNotValues(s);
	return 1;
}

/*
             111111111122222222223333333
   0123456789012345678901234567890123456
 0 +===+===+===+===+===+===+===+===+===+
 1 [   |   |   |   |   |   |   |   |   |
 2 +---+---+---+---+---+---+---+---+---+
 3 [   |   |   |   |   |   |   |   |   |
 4 +---+---+---+---+---+---+---+---+---+
 5 [   |   |   |   |   |   |   |   |   |
 6 +===+===+===+===+===+===+===+===+===+
 7 [   |   |   |   |   |   |   |   |   |
 8 +---+---+---+---+---+---+---+---+---+
 9 [   |   |   |   |   |   |   |   |   |
10 +---+---+---+---+---+---+---+---+---+
11 [   |   |   |   |   |   |   |   |   |
12 +===+===+===+===+===+===+===+===+===+
13 [   |   |   |   |   |   |   |   |   |
14 +---+---+---+---+---+---+---+---+---+
15 [   |   |   |   |   |   |   |   |   |
16 +---+---+---+---+---+---+---+---+---+
17 [   |   |   |   |   |   |   |   |   |
18 +===+===+===+===+===+===+===+===+===+
*/

void	sodukoDump(sodukoType *s)
{
	int	r;
	int	c;
	const char	*draw;
	char	endch;

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

	    for (c = 0; c < 9; c++)
	    {
                printf("%s", draw);
	    }
	    printf("%c\n", endch);

	    if (r != 9)
	    {
		for (c = 0; c < 9; c++)
	        {
		    int	v = sodukoGetValue(s, r, c);
		    if (v) printf("| %i ", v);
		    else printf("|   ");
	        }
	        printf("|\n");
	    }
	}
}
void	sodukoDumpInvalid(sodukoType *s)
{
	int		r;
	int		c;


	for (r = 0; r < 9; r++)
	{
		for (c = 0; c < 9; c++)
	    {
		    int	v = sodukoGetValue(s, r, c);
		    int nv = sodukoGetNextNotValue(s, r, c);
		    printf("[%i,%i] = %i", r, c, v);
		    switch (sodukoGetState(s, r, c))
		    {
				case cellFixed:
					printf(" - FIXED\n");
					continue;
				case cellFound:
					printf(" - FOUND\n");
					continue;
				case cellActive:
				case cellEmpty:
					break;
		    }
		    if (nv) printf(" - NV: %i", nv);
		    else printf(" - NO INVALID CELLS\n");
		    while ((nv = sodukoGetNextNotValue(s, r, c)))
		    	printf(", %i", nv);
	    }
	}
}


sState   setNotValueCell(sodukoType *s, int cr, int cc)
{
	int thatCell;
	int thisCell = sodukoGetValue(s, cr, cc);
	// set row && col for invalid numbers
	for (int i = 0; i < 9; i++)
	{
		// check for all row elements
	    if (i != cr)
	    {
			thatCell = sodukoGetValue(s, i, cc);
			if (thatCell != 0)
			{
				s->cell[cr][cc].notValues[thatCell] = true;
				IFDEBUG(DEBUG_CHECK) printf("[%d,%d]::setNotValueCell--ROW: [%i,%i]=%i\n", cr, cc, i, cc, thatCell);
				if (thisCell == thatCell)
				{
					IFDEBUG(DEBUG_CHECK) printf("setNotValueCell--ROW INVALID: thisCell: (%i,%i)=%i  "
						"rowCell: (%i,%i)=%i\n",
						cr, cc, thisCell,
						i, cc, thatCell);
					return sInvalid;
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
			thatCell = sodukoGetValue(s, cr, i);
			if (thatCell != 0)
			{
				s->cell[cr][cc].notValues[thatCell] = true;
				IFDEBUG(DEBUG_CHECK) printf("[%d,%d]::setNotValueCell--COL: [%i,%i]=%i\n",  cr, cc, cr, i, thatCell);
				if (thisCell == thatCell)
				{
					IFDEBUG(DEBUG_CHECK) printf("setNotValueCell--COL INVALID: thisCell: (%i,%i)=%i  "
						"colCell: (%i,%i)=%i\n",
						cr, cc, thisCell,
						cr,  i, thatCell);
					return sInvalid;
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
				cr, cc, cr%3, cc%3);
	}
	for (int c = BLOCK(cc); c < BLOCK(cc) + 3; c++)
	{
	    for (int r = BLOCK(cr); r < BLOCK(cr) + 3; r++)
	    {
	        if (c == cc && r == cr) continue;
	        thatCell = sodukoGetValue(s, r, c);
		    if (!thatCell) continue;
			IFDEBUG(DEBUG_CHECK) printf("[%d,%d]::setNotValueCell--BLOCK: [%i,%i]=%i\n", cr, cc, r, c, thatCell);
	        if (thisCell == thatCell)
	        {
		        IFDEBUG(DEBUG_CHECK) printf("setNotValueCell--BLOCK INVALID: thisCell: (%i,%i)=%i  "
			        "rowCell: (%i,%i)=%i\n",
			        cr, cc, thisCell,
			         r,  c, thatCell);
		        return sInvalid;
	        }
	    }
	}
	/*
	 * Now we look at the 'not' values, if there is only one,
	 * we will set the cell to 'Found'
	 */
	int ccount = 0;
	for (int v = 1; v <= 9; v++)
	{
	    if (!s->cell[cr][cc].notValues[v])
	    {
			ccount++;
			thisCell = v;
	    }
	}
	if (ccount == 1) /* only 1 possible value */
	{
	    s->cell[cr][cc].value = thisCell;
	    if (s->cell[cr][cc].state != cellFixed)
			s->cell[cr][cc].state = cellFound;
	    IFDEBUG(DEBUG_PROCESS)printf("setNotValueCell--Cell (%i,%i) set to value: %i\n",
			cr, cc, thisCell);
	    return sComplete;
	}
	return sValid;
}
	

/*
 * setNotValues will set the notValues array to mark each value
 * that the cell CANNOT be
 */
sState	setNotValues(sodukoType *s)
{
	for (int r = 0; r < 9; r++)
	{
		for (int c = 0; c < 9; c++)
		{
			if (setNotValueCell(s, r, c) != sValid) return sInvalid;
		}
	}
	return sValid;
}

/*
 * checkCell will test the past in cell to determine
 * if the cell is valid or not
 */
sState	checkCell(sodukoType *s, int crow, int ccol, sState rv)
{
	int	r;
	int	c;
	int	v;
	int	thisCell = sodukoGetValue(s, crow, ccol);
	int	thatCell;
	int	ccount = 0;

	if (thisCell == 0) return sValid;
	/*
	 * Check each row element for duplication (of course exclude
	 * the row containing this element
	 */
	for (r = 0; r < 9; r++)
	{
	    if (r == crow) continue;
	    thatCell = sodukoGetValue(s, r, ccol);
	    IFDEBUG(DEBUG_CHECK) printf("checkCell--UU: [%i,%i]=%i\n", r, ccol, thatCell);
	    if (!thatCell) continue;
	    if (thisCell == thatCell)
	    {
		    IFDEBUG(DEBUG_CHECK) printf("checkCell--ROW INVALID: thisCell: (%i,%i)=%i  "
			    "rowCell: (%i,%i)=%i\n",
			    crow, ccol, thisCell,
			    r, ccol, thatCell);
		    return sInvalid;
	    }
	}
	/*
	 * Check each column element for duplication,
	 * of course, exclude the columne containing this
	 * element
	 */
	for (c = 0; c < 9; c++)
	{
	    if (c == ccol) continue;
	    thatCell = sodukoGetValue(s, crow, c);
	    if (!thatCell) continue;
	    if (thisCell == thatCell)
	    {
		    printf("checkCell--COL INVALID: thisCell: (%i,%i)=%i  "
			    "rowCell: (%i,%i)=%i\n",
			    crow, ccol, thisCell,
			    r, ccol, thatCell);
		    return sInvalid;
	    }
	}
	/*
	 * Now check for duplication within the element's
	 * block (again - avoid checking itself)
	 */
	IFDEBUG(DEBUG_BLOCK)
	{
		printf("checkCell--Row: %i  Col: %i -- BLOCK START:: Row: %i Col: %i\n",
				crow, ccol, crow%3, ccol%3);
	}
	for (c = BLOCK(ccol); c < BLOCK(ccol) + 3; c++)
	{
	    for (r = BLOCK(crow); r < BLOCK(crow) + 3; r++)
	    {
			//printf("cr: %d  cc: %d  c: %d  r: %d\n", crow, ccol, c, r);
	        if (c == ccol && r == crow) continue;
	        thatCell = sodukoGetValue(s, r, c);
		    if (!thatCell) continue;
	        if (thisCell == thatCell)
	        {
		        printf("checkCell--BLOCK INVALID: thisCell: (%i,%i)=%i  "
			        "rowCell: (%i,%i)=%i\n",
			        crow, ccol, thisCell,
			        r, c, thatCell);
		        return sInvalid;
	        }
	    }
	}
	/*
	 * Now we look at the 'not' values, if there is only one,
	 * we will set the cell to 'Found'
	 */
	ccount = 0;
	for (v = 1; v <= 9; v++)
	{
	    if (!(s->cell[crow][ccol].notValues[v]))
	    {
			ccount++;
			thisCell = v;
	    }
	}
	if (ccount == 1) /* only 1 possible value */
	{
	    s->cell[crow][ccol].value = thisCell;
	    if (s->cell[crow][ccol].state != cellFixed)
			s->cell[crow][ccol].state = cellFound;
	    IFDEBUG(DEBUG_PROCESS)printf("checkCell--Cell (%i,%i) set to value: %i\n",
			crow, ccol, thisCell);
	    return sComplete;
	}
	return sValid;

}

/*
 * Check each cell in the soduko game for validity
 */
bool	guess(sodukoType *s)
{
	int	r;
	int	c;
	int mi = 100;
	int mr;
	int mc;

	for (r = 0; r < 9; r++)
	{
	    for (c = 0; c < 9; c++)
	    {
		    if (s->cell[r][c].state == cellEmpty)
			{
				int mm = 0;
				for (int k = 1; k <= 9; k++) 
					if (!(s->cell[r][c].notValues[k])) mm++;
				if (mm < mi)
				{
					mi = mm;
					mr = r;
					mc = c;
				}
			}
	    }
	}
	printf("Empty cell count is %d at cell (%d,%d)\n", mi, mr, mc);
	for (int k = 1; k <= 9; k++) 
		printf("NV:%d - %d ", k, s->cell[mr][mc].notValues[k]);
	printf("\n");
	int index = 1;
	while (index <= 9  &&  s->cell[mr][mc].notValues[index]) index++;
	s->cell[mr][mc].value =  index;
	for (int i = 0; i < 9; i++)
	{
		s->cell[i][mc].notValues[index] = true;
		s->cell[mr][i].notValues[index] = true;
	}
	for (r = mr%3; r < mr%3 + 3; r++)
	{
		for (c = mc%3; c < mc%3 + 3; c++)
		{
			s->cell[r][c].notValues[index] = true;
		}
	}
	printf("Setting cell [%d,%d] to %d\n", mr, mc, s->cell[mr][mc].value);
	return true;
}

/*
 * Check each cell in the soduko game for validity
 */
sState	check(sodukoType *s)
{
	int	r;
	int	c;
	sState	rv = sComplete;
	sState	xv;

	for (r = 0; r < 9; r++)
	{
	    for (c = 0; c < 9; c++)
	    {
		    xv = checkCell(s, r, c, rv);
		    if (xv == sInvalid) return xv;
		    if (xv != sComplete && rv == sComplete)
		    {
		    	rv = sValid;
		    }

	    }
	}
	return rv;
}

bool solve(soduko s)
{
	if (check(&s) == sComplete) {
		sodukoDump(&s);
		return true;
	}
	
	guess(&s);
	sodukoDump(&s);
	solve(s);
		
	return false;
}

int	main(int argc, char *argv[])
{
	const char *fname = "p096_sudoku.txt";
	sodukoType	s;
	int			i;


	IFDEBUG(DEBUG_INIT)
	{
		for (i = 0; i < argc; i++)
			printf("argv[%i] = %s\n", i, argv[i]);
	}

	if (sodukoInit(&s, fname) < 0)
	{
	     printf("ERROR - cannot open file %s\n", fname);
	     return 1;
	}

	sodukoDump(&s);
	solve(s);
	for (i = 1; i <= -1; i++){
		if (check(&s) == sComplete) printf("PUZZLE SOLVED!!!!\n");
		sodukoDump(&s);
		//sodukoDumpInvalid(&s);
	}
	return 0;

}

