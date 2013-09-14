#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtpvdbratedconceptwidget.h"

#include <cassert>

#include <boost/lexical_cast.hpp>

#include "pvdbconcept.h"
#include "pvdbconceptmap.h"
#include "pvdbedge.h"
#include "pvdbexample.h"
#include "pvdbexamples.h"
#include "pvdbnode.h"
#include "ui_qtpvdbratedconceptwidget.h"
#pragma GCC diagnostic pop

ribi::pvdb::QtPvdbRatedConceptWidget::QtPvdbRatedConceptWidget(
  const boost::shared_ptr<const ribi::pvdb::ConceptMap> concept_map,
  const boost::shared_ptr<const pvdb::Node> node,
  QWidget *parent)
  : QDialog(parent),
    ui(new Ui::QtPvdbRatedConceptWidget)
{
  ui->setupUi(this);
  assert(node);

  const int font_in_list_height = 16;
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

  //Examples
  for (const boost::shared_ptr<const pvdb::Example> example: node->GetConcept()->GetExamples()->Get())
  {
    ui->list_concept_examples->addItem(
      new QListWidgetItem(
        (boost::lexical_cast<std::string>(static_cast<int>(example->GetCompetency())) + ". " + example->GetText()).c_str()
      )
    );
  }
  ui->list_concept_examples->setMinimumHeight(ui->list_concept_examples->count() * font_in_list_height);
  ui->list_concept_examples->setMaximumHeight(ui->list_concept_examples->count() * font_in_list_height);

  for (const boost::shared_ptr<const pvdb::Edge> edge: concept_map->GetEdges())
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
          + node->GetConcept()->GetName();
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
          + node->GetConcept()->GetName();
        ui->list_cluster_relations->addItem(new QListWidgetItem(text.c_str()));
      }
      //Indendent on arrow: all examples
      for (const boost::shared_ptr<const pvdb::Example> example: edge->GetConcept()->GetExamples()->Get())
      {
        ui->list_cluster_relations->addItem(
          new QListWidgetItem(
            (std::string("  ") + example->GetText()).c_str()
          )
        );
      }
      ui->list_cluster_relations->setMinimumHeight(ui->list_cluster_relations->count() * font_in_list_height);
      ui->list_cluster_relations->setMaximumHeight(ui->list_cluster_relations->count() * font_in_list_height);
    }
  }
}

ribi::pvdb::QtPvdbRatedConceptWidget::~QtPvdbRatedConceptWidget()
{
  delete ui;
}

void ribi::pvdb::QtPvdbRatedConceptWidget::HideRating()
{
  ui->label_complexity->hide();
  ui->label_concreteness->hide();
  ui->label_specificity->hide();
}
