#include <bits/stdc++.h>
using namespace std;
const int N = 5010;
char lx[N];

void fail() {
	printf("Impossible\n");
	exit(0);
}

bool check(int l, int r) {
	for(int i = l; i <= r; ++i) {
		if(lx[i] != lx[r - i + l]) return false;
	}
	return true;
}

bool go(int x) {
	if(x & 1) return true;
	int mid = x / 2;
	if(check(1, mid)) {
		return go(mid);
	} else return false;
}

int main() {
	scanf("%s", lx + 1);
	int len = strlen(lx + 1);
	if(len == 1) fail();
	int flg = 1, pos = lx[1] - 'a' + 1;
	if(len & 1) {
		for(int i = 1; i <= len; ++i) {
			if(i == len / 2 + 1) continue;
			if(lx[i] - 'a' + 1 != pos) flg = 0;
		}
	} else {
		for(int i = 1; i <= len; ++i) {
			if(lx[i] - 'a' + 1 != pos) flg = 0;
		}
	}
	if(flg) fail();
	else {
		if(len & 1) {
			printf("2\n");
		} else {
			if(go(len)) printf("2\n");
				else printf("1\n");
		}
	} 
	return 0;
}