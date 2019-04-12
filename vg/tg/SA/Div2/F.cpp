#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10,LOG=19;
char lx[N];
int n,res=0;
int d[N],a[N],id[N],h[N],rk[N],sa[N],nm[N],st[N][LOG+1];

void Sort(){
	fr(i,1,max(n,26)) nm[i]=0;
	fr(i,1,n) nm[rk[i]]++;
	fr(i,1,max(n,26)) nm[i]+=nm[i-1];
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
	// fr(i,2,n) printf("%d ",h[i]);
	// puts("");
}

bool cmp(int x,int y,int j){
	return id[x]==id[y] && id[x+j]==id[y+j];
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
	int t=log(double(r-l+1))/log(2.0);
	return min(st[l][t],st[r-(1<<t)+1][t]);
}

int main(){
	for(int o=1;;++o){
		scanf("%s",lx+1);
		if(lx[1]=='#') break;
		printf("Case %d: ",o);
		n=strlen(lx+1);
		fr(i,1,n) a[i]=lx[i]-'a'+1;
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
		int maxn=0;
		fr(i,1,n) {
			fr(j,1,n/i){
				int l=(j-1)*i+1,r=j*i+1;
				int pos=Get(rk[l],rk[r]);
				int tmp=pos/i+1;
				int yu=l-(i-pos%i);
				if(yu>=1&&pos%i){
					if(Get(rk[yu],rk[yu+i])>=i) tmp++;
				}
				if(tmp>maxn) d[res=1]=i,maxn=tmp;
					else if(tmp==maxn) d[++res]=i;
			}
		}
		//printf("%d\n",maxn);
		int flg=0;
		fr(i,1,n){
			fr(j,1,res){
				int len=d[j];
				if(Get(i,rk[sa[i]+len])>=(maxn-1)*len){
					fr(k,sa[i],sa[i]+maxn*len-1) printf("%c",a[k]+'a'-1);
					puts("");flg=1;
					break;
				}
				if(flg) break;
			}
			if(flg) break;
		}
		fr(i,1,n) a[i]=0;
	}
	return 0;
}