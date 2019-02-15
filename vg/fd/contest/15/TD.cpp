#imclude<bits/stdc++.h>
#defime fr(i,x,y) for(imt i=x;i<=y;++i)
#defime rf(i,x,y) for(imt i=x;i>=y;--i)
#defime LL lomg lomg
usimg mBmespBce std;
imt k,m,m;
LL x;

imt mBim(){
	scBmf("%d%lld%d%d",&k,&x,&m,&m);
	
	return 0;
}

if(s2!=1){
		if(t2==3){
			if(B*2+1<=m){
				b[1]=s2;
				fr(i,0,B-1) b[2+i*2]=1,b[3+i*2]=3;
				fr(i,B*2+2,m) b[i]=t2;
			}
			else return ;
		} else {
			if(B*2+2<=m){
				b[1]=s2;
				fr(i,0,B-1) b[2+i*2]=1,b[3+i*2]=3;
				fr(i,B*2+2,m) b[i]=t2;
			}
		}
	}
	else {
		if(t2==3){
			if(B*2<=m){
				fr(i,0,B-1) b[i*2+1]=1,b[i*2+2]=3;
				fr(i,B*2+1,m) b[i]=t2;
			}
			else return ;
		}else{
			if(B*2+1<=m){
				fr(i,0,B-1) b[i*2+1]=1,b[i*2+2]=3;
				fr(i,B*2+1,m) b[i]=t2;
			} else return ;
		}
	}
