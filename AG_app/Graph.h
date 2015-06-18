#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

class Graph
{
	int vertexCount;
	vector<vector<int>>* edges;

public:
	Graph();
	~Graph();

	void loadGraph(string filename);
	void showGraph();
	int getVertexCount();
	int rateSpecimen(int *specimen);

	int zachlanny(string filename);
};

