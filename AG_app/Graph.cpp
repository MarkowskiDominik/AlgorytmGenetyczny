#include "Graph.h"

Graph::Graph()
{
}

Graph::~Graph()
{
}

void Graph::loadGraph(string filename)
{
	ifstream fileStream;
	fileStream.open(filename, fstream::in);

	if (fileStream.is_open())
	{
		string next;
		int vertex1, vertex2;

		while (!fileStream.eof())
		{
			fileStream >> next;
			if (next == "edge"){
				fileStream >> vertexCount;
				edges = new vector<vector<int>>(vertexCount);
			}
			if (next == "e"){
				fileStream >> vertex1;
				fileStream >> vertex2;

				if (vertex1 != vertex2)
					edges->at(vertex1 - 1).push_back(vertex2 - 1);
			}
		}
		fileStream.close();
	}
	else cout << "error open file";
}

void Graph::showGraph()
{
	for (unsigned int i = 0; i < edges->size(); i++)
	{
		cout << i << ":\t";
		for (unsigned int j = 0; j < edges[i].size(); j++)
		{
			cout << edges->at(i)[j] << " ";
		}
		cout << endl;
	}
}

int Graph::getVertexCount()
{
	return vertexCount;
}

int Graph::rateSpecimen(int *specimen)
{
	int errorNumber = 0;
	for (int i = 0; i < vertexCount; i++)
	{
		int color = specimen[i];

		for (int tmp : edges->at(i))
		{
			if (specimen[tmp] == color)
				errorNumber++;
		}
	}
	return errorNumber;
}

int Graph::zachlanny(string filename)
{
	ifstream fileStream;
	fileStream.open(filename, fstream::in);

	if (fileStream.is_open())
	{
		string next;
		int vertex1, vertex2;

		while (!fileStream.eof())
		{
			fileStream >> next;
			if (next == "edge"){
				fileStream >> vertexCount;
				edges = new vector<vector<int>>(vertexCount);
			}
			if (next == "e"){
				fileStream >> vertex1;
				fileStream >> vertex2;

				if (vertex1 != vertex2)
				{
					edges->at(vertex1 - 1).push_back(vertex2 - 1);
					edges->at(vertex2 - 1).push_back(vertex1 - 1);
				}
			}
		}
		fileStream.close();
	}
	else cout << "error open file";

	vector<int> colors;
	colors.assign(vertexCount, -1);

	int i = 0;
	while (i < vertexCount)
	{
		vector<int> neighbours = edges->at(i);

		vector<int> colorUsed;
		for (int tmp : neighbours)
		{
			if (colors[tmp] != -1)
				colorUsed.push_back(colors[tmp]);
		}
		sort(colorUsed.begin(), colorUsed.end());

		int j = 0;
		while (colors.at(i) == -1)
		{
			if (find(colorUsed.begin(), colorUsed.end(), j) == colorUsed.end())
				colors.at(i) = j;
			j++;
		}
		i++;
	}

	sort(colors.begin(), colors.end());
	auto it = unique(colors.begin(), colors.end());
	colors.resize(distance(colors.begin(), it));
	return colors.size();
}