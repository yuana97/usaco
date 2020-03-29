/*
Note: This question is relevant to abstract algebra. You should know some basic facts:
permutations repeat after a certain time (they have finite order) and they can be decomposed into
cycles (cycle decomposition of permutations)
https://en.wikipedia.org/wiki/Permutation_group

Question: Swapity Swapity Swap
N cows in a line. Farmer John gives M pairs of integers (L1, R1),...,(LM, RM). For each pair
the cows in Li,..,Ri reverse their order. The cows do this K times. Return the new order of the
cows.

Solution:
Calculate the first M reversals. Denote the resulting permutation by p. We want to calculate
p^K. To do so apply p and record the results until p^x[i] = i. Then take the K mod x -th result.

Summary: Mod k by the order of p.
*/

// import and namespace stuff
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
// set a constant MAXN=10^5.
#define MAXN 100000

// numbers
int N, M, K;
// reversals
int l[100], r[100];
// the initial permutation
int p[MAXN];
// cc[i] = cycle i belongs to
int cc[MAXN];
int pos[MAXN];
// A[i] = ith cycle of p
vector<int> A[MAXN + 1];
// answer
int ans[MAXN];

int main()
{
  // open read/write streams to swap.in and swap.out
  freopen("swap.in", "r", stdin);
  freopen("swap.out", "w", stdout);
  // assign N=#cows, M=#pairs, K=#repetitions
  cin >> N >> M >> K;
  for (int i = 0; i < M; i++)
  {
    // stream in Li and Ri.
    cin >> l[i] >> r[i];
    // decrement by 1 to adjust for 0 indexing.
    l[i]--, r[i]--;
  }
  // calculate p
  for (int i = 0; i < N; i++)
  {
    // set the initial position of the cow
    p[i] = i;
    // apply each reversal to the position fo the cow
    for (int j = 0; j < M; j++)
      // if the cow is in reversal j
      if (p[i] >= l[j] && p[i] <= r[j])
        // move the cow to the opposite side of reversal j
        p[i] = r[j] + l[j] - p[i];
  }
  // C indexes the cycles of p
  int C = 1;
  // put each cow into its cycle
  for (int i = 0; i < N; i++)
    // if we haven't already found i in a cycle
    if (!cc[i])
    {
      // mark i as in the Cth cycle
      cc[i] = C;
      // put i in the Cth cycle
      A[C].push_back(i);
      // get cow j at position i in p
      int j = p[i];
      // j is the first element in its cycle
      if (j != i)
        pos[j] = 1;
      while (j != i)
      {
        // add new element to cycle
        A[C].push_back(j);
        // mark j as in a cycle
        cc[j] = C;
        // pos[i] = position of cow in its cycle
        if (p[j] != i)
          pos[p[j]] = 1 + pos[j];
        // move j to its new position
        j = p[j];
      }
      // create a new label for the next cycle
      C++;
    }
  // calculate ans with the following reasoning:
  // let cycle = A[cc[i]] = cycle of ith cow
  // cycle[(pos[i] + K) % cycle.size()] = where ith cow is after K applications of this cycle.
  for (int i = 0; i < N; i++)
    ans[A[cc[i]][(pos[i] + K) % A[cc[i]].size()]] = i;
  // print ans
  for (int i = 0; i < N; i++)
    cout << ans[i] + 1 << '\n';
}