#ifndef QTPVDBTESTNODEITEMDIALOG_H
#define QTPVDBTESTNODEITEMDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "pvdbnode.h"
#include "qtpvdbconceptitem.h"
#include "qtpvdbdisplayconceptitem.h"
#include "qtpvdbnodeitem.h"
#include "qtpvdbrateconceptitem.h"
#endif

namespace Ui { class QtPvdbTestNodeItemDialog; }

///Tests all QtPvdbConceptItem items when being a member of a QtPvdbNodeItem,
///especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtPvdbTestNodeItemDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtPvdbTestNodeItemDialog(QWidget *parent = 0);
  ~QtPvdbTestNodeItemDialog();

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
  const boost::shared_ptr<pvdb::Node> m_node;
  QtPvdbNodeItem* m_display_node;
  QtPvdbNodeItem* m_edit_node;
  QtPvdbNodeItem* m_rate_node;

  ///Get the Node via the route chosen by box_edit
  const boost::shared_ptr<pvdb::Node> GetNode();

  void OnRequestsSceneUpdate();

  static void Test();
};

#endif // QTPVDBTESTNODEITEMDIALOG_H
