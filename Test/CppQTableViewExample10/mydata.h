#ifndef MYDATA_H
#define MYDATA_H

#include <string>
#include <tuple>
#include <vector>

struct MyData
{
  MyData();
  bool GetNo(const int row) const { return std::get<0>(m_data[row]); };
  const std::string& GetQuestion(const int row) const { return std::get<2>(m_data[row]); };
  int GetRowCount() const { return static_cast<int>(m_data.size()); }
  bool GetYes(const int row) const { return std::get<1>(m_data[row]); };
  void SetNo(const int row, const bool yes_no) { std::get<0>(m_data[row]) = yes_no; }
  void SetQuestion(const int row, const std::string& question)  { std::get<2>(m_data[row]) = question; }
  void SetYes(const int row, const bool yes_no) { std::get<1>(m_data[row]) = yes_no; }

  private:
  std::vector<std::tuple<bool,bool,std::string> > m_data;

  static const std::vector<std::tuple<bool,bool,std::string> > CreateData();
};

#endif // MYDATA_H
