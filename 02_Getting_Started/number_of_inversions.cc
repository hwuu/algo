//
// Chapter 02. Getting Started
//
// Number of Inversions (P41~42)
//
// Hao Wu, 04/17/2014
//

#include <stdio.h>
#include <stdlib.h> // malloc() and free()
#include <string.h> // memcpy()

//
///
//

void bubble_sort(int* a, int n, int* p_noi)
{
  *p_noi = 0;
  for (int i = n - 1; i >= 1; i--) {
    for (int j = 0; j < i; j++) {
      if (a[j] > a[j + 1]) {
        int x = a[j];
        a[j] = a[j + 1];
        a[j + 1] = x;
        (*p_noi)++;
      }
    }
  }
}

//

void insertion_sort(int* a, int n, int* p_noi)
{
  *p_noi = 0;
  for (int j = 1; j < n; j++) {
    int x = a[j];
    int i = j - 1;
    while (i >= 0 && a[i] > x) {
      a[i + 1] = a[i];
      i--;
      (*p_noi)++;
    }
    a[i + 1] = x;
  }
}

//

void _merge(int* a, int* a1, int* a2, int i, int mid, int j, int* p_noi)
{
  memcpy(a1 + i, a + i, (mid - i + 1) * sizeof(int));
  memcpy(a2 + mid + 1, a + mid + 1, (j - mid) * sizeof(int));
  int k = i, i1 = i, i2 = mid + 1;
  while (k <= j) {
    if (i2 > j || (i1 <= mid && a1[i1] <= a2[i2])) {
      a[k++] = a1[i1++];
    } else {
      a[k++] = a2[i2++];
      *p_noi += mid - i1 + 1;
    }
  }
}

//

void _merge_sort(int* a, int* a1, int* a2, int i, int j, int* p_noi)
{
  if (i == j) {
    return;
  }
  int mid = i + (j - i) / 2;
  _merge_sort(a, a1, a2, i, mid, p_noi);
  _merge_sort(a, a1, a2, mid + 1, j, p_noi);
  _merge(a, a1, a2, i, mid, j, p_noi);
}

//

void merge_sort(int* a, int n, int* p_noi)
{
  int* a1 = (int*)malloc(n * sizeof(int));
  int* a2 = (int*)malloc(n * sizeof(int));
  *p_noi = 0;
  _merge_sort(a, a1, a2, 0, n - 1, p_noi);
  free(a1);
  free(a2);
}

//
///
//

int main()
{
  int a[] = {5, 2, 4, 6, 1, 3};
  int n = 6;
  int noi;
  //bubble_sort(a, n, &noi);
  //insertion_sort(a, n, &noi);
  merge_sort(a, n, &noi);
  for (int i = 0; i < n; i++) {
    printf("%d\n", a[i]);
  }
  printf("-\n%d\n", noi);
}

//
///
////
///
//

