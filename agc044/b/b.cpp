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

ll dr[4] = { 1, -1, 0, 0 };
ll dc[4] = { 0, 0, 1, -1 };

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<vector<ll>> dp(n,vector<ll>(n));
  rep(r,n)rep(c,n) {
    ll minR = min(r,n-1-r);
    ll minC = min(c,n-1-c);
    dp[r][c] = min(minR,minC);
  }

  vector<vector<bool>> isBlank(n,vector<bool>(n));

  // printtree(dp);

  ll ans = 0;
  rep(iter,n*n) {
    ll p;
    cin >> p;
    --p;
    ll r = p/n;
    ll c = p%n;
    ans += dp[r][c];

    // Update (r,c)
    isBlank[r][c] = true;

    // Update by BFS
    P s = P(r,c);
    queue<P> q;
    q.push(s);
    while (!q.empty()) {
      P p = q.front(); q.pop();
      ll r = p.first;
      ll c = p.second;
      ll newCost; // candidate cost for surroundings
      if (isBlank[r][c]) {
        newCost = dp[r][c];
      } else { // is not blank
        newCost = dp[r][c] + 1; // 1 by (r,c)
      }
      // Update surroundings
      rep(i,4) {
        ll nr = r+dr[i];
        ll nc = c+dc[i];
        if (nr < 0 || nr >= n || nc < 0 || nc >= n) { continue; }
        if (dp[nr][nc] > newCost) {
          dp[nr][nc] = newCost;
          q.emplace(nr,nc);
        }
      }
    }

    // cout << "(r,c):" << r << "," << c << endl;
    // printtree(dp);
  }
  cout << ans << endl;
}
