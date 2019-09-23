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

int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

vector< vector<int> > A;
vector<P> q; // Match queue

// Check the remaining matches. If match can be made, push it to queue.
void check(int i) {
  if (A[i].size() == 0) { return; }
  int j = A[i].back();
  if (A[j].back() == i) {
    if (i > j) { swap(i, j); }  // Force i < j
    q.emplace_back(i, j);
  }
}

int main(int argc, char** argv) {
  int N;
  cin >> N;

  A.assign(N, vector<int>(N-1));
  rep(i, N) {
    rep(j, N-1) {
      cin >> A[i][j];
      --A[i][j];
    }
    reverse(all(A[i]));
  }

  // Push first matches.
  rep(i, N) {
    check(i);
  }

  int day = 0;
  while (q.size() > 0) { // Repeat until match que
    sort(all(q));
    q.erase(unique(all(q)), q.end());

    vector<P> prevQ;
    swap(prevQ, q); // Set q to prevQ, set empty vector to q.
    for (auto p : prevQ) {
      A[p.first].pop_back(); // pop match
      A[p.second].pop_back(); // pop match
    }
    for (auto p : prevQ) {
      check(p.first);
      check(p.second);
    }

    ++day;
  }

  // Check the remaining of A
  rep(i, N) {
    if (A[i].size() != 0) {
      cout << -1 << endl;
      return 0;
    }
  }

  cout << day << endl;
}
