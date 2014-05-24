//
// Chapter 04. Divide-and-Conquer
//
// Maximum-Subarray Problem (P68~74): O(n) Complexity (P75)
//
// Hao Wu, 04/18/2014
//
// Reference 1: http://en.wikipedia.org/wiki/Maximum_subarray_problem
// Reference 2: http://goo.gl/mMA0LZ
//

#include <stdio.h>
#include <stdlib.h> // malloc() and free()

//
///
//

inline int max(int x, int y)
{
  return x < y ? y : x;
}

//

int find_maximum_subarray(int* a, int n)
{
  //
  // b[j]: best solution in a[0..j].
  // c[j]: best solution in a[0..j], whose right edge is exactly at j.
  //
  int* b = (int*)malloc(n * sizeof(int));
  int* c = (int*)malloc(n * sizeof(int));
  b[0] = a[0];
  c[0] = a[0];
  for (int i = 1; i < n; i++) {
    c[i] = max(c[i - 1] + a[i], a[i]);
    b[i] = max(b[i - 1], c[i]);
  }
  int s = b[n - 1];
  free(b);
  free(c);
  return s;
}

//
///
//

int main()
{
  //int a[] = {5, 2, 4, 6, 1, 3};
  int a[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7,
             12, -5, -22, 15, -4, 7};
  int n = 16;
  int sum = find_maximum_subarray(a, n);
  printf("%d\n", sum);
}

//
///
////
///
//

