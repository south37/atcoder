// ref. http://luzhiled.hatenablog.com/entry/2017/10/02/020704#Swapping-Characters-%E6%96%87%E5%AD%97%E5%88%97%E3%82%B9%E3%83%AF%E3%83%83%E3%83%97

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

// const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

// BIT (Fenwick Tree) with 0-indexed query
// https://youtu.be/lyHk98daDJo?t=7960
template<typename T>
struct BIT {
  int n;
  vector<T> d;
  BIT(int n=0) : n(n), d(n+1) {}
  void add(int i, T x=1) {
    i++; // 0-indexed to 1-indexed
    for (; i <= n; i += i&-i) {
      d[i] += x;
    }
  }
  // The sum of [0, i]
  T sum(int i) {
    i++; // 0-indexed to 1-indexed
    T x = 0;
    for (; i; i -= i&-i) {
      x += d[i];
    }
    return x;
  }
  // The sum of [l, r)
  T sum(int l, int r) {
    assert(l <= r);
    if (r == 0) { return 0; } // Here, l == 0 && r == 0
    if (l == 0) { return sum(r-1); }
    return sum(r-1) - sum(l-1);
  }
};

// int main(int argc, char** argv) {
//   int N;
//   cin >> N;
//   vector<int> v(N);
//   rep(i, N) {
//     cin >> v[i];
//   }
//
//   BIT<int> bit(N);
//   rep(i, N) {
//     bit.add(i, v[i]);
//   }
//
//   cout << bit.sum(4) << endl; // sum of [0,4]. 24
//   cout << bit.sum(9) << endl; // sum of [0,9]. 55
// }

const char INF = 'z' + 1;

// Segment Tree
template <typename T>
class SegTree {
public:
  SegTree(int _n) {
    n = 1;
    while (n < _n) { n *= 2; }
    dat = vector<T>(2 * n - 1, pair<char,int>(INF,-1));
  }

  void update(int k, T a) {
    k += n - 1;
    dat[k] = a;
    while (k > 0) {
      k = (k - 1) / 2;
      dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
    }
  }

  // Calculate the min of [a, b)
  T query(int a, int b) {
    return _query(a, b, 0, 0, n);
  }

  // Calculate the min of [a, b)
  // k is the index (dat[k]). This is matched to [l, r)
  T _query(int a, int b, int k, int l, int r) {
    // The intersection of [a, b) and [r, l) is blank.
    if (r <= a || b <= l) { return pair<char,int>(INF,-1); }

    if (a <= l && r <= b) {  // [r, l) is completely included in [a, b)
      return dat[k];
    } else {
      T vl = _query(a, b, k * 2 + 1, l, (l + r) / 2);
      T vr = _query(a, b, k * 2 + 2, (l + r) / 2, r);
      return min(vl, vr);
    }
  }

private:
  int n; // The size of source data. The power of 2.
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

  string s;
  cin >> s;
  int k;
  cin >> k;
  int n = s.size();

  BIT<int> bit(n+5);
  rep(i,n) {
    bit.add(i,1);
  }

  SegTree<pair<char,int>> st(n+5);
  rep(i,n) {
    st.update(i, pair<char,int>(s[i],i));
  }

  // Return true when bit.sum(m) >= k
  auto check = [&](int m) {
    return bit.sum(0,m) > k;
  };

  string ans;
  while (k > 0 && ans.size() < n) {
    // Here, pick smallest one. [f,t]
    int l = -1, r = n;
    while (r-l > 1) {
      int m = (l+r)/2;
      if (check(m)) {
        r = m;
      } else {
        l = m;
      }
    }
    // Here, r = smallest true. search in [0,r)
    pair<char,int> p = st.query(0,r);
    ans += p.first;
    st.update(p.second,pair<char,int>(INF,-1));

    int cost = bit.sum(0,p.second); // sum of [0,p.second)
    k -= cost;
    bit.add(p.second,-1);

    // cout << "r: " << r << endl;
    // cout << "p: " << p.first << "," << p.second << endl;
    // cout << "k: " << k << endl;
    // cout << "cost: " << cost << endl;
    // cout << "ans: " << ans << endl;
  }

  if (ans.size() < n) { // remaining exist
    rep(i,n) {
      if (bit.sum(i,i+1)) {
        ans += s[i];
      }
    }
  }

  cout << ans << endl;
}
