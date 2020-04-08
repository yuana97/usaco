/*
http://www.usaco.org/index.php?page=viewproblem2&cpid=1038

Question: N cows practice social distancing over M intervals of grass on the number line. Each cow must
be located at a point which is covered in grass. Let D = distance between the closest pair of cows.
Determine the largest possible value of D.

Solution: Binary search on D. For each D place cows at the leftmost position possible and see if this arrangement
works.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long LL;

// a big number. if u square this u get a number bigger than the max value a or b
// so we square this to get an upper bound on binary search
#define INF 2000000000
#define FF first
#define SS second

int n, m;

vector<pair<LL, LL>> intervals;

// check if this d works
bool ok(LL d)
{
  // previous location of cow
  LL prev = -1LL * INF * INF;
  int cnt = 0;

  //  for each interval in ascending order
  for (auto &i : intervals)
  {
    // while we can put another cow in this interval, put a cow
    while (max(prev + d, i.FF) <= i.SS)
    {
      prev = max(prev + d, i.FF);
      cnt++;
      // if we're done, break
      if (cnt >= n)
        break;
    }
    if (cnt >= n)
      break;
  }

  // this d works if we can place at least n cows
  return (cnt >= n);
}

int main()
{
  // hook up i/o streams
  freopen("socdist.in", "r", stdin);
  freopen("socdist.out", "w", stdout);

  // read in n and m
  cin >> n >> m;

  // set the length of intervals to m
  intervals.resize(m);
  // fill intervals
  for (int i = 0; i < m; ++i)
    cin >> intervals[i].FF >> intervals[i].SS;
  // sort intervals by starting point
  sort(intervals.begin(), intervals.end());

  // initialize boundaries for binary search
  LL lo = 1;
  LL hi = 1LL * INF * INF;
  LL res = -1;

  // while we still have to narrow down the value of d
  while (lo < hi)
  {
    // pick the middle possible value of d
    LL mid = (lo + hi) / 2;
    // if mid works, look for bigger d's
    if (ok(mid))
    {
      res = mid;
      lo = mid + 1;
    }
    // otherwise look for smaller d's
    else
    {
      hi = mid - 1;
    }
  }
  // print the result
  cout << res << "\n";
}