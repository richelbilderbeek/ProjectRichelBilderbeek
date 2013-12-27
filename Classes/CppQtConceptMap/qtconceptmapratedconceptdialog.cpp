#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmapratedconceptdialog.h"

#include <cassert>

#include <boost/lexical_cast.hpp>

#include <QScrollBar>
#include <QTimer>

#include "conceptmapconcept.h"
#include "conceptmap.h"
#include "conceptmapedge.h"
#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "conceptmapnode.h"

#include "ui_qtconceptmapratedconceptdialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtConceptMapRatedConceptDialog::QtConceptMapRatedConceptDialog(
  const boost::shared_ptr<const ribi::cmap::ConceptMap> concept_map,
  const boost::shared_ptr<const cmap::Node> node,
  QWidget *parent)
  : QDialog(parent),
    ui(new Ui::QtConceptMapRatedConceptDialog),
    m_timer(new QTimer)
{
  ui->setupUi(this);
  assert(node);

  //const int font_in_list_height = 16;
  {
    QFont font = ui->list_cluster_relations->font();
    font.setPointSize(8);
    ui->list_concept_examples->setFont(font);
    ui->list_cluster_relations->setFont(font);
  }

  ui->label_name->setText(
    (std::string("Cluster bij concept: ") + node->GetConcept()->GetName()).c_str()
  );
  ui->label_complexity->setText(
    (std::string("Complexiteit: ") + boost::lexical_cast<std::string>(node->GetConcept()->GetRatingComplexity())).c_str()
  );
  ui->label_concreteness->setText(
    (std::string("Concreetheid: ") + boost::lexical_cast<std::string>(node->GetConcept()->GetRatingConcreteness())).c_str()
  );
  ui->label_specificity->setText(
    (std::string("Specificiteit: ") + boost::lexical_cast<std::string>(node->GetConcept()->GetRatingSpecificity())).c_str()
  );

  //Put examples in list
  for (const boost::shared_ptr<const cmap::Example> example: node->GetConcept()->GetExamples()->Get())
  {
    ui->list_concept_examples->addItem(
      new QListWidgetItem(
        (boost::lexical_cast<std::string>(static_cast<int>(example->GetCompetency())) + ". " + example->GetText()).c_str()
      )
    );
  }


  for (const boost::shared_ptr<const cmap::Edge> edge: concept_map->GetEdges())
  {
    if (edge->GetFrom() == node || edge->GetTo() == node)
    {
      //Dependent on arrow
      if (edge->GetFrom() == node)
      {
        const std::string first_arrow
          = ( edge->HasTailArrow() ? "<- " : "-- ");
        const std::string second_arrow
          = ( edge->HasHeadArrow() ? " -> " : " -- ");
        const std::string text
          = first_arrow
          + edge->GetConcept()->GetName()
          + second_arrow
          //+ node->GetConcept()->GetName();
          + edge->GetTo()->GetConcept()->GetName();
        ui->list_cluster_relations->addItem(new QListWidgetItem(text.c_str()));
      }
      else if (edge->GetTo() == node)
      {
        assert(edge->GetTo() == node);
        const std::string first_arrow  = (edge->HasHeadArrow() ? "<- " : "-- ");
        const std::string second_arrow = (edge->HasTailArrow() ? " -> " : " -- ");
        const std::string text
          = first_arrow
          + edge->GetConcept()->GetName()
          + second_arrow
          + edge->GetFrom()->GetConcept()->GetName();
        ui->list_cluster_relations->addItem(new QListWidgetItem(text.c_str()));
      }
      //Indendent on arrow: all examples
      for (const boost::shared_ptr<const cmap::Example> example: edge->GetConcept()->GetExamples()->Get())
      {
        ui->list_cluster_relations->addItem(
          new QListWidgetItem(
            (std::string("  ") + example->GetText()).c_str()
          )
        );
      }
    }
  }

  QObject::connect(
    m_timer,&QTimer::timeout,
    this,&ribi::cmap::QtConceptMapRatedConceptDialog::DoResizeLists);
  m_timer->setInterval(1);
  m_timer->start();
}

ribi::cmap::QtConceptMapRatedConceptDialog::~QtConceptMapRatedConceptDialog()
{
  delete ui;
}

void ribi::cmap::QtConceptMapRatedConceptDialog::HideRating()
{
  ui->label_complexity->hide();
  ui->label_concreteness->hide();
  ui->label_specificity->hide();
}

void ribi::cmap::QtConceptMapRatedConceptDialog::DoResizeLists()
{
  //Set the list displaying the concept its height and widt
  bool done = true;
  for (QListWidget * const w:
    { ui->list_cluster_relations, ui->list_concept_examples } )
  {
    if (w->verticalScrollBar()->isVisible())
    {
      done = false;
      const int h = w->height();
      w->setMaximumHeight(h+1);
      w->setMinimumHeight(h+1);
      assert(w->height() == h + 1);
    }
    //Calculate the height of list_cluster_relations from its sizehint its heights
    //Approach 2
    #ifdef USE_APPROACH_2_20131013
    const int n_items = w->count();
    int height = 0;
    for (int i=0; i!=n_items; ++i)
    {
      height += std::max(w->item(i)->sizeHint().height(),16);
    }
    assert(height >= 0);
    w->setMinimumHeight(height);
    w->setMaximumHeight(height);
    #endif
  }
  if (done) m_timer->stop();
  //Approach 1: set the height manually
  //ui->list_concept_examples->setMinimumHeight(
  //  ui->list_concept_examples->count() * font_in_list_height);
  //ui->list_concept_examples->setMaximumHeight(
  //  ui->list_concept_examples->count() * font_in_list_height);
}
