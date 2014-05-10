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

int main()
{
  int n = 7;
  int a[] = {1, 2, 3, 5, 6, 8, 10};
  int k;
  int z_x[] = {1, 2, 3, 4, 5, 6, 7, 0, 12};
  for (int i = 0; i < sizeof(z_x) / sizeof(int); i++) {
    int x = z_x[i];
    binary_search_with_best_effort(a, 0, n - 1, x, &k);
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

