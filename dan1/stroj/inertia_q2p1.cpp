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

int t;
string dp[N][N];

string solve(int n,int p,int q)
{
	int sz=__lg(q);
	int cn=(n-1)/sz;
	string s=string(n-cn*sz,'1');
	for (int i=0;i<cn;++i) s+=string(sz,'1')+"0";
	return s+"0";
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
}

