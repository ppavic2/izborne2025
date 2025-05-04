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

const int N=3010,MOD=1e9+7;
const char en='\n';
const ll LLINF=1ll<<61;

const bool DEB=0;

int dis[N][N];

int ask(int a,int b,int c)
{
	cout<<"? "<<a<<' '<<b<<' '<<c<<endl;
	int x;
	if (DEB)
	{
		
		if (dis[a][b]==dis[a][c]) x=0;
		else if (dis[a][b]<dis[a][c]) x=1;
		else x=2;
		//cout<<x<<endl;
	}
	else
	{
		cin>>x;
	}
	return x;
}

int n,ss[N],par[N];
vi ch[N],ord;

bool cmp(int a,int b)
{
	return ask(1,a,b)==1;
}

vi sor(vi v)
{
	int sz=v.size();
	if (sz==1) return v;
	vi le,ri;
	for (int i=0;i<sz/2;++i) le.pb(v[i]);
	for (int i=sz/2;i<sz;++i) ri.pb(v[i]);
	le=sor(le);
	ri=sor(ri);
	vi nov;
	int sl=le.size(),sr=ri.size(),i1=0,i2=0;
	//cout<<sl<<' '<<le[0]<<' '<<sr<<' '<<ri[0]<<en;
	while (i1+i2<sz)
	{
		if (i1==sl) nov.pb(ri[i2++]);
		else if (i2==sr) nov.pb(le[i1++]);
		else if (cmp(le[i1],ri[i2])) nov.pb(le[i1++]);
		else nov.pb(ri[i2++]);
	}
	return nov;
}

void dfs1(int i,int p=-1)
{
	ss[i]=1;
	par[i]=p;
	ord.pb(i);
	for (auto x: ch[i]) if (x!=p)
	{
		dfs1(x,i);
		ss[i]+=ss[x];
	}
}

int getCent(int i)
{
	ord.clear();
	dfs1(i);
	int vel=ord.size();
	for (auto x: ord)
	{
		if (vel-ss[x]>vel/2) continue;
		bool ok=1;
		for (auto y: ch[x]) if (y!=par[x])
		{
			if (ss[y]>vel/2) ok=0;
		}
		if (ok) return x;
	}
	assert(0);
}

vector<pii> mak;

void makni(int a,int b)
{
	mak.pb({a,b});
	ch[a].erase(find(all(ch[a]),b));
	ch[b].erase(find(all(ch[b]),a));
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	if (DEB)
	{
		for (int i=1;i<=n;++i) for (int j=1;j<=n;++j) dis[i][j]=MOD;
		for (int i=1;i<=n;++i) dis[i][i]=0;
		cout<<"pravo"<<endl;
		for (int i=1;i<n;++i)
		{
			int a=rand()%i+1,b=i+1;
			cout<<a<<' '<<b<<endl;
			dis[a][b]=dis[b][a]=1;
		}
		for (int k=1;k<=n;++k) for (int i=1;i<=n;++i) for (int j=1;j<=n;++j) dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	}
	vi v;
	for (int i=2;i<=n;++i) v.pb(i);
	v=sor(v);
	for (int i=0;i<n-1;++i)
	{
		int cu=v[i];
		int r=1;
		mak.clear();
		/*for (int j=1;j<=n;++j)
		{
			cout<<j<<": ";
			for (auto x: ch[j]) cout<<x<<' ';
			cout<<endl;
		}*/
		while (1)
		{
			int cen=getCent(r);
			//cout<<r<<' '<<cen<<' '<<ord.size()<<endl;
			if (ord.size()==1)
			{
				ch[cen].pb(cu);
				ch[cu].pb(cen);
				break;
			}
			if (ch[cen].size()==1)
			{
				if (ask(cu,ch[cen][0],cen)==1)
				{
					r=ch[cen][0];
					makni(r,cen);
					continue;
				}
				else
				{
					ch[cen].pb(cu);
					ch[cu].pb(cen);
					break;
				}
			}
			if (ch[cen].size()==2)
			{
				if (ask(cu,ch[cen][0],cen)==1)
				{
					r=ch[cen][0];
					makni(r,cen);
					continue;
				}
				else if (ask(cu,ch[cen][1],cen)==1)
				{
					r=ch[cen][1];
					makni(r,cen);
					continue;
				}
				else
				{
					ch[cen].pb(cu);
					ch[cu].pb(cen);
					break;
				}
			}
			if (ch[cen].size()==3)
			{
				int od=ask(cu,ch[cen][0],ch[cen][1]);
				if (od==0)
				{
					if (ask(cu,ch[cen][2],cen)==1)
					{
						r=ch[cen][2];
						makni(r,cen);
						continue;
					}
					else
					{
						ch[cen].pb(cu);
						ch[cu].pb(cen);
						break;
					}
				}
				else if (od==1)
				{
					r=ch[cen][0];
					makni(r,cen);
					continue;
				}
				else
				{
					r=ch[cen][1];
					makni(r,cen);
					continue;
				}
			}
			assert(0);
		}
		for (auto x: mak) ch[x.x].pb(x.y),ch[x.y].pb(x.x);
	}
	cout<<"!"<<endl;
	for (int i=1;i<=n;++i) for (auto x: ch[i]) if (x>i) cout<<i<<' '<<x<<endl;
}

