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

ll ans;
ll n, m, q;
vector<tuple<ll,ll,ll,ll>> queries;

void backtrack(vector<ll>& now, ll i) {
  if (i == n) {
    ll score = 0;
    for (auto& query : queries) {
      ll a, b, c, d;
      tie(a, b, c, d) = query;
      if (now[b] - now[a] == c) {
        score += d;
      }
    }
    chmax(ans, score);
    return;
  }

  ll pre = now[i]; // prev value
  for (ll v = pre; v <= m; ++v) { // scan value in [pre, m]
    now.push_back(v);
    backtrack(now, i+1);
    now.pop_back();
  }
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  cin >> n >> m >> q;

  rep(iter,q) {
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    --a; --b; // 0-indexed
    queries.push_back(tuple<ll,ll,ll,ll>(a,b,c,d));
  }

  vector<ll> now;
  now.push_back(1); // start from 1.
  backtrack(now, 0);
  cout << ans << endl;
}
