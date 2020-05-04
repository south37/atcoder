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

// SqrtDecomposition.
const ull sqrtN = 1ll<<9;
struct SqrtDecomposition {
  ull N, K;
  vector<ull> data;
  vector<ull> bucketSum, bucketAdd;
  vector<bool> lazyFlag;
  vector<ull> lazyUpdate;

  SqrtDecomposition(ull n) : N(n) {
    K = (N + sqrtN - 1) / sqrtN;
    data.assign(K * sqrtN, 0ull);
    bucketSum.assign(K, 0ull);
    bucketAdd.assign(K, 0ull);
    lazyFlag.assign(K, false);
    lazyUpdate.assign(K, 0ull);
  }
  void eval(ull k) {
    if (lazyFlag[k]) {
      lazyFlag[k] = false;
      for (ull i = k * sqrtN; i < (k + 1) * sqrtN; ++i) {
        data[i] = lazyUpdate[k];
      }
    }
  }

  // [s, t)
  void add(ull s, ull t, ull x) {
    for (ull k = 0; k < K; ++k) {
      ull l = k * sqrtN, r = (k + 1) * sqrtN;
      if (r <= s || t <= l)
        continue;
      if (s <= l && r <= t) {
        bucketAdd[k] += x;
      } else {
        for (ull i = max(s, l); i < min(t, r); ++i) {
          data[i] += x;
          bucketSum[k] += x;
        }
      }
    }
  }
  // [s, t)
  void update(ull s, ull t, ull x) {
    for (ull k = 0; k < K; ++k) {
      ull l = k * sqrtN, r = (k + 1) * sqrtN;
      if (r <= s || t <= l)
        continue;
      if (s <= l && r <= t) {
        bucketSum[k] = x*sqrtN;
        bucketAdd[k] = 0ull;
        lazyFlag[k] = true;
        lazyUpdate[k] = x;
      } else {
        eval(k);
        for (ull i = l; i < r; ++i){
          data[i] = data[i] + bucketAdd[k];
        }
        bucketAdd[k] = 0;
        for (ull i = max(s, l); i < min(t, r); ++i) {
          data[i] = x;
        }
        ull &sumVal = bucketSum[k] = 0ull;
        for (ull i = l; i < r; ++i) {
          sumVal = sumVal + data[i];
        }
      }
    }
  }
  // [s, t)
  ull getSum(ull s, ull t) {
    ull sumVal = 0;
    for (ull k = 0; k < K; ++k) {
      ull l = k * sqrtN, r = (k + 1) * sqrtN;
      if (r <= s || t <= l)
        continue;
      if (s <= l && r <= t) {
        sumVal = sumVal + bucketSum[k] + bucketAdd[k]*sqrtN;
      } else {
        eval(k);
        for (ull i = max(s, l); i < min(t, r); ++i) {
          sumVal = sumVal + data[i] + bucketAdd[k];
        }
      }
    }
    return sumVal;
  }
};

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ull n, m;
  cin >> n >> m;
  SqrtDecomposition rsq(n+1);

  ull ans = 0;
  ull pre = 0;
  rep(i,m) {
    ull t,l,r;
    cin >> t >> l >> r;

    rsq.add(1,n+1,t-pre);
    ans += rsq.getSum(l,r+1);
    rsq.update(l,r+1,0);
    pre=t;
  }
  cout << ans << endl;
}
