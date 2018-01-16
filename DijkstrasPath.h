#include <vector>
#include <climits>

const int MAX_NODE_COUNT = 1001; //Maximum possible number of Nodes. Preallocating space for DataStructures accordingly
const int INF = INT_MAX; //Infinity

class Graph; 

class DijkstrasPath {
public:
	DijkstrasPath();
	~DijkstrasPath();

	int FindShortestPath( Graph& graph, int startNodeIndex, int targetNodeIndex);

	// Declared here in ordert to preallocate space to contain the maximum number of nodes
	std::vector< std::pair<int, int> > adjacencyList[MAX_NODE_COUNT]; //Adjacency list
	int shortestDistance[MAX_NODE_COUNT]; //Stores shortest distance
	bool closedSet[MAX_NODE_COUNT] = { 0 }; //Determines whether the node has been visited or not
};
