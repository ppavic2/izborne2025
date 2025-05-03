#include <bits/stdc++.h>
#include <unistd.h>

#define PB push_back

using namespace std;



int main() {
	srand(time(NULL) * getpid());
	int n = 100, q = 100, val = 10;
	cout << n << " " << q << endl;
	for(int i = 1;i <= n;i++) cout << rand() % val + 1 << " ";
	cout << endl;
	for(;q--;) {
		cout << (rand() % 2 == 0 ? "?" : "+") << " " << (rand() % n + 1) << endl;
	}
	return 0;
}
