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

  ll n, p;
  cin >> n >> p;
  string s;
  cin >> s;

  if (10%p == 0) { // 2, 5
    ll ans = 0;
    rep(i, n) {
      if ((s[i]-'0') % p == 0) {
        ans += i+1;
      }
    }
    cout << ans << endl;
    return 0;
  }

  vector<ll> d(n+1);
  ll ten = 1; // 10^k at digit k
  for (int i = n-1; i >= 0; --i) {
    int a = (s[i]-'0') * ten % p;
    d[i] = (d[i+1]+a) % p;
    ten *= 10; ten %= p;
  }
  vector<ll> cnt(p);
  // We want to find the count of pairs (i,j) where d[i] == d[j]. This means d[i] - d[j]=0 mod p.
  ll ans = 0;
  for (int i = n; i >= 0; --i) {
    ans += cnt[d[i]];
    ++cnt[d[i]];
  }
  cout << ans << endl;
}
