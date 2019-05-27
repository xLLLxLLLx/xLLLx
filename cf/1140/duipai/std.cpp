#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <deque>
#include <cmath>
#include <utility>
#include <algorithm>
#include <bitset>
#include <climits>
#include <random>
#include <chrono>
#include <cassert>

using namespace std;

typedef long long ll;

#define pii pair< int, int >
#define pll pair< ll, ll >
#define pli pair< ll, int >
#define N 300001
#define LOGN 19

vector< vector<int> > adj(N);
int edgeEndXors[N], depth[N], ancestors[LOGN][N];
ll weights[N][2], crossWeights[N], d[N], dp[LOGN][N][2][2], temp[2][2], a[2][2], b[2][2], c[2][2];

void PreProcess(int n){
  priority_queue< pli, vector< pli >, greater< pli > > Q;

  for(int i = 1; i <= n; ++i){
    d[i] = crossWeights[i];
    Q.push(make_pair(d[i], i));
  }

  while(!Q.empty()){
    ll di;
    int i;
    tie(di, i) = Q.top();
    Q.pop();

    if(di > d[i]){
      continue;
    }

    for(int x : adj[i]){
      int j = edgeEndXors[x] ^ i;
      ll dj = di + weights[x][0] + weights[x][1];
      if(dj < d[j]){
        d[j] = dj;
        Q.push(make_pair(dj, j));
      }
    }
  }
}

void Compute(ll a[2][2], ll b[2][2], ll c[2][2]){
  for(int i = 0; i < 2; ++i){
    for(int j = 0; j < 2; ++j){
      ll &val = temp[i][j];
      val = LLONG_MAX;
      for(int k = 0; k < 2; ++k){
        val = min(val, a[i][k] + b[k][j]);
      }
    }
  }

  for(int i = 0; i < 2; ++i){
    for(int j = 0; j < 2; ++j){
      c[i][j] = temp[i][j];
    }
  }
}

void DFS(int i, int p){
  depth[i] = 1 + depth[p];
  
  for(int k = 1; k < LOGN; ++k){
    int j = ancestors[k - 1][i];
    ancestors[k][i] = ancestors[k - 1][j];
    Compute(dp[k - 1][i], dp[k - 1][j], dp[k][i]);
  }

  for(int x : adj[i]){
    int j = edgeEndXors[x] ^ i;
    
    if(j == p){
      continue;
    }

    ancestors[0][j] = i;
    dp[0][j][0][0] = min(weights[x][0], d[j] + weights[x][1] + d[i]);
    dp[0][j][0][1] = min(d[i] + weights[x][0], d[j] + weights[x][1]);
    dp[0][j][1][0] = min(d[i] + weights[x][1], d[j] + weights[x][0]);
    dp[0][j][1][1] = min(weights[x][1], d[j] + weights[x][0] + d[i]);

    DFS(j, i);
  }
}

int LCA(int i, int j){
  if(depth[i] > depth[j]){
    swap(i, j);
  }

  for(int k = LOGN - 1, x = depth[j] - depth[i]; x; --k){
    if((1 << k) <= x){
      j = ancestors[k][j];
      x -= (1 << k);
    }
  }

  if(i == j){
    return i;
  }

  for(int k = LOGN - 1; ancestors[0][i] != ancestors[0][j]; --k){
    if(ancestors[k][i] != ancestors[k][j]){
      i = ancestors[k][i], j = ancestors[k][j];
    }
  }

  return ancestors[0][i];
}

void ComputeTillKthAncestors(int i, int l, ll a[2][2]){
  for(int x = 0; x < 2; ++x){
    for(int y = 0; y < 2; ++y){
      a[x][y] = 0;
    }
  }

  a[0][1] = a[1][0] = d[i];

  for(int k = LOGN - 1; k > -1 && l > 0; --k){
    if(l < (1 << k)){
      continue;
    }
    Compute(a, dp[k][i], a);
    i = ancestors[k][i];
    l -= (1 << k);
  }
}

ll Query(int i, int j){
  int pi = (i + 1) / 2, pj = (j + 1) / 2;
  int qi = (i + 1) % 2, qj = (j + 1) % 2;

  int pk = LCA(pi, pj);

  ComputeTillKthAncestors(pi, depth[pi] - depth[pk], a);
  ComputeTillKthAncestors(pj, depth[pj] - depth[pk], b);
  swap(b[0][1], b[1][0]);

  Compute(a, b, c);

  return c[qi][qj];
}

int main(){
  int n;
  scanf("%d", &n);

  for(int i = 1; i <= n; ++i){
    scanf("%lld", &crossWeights[i]);
  }

  for(int x = 1; x < n; ++x){
    int i, j;
    scanf("%d%d%lld%lld", &i, &j, &weights[x][0], &weights[x][1]);
    edgeEndXors[x] = (i ^ j);
    adj[i].push_back(x);
    adj[j].push_back(x);
  }

  PreProcess(n);
  DFS(1, 0);

  int q;
  scanf("%d", &q);
  while(q--){
    int i, j;
    scanf("%d%d", &i, &j);
    printf("%lld\n", Query(i, j));
  }

  return 0;
}