//---------------------------------------------------------------------------
/*
CodeBreaker, code breaking tool
Copyright (C) 2014-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolCodeBreaker.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "codebreakermenudialog.h"

#include <cassert>
#include <iostream>
#include <boost/lexical_cast.hpp>

#include "caesarcipher.h"
#include "caesarciphermenudialog.h"
#include "codebreaker.h"
#include "codebreakermaindialog.h"
#include "loopreader.h"
#include "trace.h"
#include "vigenerecipher.h"
#include "vigenereciphermenudialog.h"
#pragma GCC diagnostic pop

int ribi::CodeBreakerMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

  //Determine if plaintext is supplied, if yes: execute
  for (int i=0; i!=argc-1; ++i) //-1 because the next argument will be used
  {
    if (argv[i] == "-t" || argv[i] == "--text")
    {
      const std::string plaintext = argv[i + 1];
      CodeBreakerMainDialog d;
      d.SetEncryptedText(plaintext);
      if (!is_silent) { std::cout << d.GetAdvice() << '\n'; }
      return 0;
    }
  }
  return 0;
}

ribi::About ribi::CodeBreakerMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "CodeBreaker",
    "code breaking tool",
    "the 4th of April 2014",
    "2014-2014",
    "http://www.richelbilderbeek.nl/ToolCodeBreaker.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("CaesarCipher (class) version: " + CaesarCipher::GetVersion());
  a.AddLibrary("CaesarCipher (tool) version: " + CaesarCipherMenuDialog().GetVersion());
  a.AddLibrary("CodeBreaker (class) version: " + CodeBreaker::GetVersion());
  a.AddLibrary("LoopReader version: " + LoopReader<int>::GetVersion());
  a.AddLibrary("VigenereCipher (class) version: " + VigenereCipher::GetVersion());
  a.AddLibrary("VigenereCipher (tool) version: " + VigenereCipherMenuDialog().GetVersion());
  return a;
}

ribi::Help ribi::CodeBreakerMenuDialog::GetHelp() const noexcept
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
      "CodeBreaker -k 123 --text \"helloworld\"",
      "CodeBreaker -k 123 --cipher \"helloworld\""
    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::CodeBreakerMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p(new ProgramCodeBreaker);
  assert(p);
  return p;

}

std::string ribi::CodeBreakerMenuDialog::GetVersion() const noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::CodeBreakerMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2014-04-04: Version 1.0: initial version"
  };
}

#ifndef NDEBUG
void ribi::CodeBreakerMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::ToolCodeBreakerMenuDialog::Test");
  {
    CodeBreakerMenuDialog d;
    d.Execute( {"CodeBreaker", "-k", "0", "--text", "helloworld", "-s" } );
    d.Execute( {"CodeBreaker", "-k", "1", "--text", "helloworld", "-s" } );
    d.Execute( {"CodeBreaker", "-k", "2", "--text", "helloworld", "-s" } );
    d.Execute( {"CodeBreaker", "-k", "123", "--cipher", "helloworld", "-s" } );
  }
  TRACE("Finished ribi::ToolCodeBreakerMenuDialog::Test successfully");
}
#endif
