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
#define mp make_pair
#define pb push_back
#define eb emplace_back

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;
typedef vector<ll> vl;
typedef vector<P> vp;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<P> p; // pair of <left,right>
  vector<ll> ls;
  rep(i,n) {
    ll x,r;
    cin >> x >> r;
    p.emplace_back(x-r,x+r);
    ls.push_back(x-r);
  }

  sort(all(ls));
  ls.erase(unique(all(ls)), ls.end());
  map<ll,ll> mp; // left => idx
  rep(i,ls.size()) {
    mp[ls[i]] = i;
  }

  //printvec(ls);
  //printmap(mp);

  vector<P> rs; // pair of <right,-index>. use -index to make decreasing order in index when r is same.
  rep(i,n) {
    ll r = p[i].second;
    ll idx = mp[p[i].first];
    rs.emplace_back(-r,-idx);
  }
  sort(all(rs));

  // rep(i,n) {
  //   cout << p[i].first << "," << p[i].second << endl;
  // }
  // rep(i,n) {
  //   cout << - rs[i].first << "," << - rs[i].second << endl;
  // }

  vector<ll> dp;
  // Here, calculate LIS.
  rep(i,n) {
    ll j = -rs[i].second;
    auto idx = lower_bound(all(dp), j) - dp.begin();
    if (idx == dp.size()) { // j is larger than all values in dp.
      dp.push_back(j);
    } else {
      dp[idx] = j;
    }
  }
  cout << dp.size() << endl;
}
