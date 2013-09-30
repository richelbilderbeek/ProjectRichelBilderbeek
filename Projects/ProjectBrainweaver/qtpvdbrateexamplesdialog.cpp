#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtpvdbrateexamplesdialog.h"

#include <QKeyEvent>
#include <QListWidgetItem>

#include <pvdbexamplefactory.h>
#include <pvdbexamplesfactory.h>
#include "pvdbconcept.h"
#include "pvdbhelper.h"
#include "qtpvdbcompetency.h"
#include "ui_qtpvdbrateexamplesdialog.h"
#include "pvdbconceptfactory.h"
#include "trace.h"
#pragma GCC diagnostic pop

struct QtPvdbListWidgetItem : public QListWidgetItem
{
  QtPvdbListWidgetItem(const boost::shared_ptr<const ribi::pvdb::Example>& example)
  {
    //Wordwrap text
    const std::string s = example->GetText();
    const std::vector<std::string> v { ribi::pvdb::Wordwrap(s,40) };
    //Display multi-line
    std::string t;
    for (const std::string& i: v) { t += i + "\n"; }
    if (!t.empty()) t.resize(t.size() - 1);
    this->setText(t.c_str());
    //Icon
    this->setIcon(ribi::pvdb::QtCompetency::CompetencyToIcon(example->GetCompetency()));
  }
};


ribi::pvdb::QtPvdbRateExamplesDialog::QtPvdbRateExamplesDialog(
  const boost::shared_ptr<ribi::pvdb::Concept> concept,
  QWidget* parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbRateExamplesDialog),
    m_concept(concept)
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  assert(m_concept);
  assert(m_concept->GetExamples());
  #endif

  //Convert the Concept to GUI elements
  {
    ui->label_concept_name->setText(concept->GetName().c_str());
    ui->list->clear();
    const auto v = concept->GetExamples()->Get();
    const std::size_t sz = v.size();
    for (std::size_t i=0; i!=sz; ++i)
    {
      const boost::shared_ptr<const pvdb::Example>& example = v[i];
      const std::string s = example->GetText();
      //const int n_lines = ribi::pvdb::Wordwrap(s,40).size();
      //ui->list->setRowHeight(row,ui->list->fontMetrics().height() * 2 * (n_lines + 1));
      QtPvdbListWidgetItem * const item
        = new QtPvdbListWidgetItem(example);
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
}

ribi::pvdb::QtPvdbRateExamplesDialog::~QtPvdbRateExamplesDialog() noexcept
{
  delete ui;
}

const boost::shared_ptr<ribi::pvdb::Examples> ribi::pvdb::QtPvdbRateExamplesDialog::GetRatedExamples() const
{
  std::vector<boost::shared_ptr<pvdb::Example> > v;

  const int sz = ui->list->count();
  for (int i=0; i!=sz; ++i)
  {
    const QListWidgetItem* const qtitem = ui->list->item(i);
    assert(qtitem);
    const QtPvdbListWidgetItem* const item = dynamic_cast<const QtPvdbListWidgetItem*>(qtitem);
    assert(item);
    const boost::shared_ptr<pvdb::Example> example
      = pvdb::ExampleFactory::Create(
        item->text().toStdString(),
        pvdb::QtCompetency::IconToCompetency(item->icon())
      );
    assert(example);
    v.push_back(example);
  }

  const boost::shared_ptr<ribi::pvdb::Examples> examples
    = pvdb::ExamplesFactory::Create(v);
  assert(examples);
  return examples;
}

void ribi::pvdb::QtPvdbRateExamplesDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape) { close(); return; }
  QDialog::keyPressEvent(e);
}

void ribi::pvdb::QtPvdbRateExamplesDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("ribi::pvdb::QtPvdbRateExamplesDialog::Test started");
  ///Test conversion between reading and writing a concept
  {
    const int sz = ribi::pvdb::ConceptFactory::GetTests().size();
    for (int i=0; i!=sz; ++i)
    {
      const auto a = QtPvdbRateExamplesDialog(pvdb::ConceptFactory::GetTests()[i]).GetRatedExamples();
      assert(a);
      for (int j=0; j!=sz; ++j)
      {
        const auto b = QtPvdbRateExamplesDialog(pvdb::ConceptFactory::GetTests()[j]).GetRatedExamples();
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
  TRACE("ribi::pvdb::QtPvdbRateExamplesDialog::Test finished successfully");
}

void ribi::pvdb::QtPvdbRateExamplesDialog::on_button_prof_clicked()
{
  if (ui->list->currentItem())
  {
    QtPvdbListWidgetItem* const item = dynamic_cast<QtPvdbListWidgetItem*>(ui->list->currentItem());
    item->setIcon(pvdb::QtCompetency::CompetencyToIcon(pvdb::Competency::profession));
  }
}

void ribi::pvdb::QtPvdbRateExamplesDialog::on_button_organisations_clicked()
{
  if (ui->list->currentItem())
  {
    QtPvdbListWidgetItem* const item = dynamic_cast<QtPvdbListWidgetItem*>(ui->list->currentItem());
    item->setIcon(pvdb::QtCompetency::CompetencyToIcon(pvdb::Competency::organisations));
  }
}

void ribi::pvdb::QtPvdbRateExamplesDialog::on_button_social_clicked()
{
  if (ui->list->currentItem())
  {
    QtPvdbListWidgetItem* const item = dynamic_cast<QtPvdbListWidgetItem*>(ui->list->currentItem());
    item->setIcon(pvdb::QtCompetency::CompetencyToIcon(pvdb::Competency::social_surroundings));
  }
}

void ribi::pvdb::QtPvdbRateExamplesDialog::on_button_target_audience_clicked()
{
  if (ui->list->currentItem())
  {
    QtPvdbListWidgetItem* const item = dynamic_cast<QtPvdbListWidgetItem*>(ui->list->currentItem());
    item->setIcon(pvdb::QtCompetency::CompetencyToIcon(pvdb::Competency::target_audience));
  }
}

void ribi::pvdb::QtPvdbRateExamplesDialog::on_button_prof_development_clicked()
{
  if (ui->list->currentItem())
  {
    QtPvdbListWidgetItem* const item = dynamic_cast<QtPvdbListWidgetItem*>(ui->list->currentItem());
    item->setIcon(pvdb::QtCompetency::CompetencyToIcon(pvdb::Competency::prof_growth));
  }
}

void ribi::pvdb::QtPvdbRateExamplesDialog::on_button_misc_clicked()
{
  if (ui->list->currentItem())
  {
    QtPvdbListWidgetItem* const item = dynamic_cast<QtPvdbListWidgetItem*>(ui->list->currentItem());
    item->setIcon(pvdb::QtCompetency::CompetencyToIcon(pvdb::Competency::misc));
  }
}

void ribi::pvdb::QtPvdbRateExamplesDialog::on_button_ti_knowledge_clicked()
{
  if (ui->list->currentItem())
  {
    QtPvdbListWidgetItem* const item = dynamic_cast<QtPvdbListWidgetItem*>(ui->list->currentItem());
    item->setIcon(pvdb::QtCompetency::CompetencyToIcon(pvdb::Competency::ti_knowledge));
  }
}

void ribi::pvdb::QtPvdbRateExamplesDialog::on_button_ok_clicked()
{
  const boost::shared_ptr<ribi::pvdb::Examples> p = GetRatedExamples();
  assert(p);
  assert(m_concept);
  m_concept->SetExamples(p);
  close();
}
