#include<bits/stdc++.h>
#define lson x<<1
#define rson x<<1|1
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long 
#define db double
using namespace std;
const int N=1e5+10;
struct data{
	int v,id;
}tr[N<<2];
int val[N];
int lastans=0,n,m,seedx,seedy,seed;

void Get_arr()
{
    unsigned x = seed;
    for (int i=1;i<=n;++i)
    {
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        val[i]=x%100;
    }
}

void build(int x,int l,int r){
	if(l==r){tr[x]=(data){val[l],l};return ;}
	int mid=(l+r)>>1;
	build(lson,l,mid),build(rson,mid+1,r);
	if(tr[lson].v>=tr[rson].v) tr[x]=tr[lson];
	else tr[x]=tr[rson];
}

data find(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R) return tr[x];
	int mid=(l+r)>>1;
	if(R<=mid) return find(lson,l,mid,L,R);
	else if(L>mid) return find(rson,mid+1,r,L,R);
	else{
		data pos=find(lson,l,mid,L,R),tmp=find(rson,mid+1,r,L,R);
		if(pos.v>=tmp.v) return pos;
		else return tmp;
	}
}

int ask()
{
   	int ans=0;
    unsigned x=seedx,y=seedy;
    for (int i=1;i<=m;++i)
    {
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        y ^= y << 13;
        y ^= y >> 17;
        y ^= y << 5;
        int L=(x^lastans)%n+1,R=(y^lastans)%n+1;
        if (L>R)swap(L,R);
        lastans=find(1,1,n,L,R).id;
        ans^=lastans;
    }
    return ans;
}

int main(){
	scanf("%d%d%d%d%d",&n,&m,&seed,&seedx,&seedy);
	Get_arr();
	//fr(i,1,n) printf("val%d\n",val[i]);
	build(1,1,n);
	cout<<ask()<<endl;
	return 0;
}
