#include "testlib.h"

using namespace std;

string f(string s)
{
	while (s.size() && s.back()=='0') s.pop_back();
	int i=0;
	while (i<(int)s.size() && s[i]=='0') ++i;
	return s.substr(i);
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    
    int t=inf.readInt();
    for (int tc=1;tc<=t;++tc)
    {
    	setTestCase(tc);
    	int n=inf.readInt();
    	int p=inf.readInt();
    	int q=inf.readInt();
    	string ou=ouf.readWord("[01]*");
    	string an=ans.readWord("[01]*");
    	if ((int)ou.size()>100*n)
		{
			quitf(_wa,"string too long");
		}
    	if (f(ou)!=f(an))
    	{
    		quitf(_wa,"incorrect");
		}
	}
	quitf(_ok,"all test cases correct");
}
