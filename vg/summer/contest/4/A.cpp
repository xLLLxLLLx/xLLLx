#include<bits/stdc++.h>
using namespace std;
const int N = 1010;
int lenx, lenl, tot = 0;
char lx[N], ll[N];

void ok() {
	printf("YES\n");
	exit(0);
}

bool check(int x) {
	for(int i = x; i <= lenx; ++i) {
		if(lx[i] != ll[i - x + 1]) return false;
	}
	return true;
}

bool get(int x, int y) {
	int pos = tot, l = 1;
	if(x == lenx) {
		if((tot & 1) && ll[1] == '0') {
			pos++;
			lx[++x] = char(49);
		}
	}
	for(int i = y; i <= lenl; ++i) {
		int tmp = ll[i] - '0';
		if(tmp != (pos & 1)) {
			int flg = 0;
			while(l <= x) {
				int gg = lx[l] - '0';
				pos -= gg;
				l++;
				if(gg) {
					flg = 1;
					break;
				}
			}
			if(!flg) {
				return false;
			}
		}
		pos += tmp;
	}
	return true;
}

int main() {
	scanf("%s%s", lx + 1, ll + 1);
	lenx = strlen(lx + 1);
	lenl = strlen(ll + 1);
	tot = 0;
	for(int i = 1; i <= lenx; ++i) {
		tot += (lx[i] == '1');
	}
	get(lenx, 1);
	for(int i = 1; i <= lenx + 1; ++i) {
		int pos = lenx - i + 1;
		if(pos > lenl) continue;
		if(check(i)) {
			pos++;
			if(pos > lenl) ok();
			if(get(i - 1, pos)) ok();
		}
	}
	printf("NO\n");
	return 0;
}