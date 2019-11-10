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

const ll INF = 1e15;
const ll MOD = 1000000007;  // 1e9 + 7

// Segment Tree
template <typename T>
class SegTree {
public:
  SegTree(ll _n) {
    n = 1;
    while (n < _n) { n *= 2; }
    dat = vector<T>(2 * n - 1, INF);
  }

  void update(ll k, T a) {
    k += n - 1;
    dat[k] = a;
    while (k > 0) {
      k = (k - 1) / 2;
      dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
    }
  }

  // Calculate the min of [a, b)
  T query(ll a, ll b) {
    return _query(a, b, 0, 0, n);
  }

  // Calculate the min of [a, b)
  // k is the index (dat[k]). This is matched to [l, r)
  T _query(ll a, ll b, ll k, ll l, ll r) {
    // The intersection of [a, b) and [r, l) is blank.
    if (r <= a || b <= l) { return INF; }

    if (a <= l && r <= b) {  // [r, l) is completely included in [a, b)
      return dat[k];
    } else {
      ll vl = _query(a, b, k * 2 + 1, l, (l + r) / 2);
      ll vr = _query(a, b, k * 2 + 2, (l + r) / 2, r);
      return min(vl, vr);
    }
  }

private:
  ll n; // The size of source data. The power of 2.
  vector<T> dat; // The data. The size if 2*n-1. The last n elements(dat[n..2*n-2]) are leaves(source data). The first n-1 elements are nodes.
};

// int main(int argc, char** argv) {
//   int arr[] = { 1, 3, 2, 7, 9, 11 };
//   int n = 6;
//
//   SegTree<int> st(n);
//   rep(i, n) {
//     st.update(i, arr[i]);
//   }
//
//   cout << st.query(1, 5) << endl;
//   cout << st.query(0, 4) << endl;
//   cout << st.query(3, 5) << endl;
// }

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, m;
  cin >> n >> m;
  vector< vector<ll> > graph(m);
  vector<ll> s; // starts
  vector<ll> t; // goals

  vector<triple> ops;
  rep(i, m) {
    ll l, r, c;
    ++r; // [l, r)
    cin >> l >> r >> c;
    ops.emplace_back(l, r, c);
  }
  sort(all(ops));

  SegTree<ll> rmq(n+1);
  rmq.update(1, 0);
  rep(i, m) {
    ll l, r, c;
    tie(l, r, c) = ops[i];
    //cout << "(l, r, c)=("<<l<<","<<r<<","<<c<<")"<<endl;
    ll new_c = c + rmq.query(l, r);
    //cout << "new_c="<<new_c<<endl;
    if (rmq.query(r, r+1) > new_c) {
      //cout << "rmq.query(r, r+1)="<<rmq.query(r, r+1)<<endl;
      rmq.update(r, new_c);
      //cout << "rmq.query(r, r+1)="<<rmq.query(r, r+1)<<endl;
    }
  }

  ll ans = rmq.query(n, n+1);
  if (ans >= INF) {
    cout << -1 << endl;
    return 0;
  } else {
    cout << ans << endl;
  }
}
