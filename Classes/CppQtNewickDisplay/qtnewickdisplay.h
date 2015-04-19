#ifndef QTNEWICKDISPLAY_H
#define QTNEWICKDISPLAY_H

#include <QWidget>

namespace Ui {
class QtNewickDisplay;
}

class QtNewickDisplay : public QWidget
{
  Q_OBJECT

public:
  explicit QtNewickDisplay(QWidget *parent = 0);
  QtNewickDisplay(const QtNewickDisplay&) = delete;
  QtNewickDisplay& operator=(const QtNewickDisplay&) = delete;
  ~QtNewickDisplay();

  void SetNewick(const std::string& newick) noexcept;

private:
  Ui::QtNewickDisplay *ui;


  void DisplayNewick(const std::string& newick) noexcept;
  void DisplayNewickExtant(const std::string& newick) noexcept;
  void DisplayNewickToLttPlot(const std::string& newick) noexcept;
  void DisplayNewickToLttPlotExtant(const std::string& newick) noexcept;
  void DisplayPhylogenyNewickUtilsAll(const std::string& newick) noexcept;
  void DisplayPhylogenyNewickUtilsExtant(const std::string& newick) noexcept;
  void DisplayPhylogenyRall(const std::string& newick) noexcept;
  void DisplayPhylogenyRextant(const std::string& newick) noexcept;

};

#endif // QTNEWICKDISPLAY_H
