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

const int N=300010,MOD=1e9+7;
const char en='\n';
const ll LLINF=1ll<<61;

int t,n,p,q;

string solve(int n,int p,int q)
{
	int cp=p;
	string s="0";
	while (n--)
	{
		int c=min(n,__lg(q))+1;
		int x=__lg(((1ll<<c)-1)*q/cp)-c;
		s+=string(x,'0')+"1";
		cp=max(p,(cp<<(x+1))-q);
	}
	reverse(all(s));
	return s;
}

string solveB(int n,int p,int q)
{
	string ms=string(20,'0');
	double kol=0,thr=p*1./q;
	for (int b=0;b<(1<<20);++b) if (__builtin_popcount(b)==n)
	{
		double cu=0,v=0;
		for (int i=0;i<20;++i)
		{
			if ((b>>i)&1) v+=1;
			cu+=v;
			v/=2;
			if (v<thr) v=0;
		}
		if (cu>kol)
		{
			kol=cu;
			for (int i=0;i<20;++i) ms[i]=((b>>i)&1)+'0';
		}
	}
	return ms;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin>>t;
	while (t--)
	{
		cin>>n>>p>>q;
		cout<<solve(n,p,q)<<endl;
	}
	
	/*for (int cn=1;cn<=10;++cn) for (int cq=3;cq<=50;cq+=2) for (int cp=1;cp*2<cq;++cp)
	{
		string s1=solve(cn,cp,cq);
		if (s1.size()>20) continue;
		cout<<cn<<' '<<cp<<' '<<cq<<' '<<s1<<' '<<s1.size()<<en;
		string s2=solveB(cn,cp,cq);
		if (s1!=s2.substr(0,s1.size()))
		{
			cout<<cn<<' '<<cp<<' '<<cq<<endl;
			cout<<solve(cn,cp,cq)<<' '<<solveB(cn,cp,cq)<<endl;
			exit(0);
		}
	}
	mt19937 rng(32589);
	uniform_int_distribution<int> dis(1,499'999'999);
	for (int cn=1;cn<=10;++cn) for (int tt=0;tt<100;++tt)
	{
		int cq=dis(rng)*2+1;
		uniform_int_distribution<int> d2(1,cq/2);
		int cp=d2(rng);
		string s1=solve(cn,cp,cq);
		if (s1.size()>20) continue;
		cout<<cn<<' '<<cp<<' '<<cq<<' '<<s1<<' '<<s1.size()<<en;
		string s2=solveB(cn,cp,cq);
		if (s1!=s2.substr(0,s1.size()))
		{
			cout<<cn<<' '<<cp<<' '<<cq<<endl;
			cout<<solve(cn,cp,cq)<<' '<<solveB(cn,cp,cq)<<endl;
			exit(0);
		}
	}*/
}

