#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtconceptmaprateexamplesdialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>
#include <QListWidgetItem>

#include "conceptmapexamplefactory.h"
#include "conceptmapexamplesfactory.h"
#include "conceptmapconcept.h"
#include "conceptmaphelper.h"
#include "qtconceptmapcompetency.h"
#include "ui_qtconceptmaprateexamplesdialog.h"
#include "conceptmapconceptfactory.h"
#include "trace.h"
#pragma GCC diagnostic pop

struct QtConceptMapListWidgetItem : public QListWidgetItem
{
  QtConceptMapListWidgetItem(const boost::shared_ptr<const ribi::cmap::Example>& example)
  {
    //Wordwrap text
    const std::string s = example->GetText();
    const std::vector<std::string> v { ribi::cmap::Wordwrap(s,40) };
    //Display multi-line
    std::string t;
    for (const std::string& i: v) { t += i + "\n"; }
    if (!t.empty()) t.resize(t.size() - 1);
    this->setText(t.c_str());
    //Icon
    this->setIcon(ribi::cmap::QtCompetency::CompetencyToIcon(example->GetCompetency()));
  }
};


ribi::cmap::QtRateExamplesDialog::QtRateExamplesDialog(
  const boost::shared_ptr<ribi::cmap::Concept> concept,
  QWidget* parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtRateExamplesDialog),
    m_concept(concept)
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  assert(m_concept);
  assert(m_concept->GetExamples());
  #endif

  //Ensure that the dialog does not resize beyond the screen's size
  {
    this->setMaximumWidth( QApplication::desktop()->width() );
  }

  //Convert the Concept to GUI elements
  {
    ui->label_concept_name->setText(concept->GetName().c_str());
    ui->list->clear();
    const auto v = concept->GetExamples()->Get();
    const std::size_t sz = v.size();
    for (std::size_t i=0; i!=sz; ++i)
    {
      const boost::shared_ptr<const cmap::Example>& example = v[i];
      const std::string s = example->GetText();
      //const int n_lines = ribi::cmap::Wordwrap(s,40).size();
      //ui->list->setRowHeight(row,ui->list->fontMetrics().height() * 2 * (n_lines + 1));
      QtConceptMapListWidgetItem * const item
        = new QtConceptMapListWidgetItem(example);
      ui->list->addItem(item);
    }
  }
  //Align the button icons and texts to the left
  {
    const std::vector<QPushButton*> v
      =
      {
        ui->button_misc,
        ui->button_organisations,
        ui->button_prof,
        ui->button_prof_development,
        ui->button_social,
        ui->button_target_audience,
        ui->button_ti_knowledge
      };
    for(QPushButton* button: v) button->setStyleSheet("text-align: left;");
  }

  //Put the dialog in the screen its center
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->move( screen.center() - this->rect().center() );
  }

}

ribi::cmap::QtRateExamplesDialog::~QtRateExamplesDialog() noexcept
{
  delete ui;
}

const boost::shared_ptr<ribi::cmap::Examples> ribi::cmap::QtRateExamplesDialog::GetRatedExamples() const
{
  std::vector<boost::shared_ptr<cmap::Example> > v;

  const int sz = ui->list->count();
  for (int i=0; i!=sz; ++i)
  {
    const QListWidgetItem* const qtitem = ui->list->item(i);
    assert(qtitem);
    const QtConceptMapListWidgetItem* const item = dynamic_cast<const QtConceptMapListWidgetItem*>(qtitem);
    assert(item);
    const boost::shared_ptr<cmap::Example> example
      = cmap::ExampleFactory::Create(
        item->text().toStdString(),
        cmap::QtCompetency::IconToCompetency(item->icon())
      );
    assert(example);
    v.push_back(example);
  }

  const boost::shared_ptr<ribi::cmap::Examples> examples
    = cmap::ExamplesFactory::Create(v);
  assert(examples);
  return examples;
}

void ribi::cmap::QtRateExamplesDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape) { close(); return; }
  QDialog::keyPressEvent(e);
}

void ribi::cmap::QtRateExamplesDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("ribi::cmap::QtRateExamplesDialog::Test started");
  ///Test conversion between reading and writing a concept
  {
    const int sz = ribi::cmap::ConceptFactory::GetTests().size();
    for (int i=0; i!=sz; ++i)
    {
      const auto a = QtRateExamplesDialog(cmap::ConceptFactory::GetTests()[i]).GetRatedExamples();
      assert(a);
      for (int j=0; j!=sz; ++j)
      {
        const auto b = QtRateExamplesDialog(cmap::ConceptFactory::GetTests()[j]).GetRatedExamples();
        assert(b);
        assert(a != b);
        if (i == j)
        {
          assert(IsEqual(*a,*b));
        }
        else
        {
          assert(!IsEqual(*a,*b));
        }
      }
    }
  }
  TRACE("ribi::cmap::QtRateExamplesDialog::Test finished successfully");
}

void ribi::cmap::QtRateExamplesDialog::on_button_prof_clicked()
{
  if (ui->list->currentItem())
  {
    QtConceptMapListWidgetItem* const item = dynamic_cast<QtConceptMapListWidgetItem*>(ui->list->currentItem());
    item->setIcon(cmap::QtCompetency::CompetencyToIcon(cmap::Competency::profession));
  }
}

void ribi::cmap::QtRateExamplesDialog::on_button_organisations_clicked()
{
  if (ui->list->currentItem())
  {
    QtConceptMapListWidgetItem* const item = dynamic_cast<QtConceptMapListWidgetItem*>(ui->list->currentItem());
    item->setIcon(cmap::QtCompetency::CompetencyToIcon(cmap::Competency::organisations));
  }
}

void ribi::cmap::QtRateExamplesDialog::on_button_social_clicked()
{
  if (ui->list->currentItem())
  {
    QtConceptMapListWidgetItem* const item = dynamic_cast<QtConceptMapListWidgetItem*>(ui->list->currentItem());
    item->setIcon(cmap::QtCompetency::CompetencyToIcon(cmap::Competency::social_surroundings));
  }
}

void ribi::cmap::QtRateExamplesDialog::on_button_target_audience_clicked()
{
  if (ui->list->currentItem())
  {
    QtConceptMapListWidgetItem* const item = dynamic_cast<QtConceptMapListWidgetItem*>(ui->list->currentItem());
    item->setIcon(cmap::QtCompetency::CompetencyToIcon(cmap::Competency::target_audience));
  }
}

void ribi::cmap::QtRateExamplesDialog::on_button_prof_development_clicked()
{
  if (ui->list->currentItem())
  {
    QtConceptMapListWidgetItem* const item = dynamic_cast<QtConceptMapListWidgetItem*>(ui->list->currentItem());
    item->setIcon(cmap::QtCompetency::CompetencyToIcon(cmap::Competency::prof_growth));
  }
}

void ribi::cmap::QtRateExamplesDialog::on_button_misc_clicked()
{
  if (ui->list->currentItem())
  {
    QtConceptMapListWidgetItem* const item = dynamic_cast<QtConceptMapListWidgetItem*>(ui->list->currentItem());
    item->setIcon(cmap::QtCompetency::CompetencyToIcon(cmap::Competency::misc));
  }
}

void ribi::cmap::QtRateExamplesDialog::on_button_ti_knowledge_clicked()
{
  if (ui->list->currentItem())
  {
    QtConceptMapListWidgetItem* const item = dynamic_cast<QtConceptMapListWidgetItem*>(ui->list->currentItem());
    item->setIcon(cmap::QtCompetency::CompetencyToIcon(cmap::Competency::ti_knowledge));
  }
}

void ribi::cmap::QtRateExamplesDialog::on_button_ok_clicked()
{
  const boost::shared_ptr<ribi::cmap::Examples> p = GetRatedExamples();
  assert(p);
  assert(m_concept);
  m_concept->SetExamples(p);
  close();
}
