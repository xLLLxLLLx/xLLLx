#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("folding.in", "r", stdin);
	freopen("folding.out", "w", stdout);
	int W, H, w, h;
	cin >> W >> H >> w >> h;
	if(W < H) swap(W, H);
	if(w < h) swap(w, h);
	if(W < w || H < h) {
		printf("-1\n");
	} else {
		int pos = 0, tmp = 2e9, W1 = W, H1 = H;
		while(W > w) {
			W = W / 2 + (W & 1);
			pos++;
		}
		while(H > h) {
			H = H / 2 + (H & 1);
			pos++;
		}
		W = W1, H = H1;
		if(W >= h && H >= w) {
			tmp = 0;
			while(W > h) {
				W = W / 2 + (W & 1);
				tmp++;
			}
			while(H > w) {
				H = H / 2 + (H & 1);
				tmp++;
			}
		}
		printf("%d\n", min(pos, tmp));
	}
	return 0;
}