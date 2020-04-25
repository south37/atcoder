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

  string s;
  string t;
  cin >> s;
  cin >> t;
  ll n = s.size();
  ll m = t.size();
  // cout << n << endl;
  // cout << m << endl;
  vector<ll> ss(n+1);
  vector<ll> tt(m+1);
  rep(i, n) {
    ll diff = (s[i] == 'A') ? 1 : 2;
    ss[i+1] = ss[i] + diff;
  }
  rep(i, m) {
    ll diff = (t[i] == 'A') ? 1 : 2;
    tt[i+1] = tt[i] + diff;
  }
  // printvec(ss);
  // printvec(tt);
  ll q;
  cin >> q;
  rep(iter, q) {
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    --a; --b; --c; --d;
    ll sn = ss[b+1] - ss[a]; // [a, b+1)
    ll tn = tt[d+1] - tt[c]; // [a, b+1)
    if (abs(sn-tn)%3 == 0) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
}
