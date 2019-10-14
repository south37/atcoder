// base: http://drken1215.hatenablog.com/entry/2019/09/16/014600

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

// Suffix Array ( Manber&Myers: O(n (logn)^2) )
struct SuffixArray {
  string str;
  vector<int> sa;  // sa[i] : the starting index of the i-th smallest suffix (i = 0, 1, ..., n)
  vector<int> lcp; // lcp[i]: the lcp of sa[i] and sa[i+1] (i = 0, 1, ..., n-1)
  inline int& operator [] (int i) {return sa[i];}

  SuffixArray(const string& str_) : str(str_) { buildSA(); calcLCP(); }
  void init(const string& str_) { str = str_; buildSA(); calcLCP(); }

  // build SA
  vector<int> rank_sa, tmp_rank_sa;
  struct CompareSA {
    int n, k;
    const vector<int> &rank;
    CompareSA(int n, int k, const vector<int> &rank_sa) : n(n), k(k), rank(rank_sa) {}
    bool operator()(int i, int j) {
      if (rank[i] != rank[j]) return (rank[i] < rank[j]);
      else {
        int rank_ik = (i + k <= n ? rank[i + k] : -1);
        int rank_jk = (j + k <= n ? rank[j + k] : -1);
        return (rank_ik < rank_jk);
      }
    }
  };
  void buildSA() {
    int n = (int)str.size();
    sa.resize(n+1), rank_sa.resize(n+1), tmp_rank_sa.resize(n+1);
    for (int i = 0; i < n; ++i) sa[i] = i, rank_sa[i] = (int)str[i];
    sa[n] = n, rank_sa[n] = -1;
    for (int k = 1; k <= n; k *= 2) {
      CompareSA csa(n, k, rank_sa);
      sort(sa.begin(), sa.end(), csa);
      tmp_rank_sa[sa[0]] = 0;
      for (int i = 1; i <= n; ++i) {
        tmp_rank_sa[sa[i]] = tmp_rank_sa[sa[i - 1]];
        if (csa(sa[i - 1], sa[i])) ++tmp_rank_sa[sa[i]];
      }
      for (int i = 0; i <= n; ++i) rank_sa[i] = tmp_rank_sa[i];
    }
  }

  // calculate lcp
  vector<int> rsa; // inverse table of sa.
  void calcLCP() {
    int n = (int)str.size();
    lcp.resize(n+1);
    rsa.resize(n+1);
    for (int i = 0; i <= n; ++i) rsa[sa[i]] = i;
    lcp[0] = 0;
    int cur = 0;
    for (int i = 0; i < n; ++i) {
      int pi = sa[rsa[i] - 1];
      if (cur > 0) --cur;
      for (; pi + cur < n && i + cur < n; ++cur) {
          if (str[pi + cur] != str[i + cur]) break;
      }
      lcp[rsa[i] - 1] = cur;
    }
  }
};

// RMQ by SparseTree
template<class T> struct SparseTable {
  vector<vector<T> > dat;
  vector<int> height;

  SparseTable() { }
  SparseTable(const vector<T> &vec) { init(vec); }
  void init(const vector<T> &vec) {
    int n = (int)vec.size(), h = 0;
    while ((1<<h) < n) ++h;
    dat.assign(h, vector<T>(1<<h));
    height.assign(n+1, 0);
    for (int i = 2; i <= n; i++) height[i] = height[i>>1]+1;
    for (int i = 0; i < n; ++i) dat[0][i] = vec[i];
    for (int i = 1; i < h; ++i) {
      for (int j = 0; j < n; ++j) {
        dat[i][j] = min(dat[i-1][j], dat[i-1][min(j+(1<<(i-1)),n-1)]);
      }
    }
  }

  // Return the min of [a, b)
  T get(int a, int b) {
    return min(dat[height[b-a]][a], dat[height[b-a]][b-(1<<height[b-a])]);
  }
};

int main(int argc, char** argv) {
  int N;
  cin >> N;
  string S;
  cin >> S;

  SuffixArray sa(S);
  // Here, sa.lcp[i] stores the lcp of S[sa.sa[i]..] and S[sa.sa[i+1]..] (i = 0, 1, ..., n-1)

  SparseTable<int> st(sa.lcp);
  // If we want to know the lcp of S[i..] ans S[j..], then st.get(sa.rsa[i], sa.rsa[j]) is the result. (sa.rsa[i] < sa.rsa[j] is necessary).

  int ans = 0;
  rep(i, N) {
    for (int j = i + 1; j < N; ++j) {
      int lcp = st.get(min(sa.rsa[i], sa.rsa[j]), max(sa.rsa[i], sa.rsa[j]));
      ans = max(ans, min(lcp, j - i));
    }
  }

  cout << ans << endl;
}
