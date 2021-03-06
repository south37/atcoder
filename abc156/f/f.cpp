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

int divceil(int a, int b) {
  return (a+b-1)/b;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll k, q;
  cin >> k >> q;
  vector<int> d(k);
  rep(i, k) {
    cin >> d[i];
  }
  rep(iq, q) {
    int n, x, m;
    cin >> n >> x >> m;
    ll last = x, eq = 0;
    rep(i, k) {
      // repeated d's length is n-1. calculate the each contribution
      ll num = divceil((n-1)-i, k);
      last += (d[i]%m)*num;
      if ((d[i]%m) == 0) {
        eq += num;
      }
    }
    // last/m - x/m .. the count of (aj mod m) > (aj+1 mod m)
    // eq .. the counf of (aj mod m) == (aj+1 mod m)
    ll ans = (n-1) - (last/m - x/m) - eq;
    cout << ans << endl;
  }
}
