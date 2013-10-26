
#include "menudialog.h"
#include <cassert>
#include <iterator>
#include <iostream>

const std::vector<std::string> ribi::MenuDialog::ConvertArguments(
  const int argc, const char * const argv[]) noexcept
{
   std::vector<std::string> v;
   v.reserve(argc);
   for (int i=0; i!=argc; ++i)
   {
     v.push_back(std::string(argv[i]));
   }
   assert(argc == static_cast<int>(v.size()));
   return v;
}

int ribi::MenuDialog::Execute(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    return ExecuteSpecific(argv);
  }
  const std::string s = argv[1];
  if (s == std::string("--about") || s == std::string("-a"))
  {
    const std::vector<std::string> v { GetAbout().CreateAboutText() };
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
    std::cout
      << "\n"
      << "Source code built on "
      << __DATE__
      << " "
      << __TIME__
      << " ("
    #ifdef NDEBUG
      << "release"
    #else
      << "debug"
    #endif
      << " version)"
      << std::endl;
    return 0;
  }
  else if (s == std::string("--help") || s == std::string("-h"))
  {
    std::cout << GetHelp() << '\n';
    return 0;
  }
  else if (s == std::string("--history") || s == std::string("-i"))
  {
    const std::vector<std::string> v { GetVersionHistory() };
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
    return 0;
  }
  else if (s == std::string("--licence") || s == std::string("-l"))
  {
    const std::vector<std::string> v { GetAbout().CreateLicenceText() };
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
    return 0;
  }
  else if (s == std::string("--version") || s == std::string("-v"))
  {
    const std::vector<std::string> v = { GetAbout().CreateLibrariesUsedText() };
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
    return 0;
  }
  return ExecuteSpecific(argv);
}
