// ref. https://www.youtube.com/watch?v=JYLI4mZH-p8

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
  cout << setprecision(10) << fixed;

  ll n, m;
  cin >> n >> m;
  vector<vector<ll>> g(n);
  vector<vector<ll>> revG(n);
  rep(i, m) {
    int s, t;
    cin >> s >> t;
    --s; --t; // 0-indexed
    g[s].push_back(t);
    revG[t].push_back(s);
  }

  vector<double> en(n); // en[i] .. expected valud from i.
  vector<double> pn(n); // pn[i] .. probability from i.
  // en[n-1] = 0;
  pn[n-1] = 1;
  for (int v = n-2; v >= 0; --v) {
    int deg = g[v].size();
    for (int u : g[v]) {
      en[v] += en[u];
      pn[v] += pn[u];
    }
    en[v] /= deg; en[v] += 1;
    pn[v] /= deg;
  }
  // Here, g is DAG, so all pn[i] = 1.

  vector<double> e1(n); // e1[i] .. expected valud to i.
  vector<double> p1(n); // p1[i] .. probability to i.
  p1[0] = 1;
  for (int v = 1; v < n; ++v) {
    for (int u : revG[v]) {
      e1[v] += (e1[u]+1)/g[u].size();
      p1[v] += p1[u]/g[u].size();
    }
  }

  double ans = en[0];
  for (int v = 0; v < n-1; ++v) {
    int deg = g[v].size();
    if (deg == 1) { continue; } // skip 1-degree
    double now = en[0];
    // 1/deg -> 0
    {
      double p = 1.0/deg;
      for (int u : g[v]) {
        double s = e1[v] * pn[u];
        s += p1[v]*en[u];
        s += p1[v]*pn[u];
        s *= p;
        now -= s;
      }
    }
    // 0 -> 1/(deg-1)
    {
      double p = 1.0/(deg-1);
      for (int u : g[v]) {
        double s = e1[v] * pn[u];
        s += p1[v]*en[u];
        s += p1[v]*pn[u];
        s *= p;
        now += s;
      }
    }

    for (int u : g[v]) {
      // 1/(deg-1) -> 0
      double p = 1.0/(deg-1);
      double s = e1[v] * pn[u];
      s += p1[v]*en[u];
      s += p1[v]*pn[u];
      s *= p;
      ans = min(ans, now-s);
    }
  }
  cout << ans << endl;
}
