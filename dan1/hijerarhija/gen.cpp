#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <unistd.h>

#define X first
#define Y second

using namespace std;

typedef vector<int> vi;

const int N = 5050;

int uzeo[N], cookie = 1, n, k;

int main() {
	srand(time(0) * getpid());
	int n = 15, k = rand() % 160 + 40;
	printf("%d %d\n", n, k);
	for(int i = 2;i <= n;i++) printf("%d%c", rand() % (i - 1) + 1, i == n ? '\n' : ' ');
	for(int i = 1;i <= n;i++) printf("%d%c", rand() % 20 + 1, i == n ? '\n' : ' ');
	for(int i = 1;i <= n;i++) printf("%d%c", rand() % 20 + 1, i == n ? '\n' : ' ');
	return 0;
}
