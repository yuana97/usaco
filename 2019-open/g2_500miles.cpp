/*

I Would Walk 500 Miles

Question:
FJ divides his N cows into K nonempty groups such that no two cows from different groups
can interact with each other without walking some number of miles. Cows x and y
are willing to walk (2019201913x+2019201949y) mod 2019201997 miles to see each other.

Let M be the minimum number of miles any two cows in two groups are willing to walk to see each
other. Return the largest possible M among all possible divisions of the cows into K groups.

Solution:
Form a graph where the vertices are the cows, each cow has an edge to every other cow, and the edge weight
equals the number of miles the cows are willing to travel to see each other.

Now consider the MST (Minimum spanning tree, a tree which contains all the vertices and has the minimum total
edge weight). To see why this helps, consider the case K=2. In order to split the cows into two groups maximizing M,
we just remove the highest weight edge, then M=weight of that edge. This generalizes to an arbitrary K: for any K
we compute the MST and and remove the K-1 heaviest edges (and M becomes the K-1-th heaviest edge in the MST).

To compute an MST there are several standard algorithms, we will use Prim's algorithm for the MST.

Summary:
K-1th heaviest edge in an MST

*/

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
#define MAX_N 7500

// visited[i] = 1 if i is in the MST, 0 otherwise
int N, K, visited[MAX_N+1];
// D[i] = min weight connecting i to MST
long long D[MAX_N+1];

/*
Prim's algorithm to find the MST of a connected graph. 

How it works:
Start with a tree T containing just the vertex 1. Consider the set S of vertices
not in T. At each step, take the minimum weight edge connecting S and T, and add
the S-vertex to T.

Summary:
At each step add the minimum weight edge connecting T to its complement (complement means the set of
things not in T).

*/
void prim(int source)
{
  // initialize the min weight as the max
  for (int i = 1; i <= N; i++) D[i] = 2019201997;
  // visit 1 vertex per iteration
  for (int iter = 0; iter<N; iter++) {
    // get the unvisited vertex which has the min weight to the mST
    int min_i = 0;
    for (int i = 1; i <= N; i++)
      if (!visited[i] && (min_i==0 || D[i] < D[min_i])) min_i = i;
    // add it to the MST
    visited[min_i] = 1;
    // update D[j] for every unvisited j
    for (int j =1; j <= N; j++)
      if (!visited[j])
        D[j] = min(D[j], (2019201913LL*min(min_i,j)+2019201949LL*max(min_i,j)) % 2019201997LL);
  }
}

int main(void)
{
  // initialize input file stream fin from walk.in
  ifstream fin ("walk.in");
  fin >> N >> K;
  // initialize output file stream fout to walk.out
  ofstream fout ("walk.out");
  // make the mst
  prim(1);
  // sort D (the array of edge weights)
  sort (D+1,D+N+1);
  // print M (K-1th biggest edge weight)
  fout << D[N+1-K] << "\n";
  // exit main
  return 0;
}