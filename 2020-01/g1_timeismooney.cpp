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

// when the gcc compiler reads this header it imports all standard libraries
// google "gcc bits/stdc++.h"
#include <bits/stdc++.h>
// use standard namespace to omit the std:: from standard functions
// google 'std namespace'
using namespace std;

// initialize max values of N and T.
// initialize means to declare a variable and assign it a value
// google 'programming initialize'
const int MAXN = 1005;
const int MAXT = 1005;

// declare n=num cities, m=num roads, c=constant to be read in
// declare means to give a variable a type and a name (so the computer reserves memory for it)
// google programming 'declare'
long long n, m, c;
// declare value where value[i] = money at city i
long long value[MAXN];
// initialize 2d dp array with 2 rows and MAXN columns
// dp[t][x] represents the most money Bessie can have at the city x at time t
// (where t is considered mod 2)
long long dp[2][MAXN];

// declare vector of int pairs "edges" representing the edges of the graph
// google 'cpp vector', 'cpp pair', 'graph edges'
vector<pair<int, int>> edges;

// program entry point
int main()
{
  // use standard input stream 'cin' to read from time.in
  // google 'cpp standard streams'
  freopen("time.in", "r", stdin);
  // use standard output stream 'cout' to write to time.out
  freopen("time.out", "w", stdout);
  // assign n to the first token from the read stream
  // m to the second token, c to the third token
  cin >> n >> m >> c;
  // fill the value array with money values
  for (int i = 1; i <= n; i++)
  {
    // assign value[i] to the next token in the read stream
    cin >> value[i];
  }
  // declare a,b = endpoints of next edge
  int a, b;
  for (int i = 0; i < m; i++)
  {
    // assign a to first token from read stream, b to second token
    cin >> a >> b;
    // push the pair (a, b) to edges.
    // more detail: std::make_pair(a, b) returns a pair<int, int> 'x' with x.first=a, x.second=b.
    // Then edges.push_back(x) makes x the last element in the vector.
    edges.push_back(make_pair(a, b));
  }
  // initialize max profit as 0
  long long max_profit = 0;
  // initialize dp to be filled with the value -1
  // dp[t][x] = -1 represents city x is unreachable by time t
  // more detail: sizeof dp = number of bytes in the block of memory reserved for dp.
  // dp = pointer to start of block of memory. std::memset(dp, -1, sizeof dp) writes
  // -1 to (sizeof dp) number of bytes starting at dp. So it writes -1 to every byte of dp.
  // -1 in binary is all ones, so memset(dp, -1, sizeof dp) fills the dp block of memory with
  // all ones. When we interpret dp[t][x] as an integer, we get 4 bytes of -1 (111111111111 x4)
  // which is the same as -1 as an integer.
  // summary: fill dp memory block with all 1's. This is the same as filling the array dp with
  // all -1's.
  // why do this: style points + faster and less lines of code.
  // google 'twos complement' and 'cpp memset'
  memset(dp, -1, sizeof dp);
  // at time 0 at city 1 the most money Bessie can earn is 0.
  // remember dp[t][x] = max money at time t at city x
  dp[0][1] = 0;
  for (int t = 1; t < MAXT; t++)
  {
    // initialize parity p = t%2
    // parity = whether number is even or odd
    // p = 0 means number is even, p = 1 means number is odd
    // this is a way to track 'current time' where p is current time
    // and 1-p is the previous time (notice 1-0=1, 1-1=0 so 1-p is the 
    // opposite of p)
    int p = t % 2;
    // reset the values of dp[p] to -1. remember p = current time.
    memset(dp[p], -1, sizeof dp[p]);
    // for each edge in edges
    // more detail: auto means figure out what type e is based on edges.
    // in this case edges is a vector<pair<int, int>> so auto becomes pair<int, int>.
    // the & indicates to pass by reference. This means it passes a reference to the memory
    // address so you're getting the original object. On the other hand for(auto e : edges) makes
    // a copy of each edge e which makes it slower. Its faster to pass a reference to the original
    // object than to copy the object and then pass a reference to the new object.
    for (auto &e : edges)
    {
      // assign a,b to the endpoints of e
      a = e.first;
      b = e.second;
      // if at the previous time we traveled to city a
      // remember dp[1-p][x] is the most money we could
      // get at the previous time at city x
      if (dp[1 - p][a] >= 0)
      {
        // try traveling from a to b
        // more detail: dp[p][b] = current max money at b, (dp[1-p][a] + value[b])
        // equals max money traveling to a previously then coming to b.
        // we update dp[p][b]=current max money at b with the new possible max
        // dp[1-p][a] + value[b].
        dp[p][b] = max(dp[p][b], dp[1 - p][a] + value[b]);
      }
    }
    // update max profit for each time t
    // detail: dp[p][1] = max money for a trip ending at city 1. Bessie's trip has to
    // end at 1 so this is the max money for a single trip. c*t*t is the travling cost
    // so we update max with the net profit dp[p][1] - c*t*t. max profit is initialized as
    // 0 so this value is never negative.
    max_profit = max(max_profit, dp[p][1] - c * t * t);
  }
  // write max profit to the output stream followed by a newline.
  cout << max_profit << "\n";
}