// /* unfinished
// Question:
// Tired of his stubborn cowlick, Farmer John decides to get a haircut.
// He has N hairs in a line, with hair i having length 0 <= Ai <= N. Let the 'badness' of his
// hairs to be the number of inversions: pairs (i, j) such that i < j but Ai > Aj.

// For each j = 0, 1, ... , N-1 calculate the badness if all hairs with length > j
// are cut to length j.

// Solution:
// For each j we need to count pairs (x, y) such that x < y, A[x] > A[y] and A[y] < j.

// */

// // imports
// #include <iostream>
// #include <algorithm>
// // namespace
// using namespace std;
// // max value of N
// #define MAXN 100005

// int N;
// // hair lengths
// int A[100000];
// int T[MAXN + 1];

// int getSum(int i) {
//   int c = 0;
//   for (++i; i > 0; i -= (i & -i))
// }