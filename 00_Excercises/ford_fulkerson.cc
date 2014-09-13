//
// Implementation of the Ford-Fulkerson algorithm
//
// Ref: http://goo.gl/c1qlCP
//
// Hao Wu, 09/14/2014
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//
///
//

template<int N>
struct Graph
{
  int adj[N][N];
  //
  Graph()
  {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        adj[i][j] = 0;
      }
    }
  }
};

//
///
//

template<int N>
void FindAugmentingPath(const Graph<N>& g, int s, int t,
    vector<int>* pv_prev)
{
  pv_prev->resize(N, -1);
  queue<int> q;
  vector<bool> v_vis(N, false);
  q.push(s);
  v_vis[s] = true;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int v = 0; v < N; v++) {
      if (g.adj[u][v] > 0 && v_vis[v] == false) {
        v_vis[v] = true;
        q.push(v);
        (*pv_prev)[v] = u;
      }
    }
  }
}

//
///
//

template<int N>
int FordFulkerson(const Graph<N>& g, int s, int t)
{
  Graph<N> h; // Residual graph.
  for (int u = 0; u < N; u++) {
    for (int v = 0; v < N; v++) {
      h.adj[u][v] = g.adj[u][v];
    }
  }
  int max_flow = 0;
  while (true) {
    vector<int> v_prev;
    FindAugmentingPath(h, s, t, &v_prev);
    if (v_prev[t] == -1) break;
    int path_flow = -1;
    int v = t;
    while (v != s) {
      int u = v_prev[v];
      int w = h.adj[u][v];
      if (path_flow == -1 || path_flow > w) {
        path_flow = w;
      }
      v = u;
    }
    v = t;
    while (v != s) {
      int u = v_prev[v];
      h.adj[u][v] -= path_flow;
      h.adj[v][u] += path_flow;
      v = u;
    }
    max_flow += path_flow;
  }
  return max_flow;
}

//
///
//

int main()
{
  Graph<6> g;
  g.adj[0][1] = 16;
  g.adj[0][2] = 13;
  g.adj[1][2] = 10;
  g.adj[1][3] = 12;
  g.adj[2][1] = 4;
  g.adj[2][4] = 14;
  g.adj[3][2] = 9;
  g.adj[3][5] = 20;
  g.adj[4][3] = 7;
  g.adj[4][5] = 4;
  cout << FordFulkerson(g, 0, 5) << endl;
  return 0;
}

//
///
////
///
//
//
///
////
///
//
//
///
////
///
//
//
///
////
///
//
//
///
////
///
//

