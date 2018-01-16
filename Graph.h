#include <vector>
#include <algorithm> 
#include <iterator>
#include <string>

using namespace std;

struct Node;

struct Edge {
public:
	Edge(Node* startNode, Node* endNode, int edgeWeight) :startNode(startNode), endNode(endNode), edgeWeight(edgeWeight) {}

	inline struct Node* GetEndNode() { return endNode; }
	
	inline int GetEndNodeIndex();

	inline int GetEdgeWeight() { return edgeWeight; }

	// Overload the == operator for comparing Edge structs for equality
	// Notice, we don't compare the weight. This is because no two edges should point between the same two Nodes, so the weight neeed not be considered.
	inline friend bool operator==(const Edge& edge1, const Edge& edge2) {
		return (edge1.endNode == edge2.endNode &&
			edge1.startNode == edge2.startNode);
	};

private:

	// the Nodes at which this edge starts and ends respectively (i.e the direction of the edge)
	Node *startNode; // TODO: consider is this necessary? As the Edge is stored inside of the Node it is pointing to.
	Node *endNode;

	//the cost to travel between nodes along this edge
	int edgeWeight;

};


// Node elements make up the graph. They contain Edge information, as well
struct Node {
public:

	Node(int index) :index(index) {}

	// Returns the number of Edges leading from this Node
	inline int GetNumberOfEdges() { return adjecentEdges.size(); }

	// Returns the index value of this node
	inline const int GetIndex() const { return index; }

	// If one deoes not exists, then adds an Edge pointing from the fromNode to the toNode, with a given weight value.
	// will return true if an edge did not already exist, and so was added. False if an edge already existed.
	bool AddEdge(Node* toNode, const int edgeWeight);

	// If an Edge exists between the fromNode and toNode, then remove it.
	// True will be returned if an Edge was found and deleted, otherwise false will be returned.
	bool DeleteEdge(Node* toNode);

	// Compares this node and the toNode to see if an edge exists between them. If so, then returns true.
	// An integer can be provided to the edgeIndex pointer in order to obtain the index of a found element, if such an element is found
	inline bool CheckForEdge(Node* toNode, int *edgeIndex = 0);

	// Returns a vector of pairs containing the index ID of the neighbour on the graph and the weight of the edge in that order
	// This ID can then be used to access the neighbouring Node and its values.
	vector< pair<int, int> > GetAllNeighboursIndicesAndWeight();

private:
	// The index value asociated with this node
	const int index;

	// stores all Edges associated with this Node
	vector<Edge> adjecentEdges;
};

class Graph {
public:
	Graph(string graphName = "", int numberOfNodes = 50, double edgeDensity = 0.1f, int rangeMin = 1, int rangeMax = 8);
	~Graph();

	// Returns the number of nodes in the graph
	inline int GetSize()  const { return nodes.size(); }

	// For retrieving individual, specific nodes
	inline Node* GetNodeByIndex(const int index) const { return nodes[index]; }

	// Populates the Adjecency list passed as a parameter.
	// This array contains the neighbours for each node, along with the weight of the edge between the two nodes.
	// A list is used as it complements the way Edges are stored within Nodes, allowing itteration through edges via their owning Node
	void PopulateAdjecencyList(std::vector < std::pair<int, int> > * adjacencyList);

	// Records the average path length for this graph.
	void SetAverageShortestPath(double newAverage) { averageShortestPath = newAverage; }



	// Prints a line to separate sections of the output stream. Also has the option to display a title message below.
	void PrintDivideLineAndTitle(string stringToPrint = "");

	// Prints the adjecency matrix for this Graph, showing the existence of edges between nodes 
	// Primarily used for debugging purposes
	void PrintAdjecencyMatrix();

	// Prints information about this graph
	void PrintGraphData();



private:

	// The name displayed for this graph
	string graphName;

	// The calculated average shortest path for this graph. Only used to record the value, and does not affect functionality.
	double averageShortestPath;

	//Performs the density equation D = (E) / (V(V -1))
	float CalculateGraphDensity() {
		float density = (/*2.f * */static_cast<float>(GetNumberOfEdges()) / 2.f)
			/ (static_cast<float>(nodes.size()) * (static_cast<float>(nodes.size()) - 1.f)
				);
		return density;
	}

	int GetNumberOfEdges() {
		int numberOfEdges = 0;
		for (vector<Node*>::iterator it1 = nodes.begin(); it1 != nodes.end(); ++it1) {
			int noToAdd = 0;
			noToAdd = (*it1)->GetNumberOfEdges();

			numberOfEdges += noToAdd;
		}
		return numberOfEdges;
	}

	// All of the nodes belonging to this graph
	vector<Node*> nodes;

};
