//---------------------------------------------------------------------------
/*
CaesarCipher, Caesar cipher tool
Copyright (C) 2014-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolCaesarCipher.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "caesarciphermenudialog.h"

#include <cassert>
#include <iostream>
#include <boost/lexical_cast.hpp>

#include "loopreader.h"
#include "caesarcipher.h"
#include "caesarciphermaindialog.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

int ribi::CaesarCipherMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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
      CaesarCipherMainDialog d;
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
      CaesarCipherMainDialog d;
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

ribi::About ribi::CaesarCipherMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "CaesarCipher",
    "Caesar cipher tool",
    "April 28th of 2015",
    "2014-2015",
    "http://www.richelbilderbeek.nl/ToolCaesarCipher.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("CaesarCipher version: " + CaesarCipher::GetVersion());
  a.AddLibrary("LoopReader version: " + LoopReader<int>::GetVersion());
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::CaesarCipherMenuDialog::GetHelp() const noexcept
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
      "CaesarCipher -k 123 --text \"HELLOWORLD\"",
      "CaesarCipher -k 123 --cipher \"HELLOWORLD\""
    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::CaesarCipherMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p(new ProgramCaesarCipher);
  assert(p);
  return p;

}

std::string ribi::CaesarCipherMenuDialog::GetVersion() const noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::CaesarCipherMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2014-04-01: Version 1.0: initial version, copied from CaesarCipher",
    "2015-04-28: Version 1.1: added nice menu screen to desktop version"
  };
}

#ifndef NDEBUG
void ribi::CaesarCipherMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    CaesarCipher(42);
    CaesarCipherMainDialog();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  {
    CaesarCipherMenuDialog d;
    d.Execute( {"CaesarCipher", "-k", "0", "--text", "HELLOWORLD", "-s" } );
    d.Execute( {"CaesarCipher", "-k", "1", "--text", "HELLOWORLD", "-s" } );
    d.Execute( {"CaesarCipher", "-k", "2", "--text", "HELLOWORLD", "-s" } );
    d.Execute( {"CaesarCipher", "-k", "123", "--cipher", "HELLOWORLD", "-s" } );
  }
}
#endif
