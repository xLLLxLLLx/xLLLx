#include <bits/stdc++.h>
using namespace std;

int main() {
  system("g++ -g B.cpp -o my");
  system("g++ -g std.cpp -o std");
  system("g++ -g gen.cpp -o gen");
  for(int o = 1; ; ++o) {
    system("./gen > out");
    system("./std < out > uu");
    system("./my < out > oo");
    if(system("diff oo uu")) {
      puts("WAI!");
      exit(0);
    } else {
      printf("test %d: pass!\n", o);
    }
  }
  return 0;
}