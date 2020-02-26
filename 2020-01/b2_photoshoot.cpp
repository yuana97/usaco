/*
Question:
There is some permutation of N, a1,..,aN. Bessie recorded the sequence
b1,...,bN-1 such that bi = ai + ai+1. Of all permutations a1,...,aN which could have 
resulted in this b1,...,bN-1, return the alphabetically smallest.

Solution:
If we set a1=i, we can figure out the rest of the ai's by ai+1 = ai - bi. We try 
a1 = 1,...,N and return the first one which works.

Complexity analysis:
O(N^2) runtime: for each a1 = i we do O(N) operations to calculate and verify a2,...,aN.
There are N possible values for a1 therefore the algorithm is O(N^2).

O(N) is possible, see b2_photoshoot_v2.

*/

#include <iostream>
#include <algorithm>
using namespace std;

int N;
int b[100000], d[100000], ans[100000];
bool used[100000];

int main()
{
  freopen("photo.in", "r", stdin);
  freopen("photo.out", "w", stdout);
  cin >> N;
  // stream in b[i]
  for (int i = 0; i < N - 1; i++)
    cin >> b[i];
  // populate d[i]
  for (int i = 2; i < N; i++)
    d[i] = b[i - 1] - b[i - 2];
  // for each possibility of a1
  for (int a = 1; a <= N; a++)
  {
    // calculate a2,...,aN
    ans[0] = a, ans[1] = b[0] - a;
    for (int i = 2; i < N; i++)
      ans[i] = ans[i - 2] + d[i];
    
    /* if this permutation doesnt work, throw it out */
    for (int i = 1; i <= N; i++)
      // used[i]=1 means i appears in the permutation
      used[i] = 0;
    // bad is a flag for the answer being a permutation.
    // bad = 0 means answer is a permutation, bad=1 means its not.
    bool bad = 0;
    for (int i = 0; i < N; i++)
    {
      // digit already found/out of bounds => not permutation, break.
      if (used[ans[i]] || ans[i] <= 0 || ans[i] > N)
      {
        bad = 1;
        break;
      }
      // mark digit as used
      used[ans[i]] = 1;
    }
    // not bad => answer found, print it out.
    if (!bad)
    {
      for (int i = 0; i < N; i++)
      {
        cout << ans[i];
        if (i < N - 1)
          cout << ' ';
      }
      cout << '\n';
      return 0;
    }
  }
}