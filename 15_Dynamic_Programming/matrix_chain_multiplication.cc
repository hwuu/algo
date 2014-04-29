//
// Chapter 15. Dynamic Programming
//
// Implementation of MATRIX-CHAIN-MULTIPLICATION in page 370~378
//
// Hao Wu, 04/29/2014
//

#include <stdio.h>
#include <stdlib.h> // malloc() and free()

//
///
//

void mcm(int n, int* p, int* m, int* s)
{
  for (int l = 1; l <= n; l++) {
    for (int i = 0; i + l - 1 < n; i++) {
      int j = i + l - 1;
      int c_opt = 0;
      int k_opt = i;
      for (int k = i; k < j; k++) {
        int c = *(m + n * i + k) + *(m + n * (k + 1) + j) +
                p[i] * p[k + 1] * p[j + 1];
        if (k == i || c_opt > c) {
          c_opt = c;
          k_opt = k;
        }
      }
      *(m + n * i + j) = c_opt;
      *(s + n * i + j) = k_opt;
    }
  }
}

//
///
//

void dump(int n, int* s, int i, int j)
{
  if (i == j) {
    printf("[%d]", i);
  } else {
    printf("(");
    int k = *(s + n * i + j);
    dump(n, s, i, k);
    dump(n, s, k + 1, j);
    printf(")");
  }
}

//
///
//

int main()
{
  //int n = 3;
  //int p[] = {10, 100, 5, 50};
  int n = 6;
  int p[] = {30, 35, 15, 5, 10, 20, 25};
  int* m = (int*)malloc(n * n * sizeof(int));
  int* s = (int*)malloc(n * n * sizeof(int));
  mcm(n, p, m, s);
  printf("m[%d][%d] = %d\n", 0, n - 1, *(m + n * 0 + (n - 1)));
  dump(n, s, 0, n - 1);
  printf("\n");
  free(m);
  free(s);
}

//
///
////
///
//

