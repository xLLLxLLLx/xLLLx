#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define Vector data
#define db double
using namespace std;
struct data{
	db x,y;
};

db cross(Vector A,Vector B){
	return A.x*B.y-A.y*B.x;
}

data js(data a,Vector A,data b,Vector B){
	data p;
	Vector u;u.x=a.x-b.x;u.y=a.y-b.y;
	db t=cross(B,u)/cross(A,B);
	p.x=a.x+A.x*t;
	p.y=a.y+A.y*t;
	return p;
}

int main(){
	for(;;){
		db s1,t1,s2,t2,s3,s4,t3,t4;
		scanf("%lf%lf%lf%lf",&s1,&t1,&s2,&t2);
		scanf("%lf%lf%lf%lf",&s3,&t3,&s4,&t4);
		data zz=js((data){s1,t1},(data){s2-s1,t2-t1},(data){s3,t3},(data){s4-s3,t4-t3});
		cout<<zz.x<<" "<<zz.y<<endl;
	}
	return 0;
}
/*
point intersect(point P, Vector v, point Q, Vector w) {
  point p;
  Vector u = P - Q;
  double t = cross(w, u) / cross(v, w);
  p = P + v * t;
  return p;
}
*/