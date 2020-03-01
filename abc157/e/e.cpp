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

// Segment Tree
// template <typename T>
class SegTree {
public:
  SegTree(ll _n, string& s) {
    n = 1;
    while (n < _n) { n *= 2; }
    dat = vector<vector<int>>(2 * n - 1, vector<int>(26));
    // Initialize dat by s
    rep(i, s.size()) {
      update(i, s[i]);
    }
  }

  void update(int k, char a) {
    k += n - 1;
    dat[k] = vector<int>(26);
    dat[k][a-'a'] = 1; // set 1 to position
    // cout <<"update: ";
    // printvec(dat[k]);

    while (k > 0) {
      k = (k - 1) / 2;
      // NOTE: We need to insert a
      // dat[k][a-'a'] = 1;

      vector<int>& l = dat[k * 2 + 1];
      vector<int>& r = dat[k * 2 + 2];
      dat[k] = vector<int>(26); // clear.
      rep(i, 26) {
        if (l[i] == 1) {
          dat[k][i] = 1;
        }
        if (r[i] == 1) {
          dat[k][i] = 1;
        }
      }
    }
  }

  // Calculate the min of [a, b)
  vector<int> query(int a, int b) {
    return _query(a, b, 0, 0, n);
  }

  // Calculate the min of [a, b)
  // k is the index (dat[k]). This is matched to [l, r)
  vector<int> _query(int a, int b, int k, int l, int r) {
    // The intersection of [a, b) and [r, l) is blank.
    if (r <= a || b <= l) { return vector<int>(26); }

    if (a <= l && r <= b) {  // [r, l) is completely included in [a, b)
      return dat[k];
    } else {
      vector<int> vl = _query(a, b, k * 2 + 1, l, (l + r) / 2);
      vector<int> vr = _query(a, b, k * 2 + 2, (l + r) / 2, r);
      // cout << "vl: "; printvec(vl);
      // cout << "vr: "; printvec(vr);

      vector<int> res(26);
      rep(i, 26) {
        if (vl[i] == 1) {
          res[i] = 1;
        }
        if (vr[i] == 1) {
          res[i] = 1;
        }
      }
      return res;
    }
  }

private:
  int n; // The size of source data. The power of 2.
  vector<vector<int>> dat; // The data. The size if 2*n-1. The last n elements(dat[n..2*n-2]) are leaves(source data). The first n-1 elements are nodes.
  // we need vector<int>(26) for containing the information
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

  ll n;
  cin >> n;
  string s;
  cin >> s;
  ll q;
  cin >> q;
  SegTree st(n, s);
  rep(i, q) {
    ll t;
    cin >> t;
    if (t == 1) { // update
      // cout << "update" << endl;

      ll i;
      char c;
      cin >> i >> c;
      --i; // 0-indexed
      st.update(i, c);
    } else { // query. t == 2
      // cout << "query" << endl;

      ll l, r;
      cin >> l >> r;
      --l; --r; // 0-indexed
      vector<int> a = st.query(l, r+1);
      // printvec(a);

      if (a.size() == 0) {
        cout << 0 << endl;
        continue;
      }

      // count the 1
      ll ans = 0;
      rep(i, 26) {
        if (a[i] == 1) { ++ans; }
      }
      cout << ans << endl;;
    }
  }
}
