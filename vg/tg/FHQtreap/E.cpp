#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2e5+10,M=1001;
struct data{
	vector<int>v;
	data(){l=N,r=0;}
	int l,r;
}b[M];
int a[N],mk[N];

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

int main(){
	int n,q;read(n),read(q);
	int len=sqrt(n);
	fr(i,1,n) a[i]=i;
	fr(i,1,n){
		mk[i]=(i-1)/len+1;
		b[mk[i]].l=min(b[mk[i]].l,i);
		b[mk[i]].r=max(b[mk[i]].r,i);
		b[mk[i]].v.push_back(i);
	}
	LL ans=0;
	//fr(i,1,3) printf("%d %d\n",b[i].l,b[i].r);
	fr(o,1,q){
		// fr(i,1,n) printf("%d ",a[i]);
		// puts("");
		int x,y;read(x),read(y);
		if(x>y) swap(x,y);
		int fx=mk[x],fy=mk[y];
		if(x==y) ;
		else if(fx==fy){
			fr(i,x+1,y-1){
				if(a[i]<a[x]) ans--;
				if(a[i]>a[y]) ans--;
				if(a[i]>a[x]) ans++;
				if(a[i]<a[y]) ans++; 
			}
			if(a[x]>a[y]) ans--;
			else ans++;
			swap(a[x],a[y]);
		} else {
			fr(i,x+1,b[fx].r){
				if(a[i]<a[x]) ans--;
				if(a[i]>a[y]) ans--;
				if(a[i]>a[x]) ans++;
				if(a[i]<a[y]) ans++; 
			}
			fr(i,b[fy].l,y-1){
				if(a[i]<a[x]) ans--;
				if(a[i]>a[y]) ans--;
				if(a[i]>a[x]) ans++;
				if(a[i]<a[y]) ans++;
			}
			if(a[x]>a[y]) ans--;
			else ans++;
			fr(i,fx+1,fy-1){
				int tot=b[i].r-b[i].l+1;
				int gg=lower_bound(b[i].v.begin(),b[i].v.end(),a[x])-b[i].v.begin();
				ans+=tot-2*gg,gg=0;
				gg=lower_bound(b[i].v.begin(),b[i].v.end(),a[y])-b[i].v.begin();
				ans+=2*gg-tot;
			}
			int tmp=a[x],pos=a[y];
			b[fx].v.erase(lower_bound(b[fx].v.begin(),b[fx].v.end(),tmp));
			b[fx].v.insert(upper_bound(b[fx].v.begin(),b[fx].v.end(),pos),pos);
			b[fy].v.erase(lower_bound(b[fy].v.begin(),b[fy].v.end(),pos));
			b[fy].v.insert(upper_bound(b[fy].v.begin(),b[fy].v.end(),tmp),tmp);
			swap(a[x],a[y]);
			//puts("xx");
		}
		printf("%lld\n",ans);
	}
	return 0;
}