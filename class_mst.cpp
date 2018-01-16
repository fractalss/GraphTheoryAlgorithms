//Minimum Spanning Tree for a weighted undirected graph
//There are some extra code since it was told to add necessary code to the class in the same code for HW2

#include<cstdlib>    //random numbers, srand(), rand()
#include<climits>    // For Maximum integer value, INT_MAX
#include<ctime>      // time function to use as seed, time(0)
#include <iostream>  //c++ style output, cout
#include <vector>    //vector
#include <queue>     //priority_queue
#include<algorithm>  //To use sort(...) function
#include<iterator>   //To use iterator
#include<fstream>    //To take input from file

#define ID pair<int,double> //macro where first int for vertex, and second double for distance:For HW2
#define mp make_pair        // macro for make_pair
#define ff first            //macro to reduce coding time
#define ss second           // macro to reduce coding time

using namespace std;

/*
A class named Graph has been created.
This contains necessary member variables and procedures to solve the intended problems
*/

class Graph
{
private:
    int nodes; //Total number of vertex in the Graph

    priority_queue<ID,vector<ID>,greater<ID> >PQ; //PQ will store vertex and its distance from source in sorted order(ascending): HW2
    vector<double>s_dist; //For storing shortest distances from source: HW2
    vector<vector<ID> >edges; //For storing edges: HW2

public:

    //Code Section For Minimum Spanning Tree

    //vector Edges for storing graph edges
    //vector mstEdges for storing Minimum Spanning Tree edges
    //In this pair<int, pair<int, int> >, first int is for weight, second int for starting vertex and last one for destination vertex
    vector< pair<int, pair<int, int> > > Edges,mstEdges;
    vector<int>par,rank; // they both are for disjoint set union purpose: par for storing parent and rank for storing rank of vertex

    //A constructor to read a graph from inputted file
    Graph(vector<int> data) //input file has read in data
    {
        reset(); // Preparing it for reuse
        //cnt for counting values of input file to categorize them as an edge
        //u for starting vertex, v for destination vertex, w for wight
        int cnt=0,u,v,w;
        //From input file, categorizing edges and adding then to vector edges
        //first value,data[0], is the total number of vertices
        for(int i=0;i<(int)data.size();i++)
        {
            if(i==0)
            {
              //To set the Total number of vertex
              //To resize vector par and rank to fit all vertices
              nodes=data[i];
              par.resize(nodes+1);
              rank.resize(nodes+1);
            }
            else
            {
                cnt++;
                if(cnt==1) u=data[i]; //if cnt is 1 then this value is a index of staring vertex for an edge
                else if(cnt==2) v=data[i]; //if cnt is 2 then this value is a index of destination vertex for an edge
                else if(cnt==3) //if cnt is 3 then this value is a weight for an edge
                {
                    w=data[i];
                    addEdgeForMST(u,v,w); // adding  edge to the vector edges
                    cnt=0; //cnt is zero for staring next edge
                }
            }
        }
    }
    //This procedure will add an edge to vector Edges
    //u is source, v is destination, and w is weight
    void addEdgeForMST(int u, int v, int w)
    {
        Edges.push_back(make_pair(w, make_pair(u,v))); //kept w beginning for sorting purpose
    }
    //This will return the number of edges in the graph for HW4
    int getNoOfEdges()
    {
        return (int)Edges.size();
    }
    //This will return the number of edges in Minimum Spanning Tree
    int getNoOfMSTEdges()
    {
        return (int)mstEdges.size();
    }

    //To clear several member variables: reusing purpose
    void reset()
    {
        nodes=0;
        Edges.clear();
        mstEdges.clear();
        par.clear();
        rank.clear();
    }
    //for disjoint set union
    void make_set(int p)
    {
        par[p]=p;
    }
    //for disjoint set union
    int find_parent(int r)
    {
        if(r!=par[r]) par[r]=find_parent(par[r]);
        return par[r];
    }
    // Kruskal Algorithm has been implemented for finding the Minimum Spanning Tree(MST) for a weighted undirected graph
    // This procedure will return cost of MST and edges of MST will be stored in vector mstEdges.
    int kruskal_MST()
    {
        int cost=0; // Total cost of Minimum Spanning Tree
        sort(Edges.begin(),Edges.end()); // sort the edges in ascending order according to the weight of edges
        //for disjoint set union(used in Kruskal algortim for MST) making each vertex its initial parent
        for(int i=0;i<nodes;i++)
        make_set(i);

        //Implementation of Kruskal's MST algorithm
        //Pseudocode: https://en.wikipedia.org/wiki/Kruskal's_algorithm
        for(int i=0;i<(int)Edges.size();i++) //For all edges in the graph
        {
          int a=find_parent(Edges[i].second.first);  //For current edge, find the representative  of starting vertex
          int b=find_parent(Edges[i].second.second); //For current edge, find the representative  of destination vertex
          if(a!=b) //If they share different representative  then take the edge
          {
              mstEdges.push_back(Edges[i]); //add the edge to the vector mstEdges and in Minimum Spanning Tree
              cost+=Edges[i].first; //Add the weight of current edge to the cost of MST
              if(rank[a]>rank[b]) //for making disjoint set union faster
              par[b]=a;
              else
              {
               par[a]=b;
               if(rank[a]==rank[b]) rank[b]++;
              }
          }
        }
     return cost; // return the cost of Minimum Spanning Tree
    }


    //Code Section for Homework 2
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
    //Taking input from a text file "data.txt" located in the same folder with this source code
    ifstream data_file("data.txt");
    if (data_file.is_open()) {;} //Check if the file exists.
    else
    {
        cout<<"File not found!"<< endl;
        getchar();
        exit(0);
    }
    istream_iterator<int>start(data_file),end;
    vector<int>data(start,end); //vector data contains the contents of inputted file
    //costOfMST is the cost of Minimum Spanning Tree
    int costOfMST;
    Graph G=Graph(data); //Declaring a Graph object

    //Calling of kruskal_MST() procedure for generating Minimum Spanning Tree of the inputted weighted undirected graph
    costOfMST=G.kruskal_MST();

    //Printing the cost of Minimum Spanning tree
    cout<<"The cost of the Minimum Spanning Tree is: "<<costOfMST<<endl;
    //Printing the Tree(the edges) as said in the problem specification
    cout<<"The edges that form the Minimum Spanning Tree are: "<<endl;
    for(int i=0;i<(int)G.mstEdges.size();i++)
    {
        cout<<G.mstEdges[i].second.first<<"  "<<G.mstEdges[i].second.second<<"  "<<G.mstEdges[i].first<<endl;
    }
    G.reset();
    return 0;
}

