#ifdef PROBLEM_DESCRIPTION

A well constructed Su Doku puzzle has a unique solution and can be solved by logic, although it may be necessary to employ "guess and test" methods in order to eliminate options (there is much contested opinion over this). The complexity of the search determines the difficulty of the puzzle; the example above is considered easy because it can be solved by straight forward direct deduction.

The 6K text file, sudoku.txt (right click and 'Save Link/Target As...'), contains fifty different Su Doku puzzles ranging in difficulty, but all with unique solutions (the first puzzle in the file is the example above).

By solving all fifty puzzles find the sum of the 3-digit numbers found in the top left corner of each solution grid; for example, 483 is the 3-digit number found in the top left corner of the solution grid above.
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>

typedef	enum {
	cellEmpty,	/* cell has no value */
	cellFixed,	/* cell has fixed value from start */
	cellActive,	/* this state indicates the cell is being actively
				processed */
	cellFound	/* value for this cell has been determined */
	} cellState;

#define	CELL_ARRAY_NUM	9
#define	ROW_NUM		9
#define	COL_NUM		9
#define	CELL_ARRAY_SIZE (CELL_ARRAY_NUM)
#define ROW_SIZE	(ROW_NUM)
#define	COL_SIZE	(COL_NUM)


FILE	*ftxt;

typedef struct cell {
	int		value;		/* if 0, cell is empty */
	cellState	state;
	int		notValues[CELL_ARRAY_SIZE+1];
	} cellType;

#define	DEBUG_OFF     0x0000
#define	DEBUG_INPUT	  0x0001
#define	DEBUG_CHECK   0x0002
#define	DEBUG_CELL	  0x0004
#define	DEBUG_BLOCK	  0x0008
#define DEBUG_INIT	  0x0010
#define DEBUG_PROCESS 0x0020

#define DEBUG_ALL	  0xFFFF

int		g_debug = DEBUG_CELL | DEBUG_BLOCK;
#define IFDEBUG(dbg)		if (g_debug & dbg)


typedef	struct soduko {
	cellType	cell[ROW_SIZE][COL_SIZE];
	} sodukoType;

#define VALUE(s, br, bc, cr, cc)	s->block[br][bc].cell[cr][cc].value

/* cell - init, set, get */

void	cellInit(cellType *cell, int row, int col, int value)
{
	int	i;

	cell->value = value;
	if (value) cell->state = cellFixed;
	else cell->state = cellEmpty;
	for (i = 1; i <= CELL_ARRAY_NUM; i++)
	{
	    if (i == value)
	        cell->notValues[i] = 0;
	    else
	        cell->notValues[i] = 1;
	}
	IFDEBUG(DEBUG_INIT) fprintf(ftxt, "R: %i  C: %i   V: %i\n", row, col, value);
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
	for (int row = 1; row <= ROW_NUM; row++)
	{
		for (int col = 1; col <= COL_NUM; col++)
		{
			int c = fgetc(f) - '0';
			cellInit(&(s.cell[row][col]), row, col, c);
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


int	sodukoInit(sodukoType *s, const char	*fName)
{
	FILE	*f = fopen(fName, "r");
	if (!f) return -1;
	IFDEBUG(DEBUG_INIT) fprintf(ftxt, "opening file %s\n", fName);

	getValues(f, *s);
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

void	sodukoDump(sodukoType *s, FILE *f)
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
                fprintf(f, "%s", draw);
	    }
	    fprintf(f, "%c\n", endch);

	    if (r != 9)
	    {
		for (c = 0; c < 9; c++)
	        {
		    int	v = sodukoGetValue(s, r, c);
		    if (v) fprintf(f, "| %i ", v);
		    else fprintf(f, "|   ");
	        }
	        fprintf(f, "|\n");
	    }
	}
}
void	sodukoDumpInvalid(sodukoType *s, FILE *f)
{
	int		r;
	int		c;


	for (r = 0; r < 9; r++)
	{
		for (c = 0; c < 9; c++)
	    {
		    int	v = sodukoGetValue(s, r, c);
		    int nv = sodukoGetNextNotValue(s, r, c);
		    fprintf(f, "[%i,%i] = %i", r, c, v);
		    switch (sodukoGetState(s, r, c))
		    {
				case cellFixed:
					fprintf(f, " - FIXED\n");
					continue;
				case cellFound:
					fprintf(f, " - FOUND\n");
					continue;
				case cellActive:
				case cellEmpty:
					break;
		    }
		    if (nv) fprintf(f, " - NV: %i", nv);
		    else fprintf(f, " - NO INVALID CELLS\n");
		    while ((nv = sodukoGetNextNotValue(s, r, c)))
		    	fprintf(f, ", %i", nv);
	    }
	}
}

typedef	enum {
	sInvalid,
	sValid,
	sComplete} sState;

#define	BLOCK(c)	((c) < 3 ? 0 : (c) < 6 ? 3 : 6)
#define	CNV(v)		s->cell[crow][ccol].notValues[v]
#define	CST		s->cell[crow][ccol].state
#define	CV		s->cell[crow][ccol].value
#define NV(t, v)		if (!CNV(v)) { \
			   fprintf(ftxt, "%s:: Not value for (%i,%i) %i set\n", \
				t, crow, ccol, v); \
			   CNV(v) = 1; \
			   ccount++; \
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
	    fprintf(ftxt, "UU: [%i,%i]=%i\n", r, ccol, thatCell);
	    if (!thatCell) continue;
	    if (thisCell == thatCell)
	    {
		    fprintf(ftxt, "ROW INVALID: thisCell: (%i,%i)=%i  "
			    "rowCell: (%i,%i)=%i\n",
			    crow, ccol, thisCell,
			    r, ccol, thatCell);
		    return sInvalid;
	    }
	    NV("Row check", thatCell);
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
		    fprintf(ftxt, "COL INVALID: thisCell: (%i,%i)=%i  "
			    "rowCell: (%i,%i)=%i\n",
			    crow, ccol, thisCell,
			    r, ccol, thatCell);
		    return sInvalid;
	    }
	    NV("Col check", thatCell);
	}
	/*
	 * Now check for duplication within the element's
	 * block (again - avoid checking itself)
	 */
	IFDEBUG(DEBUG_BLOCK)
	{
		fprintf(ftxt, "Row: %i  Col: %i -- BLOCK START:: Row: %i Col: %i\n",
				crow, ccol, BLOCK(crow), BLOCK(ccol));
	}
	for (c = BLOCK(ccol); c < BLOCK(ccol) + 3; c++)
	{
	    for (r = BLOCK(crow); r < BLOCK(crow) + 3; r++)
	    {
	        if (c == ccol && r == crow) continue;
	        thatCell = sodukoGetValue(s, r, c);
		    if (!thatCell) continue;
	        if (thisCell == thatCell)
	        {
		        fprintf(ftxt, "BLOCK INVALID: thisCell: (%i,%i)=%i  "
			        "rowCell: (%i,%i)=%i\n",
			        crow, ccol, thisCell,
			        r, c, thatCell);
		        return sInvalid;
	        }
	        NV("BLOCK check", thatCell);
	    }
	}
	/*
	 * Now we look at the 'not' values, if there is only one,
	 * we will set the cell to 'Found'
	 */
	ccount = 0;
	for (v = 1; v <= 9; v++)
	{
	    if (!CNV(v))
	    {
		ccount++;
		thisCell = v;
	    }
	}
	if (ccount == 1) /* only 1 possible value */
	{
	    CV = thisCell;
	    CST = cellFound;
	    IFDEBUG(DEBUG_PROCESS)fprintf(ftxt, "Cell (%i,%i) set to value: %i\n",
			crow, ccol, thisCell);
	    return sComplete;
	}
	return sValid;

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


int	main(int argc, char *argv[])
{
	const char *fname = "p096_sudoku.txt";
	sodukoType	s;
	int			i;

	ftxt = fopen("soduko.out", "w");

	IFDEBUG(DEBUG_INIT)
	{
		for (i = 0; i < argc; i++)
			fprintf(ftxt, "argv[%i] = %s\n", i, argv[i]);
	}

	if (sodukoInit(&s, fname) < 0)
	{
	     printf("ERROR - cannot open file %s\n", fname);
	     return 1;
	}

	sodukoDump(&s, ftxt);
	for (i = 1; i <= 10; i++){
		check(&s);
		sodukoDump(&s, ftxt);
		sodukoDumpInvalid(&s, ftxt);
	}
	if (!ftxt) printf("Could not open soduko.out\n");
	fclose(ftxt);
	return 0;

}

