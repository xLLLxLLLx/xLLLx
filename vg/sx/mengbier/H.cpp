#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=100110,LOG=18;
char lx[N];
ll f[N];
int sa[N],h[N],a[N],nm[N],rk[N],id[N],st[N][LOG+1];
int n;

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void Sort(){
	fr(i,1,max(n,26)) nm[i]=0;
	fr(i,1,n) nm[rk[i]]++;
	fr(i,1,max(n,26)) nm[i]+=nm[i-1];
	rf(i,n,1) sa[nm[rk[id[i]]]--]=id[i];
}

void Geth(){
	int H=0;
	fr(i,1,n){
		int j=sa[rk[i]-1];
		if(H) H--;
		while(a[i+H]==a[j+H]) H++;
		h[rk[i]]=H;
	}
	// fr(i,2,n) printf("%d ",h[i]);
}

bool cmp(int x,int y,int j){
	return id[x] == id[y] && id[x+j] == id[y+j];
}

void rmq(){
	fr(i,1,n) st[i][0]=h[i];
	fr(j,1,LOG){
		fr(i,1,n){
			if(i+(1<<j)+1>n) break;
			st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
		}
	}
}

int Get(int l,int r){
	if(l>r) swap(l,r);
	l++;
	int k=(log((double)r-l+1))/log(2.0);
	return min(st[l][k],st[r-(1<<k)+1][k]);
}

int yz[N],mu[N],mk[N];

void init(){
	mu[1]=1;
	fr(i,2,N-1){
		if(!mk[i]) yz[++yz[0]]=i,mu[i]=-1;
		fr(j,1,yz[0]){
			if(i*yz[j]>=N) break;
			mk[i*yz[j]]=1;
			if(i%yz[j]) mu[i*yz[j]]=-mu[i];
				else { mu[i*yz[j]]=0;break; }
		}
	}
}

int main(){
	init();
	int T;read(T);
	fr(o,1,T){
		scanf("%s",lx+1);
		n=strlen(lx+1);
		fr(i,1,n) a[i]=lx[i]-'a'+1;
		fr(i,1,n) id[i]=i,rk[i]=a[i];
		a[n+1]=0;
		Sort();
		for(int j=1,p=0;p<n;j<<=1){
			p=0;
			fr(i,n-j+1,n) id[++p]=i;
			fr(i,1,n) if(sa[i]>j) id[++p]=sa[i]-j;
			Sort(),swap(id,rk);
			p=0;
			fr(i,1,n) 
				rk[sa[i]] = cmp(sa[i],sa[i-1],j) ? p : ++p;
		}
		Geth(),rmq();
		int nm=0;
		fr(i,1,n) {
			fr(j,1,n/i){
				int l=(j-1)*i+1,r=j*i+1;
				int pos=Get(rk[l],rk[r]);
				int tmp=pos/i+1;
				int yu=l-(i-pos%i),flg=0;
				if(yu>=1&&pos%i){
					if(Get(rk[yu],rk[yu+i])>=i) tmp++;
				}
				f[tmp]++;
			}
		}
		ll ans=n*1ll*(n+1)/2;
		rf(i,n,1) f[i]+=f[i+1];
		fr(i,1,n) printf("%lld ",f[i]);
		fr(i,2,n) ans+=mu[i]*f[i];
		printf("%lld\n",ans);
		fr(i,1,n) fr(j,0,LOG) st[i][j]=0;
		fr(i,1,n) f[i]=0;
	}
	return 0;
}