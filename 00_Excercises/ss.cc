//
// String Search Algorithms
// 
// Ref: http://goo.gl/eurPL5 (TopCoder)
//
// Hao Wu, 09/25/2014
//

#include <stdio.h>
#include <stdlib.h> // malloc() and free()
#include <string.h> // strlen()

//
// Naive method. O(m^2)
//

int Naive(const char* s, const char* p)
{
  int m = strlen(s);
  int n = strlen(p);
  for (int i = 0; i <= m - n; i++) {
    bool succ = true;
    for (int j = 0; j < n; j++) {
      //printf("%d %d %c %c\n", i, j, s[i + j], p[j]);
      if (s[i + j] != p[j]) {
        succ = false;
        break;
      }
    }
    if (succ) {
      return i;
    }
  }
  return -1;
}

//
// KMP. O(m + n)
//

/**
 *
 * Build failure function (state transition array).
 *
 * Example 1: bababbac
 *
 *  0  1  2  3  4  5  6  7    j   f[j]
 * ------------------------------------
 *  b  a  b  a  b  b  a  c    0      0
 *  b  a  b  a  b  b  a  c    1      0
 *  b  a  b  a  b  b  a  c    2      0
 * (b) a [b] a  b  b  a  c    3      1
 * (b  a)[b  a] b  b  a  c    4      2
 * (b  a [b) a  b] b  a  c    5      3
 * (b) a  b  a  b [b] a  c    6      1
 * (b  a) b  a  b [b  a] c    7      2
 *
 * Example 2: abaababc
 *
 *  0  1  2  3  4  5  6  7    j   f[j]
 * ------------------------------------
 * ...
 * (a) b [a] a  b  a  b  c    3      1
 * (a) b  a [a] b  a  b  c    4      1 // go to i == 1
 * ...
 * (a  b  a)[a  b  a] b  c    6      3
 * (a  b) a  a  b [a  b] c    7      2 // go to i == 3
 *
**/
void KMP_Build(const char* p, int* f)
{
  int n = strlen(p);
  for (int j = 0; j < n; j++) {
    if (j <= 1) {
      f[j] = 0;
      continue;
    }
    int i = f[j - 1];
    while (true) {
      if (p[i] == p[j - 1]) {
        f[j] = i + 1;
        break;
      }
      if (i == 0) {
        f[j] = 0;
        break;
      }
      i = f[i];
    }
  }
}

//

int KMP_Search(const char* s, const char* p, const int* f)
{
  int m = strlen(s);
  int n = strlen(p);
  int i = 0, j = 0;
  while (i < m) {
    //printf("%d %d\n", i, j);
    if (s[i] == p[j]) {
      if (j == n - 1) {
        return i - n + 1;
      }
      i++;
      j++;
    } else if (j > 0) {
      j = f[j];
    } else {
      i++;
    }
  }
  return -1;
}

//
///
//

int RabinKarp(const char* s, const char* p)
{
  int m = strlen(s);
  int n = strlen(p);
  if (m < n) {
    return -1;
  }
  const int B = 257;
  const int M = 997;
  int hs = 0, hp = 0, b = 1;
  for (int i = 0; i < n; i++) {
    hs = (hs * B + (int)s[i]) % M;
    hp = (hp * B + (int)p[i]) % M;
    if (i < n - 1) {
      b  = (b * B) % M;
    }
  }
  for (int i = 0; i <= m - n; i++) {
    if (i > 0) {
      int x = (s[i - 1] * b) % M;
      hs = ((hs - x) * B + s[i + n - 1]) % M;
      hs = (hs + M) % M;
    }
    //printf("%d: %d %d\n", i, hs, hp);
    if (hs == hp) {
      return i;
    }
  }
  return -1;
}

//
///
//

int main()
{
  char s[] = "abcababac";
  char p[] = "ababac";
  //char s[] = "babac";
  //char p[] = "bac";
  //char s[] = "aab";
  //char p[] = "ab";
  //
  //char p[] = "bababbac";
  //char p[] = "abaababc";
  //
  // Naive method
  //
  printf("%d\n", Naive(s, p));
  //
  // Rabin-Karp method
  //
  printf("%d\n", RabinKarp(s, p));
  //
  // KMP method
  //
  int n = strlen(p);
  int* f = (int*)malloc(n * sizeof(int));
  KMP_Build(p, f);
  printf("%d\n", KMP_Search(s, p, f));
  free(f);
  //
  ///
  //
  return 0;
}

//
///
////
///
//

