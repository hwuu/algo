//
// Chapter 02. Getting Started
//
// Bubble Sort
//
// Hao Wu, 04/17/2014
//

#include <stdio.h>

//
///
//

void bubble_sort(int* a, int n)
{
  for (int i = n - 1; i >= 1; i--) {
    for (int j = 0; j < i; j++) {
      if (a[j] > a[j + 1]) {
        int x = a[j];
        a[j] = a[j + 1];
        a[j + 1] = x;
      }
    }
  }
}

//
///
//

int main()
{
  int a[] = {5, 2, 4, 6, 1, 3};
  int n = 6;
  bubble_sort(a, n);
  for (int i = 0; i < n; i++) {
    printf("%d\n", a[i]);
  }
}

//
///
////
///
//

