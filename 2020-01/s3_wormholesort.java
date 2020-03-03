/*
Question:
N cows in order represented by permutation of N, M wormholes from ai to bi. 
Cows go thru wormholes until they are sorted. Maximize the width of the
least-wide wormhole they go thru.

Input:
N, M then the permutation of N, then M triples ai,bi,wi.

Solution: 
Binary search on the answer x. For all wormholes with width >+ x,
draw an edge between ai and bi. Possible to sort cows with wormholes of width at least
x iff resulting graph is connected.

To see this is true, consider the case when edges form a tree. Can always
swap until leaf contains correct cow. Then remove leaf and continue.
*/

import java.io.*;
import java.util.*;
public class wormsort {
  public static void main(String[] args) throws IOException{
    // init bufferedreader of wormsort.in
    BufferedReader br = new BufferedReader(new FileReader("wormsort.in"));
    // init stringtokenizer of nextline
    StringTokenizer st = new StringTokenizer(br.readLine());
    // read n, m from stringtokenizer
    int n = Integer.parseInt(st.nextToken());
    int m = Integer.parseInt(st.nextToken());
    // initialize locations, component, edges.
    loc = new int[n];
    component = new int[n];
    edges = new LinkedList[n];
    for(int i = 0; i < n; i++) edges[i] = new LinkedList<>();
    // init arrays for wormholes
    lhs = new int[m];
    rhs = new int[m];
    weight = new int[m];
    // parse in locations
    st = new StringTokenizer(br.readLine());
    for(int i = 0; i < n; i++) loc[i] = Integer.parseInt(st.nextToken())-1;
    // init graph
    for(int i = 0; i < m; i++) {
      st = new StringTokenizer(br.readLine());
      int a = Integer.parseInt(st.nextToken())-1;
      int b = Integer.parseInt(st.nextToken())-1;
      int w = Integer.parseInt(st.nextToken());
      edges[a].add(new Edge(b, w));
      edges[b].add(new Edge(a, w));
    }
    br.close();
    // init min and max 
    int minW = 0;
    int maxW = 1000000001;
    // binary search for minimum width
    while(minW != maxW) {
      int mid = (minW + maxW + 1) / 2;
      if(valid(mid)) minW = mid;
      else maxW = mid-1;
    }
    // error handling
    if(minW > 1e9) minW = -1;
    // init printwriter of wormsort.out
    PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("wormsort.out")));
    // print min and close pw
    pw.println(minW);
    pw.close();
  }
  static int[] loc, lhs, rhs, weight;
  static LinkedList<Edge>[] edges;
  static int[] component;
  // label current vertex and search all children. 
  private static void dfs(int curr, int label, int minW) {
    if(component[curr] == label) return;
    component[curr] = label;
    for(Edge child: edges[curr]) if(child.w >= minW) dfs(child.d, label, minW);
  }
  // valid: if resulting graph with given minw is connected
  private static boolean valid(int minW) {
    // mark component as unvisited
    Arrays.fill(component, -1);
    int numcomps = 0;
    // dfs on each vertex
    for(int i = 0; i < component.length; i++) {
      // dfs if unvisited
      if(component[i] < 0) {
        // mark as new component, with minw constraint
        dfs(i, numcomps++, minW);
      }
    }
    // not in same component => return false.
    for(int i = 0; i < loc.length; i++) {
      if(component[i] != component[loc[i]]) return false;
    }
    return true;
  }
  static class Edge {
    int d, w;
    public Edge(int d, int w) {
      this.d = d;
      this.w = w;
    }
  }
}