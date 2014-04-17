//
// Chapter 02. Getting Started
//
// Merge Sort
//
// Hao Wu, 04/16/2014
//

#include <stdio.h>
#include <string.h> // memcpy()

//
///
//

void _merge(int* a, int i, int mid, int j)
{
  static int a1[100], a2[100];
  //
  memcpy(a1 + i, a + i, (mid - i + 1) * sizeof(int));
  memcpy(a2 + mid + 1, a + mid + 1, (j - mid) * sizeof(int));
  int k = i, i1 = i, i2 = mid + 1;
  while (k <= j) {
    if (i2 > j || (i1 <= mid && a1[i1] <= a2[i2])) {
      a[k++] = a1[i1++];
    } else {
      a[k++] = a2[i2++];
    }
  }
}

//

void _merge_sort(int* a, int i, int j)
{
  if (i == j) return;
  int mid = i + (j - i) / 2;
  _merge_sort(a, i, mid);
  _merge_sort(a, mid + 1, j);
  _merge(a, i, mid, j);
}

//

void merge_sort(int* a, int n)
{
  _merge_sort(a, 0, n - 1);
}

//
///
//

int main()
{
  int a[] = {5, 2, 4, 6, 1, 3};
  int n = 6;
  merge_sort(a, n);
  for (int i = 0; i < n; i++) {
    printf("%d\n", a[i]);
  }
}

//
///
////
///
//

