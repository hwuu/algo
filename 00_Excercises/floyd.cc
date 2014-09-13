//
// Implementation of the Floyd Algorithm
//
// Hao Wu, 06/28/2014
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

/**
 * F[i][j][k] = min {
 *                F[i][j][k - 1],
 *                F[i][k][k - 1] + F[k][j][k - 1]
 *              },
 * where k >0 and i, j <= k.
 *
 * The correctness of using a n * n matrix instead of a
 * n * n * n cube is that:
 * 
 *   1) If i == k or j == k, then F[i][j][k] == F[i][j][k - 1];
 *   2) If i != k and j != k, then updating F[i][j] will not
 *      affect the values of F[i][k] and F[k][j].
 *
 */
void Floyd(const Graph& g, vector<vector<int> >* pvv_dist)
{
  pvv_dist->resize(g.n, vector<int>(g.n, -1));
  for (int u = 0; u < g.n; u++) {
    for (int i = 0; i < g.index[u].size(); i++) {
      const Edge& e = g.v_edge[g.index[u][i]];
      (*pvv_dist)[e.u][e.v] = e.d;
    }
  }
  for (int k = 1; k < g.n; k++) {
    for (int u = 0; u < g.n; u++) {
      for (int v = 0; v < g.n; v++) {
        int d_uv = (*pvv_dist)[u][v]; 
        int d_uk = (*pvv_dist)[u][k];
        int d_kv = (*pvv_dist)[k][v];
        if (d_uk < 0 || d_kv < 0) {
          continue;
        }
        if (d_uv < 0 || d_uv > d_uk + d_kv) {
          (*pvv_dist)[u][v] = d_uk + d_kv;
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
  vector<vector<int> > vv_dist;
  Floyd(g, &vv_dist);
  cout << vv_dist[0][3] << endl;
  return 0;
}

//
///
////
///
//

