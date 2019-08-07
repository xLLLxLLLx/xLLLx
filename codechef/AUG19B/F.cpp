#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10, mod = 1e9 + 7;
int qx[N];
ll dp[N];

void dfs(int len, int lmt) {
	if(!lmt && ~dp[len]) 
		return dp[len];
	ll sum = 0;
	int up = lmt ? qx[len] : 9;
	for(int i = 0; i < up; ++i) {
		sum += dfs(len - 1, lmt && (i == up));
	} 
	if(lmt) return sum;
	else return dp[len] = sum;
}

int main() {

	return 0;
}