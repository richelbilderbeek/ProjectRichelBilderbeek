#ifndef QTPVDBRATECONCEPTTALLYDIALOG_H
#define QTPVDBRATECONCEPTTALLYDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtConceptMapRateConceptTallyDialog; }

namespace ribi {
namespace cmap {

class QtConceptMapRateConceptTallyDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  ///Sub concept map is modified by this dialog
  explicit QtConceptMapRateConceptTallyDialog(
    const boost::shared_ptr</* const */ ribi::cmap::ConceptMap> sub_concept_map,
    QWidget *parent = 0);
  QtConceptMapRateConceptTallyDialog(const QtConceptMapRateConceptTallyDialog&) = delete;
  QtConceptMapRateConceptTallyDialog& operator=(const QtConceptMapRateConceptTallyDialog&) = delete;
  ~QtConceptMapRateConceptTallyDialog() noexcept;

  static const boost::shared_ptr<ribi::cmap::ConceptMap> CreateTestConceptMap();

  ///Obtain the suggested complexity, calculated from this dialog
  int GetSuggestedComplexity() const;

  ///Obtain the suggested concreteness, calculated from this dialog
  int GetSuggestedConcreteness() const;

  ///Obtain the suggested specificity, calculated from this dialog
  int GetSuggestedSpecificity() const;

protected:
  void keyPressEvent(QKeyEvent *);
  void resizeEvent(QResizeEvent *);
private slots:
  void on_button_ok_clicked();
  void OnCellChanged(int row, int col);

private:
  Ui::QtConceptMapRateConceptTallyDialog *ui;
  //const boost::shared_ptr</* const */ ribi::cmap::ConceptMap> m_map;

  ///The concept map is converted to this data type
  ///The std::vector index equals the row
  ///Every row is a pair of a boost::shared_ptr<ribi::cmap::Concept> and an integer
  ///The boost::shared_ptr<ribi::cmap::Concept> is the concept being judged,
  ///  which might be the concept on the focal node and the concept on the egdes connected to the focal node
  ///The index is the index of the example being judged, or -1, denoting it is the concept name being judged
  typedef std::pair<boost::shared_ptr<ribi::cmap::Concept>,int> Row;
  const std::vector<Row> m_data;

  static const std::vector<Row>
    CreateData(const boost::shared_ptr</* const */ ribi::cmap::ConceptMap> map);

  #ifndef NDEBUG
  static void Test();
  #endif

};

} //~namespace pvdb
} //~namespace ribi

#endif // QTPVDBRATECONCEPTTALLYDIALOG_H
