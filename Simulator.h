#include <string>

class Graph;

class Simulator {
public:
	Simulator(std::string simName = "", int numberOfNodes = 50, double graphDensity = 0.2, int rangeMin = 1, int rangeMax = 5, int simLoops = 50) :
		simName(simName),
		numberOfNodes(numberOfNodes),
		graphDensity(graphDensity),
		rangeMin(rangeMin),
		rangeMax(rangeMax),
		simLoops(simLoops) { }

~Simulator() {};

// simulates graph generation and path finding n number of times before returning an average path length
void SimulateGraph() const;

	private:
		std::string simName;
		int numberOfNodes;
		double graphDensity;
		int rangeMin, rangeMax;
		int simLoops;
};

