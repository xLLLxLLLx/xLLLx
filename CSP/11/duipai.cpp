#include <bits/stdc++.h>
using namespace std;

int main() {
  for(int o = 1; ; ++o) {
    system("./gen > out");
    system("./C < out > oo");
    system("./TT < out > uu");
    if(system("diff oo uu")) {
      puts("WAI!");
      exit(0);
    } else {
      printf("test %d: pass!\n", o);
    }
  }
}