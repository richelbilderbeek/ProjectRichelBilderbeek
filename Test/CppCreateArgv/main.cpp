#include <cstring>
#include <iostream>
#include <string>
#include <vector>

//Function with the same signature as main
int fake_main(int argc, char * argv[])
{
  for (int i=0; i!=argc; ++i)
  {
    std::cout << i << ": " << argv[i] << std::endl;
  }
  return 0;
}

std::pair<int,char **> CreateArgv(const std::vector<std::string>& v)
{
  typedef char* String;
  typedef String* Strings;
  const int argc = static_cast<int>(v.size());
  Strings argv = new String[argc];
  for (int i=0; i!=argc; ++i)
  {
    argv[i] = new char[v[i].size() + 1];
    std::strcpy(argv[i],&v[i][0]);
  }
  std::pair<int,char **> p = std::make_pair(argc,argv);
  return p;
}

void DeleteArgv(const std::pair<int,char **>& p)
{
  const int argc = p.first;
  for(int i = 0; i != argc; ++i)
  {
    delete[] p.second[i];
  }
  delete[] p.second;
}


int main()
{
  const std::vector<std::string> v {
    "MyMain.exe",
    "--argument_1",
    "--argument_2",
    "--argument_3",
    "--argument_4",
    "--argument_5",
    "--argument_6",
    "--argument_7"
  };
  const auto p(CreateArgv(v));
  fake_main(p.first,p.second);
  DeleteArgv(p);
}
