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
#define CANNOT_READ_PERMUTATION "Neispravna ulazna datoteka: ne mogu ucitati permutaciju."
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

typedef vector<int> vi;

const int OFF = (1 << 10);

int P[OFF], T[2 * OFF];

int maax(int A, int B) {
	return P[A] > P[B] ? A : B;
}

int query(int i, int a, int b, int lo, int hi) {
	if(lo <= a && b <= hi) return T[i];
	if(a > hi || b < lo) return 0;
	return maax(query(2 * i, a, (a + b) / 2, lo, hi), query(2 * i + 1, (a + b) / 2 + 1, b, lo, hi));
}

int second_max(int l, int r) {
	int mid = query(1, 0, OFF - 1, l, r);
	return maax(query(1, 0, OFF - 1, l, mid - 1), query(1, 0, OFF - 1, mid + 1, r));	
}

// - read the test case from finput,
// - read the contestant's output from cin
// - write to the contestant's input with cout
// - log with flog
// - score and explanation to foutput
void main_problem_interaction() {
  const string QUERY_COMMAND = "?";
  const string END_COMMAND = "!";
  int n, q;

  test_condition(bool(finput >> n), CANNOT_READ_N);
  test_condition(bool(finput >> q), CANNOT_READ_Q);

  for (int i = 1;i <= n;i++) {
    test_condition(bool(finput >> P[i]), CANNOT_READ_PERMUTATION);
  	T[OFF + i] = i;
  }
  for(int i = OFF - 1; i ; i--) T[i] = maax(T[2 * i], T[2 * i + 1]);

  int QUERY_LIMIT = 2048;

  // Start interaction
  int query_count = 0;

  cout << n << " " << q << endl;

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

    int a, b;
    test_condition(bool(cin >> a >> b), WA_INVALID_COMMAND, query_count);
    test_condition(1 <= a && a <= n, WA_INVALID_COMMAND);
    test_condition(1 <= b && b <= n, WA_INVALID_COMMAND);
    test_condition(a < b, WA_INVALID_COMMAND);

    // Send the answer
    send_answer(a, b, second_max(a, b));
  }

  // Read and check the output
  flog << "Starting to ask queries" << endl;
  
  vi l(q), r(q);
  
  cout << q << endl;
  for(int i = 0;i < q;i++) {
  	test_condition(bool(finput >> l[i] >> r[i]), CANNOT_READ_QUESTION);
  	cout << l[i] << " " << r[i] << endl;
  }
  
  for(int i = 0;i < q;i++) {
  	int contestant_answer;
  	test_condition(bool(cin >> contestant_answer), WA_PREMATURE_TERMINATION);
  	test_condition(contestant_answer == second_max(l[i], r[i]), WA_INCORRECT);
  }
  
  foutput << 1 << endl;
 // foutput << "broj upita: " << query_count << endl;
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
