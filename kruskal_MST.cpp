/* Implementing MST using Kruskal's algorithm
 Saurav Mitra (saurav.mitra@gmail.com */

#include<vector>
#include<iostream>
#include<fstream>
#include<iterator>
#include<algorithm>
using namespace std;

vector<int> fathers;                    // Creating Disjoint Data Sets
    int find (int x){                   // Function FIND to create highest ancestor
        if (fathers.at(x) == x){
            return x;
			}	
    return find(fathers.at(x));         // If condition is not satisfied then call function recursively
    }

	void unite (int x, int y){          // Function to UNITE two trees, nodes x and y are from different trees
	int fx = find(x);                   // Find FATHER of node x
	int fy = find(y);                   // Find FATHER of node y
	fathers.at(fx) = fy;                // Connect two trees
    }

int main(){
    
    int i,j,cost;
	ifstream inFile("sample_data_coursera.dat");    // Open the file containing data as supplied in the website
	istream_iterator<int> start(inFile), end;       // Use iterator to read the whole file till end
	vector<int> sample_data (start,end);            // Store all the integers in the data in the vector
	
    int num_nodes=sample_data.front();              // 1st element in the supplied data is number of nodes
    fathers.resize(num_nodes);                      // Size of the fathers will be equal to number of nodes
    for(int n=0;n<num_nodes;n++){                   // Initialize the fathers vector
        fathers.at(n) = n;
    }
    sample_data.erase(sample_data.begin());         //Concentrate on the rest of data of triples (i,j,cost)
	int num_edges=sample_data.size()/3;             // Dvision by 3 since the data is in column format
	vector < pair < int , pair < int , int > > > edges; //First is cost and then a pair of i,j nodes
		for (int m=0;m<num_edges;m++)
            {
			i=sample_data.at(m*3);                  // Scan rest of the data and fill the vector edges
            j=sample_data.at(m*3+1);                // in cost, i, j format so that sorting is easier
			cost=sample_data.at(m*3+2);
			edges.push_back(make_pair(cost,make_pair(i,j)));	
			}
    
	int mst_weight = 0, mst_edges = 0, mst_nodes = 0;   // Kruskal Algorithm begins, declaring variables
    sort(edges.begin(),edges.end());                    // STEP 1: Sort the list of edges
    
    // STEPS 2-3 : Setting the upper bounds of loop, MST is complete when there (number of nodes -1) edges and the edges vector has a size of number of edges
	while ( (mst_edges < (num_nodes-1) ) || (mst_nodes < num_edges) ){
	i= edges[mst_nodes].second.first;
	j= edges[mst_nodes].second.second;
	cost=edges[mst_nodes].first;
    // Check if edge is okay to beincluded in MST
    // If i and j are in different trees (if they are on the same they will create a cycle)
	if ( find(i) != find(j)) {                          // Function for FIND at the very begining
	unite(i,j);                                         // UNITE two trees the edge connects
	mst_weight += cost;                                 // Add the weight of the edge
	cout <<  i << "\t<--->\t" << j << "\tCOST\t" << cost << endl;
	mst_edges ++ ;                                      // Increase the edge count
	}
	mst_nodes++;
 	}
 cout << "\nWeight of the MST is " << mst_weight << endl << endl;
	return 0;
}
