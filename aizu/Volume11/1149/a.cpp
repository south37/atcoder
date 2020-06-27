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

  while (true) {
    ll n,w,h;
    cin >> n >> w >> h;
    if (n == 0 && w == 0 && h == 0) { break; }

    auto cut = [&](int wi, int hi, int s) {
      // cout << "(wi,hi,s):" << wi << "," << hi << "," << s << endl;

      vector<P> ret(2); // pair of <width,height>
      s %= (2*wi+2*hi);
      if (0 <= s && s <= wi) { // cut from top
        ret[0] = P(s,hi);
        ret[1] = P(wi-s,hi);
      } else if (wi <= s && s <= wi+hi) { // cut from right
        s -= wi;
        ret[0] = P(wi,s);
        ret[1] = P(wi,hi-s);
      } else if (wi+hi <= s && s <= 2*wi+hi) { // cut from bottom
        s -= wi+hi;
        ret[0] = P(s,hi);
        ret[1] = P(wi-s,hi);
      } else { // cut from left
        s -= 2*wi+hi;
        ret[0] = P(wi,s);
        ret[1] = P(wi,hi-s);
      }
      if (ret[0].first*ret[0].second > ret[1].first*ret[1].second) {
        swap(ret[0],ret[1]);
      }

      // cout << "ret[0]:" << ret[0].first << "," << ret[0].second << endl;
      // cout << "ret[1]:" << ret[1].first << "," << ret[1].second << endl;
      return ret;
    };

    vector<P> a(1); // cakes. pair of <width, height>
    a[0] = P(w,h);
    rep(i,n) {
      ll p, s;
      cin >> p >> s;
      --p; // 0-indexed
      ll wi = a[p].first;
      ll hi = a[p].second;
      vector<P> ps = cut(wi,hi,s);
      a.push_back(ps[0]);
      a.push_back(ps[1]);

      vector<P> b;
      rep(i,a.size()) {
        if (i == p) { continue; }
        b.push_back(a[i]);
      }
      swap(a,b);

      // For Debug
      // rep(i,a.size()) {
      //   cout << a[i].first*a[i].second;
      //   if (i < a.size()-1) {
      //     cout << " ";
      //   }
      // }
      // cout << endl;
    }

    vector<ll> ans;
    for (auto& p : a) {
      ans.push_back(p.first*p.second);
    }
    sort(all(ans));
    rep(i,ans.size()) {
      cout << ans[i];
      if (i < ans.size()-1) {
        cout << " ";
      }
    }
    cout << endl;
  }
}
