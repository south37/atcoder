// ref. https://img.atcoder.jp/agc034/editorial.pdf

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

template<typename T, typename Compare = less<T>, typename RCompare = greater<T>>
struct PrioritySumStructure {
  size_t k;
  T sum;

  priority_queue<T, vector<T>, Compare> in, d_in;
  priority_queue<T, vector<T>, RCompare> out, d_out;

  PrioritySumStructure(int k) : k(k), sum(0) {}

  void modify() {
    while(in.size() - d_in.size() < k && !out.empty()) {
      auto p = out.top();
      out.pop();
      if(!d_out.empty() && p == d_out.top()) {
        d_out.pop();
      } else {
        sum += p;
        in.emplace(p);
      }
    }
    while(in.size() - d_in.size() > k) {
      auto p = in.top();
      in.pop();
      if(!d_in.empty() && p == d_in.top()) {
        d_in.pop();
      } else {
        sum -= p;
        out.emplace(p);
      }
    }
    while(!d_in.empty() && in.top() == d_in.top()) {
      in.pop();
      d_in.pop();
    }
  }

  T query() const {
    return sum;
  }

  void insert(T x) {
    in.emplace(x);
    sum += x;
    modify();
  }

  void erase(T x) {
    assert(size());
    if(!in.empty() && in.top() == x) {
      sum -= x;
      in.pop();
    } else if(!in.empty() && RCompare()(in.top(), x)) {
      sum -= x;
      d_in.emplace(x);
    } else {
      d_out.emplace(x);
    }
    modify();
  }

  void set_k(size_t kk) {
    k = kk;
    modify();
  }

  size_t get_k() const {
    return k;
  }

  size_t size() const {
    return in.size() + out.size() - d_in.size() - d_out.size();
  }
};

template<typename T>
using MaximumSum = PrioritySumStructure<T, greater<T>, less<T>>;

template<typename T>
using MinimumSum = PrioritySumStructure< T, less<T>, greater<T>>;

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, x;
  cin >> n >> x;
  vector<ll> b(n), l(n), u(n);
  ll loss = 0; // sum of lowest
  rep(i,n) {
    cin >> b[i] >> l[i] >> u[i];
    loss += b[i]*l[i];
  }

  // Return cost when use ai at i.
  auto di = [&](ll i, ll ai) {
    ll ret = 0;
    ret += l[i]*min(b[i],ai);
    if (ai > b[i]) {
      ret += u[i]*(ai-b[i]);
    }
    return ret;
  };

  vector<P> ps; // pair of <di(i,x), i>
  rep(i,n) {
    ps.emplace_back(di(i,x), i);
  }
  sort(all(ps));
  reverse(all(ps));
  // Here, ps is sorted in decreasing order

  vector<ll> s(n+1); // cummulative sum of ps[j].first in [0,i)
  rep(i,n) {
    s[i+1] = s[i] + ps[i].first;
  }

  // return true when A can win with k.
  auto check = [&](ll k) {
    ll q = k/x;
    ll r = k-q*x;
    rep(i,n) {
      P p = ps[i];
      ll idx = p.second;

      ll now = -loss; // now .. D
      if (i < q) { // add sum of [0,q+1) except for idx.
        now += s[q+1];
        now -= p.first;
      } else {
        now += s[q]; // add sum of [0,q)
      }
      now += di(idx,r);
      if (now >= 0) { return true; }
    }
    return false;
  };

  ll lt = -1, rt = n*x;
  while (rt-lt > 1) {
    ll m = (lt+rt)/2;
    if (check(m)) {
      rt = m;
    } else {
      lt = m;
    }
  }
  // Here, r is min ok.
  cout << rt << endl;
}
