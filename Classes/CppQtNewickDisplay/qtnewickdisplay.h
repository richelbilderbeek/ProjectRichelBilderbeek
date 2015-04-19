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

  void DisplayPhylogeny(
    const std::string& newick,
    const Lineages lineages,
    const Tool tool
  ) noexcept;


  void DisplayBranchLengthsAll(const std::string& newick) noexcept;
  void DisplayBranchLengthsExtant(const std::string& newick) noexcept;
  void DisplayNewickAll(const std::string& newick) noexcept;
  void DisplayNewickExtant(const std::string& newick) noexcept;
  void DisplayNewickToLttPlotAll(const std::string& newick) noexcept;
  void DisplayNewickToLttPlotExtant(const std::string& newick) noexcept;
  /*
  void DisplayPhylogenyNewickUtilsAll(const std::string& newick) noexcept;
  void DisplayPhylogenyNewickUtilsExtant(const std::string& newick) noexcept;
  void DisplayPhylogenyRall(const std::string& newick) noexcept;
  void DisplayPhylogenyRextant(const std::string& newick) noexcept;
  */
  static const std::string sm_fail;
};

#endif // QTNEWICKDISPLAY_H
