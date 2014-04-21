//
// Chapter 07. Quicksort
//
// Quicksort implementation
//
// Hao Wu, 04/21/2014
//

#include <stdio.h>

//
///
//

void _partition(int* a, int i, int j, int* p_k)
{
  int i0 = i;
  int x = a[i0];
  i++;
  while (true) {
    while (i <= j && a[i] <= x) {
      i++;
    }
    while (i <= j && a[j] >= x) {
      j--;
    }
    if (i >= j) {
      break;
    }
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
  }
  a[i0] = a[j];
  a[j] = x;
  *p_k = j;
}

//

void _quicksort(int* a, int i, int j)
{
  if (i >= j) {
    return;
  }
  int k;
  _partition(a, i, j, &k);
  _quicksort(a, i, k - 1);
  _quicksort(a, k + 1, j);
}

//

void quicksort(int* a, int n)
{
  _quicksort(a, 0, n - 1);
}

//
///
//

int main()
{
  int a[] = {5, 2, 4, 6, 1, 3};
  int n = 6;
  //int a[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7,
  //           12, -5, -22, 15, -4, 7};
  //int n = 16;
  quicksort(a, n);
  for (int i = 0; i < n; i++) {
    printf("%d\n", a[i]);
  }
  printf("\n");
}

//
///
////
///
//

