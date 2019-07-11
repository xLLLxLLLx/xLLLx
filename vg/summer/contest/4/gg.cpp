#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long LL;
const int SIZE=200010;
LL N,Bsize;
int match[SIZE];
class Curve{
public:
	int l,r;
};
bool operator < (const Curve &a,const Curve &b){
	if(a.l/Bsize==b.l/Bsize) return a.r<b.r;
	return a.l/Bsize<b.l/Bsize;
}
Curve C[SIZE];
LL nowl=1,nowr=0,now_cross=0,now_inner=0;
void try_add(int k){
	if(nowl<=match[k]&&match[k]<=nowr) now_inner++,now_cross--;
	else now_cross++;
}
void try_del(int k){
	if(nowl<=match[k]&&match[k]<=nowr) now_inner--,now_cross++;
	else now_cross--;
}
void work(void){
	LL all_tri=N*(N-1)*(N-2)/6;
	LL diff_cnt=0;//异色角的数量
	LL wrong_pure=0;//不合法的纯色三角形数目
	for(int i=1;i<=N;i++){
		printf("qwq%d %d\n", C[i].l, C[i].r);
		while(nowl>C[i].l) try_add(--nowl);
		while(nowr<C[i].r) try_add(++nowr);
		while(nowl<C[i].l) try_del(nowl++);
		while(nowr>C[i].r) try_del(nowr--);
		printf("%lld %lld\n", now_cross, now_inner);
		diff_cnt+=now_cross*(N-1-now_cross);
		wrong_pure+=(now_inner-1)*(N-now_inner-now_cross);
	}
	LL tri_cnt=all_tri-diff_cnt/2;//纯色三角形数目
	tri_cnt-=wrong_pure;
	cout<<tri_cnt<<endl;
}
void init(void){
	cin>>N;
	Bsize=sqrt(2*N+1.0);
	int a,b;
	for(int i=1;i<=N;i++){
		scanf("%d%d",&a,&b);
		if(a>b) swap(a,b);
		C[i]=(Curve){a,b};
		match[a]=b;match[b]=a;
	}
	sort(C+1,C+1+N);
}
int main(){
	//freopen("t1.in","r",stdin);
	init();
	work();
	return 0;
}
