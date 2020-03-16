/*
Question: 1,...,N cities, N <= 1000 connected by M oneway roads (directed graph).
City i earns Bessie mi moonies, mi <= 1000. Bessie starts and ends her trip at city 1.
The trip costs CT^2 moonies where C is a constant and T is the number of cities.
Return the maximum amount of moonies Bessie can make in a trip.

Solution: Let t = num cities Bessie visits. Note her max money is bounded above by
1000t - t^2 which is negative when t > 1000, therefore we can assume t <= 1000.
Let dp[x][t] = max money Bessie can make at time t if she is located at city x.
Notice dp[x][t] = max({dp[xi][t-1] + mx}), where xi ranges over the neighbors of x
and mx is the money at city x. That is, to get the max money at x at the current time,
we should choose a path to x thru its neighbor with the most money at the previous time.
Starting with dp[1][0] = 0, we use this recurrence to calculate our desired value dp[t][1] for all t.

Algorithm: Initialize DP array. Consider a fixed t. For each edge from a to b, update dp[b][t] = 
max money at b at current time against (dp[a][t-1] + mb) = max money getting to b through a. We update
the max profit against dp[1][t] - c*t*t.

We do the above for t = 1,...,1000 and write the answer to the output file.

*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// initialize MAXN=max #cities, MAXT=max time
const int MAXN = 1005;
const int MAXT = 1005;

// declare n=#cities, m=#roads, c=travel constant
long long n, m, c;
// declare value[i]=money at city i
long long value[MAXN];
// declare dp[t][x]=max money at city x at time t
long long dp[2][MAXN];
// declare vector of edges of graph
vector<pair<int, int>> edges;

// program entry point
int main()
{
  // use cin to read from time.in
  freopen("time.in", "r", stdin);
  // use cout to write to time.out
  freopen("time.out", "w", stdout);
  // read in n, m, c
  cin >> n >> m >> c;
  // initialize value[i]=money at city i
  for (int i = 1; i <= n; i++)
  {
    cin >> value[i];
  }
  // declare a,b = endpoints of next edge
  int a, b;
  // read in each edge and push it to edges
  for (int i = 0; i < m; i++)
  {
    cin >> a >> b;
    edges.push_back(make_pair(a, b));
  }
  // initialize max profit as 0
  long long max_profit = 0;
  // fill dp with -1 representing 'unreachable'
  memset(dp, -1, sizeof dp);
  // base case: at time 0 at city 1 the max money is 0. all other cities unreachable at time 0.
  dp[0][1] = 0;
  for (int t = 1; t < MAXT; t++)
  {
    // p = current time
    int p = t % 2;
    // reset the values of dp[p] to -1
    memset(dp[p], -1, sizeof dp[p]);
    // for each edge in edges
    for (auto &e : edges)
    {
      // a=source city
      a = e.first;
      // b=endpoint city
      b = e.second;
      // if city a is reachable at previous time
      if (dp[1 - p][a] >= 0)
      {
        // update dp[p][b] with recurrence: see if walking to b thru a gives Bessie more money
        dp[p][b] = max(dp[p][b], dp[1 - p][a] + value[b]);
      }
    }
    // update max profit for each time t
    max_profit = max(max_profit, dp[p][1] - c * t * t);
  }
  // write max profit to the output stream followed by a newline.
  cout << max_profit << "\n";
}