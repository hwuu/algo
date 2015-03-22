//
// Chapter 15. Dynamic Programming
//
// Problem 15-2: Longest palindrome subsequence on page 405
//
// Hao Wu, 03/22/2015
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
///
//

/**
 * Substring expansion. O(n^2) time, O(1) space.
 *
 * Expand from two kinds of substrings:
 *   1) s[i..i]
 *   2) s[i..(i + 1)]
 *
 */
void lps_0(const char* s, int* p_i, int* p_n)
{
  const int N = strlen(s);
  *p_n = 0;
  for (int i = 0; i < N; i++) {
    for (int d = 0; d <= 1; d++) {
      if (i + d >= N || s[i] != s[i + d]) {
        continue;
      }
      for (int r = 1; r < N; r++) {
        if (i - r < 0 || i + d + r >= N ||
            s[i - r] != s[i + d + r]) {
          break;
        }
        if (*p_n < 2 * r + 1) {
          *p_i = i - r;
          *p_n = 2 * r + 1;
        }
      }
    }
  }
}

//
///
//

/**
 * Dynamic programming. O(n^2) time, O(n) space.
 *
 * f[n][i] = n == 1 ||
 *           n == 2 && s[i] == s[i + n - 1] ||
 *           s[i] == s[i + n - 1] && f[n - 2][i + 1]
 */
void lps_1(const char* s, int* p_i, int* p_n)
{
  const int N = strlen(s);
  bool* f = (bool*)malloc(3 * N * sizeof(bool));
  for (int i = 0; i < 3 * N; i++) {
    f[i] = false;
  }
  //
  *p_n = 0;
  for (int n = 1; n <= N; n++) {
    for (int i = 0; i <= N - n; i++) {
      f[(n % 3) * N + i] =
          (n == 1) ||
          (n == 2 && s[i] == s[i + n - 1]) ||
          (s[i] == s[i + n - 1] && f[((n + 1) % 3) * N + (i + 1)]);
      if (f[(n % 3) * N + i] == true && *p_n < n) {
        *p_i = i;
        *p_n = n;
      }
    }
  }
  //
  free(f);
}

//
///
//

/**
 * Dynamic programming. O(n^2) time, O(n^2) space.
 *
 * f[n][i] = n == 1 ||
 *           n == 2 && s[i] == s[i + n - 1] ||
 *           s[i] == s[i + n - 1] && f[n - 2][i + 1]
 
 */
void lps_2(const char* s, int* p_i, int* p_n)
{
  const int N = strlen(s);
  bool* f = (bool*)malloc((N + 1) * N * sizeof(bool));
  for (int i = 0; i < (N + 1) * N; i++) {
    f[i] = false;
  }
  //
  *p_n = 0;
  for (int n = 1; n <= N; n++) {
    for (int i = 0; i <= N - n; i++) {
      f[n * N + i] =
          (n == 1) ||
          (n == 2 && s[i] == s[i + n - 1]) ||
          (s[i] == s[i + n - 1] && f[(n - 2) * N + (i + 1)]);
      if (f[n * N + i] == true && *p_n < n) {
        *p_i = i;
        *p_n = n;
      }
    }
  }
  //
  free(f);
}

//
///
//

int main()
{
  const char* s = "sbananas";
  int i, n;
  lps_0(s, &i, &n);
  printf("%d %d\n", i, n);
  lps_1(s, &i, &n);
  printf("%d %d\n", i, n);
  lps_2(s, &i, &n);
  printf("%d %d\n", i, n);
}

//
///
////
///
//

