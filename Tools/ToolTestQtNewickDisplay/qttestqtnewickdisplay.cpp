#include "qttestqtnewickdisplay.h"

#include <QDesktopWidget>
#include <QPixmap>

#include <cassert>

#include "fileio.h"
#include "qtnewickdisplay.h"
#include "ui_qttestqtnewickdisplay.h"

QtTestQtNewickDisplay::QtTestQtNewickDisplay(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtTestQtNewickDisplay),
  m_display{new QtNewickDisplay(this)}
{
  ui->setupUi(this);
  assert(ui->area_content->layout());
  ui->area_content->layout()->addWidget(m_display);

  on_edit_newick_returnPressed();

  //Put the dialog in the screen center
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 8 / 10, screen.height() * 8 / 10);
    this->move( screen.center() - this->rect().center() );
  }
}

QtTestQtNewickDisplay::~QtTestQtNewickDisplay()
{
  delete ui;
}

void QtTestQtNewickDisplay::on_edit_newick_returnPressed()
{
  this->m_display->SetNewick(ui->edit_newick->text().toStdString());
}
