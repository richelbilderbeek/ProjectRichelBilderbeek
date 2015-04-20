#ifndef QTBEASTDISPLAY_H
#define QTBEASTDISPLAY_H

#include <QWidget>

namespace ribi { struct DnaSequence; }
namespace Ui { class QtBeastDisplay; }

class QtBeastDisplay : public QWidget
{
  Q_OBJECT

public:
  explicit QtBeastDisplay(QWidget *parent = 0);
  QtBeastDisplay(const QtBeastDisplay&) = delete;
  QtBeastDisplay& operator=(const QtBeastDisplay&) = delete;
  ~QtBeastDisplay();

  void Analyze(
    const std::vector<ribi::DnaSequence>& sequences,
    const int mcmc_chainlength
  ) noexcept;

private:
  Ui::QtBeastDisplay *ui;

  static const std::string sm_fail;

  void AnalyzeBirthDeath(
    const std::vector<ribi::DnaSequence>& sequences,
    const int mcmc_chainlength
  ) noexcept;
  /*
  void AnalyzeCoalescent(
    const std::vector<ribi::DnaSequence>& sequences,
    const int mcmc_chainlength
  ) noexcept;
  */
};

#endif // QTBEASTDISPLAY_H
