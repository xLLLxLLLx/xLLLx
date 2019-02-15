#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define db double
#define pb push_back
using namespace std;
const db eps=1e-8;
const int N=310;

struct point{
	db x,y;
	point(double x=0,double y=0):x(x),y(y){}
};

typedef point Vector;

Vector operator + (const Vector &a,const Vector &b){
	return Vector(a.x+b.x,a.y+b.y);
}

Vector operator - (const Vector &a,const Vector &b){
	return Vector(a.x-b.x,a.y-b.y);
}

Vector operator * (const Vector &a,db p){
	return Vector(a.x*p,a.y*p);
}

Vector operator / (const Vector &a,db p){
	return Vector(a.x/p,a.y/p);
}

int sgn(db x){
	return x<-eps?-1:x>eps;
}

db cross(Vector a,Vector b){
	return a.x*b.y-b.x*a.y;
}

db dot(Vector a,Vector b){
	return a.x*b.x+a.y*b.y;
}

bool operator < (const point &a,const point &b){
	return sgn(a.x-b.x)<0||(sgn(a.x==b.x)&&sgn(a.y-b.y)<0);
}

bool operator == (const point &a,const point &b){
	return sgn(a.x-b.x)==0&&sgn(a.y-b.y)==0;
}

point insect(point a,Vector P,point b,Vector Q){
	point p;
	Vector u=a-b;
	db t=cross(Q,u)/cross(P,Q);
	p=P*t+a;
	return p;
}

int pd(point A,point s,point e){
	return sgn(cross(e-s,A-s));
}

vector<point> CUT(const vector<point>&p,point s,point e){
	vector<point>q;
	int len=p.size();
	fr(i,0,len-1){
		int pos=pd(p[i],s,e),tmp=pd(p[(i+1)%len],s,e);
		if(pos>=0) q.pb(p[i]);
		if(pos*tmp<0){
			q.pb(insect(p[i],p[(i+1)%len]-p[i],s,e-s));
		}
	}
	return q;
}

db calcul(const vector<point>&p){
	db ans=0;
	int len=p.size();
	fr(i,0,len-1){
		ans+=cross(p[i],p[(i+1)%len]);
	}
	return fabs(ans)/2;
}

vector<point>Con[N];
db area[N];

int main(){
	int n,k;scanf("%d%d",&n,&k);
	fr(i,0,k-1){
		area[i]=1000.0;
		Con[i].pb((point){i,0});
		Con[i].pb((point){i+1,0});
		Con[i].pb((point){i+1,1000});
		Con[i].pb((point){i,1000});
	}
	fr(o,1,n){
		db y1,y2,ans=0;
		scanf("%lf",&y1);
		fr(i,0,k-1){
			scanf("%lf",&y2);
			Con[i]=CUT(Con[i],(point){i,y1},(point){i+1,y2});
			db pos=calcul(Con[i]);
			ans+=area[i]-pos;
			area[i]=pos;
			y1=y2;
		}
		printf("%.12f\n",ans);
	}
}
