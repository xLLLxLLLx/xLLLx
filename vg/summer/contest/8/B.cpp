#include <bits/stdc++.h>
using namespace std;
int n;

int ask(int x) {
	if(x > n) x -= n;
	printf("? %d\n", x);
	fflush(stdout);
	int y;
	scanf("%d", &y);
	return y;
}

int get(int x) {
	if(x <= n / 2) return ask(x) - ask(x + n / 2);
	else return ask(x) - ask(x - n / 2);
}

void print(int x) {
	if(x > n / 2) x -= n / 2;
	printf("! %d\n", x);
	fflush(stdout);
	exit(0);
}

int main() {
	scanf("%d", &n);
	int l = 0, r = n / 2, vl = ask(n) - ask(n / 2), vr = -vl;
	if(vl == 0) print(n / 2);
	else if(vl > 0) {
		if(vl & 1) print(-1);
	} else {
		if(vr & 1) print(-1);
	}
	while(l <= r) {
		int mid = (l + r) >> 1;
		int pos = get(mid);
		if(!pos) print(mid);
		if(1ll * pos * vl < 0) r = mid - 1;
		else l = mid + 1;
	}
	print(-1);
	return 0;
}