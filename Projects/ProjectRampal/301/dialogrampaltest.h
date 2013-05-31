#ifndef DIALOGRAMPALTEST_H
#define DIALOGRAMPALTEST_H
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
#include <QDialog>
//---------------------------------------------------------------------------
#include "BigIntegerLibrary.hh"
//---------------------------------------------------------------------------
namespace Ui {
  class DialogRampalTest;
}
//---------------------------------------------------------------------------
class DialogRampalTest : public QDialog
{
  Q_OBJECT

public:
  explicit DialogRampalTest(QWidget *parent = 0);
  ~DialogRampalTest();

struct Row
{
  std::string m_test_name;
  double m_probability;
  double m_time;
  std::string m_newick;
  BigInteger m_complexity;
};

protected:
  void changeEvent(QEvent *e);
  void resizeEvent(QResizeEvent *);

private:
  Ui::DialogRampalTest *ui;
  std::vector<Row> m_data;
  bool m_valid_input;
  int GetFlags() const;
  int GetNumTestsChecked() const;
  void ShowData();

private slots:
  void onAnyChange();
  void onBenchmark();
  void onStart();

};
//---------------------------------------------------------------------------
const std::vector<std::string> GetHardBiologicalNewicks();
//---------------------------------------------------------------------------
const std::vector<std::string> GetHardNewicks();
//---------------------------------------------------------------------------
const std::vector<std::string> GetLightBiologicalNewicks();
//---------------------------------------------------------------------------
const std::vector<std::string> GetLightNewicks();
//---------------------------------------------------------------------------
const std::vector<std::string> GetManyNewicks();
//---------------------------------------------------------------------------
const std::vector<std::string> GetMediumNewicks();
//---------------------------------------------------------------------------
#endif // DIALOGRAMPALTEST_H
