#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbrateconceptautodialog.h"

#include <cassert>
#include <numeric>

#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <QKeyEvent>
#include "pvdbconceptmap.h"
#include "pvdbconcept.h"
#include "pvdbnode.h"
#include "pvdbexample.h"
#include "pvdbedge.h"
#include "pvdbexamples.h"
#include "ui_qtpvdbrateconceptautodialog.h"

QtPvdbRateConceptAutoDialog::QtPvdbRateConceptAutoDialog(
  const boost::shared_ptr</* const */ pvdb::ConceptMap> sub_concept_map,
  QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbRateConceptAutoDialog),
    m_map(sub_concept_map)
{
  ui->setupUi(this);
  ui->table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  assert(sub_concept_map);
  assert(!sub_concept_map->GetNodes().empty());
  const boost::shared_ptr<const pvdb::Concept> focal_concept = sub_concept_map->GetNodes().at(0)->GetConcept();
  assert(focal_concept);
  ui->label_concept_name->setText(
    (std::string("Voorbeelden/toelichting bij concept: ") + focal_concept->GetName()).c_str() );
  //Collect all examples of the focal node of this sub concept map
  //Put X,C,S checkboxes in front
  const int n_examples = boost::numeric_cast<int>(focal_concept->GetExamples()->Get().size());
  const int n_edges = boost::numeric_cast<int>(m_map->GetEdges().size());
  const int n_edge_examples
    = std::accumulate(
      m_map->GetEdges().begin(),
      m_map->GetEdges().end(),
      static_cast<int>(0),
        [](int init, const boost::shared_ptr<const pvdb::Edge>& edge)
        {
          assert(edge);
          return init + boost::numeric_cast<int>(edge->GetConcept()->GetExamples()->Get().size());
        }
    );
  ui->table->setRowCount(n_examples + n_edges + n_edge_examples);
  int current_row = 0;
  for (const boost::shared_ptr<const pvdb::Example> example: focal_concept->GetExamples()->Get())
  {
    //const boost::shared_ptr<const pvdb::Example> example = focal_concept->GetExamples()->Get().at(i);
    assert(example);
    //const int row = i;
    const int n_cols = 4;
    assert(n_cols == 4);
    for (int col=0; col!=n_cols; ++col)
    {
      QTableWidgetItem * const i = new QTableWidgetItem;
      if (col != 3)
      {
        i->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        switch (col)
        {
          case 0: i->setCheckState(example->GetIsComplex() ? Qt::Checked : Qt::Unchecked); break;
          case 1: i->setCheckState(example->GetIsConcrete() ? Qt::Checked : Qt::Unchecked); break;
          case 2: i->setCheckState(example->GetIsSpecific() ? Qt::Checked : Qt::Unchecked); break;
          default: assert(!"Should not get here");
        }
      }
      else
      {
        //Text
        i->setFlags(
            Qt::ItemIsSelectable
          | Qt::ItemIsEnabled);
        const std::string s = example->GetText();
        i->setText(s.c_str());
      }
      ui->table->setItem(current_row, col, i);
    }
    ++current_row;
  }

  //Collect all relations of the focal node of this sub concept map
  for(const boost::shared_ptr<pvdb::Edge> edge:sub_concept_map->GetEdges())
  {
    //Put X checkbox in the relation's name
    //Keep C and S columns empty
    {
      //Put X checkbox in the relation's name
      QTableWidgetItem * const i = new QTableWidgetItem;
      i->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
      i->setCheckState(edge->GetConcept()->GetIsComplex() ? Qt::Checked : Qt::Unchecked);
      const int column = 0;
      ui->table->setItem(current_row, column, i);
    }
    {
      //Put the relation's name in place
      QTableWidgetItem * const i = new QTableWidgetItem;
      i->setFlags(
          Qt::ItemIsSelectable
        | Qt::ItemIsEnabled);
      const std::string s = edge->GetConcept()->GetName();
      i->setText(s.c_str());
      const int column = 3;
      ui->table->setItem(current_row, column, i);
    }

    ++current_row;

    //Of every relation, collect all examples
    //Put X,C,S checkboxes in front

    for (const boost::shared_ptr<const pvdb::Example> example: edge->GetConcept()->GetExamples()->Get())
    {
      //const boost::shared_ptr<const pvdb::Example> example = focal_concept->GetExamples()->Get().at(i);
      assert(example);
      //const int row = i;
      const int n_cols = 4;
      assert(n_cols == 4);
      for (int col=0; col!=n_cols; ++col)
      {
        QTableWidgetItem * const i = new QTableWidgetItem;
        if (col != 3)
        {
          i->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
          switch (col)
          {
            case 0: i->setCheckState(example->GetIsComplex() ? Qt::Checked : Qt::Unchecked); break;
            case 1: i->setCheckState(example->GetIsConcrete() ? Qt::Checked : Qt::Unchecked); break;
            case 2: i->setCheckState(example->GetIsSpecific() ? Qt::Checked : Qt::Unchecked); break;
            default: assert(!"Should not get here");
          }
        }
        else
        {
          //Text
          i->setFlags(
              Qt::ItemIsSelectable
            | Qt::ItemIsEnabled);
          const std::string s = example->GetText();
          i->setText(s.c_str());
        }
        ui->table->setItem(current_row, col, i);
      }
      ++current_row;
    }

  }
}

QtPvdbRateConceptAutoDialog::~QtPvdbRateConceptAutoDialog()
{
  delete ui;
}

void QtPvdbRateConceptAutoDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void QtPvdbRateConceptAutoDialog::resizeEvent(QResizeEvent *)
{
  const int small_col_width = 24;
  ui->table->setColumnWidth(0, small_col_width);
  ui->table->setColumnWidth(1, small_col_width);
  ui->table->setColumnWidth(2, small_col_width);
  const int extra_space = 8;
  ui->table->setColumnWidth(3,ui->table->width() - (3 * small_col_width) - (3 * extra_space));
}

void QtPvdbRateConceptAutoDialog::on_button_ok_clicked()
{
  close();
}
