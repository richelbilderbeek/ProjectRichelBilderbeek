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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtpvdbtestcreatesubconceptmapdialog.h"

#include <cassert>
#include <boost/numeric/conversion/cast.hpp>
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "qtconceptmap.h"
#include "ui_qtpvdbtestcreatesubconceptmapdialog.h"
#pragma GCC diagnostic pop


ribi::pvdb::QtPvdbTestCreateSubConceptMapDialog::QtPvdbTestCreateSubConceptMapDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtPvdbTestCreateSubConceptMapDialog),
  m_qtconceptmap{},
  m_qtconceptmap_sub{}
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif
  const int n_tests = boost::numeric_cast<int>(cmap::ConceptMapFactory().GetAllTests().size());
  ui->box_index->setMaximum(n_tests - 1); //-1: 0-based counting

  QObject::connect(ui->box_index,SIGNAL(valueChanged(int)),this,SLOT(OnConceptMapChanged()));
  QObject::connect(ui->box_index_sub,SIGNAL(valueChanged(int)),this,SLOT(OnSubConceptMapChanged()));

  OnConceptMapChanged();
  OnSubConceptMapChanged();
}

ribi::pvdb::QtPvdbTestCreateSubConceptMapDialog::~QtPvdbTestCreateSubConceptMapDialog() noexcept
{
  delete ui;
}

void ribi::pvdb::QtPvdbTestCreateSubConceptMapDialog::OnConceptMapChanged()
{
  const int i = ui->box_index->value();
  const std::vector<boost::shared_ptr<ribi::cmap::ConceptMap> > v = ribi::cmap::ConceptMapFactory().GetAllTests();
  assert(i < boost::numeric_cast<int>(v.size()));
  assert(v[i]);
  const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map = v[i];
  assert(concept_map);

  if(!ui->widget_concept_map->layout())
  {
    QLayout * const my_layout = new QVBoxLayout;
    ui->widget_concept_map->setLayout(my_layout);
  }

  assert(ui->widget_concept_map->layout());
  m_qtconceptmap.reset(new cmap::QtConceptMap);
  m_qtconceptmap->SetConceptMap(concept_map);
  ui->widget_concept_map->layout()->addWidget(m_qtconceptmap.get());

  #ifdef RJCB_TODO //TODO RJCB
  const std::vector<boost::shared_ptr<ribi::cmap::ConceptMap> > subs = concept_map->CreateSubs();
  const int n_subs = boost::numeric_cast<int>(subs.size());
  assert(n_subs != 0);
  ui->box_index_sub->setMaximum(n_subs - 1); //-1: 0-based counting
  ui->box_index_sub->setValue(0);
  #endif
}

void ribi::pvdb::QtPvdbTestCreateSubConceptMapDialog::OnSubConceptMapChanged()
{
  #ifdef TODO_RJCB //TODO RJCB: Put back in
  const int i = ui->box_index->value();
  const std::vector<boost::shared_ptr<ribi::cmap::ConceptMap> > v = ribi::cmap::ConceptMapFactory::GetAllTests();
  assert(i < boost::numeric_cast<int>(v.size()));
  const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map = v[i];
  const std::vector<boost::shared_ptr<ribi::cmap::ConceptMap> > subs = concept_map->CreateSubs();
  const int j = ui->box_index_sub->value();
  assert(j < boost::numeric_cast<int>(subs.size()));
  const boost::shared_ptr<ribi::cmap::ConceptMap> sub = subs[j];

  if(!ui->widget_sub_concept_map->layout())
  {
    QLayout * const my_layout = new QVBoxLayout;
    ui->widget_sub_concept_map->setLayout(my_layout);
  }

  assert(ui->widget_sub_concept_map->layout());
  m_sub_concept_map.reset(new cmap::QtDisplayConceptMap(sub));
  ui->widget_sub_concept_map->layout()->addWidget(m_sub_concept_map.get());
  #endif //TODO RJCB: Put back in
}


#ifndef NDEBUG
void ribi::pvdb::QtPvdbTestCreateSubConceptMapDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  QtPvdbTestCreateSubConceptMapDialog d;
  const int max = d.ui->box_index->maximum();
  for (int i=0; i!=max; ++i)
  {
    d.ui->box_index->setValue(i);

    const int max_sub = d.ui->box_index_sub->maximum();
    for (int j=0; j!=max_sub; ++j)
    {
      d.ui->box_index_sub->setValue(j);
    }
  }
}
#endif
