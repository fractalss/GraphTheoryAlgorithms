#include "Simulator.h"
#include "Graph.h"
#include "DijkstrasPath.h"
#include <iostream>

using namespace std;

// A "Monte Carlo Simulation" which generates a series of graphs and records the average path length from Node 0 to every other Node.
// An average path length is calculates from the results of all of the tests.
void Simulator::SimulateGraph() const {

	if (numberOfNodes > MAX_NODE_COUNT) {
		cout << "Simulation Failes - The requested Graph size it too large." << endl;
		cout << "Reduce the number of Nodes in the graph." << endl;
		return;
	}

	// Stores the averages of all path finding tests
	double average = 0;

	int failedSearches = 0;

	for (int i = 0; i < simLoops; i++) {
        system("clear");  //For Windows please change it to "cls"
		cout << " Simulating Loop #" << i << endl;

		Graph graphData(simName, numberOfNodes, graphDensity, rangeMin, rangeMax);
		graphData.PrintGraphData();

		// Loop for each of the nodes in the graph (excluding the starting node (0)), setting each one as the target node
		for (int n = 1; n < numberOfNodes; n++) {
			cout << "\rTargetNode = " << n;


			// add to the average the value of each of the shortest paths found if the average is less than INF and filter out any failed searches
			DijkstrasPath path;
			double tempAverage = path.FindShortestPath(graphData, 0, n);
			if (tempAverage < INF) average += tempAverage; 
			else failedSearches++;


			if (n == numberOfNodes - 1 && i == simLoops - 1 ) { // On the final loop
				// calculate the mean average from the average divided by the number of path tests
				average = (average /  static_cast<double>( ( (numberOfNodes * simLoops) - failedSearches) ) );
				graphData.SetAverageShortestPath(average);
                system("clear"); //For Windows please change it to "cls"
				graphData.PrintGraphData();
			}
		}
	}
}
