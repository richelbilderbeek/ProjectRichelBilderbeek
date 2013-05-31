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
#ifndef UnitTestH
#define UnitTestH
//---------------------------------------------------------------------------
#include <string>
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
#include "BigIntegerLibrary.hh"
//---------------------------------------------------------------------------
struct Test
{
  Test(const std::string& any_newick, const double any_theta)
    : m_newick_str(any_newick),
      m_theta(any_theta),
      m_time(0.0),
      m_probability(0.0)
  {
    //Do nothing
  }
  virtual ~Test() {};
  virtual bool Execute() = 0;
  virtual const std::string GetTestName() const = 0;
  double GetProbability() const { return m_probability; }
  const std::string GetEwensProbability() const; //Ewensprobability = probability * num_of_combinations
  int GetTime() const { return m_time; }
  const BigInteger GetComplexity() const;

  const std::string& GetNewick() const { return m_newick_str; }
  double GetTheta() const { return m_theta; }

  bool Execute(
    const std::string& exe_filename,
    const std::string& full_command,
    const std::string& output_filename);

  private:
  const std::string m_newick_str;
  const double m_theta;
  double m_time;
  double m_probability;

  public:
  //helper functions
  static std::vector<boost::shared_ptr<Test> > CreateTests(
    const std::string& newick,
    const double theta,
    const int flags);
  static bool FileExists(const std::string& filename);
  static const std::vector<std::string> FileToVector(const std::string& fileName);
  static double ReadDoubleFromFile(const std::string& fileName);
};
//---------------------------------------------------------------------------
struct TestRavindran : public Test
{
  TestRavindran(const std::string& any_newick, const double any_theta)
  : Test(any_newick,any_theta) {}
  ~TestRavindran() {}
  bool Execute();
  const std::string GetTestName() const { return "Ravindran                    "; }
};
//---------------------------------------------------------------------------
struct TestEndversion2: public Test
{
  TestEndversion2(const std::string& any_newick, const double any_theta)
  : Test(any_newick,any_theta) {}
  ~TestEndversion2() {}
  bool Execute();
  const std::string GetTestName() const { return "TestProjectRampal_Endversion2"; }
};
//---------------------------------------------------------------------------
struct TestTwoDigitNewickDebug: public Test
{
  TestTwoDigitNewickDebug(const std::string& any_newick, const double any_theta)
  : Test(any_newick,any_theta) {}
  ~TestTwoDigitNewickDebug() {}
  bool Execute();
  const std::string GetTestName() const { return "TestTwoDigitNewickDebug"; }
};
//---------------------------------------------------------------------------
struct TestTwoDigitNewickRelease: public Test
{
  TestTwoDigitNewickRelease(const std::string& any_newick, const double any_theta)
  : Test(any_newick,any_theta) {}
  ~TestTwoDigitNewickRelease() {}
  bool Execute();
  const std::string GetTestName() const { return "TestTwoDigitNewickRelease"; }
};
//---------------------------------------------------------------------------
struct TestManyDigitNewickDebug: public Test
{
  TestManyDigitNewickDebug(const std::string& any_newick, const double any_theta)
  : Test(any_newick,any_theta) {}
  ~TestManyDigitNewickDebug() {}
  bool Execute();
  const std::string GetTestName() const { return "TestManyDigitNewickRelease"; }
};
//---------------------------------------------------------------------------
#endif
