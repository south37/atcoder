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

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

ll powmod(ll x, ll n) { // like pow(x, n)
  ll r = 1;
  while (n) {
    if (n & 1) {
      r = r * x % MOD;
    }
    x = x * x % MOD;
    n >>= 1;
  }
  return r;
}

int main(int argc, char** argv) {
  string S;
  cin >> S;
  int K;
  cin >> K;
  int N = S.size();

  // Run Length Encoding
  // e.g. issii -> i1s2i2
  vector< pair<char, ll> > cnts;
  rep(i, N) {
    ll cnt = 1;
    while (i < N - 1 && S[i] == S[i+1]) {
      ++cnt;
      ++i;
    }
    cnts.emplace_back(S[i], cnt);
  }

  // For Debug
  // for (auto x : cnts) {
  //   cout << x.first << x.second;
  // }
  // cout << endl;

  if (cnts.size() == 1) {
    cout << cnts[0].second * K / 2 << endl;
  } else {
    if (cnts[0].first == cnts[cnts.size()-1].first) { // The chars of pre and suf are the same
      ll ans = 0;
      ans += cnts[0].second / 2;
      ans += cnts[cnts.size()-1].second / 2;
      ans += (cnts[0].second + cnts[cnts.size()-1].second) / 2 * (K-1);
      for (int i = 1; i < cnts.size() - 1; ++i) {
        ans += cnts[i].second / 2 * K;
      }
      cout << ans << endl;
    } else {
      ll ans = 0;
      for (auto x : cnts) {
        if (x.second > 1) {
          ans += x.second / 2;
        }
      }
      ans *= K;
      cout << ans << endl;
    }
  }
}
