void solve(int rt){
	seq.clear();
	dfs(rt);
	int x=-1;
	for (auto y:seq){
		mx[y]=max(mx[y],sz[rt]-sz[y]);
		if (x==-1||(mx[y]<mx[x])) x=y;
	}//search.
	queue<int> q;
	for (auto u:seq)
		for (auto i:wzp[u])
			if (u==x){
				dis[i]=pa(0,i-bel[i]);
				q.push(i);
			}
			else dis[i]=pa(1e9,-1);
	while (!q.empty()){
		int u=q.front(); q.pop();
		for (auto v:walk[u]){
			pa newv(dis[u].fi+1,dis[u].se);
			if (newv<dis[v]){
				dis[v]=newv;
				q.push(v);
			}
		}
	}
	vector<pa> ins,Q;
	for (auto u:seq) for(auto i:wzp[u]){
		if (first[i]<1e9) ins.push_back(pa(first[i],i));
		for (auto qid:allq[i]) Q.push_back(pa(qid,i));
	}
	sort(ins.begin(),ins.end());
	sort(Q.begin(),Q.end());
	for (int i=0;i<=cnt[x];i++) fenq[i]=fens[i]=1e9;
	int tmp=0;
	for (auto u:Q){
		for (;tmp<ins.size()&&ins[tmp].fi<u.fi;++tmp){
			for (int i=dis[ins[tmp].se].se+1;i<=cnt[x];i+=i&(-i))
				fenq[i]=min(fenq[i],dis[ins[tmp].se].fi-dis[ins[tmp].se].se);
			for (int i=dis[ins[tmp].se].se+1;i>0;i-=i&(-i))
				fens[i]=min(fens[i],dis[ins[tmp].se].fi+dis[ins[tmp].se].se);
		}
		for (int i=dis[u.se].se+1;i>0;i-=i&(-i))
			if (fenq[i]<1e9) ans[u.fi]=min(ans[u.fi],fenq[i]+dis[u.se].fi+dis[u.se].se);
		for (int i=dis[u.se].se+1;i<=cnt[x];i+=i&(-i))
			if (fens[i]<1e9) ans[u.fi]=min(ans[u.fi],fens[i]+dis[u.se].fi-dis[u.se].se);
	}
	for (auto y:adj[x]) adj[y].erase(x);
	for (auto y:adj[x]) solve(y);
}