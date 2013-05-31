//---------------------------------------------------------------------------
/*
  The Rampal Etienne Project, calculates the probability of a phylogeny
  (C) 2009 Richel Bilderbeek

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
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#include <fstream>
#include <vector>
//---------------------------------------------------------------------------
#include <boost/numeric/conversion/cast.hpp>
#include <boost/timer.hpp>
//---------------------------------------------------------------------------
#include "binarynewickvector.h"
#include "newick.h"
#include "stopwatch.h"
#include "test.h"
//---------------------------------------------------------------------------
///Create all tests according to the flags given.
///Test parameters:\n
///i &  1: use Ravindran\n
///i &  2: use SortedNewick\n
///i &  4: use SmartSortedNewick\n
///i &  8: use RampalMain_Endversion2\n
///i & 16: use TestTwoDigitNewickDebug\n
///i & 32: use TestTwoDigitNewickRelease\n
///63: use all\n
std::vector<boost::shared_ptr<Test> > Test::CreateTests(
  const std::string& newick,
  const double theta,
  const int flags)
{
  std::vector<boost::shared_ptr<Test> > v;
  if (flags & 1)
  {
    boost::shared_ptr<Test> t(new TestRavindran(newick,theta));
    v.push_back(t);
  }
  if (flags & 2)
  {
    boost::shared_ptr<Test> t(new TestEndversion2(newick,theta));
    assert(t);
    v.push_back(t);
  }
  if (flags & 4)
  {
    boost::shared_ptr<Test> t(new TestTwoDigitNewickDebug(newick,theta));
    assert(t);
    v.push_back(t);
  }
  if (flags & 8)
  {
    boost::shared_ptr<Test> t(new TestTwoDigitNewickRelease(newick,theta));
    assert(t);
    v.push_back(t);
  }
  return v;
}
//---------------------------------------------------------------------------
///FileExists checks if a certain file exists
///From http://www.richelbilderbeek.nl/CppFileExists.htm
bool Test::FileExists(const std::string& filename)
{
  std::fstream f;
  f.open(filename.c_str(),std::ios::in);
  return f.is_open();
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppFileToVector.htm
const std::vector<std::string> Test::FileToVector(const std::string& fileName)
{
  assert(FileExists(fileName)==true);
  std::vector<std::string> myVector;
  std::ifstream in(fileName.c_str());
  std::string myString;
  for (int i=0; !in.eof(); ++i)
  {
    std::getline(in,myString);
    myVector.push_back(myString);
  }
  return myVector;
}
//---------------------------------------------------------------------------
const BigInteger Test::GetComplexity() const
{
  const BinaryNewickVector n(GetNewick());
  return Newick::CalcComplexity(n.Get());
}
//---------------------------------------------------------------------------
//Ewensprobability = probability * num_of_combinations
const std::string Test::GetEwensProbability() const
{
  const BigInteger n_combinations
    = Newick::CalcNumOfCombinations(
        BinaryNewickVector(GetNewick()).Get());
  try
  {
    const int i = n_combinations.toInt();
    const double d = boost::numeric_cast<double>(i);
    const double ewens_probability = d * GetProbability();
    return boost::lexical_cast<std::string>(ewens_probability);
  }
  catch (...)
  {
    const std::string s
      = bigIntegerToString(n_combinations)
      + std::string(" * ")
      + boost::lexical_cast<std::string>(GetProbability());
    return s;
  }
}
//---------------------------------------------------------------------------
bool Test::Execute(
  const std::string& exe_filename,
  const std::string& full_command,
  const std::string& output_filename)
{
  std::clog << "Starting '" << GetTestName() << "' for '"
    << this->GetNewick() << "'\n";

  if (!FileExists(exe_filename))
  {
    std::cerr << "Executable file '" << exe_filename << "' not found\n";
  }
  assert(FileExists(exe_filename));

  const Stopwatch s;

  const int sys_error = std::system(full_command.c_str());

  if (sys_error == 0)
  {
    m_time = s.elapsed();
    assert(FileExists(result_filename));
    m_probability = ReadDoubleFromFile(output_filename);
    return true;
  }
  else
  {
    m_time = 0;
    m_probability = 0.0;
    return false;
  }
}
//---------------------------------------------------------------------------
///ReadDoubleFromFile reads the first line of a file
///and converts it to a double.
///From http://www.richelbilderbeek.nl/CppReadDoubleFromFile.htm
double Test::ReadDoubleFromFile(const std::string& fileName)
{
  const std::vector<std::string> v = FileToVector(fileName);
  assert(v.empty()==false);
  const double d = std::atof(v[0].c_str());
  return d;
}
//---------------------------------------------------------------------------
//Returns if the test was successful
bool TestRavindran::Execute()
{
  std::clog << "Starting TestRavindranLinux for '"
    << this->GetNewick() << "'\n";

  if (GetComplexity() > 1000000) return false;

  //Write parameters to file
  {
    std::ofstream file("theta.txt");
    file << GetTheta();
  }
  {
    //Older version expects a /n at end
    std::ofstream file("phylogeny.txt");
    file << GetNewick() << "\n\n";
  }

  #ifdef WIN32
  const std::string exe_filename = "../Exes/phy_prob_12.exe";
  const std::string full_command = "../Exes/phy_prob_12.exe";
  #else
  const std::string exe_filename = "../Exes/phy_prob_linux";
  const std::string full_command = "./../Exes/phy_prob_linux";
  #endif

  return Test::Execute(
    exe_filename,
    full_command,
    "expected_probability.txt");
}
//---------------------------------------------------------------------------
///Just call the executable ProjectRampalMain_Endversion2
///with the parameters
bool TestEndversion2::Execute()
{
  #ifndef WIN32
  const std::string exe_filename = "../Exes/ProjectRampalMain_Endversion2";
  #else
  const std::string exe_filename = "../Exes/ProjectRampal.exe";
  #endif

  const std::string command_full =
  #ifndef WIN32
    std::string("./") +
  #endif
    exe_filename
    + " "
    + boost::lexical_cast<std::string>(GetTheta())
    + " \""
    + GetNewick()
    + "\"";

  const std::string output_filename = "Result_probability.txt";

  return Test::Execute(exe_filename,command_full,output_filename);
}
//---------------------------------------------------------------------------
///Just call the executable TestTwoDigitNewickDebug
///with the parameters
bool TestTwoDigitNewickDebug::Execute()
{
  #ifndef WIN32
  const std::string exe_filename = "../Exes/TestTwoDigitNewickUbuntuDebug";
  #else
  const std::string exe_filename = "../Exes/TestTwoDigitNewickWinDebug.exe";
  #endif

  const std::string command_full =
  #ifndef WIN32
    std::string("./") +
  #endif
    exe_filename
    + " "
    + boost::lexical_cast<std::string>(GetTheta())
    + " \""
    + GetNewick()
    + "\"";
  const std::string output_filename = "Result_probability.txt";
  return Test::Execute(exe_filename,command_full,output_filename);

  /*
  std::clog << "Starting TestTwoDigitNewickDebug for '"
    << this->GetNewick() << "'\n";
  const std::string filename
  #ifndef WIN32
    = "../../../Tools/ToolTestTwoDigitNewick-build-desktop/TestTwoDigitNewickUbuntuDebug";
  #else
    = "../../../Tools/ToolTestTwoDigitNewick/debug/TestNewickVectorWinDebug.exe";
  #endif
  if (!FileExists(filename))
  {
    std::cerr << "File '" << filename << "' not found\n";
  }
  assert(FileExists(filename));

  const std::string command =
  #ifndef WIN32
    std::string("./") +
  #endif
    filename
    + " "
    + boost::lexical_cast<std::string>(GetTheta())
    + " \""
    + GetNewick()
    + "\"";

  const Stopwatch s;

  const int sys_error = std::system(command.c_str());
  if (sys_error == 0)
  {
    time = s.elapsed();
    const std::string result_filename = "Result_probability.txt";
    assert(FileExists(result_filename));
    probability = ReadDoubleFromFile(result_filename);
    return true;
  }
  else
  {
    time = 0;
    probability = 0.0;
    return false;
  }
  */
}
//---------------------------------------------------------------------------
///Just call the executable TestTwoDigitNewickRelease
///with the parameters
bool TestTwoDigitNewickRelease::Execute()
{
  #ifndef WIN32
  const std::string exe_filename = "../Exes/TestTwoDigitNewickUbuntuRelease";
  #else
  const std::string exe_filename = "../Exes/TestTwoDigitNewickWinRelease.exe";
  #endif

  const std::string command_full =
  #ifndef WIN32
    std::string("./") +
  #endif
    exe_filename
    + " "
    + boost::lexical_cast<std::string>(GetTheta())
    + " \""
    + GetNewick()
    + "\"";
  const std::string output_filename = "Result_probability.txt";
  return Test::Execute(exe_filename,command_full,output_filename);
  /*
  std::clog << "Starting TestTwoDigitNewickRelease for '"
    << this->GetNewick() << "'\n";
  const std::string filename
  #ifndef WIN32
    = "../../../Tools/ToolTestTwoDigitNewick-build-desktop/TestTwoDigitNewickUbuntuRelease";
  #else
    = "../../../Tools/ToolTestTwoDigitNewick/release/TestNewickVectorWinRelease.exe";
  #endif
  assert(FileExists(filename));
  if (!FileExists(filename))
  {
    std::cerr << "File '" << filename << "' not found\n";
  }
  const std::string command =
  #ifndef WIN32
    std::string("./") +
  #endif
    filename
    + " "
    + boost::lexical_cast<std::string>(GetTheta())
    + " \""
    + GetNewick()
    + "\"";

  const Stopwatch s;

  const int sys_error = std::system(command.c_str());

  if (sys_error == 0)
  {
    m_time = s.elapsed();
    const std::string result_filename = "Result_probability.txt";
    assert(FileExists(result_filename));
    m_probability = ReadDoubleFromFile(result_filename);
    return true;
  }
  else
  {
    m_time = 0;
    m_probability = 0.0;
    return false;
  }
  */
}
//---------------------------------------------------------------------------
///Just call the executable TestTwoDigitNewickDebug
///with the parameters
bool TestManyDigitNewickDebug::Execute()
{
  #ifndef WIN32
  const std::string exe_filename = "../Exes/TestManyDigitNewickUbuntuDebug";
  #else
  const std::string exe_filename = "../Exes/TestManyDigitNewickWinDebug.exe";
  #endif

  const std::string command_full =
  #ifndef WIN32
    std::string("./") +
  #endif
    exe_filename
    + " "
    + boost::lexical_cast<std::string>(GetTheta())
    + " \""
    + GetNewick()
    + "\"";

  const std::string output_filename = "Result_probability.txt";

  return Test::Execute(exe_filename,command_full,output_filename);
}
//---------------------------------------------------------------------------
