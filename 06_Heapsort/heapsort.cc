//
// Chapter 06. Heapsort
//
// Heap construction, maintenance, and heapsort.
//
// Hao Wu, 04/21/2014
//

#include <stdio.h>

//
///
//

void heap_push(int* h, int n, int x)
{
  int i = n;
  while (true) {
    int j = (i - 1) / 2;
    if (i == 0 || h[j] <= x) {
      break;
    }
    h[i] = h[j];
    i = j;
  }
  h[i] = x;
}

//

void heap_pop(int* h, int n)
{
  if (n == 0) {
    return;
  }
  int x = h[n - 1];
  int i = 0;
  while (true) {
    int j = 2 * i + 1;
    if (j >= n) {
      break;
    }
    if (j + 1 < n && h[j] > h[j + 1]) {
      j++;
    }
    if (x <= h[j]) {
      break;
    }
    h[i] = h[j];
    i = j;
  }
  h[i] = x;
}

//

void heap_make(int* a, int n)
{
  for (int i = 0; i < n; i++) {
    int x = a[i];
    heap_push(a, i, x);
  }
}

//
///
//

void heapsort(int* a, int n)
{
  heap_make(a, n);
  for (int i = 0; i < n; i++) {
    int x = a[0];
    heap_pop(a, n - i);
    a[n - i - 1] = x;
  }
}

//
///
//

int main()
{
  //int a[] = {5, 2, 4, 6, 1, 3};
  //int n = 6;
  int a[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7,
             12, -5, -22, 15, -4, 7};
  int n = 16;
  heapsort(a, n);
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

