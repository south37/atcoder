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
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  ll n, m;
  cin >> n >> m;

  // d[u][v] .. The cost between u .. v.
  vector< vector<ll> > d(n, vector<ll>(n, INF));

  // initialization
  rep(i, m) {
    int a, b, c;
    cin >> a >> b >> c;
    --a; --b; // 0-indexed
    d[a][b] = c;
    d[b][a] = c;
  }

  // WarshalFloyd
  rep(k, n) {
    rep(i, n) {
      rep(j, n) {
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
      }
    }
  }

  cout << "d[0][1]: " << d[0][1] << endl;
  cout << "d[0][2]: " << d[0][2] << endl;
}
