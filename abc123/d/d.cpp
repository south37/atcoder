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

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef tuple<ll, ll, ll, ll> quad;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  ll X, Y, Z, K;
  cin >> X >> Y >> Z >> K;
  vector<ll> A(X);
  rep(i, X) {
    cin >> A[i];
  }
  vector<ll> B(Y);
  rep(i, Y) {
    cin >> B[i];
  }
  vector<ll> C(Z);
  rep(i, Z) {
    cin >> C[i];
  }
  sort(all(A), greater<ll>());
  sort(all(B), greater<ll>());
  sort(all(C), greater<ll>());

  // priority_queue<quad, vector<quad>, greater<quad> > q;
  priority_queue<quad> q;
  q.emplace(A[0] + B[0] + C[0], 0, 0, 0);
  set<triple> s;
  s.emplace(0, 0, 0);
  vector<ll> ans;
  while (!q.empty() && ans.size() < K) {
    ll x, i, j, k;
    tie(x, i, j, k) = q.top(); q.pop();
    ans.push_back(x);
    if (i+1 < X && s.count(make_tuple(i+1, j, k)) == 0) {
      s.emplace(i+1, j, k);
      q.emplace(A[i+1] + B[j] + C[k], i+1, j, k);
      // cout << "A[i+1] + B[j] + C[k]: " << A[i+1] + B[j] + C[k] << endl;
    }
    if (j+1 < Y && s.count(make_tuple(i, j+1, k)) == 0) {
      s.emplace(i, j+1, k);
      q.emplace(A[i] + B[j+1] + C[k], i, j+1, k);
      //cout << "A[i] + B[j+1] + C[k]: " << A[i] + B[j+1] + C[k] << endl;
    }
    if (k+1 < Z && s.count(make_tuple(i, j, k+1)) == 0) {
      s.emplace(i, j, k+1);
      q.emplace(A[i] + B[j] + C[k+1], i, j, k+1);
      // cout << "A[i] + B[j] + C[k+1]: " << A[i] + B[j] + C[k+1] << endl;
    }
  }

  rep(i, ans.size()) {
    cout << ans[i] << endl;
  }
}
