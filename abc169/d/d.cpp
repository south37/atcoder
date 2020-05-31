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

  vector<ll> dp(100);
  dp[0] = 0;
  for (int i = 1; i < 100; ++i) {
    dp[i] = i*(i+1)/2;
  }
  // printvec(dp);

  ll n;
  cin >> n;
  map<ll,ll> fs; // count of prime factors
  {
    ll i = 2;
    while (i*i <=n) {
      if (n%i == 0) {
        while (n%i == 0) {
          n /= i;
          ++fs[i];
        }
      }
      ++i;
    }
    if (n>1) {
      ++fs[n];
    }
  }

  ll ans = 0;
  for (auto& p : fs) {
    ll cnt = p.second;

    ll i = upper_bound(all(dp), cnt) - dp.begin();
    ans += i-1;

    // cout << "cnt:" << cnt << endl;
    // cout << "i:" << i << endl;

    // ll tot = 0;
    // ll i = 1;
    // while (tot + i <= cnt) {
    //   tot += i;
    //   ++i;
    // }
    // // Here, i is available
    // ans += i-1;
  }

  cout << ans << endl;
}
