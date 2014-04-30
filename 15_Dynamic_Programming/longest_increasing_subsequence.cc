//
// Chapter 15. Dynamic Programming
//
// Solution to the longest increasing subsequence problem in page 397
//
// Hao Wu, 04/30/2014
//

#include <stdio.h>
#include <stdlib.h> // malloc() and free()

//
///
//

int lis(int n, int* a)
{
  int* m = (int*)malloc(n * sizeof(int));
  m[0] = 1;
  for (int j = 1; j < n; j++) {
    int c_opt = 1;
    for (int i = 0; i < j; i++) {
      int c = a[j] > a[i] ? m[i] + 1 : 1;
      if (c_opt < c) {
        c_opt = c;
      }
    }
    m[j] = c_opt;
  }
  int result = m[n - 1];
  //for (int i = 0; i < n; i++) {
  //  printf("m[%d] = %d\n", i, m[i]);
  //}
  free(m);
  return result;
}

//
///
//

int main()
{
  int n = 7;
  int a[] = {1, 7, 3, 5, 9, 4, 8};
  printf("%d\n", lis(n, a));
}

//
///
////
///
//

