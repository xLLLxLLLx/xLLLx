#include <bits/stdc++.h>
using namespace std;

int main() {
	for(int o = 1; ; ++o) {
		system("./gen > out");
		system("./gg < out > oo");
		system("./L < out > uu");
		if(system("diff oo uu")) {
			printf("WAI!!!\n");
			exit(0);
		} else {
			printf("test %d : AC!\n", o);
		}
	}
	return 0;
}