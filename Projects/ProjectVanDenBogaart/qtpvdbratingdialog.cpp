#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbratingdialog.h"

#include <cassert>

#include <boost/lexical_cast.hpp>

#include <QKeyEvent>
#include <QFileDialog>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>

#include "pvdbcompetency.h"
#include "pvdbconcept.h"
#include "pvdbedge.h"
#include "pvdbconceptmap.h"
#include "pvdbexample.h"
#include "pvdbexamples.h"
#include "qtpvdbcompetency.h"
#include "qtpvdbconceptmapwidget.h"
#include "qtpvdbprintratingdialog.h"
#include "qtpvdbconceptmapeditwidget.h"
#include "pvdbfile.h"
#include "pvdbhelper.h"
#include "pvdbnode.h"
#include "trace.h"
#include "ui_qtpvdbratingdialog.h"

QtPvdbRatingDialog::QtPvdbRatingDialog(
  const boost::shared_ptr<pvdb::File> file,
  QWidget* parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbRatingDialog),
    m_back_to_menu(false),
    m_file(file)
{
  ui->setupUi(this);
  assert(file);
  assert(file->GetConceptMap());
  //Student name
  {
    const std::string s = "Naam student: " + file->GetStudentName();
    ui->label_student_name->setText(s.c_str());
  }
  //Assessor name
  {
    ui->label_assessor_name->setText("Naam assessor: ");
    if (!file->GetAssessorName().empty())
    {
      ui->edit_name->setText(file->GetAssessorName().c_str());
      ui->edit_name->setReadOnly(true);
      ui->button_print->setEnabled(true);
    }
    else
    {
      ui->button_print->setEnabled(false);
    }
  }

  DisplayConcepts(file,ui->table_concepts);
  DisplayExamples(file,ui->table_examples);
  DisplayValues(file,ui->table_values);
}

QtPvdbRatingDialog::~QtPvdbRatingDialog()
{
  delete ui;
}

void QtPvdbRatingDialog::DisplayConcepts(
  const boost::shared_ptr<const pvdb::File> file,
  QTableWidget * const table)
{
  const int sz = static_cast<int>(file->GetConceptMap()->GetNodes().size());
  table->setRowCount(sz - 1); //-1 to skip focus question node at index 0

  for (int i=1; i!=sz; ++i)
  {
    const int row = i-1; //-1 to skip focus question node at index 0
    const boost::shared_ptr<const pvdb::Concept> concept = file->GetConceptMap()->GetNodes().at(i)->GetConcept();
    //Name
    {
      QTableWidgetItem * const item = new QTableWidgetItem;
      item->setText(concept->GetName().c_str());
      table->setVerticalHeaderItem(row,item);
    }
    //Rating complexity
    {
      QTableWidgetItem * const item = new QTableWidgetItem;
      item->setText(QString::number(concept->GetRatingComplexity()));
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
      table->setItem(row,0,item);
    }
    //Rating concreteness
    {
      QTableWidgetItem * const item = new QTableWidgetItem;
      item->setText(QString::number(concept->GetRatingConcreteness()));
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
      table->setItem(row,1,item);
    }
    //Rating specificity
    {
      QTableWidgetItem * const item = new QTableWidgetItem;
      item->setText(QString::number(concept->GetRatingSpecificity()));
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
      table->setItem(row,2,item);
    }
  }

  table->verticalHeader()->setMinimumWidth(300);
  table->verticalHeader()->setMaximumWidth(300);
  table->setColumnWidth(0,100);
  table->setColumnWidth(1,100);
  table->setColumnWidth(2,100);
  table->setMaximumWidth(
      table->verticalHeader()->width()
    + table->columnWidth(0)
    + table->columnWidth(1)
    + table->columnWidth(2)
  );



}

  //Examples' icons
void QtPvdbRatingDialog::DisplayExamples(
  const boost::shared_ptr<const pvdb::File> file,
  QTableWidget * const table)
{
  {
    const int n_rows = table->rowCount();
    for(int i=0; i!=n_rows; ++i)
    {
      const pvdb::Competency competency = static_cast<pvdb::Competency>(i + 1); //Skip 0 == uninitialized
      const std::string text = pvdb::CompetencyToDutchStr(competency);
      const QIcon icon = pvdb::QtCompetency::CompetencyToIcon(competency);
      QTableWidgetItem * const item = new QTableWidgetItem;
      item->setText(text.c_str());
      item->setIcon(icon);
      table->setVerticalHeaderItem(i,item);
    }
  }
  //Examples' competencies
  {
    std::map<pvdb::Competency,int> cnts;

    for(const boost::shared_ptr<const pvdb::Node> node: AddConst(file->GetConceptMap()->GetNodes()))
    {
      for (const boost::shared_ptr<const pvdb::Example> example: node->GetConcept()->GetExamples()->Get())
      {
        const auto iter = cnts.find(example->GetCompetency());
        if (iter != cnts.end())
        {
          ++(*iter).second;
        }
        else
        {
          const pvdb::Competency competency = example->GetCompetency();
          cnts.insert(std::make_pair(competency,1));
        }
      }
    }
    const int sum = std::accumulate(cnts.begin(),cnts.end(),0,
      [](int& init,const std::pair<pvdb::Competency,int>& p)
      {
        init += p.second;
        return init;
      }
    );
    if (sum != 0)
    {
      for (const std::pair<pvdb::Competency,int>& p: cnts)
      {
        const int col = 0;
        const int row = static_cast<int>(p.first) - 1;
        if (row == -1) continue; //0 == uninitialized
        assert(row >= 0);
        assert(row < table->rowCount());
        QTableWidgetItem * const item  = new QTableWidgetItem;
        const double f = static_cast<double>(p.second) / static_cast<double>(sum);
        const int percentage = static_cast<int>(std::round(100.0 * f));
        const std::string text = boost::lexical_cast<std::string>(percentage);
        item->setText(text.c_str());
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        table->setItem(row,col,item);
      }
    }
  }
}

void QtPvdbRatingDialog::DisplayValues(
  const boost::shared_ptr<const pvdb::File> file,
  QTableWidget * const table)
{
  std::vector<boost::shared_ptr<const pvdb::Node> > all_nodes = AddConst(file->GetConceptMap()->GetNodes());
  #ifndef NDEBUG
  const int all_sz = static_cast<int>(all_nodes.size());
  #endif

  all_nodes.erase(all_nodes.begin());

  #ifndef NDEBUG
  const int sz = static_cast<int>(all_nodes.size());
  assert(sz == all_sz - 1);
  #endif

  const std::vector<boost::shared_ptr<const pvdb::Node> > nodes = all_nodes;
  const int n_nodes = static_cast<int>(nodes.size());  //Constant 'c'
  //Concreteness experimental: C_e at row = 1, col = 0
  //50.0 * sum_rated_concreteness / n_nodes
  {
    const int sum_rated_concreteness //Constant 'k_c'
      = std::accumulate(nodes.begin(),nodes.end(),0,
      [](int& init, const boost::shared_ptr<const pvdb::Node>& node)
      {
        return init + node->GetConcept()->GetRatingConcreteness();
      }
    );
    std::string text = "N/A";
    if (n_nodes != 0)
    {
      const int c_e
        = static_cast<int>(
          std::round(
           50.0 * static_cast<double>(sum_rated_concreteness)
            / static_cast<double>(n_nodes)
          )
        );
      text = boost::lexical_cast<std::string>(c_e);
    }
    QTableWidgetItem * const item = new QTableWidgetItem;
    item->setText(text.c_str());
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    table->setItem(1,0,item);
  }
  //Concreteness eStimated: C_s at row = 1, col = 1
  //C_s = 100.0 * n_examples / (n_examples + n_nodes + n_relations_not_to_focus)
  {
    const std::vector<boost::shared_ptr<const pvdb::Edge> > edges = AddConst(file->GetConceptMap()->GetEdges());
    const int n_nodes_examples = std::accumulate(nodes.begin(),nodes.end(),0,
      [](int& init, const boost::shared_ptr<const pvdb::Node>& node)
      {
        return init + static_cast<int>(node->GetConcept()->GetExamples()->Get().size());
      }
    );
    const int n_edges_examples = std::accumulate(edges.begin(),edges.end(),0,
      [](int& init, const boost::shared_ptr<const pvdb::Edge>& edge)
      {
        return init + static_cast<int>(edge->GetConcept()->GetExamples()->Get().size());
      }
    );
    const int n_relations_not_to_focus //Constant 'r'
      = std::count_if(edges.begin(),edges.end(),
      [](const boost::shared_ptr<const pvdb::Edge>& edge)
      {
        return edge->GetFrom() != 0 && edge->GetTo() != 0; //Not connected to focus question
      }
    );
    const int n_examples //Constant 'v'
      = n_nodes_examples + n_edges_examples;
    std::string text = "N/A";
    if (n_examples + n_nodes + n_relations_not_to_focus != 0)
    {
      const double c_s
        = static_cast<int>(
          std::round(
            100.0 * static_cast<double>(n_examples)
            / static_cast<double>(n_examples + n_nodes + n_relations_not_to_focus)
          )
        );
      text = boost::lexical_cast<std::string>(c_s);
    }
    QTableWidgetItem * const item = new QTableWidgetItem;
    item->setText(text.c_str());
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    table->setItem(1,1,item);
  }
  //Complexity experimental value: X_e at row = 0, col = 0
  //50.0 * sum_rated_complexity / n_nodes
  {
    const int sum_rated_complexity //Constant 'k_i'
      = std::accumulate(nodes.begin(),nodes.end(),0,
      [](int& init, const boost::shared_ptr<const pvdb::Node>& node)
      {
        return init + node->GetConcept()->GetRatingComplexity();
      }
    );
    std::string text = "N/A";
    if (n_nodes != 0)
    {
      const int x_e
        = static_cast<int>(
          std::round(
           50.0 * static_cast<double>(sum_rated_complexity)
            / static_cast<double>(n_nodes)
          )
        );
      text = boost::lexical_cast<std::string>(x_e);
    }
    QTableWidgetItem * const item = new QTableWidgetItem;
    item->setText(text.c_str());
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    table->setItem(0,0,item);
  }
  //compleXity eStimated: X_s at row = 0, col = 1
  //x_s = ((2*n_relations_not_to_focus)/(n_nodes*(n_nodes-1))))^0.25*100%
  {
    const std::vector<boost::shared_ptr<const pvdb::Edge> > edges = AddConst(file->GetConceptMap()->GetEdges());
    const int n_relations_not_to_focus //Constant 'r'
      = std::count_if(edges.begin(),edges.end(),
      [](const boost::shared_ptr<const pvdb::Edge>& edge)
      {
        return edge->GetFrom() != 0 && edge->GetTo() != 0; //Not connected to focus question
      }
    );
    std::string text = "N/A";
    if (n_nodes > 1)
    {
      const int x_s
        = static_cast<int>(
            std::round(
              100.0
              * std::pow(
                  static_cast<double>(n_relations_not_to_focus * 2)
                / static_cast<double>(n_nodes * (n_nodes - 1) ),
                0.25)
            )
          );
       text = boost::lexical_cast<std::string>(x_s);
     }
    QTableWidgetItem * const item = new QTableWidgetItem;
    item->setText(text.c_str());
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    table->setItem(0,1,item);
  }
  //Experimental specificity: s_e at row = 2, col = 0
  //s_e = 50.0 * sum_rated_specificity / n_nodes
  {
    const int sum_rated_specificity //Constant 'k_s'
      = std::accumulate(nodes.begin(),nodes.end(),0,
      [](int& init, const boost::shared_ptr<const pvdb::Node>& node)
      {
        return init + node->GetConcept()->GetRatingSpecificity();
      }
    );
    std::string text = "N/A";
    if (n_nodes != 0)
    {
      const int s_e
        = static_cast<int>(
          std::round(
            static_cast<double>(50 * sum_rated_specificity)
            / static_cast<double>(n_nodes)
          )
        );
      text = boost::lexical_cast<std::string>(s_e);
    }
    QTableWidgetItem * const item = new QTableWidgetItem;
    item->setText(text.c_str());
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    table->setItem(2,0,item);
  }
  //Richness Experimental: r_e at row = 3, col = 0
  //r_e = ((a + b) / 14) * 100%
  //a = number of different Competencies
  //b = number of Competencies between 1/12th and 1/4th of number of examples
  {
    std::map<pvdb::Competency,int> m;
    //Tally the competencies
    for (const boost::shared_ptr<const pvdb::Node>& node: nodes)
    {
      for (const boost::shared_ptr<const pvdb::Example> example: node->GetConcept()->GetExamples()->Get())
      {
        const pvdb::Competency competency = example->GetCompetency();
        const auto iter = m.find(competency);
        if (iter != m.end())
        {
          ++(*iter).second; //Tally the known competency
        }
        else
        {
          m.insert(std::make_pair(competency,1)); //Tally the first of this competency
        }
      }
    }
    //Remove category 'misc'
    #ifndef NDEBUG
    const int debug_m_size_old = static_cast<int>(m.size());
    const bool debug_will_resize = m.count(pvdb::Competency::misc);
    #endif
    m.erase(pvdb::Competency::misc);
    #ifndef NDEBUG
    const int debug_m_size_new = static_cast<int>(m.size());
    assert( ( debug_will_resize && debug_m_size_old == debug_m_size_new + 1)
         || (!debug_will_resize && debug_m_size_old == debug_m_size_new    )
    );
    #endif


    const int a = static_cast<int>(m.size());
    const int n_examples = std::accumulate(m.begin(),m.end(),0,
      [](int& init,const std::pair<pvdb::Competency,int>& p)
      {
        return init + p.second;
      }
    );
    const int my_min = static_cast<int>(std::ceil( static_cast<double>(n_examples) / 12.0));
    const int my_max = static_cast<int>(std::floor(static_cast<double>(n_examples) /  4.0));
    const int b = std::count_if(m.begin(),m.end(),
      [my_min,my_max](const std::pair<pvdb::Competency,int>& p)
      {
        return p.second >= my_min && p.second <= my_max;
      }
    );

    const int r_e
      = static_cast<int>(
        std::round(
          100.0 * ( static_cast<double>(a+b) / 12.0)
        )
      );
    std::string text = boost::lexical_cast<std::string>(r_e);
    QTableWidgetItem * const item = new QTableWidgetItem;
    item->setText(text.c_str());
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    table->setItem(3,0,item);
  }
  table->verticalHeader()->setMaximumWidth(100);
  table->verticalHeader()->setMinimumWidth(100);
  table->setColumnWidth(0,200);
  table->setColumnWidth(1,200);
  assert(table->verticalHeader()->width() == 100);
  table->setMaximumWidth(
      table->verticalHeader()->width()
    + table->columnWidth(0)
    + table->columnWidth(1)
  );
}



void QtPvdbRatingDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key() == Qt::Key_Escape) { close(); }
}

void QtPvdbRatingDialog::on_button_save_clicked()
{
  //Temporarily disable to widget, otherwise saving cannot succeed
  this->hide();
  const std::string filter_str = std::string("*.") + pvdb::File::GetFilenameExtension();
  const std::string filename_raw = QFileDialog::getSaveFileName(0,"Sla het assessment rapport op",
    QString(),
    filter_str.c_str()).toStdString();
  if (!filename_raw.empty())
  {
    const std::string filename
      =  (filename_raw.size() < pvdb::File::GetFilenameExtension().size()
        || filename_raw.substr( filename_raw.size() - 3, 3 ) != pvdb::File::GetFilenameExtension()
       ? filename_raw + std::string(".") + pvdb::File::GetFilenameExtension()
       : filename_raw);
    assert(filename.size() > 3
      && filename.substr( filename.size() - 3, 3 ) == pvdb::File::GetFilenameExtension()
      && "File must have correct file extension name");
    Save(filename);
    this->m_back_to_menu = true;
    close();
  }
  else
  {
    this->show();
  }
}

void QtPvdbRatingDialog::Save(const std::string& filename) const
{
  assert(filename.size() > 3
    && filename.substr( filename.size() - 3, 3 ) == pvdb::File::GetFilenameExtension()
    && "File must have correct file extension name");

  m_file->Save(filename);
  //{ const std::string debug_str = "File saved as " + filename; TRACE(debug_str); }
}



void QtPvdbRatingDialog::on_button_print_clicked()
{
  #define PVDB_SHOW_WHAT_TO_PRINT_7212367586280756
  #ifdef  PVDB_SHOW_WHAT_TO_PRINT_7212367586280756
  QtPvdbPrintRatingDialog d(this->m_file);

  DisplayConcepts(m_file,d.GetTableConcepts());
  {
    const int sz = static_cast<int>(m_file->GetConceptMap()->GetNodes().size());
    d.GetTableConcepts()->setMinimumHeight( ((sz-1) * 30) + 25 ); //Standard row is 30 pixels high, header 25 pixels
  }

  DisplayExamples(m_file,d.GetTableExamples());
  DisplayValues(m_file,d.GetTableValues());

  this->ShowChild(&d);
  #else
  //Set up a QPrinter
  QPrinter printer;
  const QString filename = "ProjectVanDenBogaart.pdf";
  printer.setOutputFormat(QPrinter::PdfFormat);
  printer.setOrientation(QPrinter::Portrait);
  printer.setPaperSize(QPrinter::A4);
  printer.setFullPage(false);
  printer.setOutputFileName(filename);

  //Start printer dialog
  const boost::shared_ptr<QPrintDialog> print_dialog(new QPrintDialog(&printer));
  print_dialog->setWindowTitle(tr("Print document"));
  if (print_dialog->exec() != QDialog::Accepted) return;

  //Draw the image to painter to printer
  QPainter painter;
  painter.begin(&printer);

  QtPvdbPrintRatingDialog d(this->m_file);
  d.render(&painter);
  painter.end();
  #endif

}

void QtPvdbRatingDialog::on_edit_name_textEdited(const QString &arg1)
{
  if (arg1.size() > 1)
  {
    m_file->SetAssessorName(arg1.toStdString());
    ui->button_print->setEnabled(true);
  }
  else
  {
    ui->button_print->setEnabled(false);
  }
}
