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

  ll n;
  cin >> n;
  string s;
  cin >> s;

  ll c = 0; // count of 1 at first state
  rep(i,n) {
    if (s[i] == '1') {
      ++c;
    }
  }

  auto flip = [&](ll i) {
    if (s[i] == '1') { s[i] = '0';
    } else { s[i] = '1'; }
  };

  // calculate s
  // ll now = 0;
  // rep(i,n) {
  //   now *= 2;
  //   now += (s[i] - '0');
  // }
  // cout << "num: " << now << endl;

  // We necessary only under 16 bit of first number.
  rep(i,n) {
    // cout << s << endl;

    ll nc = c; // current c
    if (s[i] == '1') { // we flip i, so decrease c.
      --nc;
    } else {
      ++nc;
    }

    // flip
    flip(i);

    // Check 0
    bool isAllZero = true;
    rep(i,n) {
      if (s[i] != '0') {
        isAllZero = false;
        break;
      }
    }
    if (isAllZero) { // already 0
      flip(i); // revert
      cout << 0 << endl;
      continue;
    }

    ll now = 0;
    // use last 32 bit.
    // rep(j,n) {
    for (ll j = max(0ll, n-1-32); j < n; ++j) {
      now *= 2;
      now += (s[j] - '0');
      // cout << "n-1-j: " << n-1-j << endl;
      // cout << "s[n-1-j]:" << s[n-1-j] << endl;
    }
    // Here, this value represent value of last 16bit

    // cout << "i: " << i << endl;
    // cout << "c: " << c << endl;
    // cout << "nc: " << nc << endl;
    // cout << "now: " << now << endl;

    // We simulat from "now".
    ll cnt = 0;
    ++cnt;
    now %= nc; // decrease.

    {
      while (now > 0) {
        ++cnt;
        now %= __builtin_popcountll(now);
      }
    }
    cout << cnt << endl;

    // revert
    flip(i);
  }

  // rep(i,10) {
  //   if (i==0) { continue; }

  //   cout << "i: " << i << endl;
  //   // simulate by i
  //   {
  //     ll now = 0;

  //     ll j = i;
  //     while (j > 0) {
  //       ++now;
  //       j %= __builtin_popcountll(j);
  //       // cout << "j: " << j << endl;
  //     }
  //     cout << now << endl;
  //   }
  // }
}
