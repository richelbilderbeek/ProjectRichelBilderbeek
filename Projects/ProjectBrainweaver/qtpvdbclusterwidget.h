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
  explicit QtPvdbClusterWidget(
    boost::shared_ptr<pvdb::Cluster> cluster,
    QWidget* parent = 0);

  ///Add a top-level item
  void Add(const std::string& text);

  ///Do something random
  void DoRandomStuff();

  ///Get the cluster (after reading from the dialog)
  const boost::shared_ptr<pvdb::Cluster> GetCluster();

protected:
  void dropEvent(QDropEvent *event);

  void keyPressEvent(QKeyEvent *event);

private slots:
  void RemoveEmptyItem(QTreeWidgetItem*,int);

  ///Block: QtPvdbTreeWidgetItem must be added instead
  void addTopLevelItem(QTreeWidgetItem *item) { QTreeWidget::addTopLevelItem(item); }

private:
  ///The cluster
  const boost::shared_ptr<pvdb::Cluster> m_cluster;

  ///Build the widget from the cluster
  void BuildCluster();

  ///Find out the depth of an item
  int GetDepth(const QTreeWidgetItem * const item) const;

  ///Test this class
  static void Test();

  ///Write the widget its data to the cluster
  void WriteToCluster();
};

#endif // QTPVDBCLUSTERWIDGET_H
