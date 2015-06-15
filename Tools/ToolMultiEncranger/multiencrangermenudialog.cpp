#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "multiencrangermenudialog.h"

#include <fstream>
#include <iostream>
#include <iterator>

#include <boost/lexical_cast.hpp>
#include "loopreader.h"
#include "encranger.h"
#include "fileio.h"
#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

//From http://www.richelbilderbeek.nl/CppSaveContainer.htm
template <class Container>
void SaveContainer(const Container& c, const std::string& filename)
{
  std::ofstream f(filename.c_str());
  std::copy(c.begin(),c.end(),std::ostream_iterator<typename Container::value_type>(f,"\n"));
}

int ribi::MultiEncrangerMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }

  std::string source_filename = "";
  for (int i=0; i!=argc-1; ++i) //-1 because next argument is needed
  {
    if (argv[i] == "-s" || argv[i] == "--source")
    {
      source_filename = argv[i + 1];
    }
  }
  if (!fileio::FileIo().IsRegularFile(source_filename))
  {
    std::cout << "Please supply an existing source filename\n";
    return 1;
  }

  std::string target_filename = "";
  for (int i=0; i!=argc-1; ++i) //-1 because next argument is needed
  {
    if (argv[i] == "-t" || argv[i] == "--target")
    {
      target_filename = argv[i + 1];
    }
  }
  if (target_filename.empty())
  {
    std::cout << "Please supply a target filename\n";
    return 1;
  }


  int key = 0;
  for (int i=0; i!=argc-1; ++i) //-1 because next argument is needed
  {
    if (argv[i] == "-k" || argv[i] == "--key")
    {
      const std::string s = argv[i + 1];
      try
      {
        key = boost::lexical_cast<int>(s);
      }
      catch (boost::bad_lexical_cast&)
      {
        std::cout << "Please supply the encryption key as a number\n";
        return 1;
      }
    }
  }
  const bool do_encrypt
    = std::count_if(
      argv.begin(),argv.end(),
      [](const std::string& s)
      {
        return s == "-e" || s == "--encrypt";
      }
    );

  const bool do_deencrypt
    = std::count_if(
      argv.begin(),argv.end(),
      [](const std::string& s)
      {
        return s == "-d" || s == "--deencrypt";
      }
    );

  if (!do_encrypt && !do_deencrypt)
  {
    std::cout << "Please select whether to encrypt or deencrypt\n";
    return 1;
  }

  if (do_encrypt && do_deencrypt)
  {
    std::cout << "Please select either encrypt or deencrypt\n";
    return 1;
  }

  const Encranger e(key);
  std::vector<std::string> v { fileio::FileIo().FileToVector(source_filename) };
  if (do_encrypt)
  {
    for(std::string& s: v) { s = e.Encrypt(s); }
  }
  else
  {
    //Decrypt
    for(std::string& s: v) { s = e.Deencrypt(s); }
  }
  SaveContainer(v,target_filename);
  return 0;
}

ribi::About ribi::MultiEncrangerMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "ToolMultiEncranger",
    "multi-line Encranger encryption",
    "the 30th of September 2013",
    "20xx-2015",
    "http://www.richelbilderbeek.nl/ToolMultiEncranger.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("Encranger version: " + Encranger::GetVersion());
  a.AddLibrary("LoopReader version: " + LoopReader<int>::GetVersion());
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::MultiEncrangerMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {
      Help::Option('d',"deencrypt","deencrypt the source file"),
      Help::Option('e',"encrypt","encrypt the source file"),
      Help::Option('k',"key","the encryption key value"),
      Help::Option('s',"source","the source file name"),
      Help::Option('t',"target","the target file name")
    },
    {
      "MultiEncranger -e -k 1234 -s plainfile.txt -t encrypted.txt",
      "MultiEncranger -d -k 1234 -s my_secret.txt -t readme.txt"

    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::MultiEncrangerMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p(new ProgramMultiEncranger);
  assert(p);
  return p;
}

std::string ribi::MultiEncrangerMenuDialog::GetVersion() const noexcept
{
  return "2.2";
}

std::vector<std::string> ribi::MultiEncrangerMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "20xx-xx-xx: Version 1.0: initial version programmed in C++ Builder",
    "2013-09-30: Version 2.0: port to Qt Creator, renamed application to ToolMultiEncranger"
    "2013-11-04: Version 2.1: conformized to ProjectRichelBilderbeekConsole",
    "2013-11-04: Version 2.2: really use multiple lines"
  };
}

#ifndef NDEBUG
void ribi::MultiEncrangerMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
