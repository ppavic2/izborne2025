#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
using pii=pair<int,int>;
using ll=long long;
using pll=pair<ll,ll>;
using vi=vector<int>;
using vl=vector<ll>;
#define pb push_back
#define all(a) begin(a),end(a)

const int N=500010,M=1<<19,MOD=1e9+7;
const char en='\n';
const ll LLINF=1ll<<61;

int seg1[M*2+10];

void upd(int i,int x)
{
	seg1[i+=M]=x;
	for (i/=2;i;i/=2) seg1[i]=seg1[i*2]+seg1[i*2+1];
}

int getL(int i)
{
	i+=M;
	while (i>1)
	{
		if ((i&1) && seg1[i^1])
		{
			i^=1;
			while (i<M)
			{
				if (seg1[i*2+1]) i=i*2+1;
				else i=i*2;
			}
			return i-M+1;
		}
		i/=2;
	}
	return 0;
}

int getR(int i)
{
	i+=M;
	while (i>1)
	{
		if (i%2==0 && seg1[i^1])
		{
			i^=1;
			while (i<M)
			{
				if (seg1[i*2]) i=i*2;
				else i=i*2+1;
			}
			return i-M-1;
		}
		i/=2;
	}
	return M-1;
}

pii rang(int i)
{
	return {getL(i),getR(i)};
}

vector<pii> upd0(int i)
{
	assert(seg1[i+M]==1);
	vector<pii> an;
	if (seg1[i-1+M]==0)
	{
		an.pb({i-getL(i-1),-1});
	}
	if (seg1[i+1+M]==0)
	{
		an.pb({getR(i+1)-i,-1});
	}
	upd(i,0);
	an.pb({getR(i)-getL(i)+1,1});
	return an;
}

vector<pii> upd1(int i)
{
	assert(seg1[i+M]==0);
	vector<pii> an;
	an.pb({getR(i)-getL(i)+1,-1});
	upd(i,1);
	if (seg1[i-1+M]==0)
	{
		an.pb({i-getL(i-1),1});
	}
	if (seg1[i+1+M]==0)
	{
		an.pb({getR(i+1)-i,1});
	}
	return an;
}

pll add(pll a,pll b)
{
	return {a.x+b.x,a.y+b.y};
}

int n,q,h[N];
pll seg2[M*2+10];

void updX(int i,ll x)
{
	seg2[i+M].x+=x;
	seg2[i+M].y+=x*i;
	i+=M;
	for (i/=2;i;i/=2) seg2[i]=add(seg2[i*2],seg2[i*2+1]);
}

pll ge(int l,int r)
{
	l+=M;
	r+=M;
	pll an={0ll,0ll};
	while (l<r)
	{
		if (l&1) an=add(an,seg2[l]),++l;
		if (r&1) an=add(an,seg2[r-1]),--r;
		l/=2;
		r/=2;
	}
	return an;
}

char ti[N];
int br[N];
vector<pii> nap[N];

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>q;
	for (int i=0;i<=n+1;++i) upd(i,1);
	map<int,vector<pii>> ev;
	for (int i=1;i<=n;++i)
	{
		cin>>h[i];
		ev[h[i]].pb({0,i});
	}
	for (int i=1;i<=q;++i)
	{
		cin>>ti[i]>>br[i];
		if (ti[i]=='+')
		{
			ev[h[br[i]]].pb({i,br[i]});
			++h[br[i]];
		}
	}
	for (int i=1;i<=q;++i) if (ti[i]=='+') --h[br[i]];
	for (auto x: ev)
	{
		vector<pii> us=x.y;
		sort(all(us));
		for (auto u: us) if (u.x==0)
		{
			auto re=upd0(u.y);
			for (auto z: re)
			{
				updX(z.x,(MOD-x.x)*z.y);
			}
		}
		else nap[u.x]=upd1(u.y);
		for (auto u: us) if (u.x!=0) upd0(u.y);
	}
	for (int i=1;i<=q;++i)
	{
		if (ti[i]=='?')
		{
			int k=br[i]-1;
			auto re=ge(k,n+1);
			cout<<MOD*1ll*(n-k)-re.y+re.x*k<<en;
		}
		else
		{
			for (auto z: nap[i]) updX(z.x,z.y);
		}
	}
}

