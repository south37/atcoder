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

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  vector<ll> ys;
  vector<tuple<ll,ll,ll,ll>> rectangles;
  ll n;
  cin >> n;
  rep(i,n) {
    ll x1,y1,x2,y2;
    cin >> x1 >> y1 >> x2 >> y2;
    rectangles.emplace_back(x1,y1,x2,y2);
    ys.push_back(y1);
    ys.push_back(y2);
  }
  sort(all(ys)); // increasing order
  ys.erase(unique(all(ys)), ys.end()); // uniquify

  ll ans = 0;
  rep(i, ys.size()-1) {
    ll miny = ys[i];
    ll maxy = ys[i+1];
    vector<P> xs; // <x,type>. type = 0 .. open, type = 1 .. close.
    for (auto& rec : rectangles) {
      ll x1,y1,x2,y2;
      tie(x1,y1,x2,y2) = rec;
      if (y1 <= miny && maxy <= y2) { // rec is effective.
        xs.emplace_back(x1, 0); // open
        xs.emplace_back(x2, 1); // close
      }
    }
    sort(all(xs));
    ll dx = 0;
    ll cnt = 0; // the count of rectangle in this range.
    ll pre = 0; // the x at opening.
    for (auto& p : xs) {
      if (p.second == 0) { // open
        if (cnt == 0) {
          pre = p.first;
        }
        ++cnt;
      } else { // p.second == 1. close
        if (cnt == 1) {
          dx += p.first - pre;
        }
        --cnt;
      }
    }
    ans += dx*(maxy-miny);
  }
  cout << ans << endl;
}
