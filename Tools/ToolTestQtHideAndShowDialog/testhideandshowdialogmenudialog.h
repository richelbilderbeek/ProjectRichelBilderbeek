#ifndef TESTNEWICKVECTORDIALOG_H
#define TESTNEWICKVECTORDIALOG_H

#include <string>
#include <vector>
#include <boost/scoped_ptr.hpp>
#include "about.h"

namespace ribi {

struct NewickVector;

struct TestNewickVectorDialog
{
  TestNewickVectorDialog() noexcept;
  void AutoCalculate() noexcept;
  void Calculate() noexcept;
  void SetAnalyseCalculation(const bool b) noexcept;
  void SetCompareToTwoDigitNewick(const bool b) noexcept;
  void SetMaxComplexity(const std::string& s);
  void SetNewick(const std::string& s);
  void SetTheta(const std::string& s);
  const std::vector<std::string>& GetText() const noexcept { return m_text; }

  private:
  //Input
  bool m_analyse_calculation;
  bool m_compare;
  std::string m_max_complexity_str;
  std::string m_newick_str;
  std::string m_theta_str;
  //Internal
  boost::scoped_ptr<NewickVector> m_newick;
  double m_theta;
  //Output
  std::string m_complexity;
  double m_denominator;
  std::string m_n_combinations;
  std::string m_n_symmetries;

  std::vector<std::string> m_text;

  void Analyse() noexcept;
  void AnalyseArity() noexcept;
  void AnalyseCalculation() noexcept;
  void AnalyseRootBranches() noexcept;
  void AnalyseSimplerNewicks() noexcept;
  bool CheckMaxComplexity() noexcept;
  bool CheckNewick() noexcept;

  ///Check if theta is valid
  bool CheckTheta() noexcept;

  public:

  static About GetAbout() noexcept;
  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // TESTNEWICKVECTORDIALOG_H
