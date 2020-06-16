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
  vector<vector<bool>> ok(5005,vector<bool>(5005));

  vector<P> vs;
  rep(i,n) {
    ll x,y;
    cin >> x >> y;
    vs.emplace_back(x,y);
    ok[x][y] = true;
  }

  // cout << vs.size() << endl;

  ll ans = 0;
  rep(i,n)rep(j,i) {
    ll xi,yi,xj,yj;
    tie(xi,yi) = vs[i];
    tie(xj,yj) = vs[j];

    if (xi>xj) {
      swap(xi,xj);
      swap(yi,yj);
    }
    // Here, xi <= xj

    P vec(xj-xi,yj-yi); // i->j
    P vec2(-vec.second, vec.first); // rotated 90deg from vec

    // v3 .. i + vec2
    P v3(xi+vec2.first,yi+vec2.second);
    // v4 .. j + vec2
    P v4(xj+vec2.first,yj+vec2.second);

    if (v3.first < 0 || v3.first > 5000) { continue; } // invalid
    if (v3.second < 0 || v3.second > 5000) { continue; } // invalid
    if (v4.first < 0 || v4.first > 5000) { continue; } // invalid
    if (v4.second < 0 || v4.second > 5000) { continue; } // invalid

    if (ok[v3.first][v3.second] && ok[v4.first][v4.second]) {
      ll now = vec.first*vec.first + vec.second*vec.second;
      chmax(ans,now);
    }
  }
  cout << ans << endl;
}
