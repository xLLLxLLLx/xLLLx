#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=3e5+10;
const double PI=acos(-1.0);
const double eps = 1e-3;
struct data{
	double a[2],b[4];
	double r;
	int id;
}s[N],f[N],q;
double down[N][2],up[N][2];
int mk[N],ch[N][2],pd;

#define ls ch[x][0]
#define rs ch[x][1]

template <class T>
void read(T &x){
	char ch=getchar();x=0;int w=0;
	for(;ch<'0'||ch>'9';ch=getchar()) w|=(ch=='-');
	for(;ch>='0'&&ch<='9';ch=getchar()) x=x*10+(ch^48);
	if(w) x=-x;
}

int sgn(double x) {
 	return x < -eps ? -1 : x > eps;
}

bool cmp(data A,data B){
	return sgn(A.a[pd]-B.a[pd])==-1 || (sgn(A.a[pd]-B.a[pd])==0 && sgn(A.a[pd^1]-B.a[pd^1])==-1);
}

void Min(double &x,double y){
	x=min(x,y);
}

void Max(double &x,double y){
	x=max(x,y);
}

void upd(int x){
	if(ls) {
		fr(i,0,1) {
			Min(down[x][i],down[ls][i]);
			Max(up[x][i],up[ls][i]);
		} 
	}
	if(rs) {
		fr(i,0,1) {
			Min(down[x][i],down[rs][i]);
			Max(up[x][i],up[rs][i]);
		}
	}
}

int build(int l,int r,int pos) {
	int mid=(l+r)>>1;
	pd=pos,nth_element(s+l,s+mid,s+r+1,cmp);
	if(l<mid) {
		ch[mid][0]=build(l,mid-1,pos^1);
	} else ch[mid][0]=0;
	if(r>mid) {
		ch[mid][1]=build(mid+1,r,pos^1);
	} else ch[mid][1]=0;
	down[mid][0]=s[mid].b[0],down[mid][1]=s[mid].b[2];
	up[mid][0]=s[mid].b[1],up[mid][1]=s[mid].b[3];
	upd(mid);
	return mid;
}

double pf(double x){
	return x*x;
}

void work(int now,int i,int x){
	// printf("now=%d xid=%d\n",now,s[x].id);
	if(!mk[s[x].id]) {
		double dis=pf(s[x].a[0]-f[i].a[0])+pf(s[x].a[1]-f[i].a[1]);
		// printf("gg%lf %lf\n",dis,pf(s[x].r+f[i].r));
		if(sgn(dis-pf(s[x].r+f[i].r))<=0){
		 // printf("FF!\n");
		 mk[s[x].id]=now;
		}
	}
	if(ls) {
		if(f[i].b[0]>up[ls][0]||f[i].b[1]<down[ls][0]||f[i].b[2]>up[ls][1]||f[i].b[3]<down[ls][1]) 2333;
		else work(now,i,ls);
	}
	if(rs) {
		if(f[i].b[0]>up[rs][0]||f[i].b[1]<down[rs][0]||f[i].b[2]>up[rs][1]||f[i].b[3]<down[rs][1]) 2333;
		else work(now,i,rs);
	}
}

int n;

bool comp(data A,data B){
	return A.r>B.r || (A.r==B.r && A.id<B.id);
}

int main(){
	srand(time(NULL));
	scanf("%d",&n);
	double Arg=0.3*PI;
	double cs=cos(Arg),sn=sin(Arg);
	fr(i,1,n) {
		double x,y,r;
		read(x),read(y),read(r);
		s[i].a[0]=x*cs+y*sn;
		s[i].a[1]=y*cs-x*sn;
		s[i].r=r;
		fr(j,0,1) {
			s[i].b[j*2]=s[i].a[j]-r;
			s[i].b[j*2+1]=s[i].a[j]+r;
		}
		s[i].id=i;
		f[i]=s[i];
	}
	int root=build(1,n,0);
	sort(f+1,f+1+n,comp);
	fr(i,1,n) {
		int x=f[i].id;
		// printf("%d ",x);
		// puts("");
		if(mk[x]) continue;
		mk[x]=x;
		work(x,i,root);
	}
	fr(i,1,n) {
		printf("%d ",mk[i]);
	}
	return 0;
}