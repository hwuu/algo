//
// Chapter 09. Medians and Order Statistics
//
// Implementation of SELECT on page 220
//
// Hao Wu, 04/23/2014
//

#include <stdio.h>
#include <stdlib.h> // malloc() and free()

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

void _partition(int* a, int i, int j, int x, int* p_ip)
{
  while (true) {
    while (i <= j && a[i] < x) {
      i++;
    }
    while (i <= j && a[j] > x) {
      j--;
    }
    if (i >= j) {
      break;
    }
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
  }
  *p_ip = j;
}

//

int _get_median_by_sorting(int* a, int i, int j)
{
  insertion_sort(a + i, j - i + 1);
  return a[i + (j - i) / 2];
}

//

int select(int* a, int n, int k)
{
  if (n == 1) {
    return a[0];
  }
  int ng = (n + 4) / 5;
  int* b = (int*)malloc(ng * sizeof(int));
  for (int g = 0; g < ng; g++) {
    int i = g * 5;
    int j = (g == ng - 1) ? n - 1 : i + 4;
    int m = _get_median_by_sorting(a, i, j);
    b[g] = m;
    printf("%d %d %d\n", i, j, m);
  }
  int mm = select(b, ng, (ng - 1) / 2);
  printf("mm = %d\n", mm);
  int ip;
  _partition(a, 0, n - 1, mm, &ip);
  printf("ip = %d\n", ip);
  int r = 0;
  if (ip == k) {
    r = mm;
  } else if (ip > k) {
    printf("******** Case 1: %d, %d, %d\n", 0, ip, k);
    r = select(a, ip, k);
  } else if (ip < k) {
    printf("******** Case 2: %d, %d, %d\n", ip + 1, n - ip - 1, k - ip - 1);
    r = select(a + ip + 1, n - ip - 1, k - ip - 1);
  }
  free(b);
  return r;
}

//
///
//

int main()
{
  int a[] = {5, 2, 4, 6, 1, 3};
  int n = 6;
  int r = select(a, n, 5);
  printf("r = %d\n", r);
}

//
///
////
///
//

