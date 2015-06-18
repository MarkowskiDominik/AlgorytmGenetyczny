#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <utility>

#include "Graph.h"

const double P_CROSS = 0.5;
const double P_MUTATION = 0.01;
const double TOURNAMENT_SIZE = 0.05;
const int LIMIT_GENERATION = 250;
const bool NO_LIMIT = true;

using namespace std;

class Population
{
	Graph graph;
	int geneCount;
	int colorNumber;
	int populationSize;
	int **generation;
	int **newGeneration;
	int *ratings;

	void ratePopulation();
	pair<int, int> selection();
	void crossAndMutation(pair<int, int> parents, int position);
	void saveToLog(int generation, int min, int max, double avg);

public:
	Population();
	Population(Graph &graph, int size, int color);
	~Population();

	void generatePopulation();
	void evolution(int *result);
};

