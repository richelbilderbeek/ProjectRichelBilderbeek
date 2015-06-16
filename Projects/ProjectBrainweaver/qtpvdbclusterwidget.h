//---------------------------------------------------------------------------
/*
Brainweaver, tool to create and assess concept maps
Copyright (C) 2012-2015 The Brainweaver Team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ProjectBrainweaver.htm
//---------------------------------------------------------------------------
 #ifndef QTPVDBCLUSTERWIDGET_H
#define QTPVDBCLUSTERWIDGET_H


#include <map>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include <QTreeWidget>

#include "conceptmapcompetency.h"
#include "pvdbcluster.h"
#include "pvdbfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace pvdb {

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
  static void Test() noexcept;

  ///Write the widget its data to the cluster
  void WriteToCluster();

  void SetCorrectFlags() noexcept;
};

} //~namespace pvdb
} //~namespace ribi

#endif // QTPVDBCLUSTERWIDGET_H
