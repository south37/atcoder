// ref. https://atcoder.jp/contests/atc001/submissions/7462530

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
// Cooley–Tukey FFT algorithm O(N log N)
vector<complex<double>> fft(vector<complex<double>> a, bool inverse = false) {
  int n = a.size();
  int h = 0; // h = log_2(n)
  for (int i = 0; (1<<i) < n; ++i) { ++h; }
  // Rearrangement for butterfly calculation
  rep(i,n) {
    int j = 0;
    for (int k = 0; k < h; k++) j |= (i >> k & 1) << (h - 1 - k);
    if (i < j) swap(a[i], a[j]);
  }
  // Butterfly calculation
  for (int b = 1; b < n; b *= 2) {
    // log_2(b) + 1
    // block size = b*2
    for (int j = 0; j < b; j++) {
      // w = (2b root)^j
      complex<double> w =
        polar(1.0, (2 * M_PI) / (2 * b) * j * (inverse ? 1 : -1));
      for (int k = 0; k < n; k += b * 2) {
        // Block of k
        complex<double> s = a[j + k];         // front
        complex<double> t = a[j + k + b] * w; // back
        a[j + k] = s + t;                     // Update front
        a[j + k + b] = s - t;                 // Update back
      }
    }
  }
  // For IDFT
  if (inverse) {
    rep(i,n) { a[i] /= n; }
  }
  return a;
}

// Cooley–Tukey FFT algorithm O(N log N)
vector<complex<double>> fft(vector<double> a, bool inverse = false) {
  vector<complex<double>> a_complex(a.size());
  rep(i,a.size()) { a_complex[i] = complex<double>(a[i], 0); }
  return fft(a_complex, inverse);
}

// Combolution by FFT O(N log N)
vector<double> convolve(vector<double> a, vector<double> b) {
  int s = a.size() + b.size() - 1; // Result size
  int t = 1; // Array size for FFT (power of 2)
  while (t < s) t *= 2;
  a.resize(t); // Resize for FFT
  b.resize(t); // Resize for FFT
  vector<complex<double>> A = fft(a);
  vector<complex<double>> B = fft(b);
  rep(i,t) {
    A[i] *= B[i]; // FFT of Combolution Result
  }
  A = fft(A, true); // IFFT

  vector<double> ans(s);
  rep(i,s) { ans[i] = A[i].real(); } // answer is real part
  return ans;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<double> a(n+1);
  vector<double> b(n+1);
  // Here, a[0] and b[0] is dummy.
  rep(i,n) {
    cin >> a[i+1] >> b[i+1];
  }
  // result of k .. combolution of a and h. We use FFT.

  vector<double> ans = convolve(a,b);

  for (int i = 1; i < ans.size(); ++i) {
    // Here, rouding result by adding 0.5.
    cout << (int)(ans[i] + 0.5) << endl;
  }
}
