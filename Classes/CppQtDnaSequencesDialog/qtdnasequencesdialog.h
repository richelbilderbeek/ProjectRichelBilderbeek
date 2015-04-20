#ifndef QTDNASEQUENCESDIALOG_H
#define QTDNASEQUENCESDIALOG_H

#include <QWidget>

namespace ribi { struct DnaSequence; }
namespace Ui { class QtDnaSequencesDialog; }

class QtDnaSequencesDialog : public QWidget
{
  Q_OBJECT

public:
  explicit QtDnaSequencesDialog(QWidget *parent = 0);
  QtDnaSequencesDialog(const QtDnaSequencesDialog&) = delete;
  QtDnaSequencesDialog& operator=(const QtDnaSequencesDialog&) = delete;
  ~QtDnaSequencesDialog();

  std::vector<ribi::DnaSequence> GetSequences() const noexcept;
  //void SetDnaSequences(const std::vector<ribi::DnaSequence>& sequences) noexcept;

private:
  Ui::QtDnaSequencesDialog *ui;

  static const std::string sm_fail;
};

#endif // QTDNASEQUENCESDIALOG_H
