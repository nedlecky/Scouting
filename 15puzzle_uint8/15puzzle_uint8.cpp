// 15 Puzzle Experimentation
// 12/12/2020

#include <stdio.h>
#include <string.h>
#include <chrono>

using namespace std::chrono;

int VRand(int max)
{
	int r = rand() % max;
	return r;
}

// 15 Puzzle
// with blank in pos n (0-15), first el is #possible moves,
// remainder are moves
uint8_t rndMove15[][5] = {
	{2,1,4,0,0},
	{3,0,2,5,0},
	{3,1,3,6,0},
	{2,2,7,0,0},
	{3,0,5,8,0},
	{4,1,4,6,9},
	{4,2,5,7,10},
	{3,3,6,11,0},
	{3,4,9,12,0},
	{4,5,8,10,13},
	{4,6,9,11,14},
	{3,7,10,15,0},
	{2,8,13,0,0},
	{3,9,12,14,0},
	{3,10,13,15,0},
	{2,11,14,0,0} };

// action representation
// uint8_t action[2];
//	0= move blank from position...
//  1= to

// Situation representation
// uint8_t situation[17];
//	position map  0  1  2  3
//				  4  5  6  7
//				  8  9 10 11
//				 12 13 14 15
//  16 is redundant location of blank

// Some test puzzles
uint8_t initialSituation1[] = {  // 20 rnds; vortex finds 18 soln
	9,3,0,10,
	13,11,12,
	2,14,1,6,
	4,15,8,7,5,
	2 };
uint8_t initialSituation2[] = {  // 30 rnds; vortex can't find
	9,12,1,3,
	11,10,7,2,
	13,4,0,5,
	14,15,8,6,
	10 };
uint8_t initialSituation3[] = {  // 1,000,001 rnds; vortex can't find
	12,5,11,15,
	1,2,9,10,
	7,8,3,13,
	4,14,0,6,
	14 };
uint8_t initialSituation4[] = {  // Actual puzzle in my apartment
	 1,  4,  2,  0,
	 5,  7,  6,  8,
	13,  3, 10, 12,
	15, 11,  9, 14,
	 3 };

uint8_t* initialSituation = initialSituation4;  // test 1

// desired goal
uint8_t goal1[] = {
	 1,  2,  3,  4,
	 5,  6,  7,  8,
	 9, 10, 11, 12,
	13, 14, 15,  0,
	15 };

uint8_t goal2[] = {
	12, 11, 10,  9,
	13,  1,  2,  3,
	14,  8,  0,  4,
	15,  7,  6,  5,
	10 };

uint8_t goal3[] = {
	 0,  1, 4,  2,
	 5,  7, 6,  8,
	13,  3,10, 12,
	15, 11, 9, 14,
	 0 };

uint8_t goal4[] = {
	 5,  1,  4,  2,
	13,  7,  6,  8,
	15,  3, 10, 12,
	 0, 11,  9, 14,
	12 };

uint8_t* goalSituation = initialSituation4;  // test 1

// display a game situation 
void ShowSituation(uint8_t* situation)
{
	printf("--------------\n");
	for (int i = 0; i < 4; i++)
	{
		char buf[28];
		buf[0] = 0;
		for (int j = 0; j < 4; j++)
		{
			char tbuf[4];
			sprintf_s(tbuf, "%2d ", situation[i * 4 + j]);
			strcat_s(buf, tbuf);
		}
		printf("|%s|\n", buf);
	}
	printf("------------%2d\n", situation[16]);  // shows redundant blank pointer
}

// Is situation in the goal state?
bool GoalCheck(uint8_t* situation)
{
	return 0 == memcmp(situation, goalSituation, 16 * sizeof(uint8_t));
}

// Given the current situation, pick a random action
// AVOID GOING BACK TO UNDO PREVIOUS ACTION
void GenerateRandomAction(uint8_t* action, uint8_t* situation)
{
	uint8_t blankPos = situation[16];
	uint8_t lastBlankPos = action[0];

	// keep picking random moves until we aren't backtracking
	uint8_t move = lastBlankPos;
	while (move == lastBlankPos)
	{
		uint8_t n = rndMove15[blankPos][0];
		move = rndMove15[blankPos][VRand(n) + 1];
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
	situation[16] = to;				// update redundant position
}

// Spinner Implementation
// return number of moves in found solution or -1 if no solution found
uint8_t moveList[128];
int Spinner(uint8_t* situation, uint8_t maxMoves)
{
	uint8_t action[2];
	action[0] = 100;  // invalid initial action to be ignored for backtrack cancelation 

	int nMoves = 0;

	while (!GoalCheck(situation) && nMoves < maxMoves)
	{
		GenerateRandomAction(action, situation);
		ComputeNewSituation(situation, action);
		moveList[nMoves] = situation[action[0]];
		nMoves++;
	}
	if (nMoves >= maxMoves)
		return -1;  // failed
	else
		return nMoves;
}

char bestMoveList[128];
int winningIteration = 0;
int SteppedCortex(uint8_t* situation, int maxIterations)
{
	int fastestSolution = 200;
	bool fSolution = false;

	for (int iteration  = 0; iteration < maxIterations; iteration++)
	{
		uint8_t tSituation[17];
		memcpy(tSituation, situation, 17 * sizeof(uint8_t));

		//srand(i);

		int nMoves = Spinner(tSituation, fastestSolution - 1);
		if (nMoves >= 0)  // found a solution
		{
			fSolution = true;
			fastestSolution = nMoves;
			printf("found solution iteration=%d nMoves=%d\n", iteration, nMoves);
			memcpy(bestMoveList, moveList, nMoves * sizeof(uint8_t));
			winningIteration = iteration;
		}
	}

	if (!fSolution) return -1;

	return fastestSolution;
}

void Randomize(uint8_t* situation, int n)
{
	uint8_t action[2];
	action[0] = 100;

	for (int i = 0; i < n; i++)
	{
		GenerateRandomAction(action, situation);
		ComputeNewSituation(situation, action);
	}
}

int main()
{
	uint8_t InitSituation[17];
	int fastestSolution = 100;

	unsigned int seed = 1;
	srand(seed);

	for (int puzzle = 0; puzzle < 1; puzzle++)
	{
		memcpy(InitSituation, goalSituation, 17 * sizeof(uint8_t));
		Randomize(InitSituation, 25);
		//memcpy(InitSituation, initialSituation, 17 * sizeof(uint8_t));
		printf("15puzzle_uint8: InitSituation\n");
		ShowSituation(InitSituation);

		int maxReps = 10000000;
		for (int trial = 0; trial < 1; trial++)
		{
			printf("Starting trial %d  maxReps=%d...\n", trial, maxReps);
			auto start = high_resolution_clock::now();
			int fastestSolution = SteppedCortex(InitSituation, maxReps);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<milliseconds>(stop - start);

			if (fastestSolution < 0) printf("NO SOLUTION ");
			printf("puzzle=%d %dmS winningIteration=%d fastestSolution=%d moves=", puzzle, duration, winningIteration, fastestSolution);
			for (int i = 0; i < fastestSolution; i++) printf("%d ",bestMoveList[i]);
			printf("\n");
		}
	}

	return 0;
}