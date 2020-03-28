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

  ll n, d, a;
  cin >> n >> d >> a;
  vector<P> p(n);
  rep(i, n) {
    cin >> p[i].first >> p[i].second;
  }
  sort(all(p));

  ll ans = 0;
  ll tot = 0; // total damge at current position
  queue<P> q;
  rep(i, n) {
    ll x = p[i].first;
    ll h = p[i].second;

    // Decrease the damage which is in the out of range.
    while (!q.empty() && q.front().first < x) {
      tot -= q.front().second;
      q.pop();
    }

    h -= tot;
    if (h > 0) { // remaining
      ll num = (h+a-1)/a; // the round up of h/a
      ans += num;
      ll damage = num*a;
      tot += damage;
      q.emplace(x+d*2, damage); // add damage which is effectve in [x, x+d*2]
    }
  }

  cout << ans << endl;
}
