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
#include "qtpvdbrateconceptmapdialog.h"

#include <cassert>

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QDesktopWidget>
#include <QFileDialog>
#include <QKeyEvent>

#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "pvdbfilefactory.h"
#include "qtpvdbfiledialog.h"
#include "qtscopeddisable.h"
#include "pvdbfile.h"
#include "qtconceptmap.h"
#include "testtimer.h"
#include "trace.h"
#include "qtpvdbratingdialog.h"

#include "qtconceptmaprateconceptdialognewname.h"
#include "ui_qtpvdbrateconceptmapdialog.h"
#pragma GCC diagnostic pop

ribi::pvdb::QtPvdbRateConceptMapDialog::QtPvdbRateConceptMapDialog(
  boost::shared_ptr<pvdb::File> file,
  QWidget* parent)
  : QtHideAndShowDialog(parent),
  ui(new Ui::QtPvdbRateConceptMapDialog),
  m_file(file),
  m_concept_map(new cmap::QtConceptMap)
{
  ui->setupUi(this);
  m_concept_map->SetConceptMap(file->GetConceptMap());
  #ifndef NDEBUG
  Test();
  assert(file);
  #endif
  //boost::shared_ptr<ribi::cmap::ConceptMap> concept_map = m_file->GetConceptMap();
  //assert(concept_map);

  {
    assert(!ui->widget->layout());
    QLayout * const layout = new QGridLayout;
    ui->widget->setLayout(layout);
    layout->addWidget(m_concept_map);
  }

  {
    const std::string s = "Naam student: " + m_file->GetStudentName();
    ui->label_name->setText(s.c_str());
  }

  //Center the dialog
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(screen.adjusted(64,64,-64,-64));
    this->move( screen.center() - this->rect().center() );
  }


  m_concept_map->m_signal_request_rate_concept.connect(
    boost::bind(&ribi::pvdb::QtPvdbRateConceptMapDialog::OnRequestRateConceptDialog,this,boost::lambda::_1));

}

ribi::pvdb::QtPvdbRateConceptMapDialog::~QtPvdbRateConceptMapDialog() noexcept
{
  delete ui;
}

ribi::cmap::QtConceptMap * ribi::pvdb::QtPvdbRateConceptMapDialog::GetWidget()
{
  assert(m_concept_map);
  return m_concept_map;
}

void ribi::pvdb::QtPvdbRateConceptMapDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape) { close(); return; }
  if ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_S) { Save(); return; }
  if ( (e->modifiers() & Qt::ControlModifier)
    && (e->modifiers() & Qt::ShiftModifier)
    && e->key() == Qt::Key_T)
  {
    //Translate
    this->setWindowTitle("Evaluate concept map");
    ui->button_next->setText("Generate parameters");
    ui->button_save->setText("Save assessment");
    ui->label_keys->setText("F1: assess concept, F2: classify examples");
    ui->label_name->setText("Name");
    ui->label_todo->setText("Click on a concept to assess it");
    return;
  }

  QDialog::keyPressEvent(e);
}

void ribi::pvdb::QtPvdbRateConceptMapDialog::on_button_next_clicked()
{
  assert(m_concept_map->GetConceptMap() == m_file->GetConceptMap());
  QtPvdbRatingDialog d(m_file);
  ShowChild(&d);
  if (d.GetBackToMenu())
  {
    close();
  }
}

void ribi::pvdb::QtPvdbRateConceptMapDialog::OnRequestRateConceptDialog(const boost::shared_ptr<ribi::cmap::ConceptMap> sub_concept_map)
{
  assert(sub_concept_map);
  #ifdef HIDE_PARENT_IDEA_5675869837643987593795
  this->setEnabled(false);
  this->hide();
  this->m_widget->setEnabled(false);
  QtPvdbRateConceptDialog d(sub_concept_map); //Item may be changed
  this->ShowChild(&d);
  this->setEnabled(true);
  this->show();
  this->m_widget->setEnabled(true);
  #else
  cmap::QtRateConceptDialogNewName d(sub_concept_map); //Item may be changed
  d.exec();
  #endif
}

#ifndef NDEBUG
void ribi::pvdb::QtPvdbRateConceptMapDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  {
    pvdb::FileFactory::GetTests();
  }
  const TestTimer test_timer{__func__,__FILE__,0.1};
  const int test_depth = 1;

  if (test_depth > 1)
  {
    const std::vector<boost::shared_ptr<pvdb::File> > v = pvdb::FileFactory::GetTests();
    const int sz = boost::numeric_cast<int>(v.size());
    for (int i=0; i!=sz; ++i)
    {
      const boost::shared_ptr<pvdb::File> file = v[i];
      assert(file);
      assert( (file->GetConceptMap() || !file->GetConceptMap() )
        && "A file may or may not have an initialized concept map");
      if (!file->GetConceptMap())
      {
        //Cannot rate a null concept map
        continue;
      }
      QtPvdbRateConceptMapDialog d(file);
      assert(d.GetWidget());
      assert(( file->GetConceptMap() &&  d.GetWidget()->GetConceptMap())
          || (!file->GetConceptMap() && !d.GetWidget()->GetConceptMap()));
      assert(
           !file->GetConceptMap()
        || ribi::cmap::ConceptMap::HasSameContent(
             *file->GetConceptMap(),
             *d.GetWidget()->GetConceptMap()
           )
        );
    }
  }

}
#endif

void ribi::pvdb::QtPvdbRateConceptMapDialog::Save()
{
  this->hide(); //Obligatory, otherwise program will freeze

  const auto d = pvdb::QtFileDialog::GetSaveFileDialog(pvdb::QtFileDialog::FileType::cmp);
  d->setWindowTitle("Sla het assessment invoer-bestand op");
  const int status = d->exec();
  if (status == QDialog::Rejected || d->selectedFiles().empty())
  {
    this->show();
    return;
  }
  assert(d->selectedFiles().size() == 1);
  const std::string filename_raw = d->selectedFiles()[0].toStdString();
  assert(!filename_raw.empty());

  const std::string filename
    =  (filename_raw.size() < pvdb::File::GetFilenameExtension().size()
      || filename_raw.substr( filename_raw.size() - 3, 3 ) != pvdb::File::GetFilenameExtension()
     ? filename_raw + "." + pvdb::File::GetFilenameExtension()
     : filename_raw);
  assert(filename.size() > 3
    && filename.substr( filename.size() - 3, 3 ) == pvdb::File::GetFilenameExtension()
    && "File must have correct file extension name");
  Save(filename);
  //close(); //Do not close after saving
  this->show();
}


void ribi::pvdb::QtPvdbRateConceptMapDialog::Save(const std::string& filename)
{
  assert(filename.size() > 3
    && filename.substr( filename.size() - 3, 3 ) == pvdb::File::GetFilenameExtension()
    && "File must have correct file extension name");
  assert(m_concept_map->GetConceptMap() == m_file->GetConceptMap());
  //const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map = GetWidget()->GetConceptMap();
  //assert(concept_map);
  //m_file->SetConceptMap(concept_map);
  //assert(IsEqual(*m_file->GetConceptMap(),*GetWidget()->GetConceptMap()));
  m_file->Save(filename);
}

void ribi::pvdb::QtPvdbRateConceptMapDialog::on_button_save_clicked()
{
  Save();
}
