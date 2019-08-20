#include <bits/stdc++.h>
using namespace std;
const int N = 2010, M = 1e5 + 10;
int nm[M], a[N];
char lx[N];

void down(int a[], int x) {
	a[1] -= x;
	for(int i = 1; i <= a[0]; ++i) {
		// printf("%d\n", a[i]);
		if(a[i] < 0) {
			a[i + 1]--;
			a[i] += 10;
		}
	}
	while(a[0] > 1 && !a[a[0]]) --a[0];
}

int b[N];

void cut() {
	b[0] = a[0];
	for(int i = a[0]; i >= 1; --i) {
		b[i] = a[i] / 2;
		a[i - 1] += (a[i] & 1) * 10;
	}
	while(b[0] > 1 && !b[b[0]]) --b[0];
}

int gcd(int A, int B) {
	return B ? gcd(B, A % B) : A;
}

int main() {
	freopen("china.in", "r", stdin);
	freopen("china.out", "w", stdout);
	scanf("%s", lx + 1);
	int len = strlen(lx + 1);
	if(len <= 7) {
		int pos = 0, ans = 1;
		for(int i = 1; i <= len; ++i) {
			pos = pos * 10 + (lx[i] - '0');
		}
		for(int i = pos / 2; i >= 1; --i) {
			if(gcd(pos, i) == 1) {
				ans = i;
				break;
			}
		}
		printf("%d\n", ans);
	} else {
		int pos = lx[len] - '0';
		for(int i = len; i >= 1; --i) {
			a[len - i + 1] = lx[i] - '0';
		}
		a[0] = len;
		if(pos & 1) {
			a[1]--;
			cut();
			for(int i = b[0]; i >= 1; --i)
				printf("%d", b[i]);
			puts("");
		} else {
			down(a, 2), cut();
			if(b[1] % 2 == 0) down(b, 1);
			for(int i = b[0]; i >= 1; --i)
				printf("%d", b[i]);
			puts("");
		}
	}
	return 0;
}