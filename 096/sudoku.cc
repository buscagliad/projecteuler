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

int     gPuzzleNumber = 0;

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
	    printf("Invalid cell state - %d value not possible\n", value);
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

int	sodukoGetNextNotValue(sodukoType *s, int row, int col, int &index)
{
	cellType	*thisCell = &(s->cell[row][col]);
	while (index <= 9 && thisCell->notValues[index]) index++;
	if (index > 9) return 0;
	return index++;
}

sState	setNotValues(sodukoType *s);

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

void	sodukoDump(sodukoType *s)
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
	fflush(stdout);
}
void	sodukoDumpInvalid(sodukoType *s)
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
		    switch (sodukoGetState(s, r, c))
		    {
				case cellFixed:
					printf(" - FIXED\n");
					continue;
				case cellFound:
					printf(" - FOUND\n");
					continue;
				case cellActive:
					printf(" - ACTIVE");
				case cellEmpty:
					break;
		    }
		    if (nv) printf(" - NV: %i", nv);
		    else printf(" - NO INVALID CELLS");
		    while ((nv = sodukoGetNextNotValue(s, r, c, nvIndex)))
		    	printf(", %i", nv);
		    printf("\n");
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
				cr, cc, BLOCK(cr), BLOCK(cc));
	}
	for (int c = BLOCK(cc); c < BLOCK(cc) + 3; c++)
	{
	    for (int r = BLOCK(cr); r < BLOCK(cr) + 3; r++)
	    {
	        if (c == cc && r == cr) continue;
	        thatCell = sodukoGetValue(s, r, c);
		    if (thatCell != 0)
		    {
				s->cell[cr][cc].notValues[thatCell] = true;
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
	int	thisCell = sodukoGetValue(s, crow, ccol);
	int	thatCell;

	if (thisCell == 0) return sEmpty;
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
		    printf("checkCell--ROW INVALID: thisCell: (%i,%i)=%i  "
			    "rowCell: (%i,%i)=%i\n",
			    crow, ccol, thisCell,
			    r, ccol, thatCell);
			fflush(stdout);
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
			fflush(stdout);
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
				crow, ccol, BLOCK(crow), BLOCK(ccol));
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
				fflush(stdout);
		        return sInvalid;
	        }
	    }
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
		    if (xv == sEmpty)
		    {
		    	rv = sValid;
		    }

	    }
	}
	return rv;
}

/*
 * Check each cell in the soduko game for validity
 */
 #define NO_GUESS_AVAILABLE 100
bool	guess(sodukoType *s)
{
	int	r;
	int	c;
	int mi = NO_GUESS_AVAILABLE;
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
				if (mm == 0) continue;
				if (mm < mi)
				{
					mi = mm;
					mr = r;
					mc = c;
				}
			}
	    }
	}
	if (mi == NO_GUESS_AVAILABLE) return false;
	printf("Empty cell count is %d at cell (%d,%d)\n", mi, mr, mc);
	for (int k = 1; k <= 9; k++) 
		printf("NV:%d - %d ", k, s->cell[mr][mc].notValues[k]);
	printf("\n");
	int index = 1;
	while (index <= 9  &&  s->cell[mr][mc].notValues[index]) index++;
	s->cell[mr][mc].value =  index;
	s->cell[mr][mc].state = cellActive;
	printf("%d:: Setting cell [%d,%d] to %d\n", __LINE__, mr, mc, s->cell[mr][mc].value);
	for (int i = 0; i < 9; i++)
	{
		s->cell[i][mc].notValues[index] = true;
		s->cell[mr][i].notValues[index] = true;
	}
	for (r = BLOCK(mr); r < BLOCK(mr) + 3; r++)
	{
		for (c = BLOCK(mc); c < BLOCK(mc) + 3; c++)
		{
			s->cell[r][c].notValues[index] = true;
		}
	}
	fflush(stdout);
	return true;
}

/*
 * Check each cell in the soduko game for validity
 */
 #define NO_GUESS_AVAILABLE 100
bool	getCellGuess(sodukoType &s, int &mr, int &mc, int &mi)
{
	int	r;
	int	c;
	mi = NO_GUESS_AVAILABLE;

	for (r = 0; r < 9; r++)
	{
	    for (c = 0; c < 9; c++)
	    {
		    if (s.cell[r][c].state == cellEmpty)
			{
				int mm = 0;
				for (int k = 1; k <= 9; k++) 
					if (!(s.cell[r][c].notValues[k])) mm++;
				if (mm == 0) continue;
				if (mm < mi)
				{
					mi = mm;
					mr = r;
					mc = c;
				}
			}
	    }
	}
	if (mi == NO_GUESS_AVAILABLE) return false;

	return true;
}

/*
 * Check each cell in the soduko game for validity
 */
 #define NO_GUESS_AVAILABLE 100
bool	setCellGuess(sodukoType &s, int mr, int mc, int value, bool final)
{
	int	r;
	int	c;

	s.cell[mr][mc].value = value;
	//if (final)
	//	s.cell[mr][mc].state = cellFound;
	//else
		s.cell[mr][mc].state = cellActive;
	for (int i = 0; i < 9; i++)
	{
		s.cell[i][mc].notValues[value] = true;
		s.cell[mr][i].notValues[value] = true;
	}
	for (r = BLOCK(mr); r < BLOCK(mr) + 3; r++)
	{
		for (c = BLOCK(mc); c < BLOCK(mc) + 3; c++)
		{
			s.cell[r][c].notValues[value] = true;
		}
	}
	fflush(stdout);
	return true;
}


bool solveRec(soduko s)
{
	sState ch = check(&s);
	int    mr, mc, mi;
	if (ch == sComplete) {
		printf("SOLVED!!!\n");
		sodukoDump(&s);
		return true;
	}
	else if (ch == sInvalid)
	{
		printf("BAD RESULT!!!\n");
		return false;
	}
	
	if (!getCellGuess(s, mr, mc, mi)) return false;
	for (int k = 1; k <= 9; k++)
	{
		if (s.cell[mr][mc].notValues[k]) continue;
		setCellGuess(s, mr, mc, k, (mi == 1));
		printf("%d:: Setting cell [%d,%d] to %d (%s)\n", __LINE__, mr, mc, s.cell[mr][mc].value, 
			STATE[s.cell[mr][mc].state]);;
		//sodukoDump(&s);
		if (solveRec(s)) return true;
	}
	printf("Returning FALSE on (%d,%d)\n", mr, mc);
	sodukoDump(&s);
	return false;
}

bool solve(soduko s)
{
	sState ch = check(&s);
	if (ch == sComplete) {
		printf("SOLVED!!!\n");
		sodukoDump(&s);
		return true;
	}
	else if (ch == sInvalid)
	{
		printf("BAD RESULT!!!\n");
		return false;
	}
	
	if (!guess(&s)) return false;
	
	sodukoDump(&s);
	return solve(s);
}

void resolve(sodukoType *s)
{
	int r, c;
	for (c = 0; c < 9; c++)
	{
		for (r = 0; r < 9; r++)
		{
		}
	}
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
	while (!feof(f)) {
		setNotValues(&s);
		sodukoDump(&s);//sodukoDumpInvalid(&s); 
		solveRec(s);
		getValues(f, s);
	}
	return 0;

}

