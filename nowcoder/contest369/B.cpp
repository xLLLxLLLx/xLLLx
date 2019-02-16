#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define db double
#define LL long long
using namespace std;
const int N=2e5+10;
struct data{
	db t,ed,z;
	int rk;
}a[N];
struct node{
	db z,yu;
	bool operator < (const node &C) const{
		return z<C.z;
	}
};
priority_queue<node>q;

bool cmp(data xx,data yy){
	return xx.ed<yy.ed;
}

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) scanf("%lf%lf%lf",&a[i].z,&a[i].t,&a[i].ed),a[i].rk=i;
	db ans=0;
	sort(a+1,a+1+n,cmp);
	db now=0;
	fr(i,1,n){
		q.push((node){a[i].z,a[i].t});
		if(now+a[i].t<=a[i].ed){
			now+=a[i].t;
		} else {
	//		cout<<a[i].z<<" "<<a[i].t<<" "<<a[i].ed<<" "<<a[i].rk<<endl;
			db zz=now+a[i].t-a[i].ed;
			while(zz>0){
				node tmp=q.top();q.pop();
				if(zz<tmp.yu){
					ans+=zz/tmp.z;
					tmp.yu-=zz;
					zz=0;
					q.push((node){tmp.z,tmp.yu});
				} else {
					ans+=tmp.yu/tmp.z;
					zz-=tmp.yu;
				}
			}
			now=a[i].ed;
		}
	}
	printf("%.1lf\n",ans);
	return 0;
}
