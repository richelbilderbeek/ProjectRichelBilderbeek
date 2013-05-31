#ifndef QTPVDBCLUSTERWIDGET_H
#define QTPVDBCLUSTERWIDGET_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <map>

#include <boost/shared_ptr.hpp>

#include <QTreeWidget>

#include "pvdbcompetency.h"
#include "pvdbcluster.h"

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else

#endif


class QtPvdbClusterWidget : public QTreeWidget
{
  Q_OBJECT

public:
  explicit QtPvdbClusterWidget(QWidget* parent = 0);

  ///Add a top-level item
  void Add(const std::string& text);

  ///Do something random
  void DoRandomStuff();

  ///Initialize the widget with a cluster
  void ReadFromCluster(const boost::shared_ptr<pvdb::Cluster>& cluster);

  ///Write the widget its data to a cluster
  const boost::shared_ptr<pvdb::Cluster> WriteToCluster() const;

protected:
  void dropEvent(QDropEvent *event);

  void keyPressEvent(QKeyEvent *event);

private slots:
  void RemoveEmptyItem(QTreeWidgetItem*,int);

  ///Block: QtPvdbTreeWidgetItem must be added instead
  void addTopLevelItem(QTreeWidgetItem *item) { QTreeWidget::addTopLevelItem(item); }

private:
  ///Find out the depth of an item
  int GetDepth(const QTreeWidgetItem * const item) const;

  ///Test this class
  static void Test();
};

#endif // QTPVDBCLUSTERWIDGET_H
