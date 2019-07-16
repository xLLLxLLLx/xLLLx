#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int a[N], q1[N], q2[N], ys[N], ;

void fail() {
	printf("Fail\n");
	exit(0);
}

void out() {
	printf("%d\n", q1[0]);
	for(int i = 1; i <= q1[0]; ++i) {
		printf("%d ", q1[i]);
	}
	puts("");
	printf("%d\n", q2[0]);
	for(int i = 1; i <= q2[0]; ++i) {
		printf("%d\n", q2[i]);
	}
	exit(0);
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		ys[a[i]] = i;
	}

	//case1
	int flg = 1;
	for(int i = 1; i <= n; ++i) {
		if(!q1[0]&&!q2[0]) {
			q1[++q1[0]] = a[i];
		} else {
			int pos = (q1[q1[0]] < a[i]), tmp = (q2[q2[0]] < a[i]);
			if(pos && !tmp) q1[++q1[0]] = a[i];
			else if(tmp && !pos) q2[++q2[0]] = a[i];
			else if(tmp && pos) {
				if(q1[q1[0]] > q2[q2[0]]) q1[++q1[0]] = a[i];
				else q2[++q2[0]] = a[i];
			}
			else {
				flg = 0;
				break;
			}
		}
	}
	if(flg&&!q2[0]) {
		q2[++q2[0]] = q1[q1[0]--];
	}
	if(flg) out();

	//case2
	flg = 1;
	memset(q1, 0, sizeof q1);
	memset(q2, 0, sizeof q2);
	int flg = 1;
	for(int i = 1; i <= n; ++i) {
		if(!q1[0]&&!q2[0]) {
			q1[++q1[0]] = a[i];
		} else {
			int pos = (q1[q1[0]] > a[i]), tmp = (q2[q2[0]] > a[i]);
			if(pos && !tmp) q1[++q1[0]] = a[i];
			else if(tmp && !pos) q2[++q2[0]] = a[i];
			else if(tmp && pos) {
				if(q1[q1[0]] < q2[q2[0]]) q1[++q1[0]] = a[i];
				else q2[++q2[0]] = a[i];
			}
			else {
				flg = 0;
				break;
			}
		}
	}
	if(flg&&!q2[0]) {
		q2[++q2[0]] = q1[q1[0]--];
	}
	if(flg) out();

	//case3
	flg = 1;
	memset(q1, 0, sizeof q1);
	memset(q2, 0, sizeof q2);
	for(int i = n; i >= 1; --i) {
		int now = a[i], sit = ;
	}

	fail();
	return 0;
}