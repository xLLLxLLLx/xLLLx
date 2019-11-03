#include <bits/stdc++.h>
using namespace std;
const int N = 1010, M = 30;
char s[N], t[N];
int ch[M][M], a[M][M], vs[N], vt[N];

void init() {
  for(int i = 0; i < 26; ++i) {
    for(int j = 0; j < 26; ++j) {
      ch[i][j] = (i + j) % 26;
      // printf("%c", char(ch[i][j] + 'a'));
    }
    // puts("");
  }
  for(int i = 0; i < 26; ++i)
    for(int j = 0; j < 26; ++j) {
      a[ch[i][j]][j] = i;
    }
}

int main() {
  init();
  scanf("%s%s", s, t);
  int ls = strlen(s), lt = strlen(t);
  for(int i = 0; i < ls; ++i) {
    if(s[i] >= 'A' && s[i] <= 'Z') vs[i] = s[i] - 'A';
    else vs[i] = s[i] - 'a';
  }
  for(int i = 0; i < lt; ++i) {
    if(t[i] >= 'A' && t[i] <= 'Z') vt[i] = t[i] - 'A';
    else vt[i] = t[i] - 'a';
  }
  for(int i = 0; i < lt; ++i) {
    int j = i % ls;
    if(t[i] >= 'A' && t[i] <= 'Z') printf("%c", char(a[vt[i]][vs[j]] + 'A'));
    else printf("%c", char(a[vt[i]][vs[j]] + 'a'));
  }
  puts("");
  return 0;
}