// ref. https://www.utakata.work/entry/2015/06/07/195042

#include <algorithm>
#include <bitset>
#include <cassert>
#include <complex>
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

// FFT (Fast Fourier transform)
// inverse = 1 .. DFT, inverse = -1 .. IDFT
const double PI = 4.0*atan(1.0);
const complex<double> I(0,1);

void fft(vector<complex<double>>& a, int inverse = 1) {
  int n = a.size();
  double theta = 2*inverse*PI / n; // theta = 2pi/n

  for (int m = n; m >= 2; m >>= 1) {
    int mh = m >> 1;
    rep(i,mh) {
      complex<double> w = exp(i*theta*I);
      for (int j = i; j < n; j += m) {
        int k = j + mh;
        complex<double> x = a[j] - a[k];
        a[j] += a[k];
        a[k] = w * x;
      }
    }
    theta *= 2;
  }
  int i = 0;
  for (int j = 1; j < n - 1; ++j) {
    for (int k = n >> 1; k > (i ^= k); k >>= 1);
    if (j < i) swap(a[i], a[j]);
  }

  if (inverse == -1) {
    complex<double> d(n,0);
    rep(i,n) {
      a[i] = a[i] / d;
    }
  }
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<ll> g(n);
  vector<ll> h(n);
  rep(i,n) {
    cin >> g[i] >> h[i];
  }
  // result of k .. combolution of g and h. We use FFT.

  ll n2 = 1;
  while (n2 < 2*n) {
    n2 *= 2;
  }
  // Here, n2 is 2^i and n2 >= 2*n

  vector<complex<double>> gg(n2);
  vector<complex<double>> hh(n2);
  rep(i,n){
    gg[i] = g[i];
    hh[i] = h[i];
  }
  fft(gg);
  fft(hh);
  // Here, gg and hh is the result of FFT.

  vector<complex<double>> ff(n2);
  rep(i,n2) {
    ff[i] = gg[i]*hh[i];
  }
  fft(ff,-1); // inverse IDFT

  cout << 0 << endl;
  rep(i,2*n-1) {
    cout << ff[i].real() << endl;
  }
}
