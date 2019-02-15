/*
add some notes
*/
#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long

const double eps=1e-8;
const int N=310;
using namespace std;

struct point{
	double x,y;
	point (double x=0,double y=0):x(x),y(y){}
};

typedef point Vector;

Vector operator + (const Vector &a,const Vector &b){	//Vector a+Vector b
	return Vector(a.x+b.x,a.y+b.y);
}

Vector operator - (const Vector &a,const Vector &b){	//Vector a-Vector b
	return Vector(a.x-b.x,a.y-b.y);
}

Vector operator * (const Vector &a,double p){	//(Vector a)*p
	return Vector(a.x*p,a.y*p);
}

Vector operator / (const Vector &a,double p){	//(Vector a)/p
	return Vector(a.x/p,a.y/p);
}

int sgn(double x) {		//check Poor precision
	return x<-eps?-1:x>eps;
}

bool operator < (const point &a, const point &b) {
  return sgn(a.x-b.x)<0 || sgn(a.x-b.x)==0 && sgn(a.y-b.y)<0;
}

bool operator == (const point &a, const point &b) {
  return sgn(a.x-b.x)==0&&sgn(a.y - b.y)==0;
}

double cross(Vector a, Vector b) {	//calculation cross product
  return a.x*b.y-a.y*b.x;
}

double dot(Vector a, Vector b) {	//calculation dot product
	return a.x*b.x+a.y*b.y;
}

point intersect(point P, Vector v, point Q, Vector w) {		//Calculate the intersection point
	point p;
	Vector u=P-Q;
	double t=cross(w, u)/cross(v, w);
	p=P+v*t;
	return p;
}

int inhalfplane(point p,point s,point e) {
	return sgn(cross(e-s,p-s)) ;
}

vector<point> CUT(const vector<point> &p, point s, point e) {	//Get the new Convex
	vector<point> q;
	int n=(int)p.size();
	fr(i,0,n-1){
		int nowin=inhalfplane(p[i],s,e);
		int nextin=inhalfplane(p[(i+1)%n],s,e);
		if(nowin>=0){
			q.push_back(p[i]);
		}
		if(nextin*nowin<0) {
		  q.push_back(intersect(p[i],p[(i+1)%n]-p[i],s,e-s));
		}
	}
	return q;
}

double calc(const vector<point> &p) {	//calculate the Convex hull p's area
	int n=(int)p.size();
	double ans=0;
	fr(i,0,n-1) ans+=cross(p[i],p[(i+1)%n]);
	return fabs(ans)/2;
}

vector<point>convex[N];
double area[N];

int main(){
	int n,k;scanf("%d%d",&n,&k);
	fr(i,0,k-1){
		area[i]=1000.0;
		convex[i].push_back((point){i,0});
		convex[i].push_back((point){i+1,0});
		convex[i].push_back((point){i+1,1000});
		convex[i].push_back((point){i,1000});
	}
	fr(o,1,n){
		double y1,y2,ans=0;
		scanf("%lf",&y1);
		fr(i,0,k-1){
			scanf("%lf",&y2);
			convex[i]=CUT(convex[i],(point){i,y1},(point){i+1,y2});
			double pos=calc(convex[i]);
			ans+=area[i]-pos;
			area[i]=pos;
			y1=y2;
		}
		printf("%.12f\n",ans);
	}
	return 0;
}
