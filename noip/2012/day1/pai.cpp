#include <bits/stdc++.h>
using namespace std;

int main() {
  for(int o = 1; ; ++o) {
    system("./gen > out");
    system("./B < out > oo");
    system("./tB < out > uu");
    if(system("diff oo uu")) {
      puts("WAI!");
      exit(0);
    } else {
      printf("test %d: pass!\n", o);
    }
  }
  return 0;
}