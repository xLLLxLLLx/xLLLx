#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=3e5+10,M=15;
int jl[M][N],zf[M][N],ans=3e5+10,res=0,fk=-1,cnt=0,n,m;
int fa[6][2]={{1,2},{1,3},{1,4},{2,3},{2,4},{3,4}};
vector<int>qx[N];
string lx[N];

char zh(int z){
	if(z==1) return 'A';
	if(z==2) return 'G';
	if(z==3) return 'T';
	if(z==4) return 'C';
}

int hz(char ch){
	if(ch=='A') return 1;
	if(ch=='G') return 2;
	if(ch=='T') return 3;
	if(ch=='C') return 4;
}

void out(){
	if(fk) {
		fr(i,1,n){
		 int nw=jl[res][i];
		 fr(j,0,m-1){
		 	int kk=j&1;
			if(zf[res][i]<0) kk=1-kk;
			qx[i].push_back(fa[nw][kk]);
		 }
		}
	} else {
		fr(i,0,m-1){
		 int nw=jl[res][i];
		 fr(j,1,n){
		 	int kk=j&1;
		 	if(!zf[res][i]) kk=1-kk;
		 	qx[j].push_back(fa[nw][kk]);
		 }
		}
	}
	fr(i,1,n) {
	 fr(j,0,m-1) cout<<zh(qx[i][j]);
	 cout<<"\n";
	} 
}

int main(){
	cin>>n>>m;
	fr(i,1,n) cin>>lx[i];
	fr(i,0,5){
		++cnt;
		int pos=0,ds=i,fs=5-i;
		fr(j,1,n){
		 if(j&1){
		 	int zx=0,nx=0;
		 	fr(k,0,m-1) {
		 		int nw=hz(lx[j][k]),zz=k&1;
		 		if(fa[ds][zz]!=nw) zx++;
		 		if(fa[ds][1-zz]!=nw) nx++;
		 	}
		 	pos+=min(zx,nx);
		 	if(zx<nx) jl[cnt][j]=ds;
		 	else jl[cnt][j]=ds,zf[cnt][j]=-1;
		 } else {
		 	int zx=0,nx=0;
		 	fr(k,0,m-1) {
		 		int nw=hz(lx[j][k]),zz=k&1;
		 		if(fa[fs][zz]!=nw) zx++;
		 		if(fa[fs][1-zz]!=nw) nx++;
		 	}
		 	pos+=min(zx,nx);
		 	if(zx<nx) jl[cnt][j]=fs;
		 	else jl[cnt][j]=fs,zf[cnt][j]=-1;
		 }
		}
		if(pos<ans) ans=pos,fk=1,res=cnt;
	}
	fr(i,0,5){
		++cnt;
		int pos=0,ds=i,fs=5-i;
		fr(j,0,m-1){
			if(j&1){
				int zx=0,nx=0;
				fr(k,1,n){
					int nw=hz(lx[k][j]),zz=k&1;
					if(fa[ds][zz]!=nw) nx++;
					if(fa[ds][zz^1]!=nw) zx++;
				}
				pos+=min(zx,nx);
				if(zx<nx) jl[cnt][j]=ds;
				else jl[cnt][j]=ds,zf[cnt][j]=-1;
			} else {
				int zx=0,nx=0;
				fr(k,1,n){
					int nw=hz(lx[k][j]),zz=k&1;
					if(fa[fs][zz]!=nw) nx++;
					if(fa[fs][zz^1]!=nw) zx++;
				}
				pos+=min(zx,nx);
				if(zx<nx) jl[cnt][j]=fs;
				else jl[cnt][j]=fs,zf[cnt][j]=-1;
			}
		}
		if(pos<ans) ans=pos,res=cnt,fk=0;
	}
//	cout<<ans<<" "<<res<<" "<<fk<<endl;
//	fr(i,1,n) cout<<jl[res][i]<<" "<<zf[res][i]<<endl;
	//puts("");
	out();
	return 0;
}
