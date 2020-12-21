// 15 Puzzle Experimentation
// 12/15/2020

#include <stdio.h>
#include <chrono>
#include <random>

using namespace std::chrono;

std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<std::mt19937::result_type> dist0(0, 0); // distribution in range [0, 0]
std::uniform_int_distribution<std::mt19937::result_type> dist1(1, 1); // distribution in range [1, 1]
std::uniform_int_distribution<std::mt19937::result_type> dist2(1, 2); // distribution in range [1, 2]
std::uniform_int_distribution<std::mt19937::result_type> dist3(1, 3); // distribution in range [1, 3]
std::uniform_int_distribution<std::mt19937::result_type> dist4(1, 4); // distribution in range [1, 4]
std::uniform_int_distribution<std::mt19937::result_type> dist[] = {
	dist0,
	dist1,
	dist2,
	dist3,
	dist4
};

// Generate a uniform integer on the interval [1, max] 1 <= max <= 4
int UniformInt(int max)
{
	return dist[max](rng);
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
uint8_t goal1A[] = {
	 1,  2,  3,  4,
	 5,  6,  7,  8,
	 9, 10, 11, 12,
	13, 14, 15,  0,
	15 };

uint8_t goal1B[] = {
	 1,  2,  3,  4,
	 5,  6,  7,  8,
	 9, 10, 11, 12,
	14, 13, 15,  0,
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

uint8_t* goalSituation = goal1A;  // test 1

// Display a game situation 
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
		move = rndMove15[blankPos][UniformInt(n)];
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

// Make n random moves in a puzzle
void RandomizePuzzle(uint8_t* situation, int n)
{
	uint8_t action[2];
	action[0] = 255;

	for (int i = 0; i < n; i++)
	{
		GenerateRandomAction(action, situation);
		ComputeNewSituation(situation, action);
	}
}

// AverageBranching
// Computes average branching for puzzle given that we will reject direct backtracks of last move
double AverageBranching(uint8_t* situation, int n)
{
	uint8_t action[2];
	action[0] = 255;

	uint8_t s[17];
	memcpy(s, situation, 17 * sizeof(uint8_t));
	uint64_t branchSum = 0;

	for (int i = 0; i < n; i++)
	{
		uint8_t blankPos = s[16];
		uint8_t nBranch = rndMove15[blankPos][0] - 1;
		branchSum += nBranch;
		//printf("%d ", nBranch);

		GenerateRandomAction(action, s);
		ComputeNewSituation(s, action);
	}
	//printf("\n");

	return (double)branchSum / (double)n;
}

// Spinner Implementation
// return number of moves in found solution or -1 if no solution found
uint8_t moveList[128];
int Spinner(uint8_t* situation, uint8_t maxMoves)
{
	uint8_t action[2];
	action[0] = 255;  // invalid initial action to be ignored for backtrack cancelation 

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
	int fastestSolution = 100;
	bool fSolution = false;

	for (int iteration = 1; iteration <= maxIterations; iteration++)
	{
		uint8_t tSituation[17];
		memcpy(tSituation, situation, 17 * sizeof(uint8_t));

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

unsigned __int64 nDfsEntries = 0;
int DFS(uint8_t* situation, uint8_t* lastAction, int maxDepth, int myDepth = 0)
{
	nDfsEntries++;

	if (GoalCheck(situation))
	{
		printf("myDepth=%d passed in solution  maxDepth=%d moves=", maxDepth, myDepth);
		for (int i = 0; i < myDepth; i++)
			printf("%d ", moveList[i]);
		printf("\n");
		return myDepth;
	}

	if (maxDepth < 1)
		return -1;

	uint8_t action[2];

	uint8_t blankPos = situation[16];
	uint8_t nMoves = rndMove15[blankPos][0];

	int bestDepth = -1;
	for (int moveID = 1; moveID <= nMoves; moveID++)
	{
		uint8_t move = rndMove15[blankPos][moveID];
		if (move == lastAction[0]) continue;

		action[0] = blankPos;
		action[1] = move;

		uint8_t tSituation[17];
		memcpy(tSituation, situation, 17 * sizeof(uint8_t));
		uint8_t tLastAction[2];
		memcpy(tLastAction, action, 2 * sizeof(uint8_t));

		moveList[myDepth] = situation[action[1]];
		ComputeNewSituation(tSituation, action);
		//printf("DFS: %d move: %d\n", myDepth, moveID);

		int foundDepth = DFS(tSituation, tLastAction, maxDepth - 1, myDepth + 1);
		if (foundDepth >= 0)
		{
			if (bestDepth == -1)
			{
				bestDepth = foundDepth;
				printf("FIRST BEST: ");
			}
			else if (foundDepth < bestDepth)
			{
				bestDepth = foundDepth;
				printf("NEW BEST: ");
			}
			printf("DFS%d returned solution foundDepth=%d\n", myDepth, foundDepth);
		}
	}
	return bestDepth;
}


// What we've learned
// Average solution branching is 2.168 
// Theoretical would by 3 - 1 (since we forbid direct undo of last move)
// Experimental > 2 since in actual play corners seem harder to get into!
// Complexity thus O(n^2) with DFS getting cumbersome by d=30

int main()
{
	uint8_t InitSituation[17];
	int fastestSolution = 100;

	for (int puzzle = 0; puzzle < 1; puzzle++)
	{
		int nRandomize = 20;
		memcpy(InitSituation, goal1A, 17 * sizeof(uint8_t));
		RandomizePuzzle(InitSituation, nRandomize);
		//memcpy(InitSituation, initialSituation, 17 * sizeof(uint8_t));
		printf("15puzzle_uint8: InitSituation (%d random moves)\n", nRandomize);
		ShowSituation(InitSituation);
		int branchAverage = 100000;
		printf("Average branching(%d)=%.3lf\n", branchAverage, AverageBranching(InitSituation, branchAverage));
		printf("goalSituation\n");
		ShowSituation(goalSituation);

		int maxReps = 1000000;
		for (int trial = 1; trial <= 1; trial++)
		{
			printf("Starting Scout trial %d  maxReps=%d...\n", trial, maxReps);
			auto start1 = high_resolution_clock::now();
			int fastestScoutSolution = SteppedCortex(InitSituation, maxReps);
			auto stop1 = high_resolution_clock::now();
			auto duration1 = duration_cast<milliseconds>(stop1 - start1);
			printf("puzzle=%d %llumS winningIteration=%d fastestSolution=%d moves=", puzzle, duration1.count(), winningIteration, fastestScoutSolution);
			for (int i = 0; i < fastestScoutSolution; i++) printf("%d ", bestMoveList[i]);
			printf("\n");

			uint8_t lastAction[2];
			lastAction[0] = 255;
			lastAction[1] = 0;
			nDfsEntries = 0;
			printf("Starting DFS trial %d...\n", trial);
			auto start2 = high_resolution_clock::now();
			int fastestDfsSolution = DFS(InitSituation, lastAction, nRandomize);
			auto stop2 = high_resolution_clock::now();
			auto duration2 = duration_cast<milliseconds>(stop2 - start2);
			if (fastestDfsSolution < 0) printf("NO SOLUTION ");
			printf("nDFSentries=%llu ", nDfsEntries);
			printf("puzzle=%d %llumS fastestDfsSolution=%d moves=", puzzle, duration2.count(), fastestDfsSolution);
			for (int i = 0; i < fastestDfsSolution; i++) printf("%d ", bestMoveList[i]);
			printf("\n");

			ShowSituation(InitSituation);
		}
	}

	return 0;
}