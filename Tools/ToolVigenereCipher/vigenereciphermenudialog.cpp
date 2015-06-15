//---------------------------------------------------------------------------
/*
VigenereCipher, Vigenere cipher tool
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
//From http://www.richelbilderbeek.nl/ToolVigenereCipher.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "vigenereciphermenudialog.h"

#include <cassert>
#include <iostream>
#include <boost/lexical_cast.hpp>

#include "loopreader.h"
#include "richelbilderbeekprogram.h"
#include "vigenerecipher.h"
#include "testtimer.h"
#include "vigenereciphermaindialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

int ribi::VigenereCipherMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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
  std::string key = "";
  for (int i=0; i!=argc-1; ++i) //-1 because the next argument will be used
  {
    if (argv[i] == "-k" || argv[i] == "--key")
    {
      key = argv[i+1];
    }
  }
  //Determine if plaintext is supplied, if yes: execute
  for (int i=0; i!=argc-1; ++i) //-1 because the next argument will be used
  {
    if (argv[i] == "-t" || argv[i] == "--text")
    {
      const std::string plaintext = argv[i + 1];
      VigenereCipherMainDialog d(key);
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
      VigenereCipherMainDialog d(key);
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

ribi::About ribi::VigenereCipherMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "VigenereCipher",
    "Vigenere cipher tool",
    "the 1st of April 2014",
    "2014-2015",
    "http://www.richelbilderbeek.nl/ToolVigenereCipher.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("VigenereCipher version: " + VigenereCipher::GetVersion());
  a.AddLibrary("LoopReader version: " + LoopReader<int>::GetVersion());
  return a;
}

ribi::Help ribi::VigenereCipherMenuDialog::GetHelp() const noexcept
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
      "VigenereCipher -k \"KEY\" --text \"HELLOWORLD\"",
      "VigenereCipher -k \"LEMON\" --cipher \"HELLOWORLD\""
    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::VigenereCipherMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p(new ProgramVigenereCipher);
  assert(p);
  return p;

}

std::string ribi::VigenereCipherMenuDialog::GetVersion() const noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::VigenereCipherMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2014-04-01: Version 1.0: initial version, copied from CaesarCipher"
  };
}

#ifndef NDEBUG
void ribi::VigenereCipherMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  {
    VigenereCipherMenuDialog d;
    d.Execute( {"VigenereCipher", "-k", "A", "--text", "HELLOWORLD", "-s" } );
    d.Execute( {"VigenereCipher", "-k", "AB", "--text", "HELLOWORLD", "-s" } );
    d.Execute( {"VigenereCipher", "-k", "ABC", "--text", "HELLOWORLD", "-s" } );
    d.Execute( {"VigenereCipher", "-k", "ABCDEF", "--cipher", "HELLOWORLD", "-s" } );
  }
}
#endif
