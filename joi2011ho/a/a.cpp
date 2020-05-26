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

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll h,w;
  cin >> h >> w;
  ll K;
  cin >> K;
  vector<string> mat(h);
  rep(r,h) {
    cin >> mat[r];
  }

  string chars = "JOI";
  vector<vector<vector<ll>>> s(3, vector<vector<ll>>(h+1,vector<ll>(w+1)));
  rep(k,3) {
    char nc = chars[k];
    vector<vector<ll>>& s1 = s[k];

    rep(r,h) {
      vector<ll> now(w+1);
      rep(c,w) {
        now[c+1] = now[c] + (mat[r][c] == nc ? 1 : 0); // add 1 if current character is nc.
        s1[r+1][c+1] = s1[r][c+1] + now[c+1];
      }
    }
  }
  // printtree(s[0]);
  // printtree(s[1]);
  // printtree(s[2]);
  // Heere, s[r][c] is sum of values in rectangles [0,r)-[0,c)

  // return sum in [r1,r2)-[c1,c2)
  auto solve = [&](ll r1, ll c1, ll r2, ll c2, ll k) {
    return s[k][r2][c2] - s[k][r1][c2] - s[k][r2][c1] + s[k][r1][c1];
  };

  rep(iter,K) {
    ll r1,c1,r2,c2;
    cin >> r1 >> c1 >> r2 >> c2;
    ll jCnt = solve(r1-1,c1-1,r2,c2,0);
    ll oCnt = solve(r1-1,c1-1,r2,c2,1);
    ll iCnt = solve(r1-1,c1-1,r2,c2,2);
    cout << jCnt << " " << oCnt << " " << iCnt << endl;
  }
}
