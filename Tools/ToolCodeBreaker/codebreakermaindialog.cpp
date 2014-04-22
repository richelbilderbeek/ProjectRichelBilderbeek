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
#include "codebreakermaindialog.h"

#include <cassert>
#include <sstream>

#include "trace.h"

ribi::CodeBreakerMainDialog::CodeBreakerMainDialog() noexcept
  : m_codebreaker(new CodeBreaker),
    m_encrypted_text{}
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::string ribi::CodeBreakerMainDialog::GetAdvice() const noexcept
{
  std::stringstream s;



  return s.str();
}

void ribi::CodeBreakerMainDialog::SetEncryptedText(const std::string& s) noexcept
{
  m_encrypted_text = s;
}

#ifndef NDEBUG
void ribi::CodeBreakerMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::CodeBreakerMainDialog::Test");
  {
    CodeBreaker b;
    CodeBreakerMainDialog d;
    d.SetEncryptedText(b.GetExampleEnglish());
  }
  TRACE("Finished ribi::CodeBreakerMainDialog::Test successfully");
}
#endif
