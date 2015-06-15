//---------------------------------------------------------------------------
/*
Encranger, encryption tool
Copyright (C) 2009-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolEncranger.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "encrangermenudialog.h"

#include <cassert>
#include <iostream>
#include <boost/lexical_cast.hpp>

#include "encranger.h"
#include "encrangermaindialog.h"
#include "loopreader.h"
#include "testtimer.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#pragma GCC diagnostic pop

int ribi::ToolEncrangerMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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
  bool is_silent = false;
  for (int i=0; i!=argc; ++i)
  {
    if (argv[i] == "-s" || argv[i] == "--silence")
    {
      is_silent = true;
    }
  }

  //Determine key, if supplied as an argument
  int key = 0;
  for (int i=0; i!=argc-1; ++i) //-1 because the next argument will be used
  {
    if (argv[i] == "-k" || argv[i] == "--key")
    {
      const std::string s = argv[i+1];
      try
      {
        key = boost::lexical_cast<int>(s);
        //Can key be negative? Yes, it is used only be std::srand
      }
      catch (boost::bad_lexical_cast&)
      {
        std::cout << "Key must be an integer number\n";
        return 1;
      }
    }
  }
  //Determine if plaintext is supplied, if yes: execute
  for (int i=0; i!=argc-1; ++i) //-1 because the next argument will be used
  {
    if (argv[i] == "-t" || argv[i] == "--text")
    {
      const std::string plaintext = argv[i + 1];
      ToolEncrangerMainDialog d;
      d.SetKey(key);
      d.SetPlainText(plaintext);
      d.Encrypt();
      if (!is_silent) { std::cout << d.GetEncryptedText() << '\n'; }
      return 0;
    }
  }
  //Determine if cipertext is supplied, if yes: execute
  for (int i=0; i!=argc-1; ++i) //-1 because the next argument will be used
  {
    if (argv[i] == "-c" || argv[i] == "--cipher")
    {
      const std::string ciphertext = argv[i + 1];
      ToolEncrangerMainDialog d;
      d.SetKey(key);
      d.SetEncryptedText(ciphertext);
      d.Deencrypt();
      if (!is_silent) { std::cout << d.GetPlainText() << '\n'; }
      return 0;
    }
  }
  std::cout << GetHelp() << '\n';
  return 1;
}

ribi::About ribi::ToolEncrangerMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "ToolEncranger",
    "tool to test the Encranger class",
    "the 1th of November 2013",
    "2009-2015",
    "http://www.richelbilderbeek.nl/ToolEncranger.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Encranger version: " + Encranger::GetVersion());
  a.AddLibrary("LoopReader version: " + LoopReader<int>::GetVersion());
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::ToolEncrangerMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {
      Help::Option('c',"cipher","the ciphertext, will be decrypted"),
      Help::Option('k',"key","the encryption key, a number, zero by default"),
      Help::Option('t',"text","the plaintext, will be encrypted"),
      Help::Option('s',"silent","silence output, used for debugging")
    },
    {
      "Encranger -k 123 --text \"Hello World\"",
      "Encranger -k 123 --cipher \"bc30h3g8h287g\""
    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::ToolEncrangerMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p(new ProgramEncranger);
  assert(p);
  return p;

}

std::string ribi::ToolEncrangerMenuDialog::GetVersion() const noexcept
{
  return "2.7";
}

std::vector<std::string> ribi::ToolEncrangerMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2009-08-22: Version 1.0: initial version (then called 'Encranger') programmed in C++ Builder",
    "2011-03-06: Version 2.0: port to Qt Creator, renamed application to ToolEncranger",
    "2011-03-22: Version 2.1: seperated GUI from logic, added website version",
    "2011-04-25: Version 2.2: removed website version\'s Close button",
    "2011-06-22: Version 2.3: improved website version",
    "2011-08-31: Version 2.4: added arrows and Welcome image",
    "2013-09-27: Version 2.5: conformized for ProjectRichelBilderbeek",
    "2013-11-01: Version 2.6: improved console version",
    "2014-04-01: Version 2.7: added silent mode",
    "2014-07-21: Version 2.8: added picture to desktop menu"
  };
}

#ifndef NDEBUG
void ribi::ToolEncrangerMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  {
    ToolEncrangerMenuDialog d;
    d.Execute( {"Encranger", "-k", "123", "--text", "Hello World", "-s" } );
    d.Execute( {"Encranger", "-k", "123", "--cipher", "bc30h3g8h287g", "--silent" } );
  }
}
#endif
