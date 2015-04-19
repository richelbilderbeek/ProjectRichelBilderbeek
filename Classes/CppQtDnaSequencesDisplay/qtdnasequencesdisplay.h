#ifndef QTDNADISPLAY_H
#define QTDNADISPLAY_H

#include <QWidget>

namespace ribi { struct DnaSequence; }
namespace Ui { class QtDnaSequencesDisplay; }

class QtDnaSequencesDisplay : public QWidget
{
  Q_OBJECT

public:
  explicit QtDnaSequencesDisplay(QWidget *parent = 0);
  QtDnaSequencesDisplay(const QtDnaSequencesDisplay&) = delete;
  QtDnaSequencesDisplay& operator=(const QtDnaSequencesDisplay&) = delete;
  ~QtDnaSequencesDisplay();

  void SetDnaSequences(const std::vector<ribi::DnaSequence>& sequences) noexcept;

private:
  Ui::QtDnaSequencesDisplay *ui;

  static const std::string sm_fail;
};

#endif // QTDNADISPLAY_H
