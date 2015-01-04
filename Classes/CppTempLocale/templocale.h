//---------------------------------------------------------------------------
/*
TempLocale, class for a temporary std::locale
Copyright (C) 2015-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppTempLocale.htm
//---------------------------------------------------------------------------
#ifndef RIBI_TEMPLOCALE_H
#define RIBI_TEMPLOCALE_H

#include <string>
#include <vector>
#include <memory>

namespace ribi {

struct TempLocale
{
  explicit TempLocale(
    const std::string& temp_locale_name
  );
  TempLocale(const TempLocale&) = delete;
  TempLocale& operator=(const TempLocale&) = delete;
  ~TempLocale() noexcept;
  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  private:
  struct TempLocaleImpl;
  const std::unique_ptr<TempLocaleImpl> m_impl;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // STOPWATCH_H
