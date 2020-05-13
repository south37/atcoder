// ref. http://mayokoex.hatenablog.com/entry/2016/02/03/121148

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

// probability for l wins to r.
double calc_probe(double Rl, double Rr) {
  return 1/(1 + pow(10, (Rr-Rl)/400));
}

const ll K=10;
double dp[1<<K][K];

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  cout << setprecision(10) << fixed;

  ll K;
  cin >> K;
  vector<double> R(1<<K);
  rep(i,1<<K) {
    cin >> R[i];
  }
  rep(i,1<<K) {
    dp[i][0] = 1.0;
  }

  for (int k = 1; k <= K; ++k) {
    int p = 1<<k;
    rep(i,1<<K) {
      int maxi = (i+p)/p*p; // e.g. if p = 2 and i = 0, then maxi = 2.
      int mini = maxi-p;
      int med = (maxi+mini)/2;
      double prob = 0;
      if (i >= med) {
        for (int j = mini; j < med; ++j) {
          prob += dp[j][k-1] * calc_probe(R[i],R[j]);
        }
      } else {
        for (int j = med; j < maxi; ++j) {
          prob += dp[j][k-1] * calc_probe(R[i],R[j]);
        }
      }
      dp[i][k] = dp[i][k-1] * prob;
    }
  }

  rep(i,1<<K) {
    cout << dp[i][K] << endl;
  }
}
