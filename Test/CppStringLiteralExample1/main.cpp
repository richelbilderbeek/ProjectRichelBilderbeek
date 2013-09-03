#include <cassert>

int main()
{
  const char c[] = "ABC";

  static_assert(sizeof(c) == 4,
    "A string literal contains one more character than it appears to have");

  assert(c[0] == 'A');
  assert(c[1] == 'B');
  assert(c[2] == 'C');
  assert(c[3] == '\0');
}
