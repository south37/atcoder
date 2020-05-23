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

template<class T> void printvec(const vector<T>& v) {
  for (auto x : v) { cout << x << " "; }
  cout << endl;
}
template<class T> void printtree(const vector< vector<T> >& tree) {
  for (long long i = 0; i < tree.size(); ++i) {
    cout << i + 1 << ": "; printvec(tree[i]);
  }
}
template<class T, class U> void printmap(const map<T, U>& mp) {
  for (auto x : mp) { cout << x.first << "=>" << x.second << endl; }
}

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

#define rep(i, n) for(ll i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()
#define sz(x) (ll)(x).size()
#define fr first
#define sc second
#define pb push_back
#define eb emplace_back

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;
typedef vector<ll> vl;
typedef vector<P> vp;

const ll INF = 1e18;
const ll MOD = 1000000007;  // 1e9 + 7

map<ll,ll> mp; // dp map
ll n,a,b,c,d;
vector<ll> costs;
vector<ll> nums = { 2, 3, 5 };

ll dfs(ll n) {
  if (n == 0) { return 0; }
  if (n == 1) { return d; }
  if (mp.find(n) != mp.end()) {
    return mp[n];
  }

  // Here, we skip
  ll res = INF;
  // try D(+/- 1)
  if (n < res/d) { // n*d < res
    chmin(res, n*d);
  }
  // try A,B,C
  rep(i,3) {
    ll cost = costs[i];
    ll num  = nums[i];
    {
      // floor
      ll t = n/num; // target
      ll now = dfs(t) + cost;
      now += abs(n-(num*t))*d;
      chmin(res,now);
    }
    {
      // ceil
      ll t = (n+num-1)/num; // target
      ll now = dfs(t) + cost;
      now += abs(n-(num*t))*d;
      chmin(res,now);
    }
  }
  return mp[n] = res;
}

void solve() {
  cin >> n >> a >> b >> c >> d;
  costs = { a, b, c };
  mp.clear();
  // printvec(costs);
  // printvec(nums);
  // printmap(mp);
  cout << dfs(n) << endl;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll t;
  cin >> t;
  rep(i,t) {
    solve();
  }
}
