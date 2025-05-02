#include "testlib.h"

const int MAXN=100'000;
const int MAXQ=1'000'000'000;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int t=inf.readInt(1, 10000, "t");
    inf.readEoln();
    int sumn=0;
    for (int tc=1;tc<=t;++tc)
    {
    	setTestCase(tc);
    	int n=inf.readInt(1,MAXN,"n");
    	sumn+=n;
    	ensuref(sumn<=MAXN,"sum of n must not exceed %d",MAXN);
    	inf.readSpace();
    	int p=inf.readInt(1,MAXQ,"p");
    	inf.readSpace();
    	int q=inf.readInt(1,MAXQ,"q");
    	inf.readEoln();
    	ensuref(q%2==1,"q must be odd");
    	ensuref(2*p<q,"p/q must be less than 1/2");
	}
	inf.readEof();
}
