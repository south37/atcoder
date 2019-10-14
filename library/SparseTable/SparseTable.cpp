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

// RMQ by SparseTree. O(NlogN) in initialization, O(1) in get.
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
  vector<int> a = {7, 2, 3, 0, 5, 10, 3, 12, 18};
  SparseTable<int> st(a);

  cout << st.get(0, 4) << endl; // 0
  cout << st.get(4, 8) << endl; // 3
  cout << st.get(7, 9) << endl; // 12
}
