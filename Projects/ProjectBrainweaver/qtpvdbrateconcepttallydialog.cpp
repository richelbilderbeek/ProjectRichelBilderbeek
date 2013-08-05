#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbrateconcepttallydialog.h"

#include <cassert>
#include <numeric>

#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <QKeyEvent>
#include "pvdbconceptfactory.h"
#include "pvdbcenternode.h"
#include "pvdbconceptmap.h"
#include "pvdbconceptmapfactory.h"
#include "pvdbconcept.h"
#include "pvdbedge.h"
#include "pvdbedgefactory.h"
#include "pvdbnode.h"
#include "pvdbnodefactory.h"
#include "pvdbexample.h"
#include "pvdbedge.h"
#include "pvdbexamples.h"
#include "pvdbrating.h"
#include "trace.h"
#include "ui_qtpvdbrateconcepttallydialog.h"

QtPvdbRateConceptTallyDialog::QtPvdbRateConceptTallyDialog(
  const boost::shared_ptr</* const */ pvdb::ConceptMap> sub_concept_map,
  QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbRateConceptTallyDialog),
    m_data(CreateData(sub_concept_map))
{
  #ifndef NDEBUG
  Test();  
  #endif
  ui->setupUi(this);

  const int n_rows = static_cast<int>(m_data.size());
  const int n_cols = 4;
  ui->table->setRowCount(n_rows);
  for (int row_index=0; row_index!=n_rows; ++row_index)
  {
    const Row& row = m_data[row_index];
    const boost::shared_ptr<pvdb::Concept> concept = row.first;
    const int example_index = row.second;

    assert(concept);
    if (example_index == -1)
    {
      //Display concept text
      //Put X checkbox in the relation's name
      //Keep C and S columns empty
      {
        //Put X checkbox in the relation's name in column[0]
        const int column = 0;
        QTableWidgetItem * const i = new QTableWidgetItem;
        i->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        i->setCheckState(concept->GetIsComplex() ? Qt::Checked : Qt::Unchecked);
        ui->table->setItem(row_index, column, i);
      }
      {
        //Put uneditable nothing column[1]
        const int column = 1;
        QTableWidgetItem * const i = new QTableWidgetItem;
        i->setFlags(Qt::ItemIsEnabled);
        ui->table->setItem(row_index, column, i);
      }
      {
        //Put uneditable nothing column[2]
        const int column = 2;
        QTableWidgetItem * const i = new QTableWidgetItem;
        i->setFlags(Qt::ItemIsEnabled);
        ui->table->setItem(row_index, column, i);
      }
      {
        //Put the relation's name in place
        QTableWidgetItem * const i = new QTableWidgetItem;
        i->setFlags(
            Qt::ItemIsSelectable
          | Qt::ItemIsEnabled);
        const std::string s = concept->GetName();
        i->setText(s.c_str());
        const int column = 3;
        ui->table->setItem(row_index, column, i);
      }
    }
    else
    {
      assert(concept->GetExamples());
      assert(example_index < static_cast<int>(concept->GetExamples()->Get().size()));
      const boost::shared_ptr<pvdb::Example> example = concept->GetExamples()->Get()[example_index];
      //Display index'th example
      for (int col_index=0; col_index!=n_cols; ++col_index)
      {
        if (col_index != 3)
        {
          QTableWidgetItem * const item = new QTableWidgetItem;
          item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
          switch (col_index)
          {
            case 0: item->setCheckState(example->GetIsComplex() ? Qt::Checked : Qt::Unchecked); break;
            case 1: item->setCheckState(example->GetIsConcrete() ? Qt::Checked : Qt::Unchecked); break;
            case 2: item->setCheckState(example->GetIsSpecific() ? Qt::Checked : Qt::Unchecked); break;
            default: assert(!"Should not get here");
          }
          ui->table->setItem(row_index, col_index, item);
        }
        else
        {
          //Text
          QTableWidgetItem * const item = new QTableWidgetItem;
          item->setFlags(
              Qt::ItemIsSelectable
            | Qt::ItemIsEnabled);
          const std::string s = example->GetText();
          item->setText(s.c_str());
          ui->table->setItem(row_index, col_index, item);
        }
      }
    }

  }

  //Set text on top
  if (sub_concept_map)
  {
    assert(!sub_concept_map->GetNodes().empty());
    const boost::shared_ptr<const pvdb::Concept> focal_concept = sub_concept_map->GetNodes().at(0)->GetConcept();
    assert(focal_concept);
    ui->label_concept_name->setText(
      (std::string("Voorbeelden/toelichting bij concept: ") + focal_concept->GetName()).c_str() );
  }
  else
  {
    ui->label_concept_name->setText("Voorbeelden/toelichting bij concept: (geen concept)");
  }

  ui->table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  #ifndef NDEBUG
  ui->label_debug->setVisible(true);
  #else
  ui->label_debug->setVisible(false);
  #endif

  QObject::connect(ui->table,SIGNAL(cellChanged(int,int)),this,SLOT(OnCellChanged(int,int)));
}

QtPvdbRateConceptTallyDialog::~QtPvdbRateConceptTallyDialog()
{
  delete ui;
}

const std::vector<QtPvdbRateConceptTallyDialog::Row>
  QtPvdbRateConceptTallyDialog::CreateData(const boost::shared_ptr</* const */ pvdb::ConceptMap> map)
{
  std::vector<Row> data;

  if (!map) return data;

  assert(map);
  assert(!map->GetNodes().empty());


  //Add the focal concept its examples (not its name: this cannot be judged)
  {
    const boost::shared_ptr<pvdb::Concept> focal_concept = map->GetNodes().at(0)->GetConcept();
    assert(focal_concept);
    const int n_examples = boost::numeric_cast<int>(focal_concept->GetExamples()->Get().size());
    for (int i=0; i!=n_examples; ++i)
    {
      data.push_back(std::make_pair(focal_concept,i));
    }
  }

  //Collect all relations of the focal node of this sub concept map
  for(const boost::shared_ptr<pvdb::Edge> edge: map->GetEdges())
  {
    //But skip the connections to the focal question
    if (boost::dynamic_pointer_cast<pvdb::CenterNode>(edge->GetTo())
      || boost::dynamic_pointer_cast<pvdb::CenterNode>(edge->GetFrom()))
    {
      continue;
    }


    const boost::shared_ptr<pvdb::Concept> concept = edge->GetConcept();
    data.push_back(std::make_pair(concept,-1));
    const int n_examples = boost::numeric_cast<int>(concept->GetExamples()->Get().size());
    for (int i=0; i!=n_examples; ++i)
    {
      data.push_back(std::make_pair(concept,i));
    }
  }
  return data;
}

const boost::shared_ptr<pvdb::ConceptMap> QtPvdbRateConceptTallyDialog::CreateTestConceptMap()
{
  //Create a concept map for testing:
  // - node with a concept with (1) text 'TextNode' (2) one example with text 'TextExampleNode'
  // - edge with a concept with (1) text 'TextEdge' (2) one example with text 'TextExampleEdge'
  // - node with a concept with (1) text 'TextDontCare'

  const boost::shared_ptr<pvdb::Concept> concept_node_focal(pvdb::ConceptFactory::Create("TextNode",
    {
      {"TextExampleNpde",pvdb::Competency::misc}
    },
    0,1,2));
  const boost::shared_ptr<pvdb::Concept> concept_node_other(pvdb::ConceptFactory::Create("TextDontCare",
    {
      { }
    },
    0,1,2));

  const boost::shared_ptr<pvdb::Concept> concept_edge(pvdb::ConceptFactory::Create("TextEdge",
    {
      {"TextExampleEdge",pvdb::Competency::misc}
    },
    2,1,0));
  const boost::shared_ptr<pvdb::Node> node_focal(pvdb::NodeFactory::Create(concept_node_focal));
  const boost::shared_ptr<pvdb::Node> node_other(pvdb::NodeFactory::Create(concept_node_other));

  const boost::shared_ptr<pvdb::ConceptMap> concept_map(
    pvdb::ConceptMapFactory::Create(
      {
        node_focal,
        node_other
      } ,
      {
        pvdb::EdgeFactory::Create(concept_edge,1.2,3.4,node_focal,true,node_other,true)
      }
    )
  );
  assert(concept_map);
  return concept_map;
}

int QtPvdbRateConceptTallyDialog::GetSuggestedComplexity() const
{
  //Tally the edges that contribute to complexity
  const int n_edges = std::accumulate(m_data.begin(),m_data.end(),0,
    [](int init, const Row& row)
      {
        return init + (row.second == -1 && row.first->GetIsComplex() ? 1 : 0);
      }
    );

  //Tally the examples that contribute to complexity
  const int n_examples = std::accumulate(m_data.begin(),m_data.end(),0,
    [](int init, const Row& row)
      {
        const int index = row.second;
        if (index == -1) return init + 0;
        assert(row.first);
        assert(row.first->GetExamples());
        assert(index < static_cast<int>(row.first->GetExamples()->Get().size()));
        return init + (row.first->GetExamples()->Get()[index]->GetIsComplex() ? 1 : 0);
      }
    );
  const int n_tallied = n_examples + n_edges;
  if (n_tallied < 2) return 0;
  if (n_tallied < 4) return 1;
  return 2;
}

int QtPvdbRateConceptTallyDialog::GetSuggestedConcreteness() const
{
  //Tally the examples that contribute to concreteness
  const int n_examples = std::accumulate(m_data.begin(),m_data.end(),0,
    [](int init, const Row& row)
      {
        const int index = row.second;
        if (index == -1) return init + 0;
        assert(row.first);
        assert(row.first->GetExamples());
        assert(index < static_cast<int>(row.first->GetExamples()->Get().size()));
        return init + (row.first->GetExamples()->Get()[index]->GetIsConcrete() ? 1 : 0);
      }
    );
  const int n_tallied = n_examples;
  if (n_tallied < 2) return 0;
  if (n_tallied < 4) return 1;
  return 2;
}

int QtPvdbRateConceptTallyDialog::GetSuggestedSpecificity() const
{
  //Tally the examples that contribute to specificity
  const int n_examples = std::accumulate(m_data.begin(),m_data.end(),0,
    [](int init, const Row& row)
      {
        const int index = row.second;
        if (index == -1) return init + 0;
        assert(row.first);
        assert(index < static_cast<int>(row.first->GetExamples()->Get().size()));
        assert(row.first->GetExamples());
        return init + (row.first->GetExamples()->Get()[index]->GetIsSpecific() ? 1 : 0);
      }
    );
  const int n_tallied = n_examples;
  if (n_tallied < 2) return 0;
  if (n_tallied < 4) return 1;
  return 2;
}

void QtPvdbRateConceptTallyDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void QtPvdbRateConceptTallyDialog::OnCellChanged(int row_index, int col)
{
  assert(row_index >= 0);
  assert(row_index < static_cast<int>(m_data.size()));
  assert(col >= 0);
  assert(col < 4);
  const QTableWidgetItem * const item = ui->table->item(row_index,col);
  assert(item);
  const Row& row = m_data[row_index];
  boost::shared_ptr<pvdb::Concept> concept = row.first;
  const int index = row.second;

  if (index == -1)
  {
    //Concept name
    switch (col)
    {
      case 0: concept->SetIsComplex( item->checkState() == Qt::Checked );
      case 1: break; //Empty cell
      case 2: break; //Empty cell
      case 3: break; //It's read-only! //concept->SetName( item->text().toStdString() ); break;
    }
  }
  else
  {
    //Concept example
    assert(index < static_cast<int>(concept->GetExamples()->Get().size()));
    const boost::shared_ptr<pvdb::Example> example = concept->GetExamples()->Get()[index];
    switch (col)
    {
      case 0: example->SetIsComplex( item->checkState() == Qt::Checked ); break;
      case 1: example->SetIsConcrete( item->checkState() == Qt::Checked ); break;
      case 2: example->SetIsSpecific( item->checkState() == Qt::Checked ); break;
      case 3: break; //It's read-only! //example->SetText( item->text().toStdString() ); break;
    }
  }

  #ifndef NDEBUG
  {
    const int x = GetSuggestedComplexity();
    const int c = GetSuggestedConcreteness();
    const int s = GetSuggestedSpecificity();
    std::stringstream m;
    m << "DEBUG ONLY: X: " << x << ", C: " << c << ", S: " << s;
    ui->label_debug->setText(m.str().c_str());

  }
  #endif
}

void QtPvdbRateConceptTallyDialog::resizeEvent(QResizeEvent *)
{
  const int small_col_width = 24;
  ui->table->setColumnWidth(0, small_col_width);
  ui->table->setColumnWidth(1, small_col_width);
  ui->table->setColumnWidth(2, small_col_width);
  const int extra_space = 8;
  ui->table->setColumnWidth(3,ui->table->width() - (3 * small_col_width) - (3 * extra_space));
}

void QtPvdbRateConceptTallyDialog::on_button_ok_clicked()
{
  close();
}

#ifndef NDEBUG
void QtPvdbRateConceptTallyDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Started QtPvdbRateConceptTallyDialog::Test");
  //Empty table
  {
    const boost::shared_ptr<pvdb::ConceptMap> concept_map;
    assert(!concept_map);
    QtPvdbRateConceptTallyDialog d(concept_map);
  }

  const boost::shared_ptr<pvdb::ConceptMap> concept_map = CreateTestConceptMap();
  assert(concept_map);


  QtPvdbRateConceptTallyDialog d(concept_map);
  assert(d.ui->table->columnCount() == 4);
  assert(d.ui->table->rowCount() == 3);
  assert(concept_map->GetNodes().size() == 2);
  assert(concept_map->GetEdges().size() == 1);
  const boost::shared_ptr<pvdb::Node> focal_node = concept_map->GetNodes()[0];
  //const boost::shared_ptr<pvdb::Node> other_node = concept_map->GetNodes()[1]; //Don't care
  const boost::shared_ptr<pvdb::Edge> edge = concept_map->GetEdges()[0];

  assert(d.ui->table->item(0,0)->flags() == (Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable));
  assert(d.ui->table->item(0,1)->flags() == (Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable));
  assert(d.ui->table->item(0,2)->flags() == (Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable));
  assert(d.ui->table->item(0,3)->flags() == (Qt::ItemIsSelectable | Qt::ItemIsEnabled));

  assert(d.ui->table->item(1,0)->flags() == (Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable));
  assert(d.ui->table->item(1,1)->flags() == Qt::ItemIsEnabled); //Empty
  assert(d.ui->table->item(1,2)->flags() == Qt::ItemIsEnabled); //Empty
  assert(d.ui->table->item(1,3)->flags() == (Qt::ItemIsSelectable | Qt::ItemIsEnabled));

  assert(d.ui->table->item(2,0)->flags() == (Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable));
  assert(d.ui->table->item(2,1)->flags() == (Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable));
  assert(d.ui->table->item(2,2)->flags() == (Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable));
  assert(d.ui->table->item(2,3)->flags() == (Qt::ItemIsSelectable | Qt::ItemIsEnabled));

  //Check current state, before modification

  assert(d.ui->table->item(0,0)->checkState() == (focal_node->GetConcept()->GetExamples()->Get()[0]->GetIsComplex() ? Qt::Checked : Qt::Unchecked));
  assert(d.ui->table->item(0,1)->checkState() == (focal_node->GetConcept()->GetExamples()->Get()[0]->GetIsConcrete() ? Qt::Checked : Qt::Unchecked));
  assert(d.ui->table->item(0,2)->checkState() == (focal_node->GetConcept()->GetExamples()->Get()[0]->GetIsSpecific() ? Qt::Checked : Qt::Unchecked));
  assert(d.ui->table->item(0,3)->text() == QString(focal_node->GetConcept()->GetExamples()->Get()[0]->GetText().c_str()));

  assert(d.ui->table->item(1,0)->checkState() == (edge->GetConcept()->GetIsComplex() ? Qt::Checked : Qt::Unchecked));
  assert(d.ui->table->item(1,1)->text() == "");
  assert(d.ui->table->item(1,2)->text() == "");
  assert(d.ui->table->item(1,3)->text() == QString(edge->GetConcept()->GetName().c_str()));

  assert(d.ui->table->item(2,0)->checkState() == (edge->GetConcept()->GetExamples()->Get()[0]->GetIsComplex() ? Qt::Checked : Qt::Unchecked));
  assert(d.ui->table->item(2,1)->checkState() == (edge->GetConcept()->GetExamples()->Get()[0]->GetIsConcrete() ? Qt::Checked : Qt::Unchecked));
  assert(d.ui->table->item(2,2)->checkState() == (edge->GetConcept()->GetExamples()->Get()[0]->GetIsSpecific() ? Qt::Checked : Qt::Unchecked));
  assert(d.ui->table->item(2,3)->text() == QString(edge->GetConcept()->GetExamples()->Get()[0]->GetText().c_str()));

  //Modify table
  d.ui->table->item(0,0)->setCheckState(d.ui->table->item(0,0)->checkState() == Qt::Unchecked ? Qt::Checked : Qt::Unchecked);
  d.ui->table->item(0,1)->setCheckState(d.ui->table->item(0,1)->checkState() == Qt::Unchecked ? Qt::Checked : Qt::Unchecked);
  d.ui->table->item(0,2)->setCheckState(d.ui->table->item(0,2)->checkState() == Qt::Unchecked ? Qt::Checked : Qt::Unchecked);
  //d.ui->table->item(0,3)->setText("MODIFIED"); //User should not be able to modify this

  d.ui->table->item(1,0)->setCheckState(d.ui->table->item(1,0)->checkState() == Qt::Unchecked ? Qt::Checked : Qt::Unchecked);
  //d.ui->table->item(1,3)->setText("MODIFIED TOO"); //User should not be able to modify this

  d.ui->table->item(2,0)->setCheckState(d.ui->table->item(2,0)->checkState() == Qt::Unchecked ? Qt::Checked : Qt::Unchecked);
  d.ui->table->item(2,1)->setCheckState(d.ui->table->item(2,1)->checkState() == Qt::Unchecked ? Qt::Checked : Qt::Unchecked);
  d.ui->table->item(2,2)->setCheckState(d.ui->table->item(2,2)->checkState() == Qt::Unchecked ? Qt::Checked : Qt::Unchecked);
  //d.ui->table->item(2,3)->setText("MODIFIED AS WELL"); //User should not be able to modify this

  //Check that data is modified by GUI

  assert(d.ui->table->item(0,0)->checkState() == (focal_node->GetConcept()->GetExamples()->Get()[0]->GetIsComplex() ? Qt::Checked : Qt::Unchecked));
  assert(d.ui->table->item(0,1)->checkState() == (focal_node->GetConcept()->GetExamples()->Get()[0]->GetIsConcrete() ? Qt::Checked : Qt::Unchecked));
  assert(d.ui->table->item(0,2)->checkState() == (focal_node->GetConcept()->GetExamples()->Get()[0]->GetIsSpecific() ? Qt::Checked : Qt::Unchecked));
  assert(d.ui->table->item(0,3)->text() == QString(focal_node->GetConcept()->GetExamples()->Get()[0]->GetText().c_str()));

  assert(d.ui->table->item(1,0)->checkState() == (edge->GetConcept()->GetIsComplex() ? Qt::Checked : Qt::Unchecked));
  assert(d.ui->table->item(1,1)->text() == "");
  assert(d.ui->table->item(1,2)->text() == "");
  assert(d.ui->table->item(1,3)->text() == QString(edge->GetConcept()->GetName().c_str()));

  assert(d.ui->table->item(2,0)->checkState() == (edge->GetConcept()->GetExamples()->Get()[0]->GetIsComplex() ? Qt::Checked : Qt::Unchecked));
  assert(d.ui->table->item(2,1)->checkState() == (edge->GetConcept()->GetExamples()->Get()[0]->GetIsConcrete() ? Qt::Checked : Qt::Unchecked));
  assert(d.ui->table->item(2,2)->checkState() == (edge->GetConcept()->GetExamples()->Get()[0]->GetIsSpecific() ? Qt::Checked : Qt::Unchecked));
  assert(d.ui->table->item(2,3)->text() == QString(edge->GetConcept()->GetExamples()->Get()[0]->GetText().c_str()));

  TRACE("Finished QtPvdbRateConceptTallyDialog::Test successfully");
}
#endif
