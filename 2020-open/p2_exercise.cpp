/*
Exercise

Question:
Farmer John has come up with another exercise routine for the cows.

N cows (1 <= N <= 7500) are standing in a line. They repeat the following step until the cows are in
the same order as they started:

Given a permutation A, the cows change their order so the cow at position i goes to position Ai (this is
what it means to apply a permutation to an array). Compute the product of the steps needed over all N! possible
permutations A of N. As the number may be very large, output the answer modulo the prime M.

Solution:
First some basic math: The number of steps a permutation takes to repeat is called the period of the permutaiton.
Every permutation can be partitioned into cycles of lengths c1, c2, ..., ck and the period of the permutation is equal
to the least common multiple lcm(c1, c2, ... , ck).

Now we build the solution up from a basic solution to one which is fast enough for N=7500.

N <= 50: Naive
Maintain the number of possible permutations for each possible LCM of a permutation with n elements for each
1 <= n <= N. Then for each LCM we multiply the answer by lcm^count to get the result. We can make a small optimization
by storing each count mod M-1 because by Fermat's Little Theorem a^(M-1) mod M = 1 where a is any integer, so 
multiplying lcm^(k(m-1)) wouldn't contribute anything to the answer (in mod M, its the same as multiplying by 1).

N <= 500: Mediocre
Speed up the period calculation: note that LCM(c1, c2, ... , ck) = product of greatest number of times a prime power
appears in any of the ci's.

N <= 3000:
If we count the number of ways to create a permutation of length n for n=1,...,N such that no cycle length is divisible
by p^k in O(N^2/D), then the solution runs in O(N^2logN).

N <= 7500:
Note if 2D > N we can compute the number of permutations containing a cycle with length divisible by D in O(1).
This is true because if there is a cycle with length divisble by D, then there must be exactly one cycle with
length = D and the rest can have arbitrary lengths.

Let D = p^k. Any permutations has between 0 and floor(N/D) cycles with length divisible by D. So it suffices to count
each of the following quantities for each k = 0,..,floor(N/D):

1. The number of permutations of length Dk such that every cycle has length divisible by D
2. The number of permutations of length N-Dk such that no cycle has length divisible by D.

If we can count both of these in O(N^2/D^2) this solution runs in O(N^2).

Summary:
This is a very difficult problem, I'll have to look at it again and come up with a summary later.

*/

#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;

int n; LL m;

typedef unsigned long long ull;
typedef __uint128_t L;

// this is known as the Barrett reduction, it speeds up mod calculations but you don't have
// to understand it.
struct FastMod {
  ull b, m;
  FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}
  ull reduce(ull a) {
    ull q = (ull)((L(m) * a) >> 64);
    ull r = a - q * b;
    return r >= b ? r - b : r;
  }
};
// initialize fastmod object
FastMod f(2);

// multiply x, y mod m
LL mul(LL x, LL y) {
  return f.reduce(x * y);
}

// add mod m
LL add(LL x, LL y) {
  x += y;
  if (x >= m) x -= m;
  return x;
}

// subtract mod m
LL sub(LL x, LL y) {
  x -= y;
  if (x < 0) x += m;
  return x;
}

// a^b mod m using binary exponentiation
LL powmod(LL a, LL b) {
  LL res=1;
  a %= (m+1);
  for(;b;b>>=1) {
    if (b&1) res = res*a % (m+1);
    a = a*a % (m+1);
  }
  return res;
}

const int MAXN = 7505;
// factorial[i] = i!
// c[i][j] = i choose j = # of ways to choose a subset of size j from a set of size i
LL factorial[MAXN], c[MAXN][MAXN];

int main() {
  // open io streams and get data
  freopen("exercise.in", "r", stdin);
  freopen("exercise.out", "w", stdout);
  cin >> n >> m;
  // take numbers modulo m-1
  m--;
  f = FastMod(m);

  // populate factorial array
  factorial[0] = 1;
  for (int i = 1; i < MAXN; ++i) factorial[i] = mul(factorial[i-1], i);

  // populate c[i][j] with the pascal triangle recurrence
  c[1][0] = c[1][1] = 1;
  for (int i = 2; i < MAXN; i++) {
    c[i][0] = c[i][i] = 1;
    for (int j = 1; j < i; j++) c[i][j] = add(c[i-1][j-1], c[i-1][j]);
  }

  // composite[i] = 0 if i is prime and 1 if i is composite
  vector<int> composite(MAXN);

  LL ans = 1;
  for (int i = 2; i <= n; i++) {
    // if i is prime
    if (!composite[i]) {
      // for every power j of i
      for (int j = i; j <= n; j *= i) {
        // aj[k] = # permutations of length j*k where ALL cycles divisible by j
        vector<LL> aj(n/j+1);
        aj[0] = 1;

        for (int k = 1; k < n/j+1; k++) {
          for (int l = 1; l <= k; l++) {
            // a recurrence for aj[k]. how it works:
            // for a fixed tail size j*l, pick j*l numbers and scramble them in any way, and
            // append those to permutations for k-1.
            aj[k] = add(aj[k], mul(mul(c[j*k-1][j*l-1], factorial[j*l-1]), aj[k-1]));
          }
        }

        // count permutations of length n-j*k where NO cycle is divisible by j
        vector<LL> nj(n/j+1);
        for (int k = n/j; k >= 0; k--) {
          // count all permutations with that length
          nj[k] = factorial[n-j*k];
          for (int l = k+1; l <= n/j; l++) {
            // subtract out all permutations with a cycle divisible by j
            nj[k] = sub(nj[k], mul(c[n-j*k][n-l*j], mul(aj[l-k], nj[l])));
          }
        }
        // add contribution of prime i to the result
        ans = (ans * powmod(i, sub(factorial[n], nj[0]))) % (m+1);
      }
      // do sieve of eratosthenes to mark multiples of i as composite
      for (int j = 2*i; j <= n; j+= i) {
        composite[j] = 1;
      }
    }
  }
  printf("%lld\n", ans);
}
