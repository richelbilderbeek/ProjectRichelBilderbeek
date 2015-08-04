#include <cassert>
#include <iostream>
#include <string>

///From http//www.richelbilderbeek.nl/CppStrToLines.htm
///Add newlines to a std::string so that
///each line has length characters at most
std::string StrToLines(std::string s, const int length)
{
  const bool verbose{false};
  assert(length > 0);
  const int sz{static_cast<int>(s.size())};
  int this_line_start = 0;
  int pos = this_line_start + length;

  while (1)
  {
    if (pos >= sz) break;
    assert(pos >= 0 && pos < sz);
    if (s[pos] == '\n')
    {
      this_line_start = pos + 1;
      pos = this_line_start + length;
      continue;
    }
    if (s[pos] == ' ')
    {
      s[pos] = '\n';
      this_line_start = pos + 1;
      pos = this_line_start + length;
    }
    if (pos >= sz) break;
    --pos;
    assert(pos >= this_line_start);
    if (pos == this_line_start)
    {
      if (verbose) { std::clog << "Word is longer than length, insert a newline in the word" << std::endl; }
      s = s.substr(0,this_line_start+length)
        + "\n"
        + s.substr(this_line_start+length,sz-this_line_start-length)
      ;

      if (verbose) { std::clog << "New string: " << s << std::endl; }

      this_line_start = this_line_start + length + 1;
      pos = this_line_start + length;

      if (verbose) { std::clog << "New pos: " << pos << std::endl; }
      if (verbose) { std::clog << "New this_line_start: " << this_line_start << std::endl; }

      assert(pos >= this_line_start);
    }
  }
  return s;
}

int main()
{
  assert(StrToLines("Hello",5) == "Hello");
  assert(StrToLines("Hello World",5) == "Hello\nWorld");
  assert(StrToLines("Hi to you",5) == "Hi to\nyou");
  assert(StrToLines("Hi to you again",5) == "Hi to\nyou\nagain");
  assert(StrToLines("Toolong",4) == "Tool\nong");
  assert(StrToLines("Toolong",4) == "Tool\nong");
  assert(StrToLines("01\n23\n45",4) == "01\n23\n45");
}
