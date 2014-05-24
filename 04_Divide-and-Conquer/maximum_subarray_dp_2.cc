//
// Chapter 04. Divide-and-Conquer
//
// Maximum-Subarray Problem (P68~74):
// O(n) time complexity, and O(1) space complexity.
//
// Hao Wu, 05/24/2014
//

#include <stdio.h>

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
  int b = a[0];
  int c = a[0];
  for (int i = 1; i < n; i++) {
    c = max(c + a[i], a[i]);
    b = max(b, c);
  }
  return b;
}

//
///
//

int main()
{
  //int a[] = {5, 2, 4, 6, 1, 3};
  int a[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7,
             12, -5, -22, 15, -4, 7};
  int n = sizeof(a) / sizeof(int);
  int sum = find_maximum_subarray(a, n);
  printf("%d\n", sum);
}

//
///
////
///
//

