// copy. https://simezi-tan.hatenadiary.org/entry/20101207/1291681751

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string.h>
#include <set>
#include <stack>

using namespace std;

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

#define rep(i, n) for(ll i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()
#define sz(x) (ll)(x).size()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define vi vector<int>

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;
typedef vector<ll> vl;
typedef vector<P> vp;

const ll INF = 1e15;
const int inf = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

int n,m,l;
int d[100][100];
int t[1000],pl[1000];
vector<vi> e;

int p[2000]; bool v[2000];
bool rec(int s)
{
	if(s<0)return 1;
	for (int i : e[s])if(!v[i])
	{
		v[i]=1;
		if(rec(p[i]))return p[s]=i,p[i]=s,1;
	}
	return 0;
}

int main()
{
	while(scanf("%d%d%d",&n,&m,&l),n)
	{
		rep(i,n)rep(j,n)d[i][j]=i==j?0:inf;
		rep(i,m)
		{
			int a,b,c; scanf("%d%d%d",&a,&b,&c);
			d[a][b]=d[b][a]=c;
		}
		rep(k,n)rep(i,n)rep(j,n)d[i][j]=min(d[i][j],d[i][k]+d[k][j]);

		rep(i,l)scanf("%d%d",pl+i,t+i);
		e.clear(); e.resize(2*l);
		rep(i,l)rep(j,l)if(i!=j&&d[pl[i]][pl[j]]<=t[j]-t[i])
		e[i].pb(j+l),e[j+l].pb(i);

		int ans=l;
		rep(i,2*l)p[i]=-1;
		rep(i,l)
		{
			rep(j,2*l)v[j]=0;
			if(rec(i))ans--;
		}
		printf("%d\n",ans);
	}
	return 0;
}
