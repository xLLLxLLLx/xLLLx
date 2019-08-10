#include <bits/stdc++.h>
using namespace std;
multiset<int> s;
multiset<int> :: iterator it;

int main() {
	/**/
	it = s.begin();
	s.erase(it);
	printf("%d\n", *s.begin());
	return 0;
}