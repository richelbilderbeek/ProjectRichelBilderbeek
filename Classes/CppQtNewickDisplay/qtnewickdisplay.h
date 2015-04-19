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

  enum class Lineages { all, extant };
  enum class Tool { NewickUtils, PhylogenyR };

  void DisplayBranchingTimes(
    std::string newick,
    const Lineages lineages
  ) noexcept;

  void DisplayBranchLengths(
    std::string newick,
    const Lineages lineages
  ) noexcept;

  void DisplayNewick(
    const std::string& newick,
    const Lineages lineages
  ) noexcept;

  void DisplayNewickToLttPlot(
    const std::string& newick,
    const Lineages lineages
  ) noexcept;

  void DisplayPhylogeny(
    const std::string& newick,
    const Lineages lineages,
    const Tool tool
  ) noexcept;



  static const std::string sm_fail;
};

#endif // QTNEWICKDISPLAY_H
