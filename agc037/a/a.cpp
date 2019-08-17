#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef pair<int, int> P;

int main(int argc, char** argv) {
  string s;
  cin >> s;

  vector<P> results;

  // TODO(south37) Handle exceptions.

  // For Debug
  // cout << s << endl;

  string left_s = s.substr(0, 1);
  string right_s = s.substr(s.size()-1, 1);
  s = s.substr(1, s.size() - 2);

  vector<string> left_res;
  vector<string> right_res;
  left_res.push_back(left_s);
  right_res.push_back(right_s);

  // For debug
  // cout << "(" << left_s << ")" << " (" << s << ")" << " (" << right_s << ")" << endl;
  // cout << "left: " << left_s << endl;
  // cout << "right: " << right_s << endl;

  bool left = false;
  bool right = false;
  while (s.size() != 0) {
    // Fast path
    if (s.size() == 3) {
      { // Try (x), (xx)
        string l = s.substr(0, 1);
        string r = s.substr(1, 2);
        if ((left_s != l) && (right_s != r)) {
          left_s = l;
          s = r;
          left_res.push_back(left_s);
          continue;
        } else {
          // Try (xx), (x)
          string l = s.substr(0, 2);
          string r = s.substr(2, 1);
          if ((left_s != l) && (right_s != r)) {
            right_s = r;
            s = l;
            right_res.push_back(right_s);
            continue;
          } else {
            // Try (x), (x), (x)
            string l = s.substr(0, 1);
            string r = s.substr(2, 1);
            if ((left_s != l) && (right_s != r)) {
              right_s = r;
              s = l;
              right_res.push_back(right_s);
              continue;
            } else {
              if (left_s == l && right_s == r) {
                left_res.push_back(s);
                break;
              } else if (left_s == l) {
                right_s = r;
                s = s.substr(0, 2);
                right_res.push_back(right_s);
                continue;
              } else { // right_s == r
                left_s = l;
                s = s.substr(1, 2);
                left_res.push_back(left_s);
                continue;
              }
            }
          }
        }
      }
    } else if (s.size() == 2) {
      string l = s.substr(0, 1);
      string r = s.substr(1, 1);
      if ((left_s != l) && (right_s != r)) {
        left_res.push_back(l);
        right_res.push_back(r);
        break;
      } else {
        left_res.push_back(s);
        break;
      }
    } else if (s.size() == 1) {
      left_res.push_back(s);
      break;
    }

    // Try left at first
    if (left_s.size() == 1) {
      if (s[0] != left_s[0]) { // Not match
        left_s = s.substr(0, 1);
        s = s.substr(1, s.size() - 1);
        left_res.push_back(left_s);
        left = true;
        // cout << "left1: " << left_s << endl;
      } else {  // Match
        // Try right
        if (right_s.size() == 1) {
          if (s[s.size()-1] != right_s[0]) {  // Not match
            right_s = s.substr(s.size() - 1, 1);
            s = s.substr(0, s.size() - 1);
            right_res.push_back(right_s);
            right = true;
            // cout << "right1: " << right_s << endl;
          } else {  // Match
            if (s.size() <= 3) {
              // NOTE: We can't fecth here. See ex.2
              left_res.push_back(s);
              break;
            } else { // Ordinary case
              // Fetch 2 from left
              left_s = s.substr(0, 2);
              s = s.substr(2, s.size() - 2);
              left_res.push_back(left_s);
              left = true;
              // cout << "left2: " << left_s << endl;
            }
          }
        } else {  // right_s.size() == 2
          right_s = s.substr(s.size() - 1, 1);
          s = s.substr(0, s.size() - 1);
          right_res.push_back(right_s);
          right = true;
          // cout << "right2: " << right_s << endl;
        }
      }
    } else { // left_s.size() == 2
      left_s = s.substr(0, 1);
      s = s.substr(1, s.size() - 1);
      left_res.push_back(left_s);
      left = true;
    }

    // For debug
    // cout << "(" << left_s << ")" << " (" << s << ")" << " (" << right_s << ")" << endl;
    // if (left) {
    //   cout << "left: " << left_s << endl;
    // }
    // if (right) {
    //   cout << "right: " << right_s << endl;
    // }

    left = false;
    right = false;
  }

  // For Debug
  // rep(i, left_res.size()) {
  //   cout << left_res[i] << " ";
  // }
  // for (int i = right_res.size() - 1; i >= 0; --i) {
  //   cout << right_res[i] << " ";
  // }
  // cout << endl;

  cout << left_res.size() + right_res.size() << endl;

  // bool dup = false;
  // for(int i = 1; i < res.size(); ++i) {
  //   if (res[i-1] == res[i]) {
  //     dup = true;
  //   }
  // }
  // if (dup) {
  //   cout << res.size() - 1 << endl;
  // } else {
  //   cout << res.size() << endl;
  // }

  // int left_pos = 0;
  // results.push_back(P(left_pos, 1));
  // int prev_left_pos = left_pos;
  // int prev_left_len = 1;

  // int right_pos = s.size() - 1;
  // results.push_back(P(right_pos, 1));
  // int prev_right_pos = s.size() - 2;
  // int prev_right_len = 1;
  //
  // right_pos--;
  // left_pos++;

  // while (true) {
  //   // NOTE: Check at first

  //   // Check "length-1" at first
  //   if (prev_left_len == 1) { // Many times
  //     if (s[prev_left_s] == s[left_s]) { // NOTE: Check only character
  //       // Check right
  //       if (prev_right_len == 1) {
  //         if (s[prev_left_s] == s[left_s]) { // NOTE: Check only character
  //       } else { // prev_right_len == 2
  //         results.push_back(P(right_pos, 1));
  //         prev_right_pos = left_pos;
  //         prev_right_len = 1;
  //         ritht_pos--;
  //       }
  //     } else {
  //       results.push_back(P(left_pos, 1));
  //       prev_left_pos = left_pos;
  //       prev_left_len = 1;
  //       left_pos++;
  //     }
  //   } else { // prev_left_len == 2
  //     results.push_back(P(left_pos, 1));
  //     prev_left_pos = left_pos;
  //     prev_left_len = 1;
  //     left_pos++;
  //     continue;  // Back to first
  //   }
  // }
  // cout << left_s << endl;
}
