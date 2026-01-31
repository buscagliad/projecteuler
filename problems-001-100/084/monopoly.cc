#ifdef PROBLEM_DESCRIPTION

    Community Chest (2/16 cards):
        Advance to GO
        Go to JAIL
    Chance (10/16 cards):
        Advance to GO
        Go to JAIL
        Go to C1
        Go to E3
        Go to H2
        Go to R1
        Go to next R (railway company)
        Go to next R
        Go to next U (utility company)
        Go back 3 squares.

#endif


#include <cstdio>

typedef
enum { GO,  A1, CC1,  A2, T1, R1,   B1, CH1,  B2, B3, 
	  JAIL, C1,  U1,  C2, C3, R2,   D1, CC2,  D2, D3, 
	   FP,  E1, CH2,  E2, E3, R3,   F1,  F2,  U2, F3,
	  G2J,  G1,  G2, CC3, G3, R4,  CH3,  H1,  T2, H2} squares;

#define NUMSQUARES 40
#define NUMROLLS    9

			//   ROLL   0    1     2      3       4        5      6       7      8
			//   Num    0    0     1      2       3        4      3       2      1
double roll[9]      = {0.0, 0.0, 0.0625, 0.125,  0.1875,  0.25,  0.1875, 0.125, 0.0625};
			//	[0] is chance (CH1, CH2 or CH3)
//		GO,  A1, CC1,  A2, T1, R1,   B1, CH1,  B2, B3, 
//	  JAIL, C1,  U1,  C2, C3, R2,   D1, CC2,  D2, D3, 
//	   FP,  E1, CH2,  E2, E3, R3,   F1,  F2,  U2, F3,
//	  G2J,  G1,  G2, CC3, G3, R4,  CH3,  H1,  T2, H2
	  
	//           	   GO,   A1,  CC1,   A2, T1,  R1,   B1, CH1,  B2, B3, 
double cc1[40]   = {    1,   0,    6,    0,   0,   3,   0,    0,   0,  0,
	//         	     JAIL,  C1,   U1,   C2,  C3,  R2,  D1,  CC2,  D2, D3, 
                        1,   1,    1,    0,   0,   0,   0,    0,   0,  0,
	// 	               FP,  E1,  CH2,   E2,  E3,  R3,  F1,   F2,  U2, F3,
                        0,   0,    0,    0,   1,   0,   0,    0,   0,  0,
	// 	              G2J,  G1,   G2,  CC3,  G3,  R4, CH3,   H1,  T2, H2
                        0,   0,    0,    0,   0,   0,   0,    0,   0,  2};
                        
	//           	   GO,   A1,  CC1,   A2, T1,  R1,   B1, CH1,  B2, B3, 
double cc2[40]   = {    1,   0,    0,    0,   0,   1,   0,    0,   0,  0,
	//         	     JAIL,  C1,   U1,   C2,  C3,  R2,  D1,  CC2,  D2, D3, 
                        1,   1,    1,    0,   1,   0,   0,    6,   0,  0,
	// 	               FP,  E1,  CH2,   E2,  E3,  R3,  F1,   F2,  U2, F3,
                        0,   0,    0,    0,   1,   2,   0,    0,   0,  0,
	// 	              G2J,  G1,   G2,  CC3,  G3,  R4, CH3,   H1,  T2, H2
                        0,   0,    0,    0,   0,   0,   0,    0,   0,  1};
                        
	//           	   GO,   A1,  CC1,   A2, T1,  R1,   B1, CH1,  B2, B3, 
double cc3[40]   = {    1,   0,    0,    0,   0,   1,   0,    0,   0,  0,
	//         	     JAIL,  C1,   U1,   C2,  C3,  R2,  D1,  CC2,  D2, D3, 
                        1,   1,    1,    0,   0,   0,   0,    0,   0,  0,
	// 	               FP,  E1,  CH2,   E2,  E3,  R3,  F1,   F2,  U2, F3,
                        0,   0,    0,    0,   1,   0,   0,    0,   0,  0,
	// 	              G2J,  G1,   G2,  CC3,  G3,  R4, CH3,   H1,  T2, H2
                        1,   0,    0,    6,   0,   2,   0,    0,   0,  1};

	//           	   GO,   A1,  CC1,   A2, T1,  R1,   B1, CH1,  B2, B3, 
double ch1[40]   = {    1,   0,    0,    0,   0,   0,   0,   14,   0,  0,
	//         	     JAIL,  C1,   U1,   C2,  C3,  R2,  D1,  CC2,  D2, D3, 
                        1,   0,    0,    0,   0,   0,   0,    0,   0,  0,
	// 	               FP,  E1,  CH2,   E2,  E3,  R3,  F1,   F2,  U2, F3,
                        0,   0,    0,    0,   0,   0,   0,    0,   0,  0,
	// 	              G2J,  G1,   G2,  CC3,  G3,  R4, CH3,   H1,  T2, H2
                        0,   0,    0,    0,   0,   0,   0,    0,   0,  0};
                        
	//           	   GO,   A1,  CC1,   A2, T1,  R1,   B1, CH1,  B2, B3, 
double ch2[40]   = {    1,   0,    0,    0,   0,   0,   0,    0,   0,  0,
	//         	     JAIL,  C1,   U1,   C2,  C3,  R2,  D1,  CC2,  D2, D3, 
                        1,   0,    0,    0,   0,   0,   0,    0,   0,  0,
	// 	               FP,  E1,  CH2,   E2,  E3,  R3,  F1,   F2,  U2, F3,
                        0,   0,   14,    0,   0,   0,   0,    0,   0,  0,
	// 	              G2J,  G1,   G2,  CC3,  G3,  R4, CH3,   H1,  T2, H2
                        0,   0,    0,    0,   0,   0,   0,    0,   0,  0};
                        
	//           	   GO,   A1,  CC1,   A2, T1,  R1,   B1, CH1,  B2, B3, 
double ch3[40]   = {    1,   0,    0,    0,   0,   0,   0,    0,   0,  0,
	//         	     JAIL,  C1,   U1,   C2,  C3,  R2,  D1,  CC2,  D2, D3, 
                        1,   0,    0,    0,   0,   0,   0,    0,   0,  0,
	// 	               FP,  E1,  CH2,   E2,  E3,  R3,  F1,   F2,  U2, F3,
                        0,   0,    0,    0,   0,   0,   0,    0,   0,  0,
	// 	              G2J,  G1,   G2,  CC3,  G3,  R4, CH3,   H1,  T2, H2
                        0,   0,    0,    0,   0,   0,  14,    0,   0,  0};
double mono[40][40];
double prod[40][40];

void normal(double *m, const char *t, int ix)
{
	double sum = 0;
	for (int i = 0; i < NUMSQUARES; i++) sum += m[i];
	if (sum != 16.0) printf ("ERROR - %s\n", t);
	for (int i = 0; i < NUMSQUARES; i++) m[i] /= sum; // normalizes to unit probability
	// now account for the rolls, m[ix] is the chance/community chest square,
	// that number will be multiplied by the 'roll' vector
	// and added
	double factor = m[ix];
	printf("Factor: %.3f\n", factor);
	m[ix] = 0.0;
	for (int i = 0; i < NUMSQUARES; i++) {
		mono[ix][i] += factor * m[i]; // normalizes to unit probability
	}
}

void mult()
{
	for (int i = 0; i < NUMSQUARES; i++) 
	{
		for (int j = 0; j < NUMSQUARES; j++) 
		{
			prod[i][j] = 0;
			for (int k = 0; k < NUMSQUARES; k++) 
			{
				prod[i][j] += mono[i][k] * mono[k][j];
			}
		}
	}
}

void makemono()
{
	for (int row = 0; row < NUMSQUARES; row++)
	{
		for (int i = 0; i < NUMROLLS; i++)
		{
			int  col = row + i;
			col %= NUMSQUARES;
			mono[row][col] = roll[i];
		}
	}
	normal(cc1, "cc1", CC1);
	normal(cc2, "cc2", CC2);
	normal(cc3, "cc3", CC3);
	normal(ch1, "ch1", CH1);
	normal(ch2, "ch2", CH2);
	normal(ch3, "ch3", CH3);
}

void printmat(double mat[40][40])
{
	double row;
	for (int i = 0; i < NUMSQUARES; i++)
	{
		printf("\n");
		row = 0;
		for (int j = 0; j < NUMSQUARES; j++)
		{
			row += mat[i][j];
			printf(" %.3f", mat[i][j]);
		}
		if (row != 1) printf("\n ERROR row %d = %.3f\n", i, row);
	}
}
void printvec(double mat[40][40])
{
	double sum;
	for (int col = 0; col < NUMSQUARES; col++)
	{
		printf("\n");
		sum = 0;
		for (int row = 0; row < NUMSQUARES; row++)
		{
			sum += mat[row][col];
		}
		printf("col: %d  %.3f", col, sum);
	}
}

int main()
{
	makemono();
	//printmat(mono);
	//for (int i = 0; i < 1000; i++) mult();
	//mult();
	//mult();
	//mult();
	//mult();
	printf("\n\n");
	printmat(mono);
	
	printvec(mono);

}
