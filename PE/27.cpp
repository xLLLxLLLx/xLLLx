#include <bits/stdc++.h>
using namespace std;
const int N = 1e7 + 1, M = 1e6 + 1;
bool flg[N];
int pr[M];
int A, B, ans = 0, kk = 0;

void init() {
  for(int i = 2; i < N; ++i) {
    if(!flg[i]) pr[++pr[0]] = i;
    for(int j = 1; j <= pr[0]; ++j) {
      if(i * pr[j] >= N) break;
      flg[i * pr[j]] = 1;
      if(i % pr[j] == 0) break;
    }
  }
}

int main() {
  init();
  for(int i = -999; i < 1000; ++i) {
    for(int j = 0; j < 1000; ++j) {
      A = i, B = j;
      for(int k = 0; ; ++k) {
        int pos = k * k + k * A + B;
        if(pos <= 0 || flg[pos]) {
          if(ans < k) {
            ans = k - 1;
            kk = A * B;
            if(ans == 70) {
              printf("%d %d\n", A, B);
            }
          }
          break;
        }
      }
    }
  }
  printf("%d %d\n", ans, kk);
  return 0;
}