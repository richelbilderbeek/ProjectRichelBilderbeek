#ifndef QTPVDBTESTEDGEITEMDIALOG_H
#define QTPVDBTESTEDGEITEMDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif


#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "pvdbedge.h"
#include "qtpvdbedgeitem.h"
#endif

namespace Ui { class QtPvdbTestEdgeItemDialog; }

///Tests all QtPvdbConceptItem items when being a member of a QtPvdbNodeItem,
///especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtPvdbTestEdgeItemDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtPvdbTestEdgeItemDialog(QWidget *parent = 0);
  ~QtPvdbTestEdgeItemDialog();
protected:

  void keyPressEvent(QKeyEvent *);

private slots:

  void on_box_competency_currentIndexChanged(int index);
  void on_edit_name_textChanged(const QString &arg1);
  void on_box_complexity_currentIndexChanged(const QString &arg1);
  void on_box_concreteness_currentIndexChanged(const QString &arg1);
  void on_box_specificity_currentIndexChanged(const QString &arg1);
  void on_edit_example_text_textChanged(const QString &arg1);

  void on_box_arrow_head_currentIndexChanged(int index);

  void on_box_arrow_tail_currentIndexChanged(int index);

private:

  Ui::QtPvdbTestEdgeItemDialog *ui;
  boost::shared_ptr<pvdb::Edge> m_edge;
  QtPvdbEdgeItem* m_edge_item;
  const boost::shared_ptr<pvdb::Node> m_from;
  const boost::shared_ptr<pvdb::Node> m_to;

  static const boost::shared_ptr<pvdb::Node> CreateFrom();
  static const boost::shared_ptr<pvdb::Node> CreateTo();

  ///Get the Edge via the route chosen by box_edit
  const boost::shared_ptr<pvdb::Edge> GetEdge();

  ///Called whenever an item requests a scene update
  void OnRequestSceneUpdate();

  static void Test();
};

#endif // QTPVDBTESTEDGEITEMDIALOG_H

