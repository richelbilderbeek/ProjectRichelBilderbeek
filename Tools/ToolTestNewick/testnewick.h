#ifndef TESTNEWICK_H
#define TESTNEWICK_H
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
#include "BigIntegerLibrary.hh"
//---------------------------------------------------------------------------
///TestNewick is the base class for testing Newicks for
///their calculated probabilities and its calculation time.
struct TestNewick
{
  TestNewick();
  virtual ~TestNewick() {}
  virtual bool CanCalculate(const std::string& newick_str, const double theta) = 0;
  virtual void Calculate(const std::string& newick_str, const double theta) = 0;
  virtual const std::string GetTestName() const = 0;

  double GetProbability() const { return m_probability; }
  double GetTime() const { return m_time; }

  protected:
  void SetProbability(const double probability);
  void SetTime(const double time);

  private:
  double m_time;
  double m_probability;

  public:
  static const std::vector<boost::shared_ptr<TestNewick> > CreateTests(const int flags);
  static const int m_flag_all;
  static const int m_flag_binary_newick_vector;
  static const int m_flag_many_digit_newick;
  static const int m_flag_newick_vector;
  static const int m_flag_ravindran;
  static const int m_flag_sorted_binary_newick_vector;
  static const int m_flag_two_digit_newick;

};
//---------------------------------------------------------------------------
struct TestBinaryNewickVector : public TestNewick
{
  TestBinaryNewickVector() : TestNewick() {}
  ~TestBinaryNewickVector() {}
  bool CanCalculate(const std::string& newick_str, const double theta);
  void Calculate(const std::string& newick_str, const double theta);
  const std::string GetTestName() const { return "BinaryNewickVector"; }
};
//---------------------------------------------------------------------------
struct TestManyDigitNewick : public TestNewick
{
  TestManyDigitNewick() : TestNewick() {}
  ~TestManyDigitNewick() {}
  bool CanCalculate(const std::string& newick_str, const double theta);
  void Calculate(const std::string& newick_str, const double theta);
  const std::string GetTestName() const { return "ManyDigitNewick"; }
};
//---------------------------------------------------------------------------
struct TestNewickVector : public TestNewick
{
  TestNewickVector() : TestNewick() {}
  ~TestNewickVector() {}
  bool CanCalculate(const std::string& newick_str, const double theta);
  void Calculate(const std::string& newick_str, const double theta);
  const std::string GetTestName() const { return "NewickVector"; }
};
//---------------------------------------------------------------------------
struct TestRavindran : public TestNewick
{
  TestRavindran() : TestNewick() {}
  ~TestRavindran() {}
  bool CanCalculate(const std::string& newick_str, const double theta);
  void Calculate(const std::string& newick_str, const double theta);
  const std::string GetTestName() const { return "Ravindran"; }
};
//---------------------------------------------------------------------------
struct TestSortedBinaryNewickVector : public TestNewick
{
  TestSortedBinaryNewickVector() : TestNewick() {}
  ~TestSortedBinaryNewickVector() {}
  bool CanCalculate(const std::string& newick_str, const double theta);
  void Calculate(const std::string& newick_str, const double theta);
  const std::string GetTestName() const { return "SortedBinaryNewickVector"; }
};
//---------------------------------------------------------------------------
struct TestTwoDigitNewick : public TestNewick
{
  TestTwoDigitNewick() : TestNewick() {}
  ~TestTwoDigitNewick() {}
  bool CanCalculate(const std::string& newick_str, const double theta);
  void Calculate(const std::string& newick_str, const double theta);
  const std::string GetTestName() const { return "TwoDigitNewick"; }
};
//---------------------------------------------------------------------------
#endif //~TESTNEWICK_H
