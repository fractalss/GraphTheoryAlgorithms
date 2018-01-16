#include "Graph.h"
#include "DijkstrasPath.h"
#include <iostream>
#include <queue>
#include <climits>

//Implementation for Dijkstra's SSSP(Single source shortest path) algorithm
using namespace std;

DijkstrasPath::DijkstrasPath() {
}


DijkstrasPath::~DijkstrasPath() {
}


// Obtains an adjecency list from the graph, which is contained inside of an array.
// The shrtestDistance from the startNode to each of the other Nodes is recorded, but after initially being set to INF
// While there are still Nodes left to explore in the priorityQueue, the code itterates through the neighbours of
// Nodes taken from the queue, and compares the distance along that Edge to the previous recorded shortestDistance.
// When a shorter ditance is found, if the Node has yet to be explored, then it is added to the PriorityQueue to be explored in a later iteration.
// Finally, when there are no more explorable Nodes, the distance from the startNode to the targetNode is returned.
int DijkstrasPath::FindShortestPath(Graph& graph, int startNodeIndex, int targetNodeIndex)  {

	//Set initial distances to Infinity
	for (int i = 0; i < MAX_NODE_COUNT; i++)
		shortestDistance[i] = INF;

	// populate the adjecency list array
	graph.PopulateAdjecencyList(adjacencyList);

	// Custom Comparator for Determining priority for priority queue (shortest edge comes first)
	class prioritize { public: bool operator ()(pair<int, int>&p1, pair<int, int>&p2) { return p1.second > p2.second; } };
	priority_queue<pair<int, int>, vector<pair<int, int> >, prioritize> priorityQueue; // Priority queue to store vertex,weight pairs
	priorityQueue.push(make_pair(startNodeIndex, shortestDistance[startNodeIndex] = 0)); // Pushing the startNodeIndex with distance from itself as 0

	// While there are still explorable Nodes.
	while (!priorityQueue.empty()) {
		pair<int, int> currentNode = priorityQueue.top(); // Current Node taken from the openSet. The shortest distance for this has been found
		priorityQueue.pop(); // Remove the top element (which is now stored in currentNode)
		int currentNodeIndex = currentNode.first; // The Node index for the current Node
		int currentWeight = currentNode.second; // The final shortest distance for this Node

		if (closedSet[currentNodeIndex]) continue; // If the Node is already in the closedSet, skip it		
		else closedSet[currentNodeIndex] = true; // Add the Node to the closedSet

		// Iterate through all neighbours
		for (unsigned int i = 0; i < adjacencyList[currentNodeIndex].size(); i++) {

			// If the Node has already been visited, then skip it.
			if (closedSet[adjacencyList[currentNodeIndex][i].first]) continue;		

			// If this node is not present in the closedSet, and the current parent node distance+distance from there to this node is shorter than the initial distace set to this Node, then update it
			if(adjacencyList[currentNodeIndex][i].second + currentWeight < shortestDistance[adjacencyList[currentNodeIndex][i].first]) {
				
				// Set the new distance and add the Node to priority queue
				priorityQueue.push(
					make_pair(adjacencyList[currentNodeIndex][i].first, 
					(shortestDistance[adjacencyList[currentNodeIndex][i].first] = adjacencyList[currentNodeIndex][i].second + currentWeight))
				);
			}
		}
	}
	return shortestDistance[targetNodeIndex];
}
