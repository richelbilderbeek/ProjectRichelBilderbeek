//---------------------------------------------------------------------------
/*
QtConceptMap, Qt classes for display and interaction with ConceptMap
Copyright (C) 2013-2015 The Brainweaver Team

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
//From http://www.richelbilderbeek.nl/CppQtConceptMap.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmapconcepteditdialog.h"

#include <cassert>

#include <QKeyEvent>
#include <QObjectList>

#include "conceptmapcompetency.h"
#include "conceptmapexample.h"
#include "conceptmapexamplefactory.h"
#include "conceptmapexamplesfactory.h"
#include "conceptmapexamples.h"
#include "conceptmaphelper.h"
#include "conceptmapconcept.h"
#include "conceptmapconceptfactory.h"
#include "qtconceptmapcompetency.h"
#include "ui_qtconceptmapconcepteditdialog.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

///QTreeWidgetItem with the only function of storing a cmap::Competency additionally, only used in testing
struct QtConceptMapListWidgetItem : public QListWidgetItem
{
  QtConceptMapListWidgetItem(
    const ribi::cmap::Competency competency
    )
    : QListWidgetItem(0),
      m_competency(competency)
  {

  }
  const ribi::cmap::Competency m_competency;
};

ribi::cmap::QtConceptMapConceptEditDialog::QtConceptMapConceptEditDialog(
  const boost::shared_ptr<Concept> concept,
  QWidget* parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtConceptMapConceptEditDialog),
#ifdef CONCEPTMAP_WRITE_TO_CONCEPT
    m_rating_complexity(concept->GetRatingComplexity()),
    m_rating_concreteness(concept->GetRatingConcreteness()),
    m_rating_specificity(concept->GetRatingSpecificity())
#else
    m_concept(concept)
#endif
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  assert(concept);
  #endif

  //Convert the concept to its GUI elements
  //Add the name
  ui->edit_concept->setText(concept->GetName().c_str());
  //Add the examples
  const std::vector<boost::shared_ptr<const cmap::Example> > v = AddConst(concept->GetExamples()->Get());
  std::for_each(v.begin(),v.end(),
    [this](const boost::shared_ptr<const cmap::Example>& s)
    {
      assert(!s->GetText().empty());
      QtConceptMapListWidgetItem * const item = new QtConceptMapListWidgetItem(s->GetCompetency());
      item->setText(s->GetText().c_str());
      item->setFlags(
            Qt::ItemIsSelectable
          | Qt::ItemIsEnabled
          | Qt::ItemIsEditable
          | Qt::ItemIsDragEnabled
          | Qt::ItemIsDropEnabled);
      ui->list_examples->addItem(item);
    }
  );

  assert(ui->list_examples->isEnabled());
  QObject::connect(
    ui->list_examples,
    SIGNAL(itemChanged(QListWidgetItem*)),
    this,
    SLOT(RemoveEmptyItem(QListWidgetItem*)));
}

ribi::cmap::QtConceptMapConceptEditDialog::~QtConceptMapConceptEditDialog() noexcept
{
  delete ui;
}

void ribi::cmap::QtConceptMapConceptEditDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape) { close(); return; }

  if (e->key()  == Qt::Key_Enter || e->key()  == Qt::Key_Return)
  {
    if (e->modifiers() & Qt::AltModifier)
    {
      on_button_ok_clicked();
      return;
    }
  }
  //QDialog::keyPressEvent(e); //Causes dialog to close unwanted?
}

void ribi::cmap::QtConceptMapConceptEditDialog::on_button_add_clicked()
{
  //Close when the user has entered an empty edit
  if (ui->edit_text->text().isEmpty())
  {
    close();
    return;
  }

  {
    QListWidgetItem * const item = new QListWidgetItem;
    item->setText(ui->edit_text->text());
    item->setFlags(
          Qt::ItemIsSelectable
        | Qt::ItemIsEnabled
        | Qt::ItemIsEditable
        | Qt::ItemIsDragEnabled
        | Qt::ItemIsDropEnabled);
    ui->list_examples->addItem(item);
  }
  ui->edit_text->clear();
  ui->edit_text->setFocus();
}

void ribi::cmap::QtConceptMapConceptEditDialog::RemoveEmptyItem(QListWidgetItem * item)
{
  if (item->text().isEmpty())
  {
    delete item;
    this->update();
  }
}

#ifndef NDEBUG
void ribi::cmap::QtConceptMapConceptEditDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  {
    //Assume reading in a concept and clicking OK without modification does not modify anything
    const auto v = ribi::cmap::ConceptFactory().GetTests();
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<ribi::cmap::Concept>& concept)
      {
        const boost::shared_ptr<const ribi::cmap::Concept> old_concept = ConceptFactory().DeepCopy(concept);
        assert(concept != old_concept);
        assert(*concept == *old_concept);
        QtConceptMapConceptEditDialog d(concept);
        //Do nothing...
        d.on_button_ok_clicked();
        #ifdef CONCEPTMAP_WRITE_TO_CONCEPT
        assert(d.WriteToConcept() == old_concept);
        #else
        assert(*concept == *old_concept);
        #endif
      }
    );
  }
  {
    //Assume reading in a concept and clicking OK after modification of the name does modify concept
    const auto v = ribi::cmap::ConceptFactory().GetTests();
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<ribi::cmap::Concept>& concept)
      {
        const boost::shared_ptr<const ribi::cmap::Concept> old_concept = ConceptFactory().DeepCopy(concept);
        assert(*concept == *old_concept);
        QtConceptMapConceptEditDialog d(concept);
        d.ui->edit_concept->setText(d.ui->edit_concept->text() + "MODIFICATION");
        d.on_button_ok_clicked();
        #ifdef CONCEPTMAP_WRITE_TO_CONCEPT
        TRACE("TODO");
        #else
        //TODO
        //assert(concept != old_concept);
        #endif
      }
    );
  }
  {
    //Assume reading in a concept and clicking OK after adding an example
    const auto v = ribi::cmap::ConceptFactory().GetTests();
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<ribi::cmap::Concept>& concept)
      {
        const boost::shared_ptr<const ribi::cmap::Concept> old_concept = ConceptFactory().DeepCopy(concept);
        assert(*concept == *old_concept);
        QtConceptMapConceptEditDialog d(concept);
        assert(d.ui->edit_text->text().isEmpty());
        d.ui->edit_text->setText("TO BE ADDED EXAMPLE");
        d.on_button_add_clicked(); //Should add
        d.on_button_ok_clicked();
        #ifdef CONCEPTMAP_WRITE_TO_CONCEPT
        TRACE("TODO");
        #else
        TRACE("TODO");
        //assert(concept != old_concept);
        #endif
      }
    );
  }
  {
    //Assume reading in a concept and NOT clicking OK does not change the concept,
    //even when having changed the name and examples in the GUI
    const auto v = ribi::cmap::ConceptFactory().GetTests();
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<ribi::cmap::Concept>& concept)
      {
        const boost::shared_ptr<const ribi::cmap::Concept> old_concept = ConceptFactory().DeepCopy(concept);
        assert(*concept == *old_concept);
        QtConceptMapConceptEditDialog d(concept);
        //Change name
        d.ui->edit_concept->setText(d.ui->edit_concept->text() + "MODIFICATION");
        //Change examples
        assert(d.ui->edit_text->text().isEmpty());
        d.ui->edit_text->setText("TO BE ADDED EXAMPLE");
        d.on_button_add_clicked(); //Should add
        //DO NOT PRESS OK d.on_button_ok_clicked();
        #ifdef CONCEPTMAP_WRITE_TO_CONCEPT
        TRACE("TODO");
        #else
        assert(*concept == *old_concept);
        #endif
      }
    );
  }
  TRACE("ribi::cmap::QtConceptMapConceptEditDialog::Test completed successfully");

}
#endif

void ribi::cmap::QtConceptMapConceptEditDialog::on_button_ok_clicked()
{
  #ifndef CONCEPTMAP_WRITE_TO_CONCEPT
  assert(m_concept);
  //Name
  const std::string name = ui->edit_concept->text().toStdString();
  //Examples
  std::vector<boost::shared_ptr<cmap::Example> > v;

  const int n_items = ui->list_examples->count();
  for (int i=0; i!=n_items; ++i)
  {
    const QListWidgetItem * const item = ui->list_examples->item(i);
    const QtConceptMapListWidgetItem * const pvdb_item = dynamic_cast<const QtConceptMapListWidgetItem *>(item);
    const cmap::Competency competency = pvdb_item ? pvdb_item->m_competency : cmap::Competency::uninitialized;
    boost::shared_ptr<cmap::Example> p(
      ExampleFactory().Create(
        item->text().toStdString(),
        competency
      )
    );
    v.push_back(p);
  }
  assert(n_items == boost::numeric_cast<int>(v.size()));
  //Set to concept
  const boost::shared_ptr<ribi::cmap::Examples> examples(new cmap::Examples(v));
  assert(examples);
  assert(this);
  assert(m_concept);
  assert(m_concept->GetExamples());
  m_concept->SetName(name);
  m_concept->SetExamples(examples);
  #endif
  close();
}

#ifdef CONCEPTMAP_WRITE_TO_CONCEPT
const boost::shared_ptr<ribi::cmap::Concept> ribi::cmap::QtConceptMapConceptEditDialog::WriteToConcept() const
{
  //Name
  const std::string name = ui->edit_concept->text().toStdString();
  //Examples
  std::vector<boost::shared_ptr<cmap::Example> > v;

  const int n_items = ui->list_examples->count();
  for (int i=0; i!=n_items; ++i)
  {
    const QListWidgetItem * const item = ui->list_examples->item(i);
    const QtConceptMapListWidgetItem * const pvdb_item = dynamic_cast<const QtConceptMapListWidgetItem *>(item);
    const cmap::Competency competency = pvdb_item ? pvdb_item->m_competency : cmap::Competency::uninitialized;
    boost::shared_ptr<cmap::Example> p(
      cmap::ExampleFactory().Create(
        item->text().toStdString(),
        competency
      )
    );
    v.push_back(p);
  }
  assert(n_items == boost::numeric_cast<int>(v.size()));
  //Set to concept
  const boost::shared_ptr<ribi::cmap::Examples> examples(new cmap::Examples(v));
  assert(examples);
  const boost::shared_ptr<Concept> concept
    = ribi::cmap::ConceptFactory().Create(
      name,
      examples,
      m_rating_complexity,
      m_rating_concreteness,
      m_rating_specificity);

  assert(concept);
  return concept;
}
#endif
