//
// Implementation of the Dijkstra Algorithm
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

void Dijkstra(const Graph& g, int s, vector<int>* pv_dist)
{
  vector<int> v_closed(g.n, false);
  pv_dist->resize(g.n, -1);
  (*pv_dist)[s] = 0;
  while (true) {
    int u = 0;
    int d_su = -1;
    for (int v = 0; v < g.n; v++) {
      if (v_closed[v] == true) {
        continue;
      }
      int d_sv = (*pv_dist)[v];
      if (d_sv >= 0 && (d_su < 0 || d_su > d_sv)) {
        u = v;
        d_su = d_sv;
      }
    }
    if (d_su == -1) {
      break;
    }
    v_closed[u] = true;
    for (int i = 0; i < g.index[u].size(); i++) {
      const Edge& e = g.v_edge[g.index[u][i]];
      int v = e.v;
      if ((*pv_dist)[v] < 0 || (*pv_dist)[v] > d_su + e.d) {
        (*pv_dist)[v] = d_su + e.d;
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
  Dijkstra(g, 0, &v_dist);
  cout << v_dist[3] << endl;
  return 0;
}

//
///
////
///
//

