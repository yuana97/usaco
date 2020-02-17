/*
B3 Livestock Lineup

Input: 8 cows with N constraints "X must be milked beside Y"
Output: Ordering satisfying these constraints
*/

// solution 1: brute force. Try every permutation of cows
// until you find one which satisfies all constraints.

/* import standard libraries */
// import base file input/output library
#include <iostream>
// import fstream (fin, fout) which extends iostream
#include <fstream>
// import vectors library (arrays with flexible size and extra functionality)
#include <vector>
// import standard arrays algorithms library
#include <algorithm>
// specify we are using the standard namespace (google it)
// this way we can just write "vector" instead of "std::vector"
using namespace std;

/* store info from text */
// initialize 3 vectors: cows = cow names
// beside_a and beside_b together encode the pairs of cows
// e.g. beside_a[i] is next to beside_b[i] for all i.
// when we see a statement "X beside Y" we put X into beside_a and
// Y into beside_b.
vector<string> cows, beside_a, beside_b;
// the number of constraints (first variable streamed in)
int N;

// string c = cow
// where(c) returns index of c in cows and -1
// if c not found.
int where(string c)
{
   for (int i = 0; i < 8; i++)
      if (cows[i] == c)
         return i;
   return -1;
}

// returns whether or not our cows list satisfies the constraints
bool satisfies_constraints(void)
{
   // for each constraint
   for (int i = 0; i < N; i++)
      // if distance between two cows which are supposed to be neighbors
      // is more than 1, return false.
      if (abs(where(beside_a[i]) - where(beside_b[i])) != 1)
         return false;
   // loop finished => all constraints satisfied => return true
   return true;
}

// driver function
int main(void)
{
   // open input stream from lineup.in and output stream to lineup.out
   ifstream fin("lineup.in");
   ofstream fout("lineup.out");

   // read in number of constraints
   fin >> N;
   // populate the list of cows
   cows.push_back("Beatrice");
   cows.push_back("Belinda");
   cows.push_back("Bella");
   cows.push_back("Bessie");
   cows.push_back("Betsy");
   cows.push_back("Blue");
   cows.push_back("Buttercup");
   cows.push_back("Sue");

   // a = first cow, b = second cow
   // t = temp var to hold the irrelevant text
   string a, b, t;
   // for each constraint "a beside b" add a to beside_a
   // and b to beside_b
   for (int i = 0; i < N; i++)
   {
      // stream in a
      fin >> a;
      // skip past irrelevant text
      fin >> t; // must
      fin >> t; // be
      fin >> t; // milked
      fin >> t; // beside
      // stream in b
      fin >> b;
      // push a, b to their respective arrays
      beside_a.push_back(a);
      beside_b.push_back(b);
   }
   // iterate thru the permutations of cows until
   // we find one satisfying the constraints
   do
   {
      // satisfies constraints => print cow names
      if (satisfies_constraints())
      {
         // for each cow print their name to lineup.out followed by a newline
         for (int i = 0; i < 8; i++)
            fout << cows[i] << "\n";
         break;
      }
   // get next permutation of cows (next_permutation is a standard algorithm
   // from <algorithm>)
   } while (next_permutation(cows.begin(), cows.end()));
   // end of main
   return 0;
}