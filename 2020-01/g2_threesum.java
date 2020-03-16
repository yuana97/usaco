/*

Question: 
The 3SUM problem: find all triples in an array adding up to zero.
Bessie provides array A of size N and Q subarrays of A. Solve 3SUM for each subarray.

Solution: 
For each pair (i, k) such that i < k let num[i][k] be the number of j between i and k
such that Ai + Aj + Ak = 0. Let ans[i][k] = 3SUM for Ai,...,Ak.
Then ans[i][k] = num[i][k] + ans[i][k-1] + ans[i+1][k] - ans[i+1][k-1].
Explanation: num[i][k] = add solutions on border of Ai,..,Ak,
ans[i][k-1]+ans[i+1][k] = add all solutions from left and right subarrays
- ans[i+1][k+1] = subtract doublecounted solutions from the middle.

Hence to compute all ans[i][k] it suffices to compute num[i][k] and use dynamic programming.
To compute num[i][i+1],...,num[i][N] in O(N) time, do the following. For k = i+1,...,N consider
a map that allows you to query the frequency of any integer among Ai+1,...,Ak-1.
Then num[i][k] = frequency of -Ai-Ak in this map. When k is incremented we insert
the new value into the map. This solution runs in O(N^2) time overall.

As the values of A are constrained between ±10^6, we use an array of 2*10^6+1 as the
frequency map.

Summary: 
ans[i][k] = #{answers using both i and k} + #{answers not using both i and k}.
#{answers not using both i and k} = ans[i+1][k]+ans[i][k-1]-ans[i+1][k-1] so it suffices
to calculate num[i][k] = #{answers using i and k}. To calculate num[i][i+1],...,num[i][N]
keep a frequency map of integers in Ai,...,Ak and set num[i][k] = frequency(-Ai-Ak).

*/

import java.io.*;

public class g2_threesum {
  public static void main(String[] args) throws IOException {
    // initialize file reader
    BufferedReader in = new BufferedReader(new FileReader("threesum.in"));
    // initialize file writer
    PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("threesum.out")));
    // get array of values from first line
    String[] line = in.readLine().split(" ");
    // read in N and Q from first line
    int N = Integer.parseInt(line[0]);
    int Q = Integer.parseInt(line[1]);
    // get array of values from second line
    line = in.readLine().split(" ");
    // initialize A
    int[] A = new int[N];
    // ans[i][k] = num[i][k] at first
    // then we do dynamic programming to make ans[i][k]=answer for Ai,..,Ak
    long[][] ans = new long[N][N];
    // read in integer values to A
    for (int i = 0; i < N; ++i)
      A[i] = Integer.parseInt(line[i]);
    // initialize frequency map
    // z[0]=frequency(-10^6),
    // z[1]=frequency(-10^6+1),...,z[10^6]=frequency(0),...,z[2*10^6]=frequency(10^6).
    int[] z = new int[2000001];
    // for every pair of indexes i<j
    for (int i = N - 1; i >= 0; --i) {
      for (int j = i + 1; j < N; ++j) {
        // get index of -Ai-Aj
        int ind = 1000000 - A[i] - A[j];
        // do a bounds check and set num[i][j] = frequency(-Ai-Aj)
        if (ind >= 0 && ind <= 2000000)
          ans[i][j] = z[ind];
        // increment the frequency of the jth number
        z[1000000 + A[j]]++;
      }
      // clear the frequency map
      for (int j = i + 1; j < N; ++j) {
        z[1000000 + A[j]]--;
      }
    }
    // use the equation ans[i][j]=num[i][j]+ans[i+1][j]+ans[i][j-1]-ans[i+1][j-1]
    // to fill ans.
    for (int i = N - 1; i >= 0; --i)
      for (int j = i + 1; j < N; ++j)
        ans[i][j] += ans[i + 1][j] + ans[i][j - 1] - ans[i + 1][j - 1];
    // for each pair of indexes, print the answer
    for (int i = 0; i < Q; ++i) {
      // read in next pair of indexes to an array
      line = in.readLine().split(" ");
      // parse them to integers
      int a = Integer.parseInt(line[0]);
      int b = Integer.parseInt(line[1]);
      // look up the answer in ans and write it to out
      out.println(ans[a - 1][b - 1]);
    }
    // close the write stream
    out.close();
  }
}