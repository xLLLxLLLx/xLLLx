#include <bits/stdc++.h>
using namespace std;

int main() {
  for(int o = 1; ; ++o) {
    system("./gen > out");
    system("./my < out > oo");
    system("./std < out > uu");
    if(system("diff oo uu")) {
      puts("WAI!!");
      return 0;
    } else {
      printf("test %d: pass!\n", o);
    }
  }
  return 0;
}