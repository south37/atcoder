// ref. https://img.atcoder.jp/tenka1-2017/editorial.pdf

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
#define fr first
#define sc second
#define mp make_pair
#define pb push_back

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, k;
  cin >> n >> k;
  vector<P> ps(n);
  rep(i, n) {
    cin >> ps[i].first >> ps[i].second;
  }

  vector<ll> ks;
  ks.push_back(k);
  rep(i, 30) {
    if (k&(1ll<<i)) { // i-bit is 1 in k
      ll nk = k; // 0 at i, 1 at [0, i)
      nk &= ~(1ll<<i);
      rep(j, i) {
        nk |= 1ll<<j;
      }
      ks.push_back(nk);
    }
  }

  ll ans = 0;
  for (ll nk : ks) {
    ll now = 0;
    for (auto&p : ps) {
      if ((nk|p.first) == nk) { // p.first is in nk
        now += p.second;
      }
    }
    ans = max(ans, now);
  }
  cout << ans << endl;
}
