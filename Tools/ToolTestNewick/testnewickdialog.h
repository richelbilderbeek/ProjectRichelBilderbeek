#ifndef TESTNEWICKDIALOG_H
#define TESTNEWICKDIALOG_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/tuple/tuple.hpp>
#include "about.h"
#include "testnewickresult.h"
#pragma GCC diagnostic pop

namespace ribi {

///TestNewickDialog is the graphics-independent
///part of QtTestNewickDialog (desktop application) and
///WtTestNewickDialog (web application)
struct TestNewickDialog
{
  typedef std::vector<TestNewickResult> TableType;
  TestNewickDialog(const int types = 63);
  void DoAutoCalculate(
    const std::string& newick_str,
    const std::string& theta_str,
    const std::string& max_complexity_str);
  void DoCalculate(
    const std::string& newick_str,
    const std::string& theta_str
  );
  void DoCalculate(
    const std::string& newick_str,
    const double theta
  );

  static const About GetAbout();
  static const std::vector<std::string> GetVersionHistory();
  static const std::string GetVersion();

  const std::string& GetText() const { return m_text; }
  const TableType& GetTable() const { return m_table; }

  void SaveTable(const std::string& filename) const;

  private:
  //Results of all calculations
  TableType m_table;
  //Output about the calculations
  std::string m_text;
  //The types of classes/algorithms used
  const int m_types;


  static double GetRandomUniform();
  static void RandomizeTimer();
  static const std::vector<double> ExtractProbabilities(
    const std::vector<TestNewickResult>& v);

  static const std::vector<std::string> GetHardBiologicalBinaryNewicks();
  static const std::vector<std::string> GetHardBinaryNewicks();
  static const std::vector<std::string> GetLightBiologicalBinaryNewicks();
  static const std::vector<std::string> GetLightBinaryNewicks();
  static const std::vector<std::string> GetLightTrinaryNewicks();
  static const std::vector<std::string> GetMediumBinaryNewicks();
  static const std::vector<std::string> GetManyBinaryNewicks();

};

} //~namespace ribi

#endif // TESTNEWICKDIALOG_H
