#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(time(NULL));
  printf("134\n");
  for(int i = 1; i <= 134; ++i) {
    int pos = rand() % 5 + 1;
    printf("\"SASADADS%d\" %d %d\n", i, i, pos);
  }
  return 0;
}