#include <cstdio>
#include <iostream>

#include "Graph.h"
#include "Population.h"

int main()
{
	string path = "..//..//david_11.txt";	//nazwa grafu
	int colors = 11;	//ilosœæ kolorów
	int size = 100;		//rozmiar populacji
	int *result = new int[];

	Graph graf;
	cout << graf.zachlanny(path) << endl;

	graf.loadGraph(path);
	//graf.showGraph();

	clock_t start = clock();
	Population population(graf, colors, size);
	population.evolution(result);
	printf("Czas wykonywania: %lu ms\n", clock() - start);

	system("PAUSE");
	return 0;
}