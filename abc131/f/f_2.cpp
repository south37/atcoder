#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string.h>
#include <set>

using namespace std;

#define COUT(x) cout << #x << " = " << (x) << " (L" << __LINE__ << ")" << endl

#define rep(i, n) for(ll i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

const ll V = 100010;

ll cnt[2]; // cnt[0]: x, cnt[1]: y
vector<bool> visited(V*2);
vector< vector<ll> > to(V*2);

void dfs(ll v) {
  if (visited[v]) { return; }
  visited[v] = true;
  ++cnt[v/V];
  for (ll u : to[v]) { dfs(u); }
}

int main(int argc, char** argv) {
  ll N;
  cin >> N;
  vector<P> vertices(N);
  map<ll, vector<ll> > X; // stores the group of vertices with same x
  map<ll, vector<ll> > Y; // stores the group of vertices with same y
  rep(i, N) {
    ll x, y;
    cin >> x >> y;
    y += V;
    to[x].push_back(y);
    to[y].push_back(x);
  }
  ll ans = 0;
  rep(i, V*2) {
    if (visited[i]) { continue; }
    cnt[0]=0; cnt[1]=0;
    dfs(i);
    ans += (ll)cnt[0] * cnt[1];
  }
  ans -= N;
  cout << ans << endl;
}
