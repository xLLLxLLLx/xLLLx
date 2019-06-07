#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=2e5+10,M=5e5+10,LOG=19;
struct data{
	int l,r;
}a[N];
int st[M][LOG+1];

bool cmp(data A,data B){
	return A.l<B.l || (A.l==B.l && A.r>B.r);
}

void Max(int &x,int y){
	x=max(x,y);
}

int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	int maxn=0;
	fr(i,1,n) {
		scanf("%d%d",&a[i].l,&a[i].r);
		a[i].l++,a[i].r++;
		maxn=max(maxn,a[i].r);
		Max(st[a[i].l][0],a[i].r);
	}
	sort(a+1,a+1+n,cmp);
	fr(i,1,maxn) {
		Max(st[i][0],st[i-1][0]);
	}
	fr(j,1,LOG) fr(i,0,maxn) {
		st[i][j]=st[i][j-1];
		Max(st[i][j],st[st[i][j-1]][j-1]);
	}
	// fr(j,0,LOG) fr(i,1,maxn) {
	// 	printf("st[%d][%d]=%d\n",i,j,st[i][j]);
	// }
	fr(o,1,m) {
		int x,y;
		scanf("%d%d",&x,&y);
		x++,y++;
		int ans=0;
		if(st[x][LOG]<y) printf("-1\n");
		else {
			rf(i,LOG,0) {
				if(st[x][i]<y) {
					ans+=(1<<i);
					x=st[x][i];
				}
			}
			if(x<y) {
				x=st[x][0];
				ans++;
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}