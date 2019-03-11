#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10,mod=1073741824;
struct data{
	int x,y,z,id;
}a[N],b[N];
struct node{
	int dp;
	LL f;
}tr[N],d[N];
LL tot=0;
int Ax[N],Ay[N],Az[N];
int n,ans=0;

bool cmp(data xx,data yy){
	if(xx.x!=yy.x) return xx.x<yy.x;
	if(xx.y!=yy.y) return xx.y<yy.y;
	if(xx.z!=yy.z) return xx.z<yy.z;
}

node Go(node x,node y){
	node tmp;tmp=x;
	printf("GGGG%d %lld %d %lld\n",x.dp,x.f,y.dp,y.f);
	if(x.dp<y.dp) tmp.dp=y.dp,tmp.f=y.f;
	else if(x.dp==y.dp) tmp.dp=x.dp,tmp.f=(x.f+y.f)%mod;
	return tmp;
}

void Ch(int x){
	cout<<x<<" "<<d[x].dp<<" "<<d[x].f<<endl;
	if(d[x].dp<ans) return ;
	else if(d[x].dp==ans) tot=(tot+d[x].f)%mod;
	else ans=d[x].dp,tot=d[x].f;
}

int lowerbit(int x){ return x&(-x); }

void Upd(int x,node y){
	for(;x<N;x+=lowerbit(x)) {
		tr[x]=Go(tr[x],y);
	}
}

node Get(int x){
	if(!x) return (node){0,0};
	node tmp;
	for(;x;x-=lowerbit(x)) tmp=Go(tmp,tr[x]);
	return tmp;
}

void Qk(int x){
	for(;x<N;x+=lowerbit(x)) tr[x].dp=0,tr[x].f=0;
}

void cdq(int l,int r){
	if(l==r) return ;
	int mid=(l+r)>>1;
	cdq(l,mid),cdq(mid+1,r);
	int pos=l-1,nw=l;
	cout<<"l="<<l<<" r="<<r<<endl;
	fr(i,mid+1,r){
		while(pos+1<=mid&&a[pos+1].y<=a[i].y){
			printf("Go%d %lld\n",d[a[pos+1].id].dp,d[a[pos+1].id].f);
			pos++,Upd(a[pos].z,(node){d[a[pos].id].dp+1,d[a[pos].id].f}),b[nw++]=a[pos];
		}
		b[nw++]=a[i];
		printf("WMLWAI!\n");
		node gg=Get(a[i].z);
		printf("wtf%d %lld\n",gg.dp,gg.f);
		d[a[i].id]=Go(d[a[i].id],gg);
		Ch(a[i].id);
	}
	fr(i,pos+1,mid) b[nw++]=a[i];
	fr(i,l,pos) Qk(a[i].z);
	fr(i,l,r) a[i]=b[i];
	/*fr(i,l,r){
		printf("x=%d y=%d z=%d\n",a[i].x,a[i].y,a[i].z);
	}*/
}

int main(){
	int T;scanf("%d",&T);
	fr(o,1,T){
		ans=0,tot=0;
		scanf("%d",&n);
		fr(i,1,n) {
			scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z),a[i].id=i;
			Ax[i]=a[i].x,Ay[i]=a[i].y,Az[i]=a[i].z;
		}
		sort(Ax+1,Ax+1+n),sort(Ay+1,Ay+1+n),sort(Az+1,Az+1+n);
		Ax[0]=unique(Ax+1,Ax+1+n)-Ax-1;
		Ay[0]=unique(Ay+1,Ay+1+n)-Ay-1;
		Az[0]=unique(Az+1,Az+1+n)-Az-1;
		fr(i,1,n){
			a[i].x=lower_bound(Ax+1,Ax+1+Ax[0],a[i].x)-Ax;
			a[i].y=lower_bound(Ay+1,Ay+1+Ay[0],a[i].y)-Ay;
			a[i].z=lower_bound(Az+1,Az+1+Az[0],a[i].z)-Az;
			//printf("x=%d y=%d z=%d\n",a[i].x,a[i].y,a[i].z);
		}
		fr(i,1,n) d[i].dp=1,d[i].f=1;
		sort(a+1,a+1+n,cmp);
		cdq(1,n);
		printf("%d %lld\n",ans,tot);
		fr(i,1,n) d[i]=(node){0,0LL};
	}
	return 0;
}
