void buildByFt(int v, int tl, int tr, int id)
{
 	if (tl == tr) 
 	{
 		t[id][v] = tv1[id][tl];
 		sort(all(t[id][v]));
 		return;
 	}

	int mid = (tl + tr) >> 1;
	buildByFt((v << 1), tl, mid, id);
	buildByFt((v << 1) + 1, mid + 1, tr, id);
	
	int i = 0;
	int j = 0;
	
	int szt = 0;

	int szt1 = sz(t[id][(v << 1)]);
	int szt2 = sz(t[id][(v << 1) + 1]);

	int allszt = sz(t[id][(v << 1)]) + sz(t[id][(v << 1) + 1]);
	
	t[id][v].resize(allszt);

	while (szt < allszt)
	{
	 	if (i < szt1 && j < szt2)
	 	{
	 	 	if (t[id][(v << 1)][i] <= t[id][(v << 1) + 1][j])
	 	 	{
	 	 		t[id][v][szt++] = t[id][(v << 1)][i];
	 	 		i++;
	 	 	}
	 	 	else
	 	 	{
	 	 		t[id][v][szt++] = t[id][(v << 1) + 1][j];
	 	 		j++;
	 	 	}
	 	 	continue;
	 	}
	 	if (i < szt1)
	 	{
	 		t[id][v][szt++] = t[id][(v << 1)][i];
	 	 	i++;
	 	}

	 	if (j < szt2)
	 	{
	 	 	t[id][v][szt++] = t[id][(v << 1) + 1][j];
	 	 	j++;
	 	}
	}
}

void buildBySc(int v, int tl, int tr, int id)
{
 	if (tl == tr) 
 	{
 	    t[id + 2][v] = tv2[id][tl];
        sort(all(t[id + 2][v]));
        reverse(all(t[id + 2][v]));
    
        return;
 	}

    int mid = (tl + tr) >> 1;
	buildBySc((v << 1), tl, mid, id);
	buildBySc((v << 1) + 1, mid + 1, tr, id);
	
	id += 2;

	int i = 0;
	int j = 0;
	
	int szt = 0;

	int szt1 = sz(t[id][(v << 1)]);
	int szt2 = sz(t[id][(v << 1) + 1]);

	int allszt = sz(t[id][(v << 1)]) + sz(t[id][(v << 1) + 1]);
	
	t[id][v].resize(allszt);

	while (szt < allszt)
	{
	 	if (i < szt1 && j < szt2)
	 	{
	 	 	if (t[id][(v << 1)][i] >= t[id][(v << 1) + 1][j])
	 	 	{
	 	 		t[id][v][szt++] = t[id][(v << 1)][i];
	 	 		i++;
	 	 	}
	 	 	else
	 	 	{
	 	 		t[id][v][szt++] = t[id][(v << 1) + 1][j];
	 	 		j++;
	 	 	}
	 	 	continue;
	 	}
	 	if (i < szt1)
	 	{
	 		t[id][v][szt++] = t[id][(v << 1)][i];
	 	 	i++;
	 	}

	 	if (j < szt2)
	 	{
	 	 	t[id][v][szt++] = t[id][(v << 1) + 1][j];
	 	 	j++;
	 	}
	}
}

void get(int v, int tl, int tr, int l, int r, int id, int tvalue)
{
 	if (l > r)
 		return;                                     
                       

 	if (l == tl && r == tr)
 	{
 		
 		if (id < 2)
 		{
 			while (!t[id][v].empty())
 			{
 			 	pt s = t[id][v].back();

 			 	if (s.ft > tvalue)
 			 	{                        
 			 		
 			 		if (!used[id & 1][s.sc]) 
 			 	    {
 			 	    	used[id & 1][s.sc] = 1;
 			 	    	ncur[szncur++] = s.sc;
 			 	    }

 			 	    t[id][v].pop_back();
 			 	} else
 			 		break;	
 			}
 		} 
 		else
 		{
 			while (!t[id][v].empty())
 			{
 			 	pt s = t[id][v].back();
 			 	if (s.ft < tvalue) 
               	{                
 			 	    if (!used[id & 1][s.sc])
 			 	    {
 			 	    	used[id & 1][s.sc] = 1;
 			 	    	ncur[szncur++] = s.sc;
 			 	    }
 			 	    t[id][v].pop_back();
 			 	} else
 			 		break;	
 			}
 		}

 	   	return;
	}

	int mid = (tl + tr) >> 1;

	get((v << 1), tl, mid, l, min(r, mid), id, tvalue);
	get((v << 1) + 1, mid + 1, tr, max(l, mid + 1), r, id, tvalue);
		
} 
inline void solve() 
{       
    curtime = 0;
    go(0, 0);

    curtime = 0;
    go(1, 0);    

    forn(it, 2)
	 	forn(i, n - 1)
	 	{
	 		int u = edges[it][i].ft;
	 		int v = edges[it][i].sc;
       
         	int dv1 = in[it ^ 1][u];
        	int dv2 = in[it ^ 1][v];

        	if (dv1 > dv2)
        		swap(dv1, dv2);

        	tv1[it][dv1].pb(mp(dv2, i));
        	tv2[it][dv2].pb(mp(dv1, i));
        }
	
	forn(it, 2)
		buildByFt(1, 0, 2 * n - 1, it);

	forn(it, 2)
		buildBySc(1, 0, 2 * n - 1, it);

    int idx = 0;

    forn(i, szcur)
    	used[0][cur[i]] = 1;

	while(true)
	{                
		if (szcur == 0) break;
		if (idx & 1)
			puts("Red");
		else
			puts("Blue");

		sort(cur, cur + szcur);

		forn(i, szcur) 
		{
			if (i) printf(" ");
			printf("%d", cur[i] + 1);
		}		 	
		puts("");
		forn(i, szcur) 
		{
			int u = edges[idx][cur[i]].ft;
			int v = edges[idx][cur[i]].sc;

		}

		forn(i, szcur) 
		{
			int u = edges[idx][cur[i]].ft;
			int v = edges[idx][cur[i]].sc;
        	
        	int l, r;

        	if (out[idx][u] > out[idx][v])
        		l = in[idx][v], r = out[idx][v];
        	else
        		l = in[idx][u], r = out[idx][u];
        
            if (!(idx & 1))
        		get(1, 0, 2 * n - 1, l, r, 1, r),
        		get(1, 0, 2 * n - 1, l, r, 3, l);
       		else
       			get(1, 0, 2 * n - 1, l, r, 0, r),
        		get(1, 0, 2 * n - 1, l, r, 2, l);
       			
        }
  
        idx ^= 1;

        forn(i, szncur)
        	cur[i] = ncur[i];

        szcur = szncur;
        szncur = 0;
   	}
}
