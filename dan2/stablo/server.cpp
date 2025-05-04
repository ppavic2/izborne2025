// Server to be used by evaluator.
//
// Usage: TASK_server input_file config_file log_file output_file
//
// To test locally:
//   mkfifo temp
//   ./TASK_server test/TASK.in.1 /dev/null flog foutput < temp | ./MY_SOLUTION
//   > temp
//

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdarg>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <signal.h>
#include <stack>
#include <string>
#include <unistd.h>
#include <utility>

using namespace std;

#define TRACE(x) cerr << #x << "  " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); i++)
#define REP(i, n) FOR(i, 0, n)
#define all(x) (x).begin(), (x).end()
#define _ << " " <<

#define fi first
#define se second
#define mp make_pair
#define pb push_back

typedef long long ll;

/******************************* CROATIAN
 * ***************************************/

#define CANNOT_READ_N "Neispravna ulazna datoteka: ne mogu procitati broj n."
#define CANNOT_READ_K "Neispravna ulazna datoteka: ne mogu procitati broj k."
#define CANNOT_READ_Q "Neispravna ulazna datoteka: ne mogu procitati broj q."
#define CANNOT_READ_TREE "Neispravna ulazna datoteka: ne mogu ucitati stablo."
#define CANNOT_READ_QUESTION "Neispravna ulazna datoteka: ne mogu ucitate svoje upite."
#define WA_INCORRECT "Netocno!"
#define WA_INVALID_COMMAND "Netocno, neispravna naredba!"
#define WA_PREMATURE_TERMINATION                                               \
  "Netocno, Vas program je zavrsio prije nego sto je ispisao rjesenje!"
#define WAITING "Cekam..."
#define CORRECT "Tocno!"
#define WA_TOO_MANY_QUERIES "Netocno, previse upita!"
#define WAITING_FOR_SOLUTION "Cekam rjesenje..."

ifstream finput;  // read from the input file (test case description)
ifstream fconfig; // read from the config file (additional, per test case)
ofstream foutput; // write the output, first the score for the test case,
                  // then the output the contestants will see in the system
ofstream flog;    // write to an official log for tracing purposes

// assert a condition, awards 0 points if condition fails, same format as a
// regular printf
void test_condition(bool condition, const char *format, ...) {
  if (!condition) {
    static char dest[1024 * 16];
    va_list argptr;
    va_start(argptr, format);
    vsprintf(dest, format, argptr);
    va_end(argptr);

    foutput << 0 << endl;
    flog << dest << endl;
    exit(0);
  }
}

void send_answer(int a, int b, int ret) {
  flog << "Query was (" << a << "," << b << "), answer is " << ret << endl;
  cout << ret << endl;
}

vector<int> v[505];
int n;

void bfs(int start, vector<int> &dist) {
	queue<int> Q;
	dist = vector<int>(n + 1, -1);
	dist[start] = 0; Q.push(start);
	for(;!Q.empty();Q.pop()) {
		int current = Q.front();
		for(int next : v[current]) {
			if(dist[next] == -1) {
				dist[next] = dist[current] + 1;
				Q.push(next);
			}
		}
	}
}


// - read the test case from finput,
// - read the contestant's output from cin
// - write to the contestant's input with cout
// - log with flog
// - score and explanation to foutput
void main_problem_interaction() {
  const string QUERY_COMMAND = "?";
  const string END_COMMAND = "!";

  test_condition(bool(finput >> n), CANNOT_READ_N);

  vector<vector<int>> dist(n + 1);

  for (int i = 1;i <= n;i++) {
  	int x;
    test_condition(bool(finput >> x), CANNOT_READ_TREE);
    v[i].push_back(x);
    v[x].push_back(i);
  }
  
  for(int i = 1;i <= n;i++) bfs(i, dist[i]);
  
  for(int k = 1;k <= n;k++)
  	for(int i = 1;i <= n;i++)
  		for(int j = 1;j <= n;j++)
  			dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
 
  int QUERY_LIMIT = 250000;

  // Start interaction
  int query_count = 0;

  cout << n << endl;

  flog << WAITING << endl;
  // Loop.
  while (true) {
    string cmd;
    test_condition(bool(cin >> cmd), WA_PREMATURE_TERMINATION);

    if (cmd == END_COMMAND) {
      break;
    }

    ++query_count;
    test_condition(cmd == QUERY_COMMAND, WA_INVALID_COMMAND);
    test_condition(query_count <= QUERY_LIMIT, WA_TOO_MANY_QUERIES);

    int a, b, c;
    test_condition(bool(cin >> a >> b >> c), WA_INVALID_COMMAND, query_count);
    test_condition(1 <= a && a <= n, WA_INVALID_COMMAND);
    test_condition(1 <= b && b <= n, WA_INVALID_COMMAND);
    test_condition(1 <= c && c <= n, WA_INVALID_COMMAND);
    test_condition(a != b && b != c && c != a, WA_INVALID_COMMAND);

	int ret = 0;
	if(dist[a][b] < dist[a][c])
		ret = 1;
	if(dist[a][b] > dist[a][c])
		ret = 2;

    // Send the answer
    
    send_answer(a, b, ret);
  }

  // Read and check the output
  flog << "Starting to read answer" << endl;
  
  for(int i = 1;i < n;i++) {
  	int a, b; 
  	test_condition(bool(finput >> a >> b), WA_INCORRECT);
  	test_condition(bool(dist[a][b] == 1), WA_INCORRECT);
  	dist[a][b] = -1; dist[b][a] = -1;
  }
  if(!query_count) query_count = 1;
  foutput << min(1.0, pow((double)13500/query_count, 0.7)) << endl;
}

int main(int argc, char *argv[]) {
  struct sigaction act;
  act.sa_handler = SIG_IGN;
  sigaction(SIGPIPE, &act, NULL);

  assert(argc == 5);
  finput.open(argv[1]);
  fconfig.open(argv[2]);
  flog.open(argv[3]);
  foutput.open(argv[4]);
  assert(!finput.fail() && !fconfig.fail() && !flog.fail() && !foutput.fail());
  main_problem_interaction();
  return 0;
}
