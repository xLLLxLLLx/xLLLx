#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
char lx[N][N];
int a[N][N];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int dd[3][4] = {
  {0, 1, 2, 3}, // F
  {1, 2, 3, 0}, // L
  {3, 0, 1, 2}  // R
};
char dc[3] = {'F', 'L', 'R'};

typedef pair<int, int> P;
queue<P> q;

int main() {
  freopen("straight.in", "r", stdin);
  freopen("straight.out", "w", stdout);
  int n, m;
  scanf("%d%d", &m, &n);
  for(;getchar() != '\n';) ;
  memset(lx, ' ', sizeof lx);
  for(int i = 2; i <= 2 * m; ++i) {
    fgets(lx[i] + 2, sizeof(lx[i]) - 2, stdin);
  }
  // puts("XXX");
  memset(a, -1, sizeof a);
  a[1][n] = 0;
  q.push(P(1, n));
  while(!q.empty()) {
    int x = q.front().first, y = q.front().second;
    for(int i = 0; i < 4; ++i) {
      int xx = x * 2 + dx[i];
      int yy = y * 2 + dy[i];
      if(lx[xx][yy] == '-' || lx[xx][yy] == '|') {
        xx += dx[i], yy += dy[i];
        if(a[xx / 2][yy / 2] == -1) {
          a[xx / 2][yy / 2] = a[x][y] + 1;
          q.push(P(xx / 2, yy / 2));
        }
      }
    }
    q.pop();
  }
  P p;
  // puts("XXX");
  int d;
  if(lx[2 * m - 1][2] == '|' && a[m - 1][1] == a[m][1] - 1) {
    puts("N");
    p = P(m - 1, 1);
    d = 2;
  } else if(lx[2 * m][3] == '-' && a[m][2] == a[m][1] - 1) {
    puts("E");
    p = P(m, 2);
    d = 1;
  } 
  for(;;) {
    int x = p.first, y = p.second;
    if(a[x][y] == 0) {
      puts("");
      break;
    }
    for(int k = 0; k < 3; ++k) {
      int xx = x * 2 + dx[dd[k][d]], yy = y * 2 + dy[dd[k][d]];
      if(lx[xx][yy] == '-' || lx[xx][yy] == '|') {
        xx += dx[dd[k][d]], yy += dy[dd[k][d]];
        if(a[xx / 2][yy / 2] == a[x][y] - 1) {
          p = P(xx / 2, yy / 2);
          d = dd[k][d];
          putchar(dc[k]);
          break;
        }
      }

    }
  }
  return 0;
}