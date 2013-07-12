//---------------------------------------------------------------------------
/*
RandomCode, class to generate random C++ code
Copyright (C) 2007  Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRandomCode.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "randomcode.h"

#include <cstdlib>

const std::vector<std::string> RandomCode::CreateRandomCode()
{
  std::vector<std::string> v;
  v.push_back("#include <iostream>");
  v.push_back("#include <string>");
  v.push_back("#include <vector>");
  v.push_back("");
  v.push_back("int main(int argc, char* argv[])");
  v.push_back("{");

  for (int i=0; i!=50; ++i)
  {
    v.push_back(CreateRandomLine(3+std::rand()%10));
  }
  v.push_back("  return 0;");
  v.push_back("}");
  return v;
}
//---------------------------------------------------------------------------
const std::string RandomCode::CreateRandomLine(const unsigned int length)
{
  std::string s = "  ";
  for (unsigned int i=0; i!=length; ++i)
  {
    s+=CreateRandomString();
  }
  s+=";";
  return s;
}
//---------------------------------------------------------------------------
const std::string RandomCode::CreateRandomString()
{
  switch (std::rand()%70)
  {
    case 0: return "a = ";
    case 1: return "b = ";
    case 2: return "c = ";
    case 3: return "d = ";
    case 4: return "e = ";
    case 5: return "f = ";
    case 6: return "g = ";
    case 7: return "h = ";
    case 8: return "i = ";
    case 9: return "j = ";
    case 10: return "k = ";
    case 11: return "l = ";
    case 12: return "m = ";
    case 13: return "n = ";
    case 14: return "o = ";
    case 15: return "p = ";
    case 16: return "q = ";
    case 17: return "r = ";
    case 18: return "s = ";
    case 19: return "t = ";
    case 20: return "u = ";
    case 21: return "v = ";
    case 22: return "w = ";
    case 23: return "x = ";
    case 24: return "y = ";
    case 25: return "z = ";
    case 26: return "{";
    case 27: return "}";
    case 28: return "(";
    case 29: return ")";
    case 30: return "*";
    case 31: return "&";
    case 32: return "int ";
    case 33: return "const ";
    case 34: return "double ";
    case 35: return "std::string ";
    case 36: return "++";
    case 37: return "--";
    case 38: return "+";
    case 39: return "-";
    case 40: return "/";
    case 41: return "*";
    case 42: return "static_cast<int>(";
    case 43: return "static_cast<double>(";
    case 44: return "class ";
    case 45: return "struct ";
    case 46: return "std::vector<double> ";
    case 47: return "std::vector<int> ";
    case 48: return "std::vector<std::string> ";
    case 49: return "std::vector<std::vector<double> >";
    case 50: return "std::vector<std::vector<int> >";
    case 51: return "std::vector<std::vector<std::string> >";
    case 52: return "for(int i=0; i!=j; ++i) { ";
    case 53: return "while(1) { ";
    case 55: return ")";
    case 56: return ")";
    case 57: return ")";
    case 58: return "}";
    case 59: return "}";
    case 60: return "}";
  }
  return " ";
}
//---------------------------------------------------------------------------
const std::vector<std::string> RandomCode::GetAbout()
{
  std::vector<std::string> v;
  v.push_back("Random Code, generates random C++ code");
  v.push_back("Version " + GetVersion());
  v.push_back("Copyright (C) 2007  Richel Bilderbeek");
  v.push_back("");
  v.push_back("Programmed by Richel Bilderbeek");
  v.push_back("on the 23rd of December 2010");
  v.push_back("");
  v.push_back("From http://www.richelbilderbeek.nl/ToolRandomCode.htm");
  v.push_back("Licenced under GPL 3.0");
  return v;
}
//---------------------------------------------------------------------------
const std::vector<std::string> RandomCode::GetLicence()
{
  std::vector<std::string> v;
  v.push_back("Random Code, generates random C++ code");
  v.push_back("Copyright (C) 2007  Richel Bilderbeek");
  v.push_back("");
  v.push_back("This program is free software: you can redistribute it and/or modify");
  v.push_back("it under the terms of the GNU General Public License as published by");
  v.push_back("the Free Software Foundation, either version 3 of the License, or");
  v.push_back("(at your option) any later version.");
  v.push_back("");
  v.push_back("This program is distributed in the hope that it will be useful,");
  v.push_back("but WITHOUT ANY WARRANTY; without even the implied warranty of");
  v.push_back("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the");
  v.push_back("GNU General Public License for more details.");
  v.push_back("\n");
  v.push_back("You should have received a copy of the GNU General Public License");
  v.push_back("along with this program.  If not, see <http://www.gnu.org/licenses/>.");
  return v;
}
//---------------------------------------------------------------------------
const std::string RandomCode::GetVersion()
{
  return "3.0";
}
//---------------------------------------------------------------------------
const std::vector<std::string> RandomCode::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("YYYY-MM-DD: Version X.Y: [description]");
  v.push_back("2007-10-19: Version 1.0: initial version");
  v.push_back("2010-12-23: Version 2.0: seperated code generation from user interface");
  v.push_back("2011-01-07: Version 3.0: RandomCode can be used as desktop and web application");
  return v;
}
//---------------------------------------------------------------------------
