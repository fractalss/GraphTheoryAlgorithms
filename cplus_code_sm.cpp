/* Convert this program to C++
 *
 * * change to C++ io
 *
 * * change to one line comments
 *
 * * change defines of constants to const
 *
 * * change array to vector<>
 *
 * * inline any short function
 *
 * * Saurav Mitra (saurav.mitra@gmail.com)  */

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

const int N=40; 

inline void sum(int *p,  vector<int> d) // making use of inline function and vector as one of the arguments, dropping index of an array as an argument in the original code

{

*p = 0;

*p = std::accumulate(d.begin(), d.end(), 0); // sum of integers via accumulate keyword

}

int main()

{

int accum = 0;

vector<int> data;

for(int i = 0; i < N; ++i)

data.push_back(i); // Reading the elements of the vector

sum(&accum, data);

cout <<"sum is " << accum << endl; // C++ output

return 0;

}
