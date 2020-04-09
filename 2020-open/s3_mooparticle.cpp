/*
Question:
Quarantined for their protection during an outbreak of COWVID-19, Farmer John's cows have come up with a new way
to alleviate their boredom: studying advanced physics! In fact, the cows have even managed to discover a new subatomic 
particle, which they have named the "moo particle".

N moo particles, each described by a 'spin' (xi, yi) in [-10^9, 10^9]. If xi <= xj and yi <= yj its possible
either particle i or j will disappear. Return the minimum number of moo particles left after a sequence of interactions.

Solution:
Construct an undirected graph where the vertices are the moo particles and there is an edge between particles which
can interact. Note we can reduce any connected component down to one particle by removing particles
leaf-first. It remains to quickly (O(NlogN)) calculate the number of connected components.

To do this sort the moo particles increasing in x and then in y. Start by assuming each aprticle
is in its own connected component. Then while two components are adjacent in the order with the minimum y
in the left component <= the maxmimum y of the right component (then xleft <= xright and yleft <= yright
so there is an edge between the two components), combine the two components.

Summary:
Find the number of connected components. Sort by x (tiebreak by y) and merge adjacent components.
*/

#include <iostream>
#include <algorithm>
using namespace std;
#define MAXN 100000

int N;
// spin
int x[MAXN], y[MAXN];
// cid[i] = particle at location i
int cid[MAXN];
// minl[i] = min y left of i
int minl[MAXN];
// maxr[i] = max y right of i
int maxr[MAXN];

// comparator for sorting
// sorts by x first and breaks ties by sorting with y
bool cmp(int a, int b)
{
  if (x[a] == x[b]) return y[a] < y[b];
  return x[a] < x[b];
}

int main()
{
  // point i/o streams to the problem files
  freopen("moop.in", "r", stdin);
  freopen("moop.out", "w", stdout);
  // stream in spin data and initialize each particle as being its own component
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> x[i] >> y[i];
    cid[i] = i;
  }
  // sort particles by x then y
  sort(cid, cid+N, cmp);
  // populate minl
  minl[0] = y[cid[0]];
  for (int i = 1; i < N; i++)
    minl[i] = min(minl[i-1], y[cid[i]]);
  // populate maxr
  maxr[N-1] = y[cid[N-1]];
  for (int i = N-2; i >= 0; i--)
    maxr[i] = max(maxr[i+1], y[cid[i]]);
  // count the connected components
  int ans = 1;
  for (int i = 0; i < N-1; i++)
    // no connections between i and i+1 => add another connected component
    if (minl[i] > maxr[i+1])
      ans++;
  cout << ans << '\n';
}
