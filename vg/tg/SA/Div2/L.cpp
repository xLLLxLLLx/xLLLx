#include<bits/stdc++.h>
#define lson (x<<1)
#define rson (x<<1|1)
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2e5+10,LOG=20;
char lx[N];
int mk[N],tot[N],a[N],id[N],rk[N],h[N],sa[N],nm[N],st[N][LOG+1];
int v[N<<2];
LL d[N>>1];
int q,k,n=0,ans=0;

void change(int x,int l,int r,int L,int R,int val){
	if(L<=l&&r<=R){
		v[x]=max(v[x],val);
		return ;
	}
	int mid=(l+r)>>1;
	if(L<=mid) change(lson,l,mid,L,R,val);
	if(R>mid) change(rson,mid+1,r,L,R,val);
}

void Ask(int x,int l,int r,int L){
	ans=max(ans,v[x]);
	if(l==r) return ;
	int mid=(l+r)>>1;
	if(L<=mid) Ask(lson,l,mid,L);
	else Ask(rson,mid+1,r,L);
}

void Sort(){
	memset(nm,0,sizeof nm);
	fr(i,1,n) nm[rk[i]]++;
	fr(i,1,max(n,26+q)) nm[i]+=nm[i-1];
	rf(i,n,1) sa[nm[rk[id[i]]]--]=id[i];
}

void Geth(){
	int H=0;
	fr(i,1,n){
		if(H) H--;
		int j=sa[rk[i]-1];
		while(a[i+H]==a[j+H]) H++;
		h[rk[i]]=H;
	}
	//fr(i,2,n) printf("%d ",h[i]);
}

bool cmp(int x,int y,int j){
	return id[x]==id[y] && id[x+j]==id[y+j];
}

void rmq(){
	fr(i,1,n) st[i][0]=h[i];
	fr(j,1,LOG){
		fr(i,1,n){
			if(i+(1<<j)>n+1) break;
			st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
		}
	}
}

int Get(int l,int r){
	int t=log(double(r-l+1))/log(2.0);
	return min(st[l][t],st[r-(1<<t)+1][t]);
}

int main(){
	scanf("%d%d",&q,&k);
	fr(i,1,q){
		scanf("%s",lx+1);
		int len=strlen(lx+1);
		if(k==1) d[i]=len*1LL*(len+1)/2;
		fr(j,1,len) a[++n]=lx[j]-'a'+1,mk[n]=i;
		a[++n]=i+26;
	}
	if(k==1){
		fr(i,1,q) printf("%lld ",d[i]);
		return 0;
	}
	// n=8;
	// a[1]=1,a[2]=1,a[3]=2,a[4]=1,a[5]=1,a[6]=1,a[7]=1,a[8]=2;
	//fr(i,1,n) printf("%d ",a[i]);
	//puts("");
	fr(i,1,n) id[i]=i,rk[i]=a[i];
	Sort();
	for(int j=1,p=0;p<n;j<<=1){
		p=0;
		fr(i,n-j+1,n) id[++p]=i;
		fr(i,1,n) if(sa[i]>j) id[++p]=sa[i]-j;
		Sort(),swap(id,rk);
		p=0;
		fr(i,1,n) rk[sa[i]] = cmp(sa[i],sa[i-1],j) ? p : ++p;
	}
	Geth(),rmq();
	//puts("WCNM!");
	int i=0;
	fr(j,1,n){
		//printf("j=%d %d\n",j,sa[j]);
		if(mk[sa[j]]){
			if(!tot[mk[sa[j]]]) tot[0]++;
			tot[mk[sa[j]]]++;
		}
		if(tot[0]<k) continue;
		while(i<j&&tot[0]>k){
			//printf("%d %d\n",i,j);
			if(mk[sa[i]]) tot[mk[sa[i]]]--;
			if(mk[sa[i]]&&!tot[mk[sa[i]]]) tot[0]--;
			i++;
		}
		while(i<j&&tot[0]==k){
			//printf("dejd%d %d\n",i,j);
			if(tot[0]==k) change(1,1,n,i,j,Get(i+1,j));
			if(mk[sa[i]]) tot[mk[sa[i]]]--;
			if(mk[sa[i]]&&!tot[mk[sa[i]]]) { tot[mk[sa[i]]]++; break ; }
			i++; 
		}
		if(tot[0]==k) change(1,1,n,i,j,Get(i+1,j));
	}
	fr(i,1,n) Ask(1,1,n,i),d[mk[sa[i]]]+=ans,ans=0;
	fr(i,1,q) printf("%lld ",d[i]);
	return 0;
}