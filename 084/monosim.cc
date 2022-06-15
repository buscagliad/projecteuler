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
#include <cmath>

typedef
enum { GO,  A1, CC1,  A2, T1, R1,   B1, CH1,  B2, B3, 
	  JAIL, C1,  U1,  C2, C3, R2,   D1, CC2,  D2, D3, 
	   FP,  E1, CH2,  E2, E3, R3,   F1,  F2,  U2, F3,
	  G2J,  G1,  G2, CC3, G3, R4,  CH3,  H1,  T2, H2} squares;

#define NUMSQUARES 40
#define NUMROLLS    9

int maxDice = 4;

void setDice(int dice)
{
	maxDice = dice;
}

int	getRoll()
{
	int d1 = rand()%maxDice + 1;
	int d2 = rand()%maxDice + 1;
	return d1 + d2;
}

int mono[40];
double prob[40];

int getCommChest(int cur)
{
	int	cc = rand()%16;
	
	switch(cc)
	{
		case 0:
			return GO;
		case 1:
			return JAIL;
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
			return cur;
		default:
			printf("ERROR cc = %d %s::%d\n", cc, __FILE__, __LINE__);
	}
	return cur;
}

int getChance(int cur)
{
	int	cc = rand()%16;
	
	switch(cc)
	{
		case 0:
			return GO;
		case 1:
			return JAIL;
		case 2:
			return C1;
		case 3:
			return E3;
		case 4:
			return H2;
		case 5:
			return R1;
		case 6:
		case 7:
			if (cur == CH1) return R2;
			if (cur == CH2) return R3;
			if (cur == CH3) return R1;
			printf("ERROR %s::%d\n", __FILE__, __LINE__);
		case 8:
			if (cur == CH1) return U1;
			if (cur == CH2) return U2;
			if (cur == CH3) return U1;
			printf("ERROR %s::%d\n", __FILE__, __LINE__);
		case 9: // retreat 3 spaces
			if (cur == CH1) return T1;
			if (cur == CH2) return D3;
			if (cur == CH3) return getCommChest(CC3);
			printf("ERROR %s::%d\n", __FILE__, __LINE__);
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
			return cur;
		default:
			printf("ERROR %s::%d\n", __FILE__, __LINE__);
	}
	return cur;
}	
		
	
int total_moves = 0;
int current_place = 0;
void move()
{
	current_place += getRoll();
	current_place %= NUMSQUARES;
	total_moves++;
	switch(current_place)
	{
		case CC1:
		case CC2:
		case CC3:
			current_place = getCommChest(current_place);
			break;
		case CH1: 
		case CH2:
		case CH3:		
			current_place = getChance(current_place);
			break;
		case G2J:
			current_place = JAIL;
		default:
			break;
	}
	mono[current_place]++;
}

void compute_probs()
{
	for (int i = 0; i < NUMSQUARES; i++) 
	{
		prob[i] = (double) mono[i] / (double) total_moves;
	}
}

void score()
{
	int max1 = 0;
	int max2 = 0;
	int max3 = 0;
	for (int i = 1; i < NUMSQUARES; i++)
	{
		if (prob[i] > prob[max1]) max1 = i;
	}
	prob[max1] = 0;
	for (int i = 1; i < NUMSQUARES; i++)
	{
		if (prob[i] > prob[max2]) max2 = i;
	}	
	prob[max2] = 0;
	for (int i = 1; i < NUMSQUARES; i++)
	{
		if (prob[i] > prob[max3]) max3 = i;
	}
	printf("Dice Value: %d Modal value: %2.2d%2.2d%2.2d\n", maxDice, max1, max2, max3);
}
		
void zero()
{
	total_moves = 0;
	current_place = 0;
	for (int i = 0; i < NUMSQUARES; i++)
	{
		prob[i] = 0;
		mono[i] = 0;
	}
}

void run(int dice)
{
	setDice(dice);
	zero();
	for (int i = 0; i < 10000000; i++)
	    move();
	compute_probs();
	for (int i = 0; i < NUMSQUARES; i++) 
	{
		printf("Square: %2d   Lands: %6d     Prob: %6.3f%%\n",
			i, mono[i], prob[i]*100.0);
	}
	score();
}



int main()
{
	run(6);
	run(4);
}
