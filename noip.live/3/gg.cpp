#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
 
using namespace std;
 
double dp[42][52][52][52];
 
double sum[52][52][52]; // R,G,B
 
int maxR, maxG, maxB;
 
int is(int l, int r, int L, int R) {
  l = max(l, L), r = min(r, R);
  if (l <= r)
    return r - l + 1;
  else
    return 0;
}
 
int count(int r, int g, int b, int d) {
  int ret = is(0, maxR - 1, r - d, r + d);
  ret *= is(0, maxG - 1, g - d, g + d);
  ret *= is(0, maxB - 1, b - d, b + d);
  return ret;
}
 
double calc(int l1, int r1, int l2, int r2, int l3, int r3) { //r,g,b
  double ret = 0;
 
  int MAX[] = { maxR, maxG, maxB };
  int L[] = { l1, l2, l3 }, R[] = { r1, r2, r3 };
 
  for (int i = 0; i < 3; ++i) {
    L[i] = max(L[i], 0);
    R[i] = min(R[i], MAX[i] - 1);
    if (L[i] > R[i])
      return 0;
  }
 
  for (int mask = 0; mask < 8; ++mask) {
    int w[3], sign = 1;
    for (int i = 0; i < 3; ++i) {
      if (mask >> i & 1) {
        w[i] = R[i];
      } else {
        w[i] = L[i] - 1;
        sign *= -1;
      }
    }
    if (w[0] >= 0 && w[1] >= 0 && w[2] >= 0)
      ret += sum[w[0]][w[1]][w[2]] * sign;
  }
 
  return ret;
}
 

double getProbability(int N, int maxR, int maxG, int maxB, int startR, int startG, int startB, int d1, int d2) {
    memset(dp, 0, sizeof dp);
    ::maxR = maxR, ::maxB = maxB, ::maxG = maxG;

    dp[0][startR][startG][startB] = 1;

    --d1;

    for (int i = 0; i < N; ++i) {

        if (i + 1 < N) {
        for (int r = 0; r < maxR; ++r) {
            for (int g = 0; g < maxG; ++g) {
            for (int b = 0; b < maxB; ++b) {
                int cnt = count(r, g, b, d2) - count(r, g, b, d1);
                // printf("%d %d %d %d %lf\n", r + 1, g + 1, b + 1, cnt, dp[i][r][g][b]);
                if (cnt > 0)
                dp[i][r][g][b] /= cnt;
                else
                dp[i][r][g][b] = 0;
              if(dp[i][r][g][b]) {
                printf("dp[%d][%d][%d][%d]=%lf\n", i + 1, r + 1, g + 1, b + 1, dp[i][r][g][b]);
              }
            }
            }
        }
        }

        //make sum

        for (int r = 0; r < maxR; ++r) {
        for (int g = 0; g < maxG; ++g) {
            for (int b = 0; b < maxB; ++b) {
            sum[r][g][b] = dp[i][r][g][b];
            for (int mask = 1; mask < 8; ++mask) {
                int nr = r, ng = g, nb = b, sign = -1;
                if (mask & 1)
                --nr, sign *= -1;
                if (mask & 2)
                --ng, sign *= -1;
                if (mask & 4)
                --nb, sign *= -1;
                if (nr >= 0 && ng >= 0 && nb >= 0)
                sum[r][g][b] += sign * sum[nr][ng][nb];
            }
            }
        }
        }

        //calc next
        for (int r = 0; r < maxR; ++r) {
        for (int g = 0; g < maxG; ++g) {
            for (int b = 0; b < maxB; ++b) {
            dp[i + 1][r][g][b] = calc(r - d2, r + d2, g - d2, g + d2, b - d2, b + d2) - calc(r - d1, r + d1, g - d1, g + d1, b - d1, b + d1);
            if(i + 1 == N) {
              if(dp[i + 1][r][g][b]) {
                printf("dp[%d][%d][%d][%d]=%lf\n", i + 2, r + 1, g + 1, b + 1, dp[i + 1][r][g][b]); 
              }
            }
            }
        }
        }
    }

    return 1 - dp[N][startR][startG][startB];
}


int main() {
    vector <int> v(9);
    for (int i = 0; i < 9; i++) {
        cin >> v[i];
    }
    printf("%.8f\n", getProbability(v[0], v[1], v[2], v[3], v[4], v[5],v[6],v[7], v[8]));
    return 0;
}