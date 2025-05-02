#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
using pii=pair<int,int>;
using ll=long long;
using vi=vector<int>;
using vl=vector<ll>;
#define pb push_back
#define all(a) begin(a),end(a)

const int N=210,MOD=1e9+7;
const char en='\n';
const ll LLINF=1ll<<61;

int t,op=0;

bool good(string s,int p,int q)
{
	assert(s[0]=='1');
	int cu=q/2;
	for (int i=1;i<(int)s.size()-1;++i)
	{
		cu=(cu+(s[i]-'0')*q)/2;
		++op;
		if (cu<p) return 0;
	}
	return 1;
}

string solve(int n,int p,int q)
{
	op=0;
	string u="0";
	while (n)
	{
		if (good(string(n,'1')+"0"+u,p,q)) u="0"+u;
		else u="1"+u,--n;
	}
	return u;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin>>t;
	while (t--)
	{
		int n,p,q;
		cin>>n>>p>>q;
		cout<<solve(n,p,q)<<en;
	}
	/*int ma=0;
	for (int n=1;n<=20;++n) for (int p=1;p<=1000;++p) for (int q=2*p+1;q<=1000;q+=2)
	{
		solve(n,p,q);
		if (op>ma)
		{
			ma=op;
			cout<<n<<' '<<p<<' '<<q<<en<<solve(n,p,q)<<en<<op<<endl;
		}
	}*/
}

