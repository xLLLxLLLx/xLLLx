#include <bits/stdc++.h>
using namespace std;

#define N 1100000

int n;
long long k;
long long p[1100];

long long dp[1 << 12][13];
long long dp1[1 << 12][13];
long long ff[1 << 12];
int used[1 << 12];

int len;

long long a[N];
long long b[N];
long long mul[N];

int tx[N];
int e[N];

unordered_map <long long, int> app;

bool cmp(int x, int y) {
	return e[x] < e[y];
}

long long gcd(long long x, long long y) {
	if (!x)
		return y;
	return gcd(y % x, x);
}

void conv(int mask, int e) {
	for (int i = len - 1; i >= 0; i--)
		for (int j = 0; j < (1 << len); j++)
			dp[j | mask][i + 1] = min(dp[j | mask][i + 1], dp1[j][i] + e);
}

int main() {
	scanf("%d%lld", &n, &k);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for (int i = 1; i <= n; i++)
		scanf("%d", &e[i]);
	long long GCD = 0;
	for (int i = 1; i <= n; i++)
		GCD = gcd(GCD, a[i]);
	for (long long ll = 2; ll * ll <= GCD; ll++)
		if (GCD % ll == 0) {
			p[len] = ll;
			len++;
			while (GCD % ll == 0)
				GCD /= ll;
		}
	if (GCD > 1)
		p[len++] = GCD;

	if (len == 0) {
		printf("0\n");
		return 0;
	}
	for (int i = 1; i <= n; i++) {
		b[i] = 1;
		for (int j = 0; j < len; j++) {
			while (a[i] % p[j] == 0) {
				b[i] *= p[j];
				a[i] /= p[j];
			}
		}
	}

	for (int i = 1; i <= n; i++)
		tx[i] = i;
	sort(tx + 1, tx + n + 1, cmp);

	// sort(b + 1, b + n + 1, cmp);

	for (int i = 0; i < (1 << len); i++)
		for (int j = 0; j <= len; j++)
			dp[i][j] = 1e16;

	dp[0][0] = 0;

	for (int i = 1; i <= n; i++) {

		app[b[tx[i]]]++;
		if (app[b[tx[i]]] > len)
			continue;

		for (int j = 0; j < len; j++) {
			mul[j] = 1;
			while (b[tx[i]] % p[j] == 0)
				mul[j] *= p[j], b[tx[i]] /= p[j];
		}


		bool FIRST = false;

		ff[0] = 1;
		for (int high = 0; high < len; high++) {
			for (int j = (1 << high); j < (1 << (high + 1)); j++) {
				ff[j] = ff[j - (1 << high)] * mul[high];
				if (ff[j] <= k && used[j] < len) {
					if (!FIRST) {
						memcpy(dp1, dp, sizeof dp);
						FIRST = true;
					}
					// printf("%d %d %lld %d\n", high, j, ff[j], e[tx[i]]);
					conv(j, e[tx[i]]);
					used[j]++;
				}
			}
		}
	}

	long long ans = 1e18;
	for (int i = 1; i <= len; i++)
		ans = min(ans, 1LL * i * dp[(1 << len) - 1][i]);
	if (ans < 1e15)
		printf("%lld\n", ans);
	else
		printf("-1\n");
}