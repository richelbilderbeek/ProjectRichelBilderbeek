#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbconcepteditdialog.h"

#include <cassert>

#ifdef COMPILER_SUPPORTS_THREADS_20130507
#include <thread>
#endif

#include <QKeyEvent>
#include <QObjectList>

#include "pvdbcompetency.h"
#include "pvdbexample.h"
#include "pvdbexamplefactory.h"
#include "pvdbexamplesfactory.h"
#include "pvdbexamples.h"
#include "pvdbhelper.h"
#include "pvdbconcept.h"
#include "pvdbconceptfactory.h"
#include "qtpvdbcompetency.h"
#include "ui_qtpvdbconcepteditdialog.h"
#include "trace.h"

///QTreeWidgetItem with the only function of storing a pvdb::Competency additionally, only used in testing
struct QtPvdbListWidgetItem : public QListWidgetItem
{
  QtPvdbListWidgetItem(
    const pvdb::Competency competency
    )
    : QListWidgetItem(0),
      m_competency(competency)
  {

  }
  const pvdb::Competency m_competency;
};

QtPvdbConceptEditDialog::QtPvdbConceptEditDialog(
  const boost::shared_ptr<pvdb::Concept> concept,
  QWidget* parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbConceptEditDialog),
#ifdef PVDB_WRITE_TO_CONCEPT
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
  const std::vector<boost::shared_ptr<const pvdb::Example> > v = AddConst(concept->GetExamples()->Get());
  std::for_each(v.begin(),v.end(),
    [this](const boost::shared_ptr<const pvdb::Example>& s)
    {
      assert(!s->GetText().empty());
      QtPvdbListWidgetItem * const item = new QtPvdbListWidgetItem(s->GetCompetency());
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

QtPvdbConceptEditDialog::~QtPvdbConceptEditDialog()
{
  delete ui;
}

void QtPvdbConceptEditDialog::keyPressEvent(QKeyEvent* e)
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

void QtPvdbConceptEditDialog::on_button_add_clicked()
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

void QtPvdbConceptEditDialog::RemoveEmptyItem(QListWidgetItem * item)
{
  if (item->text().isEmpty())
  {
    delete item;
    this->update();
  }
}

#ifndef NDEBUG
void QtPvdbConceptEditDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
  std::thread t(
    []
    {
  #endif
  {
    //Assume reading in a concept and clicking OK without modification does not modify anything
    const auto v = pvdb::ConceptFactory::GetTests();
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<pvdb::Concept>& concept)
      {
        const boost::shared_ptr<const pvdb::Concept> old_concept = pvdb::ConceptFactory::DeepCopy(concept);
        assert(concept != old_concept);
        assert(IsEqual(*concept,*old_concept));
        QtPvdbConceptEditDialog d(concept);
        //Do nothing...
        d.on_button_ok_clicked();
        #ifdef PVDB_WRITE_TO_CONCEPT
        assert(d.WriteToConcept() == old_concept);
        #else
        assert(IsEqual(*concept,*old_concept));
        #endif
      }
    );
  }
  {
    //Assume reading in a concept and clicking OK after modification of the name does modify concept
    const auto v = pvdb::ConceptFactory::GetTests();
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<pvdb::Concept>& concept)
      {
        const boost::shared_ptr<const pvdb::Concept> old_concept = pvdb::ConceptFactory::DeepCopy(concept);
        assert(IsEqual(*concept,*old_concept));
        QtPvdbConceptEditDialog d(concept);
        d.ui->edit_concept->setText(d.ui->edit_concept->text() + "MODIFICATION");
        d.on_button_ok_clicked();
        #ifdef PVDB_WRITE_TO_CONCEPT
        TRACE("TODO");
        #else
        TRACE("TODO");
        //assert(concept != old_concept);
        #endif
      }
    );
  }
  {
    //Assume reading in a concept and clicking OK after adding an example
    const auto v = pvdb::ConceptFactory::GetTests();
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<pvdb::Concept>& concept)
      {
        const boost::shared_ptr<const pvdb::Concept> old_concept = pvdb::ConceptFactory::DeepCopy(concept);
        assert(IsEqual(*concept,*old_concept));
        QtPvdbConceptEditDialog d(concept);
        assert(d.ui->edit_text->text().isEmpty());
        d.ui->edit_text->setText("TO BE ADDED EXAMPLE");
        d.on_button_add_clicked(); //Should add
        d.on_button_ok_clicked();
        #ifdef PVDB_WRITE_TO_CONCEPT
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
    const auto v = pvdb::ConceptFactory::GetTests();
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<pvdb::Concept>& concept)
      {
        const boost::shared_ptr<const pvdb::Concept> old_concept = pvdb::ConceptFactory::DeepCopy(concept);
        assert(IsEqual(*concept,*old_concept));
        QtPvdbConceptEditDialog d(concept);
        //Change name
        d.ui->edit_concept->setText(d.ui->edit_concept->text() + "MODIFICATION");
        //Change examples
        assert(d.ui->edit_text->text().isEmpty());
        d.ui->edit_text->setText("TO BE ADDED EXAMPLE");
        d.on_button_add_clicked(); //Should add
        //DO NOT PRESS OK d.on_button_ok_clicked();
        #ifdef PVDB_WRITE_TO_CONCEPT
        TRACE("TODO");
        #else
        assert(IsEqual(*concept,*old_concept));
        #endif
      }
    );
  }
  TRACE("QtPvdbConceptEditDialog::Test completed successfully");
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
    }
  );
  t.detach();
  #endif

}
#endif

void QtPvdbConceptEditDialog::on_button_ok_clicked()
{
  #ifndef PVDB_WRITE_TO_CONCEPT
  assert(m_concept);
  //Name
  const std::string name = ui->edit_concept->text().toStdString();
  //Examples
  std::vector<boost::shared_ptr<pvdb::Example> > v;

  const int n_items = ui->list_examples->count();
  for (int i=0; i!=n_items; ++i)
  {
    const QListWidgetItem * const item = ui->list_examples->item(i);
    const QtPvdbListWidgetItem * const pvdb_item = dynamic_cast<const QtPvdbListWidgetItem *>(item);
    const pvdb::Competency competency = pvdb_item ? pvdb_item->m_competency : pvdb::Competency::uninitialized;
    boost::shared_ptr<pvdb::Example> p(
      pvdb::ExampleFactory::Create(
        item->text().toStdString(),
        competency
      )
    );
    v.push_back(p);
  }
  assert(n_items == boost::numeric_cast<int>(v.size()));
  //Set to concept
  const boost::shared_ptr<pvdb::Examples> examples(new pvdb::Examples(v));
  assert(examples);
  assert(this);
  assert(m_concept);
  assert(m_concept->GetExamples());
  m_concept->SetName(name);
  m_concept->SetExamples(examples);
  #endif
  close();
}

#ifdef PVDB_WRITE_TO_CONCEPT
const boost::shared_ptr<pvdb::Concept> QtPvdbConceptEditDialog::WriteToConcept() const
{
  //Name
  const std::string name = ui->edit_concept->text().toStdString();
  //Examples
  std::vector<boost::shared_ptr<pvdb::Example> > v;

  const int n_items = ui->list_examples->count();
  for (int i=0; i!=n_items; ++i)
  {
    const QListWidgetItem * const item = ui->list_examples->item(i);
    const QtPvdbListWidgetItem * const pvdb_item = dynamic_cast<const QtPvdbListWidgetItem *>(item);
    const pvdb::Competency competency = pvdb_item ? pvdb_item->m_competency : pvdb::Competency::uninitialized;
    boost::shared_ptr<pvdb::Example> p(
      pvdb::ExampleFactory::Create(
        item->text().toStdString(),
        competency
      )
    );
    v.push_back(p);
  }
  assert(n_items == boost::numeric_cast<int>(v.size()));
  //Set to concept
  const boost::shared_ptr<pvdb::Examples> examples(new pvdb::Examples(v));
  assert(examples);
  const boost::shared_ptr<pvdb::Concept> concept
    = pvdb::ConceptFactory::Create(
      name,
      examples,
      m_rating_complexity,
      m_rating_concreteness,
      m_rating_specificity);

  assert(concept);
  return concept;
}
#endif
