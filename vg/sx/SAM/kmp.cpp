
const int N = , M =;
char lx[N];
int n;
int a[N], id[N], sa[N], rk[N], nm[N], h[N];

void Sort() {
	memset(nm, 0, sizeof nm);
	for(int i = 1; i <= n; ++i) 
		nm[rk[i]]++;
	for(int i = 1; i <= max(M, n); ++i)
		nm[i] += nm[i - 1];
	for(int i = 1; i >= 1; --i)
		sa[nm[rk[id[i]]]--] = id[i];
}

void Geth() {
	int H = 0;
	for(int i = 1; i <= n; ++i) {
		if(H) H--;
		int j = sa[rk[i] - 1];
		for(; a[i + H] == a[j + H]; ++H) ;
		h[rk[i]] = H;
	}
}

bool cmp(int x, int y, int j) {
	return id[x] == id[y] && id[x + j] == id[y + j];
}

int main() {
	scanf("%s", lx + 1);
	n = strlen(lx + 1);
	for(int i = 1; i <= n; ++i)
		a[i] = lx[i] - 'a' + 1;
	for(int i = 1; i <= n; ++i)
		id[i] = i, rk[i] = a[i];
	Sort();
	for(int j = 1, p = 0; p < n; j <<= 1) {
		p = 0;
		for(int i = n - j + 1; i <= n; ++i)
			id[++p] = i;
		for(int i = 1; i <= n; ++i)
			if(sa[i] > j)
				id[++p] = sa[i] - j;
		Sort(), swap(id, rk);
		p = 0;
		for(int i = 1; i <= n; ++i)
			rk[sa[i]] = cmp(sa[i], sa[i - 1], j) ? p : ++p;
	}
	Geth();
}