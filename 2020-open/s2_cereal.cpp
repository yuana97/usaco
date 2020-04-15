/*

Cereal

Question:
1 <= M <= 10^5 types of cereal, one box of each type. Each of 1 <= N <= 10^5 cows has a favorite cereal
and a second favorite cereal. When a cow gets to choose cereal, she will choose her favorite cereal if its
available, otherwise her second favorite cereal, otherwise leave with no cereal.

The cows have lined up for cereal. For 0 <= i <= N-1, determine how many cows would get cereal if FJ removed
the first i cows from the line.

Solution:
Simulation yields an O(N^2) solution which is too slow. Instead, we want to start with i=N and find a recurrence
for updating the cereal count under the operation "add cow to the front of the line".

Suppose the new cow has preferences (f, s). IF the last N-i cows didn't take cereal f, then nothing changes.
If some cow j took cereal f, then j no longer gets f. If f is j's second choice, j now gets nothing. But if f
is j's first choice, then j might steal her second choice from a previous cow k...and so on.

Its not clear that this approach is fast enough, as each cow we add to the front of the line might trigger an
O(N) recursive process which would bring the total complexity to O(N^2). However we can prove that the sum of 
the recursive calls is O(N) using the method of invariants: adding a cow can kick a later cow from first-preference
to second-preference or second-preference to nothing. However, adding a cow will never give a later cow something.
Therefore the number of 'kicks' (steps in the recursion) is monotonically increasing towards a maximum of 2N
(each cow can be kicked at most twice), so all the recursive calls put together are at most O(N). Hence this solution
is fast enough.

Summary:
Start with i=N and get recurrence for "add cow to the front".

*/

#include <iostream>
#include <algorithm>
using namespace std;
#define MAXN 100001

int N,M;
// f, s are first and second preferences of cow i
int f[MAXN];
int s[MAXN];
// occ[j] = cow which gets cereal j
int occ[MAXN];

int ans[MAXN];

int main()
{
  cin >> N >> M;
  for (int i = 0; i < N; i++)
    cin >> f[i] >> s[i];
  // cereal count
  int cnt = 0;
  for(int i = N-1; i >= 0; i--)
  {
    // get favorite cereal 'pos' of new front cow
    int j = i;
    int pos = f[i];
    // infinite loop. we break it when we're done updating count
    while(1)
    {
      // cereal not taken => give it to j, done
      if(occ[pos] == 0)
      {
        occ[pos] = j;
        cnt++;
        break;
      }
      // this should never happen
      else if(occ[pos] < j)
        break;
      else
      {
        // previous holder of pos cereal
        int k = occ[pos];
        // give pos to j
        occ[pos] = j;
        // if pos was a second choice don't do anything
        if (pos == s[k]) break;
        // otherwise k should get her second choice and we recursively continue this process
        j = k;
        pos = s[k];
      }
    }
    ans[i] = cnt;
  }
  for(int i = 0; i < N; i++)
    cout << ans[i] << '\n';
}