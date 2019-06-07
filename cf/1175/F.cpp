#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10,LOG=19;
int n,ans=0;
int nm[N],a[N],g[N],st[N][LOG];

int get(int l,int r){
	int k=log(double(r-l+1))/log(2.0);
	return max(st[l][k],st[r-(1<<k)+1][k]);
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i) {
		scanf("%d",&a[i]);
		st[i][0]=a[i];
		if(a[i]==1)
			g[++g[0]]=i;
	}
	for(int j=1;j<=LOG;++j) 
		for(int i=1;i<=n;++i) {
			if(i+(1<<j)>n+1) continue;
			st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
		}
	for(int i=1;i<=g[0];++i) {
		int maxn=1,now=0;
		int xd= i==g[0] ? n : g[i+1]-1;
		int dx= i==1 ? 1 : g[i-1]+1;
		int l=g[i],r=g[i];
		nm[1]=1;
		for(int j=g[i]+1;j<=xd;++j) {
			int v=a[j];
			maxn=max(maxn,v);
			nm[v]++;
			if(nm[v]==2) now++;
			int L=j-maxn+1;
			// printf("%d %d\n",L,j);
			if(L<dx) continue;
			if(get(L,j)>maxn) continue;
			for(int k=l;k<L;++k) {
				int vv=a[k];
				nm[vv]--;
				if(nm[vv]==1) now--;
			}
			for(int k=L;k<l;++k) {
				int vv=a[k];
				nm[vv]++;
				if(nm[vv]==2) now++;
			}
			l=L;
			// printf("%d %d\n",l,j);
			if(!now) ans++;
		}
		for(int j=dx;j<=xd;++j) {
			nm[a[j]]=0;
		}
		nm[1]=1,maxn=1,now=0;
		for(int j=g[i]-1;j>=dx;--j) {
			int v=a[j];
			maxn=max(maxn,v);
			nm[v]++;
			if(nm[v]==2) now++;
			int R=maxn+j-1;
			if(R>xd) continue;
			if(get(j,R)>maxn) continue;
			for(int k=R+1;k<=r;++k) {
				int vv=a[k];
				nm[vv]--;
				if(nm[vv]==1) now--;
			}
			for(int k=r+1;k<=R;++k) {
				int vv=a[k];
				nm[vv]++;
				if(nm[vv]==2) now++;
			}
			r=R;
			if(!now) ans++;
			// printf("%d %d\n",j,r);
		}
		for(int j=dx;j<=xd;++j) {
			nm[a[j]]=0;
		}
	}
	printf("%d\n",ans+g[0]);
	return 0;
}