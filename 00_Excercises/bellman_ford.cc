//
// Implementation of the Bellman-Ford Algorithm
//
// Hao Wu, 06/27/2014
//

#include <iostream>
#include <vector>
//
using namespace std;

//
///
//

struct Edge
{
  int u;
  int v;
  int d;
  //
  Edge(int u, int v, int d);
};

//

struct Graph
{
  int n;
  vector<Edge> v_edge;
  vector<vector<int> > index;
  //
  Graph(int n);
  void AddEdge(int u, int v, int d);
};

//
///
//

Edge::Edge(int u, int v, int d)
  : u(u), v(v), d(d)
{}

//

Graph::Graph(int n)
  : n(n)
{
  index.resize(n);
}

//

void Graph::AddEdge(int u, int v, int d)
{
  v_edge.push_back(Edge(u, v, d));
  index[u].push_back(v_edge.size() - 1);
}

//
///
//

void BellmanFord(
    const Graph& g, int s,
    vector<int>* pv_dist, bool* p_neg)
{
  vector<int> v_visited(g.n, false);
  v_visited[s] = true;
  pv_dist->resize(g.n, -1);
  (*pv_dist)[s] = 0;
  for (int i = 0; i < g.n; i++) {
    for (int j = 0; j < g.v_edge.size(); j++) {
      const Edge& e = g.v_edge[j];
      if (v_visited[e.u] == false) {
        continue;
      }
      int& d_su = (*pv_dist)[e.u];
      int& d_sv = (*pv_dist)[e.v];
      if (v_visited[e.v] == false || d_sv > d_su + e.d) {
        if (i < g.n - 1) {
          d_sv = d_su + e.d;
          v_visited[e.v] = true;
        } else {
          *p_neg = true;
          return;
        }
      }
    }
  }
}

//
///
//

int main()
{
  Graph g(4);
  g.AddEdge(0, 1, 20);
  g.AddEdge(0, 2, 40);
  g.AddEdge(1, 3, 30);
  g.AddEdge(2, 3, 15);
  vector<int> v_dist;
  bool neg;
  BellmanFord(g, 0, &v_dist, &neg);
  cout << v_dist[3] << endl;
  return 0;
}

//
///
////
///
//

