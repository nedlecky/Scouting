// 15 Puzzle Experimentation
// 12/12/2020

#include <stdio.h>
#include <string.h>
#include <chrono>

using namespace std::chrono;

int UniformInt(int max)
{
	int r = rand() % max;
	return r;
}

// 15 Puzzle
// with blank in pos n (0-15), first el is #possible moves,
// remainder are moves
int rndMove15[][5] = {
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
// int action[2];
//	0= move blank from position...
//  1= to

// Situation representation
// int situation[17];
//	position map  0  1  2  3
//				  4  5  6  7
//				  8  9 10 11
//				 12 13 14 15
//  16 is redundant location of blank

// Some test puzzles
int initialSituation1[] = {  // 20 rnds; vortex finds 18 soln
	9,3,0,10,
	13,11,12,
	2,14,1,6,
	4,15,8,7,5,
	2 };
int initialSituation2[] = {  // 30 rnds; vortex can't find
	9,12,1,3,
	11,10,7,2,
	13,4,0,5,
	14,15,8,6,
	10 };
int initialSituation3[] = {  // 1,000,001 rnds; vortex can't find
	12,5,11,15,
	1,2,9,10,
	7,8,3,13,
	4,14,0,6,
	14 };
int initialSituation4[] = {  // Actual puzzle in my apartment
	1,4,2,0,
	5,7,6,8,
	13,3,10,12,
	15,11,9,14,
	3 };

int* initialSituation = initialSituation1;

// desired goal
int goal1[] = {
	 1,  2,  3,  4,
	 5,  6,  7,  8,
	 9, 10, 11, 12,
	13, 14, 15,  0,
	15 };

int goal2[] = {
	12, 11, 10,  9,
	13,  1,  2,  3,
	14,  8,  0,  4,
	15,  7,  6,  5,
	10 };

int goal3[] = {
	 0,  1, 4,  2,
	 5,  7, 6,  8,
	13,  3,10, 12,
	15, 11, 9, 14,
	 0 };

int goal4[] = {
	 5,  1,  4,  2,
	13,  7,  6,  8,
	15,  3, 10, 12,
	 0, 11,  9, 14,
	12 };

int* goalSituation = goal1;

// display a game situation 
void ShowSituation(int* situation)
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
	printf("-------------%d\n", situation[16]);  // shows redundant blank pointer
}

// Is situation in the goal state?
bool GoalCheck(int* situation)
{
	return 0 == memcmp(situation, goalSituation, 16 * sizeof(int));
}

// Given the current situation, pick a random action
void GenerateRandomAction(int* action, int* situation)
{
	// pick a random move using the possible move table
	int blankPos = situation[16];
	int n = rndMove15[blankPos][0];
	int move = rndMove15[blankPos][UniformInt(n) + 1];

	// build action = from,to
	action[0] = blankPos;
	action[1] = move;
}

// Given the current situation, pick a random action
// AVOID GOING BACK TO UNDO PREVIOUS ACTION
void GenerateRandomAction2(int* action, int* situation)
{
	int blankPos = situation[16];
	int lastBlankPos = action[0];

	// keep picking random moves until we aren't backtracking
	int move = lastBlankPos;
	while (move == lastBlankPos)
	{
		int n = rndMove15[blankPos][0];
		move = rndMove15[blankPos][UniformInt(n) + 1];
	}

	// build action = from,to
	action[0] = blankPos;
	action[1] = move;
}

// perform 'action' on 'situation'
void ComputeNewSituation(int* situation, int* action)
{
	int from = action[0];
	int to = action[1];

	situation[from] = situation[to];  // move the blank
	situation[to] = 0;
	situation[16] = to;				// update redundant position
}

// Spinner2 Implementation
// return depth of found solution or -1 if no solution found
char soln[1024];
int Spinner2(int* situation, int maxIterations)
{
	int action[2];
	action[0] = -1;  // invalid initial action to be ignored

	int iterations = 0;
	soln[0] = 0;
	while (!GoalCheck(situation) && iterations < maxIterations)
	{
		GenerateRandomAction2(action, situation);
		ComputeNewSituation(situation, action);
		char tbuf[32];
		sprintf_s(tbuf, "%d ", situation[action[0]]);
		strcat_s(soln, tbuf);
		iterations++;
	}
	if (iterations >= maxIterations)
		return -1;  // failed
	else
		return iterations;
}

char bestSoln[1024];
int winningIteration = 0;
int SteppedCortex(int* situation, int maxIterations)
{
	int best = 100;
	int bestSituation[17];
	bool fSolution = false;

	for (int i = 0; i < maxIterations; i++)
	{
		int tSituation[17];
		memcpy(tSituation, situation, 17 * sizeof(int));

		//srand(i);

		int d = Spinner2(tSituation, best - 1);
		if (d >= 0)  // found a solution
		{
			fSolution = true;
			best = d;
			printf("found solution i=%d d=%d\n",i,best);
			memcpy(bestSituation, tSituation, 17 * sizeof(int));
			strcpy_s(bestSoln, soln);
			winningIteration = i;
			ShowSituation(bestSituation);
		}
	}

	if (!fSolution) return -1;

	return best;
}
void Randomize(int* situation, int n)
{
	int action[2];
	action[0] = -1;

	for (int i = 0; i < n; i++)
	{
		GenerateRandomAction2(action, situation);
		ComputeNewSituation(situation, action);
	}
}


int main()
{
	int InitSituation[17];
	int best = 100;

	unsigned int seed = 1;
	srand(seed);

	for (int p = 0; p < 1; p++)
	{
		memcpy(InitSituation, goalSituation, 17 * sizeof(int));
		Randomize(InitSituation, 35);
		//memcpy(InitSituation, initialSituation, 17 * sizeof(int));
		printf("15puzzle1_int: InitSituation\n");
		ShowSituation(InitSituation);

		int maxReps = 1000000;
		for (int trial = 0; trial < 1; trial++)
		{
			printf("Starting trial %d  maxReps=%d...\n", trial, maxReps);
			auto start = high_resolution_clock::now();
			int d = SteppedCortex(InitSituation, maxReps);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<milliseconds>(stop - start);

			if (d < 0) printf("NO SOLUTION ");
			printf("%llumS p=%d i=%d d=%d %s\n", duration.count(), p, winningIteration, d, bestSoln);
		}
	}

	return 0;
}