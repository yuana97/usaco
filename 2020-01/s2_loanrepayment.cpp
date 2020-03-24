/*
Question:
Farmer John has to pay Bessie N gallons of milk within K days. He must give Bessie
at least M gallons of milk per day. Suppose G is the amount of gallons Farmer John
has paid so far. He gives Bessie max((N-G)/X, M) the next day, where X is some integer.
Determine the maximum possible X such that Farmer John pays off his debt within K days.

Solution:
We do binary search for X. That is, we set minX = 1, maxX = N/M, midX = (minX+maxX)/2.
If midX works that means we should search for bigger X, set minX = midX and recalculate.
If midX doesn't work that means we should search for smaller X, set maxX = midX and recalculate.

Hence it suffices to efficiently calculate whether a given X works. Consider Y = int((N-G)/X).
Y does not change with every payment when X is sufficiently large: for a given N-G gallons left,
it will take num = ((N-G)%X)/Y + 1 days for Y to decrease. We skip calculating Y for these days
and instead just add num*Y to G and decrease K by num.

*/

#include <stdio.h>

// check if the given x works to pay n gallons within k days with m minimum payment
int valid(long long n, long long k, long long m, long long x)
{
  long long g = 0;
  // while we still have days to pay debt (k > 0)
  // and we haven't paid off the debt yet (g < n)
  while (k > 0 && g < n)
  {
    // calculate y
    long long y = (n - g) / x;
    // if y < m, decide if we're done
    if (y < m)
    {
      // calculate days left to pay off debt with M gallons per day
      long long leftover = (n - g + m - 1) / m;
      // return true if we have enough time and false otherwise
      return leftover <= k;
    }
    // I'm not sure why the author calculates it in this way, but the idea is:
    // maxmatch-g = (n-g)%x = distance of n-g to the nearest multiple of x
    // = gallons remaining until y decreases by 1.
    // then divide this by y and add 1 to get number of payments we make until y decreases
    long long maxmatch = n - x * y;
    long long numdays = (maxmatch - g) / y + 1;
    if (numdays > k)
      numdays = k;
    // add y*numdays gallons
    g += y * numdays;
    // subtract numdays days
    k -= numdays;
  }
  // return true if we pay at least n gallons in k days
  return g >= n;
}

int main()
{
  // open read/write streams
  freopen("loan.in", "r", stdin);
  freopen("loan.out", "w", stdout);
  // declare n, k, m
  long long n, k, m;
  // read the first 3 numbers into n, k, m
  scanf("%lld %lld %lld", &n, &k, &m);
  // declare lhs (left hand side) = largest X we know will work = minX,
  // rhs (right hand side) = smallest X we know will fail = maxX
  long long lhs = 1;
  long long rhs = 1e12;
  // while we still have a range to search
  while (lhs < rhs)
  {
    // calculate midX
    long long mid = (lhs + rhs + 1) / 2;
    // if mid is valid
    if (valid(n, k, m, mid))
    {
      // search for larger X
      lhs = mid;
    }
    else
    {
      // otherwise search for smaller X
      rhs = mid - 1;
    }
  }
  // print the X we found
  printf("%lld\n", lhs);
}