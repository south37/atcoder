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

  ull n, K;
  cin >> n >> K;
  vector<ull> xs;
  vector<ull> ys;
  vector<ull> ds;
  vector<tuple<ull,ull,ull,ull,ull,ull>> boxes;
  rep(i, n) {
    ull x1,y1,d1,x2,y2,d2;
    cin >> x1 >> y1 >> d1 >> x2 >> y2 >> d2;
    boxes.emplace_back(x1,y1,d1,x2,y2,d2);
    xs.push_back(x1); xs.push_back(x2);
    ys.push_back(y1); ys.push_back(y2);
    ds.push_back(d1); ds.push_back(d2);
  }
  sort(all(xs));
  xs.erase(unique(all(xs)), xs.end());
  sort(all(ys));
  ys.erase(unique(all(ys)), ys.end());
  sort(all(ds));
  ds.erase(unique(all(ds)), ds.end());
  // printvec(xs);
  // printvec(ys);
  // printvec(ds);

  ull ans = 0;
  rep(i,xs.size()-1)rep(j,ys.size()-1)rep(k,ds.size()-1) {
    ull minX = xs[i], maxX = xs[i+1];
    ull minY = ys[j], maxY = ys[j+1];
    ull minD = ds[k], maxD = ds[k+1];

    ll cnt = 0;
    for (auto& box : boxes) {
      ull x1,y1,d1,x2,y2,d2;
      tie(x1,y1,d1,x2,y2,d2) = box;
      if ((x1 <= minX && maxX <= x2) && (y1 <= minY && maxY <= y2) && (d1 <= minD && maxD <= d2)) {
        ++cnt;
      }
    }
    if (cnt >= K) {
      ans += (maxX-minX)*(maxY-minY)*(maxD-minD);
    }
  }
  cout << ans << endl;
}
