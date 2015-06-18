#include "Population.h"

Population::Population()
{
}

Population::Population(Graph &graph, int color, int size)
{
	this->graph = graph;
	geneCount = graph.getVertexCount();
	colorNumber = color;
	populationSize = size;

	srand(unsigned int(time(NULL)));
	generation = new int*[populationSize];
	generatePopulation();
	ratings = new int[populationSize];
	ratePopulation();
}

Population::~Population()
{
	if (generation != nullptr) delete generation;
}

void Population::generatePopulation()
{
	for (int i = 0; i < populationSize; i++)
	{
		int *colors = new int[geneCount];

		for (int j = 0; j < geneCount; j++)
			colors[j] = (rand() % colorNumber);
		generation[i] = colors;
	}
}

void Population::evolution(int *result)
{
	int numberGeneration = 0;
	bool next = true;
	while (next && (numberGeneration < LIMIT_GENERATION || NO_LIMIT))
	{
		newGeneration = new int*[populationSize];
		for (int i = 0; i < populationSize / 2; i++)
			crossAndMutation(selection(), i);

		delete[] generation;
		generation = newGeneration;
		numberGeneration++;

		ratePopulation();
		int min = ratings[0], max = ratings[0], sum = 0;
		for (int i = 0; i < populationSize; i++)
		{
			if (ratings[i] == 0 && result != nullptr)
			{
				result = generation[i];
				next = false;
			}
			if (ratings[i] < min) min = ratings[i];
			if (ratings[i] > max) max = ratings[i];
			sum += ratings[i];
		}
		saveToLog(numberGeneration, min, max, (double)sum / populationSize);
	}
}

void Population::ratePopulation()
{
	for (int i = 0; i < populationSize; i++)
	{
		ratings[i] = graph.rateSpecimen(generation[i]);
	}
}

pair<int, int> Population::selection()
{
	int first = rand() % populationSize;
	for (int i = 1; i < populationSize*TOURNAMENT_SIZE; i++)
	{
		int tmp = rand() % populationSize;
		if (ratings[tmp] < ratings[first]) first = tmp;
	}

	int second = rand() % populationSize;
	for (int i = 1; i < populationSize*TOURNAMENT_SIZE; i++)
	{
		int tmp = rand() % populationSize;
		if (tmp != first && ratings[tmp] < ratings[second]) second = tmp;
	}

	return make_pair(first, second);
}

void Population::crossAndMutation(pair<int, int> parents, int position)
{
	int *child_1 = new int[populationSize];
	int *child_2 = new int[populationSize];
	
	if (((double)rand() / RAND_MAX) < P_CROSS)
	{
		int splitPoint = rand() % geneCount;
		for (int i = 0; i < splitPoint; i++)
		{
			child_1[i] = generation[parents.first][i];
			child_2[i] = generation[parents.second][i];
		}
		for (int i = splitPoint; i < geneCount; i++)
		{
			child_1[i] = generation[parents.second][i];
			child_2[i] = generation[parents.first][i];
		}
	}
	else
	{
		for (int i = 0; i < geneCount; i++)
		{
			child_1[i] = generation[parents.first][i];
			child_2[i] = generation[parents.second][i];
		}
	}
	
	for (int i = 0; i < geneCount; i++)
	{
		if ((double)rand() / RAND_MAX < P_MUTATION)	child_1[i] = rand() % colorNumber;
		if ((double)rand() / RAND_MAX < P_MUTATION)	child_2[i] = rand() % colorNumber;
	}

	newGeneration[position * 2] = child_1;
	newGeneration[position * 2 + 1] = child_2;
}

void Population::saveToLog(int generation, int min, int max, double avg)
{
	ofstream fileStream;
	fileStream.open("..//..//log.txt", fstream::app);

	if (fileStream.is_open())
	{
		fileStream << generation << "\t" << min << "\t" << max << "\t" << avg << endl;
		fileStream.close();
	}
	else cout << "error open file";
}