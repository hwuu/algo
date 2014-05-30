//
// Chapter 16. Greedy Algorithms
//
// 0-1 Knapsack Problem in Exercise 16.2-2, page 427.
//
// Hao Wu, 05/30/2014
//

#include <stdio.h>
#include <stdlib.h> // malloc() and free()

//
///
//

int knapsack(int* v, int* w, int n, int wt)
{
  int m = wt + 1;
  int* a = (int*)malloc(n * m * sizeof(int));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      a[i * m + j] = (i == 0 && j >= w[i]) ? v[i] : 0;
    }
  }
  //for (int j = 0; j < m; j++) {
  //  printf("a[%d][%d] = %d\n", 0, j, a[0 * m + j]);
  //}
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int v0 = a[(i - 1) * m + j];
      int v1 = (j - w[i]) >= 0
               ? a[(i - 1) * m + (j - w[i])] + v[i]
               : 0;
      a[i * m + j] = v0 > v1 ? v0 : v1;
      //printf("%d, a[%d][%d] = %d\n", w1, i, j, a[i * m + j]);
    }
  }
  int res = a[(n - 1) * m + wt];
  free(a);
  return res;
}

//
///
//

int main()
{
  int v[] = {60, 100, 120};
  int w[] = {10, 20, 30};
  int wt = 50;
  int n = sizeof(v) / sizeof(int);
  int vt = knapsack(v, w, n, wt);
  printf("%d\n", vt);
  return 0;
}

//
///
////
///
//

