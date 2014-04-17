//
// Chapter 02. Getting Started
//
// Maximum-Subarray Problem (P68~74)
//
// Hao Wu, 04/17/2014
//

#include <stdio.h>

//
///
//

inline int _max(int a, int b, int c)
{
  if (a < b) {
    return (c < b) ? b : c;
  } else {
    return (c < a) ? a : c;
  }
}

//

int _find_crossing_maximum_subarray(int* a, int i, int mid, int j)
{
  int sum1 = 0, max1 = 0;
  for (int k = mid; k >= i; k--) {
    sum1 += a[k];
    if (k == mid || max1 < sum1) {
      max1 = sum1;
    }
  }
  int sum2 = 0, max2 = 0;
  for (int k = mid + 1; k <= j; k++) {
    sum2 += a[k];
    if (k == mid + 1 || max2 < sum2) {
      max2 = sum2;
    }
  }
  return max1 + max2;
}

//

int _find_maximum_subarray(int* a, int i, int j)
{
  if (i == j) {
    return a[i];
  }
  int mid = i + (j - i) / 2;
  int sum1 = _find_maximum_subarray(a, i, mid);
  int sum2 = _find_maximum_subarray(a, mid + 1, j);
  int sum3 = _find_crossing_maximum_subarray(a, i, mid, j);
  return _max(sum1, sum2, sum3);
}

//

int find_maximum_subarray(int* a, int n)
{
  return _find_maximum_subarray(a, 0, n - 1);
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

