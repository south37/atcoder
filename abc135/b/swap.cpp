#include <iostream>
#include <vector>

#define SWAP(x, y) do {        \
  int tmp = x; x = y; y = tmp; \
} while (0)

bool is_ordered(const std::vector<int> &a) {
  int n = a.size();
  int last = a[0];
  for (int k = 1; k < n; ++k) {
    if (last < a[k]) {
      // OK
      last = a[k];
    } else {
      return false;
    }
  }
  return true;
}

int main(int argc, char** argv) {
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }

  if (is_ordered(a)) {
    std::cout << "YES" << std::endl;
    return 0;
  }

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      // std::cout << i << " " << j << std::endl;
      SWAP(a[i], a[j]);

      bool r = is_ordered(a);
      if (r) {
        std::cout << "YES" << std::endl;
        return 0;
      }

      // Swap one more
      SWAP(a[i], a[j]);
    }
  }

  std::cout << "NO" << std::endl;
}
