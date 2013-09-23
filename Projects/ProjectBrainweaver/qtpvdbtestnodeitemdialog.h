#ifndef QTPVDBTESTNODEITEMDIALOG_H
#define QTPVDBTESTNODEITEMDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "pvdbfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtPvdbTestNodeItemDialog; }

namespace ribi {
namespace pvdb {

///Tests all QtPvdbConceptItem items when being a member of a QtPvdbNodeItem,
///especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtPvdbTestNodeItemDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtPvdbTestNodeItemDialog(QWidget *parent = 0);
  QtPvdbTestNodeItemDialog(const QtPvdbTestNodeItemDialog&) = delete;
  QtPvdbTestNodeItemDialog& operator=(const QtPvdbTestNodeItemDialog&) = delete;
  ~QtPvdbTestNodeItemDialog() noexcept;

protected:

  void keyPressEvent(QKeyEvent *);

private slots:

  void on_box_competency_currentIndexChanged(int index);
  void on_edit_name_textChanged(const QString &arg1);
  void on_box_complexity_currentIndexChanged(const QString &arg1);
  void on_box_concreteness_currentIndexChanged(const QString &arg1);
  void on_box_specificity_currentIndexChanged(const QString &arg1);
  void on_edit_example_text_textChanged(const QString &arg1);

private:

  Ui::QtPvdbTestNodeItemDialog *ui;
  const boost::shared_ptr<ribi::pvdb::Node> m_node;
  QtPvdbNodeItem* m_display_node;
  QtPvdbNodeItem* m_edit_node;
  QtPvdbNodeItem* m_rate_node;

  ///Get the Node via the route chosen by box_edit
  const boost::shared_ptr<ribi::pvdb::Node> GetNode();

  void OnRequestsSceneUpdate();

  static void Test();
};

} //~namespace pvdb
} //~namespace ribi

#endif // QTPVDBTESTNODEITEMDIALOG_H
