//
// Chapter 09. Medians and Order Statistics
//
// Implementation of RANDOMIZED-SELECT on page 215
// Iterative version on page 219
//
// Hao Wu, 04/23/2014
//

#include <stdio.h>
#include <stdlib.h> // srand() and rand()
#include <time.h>   // time()

//
///
//

typedef unsigned int uint;

//
///
//

uint rand(uint n)
{
  uint x = 0;
  for (uint i = 0; i < n; i++) {
    x += (rand() % 2) << i;
  }
  return x;
}

//

uint rand(uint lb, uint ub)
{
  if (lb == 0 && ub + 1 == 0) {
    return rand(sizeof(uint) * 8);
  }
  uint L = ub - lb;
  uint n = 0;
  while ((L >> n) > 0) {
    n++;
  }
  while (true) {
    uint x = rand(n);
    if (x <= L) {
      return lb + x;
    }
  }
}

//
///
//

void _randomized_partition(int* a, int i, int j, int* p_ip)
{
  int i0 = i;
  int ir = rand(i, j);
  int x = a[ir];
  a[ir] = a[i0];
  a[i0] = x;
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
  *p_ip = j;
}

//

void _randomized_select_iterative(int* a, int i, int j, int k, int* p_x)
{
  printf("i = %d, j = %d, k = %d\n", i, j, k);
  while (i < j) {
    printf("******** i = %d, j = %d, k = %d\n", i, j, k);
    int ip;
    _randomized_partition(a, i, j, &ip);
    int m = ip - i;
    printf("******** ip = %d, m = %d\n", ip, m);
    printf("******** -\n");
    for (int ii = i; ii <= j; ii++) {
      printf("******** %d\n", a[ii]);
    }
    printf("******** -\n");
    if (m == k) {
      i = ip;
      break;
    } else if (m > k) {
      j = ip - 1;
    } else if (m < k) {
      i = ip + 1;
      k = k - m - 1;
    }
  }
  *p_x = a[i];
}

//

void randomized_select_iterative(int* a, int n, int k, int* p_x)
{
  _randomized_select_iterative(a, 0, n - 1, k, p_x);
}

//
///
//

int main()
{
  srand(time(0));
  //
  int a[] = {5, 2, 4, 6, 1, 3};
  int n = 6;
  int x;
  randomized_select_iterative(a, n, 3, &x);
  printf("%d\n", x);
}

//
///
////
///
//

