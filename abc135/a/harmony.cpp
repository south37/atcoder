#include <iostream>

int main(int argc, char** argv) {
  int a, b;
  std::cin >> a;
  std::cin >> b;

  int s = (a + b);
  int r = s / 2;
  if ((r * 2) == s) {
    std::cout << r << std::endl;
  } else {
    std::cout << "IMPOSSIBLE";
  }
}
