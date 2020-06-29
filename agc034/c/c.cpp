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
  vector<ll> ord;
  ll loss = 0; // sum of lowest
  rep(i,n) {
    cin >> b[i] >> l[i] >> u[i];
    loss += b[i]*l[i];
    ord.push_back(i);
  }
  sort(all(ord), [&](const ll a, const ll b) {
    return l[a] > l[b];
  });
  // Here, idx in ord are sorted in decreasing order of l[idx].

  // sum is sum of left and right. If sum > b[idx], then larger than loss by
  // u[idx]*(sum-b[idx]). Else, smaller than loss by l[idx]*(b[idx]-sum).
  auto get_cost = [&](ll idx, ll sum) {
    ll ret = 0;
    // if sum > b[idx] then (b[idx], sum-b[idx])
    //                 else (sum,    0)
    ret += l[idx]*min(sum, b[idx]);
    ret += u[idx]*max(0ll, sum-b[idx]);
    return ret;
  };

  MaximumSum<ll> maxsum(0);
  rep(i,n) {
    maxsum.insert(get_cost(i,x));
  }
  auto check = [&](ll sum) {
    ll v = sum/x; // required elements.
    maxsum.set_k(v);
    for (ll i : ord) {
      maxsum.erase(get_cost(i,x));
      bool now = maxsum.query() + get_cost(i, sum%x) >= loss;
      maxsum.insert(get_cost(i,x)); // revert state
      if (now) { return true; }
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
