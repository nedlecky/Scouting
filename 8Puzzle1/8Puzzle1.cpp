// Improved 8-Puzzle Calculator
// Ned Lecky 1/20/2016

#include <conio.h>
#include <random>
#include <ctime>

unsigned seed = 2;
//std::default_random_engine generator = std::default_random_engine(seed);
//std::ranlux24_base generator = std::ranlux24_base(seed);

//std::uniform_int_distribution<int> distribution[] = {
//	std::uniform_int_distribution<int>(1, 1),
//	std::uniform_int_distribution<int>(1, 1),
//	std::uniform_int_distribution<int>(1, 2),
//	std::uniform_int_distribution<int>(1, 3),
//	std::uniform_int_distribution<int>(1, 4),
//	std::uniform_int_distribution<int>(1, 5),
//	std::uniform_int_distribution<int>(1, 6),
//	std::uniform_int_distribution<int>(1, 7),
//	std::uniform_int_distribution<int>(1, 8),
//};

#define RANDOM(n) (rand()%n+1)
//#define RANDOM(n) (distribution[n](generator))
//#define RANDOM(n) (distribution[n](std::random_device()))

// 8 Puzzle
// with blank in pos n (0-8), first el is #possible moves,
// remainder are moves
uint8_t rndMove8[][5] = {
	{2,1,3,0,0},  // with blank in pos 0, there are 2 moves, 1 and 3
	{3,0,2,4,0},  // with blank in pos 1, there are 3 moves, 0, 2, and 4
	{2,1,5,0,0},  // etc.
	{3,0,4,6,0},
	{4,1,3,5,7},
	{3,2,4,8,0},
	{2,3,7,0,0},
	{3,4,6,8,0},
	{2,5,7,0,0} };

// action representation
// uint8_t action[2];
//	0= move blank from position...
//  1= to

// situation representation
// uint8_t situation[10];
//	position map 0 1 2
//				 3 4 5
//				 6 7 8
//  9 is redundant location of blank

// test puzzles
uint8_t pathPuzzle1[] = {
	1,6,8,5,4,0,3,2,7,
	5 };
uint8_t pathPuzzle2[] = {
	3,5,4,1,2,8,6,0,7,
	7 };
uint8_t pathPuzzle3[] = {
	2,5,7,3,4,1,8,0,6,
	7 };
uint8_t pathPuzzle4[] = { // This is the #1 worst-case 31-move puzzle requiring 31 moves
	8,6,7,2,5,4,3,0,1,
	7 };
uint8_t pathPuzzle5[] = { // This is the #2 worst-case 31-move puzzle requiring 31 moves
	6,4,7,8,5,0,3,2,1,
	5 };


uint8_t* pathPuzzles[] = {
	pathPuzzle1,
	pathPuzzle2,
	pathPuzzle3,
	pathPuzzle4,
	pathPuzzle5
};


// desired goal
uint8_t goalSituation[] = {
	// 1 2 3
	// 8 0 4
	// 7 6 5  with blank in pos 4
	1, 2, 3, 4, 5, 6, 7, 8, 0,
	8 };
	//1, 2, 3, 8, 0, 4, 7, 6, 5,
	//4 };

// display a game situation 
void ShowSituation(uint8_t* situation)
{
	printf("-----\n");
	for (int i = 0; i < 3; i++)
	{
		char buf[28];
		buf[3] = 0;
		for (int j = 0; j < 3; j++)
			buf[j] = '0' + situation[i * 3 + j];
		printf("|%s|\n", buf);
	}
	printf("----%1d\n\n", situation[9]);  // shows redundant blank pointer
}

// Is situation in the goal state?
int GoalCheck(uint8_t* situation)
{
	return 0 == memcmp(situation, goalSituation, 9 * sizeof(uint8_t));
}

// Given the current situation, pick a random action
void GenerateRandomAction(int* action, int* situation)
{
	// pick a random move using the possible move table
	uint8_t blankPos = situation[9];
	uint8_t n = rndMove8[blankPos][0];
	uint8_t move = rndMove8[blankPos][RANDOM(n)];

	// build action = from,to
	action[0] = blankPos;
	action[1] = move;
}

// Given the current situation, pick a random action
// AVOID GOING BACK TO UNDO PREVIOUS ACTION
void GenerateRandomAction2(uint8_t* action, uint8_t* situation)
{
	uint8_t blankPos = situation[9];
	uint8_t lastBlankPos = action[0];

	// keep picking random moves until we aren't backtracking
	uint8_t move = lastBlankPos;
	while (move == lastBlankPos)
	{
		uint8_t n = rndMove8[blankPos][0];
		move = rndMove8[blankPos][RANDOM(n)];
	}

	// build action = from,to
	action[0] = blankPos;
	action[1] = move;
}

// perform 'action' on 'situation'
void ComputeNewSituation(uint8_t* situation, uint8_t* action)
{
	uint8_t from = action[0];
	uint8_t to = action[1];

	situation[from] = situation[to];  // move the blank
	situation[to] = 0;
	situation[9] = to;				// update redundant position
}

// Spinner2 Implementation
// return depth of found solution or -1 if no solution found
const int maxSolnLen = 1023;
char soln[maxSolnLen + 1];
int Spinner(uint8_t* initialSituation, int maxIterations)
{
	uint8_t situation[10];
	memcpy(situation, initialSituation, 10 * sizeof(uint8_t));

	uint8_t action[2];
	action[0] = -1;  // invalid initial action to be ignored

	int iterations = 0;
	soln[0] = 0;

	int depth = 0;
	while (!GoalCheck(situation) && iterations < maxIterations)
	{
		GenerateRandomAction2(action, situation);
		ComputeNewSituation(situation, action);
		soln[depth++]=situation[action[0]] + '0';
		iterations++;
	}
	soln[depth] = 0;

	if (iterations < maxIterations)
		return iterations;
	else
		return -1;
}

int bestIter;
char bestSoln[maxSolnLen + 1];
int Cortex(uint8_t* situation, int maxIterations)
{
	int best = 40;

	for (int i = 0; i < maxIterations; i++)
	{
		int d = Spinner(situation, best - 1);
		if (d >= 0 && d < best)
		{
			printf("Found solution spinner %d, depth=%d\n", i, d);
			best = d;
			bestIter = i;
			strncpy_s(bestSoln, soln, maxSolnLen);
		}
	}
	if (best < 100) return best;
	else return -1;
}

void RandomizePuzzle(uint8_t* situation, int n)
{
	uint8_t action[2];
	action[0] = -1;

	for (int i = 0; i < n; i++)
	{
		GenerateRandomAction2(action, situation);
		ComputeNewSituation(situation, action);
	}
}

int main()
{
	/*
	for (int i = 0; i < 4; i++)
	{
		const int N = 8;
		int count[N + 1];
		memset(&count, 0, (N + 1) * sizeof(int));
		for (int i = 0; i < N * 10000; i++)
			count[RANDOM(N)]++;
		for (int i = 1; i <= N; i++)
			printf("Count[%d]=%d\n", i, count[i]);
	}
	*/

	clock_t start = std::clock();

	int nTotalFails = 0;
	for (int p = 3; p < 5; p++)
	{
		uint8_t situation[10];
		memcpy(situation, goalSituation, 10 * sizeof(uint8_t));
		int knownSolution = 31;
		//RandomizePuzzle(situation, knownSolution);
		memcpy(situation,pathPuzzles[p],10*sizeof(uint8_t));
		ShowSituation(situation);

		int nFails = 0;
		for (int i = 0; i < 2; i++)
		{
			int d = Cortex(situation, 1000000);
			printf("%d %d %d %s", p, d, bestIter, bestSoln);
			if (d > knownSolution)
			{
				nFails++;
				nTotalFails++;
				printf("  FAIL");
			}
			printf("\n");
		}
		printf("nFails=%d\n", nFails);
	}

	clock_t end = std::clock();
	printf("\nTotalFails=%d\nExecution Time = %.3f S\n", nTotalFails, (end - start) / 1000.0);

	printf("press any key....");
	char c=_getch();
	return 0;
}

