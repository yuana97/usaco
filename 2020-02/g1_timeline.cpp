/*
Question: Timeline
Bessie attended N milking sessions over the past M days. For each session i she knows
it occurred at or after day Si. Bessie also has C memories (a, b, x) that b happened 
at least x days after a.

For each milking session, compute the earliest possible date it occurred.

Solution:
For each (a, b, x) draw a directed edge from a to b with weight x. Then apply topological sort
(create a list v1, v2, ... , vN of verticies such that vj comes after vi means there
is a path from vj to vi). Topological sort: Let indegree(v)=#edges going into v.
add 0 indegree verticies to list. Remove their edges. Add resulting 0 indegree vertices to list. 
Remove their edges...repeat until all vertices are used up.

Let v1, v2, ..., vN be the resulting list of vertices. For each va, for each neighbor vb with weight x
set S[b] = max(S[b], S[a] + x).

Summary: Topological sort. Update neighbors of each vertex.
*/

// import standard libraries
#include "bits/stdc++.h"

using namespace std;

// set IO streams
void setIO(string s)
{
  // turn off syncing with stdio: speeds up cin and cout
  ios_base::sync_with_stdio(0);
  // turn off console flushing: speeds up cin
  cin.tie(0);
  // open up read, write streams to given files
  freopen((s + ".in").c_str(), "r", stdin);
  freopen((s + ".out").c_str(), "w", stdout);
}

// use f and s as aliases for first and second
#define f first
#define s second

// max value of x = 1*10^5 + 5
const int MX = 1e5 + 5;

// N=#milking sessions, M=#days, C=#memories, S[i] = earliest time session i occurred
// indegree of a vertex = number of edges going into it
// in[i] = indegree of i
int N, M, C, S[MX], in[MX];
// vis[i] = whether or not vertex i was visited
// used for testing topological sort is working
bool vis[MX];
// adj[a] = vector of edges coming out of a
vector<pair<int, int>> adj[MX];
// queue for topological sort
queue<int> q;

int main()
{
  // open up read/write streams to timeline.in and timeline.out
  setIO("timeline");
  // assign N=#milking sessions, M=#days, C=#memories
  cin >> N >> M >> C;
  // stream in S[i] = lower bound for when milking session i occurred
  for (int i = 1; i <= N; ++i)
    cin >> S[i];
  // construct the graph and indegree function
  for (int i = 0; i < C; ++i)
  {
    // get (a, b, x)
    int a, b, x;
    cin >> a >> b >> x;
    // form an edge from a to b with weight x
    adj[a].push_back({b, x});
    // increase the indegree of b
    in[b]++;
  }
  // push root vertexes (0 indegree) into queue
  for (int i = 1; i <= N; ++i)
    if (!in[i])
      q.push(i);
  // topological sort while there are still vertices to process.
  while (q.size())
  {
    // remove first vertex from queue
    int x = q.front();
    q.pop();
    // mark x as visited
    vis[x] = 1;
    // test that S{x} is valid (to make sure S[x] is calculated correctly)
    assert(S[x] <= M);
    // foreach neighbor of x
    for (auto &t : adj[x])
    {
      // for the edge (x, t.f, t.s) apply the memory:
      // set S[t.f] = max(S[t.f], S[x] + t.s)
      S[t.f] = max(S[t.f], S[x] + t.s);
      // decrement the indegree of t.f. If it is zero, push it to the queue
      if (!(--in[t.f]))
        q.push(t.f);
    }
  }
  // For each vertex, assert that it's visited for testing purposes
  // print the result.
  for (int i = 1; i <= N; ++i)
  {
    assert(vis[i]);
    cout << S[i] << "\n";
  }
}