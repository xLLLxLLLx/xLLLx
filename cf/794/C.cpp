	string s, t; cin>>s>>t;
	int n = s.length();

	sort(s.begin(), s.end());
	sort(t.begin(), t.end(), greater<char>());

	s.resize((n+1) >> 1);
	t.resize(n >> 1);

	string ans;
	int st = 0, tt = 0;

	int c = 1;
	while((int) ans.length() < n) {
		if(c == 1) {
			if(s[st] < t[tt]) {
				ans += s[st++];
				c = 2;
			}
			else break;
		}
		else {
			if(s[st] < t[tt]) {
				ans += t[tt++];
				c = 1;
			}
			else break;
		}
	}

	if((n-ans.length()) & 1); else {
		c = 3-c;
	}

	while((int) ans.length() < n) {
		if(c == 1) {
			ans += s[st++];
			c = 2;
		}
		else {
			ans += t[tt++];
			c = 1;
		}
	}

	cout<<ans<<"\n";
	
