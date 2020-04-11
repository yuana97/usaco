/*

Question:
N cows each has a favorite color from 1 to N. There are M pairs of cows (a, b) such that b admires a.
x, y admire a => x, y have the same favorite color. Determine the lexicographically minimum assignment 
of favorite colors to cows such that the number of distinct favorite colors among all 
cows is maximized.

Solution:
Draw a graph where the vertices are cows and each cow has directed edges to its admirers.
Cows b, c admire a => they have the same color => treat b and c as the same cow. Change all occurrences
of c to b and merge the adjacency list of c into that of b. 

Once this process terminates each cow is admired by at most one cow, so we can color each cow differently.

Summary:
merge the color groups
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// given a filename, hook up io streams and do some performance optimizations
void setIO(string s) {
  // turn off multithreading and flushing for performance
  ios_base::sync_with_stdio(0); cin.tie(0);
  // set read/write streams
  freopen((s+".in").c_str(), "r", stdin);
  freopen((s+".out").c_str(), "w", stdout);
}

// upper bound for N, M
const int MX = 2e5+5;

int N, M;

// par[i] = parent[i] = color group i belongs to
int par[MX],cnt[MX];
// adj[i] = adjacencylist[il = list of neighbors (admirers) of i
// rpar[i] = reverseparent[i] = list of cows in the color group i
vector<int> adj[MX], rpar[MX];
// q contains groups we need to process with the procedure described in the solution
queue<int> q;

// merge two color groups a, b
void merge(int a, int b) {
  // get the color groups of a and b
  a = par[a], b = par[b];
  // always merge the smaller group into the larger group to maintain O(N) runtime of merges
  // otherwise it could go to O(N^2)
  if (rpar[a].size() < rpar[b].size()) swap(a, b);
  // give a the children of b
  for (int t : rpar[b]) { par[t] = a; rpar[a].push_back(t); }
  // merge the adjacency list of b into a
  adj[a].insert(end(adj[a]), begin(adj[b]), end(adj[b]));
  // clear the adjacency list of b
  adj[b].clear();
  // push group to the queue
  if (adj[a].size() > 1) q.push(a);
}

int main() {
  setIO("fcolor");
  cin >> N >> M;
  // populate adjacency list
  for (int i = 0; i < M; ++i) {
    int a,b; cin >> a >> b;
    adj[a].push_back(b);
  }
  // populate parent and reverseparent structures
  for (int i = 1; i <= N; ++i) {
    par[i] = i; rpar[i].push_back(i);
    if (adj[i].size() > 1) q.push(i);
  }
  // apply the procedure while we haven't reduced all cows to single-cow groups
  while(q.size()) {
    // group reduced down to a single cow => kick it out of the queue
    int x = q.front(); if (adj[x].size() <= 1) { q.pop(); continue; }
    // merge admirers if we have to
    int a = adj[x].back(); adj[x].pop_back();
    if (par[a] == par[adj[x].back()]) continue;
    merge(a, adj[x].back());
  }
  // coloring for the next group of cows, starting with the smallest color
  int co = 0;
  // print the colors
  for (int i = 1; i <= N; i++) {
    // if we encounter a new color group, give it a new color.
    if (!cnt[par[i]]) cnt[par[i]] = ++co;
    cout << cnt[par[i]] << "\n";
  }
}