// In order to improve their physical fitness, the cows have taken up gymnastics! Farmer John designates his favorite cow Bessie to coach the N other cows and to assess their progress as they learn various gymnastic skills.
// In each of K practice sessions (1≤K≤10), Bessie ranks the N cows according to their performance (1≤N≤20). Afterward, she is curious about the consistency in these rankings. A pair of two distinct cows is consistent if one cow did better than the other one in every practice session.

// Help Bessie compute the total number of consistent pairs.

// INPUT FORMAT (file gymnastics.in):
// The first line of the input file contains two positive integers K and N. The next K lines will each contain the integers 1…N in some order, indicating the rankings of the cows (cows are identified by the numbers 1…N). If A appears before B in one of these lines, that means cow A did better than cow B.
// OUTPUT FORMAT (file gymnastics.out):
// Output, on a single line, the number of consistent pairs.

// SAMPLE INPUT:
// 3 4
// 4 1 2 3
// 4 1 3 2
// 4 2 1 3
// SAMPLE OUTPUT:
// 4

// for each pair of cows (a, b) we will count how many practice sessions
// a did better than b in. a>b in all K practice sessions => increment counter.
// print counter once done looping over all pairs of cows

#include <iostream>
#include <fstream>
using namespace std;

int N, K;
// array recording data
int arr[10][20];

// return true if a is better than b in a given session
bool better(int a, int b, int session)
{
   int apos, bpos;
   for(int i = 0; i<N; i++) {
      if (arr[session][i] == a) apos = i;
      if (arr[session][i] == b) bpos = i;
   }
   return apos < bpos;
}

// count # of sessions in which a > b
int Nbetter(int a, int b)
{
   int total=0;
   for (int session=0; session<K; session++)
      if (better(a, b, session)) total++;
   return total;
}

int main(void)
{
   ifstream fin ("gymnastics.in");
   ofstream fout ("gymnastics.out");
   // stream in K, N
   fin >> K >> N;
   // stream in data to arr
   for (int k=0; k<K; k++)
      for (int n=0; n<N; n++)
         fin >> arr[k][n];
   int answer = 0;
   // for each pair increment answer if a dominates b
   for (int a=1; a <= N; a++)
      for (int b=1; b<=N; b++)
         if (Nbetter(a,b)==K) answer++;
   // print answer
   fout << answer << "\n";
   return 0;
}