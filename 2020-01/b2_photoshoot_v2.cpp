#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

const int BIG = 1000000000;

//======================================================================

void adjustForA1(vector<int> &a, int a1) // a[0] irrelevant; add a1 to odds, subtract a1 from evens
{
  for (int &value : a)
  {
    value -= a1;
    a1 = -a1;
  }
}

//======================================================================

bool check(const vector<int> &a) // Check that this is the numbers 1, ..., N (ignoring a[0])
{
  int N = a.size() - 1;
  set<int> S(a.begin() + 1, a.end());
  return (S.size() == N && (*S.begin() == 1) && (*S.rbegin() == N));
}

//======================================================================

int main()
{
  // istream &in = cin;
  // istringstream in( "5       \n"                   // Original example
  //                   "4 6 7 6 \n" );
  // istringstream in( "8                    \n"      // Dutch's example
  //                   "12  9  7  9 13  7  4 \n" );
  istringstream in("100 \n"
                   "11  84  77  76  93  74  99  57  30  105 149 127 147 179 126 86    "
                   "101 124 139 89  113 147 99  88  125 104  43  37  50 117 189    "
                   "157 98  88  153 146 143 174 124 111 100 120 158  84  89 175    "
                   "158 149 106 110 115 53  54  74  127  93  32  71 146  96  25 44 "
                   "43  68  100 82  41  13  71  110 46   78 161 119  44  63 101 90 77  "
                   "123 143 141 128 89  56  73  126 151 176 162  79  13  32  63 130 "
                   "191 169 139 108                                          \n");

  // Input data
  int N;
  in >> N;
  vector<int> a(1 + N), b(1 + N); // ignore index [0]
  for (int i = 1; i < N; i++)
    in >> b[i];

  // First set values as if a[1]=0.
  // Later, adjust this: even indices - subtract a[1]; odd indices: add a[1];
  bool even = true;              // Here, refers to i+1
  int minEven = BIG, minOdd = 0; // a[1] is initially 0, hence setting of minOdd.
  for (int i = 1; i < N; i++)
  {
    a[i + 1] = b[i] - a[i];
    if (even && a[i + 1] < minEven)
      minEven = a[i + 1];
    if (!even && a[i + 1] < minOdd)
      minOdd = a[i + 1];
    even = !even;
  }

  // Work out what a[1] would have to be if 1 is to be in the even or odd indices
  int a1Even = minEven - 1;
  int a1Odd = 1 - minOdd;

  // Now try one or both of these two possible values for a[1]
  bool ok = true;
  if (a1Odd < 1) // Only one possible solution with 1 lying in even indices
  {
    adjustForA1(a, a1Even);
    ok = check(a);
  }
  else if (a1Even < 1) // Only one possible solution with 1 lying in odd indices
  {
    adjustForA1(a, a1Odd);
    ok = check(a);
  }
  else // Two possible solutions: gonna have to try them
  {
    int a1 = min(a1Even, a1Odd); // Try this first; if it works it's optimal (minimum lexico..whatever)
    adjustForA1(a, a1);
    ok = check(a);
    if (!ok) // Yuk; try the other
    {
      a1 = max(a1Even, a1Odd) - a1;
      adjustForA1(a, a1);
      ok = check(a);
    }
  }

  // Write out if solved; cry if not
  if (!ok)
  {
    cout << "Something's wrong!";
    return 1;
  }
  else // Write solution
  {
    for (int i = 1; i <= N; i++)
      cout << a[i] << ' ';
    cout << '\n';
  }
}