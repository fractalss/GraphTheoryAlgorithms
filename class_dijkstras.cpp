//Monte carlo simulation for calculating average shortest paths in graphs

#include<cstdlib>    //random numbers, srand(), rand()
#include<climits>    // For Maximum integer value, INT_MAX
#include<ctime>      // time function to use as seed, time(0)
#include <iostream>  //c++ style output, cout
#include <vector>    //vector
#include <queue>     //priority_queue

#define ID pair<int,double> //macro where first int for vertex, and second double for distance
#define mp make_pair        // macro for make_pair
#define ff first            //macro to reduce coding time
#define ss second           // macro to reduce coding time

using namespace std;

/*
A class named Graph has been created.
This contains necessary member variables and procedures to solve the intended problem
*/

class Graph
{
private:
    int nodes; //Number of vertices
    priority_queue<ID,vector<ID>,greater<ID> >PQ; //PQ will store vertex and its distance from source in sorted order(ascending)
    vector<double>s_dist; //For storing shortest distances from source
    vector<vector<ID> >edges; //For storing edges

public:

    Graph() {}; //Constructor
    Graph(int vertices) //Constructor with parameters
    {
        nodes=vertices; //store number of vertices
        edges.resize(nodes+1); //Resize to fit since vertex number starts from 1.
    }
    // To add an edge in a Graph.
    //First one source, then destination, and then distance.
    void addEdge(int x, int y, double w)
    {
        edges[x].push_back(ID(y,w));
        edges[y].push_back(ID(x,w));
    }

    //For generating probability about having an edge between two vertices
    double probability()
    {
        return static_cast<double>(rand())/RAND_MAX;
    }

    //Generating Graph. Density is given. lo is the lowest value of distance and hi is the highest value.
    void monte_carlo_simulation(double density, double lo, double hi)
    {
        double dist,prob;
        for(int i=1;i<=50;i++)
        {
            for(int j=i+1;j<=50;j++) // No looping
            {
                prob=probability();
                if(prob<=density) //If this is true then an  edge between two vertices is possible
                {
                    dist=lo+(hi-lo)*probability(); //Generating distance
                    addEdge(i,j,dist); //Adding into Graph
                }
            }
        }
    }

    void dijkstra(int source)
    {

        s_dist.resize(nodes+1); //Resizing s_dist vector to fit for all vertices
        for(int i=0;i<nodes;i++) s_dist[i]=static_cast<double>(INT_MAX); // Initializing to large value

        s_dist[source]=0.0; // Distance from source to source is zero.
        ID u,v; //two pair<int,double> variable for storing vertices and distances
        u=mp(source,0.0); //Putting source and its distance to u
        PQ.push(u); //inserting  source information to priority_queue

        //iterating until the queue is empty
        while(!PQ.empty())
        {
            u=PQ.top(); //getting the top element
            PQ.pop(); //deleting the top element
            //u.ff is the present vertex number
            //u.ss is the distance from source to this vertex
            //Iterating for all adjacent vertices of present vertex
            for(unsigned int i=0;i<edges[u.ff].size();i++)
            {
                v=edges[u.ff][i]; //Adjacent vertex of u.ff
                //v.ff is the vertex number
                //v.ss is the distance from u.ff to this vertex
                v.ss+=u.ss; //total distance to this vertex form source

                //If current total distance is less then shortest path distance
                //then current total distance is the new shortest path distance
                if(s_dist[v.ff]>v.ss)
                {
                    s_dist[v.ff]=v.ss;
                    PQ.push(v); //insert to PQ for further processing
                }
            }
           }
        return;
     }

     double averageDistance()
     {
        double total_dist=0.0; //Total shortest path distance of all path from source is initially zero
        int connected_vertices=nodes-1; //Total number of paths will be total_number_of_vertex-1
        for(int i=2;i<=nodes;i++)
        {
                //If not reachable from source then omit and reduce number of connected_vertices by 1.
                //else add distance to the total_dist
                if(s_dist[i]==static_cast<double>(INT_MAX)) connected_vertices--;
                else total_dist+=s_dist[i];
        }
        //To find average shortest path distance divide total_dist by the number of connected_vertices
        double avg_distance=total_dist/static_cast<double>(connected_vertices);
        return avg_distance;
    }

};
int main()
{
    srand(time(0)); //seed
    //Declaring, Allocating, and Initializing two Graphs of 50 nodes
    //G20 with density 20% and G40 with density 40%
    Graph G20=Graph(50),G40=Graph(50);

    //For storing average shortest path for two Graphs
    double avg_shortest_path_20, avg_shortest_path_40;

    //Graphs with 20% density
    G20.monte_carlo_simulation(0.20,1.0,10.0); //Generating Graph
    G20.dijkstra(1); //Finding Shortest Path from vertex number 1
    avg_shortest_path_20=G20.averageDistance(); // Finding average shortest path


    G40.monte_carlo_simulation(0.40,1.0,10.0); //Generating Graph
    G40.dijkstra(1); //Finding Shortest Path from vertex number 1
    avg_shortest_path_40=G40.averageDistance();// Finding average shortest path

    cout<<"Average Shortest Path for a Graph with 20% Density is: "<<avg_shortest_path_20<<endl;
    cout<<"Average Shortest Path for a Graph with 40% Density is: "<<avg_shortest_path_40<<endl;
    return 0;
}
