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

const ll INF = 1e12;
const ll MOD = 1000000007;  // 1e9 + 7

ll dr[4] = { 1, -1, 0, 0 };
ll dc[4] = { 0, 0, 1, -1 };

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll h,w;
  cin >> h >> w;
  vector<vector<ll>> a(h, vector<ll>(w));
  rep(r,h)rep(c,w) {
    cin >> a[r][c];
  }

  vector<vector<ll>> ds(3, vector<ll>(h*w,INF));
  vector<ll> sts = { (h-1)*w, (h-1)*w+(w-1), w-1 }; // left-bottom, right-bottom, right-top

  rep(k,3) {
    vector<ll>& d = ds[k];
    ll s = sts[k];

    priority_queue<P, vector<P>, greater<P> > q;
    q.emplace(0, s);
    d[s] = 0;
    while (!q.empty()) {
      P p = q.top(); q.pop();
      ll dist = p.first;
      ll v = p.second;
      if (dist > d[v]) { continue; }
      rep(i,4) {
        ll r = v/w;
        ll c = v%w;
        ll nr = r+dr[i];
        ll nc = c+dc[i];
        if (nr < 0 || nr >= h || nc < 0 || nc >= w) { continue; }
        if (d[nr*w+nc] > dist + a[nr][nc]) {
          d[nr*w+nc] = dist + a[nr][nc];
          q.emplace(d[nr*w+nc], nr*w+nc);
        }
      }
    }
  }

  ll ans = INF;
  rep(i,h*w) {
    ll now = 0;
    rep(k,3) {
      now += ds[k][i];
    }
    ll r = i/w;
    ll c = i%w;
    now -= a[r][c]*2;
    chmin(ans, now);
  }
  cout << ans << endl;
}
