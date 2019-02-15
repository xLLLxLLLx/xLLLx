#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define lson x<<1
#define rson x<<1|1
#define LL long long
using namespace std;
const int N=2e6+10;
struct data{
	int V,K;
};
int n,m,cnt=0,tot;
map<LL,int>mp;
int v[N<<2],knw[N<<2],all[N],a[N],r[N];

void change(int x,int l,int r,int L,int k){
	if(l==r&&l==L){
		knw[x]=1;
		v[x]=k;
		return ;
	}
	int mid=(l+r)>>1;
	if(L<=mid) change(lson,l,mid,L,k);
	else change(rson,mid+1,r,L,k);
	v[x]=max(v[lson],v[rson]),knw[x]=knw[lson]+knw[rson];
}

data find(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R) return (data){v[x],knw[x]};
	int mid=(l+r)>>1;
	if(R<=mid) return find(lson,l,mid,L,R);
	else if(L>mid) return find(rson,mid+1,r,L,R);
	else {
		data pos=find(lson,l,mid,L,R),tmp=find(rson,mid+1,r,L,R);
		return (data){max(pos.V,tmp.V),pos.K+tmp.K};
	}
}

int main(){
	scanf("%d",&n);
	fr(i,1,n){
		scanf("%d%d",&a[i],&r[i]),all[++cnt]=a[i];
		mp[a[i]]=r[i];
	}
	scanf("%d",&m);
	fr(i,n+1,n+m){
		scanf("%d%d",&a[i],&r[i]),all[++cnt]=a[i],all[++cnt]=r[i];
	}
	sort(all+1,all+1+n+m);
	int tot=unique(all+1,all+1+n+m)-all-1;
	fr(i,1,n){
		int pos=lower_bound(all+1,all+1+tot,a[i])-all;
		change(1,1,tot,pos,r[i]);
	}
	fr(i,n+1,n+m){
		if(a[i]>r[i]){
			printf("false\n");
			continue;
		}
		int flg1=mp.count(a[i]),flg2=mp.count(r[i]);
		int x=lower_bound(all+1,all+1+tot,a[i])-all;
		int y=lower_bound(all+1,all+1+tot,r[i])-all;
		if(flg1) flg1=mp[a[i]];
		if(flg2) flg2=mp[r[i]];
		if(!flg1&&!flg2) printf("maybe\n");
		if(flg1&&!flg2){
			if(x+1>y-1) printf("maybe\n");
			else {
				data zz=find(1,1,tot,x+1,y-1);
				if(zz.V<flg1) printf("maybe\n");
				else printf("false\n");
			}
		}
		if(!flg1&&flg2){
			if(x+1>y-1) printf("maybe\n");
			else {
				data zz=find(1,1,tot,x+1,y-1);
				if(zz.V<flg2) printf("maybe\n");
				else printf("false\n");
			}
		}
		if(flg1&&flg2){
			if(flg1<flg2) printf("false\n");
			else{
				if(x+1>y-1){
					if(r[i]-a[i]<2) printf("true\n");
					else printf("maybe\n");
				} else {
					data zz=find(1,1,tot,x+1,y-1);
					if(zz.V<flg2){
						if(zz.K==r[i]-a[i]-1) printf("true\n");
						else printf("maybe\n");
					}
					else printf("false\n");
				}
			}
		}
	}
	return 0;
}
