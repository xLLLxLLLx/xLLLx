#include<bits/stdc++.h>
using namespace std;
const int Maxn=40005;
struct Operator{
	int x,k,type;//-1删除 1添加 0询问
	int L,R,index;
}a[Maxn],Left[Maxn],Right[Maxn];
int n,m,cnt,cntq,v[Maxn],ans[Maxn];
struct Tree_Array{
	int c[Maxn];
	#define lowbit(x) (x)&-(x)
	void add(int x,int k){
		for(;x<=n;x+=lowbit(x))c[x]+=k;
	}
	int sum(int x){
		int ret=0;
		for(;x>0;x-=lowbit(x))ret+=c[x];
		return ret;
	}
}bit;
void Solve(int ql,int qr,int al,int ar){
	if(ql>qr)return ;
	if(al==ar){
		for(int i=ql;i<=qr;++i)
			if(a[i].type==0)ans[a[i].index]=al;
		return ;
	}
	int cntl=0,cntr=0,cnt=ql-1,mid=(al+ar)/2;
	for(int i=ql;i<=qr;++i){
		if(a[i].type){
			if(a[i].k<=mid){
				bit.add(a[i].x,a[i].type);
				Left[++cntl]=a[i];
			}else {
				Right[++cntr]=a[i];
			}
		}else {
			int Rank=bit.sum(a[i].R)-bit.sum(a[i].L-1);
			if(a[i].k<=Rank){
				Left[++cntl]=a[i];
			}else {
				a[i].k-=Rank;
				Right[++cntr]=a[i];
			}
		}
	}
	for(int i=ql;i<=qr;++i)
		if(a[i].type&&a[i].k<=mid)bit.add(a[i].x,-a[i].type);
	for(int i=1;i<=cntl;++i)a[++cnt]=Left[i];
	for(int i=1;i<=cntr;++i)a[++cnt]=Right[i];
	Solve(ql,ql+cntl-1,al,mid),Solve(ql+cntl,qr,mid+1,ar);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		scanf("%d",&v[i]);
		a[++cnt]=(Operator){i,v[i],1};
	}
	for(int i=1;i<=m;++i){
		char c=getchar();while(!isalpha(c))c=getchar();
//		cout<<c<<"\n";
		if(c=='Q'){
			a[++cnt].type=0;a[cnt].index=++cntq;
			scanf("%d%d%d",&a[cnt].L,&a[cnt].R,&a[cnt].k);
		}else {
			int x,k;scanf("%d%d",&x,&k);
			a[++cnt]=(Operator){x,v[x],-1};
			a[++cnt]=(Operator){x,v[x]=k,1};
		}
	}
	Solve(1,cnt,-(1<<30),(1<<30));
	for(int i=1;i<=cntq;++i)
		cout<<ans[i]<<endl;
	return 0;
}
