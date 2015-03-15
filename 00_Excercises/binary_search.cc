//
// Implementation of the Binary Search Algorithm
//
// Hao Wu, 05/04/2014
//

#include <stdio.h>

//
///
//

void binary_search(int* a, int i, int j, int x, int* p_k)
{
  *p_k = -1;
  while (i <= j) {
    int k = i + ((j - i) >> 1);
    if (a[k] == x) {
      *p_k = k;
      break;
    } else if (a[k] < x) {
      i = k + 1;
    } else if (a[k] > x) {
      j = k - 1;
    }
  }
}

//
///
//

void binary_search_with_best_effort(int* a, int i, int j, int x, int* p_k)
{
  while (i <= j) {
    int k = i + ((j - i) >> 1);
    if (a[k] == x) {
      *p_k = k;
      break;
    } else if (a[k] < x) {
      *p_k = k;
      i = k + 1;
    } else if (a[k] > x) {
      *p_k = k - 1;
      j = k - 1;
    }
  }
}

//
///
//

void binary_search_for_the_first(int* a, int i, int j, int x, int* p_k)
{
  while (i <= j) {
    int k = i + ((j - i) >> 1);
    if (a[k] == x) {
      if (k > 0 && a[k - 1] == x) {
        j = k - 1;
      } else {
        *p_k = k;
        break;
      }
    } else if (a[k] < x) {
      *p_k = k;
      i = k + 1;
    } else if (a[k] > x) {
      *p_k = k - 1;
      j = k - 1;
    }
  }
}

//
///
//

int main()
{
  //int a[] = {1, 2, 3, 3, 3, 5, 6, 6, 6, 6, 8, 10, 10};
  int a[] = {3, 3, 3, 3, 3, 3};
  int n = sizeof(a) / sizeof(int);
  int z_x[] = {1, 2, 3, 4, 5, 6, 7, 0, 12};
  for (int i = 0; i < sizeof(z_x) / sizeof(int); i++) {
    int x = z_x[i];
    int k;
    //binary_search_with_best_effort(a, 0, n - 1, x, &k);
    binary_search_for_the_first(a, 0, n - 1, x, &k);
    printf("Search for %d: %d\n", x, k);
  }
}

//
///
////
///
//
//
///
////
///
//
//
///
////
///
//
//
///
////
///
//

