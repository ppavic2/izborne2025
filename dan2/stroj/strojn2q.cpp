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

const int N=1010,MOD=1e9+7;
const char en='\n';
const ll LLINF=1ll<<61;

int t;
string dp[N][N];

bool gr(string a,string b)
{
	reverse(all(a));
	reverse(all(b));
	while (a.size()<b.size()) a.pb('0');
	while (a.size()>b.size()) b.pb('0');
	return a<b;
}

string solve(int n,int p,int q)
{
	for (int i=0;i<=n;++i) for (int j=0;j<q;++j) dp[i][j]="";
	dp[1][q/2]="1";
	for (int i=1;i<=n;++i) for (int j=q-1;j>=p;--j) if (dp[i][j]!="")
	{
		if (j/2>=p && (dp[i][j/2]=="" || gr(dp[i][j]+"0",dp[i][j/2]))) dp[i][j/2]=dp[i][j]+"0";
		if (i<n && (dp[i+1][(j+q)/2]=="" || gr(dp[i][j]+"1",dp[i+1][(j+q)/2]))) dp[i+1][(j+q)/2]=dp[i][j]+"1";
	}
	string ma="";
	for (int j=p;j<q;++j) if (dp[n][j]!="" && (ma=="" || gr(dp[n][j],ma))) ma=dp[n][j];
	return ma+"0";
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

