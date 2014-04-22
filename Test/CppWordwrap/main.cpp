#include <cassert>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

///Undo a Wordwrap
const std::string Unwordwrap(const std::vector<std::string>& v) noexcept;

///Wordwrap the text to obtain lines of max_len characters
///If the string _must_ be seperable by spaces; a word can have a maximum length of max_len
const std::vector<std::string> Wordwrap(const std::string& s, const std::size_t max_len) noexcept;


const std::string Unwordwrap(
  const std::vector<std::string>& v) noexcept
{
  //Simply concatenate
  std::string t;
  for (const std::string& s: v) { t += s; }
  return t;
}

const std::vector<std::string> Wordwrap(
  const std::string& s_original, const std::size_t max_len) noexcept
{
  if (max_len == 0)
  {
    throw std::logic_error("Cannot wordwrap for a max_len of zero");
  }
  //std::clog << "Wordwrap \'" << s_original << '\'' << std::endl;
  std::string s{s_original};
  assert(s.size() == s_original.size());

  ///Replace multiple spaces with '\b ', where x is a char not in the string
  std::string::value_type x = '\b'; //Bell
  {
    const std::size_t sz = s.size();

    ///Replace spaces at beginning
    for (std::size_t i=0; i!=sz; ++i)
    {
      if (s[i] == ' ')
        s[i] = x;
      else
        break;
    }
    //Replace spaces at end
    if (sz > 0)
    {
      //i!=0, because if s[0] is a space, it is already converted to bell
      for (std::size_t i=sz-1; i!=0; ++i)
      {
        if (s[i] == ' ')
          s[i] = x;
        else
          break;
      }
    }
    ///Replace "  " by "\b "
    for (std::size_t i=0; i!=sz-1; ++i)
    {
      if (s[i] == ' ' && s[i+1] == ' ')
        s[i] = x;
      else
        break;
    }
  }

  std::vector<std::string> v;

  //Start the actual wordwrapping
  while (!s.empty())
  {
    //TRACE(s);
    //Is the word short enough?
    if (s.size() < max_len)
    {
      //Copy entire word
      v.push_back(s);
      s = {};
      assert(s.empty());
      continue;
    }
    //No spaces, or space beyond max_len: cut word
    if (s.find(' ') == std::string::npos || s.find(' ') > max_len)
    {
      v.push_back(s.substr(0,max_len));
      s = s.substr(max_len,s.size() - max_len);
      continue;
    }
    //Find last space before max_len
    std::size_t len = s.find(' ');
    assert(len != std::string::npos);
    assert(len < s.size());
    while (1)
    {
      const std::size_t new_len = s.find(' ',len + 1);
      if (new_len > max_len || new_len == std::string::npos) break;
      len = new_len;
    }
    assert(len + 0 < s.size());
    assert(len + 1 < s.size());
    //cut s, put cut part in vector
    const std::string line = s.substr(0,len+1); //Keep space
    assert(!line.empty());
    v.push_back(line);
    const std::size_t new_index = len+1; //After the space found
    assert(new_index < s.size());
    const std::string new_s = s.substr(new_index,s.size() - new_index);
    assert(s != new_s);
    s = new_s;
  }

  ///Replace bell characters by spaces again
  for (std::string& s: v)
  {
    assert(x != ' ');
    std::size_t pos = s.find(x);
    while (pos != std::string::npos)
    {
      assert(pos != std::string::npos);
      assert(pos < s.size());
      assert(pos == s.find(x)); //To prevent infinite while loop
      s[pos] = ' ';
      assert(s[pos] == ' ');
      assert(pos != s.find(x)); //To prevent infinite while loop
      pos = s.find(x);
    }
    assert(s.find(x) == std::string::npos);
  }

  #ifndef NDEBUG
  //Test if Unwordwrap the result produces the original input
  if (Unwordwrap(v) != s_original)
  {
    std::cerr << v.size() << '\n';
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::cerr,"\n"));
    std::cerr << Unwordwrap(v) << '\n';
    std::cerr << s_original << std::endl;

  }
  #endif
  assert(Unwordwrap(v) == s_original);
  return v;
}

int main()
{
  {
    const std::string s = "123";
    const std::vector<std::string> expected = { "123" };
    const std::vector<std::string> v = Wordwrap(s,11);
    assert(v == expected);
    assert(Unwordwrap(v) == s);
  }
  {
    const std::string s = "1234567890 123";
    //Note that exected keeps trailing spaces at then end of a cut
    const std::vector<std::string> expected = { "1234567890 ", "123" };
    const std::vector<std::string> v = Wordwrap(s,11);
    //if (v != expected)
    //{
    //  const std::size_t sz = v.size();
    //  for (std::size_t i=0; i!=sz; ++i)
    //  {
    //    std::cout << i << '/' << sz << ": '" << v[i] << '\'' << std::endl;
    //  }
    //}
    assert(v == expected);
    assert(Unwordwrap(v) == s);
  }
  {
    const std::string s = "1234567890  123";
    const std::vector<std::string> expected = { "1234567890  ", "123" };
    const std::vector<std::string> v = Wordwrap(s,11);
    //if (v != expected)
    //{
    //  const std::size_t sz = v.size();
    //  for (std::size_t i=0; i!=sz; ++i)
    //  {
    //    std::cout << i << '/' << sz << ": '" << v[i] << '\'' << std::endl;
    //  }
    //}
    assert(v == expected);
    assert(Unwordwrap(v) == s);
  }
  {
    const std::string s = "123 567890 123";
    const std::vector<std::string> expected = { "123 567890 ", "123" };
    const std::vector<std::string> v = Wordwrap(s,11);
    assert(v == expected);
    assert(Unwordwrap(v) == s);
  }
  {
    const auto v {
      "",
      "1",
      "12",
      "123",
      "1234",
      "12345",
      "123456",
      "1234567",
      "12345678",
      "123456789",
      "1234567890",
      "12345678901",
      "123456789012",
      "1234567890123",
      "12345678901234",
      "123456789012345",
      "1234567890123456",
      "12345678901234567",
      "123456789012345678",
      "1234567890123456789",
      "12345678901234567890",
      "123456789012345678901",
      "1234567890123456789012",
      "12345678901234567890123",
      "123456789012345678901234",
      "1234567890123456789012345",
      "12345678901234567890123456",
      "123456789012345678901234567",
      "1234567890123456789012345678",
      "12345678901234567890123456789",
      "123456789012345678901234567890",
      "1234567890123456789012345678901",
      "12345678901234567890123456789012",
      "123456789012345678901234567890123",
      "1234567890123456789012345678901234",
      "12345678901234567890123456789012345",
      "123456789012345678901234567890123456",
      "1234567890123456789012345678901234567",
      "12345678901234567890123456789012345678",
      "123456789012345678901234567890123456789",
      "1234567890123456789012345678901234567890",
      "1 1",
      "12 12",
      "123 123",
      "1234 1234",
      "12345 12345",
      "123456 123456",
      "1234567 1234567",
      "12345678 8",
      "123456789 9",
      "1234567890 0",
      "1234567890 1234567890",
      "1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      " 1",
      "  1",
      "  1 ",
      "  1  ",
      "  1 2 ",
      "  1 23 ",
      "  12 34  ",
      "  12  34  ",
      "   12   34   ",
      "   12   34   5",
      "   12   34   5 ",
      "   12   34   5 6",
      "0   12   34   5 6",
      "0   12   34   5 6  ",
      "                    ",
      "                      ",
      "                        ",
      "                            ",
      "                                    ",
      "                                                    ",
      "                                                                                     "
    };
    for (int len=1; len!=1000; ++len)
    {
      for (const std::string& s: v)
      {
        //Wordwrap calls Unwordwrap
        Wordwrap(s,len);
      }
    }
  }
}
