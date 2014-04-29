//
// Chapter 15. Dynamic Programming
//
// Implementation of CUT-ROD in page 360~370
//
// Hao Wu, 04/29/2014
//

#include <stdio.h>
#include <stdlib.h> // malloc() and free()

//
///
//

void cut_rod(int n, int* p, int* r, int* s)
{
  for (int i = 1; i <= n; i++) {
    int r_opt = (i <= n) ? p[i] : 0;
    int s_opt = 0;
    for (int j = 1; j <= n && j < i; j++) {
      int rij = p[j] + r[i - j];
      if (r_opt < rij) {
        r_opt = rij;
        s_opt = j;
      }
    }
    r[i] = r_opt;
    s[i] = s_opt;
  }
}

//
///
//

int main()
{
  int n = 9;
  int p[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
  int* r = (int*)malloc((n + 1) * sizeof(int));
  int* s = (int*)malloc((n + 1) * sizeof(int));
  cut_rod(n, p, r, s);
  printf("r[%d] = %d\n", n, r[n]);
  int i = n;
  while (true) {
    int j = s[i];
    if (j > 0) {
      printf("%d\n", j);
    } else {
      printf("%d\n", i - j);
      break;
    }
    i -= j;
  }
}

//
///
////
///
//

