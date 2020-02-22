/*
Determine Nth number which is not a multiple of 3 or 5.
*/

/*
Solution: Let f(n) denote the n-th number spoken. Per 15 turns
there are 8 numbers spoken (as there are 7 multiples of 3 or 5: 
3, 5, 6, 9, 10, 12, 15). 

Hence f(n) = f(n-8) + 15 (8 numbers spoken per 15 numbers). Use this recurrence
to calculate f(n).
*/

#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi; 
 
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define trav(a,x) for (auto& a: x)
 
#define pb push_back
 
void setIO(string name) {
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
	ios_base::sync_with_stdio(0);
}

vi stor; // first 8 numbers

// number => is spoken
bool ok(int x) { return x%3 && x%5; } // not fizz or buzz
// get nth spoken via brute force
int dumb(int N) { // get f(n) slowly
	for (int i = 1;;++i) if (ok(i)) {
		N --;
		if (N == 0) return i;
	}
}
// get value of f(n) from equivalence class
int smart(int N) { // get f(n) quickly
	int num = (N-1)/8;
	return stor[N-8*num-1]+15*num;
}

int main() {
	setIO("moobuzz");
   // brute force the first 8 nums
	FOR(i,1,16) if (ok(i)) stor.pb(i);
	int N; cin >> N;
   // calculate f(n) via recurrence
	cout << smart(N) << "\n";
}