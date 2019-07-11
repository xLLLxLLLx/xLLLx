#include <bits/stdc++.h>
using namespace std;

int main() {
	for(int o = 1; ; o++) {
		system("./gen > data");
		system("./my < data > oo");
		system("./std < data > uu");
		if(system("diff oo uu")) {
			printf("NO\n");
			return 0;
		}
		printf("test%d: AC!\n",o);
	}
	return 0;
}