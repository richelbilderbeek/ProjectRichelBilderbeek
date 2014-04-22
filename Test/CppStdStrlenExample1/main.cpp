#include <cassert>
#include <cstring>

int main()
{
  //String of one character
  {
    const char s[] = "X";
    assert(std::strlen(s) == 1);
    assert(s[0] == 'X');
    assert(s[1] == '\0');
  }
  //String of ten characters
  {
    const char s[] = "0123456789";
    assert(std::strlen(s) == 10);
    assert(s[ 0] == '0');
    assert(s[ 1] == '1');
    //Etcetera
    assert(s[ 8] == '8');
    assert(s[ 9] == '9');
    assert(s[10] == '\0');
  }
  //Empty string
  {
    const char s[] = "";
    assert(std::strlen(s) == 0);
    assert(s[0] == '\0');
  }
  //Dynamically allocated string of one character
  {
    char * const s = new char[1 + 1]; //+1 for the null terminator
    s[0] = 'X';
    s[1] = '\0'; //Must add the null terminator
    assert(std::strlen(s) == 1);
    delete[] s;
  }
  //Dynamically allocated string of ten characters
  {
    char * const s = new char[10 + 1]; //+1 for the null terminator
    std::strcpy(s,"0123456789"); //Adds the null terminator
    assert(std::strlen(s) == 10);
    assert(s[0] == '0');
    assert(s[1] == '1');
    //Etcetera
    assert(s[ 8] == '8');
    assert(s[ 9] == '9');
    assert(s[10] == '\0');
    delete[] s;
  }
}
