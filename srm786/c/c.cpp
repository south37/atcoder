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

const ll INF = 1e12;
const ll MOD = 1812447359; // 2e9

// Mod int
// cf. https://www.youtube.com/watch?v=1Z6ofKN03_Y
struct mint {
  ll x;
  mint(ll x = 0) : x((x + MOD) % MOD) {}
  mint& operator+= (const mint a) {
    if ((x += a.x) >= MOD) x %= MOD;
    return *this;
  }
  mint operator+ (const mint a) const {
    mint res(*this);
    return res += a;
  }
  mint& operator-= (const mint a) {
    if ((x += MOD - a.x) >= MOD) x %= MOD;
    return *this;
  }
  mint operator- (const mint a) const {
    mint res(*this);
    return res -= a;
  }
  mint& operator*= (const mint a) {
    (x *= a.x) %= MOD;
    return *this;
  }
  mint operator* (const mint a) const {
    mint res(*this);
    return res *= a;
  }
  mint pow(ll t) const {
    if (!t) { return 1; }
    mint a = pow(t >> 1);
    a *= a;
    if (t & 1) a *= *this;
    return a;
  }

  // for prime mod
  mint inv() const {
    return pow(MOD-2);
  }
  mint& operator/= (const mint a) {
    return (*this) *= a.inv();
  }
  mint operator/ (const mint a) const {
    mint res(*this);
    return res /= a;
  }
};
istream& operator>>(istream& is, const mint& a) { return is >> a.x;}
ostream& operator<<(ostream& os, const mint& a) { return os << a.x;}


class SuffixDecomposition {
public:
  long long findTotalFun(vector <int> P, int A0, int X, int Y, int B0, int X1, int Y1, int N) {
    vector<ll> S = buildS(P, A0, X, Y, B0, X1, Y1, N);
    // printvec(S);
    return calcCount(S);
  }

  vector<ll> buildS(const vector <int>& P, int A0, int X, int Y, int B0, int X1, int Y1, int N) {
    vector<ll> ans(N);
    rep(i,P.size()) {
      ans[i] = P[i];
    }

    vector<mint> A(N);
    A[0] = A0;
    rep(i,N-1) {
      A[i+1] = (A[i] * X) + Y;
    }

    vector<mint> B(N);
    B[0] = B0;
    rep(i,N-1) {
      B[i+1] = (B[i] * X1) + Y1;
    }

    for (int i = P.size(); i < N; ++i) {
      ans[i] = max(A[i].x, B[i].x);
    }

    return ans;
  }

  ll calcCount(const vector<ll>& s) {
    ll ans = 0;
    ll n = s.size();

    stack<ll> st; // contains all min values. st
    st.push(INF);
    int i = n-1;
    while (i >= 0) {
      ll now = s[i];
      while (!st.empty() && st.top() <= s[i]) {
        chmin(now, st.top());
        st.pop();
      }
      // Here, st is valid.
      st.push(now);
      ans += st.size()-1;
      --i;
    }
    return ans;
  }
};

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);

  // Class a0;
  // std::cout << "a0: Expected ~, Got \"" << a0.method() << "\"" << std::endl;
  SuffixDecomposition a0;
  cout << a0.findTotalFun({3,9,5},0,0,0,0,0,0,3) << endl;
  cout << a0.findTotalFun({10},1,2,2,3,1,2,4) << endl;
  // std::cout << "a0: Expected ~, Got \"" << setprecision(10) << a0.getMin() << "\"" << std::endl;
}
