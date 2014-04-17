//
// Chapter 02. Getting Started
//
// Insertion Sort
//
// Hao Wu, 04/16/2014
//

#include <stdio.h>

//
///
//

void insertion_sort(int* a, int n)
{
  for (int j = 1; j < n; j++) {
    int x = a[j];
    int i = j - 1;
    while (i >= 0 && a[i] > x) {
      a[i + 1] = a[i];
      i--;
    }
    a[i + 1] = x;
  }
}

//
///
//

int main()
{
  int a[] = {5, 2, 4, 6, 1, 3};
  int n = 6;
  insertion_sort(a, n);
  for (int i = 0; i < n; i++) {
    printf("%d\n", a[i]);
  }
}

//
///
////
///
//

