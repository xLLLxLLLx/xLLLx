#include<bits/stdc++.h>
using namespace std;

int main() {
	int x,y,z;
	cin>>x>>y>>z;
	y=-y;
	if(x+y+z>0 && x+y-z>0) printf("+\n");
	else if(x+y+z<0 &&x+y-z<0) printf("-\n");
	else if(x+y+z==0 &&x+y-z==0 )printf("0\n");
	else printf("?\n");
	return 0;
}