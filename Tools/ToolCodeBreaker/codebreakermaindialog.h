//---------------------------------------------------------------------------
/*
CodeBreaker, code breaking tool
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
//From http://www.richelbilderbeek.nl/ToolCodeBreaker.htm
//---------------------------------------------------------------------------
#ifndef CODEBREAKERMAINDIALOG_H
#define CODEBREAKERMAINDIALOG_H

#include <string>
#include <vector>
#include <boost/scoped_ptr.hpp>
#include "about.h"
#include "codebreaker.h"

namespace ribi {

struct CodeBreakerMainDialog
{
  CodeBreakerMainDialog() noexcept;

  std::string GetAdvice() const noexcept;

  const std::string& GetEncryptedText() const noexcept { return m_encrypted_text; }
  void SetEncryptedText(const std::string& s) noexcept;

  private:
  boost::scoped_ptr<CodeBreaker> m_codebreaker;
  std::string m_encrypted_text;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // CODEBREAKERMAINDIALOG_H
