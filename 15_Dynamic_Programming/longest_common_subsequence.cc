//
// Chapter 15. Dynamic Programming
//
// Solution to the longest common subsequence problem in page 390~396
//
// Hao Wu, 04/29/2014
//

#include <stdio.h>
#include <stdlib.h> // malloc() and free()
#include <string.h>

//
///
//

int lcs(const char* s1, const char* s2)
{
  int l1 = strlen(s1);
  int l2 = strlen(s2);
  int* m = (int*)malloc((l1 + 1) * (l2 + 1) * sizeof(int));
  for (int i = 0; i <= l1; i++) {
    for (int j = 0; j <= l2; j++) {
      if (i == 0 || j == 0) {
        *(m + (l2 + 1) * i + j) = 0;
        continue;
      }
      if (s1[i - 1] == s2[j - 1]) {
        *(m + (l2 + 1) * i + j) = *(m + (l2 + 1) * (i - 1) + (j - 1)) + 1;
      } else {
        int c1 = *(m + (l2 + 1) * (i - 1) + j);
        int c2 = *(m + (l2 + 1) * i + (j - 1));
        *(m + (l2 + 1) * i + j) = c1 > c2 ? c1 : c2;
      }
    }
  }
  int result = *(m + (l2 + 1) * l1 + l2);
  free(m);
  return result;
}

//
///
//

int main()
{
  char s1[] = "abcde";
  char s2[] = "ace";
  printf("%d\n", lcs(s1, s2));
}

//
///
////
///
//

