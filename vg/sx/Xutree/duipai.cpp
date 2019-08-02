#include <bits/stdc++.h>
using namespace std;

int main() {
	for(int o = 1; ; ++o) {
		system("./gen > out");
		system("./B < out > oo");
		system("./gg < out > uu");
		if(system("diff uu oo")) {
			printf("WAI!!!\n");
			return 0;
		}
		printf("test %d : AC!!!\n", o);
	}
	return 0;
}