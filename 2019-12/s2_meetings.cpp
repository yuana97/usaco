// Question: N cows on a line move at speed +/- 1. If a cow hits a barn its called a meeting
// and if two cows hit each other its called a "meeting" and they go in opposite directions.
// Let T = time when half the cows by weight stop moving. Return the number of meetings
// between start and T.

// Input: num cows, barn location from first line. Next N lines contain cow data
// as weight location direction.

/*
Solution: First Sort all cows by x-coordinate. 

Determining T: Consider the multiset of times when cows reach barns. Cows didnt switch
velocities => (di = -1 => add xi to multiset, di = 1 => add L - xi to multiset).
Note multiset is invariant whether cows switch velocities or not. Let z=number of cows
going left. Then z leftmost cows reach left barn in time xi and N-z
rightmost cows reach right barn in time L-xi. Sort finishing times and maintain
current total weight to determine T.

Summary: z=#leftdirs. z leftlocs at left in xi, N-z rightmost at right in L-xi. Sort by finish time.

Counting meetings: Now assume cows dont switch vels. Then xi < xj meet if 
going in opp directions and xj - xi <= 2T. Compute # of such pairs by iterating left to right
maintaining q that consists of those cows with di = 1 considering as candidates.

Summary: meet if opp dirs and close enough together (within 2T)
*/

// import all std algos
#include <bits/stdc++.h>
// use standard namespace
using namespace std;

// long long = ll
typedef long long ll;
// int vector = vi
typedef vector<int> vi; 
// vector of pairs = vpi
typedef vector<pair<int,int>> vpi; 
 
// for in range [a, b)
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
// for a times
#define F0R(i,a) FOR(i,0,a)
// reverse for in range
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
// reverse a times
#define R0F(i,a) ROF(i,0,a)
// trav: foreach a in x
#define trav(a,x) for (auto& a: x)

// pb=pushback: push to end of container
#define pb push_back
// rsz=resize: resize container
#define rsz resize
//sz(x)=size(x)
#define sz(x) int(x.size())
//all(x)=beginning to end iterators
#define all(x) begin(x), end(x)
// f,s = first/second in pairs
#define f first
#define s second

// set input/output from given files
void setIO(string name) {
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}

// vars
int N,L;
vi w,x,d;

// get cow weight,location,directions in location-sorted order
void init() {
   // init io
   setIO("meetings");
   // stream in size and barn location
   cin >> N >> L;
   // set weight, location, direction vectors
   w.rsz(N), x.rsz(N), d.rsz(N);
   // stream in vals in w, x, d vectors
   F0R(i, N) cin >> w[i] >> x[i] >> d[i];
   // fill inds(N) with 0, 1, .. N-1 (representing the cows)
   vi inds(N); iota(all(inds),0);
   // sort cows by location
	sort(all(inds),[](int a, int b) { return x[a] < x[b]; });
   // fill W,X,D with new cow order.
	vi W,X,D;
	trav(t,inds) {
		W.pb(w[t]);
		X.pb(x[t]);
		D.pb(d[t]);
	}
   // swap W,X,D vals back to w,x,d vals.
	swap(w,W), swap(x,X), swap(d,D);
}

// calc T: sort cows by arrival times and count weights
int getTime() {
   // lef=leftdir locs, rig=rightdir locs
	vi lef, rig;
	F0R(i,N) {
		if (d[i] == -1) lef.pb(x[i]);
		else rig.pb(x[i]);
	}
   // populate v with arrival,weight pairs and sort by arrival
	vpi v;
	F0R(i,sz(lef)) v.pb({lef[i],w[i]});
	F0R(i,sz(rig)) v.pb({L-rig[i],w[sz(lef)+i]});
	sort(all(v));
   // let tot=sum of weights
	int tot = 0; trav(t,v) tot += t.s;
   // decrease tot for each arrival, return arrival time when tot less than half.
	trav(t,v) {
		tot -= 2*t.s;
		if (tot <= 0) return t.f;
	}
}

int main() {
   // get weight,location,directions
	init();
   // get end time
	int t = getTime();
   // keep queue of right pointing cows
	queue<int> rig;
	int ans = 0;
	F0R(i,N) {
		if (d[i] == -1) {
         // pop old cows which dont work
			while (sz(rig) && rig.front()+2*t < x[i]) rig.pop();
         // add # working cows to ans
			ans += sz(rig);
		}
      // rightcow => push
      else rig.push(x[i]);
	}
	cout << ans << "\n";
}

// summary: sort by location, get end time, find valid pairs.