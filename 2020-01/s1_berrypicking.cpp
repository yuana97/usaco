/*
Question:
N trees 1,...,N. Tree i contains exactly Bi berries. Bessie has K baskets.
Each basket can hold as many berries as Bessie wants, but only one type
of berry. Bessie has to give Elsie the K/2 baskets with the largest amt of berries.
Return the maximum number of berries Bessie can collect for herself. 

Solution:
  Setup:
  Let b be the minimum number of berries in a bucket Elsie receives. Without loss of
  generality assume all Elsie's buckets contain exactly b berries (it doesn't help Bessie
  to give Elsie more than b berries per bucket). Now our goal is the maximize the number of berries
  placed into K buckets of size at most b such that K/2 buckets have exactly b berries inside.

  Consider a single tree's contribution to the buckets. Theres no point having multiple
  buckets with less than b berries from this tree (it only decreases the number of berries
  Bessie gets), so all buckets from this tree have exactly b berries except possibly one.

  Algorithm:
  Thus its optimal to repeatedly fill buckets with b berries unti we run out of buckets or all trees
  have less than b berries remaining. If we still have buckets, we sort the trees by berries remaining
  (Bi mod b) and add berries from the most remaining to the least.

  We repeat the above process for b = 0,...,max(Bi) and pick the max result.

Runtime:
O(max(Bi)*NlogN), because for a fixed b it takes O(N) time to fill the buckets of size b, plus
O(NlogN) time to sort the trees (standard knowledge, google sorting algorithm complexity), plus
O(N) time to add the remaining berries to the buckets. This is O(NlogN) because NlogN is the dominating 
term (look up big-O notation). 

We do this max(Bi) times for a total complexity of O(max(Bi)*NlogN).

Summary: 
Elsie gets K/2 buckets of size b each. Fill buckets with b berries until you can't.
Then fill buckets with the leftover. Do this for b = 1,...,max(Bi).
*/

// include file io library
#include <iostream>
// include standard algorithms
#include <algorithm>
// use standard namespace
using namespace std;

// reserve memory for ints called N, K.
// N=num trees, K=num buckets.
int N, K;
// reserve memory for an int[100000] called A.
// A[i]=num berries on tree i
int A[100000];
// reserve memory for the int mod (b=1,...,max(Bi))
int mod;

// comparison function for sorting the trees: sort by residue mod b.
// we will use this later as an argument to sort.
bool cmp(int a, int b)
{
  // true => a comes before b
  // so this function tells the sorting function to decreasing order of
  // residue mod mod.
  return (a % mod) > (b % mod);
}

// program entry point
int main()
{
  // use cin to read from berries.in
  freopen("berries.in", "r", stdin);
  // use cout to write to berries.out
  freopen("berries.out", "w", stdout);
  // stream in N=num trees and K=num buckets from berries.in
  cin >> N >> K;
  // initialize max(Bi) = 0
  int M = 0;
  // for each tree
  for (int i = 0; i < N; i++)
  {
    // fill A[i]=num berries of tree i
    cin >> A[i];
    // update max = max num berries on a tree
    M = max(M, A[i]);
  }
  // initialize best = max number of berries for bessie
  int best = 0;
  // for each possible value of b
  for (int b = 1; b <= M; b++)
  {
    // initialize full = num buckets of size b
    int full = 0;
    // for each tree
    for (int i = 0; i < N; i++)
      // extract all the full buckets from the tree
      full += A[i] / b;
    // elsie has uneven number of berries => shes getting extra berries
    // => this solution is not optimal, b is too large => were done searching
    // => break loop
    if (full < K / 2)
      break;
    // if all buckets are filled with b berries
    if (full >= K)
    {
      // we can't add any more berries, update max now
      // K/2 full buckets, b berries each => b*K/2 berries
      // note we calculate (K/2) first to avoid overflow from b*K.
      best = max(best, b * (K / 2));
      // skip adding remaining berries.
      continue;
    }
    // we will add remaining berries, set mod=b.
    mod = b;
    // sort A by most berries remaining to least (see cmp function above)
    // Note: in this function, A refers to iterator (google cpp iterator) pointing
    // to start of array A in memory. A+N is iterator pointing to Nth position
    // after A (in this case the end of A).
    sort(A, A + N, cmp);
    // get current number of berries for bessie: we have 'full' num
    // of filled buckets, subtract out K/2 buckets for Elsie, multiply
    // by b berries per bucket.
    int cur = b * (full - K / 2);
    // for each tree, while we still have to process and empty buckets
    // i = tree, i+full=current bucket
    for (int i = 0; i < N && i + full < K; i++)
      // add remaining berries from the tree
      cur += A[i] % b;
    // update best with current max berries.
    best = max(best, cur);
  }
  // write best answer + newline to berries.out.
  cout << best << '\n';
}