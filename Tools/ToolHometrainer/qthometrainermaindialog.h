#ifndef QTHOMETRAINERMAINDIALOG_H
#define QTHOMETRAINERMAINDIALOG_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtHometrainerMainDialog;
}

namespace ribi {

struct TestQuestionMainDialog;
struct QtQuestionDialog;

class QtHometrainerMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtHometrainerMainDialog(
    const std::vector<std::string>& questions,
    QWidget *parent = 0) noexcept;
  QtHometrainerMainDialog(const QtHometrainerMainDialog&) = delete;
  QtHometrainerMainDialog& operator=(const QtHometrainerMainDialog&) = delete;
  ~QtHometrainerMainDialog() noexcept;
  
  const boost::shared_ptr<const QtQuestionDialog> GetDialog() const { return m_dialog; }
  void SetQuestion(const std::string& s);

protected:
  void keyPressEvent(QKeyEvent* event);

private:
  Ui::QtHometrainerMainDialog *ui;
  std::size_t m_current_question_index;
  boost::shared_ptr<QtQuestionDialog> m_dialog;
  int m_n_correct;
  int m_n_incorrect;
  std::vector<std::string> m_questions;

  static boost::shared_ptr<QtQuestionDialog> CreateQtQuestionDialog(const std::string& s);
  void DisplayScore();
  void OnSubmitted(const bool is_correct);


  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void NewQuestion();

};

} //~namespace ribi

#endif // QTHOMETRAINERMAINDIALOG_H
