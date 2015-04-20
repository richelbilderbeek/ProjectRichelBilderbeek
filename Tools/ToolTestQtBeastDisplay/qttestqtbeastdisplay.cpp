#include "qttestqtbeastdisplay.h"

#include <QDesktopWidget>
#include <QPixmap>

#include <cassert>

#include "fileio.h"
#include "qtbeastdisplay.h"
#include "ui_qttestqtbeastdisplay.h"

QtTestQtBeastDisplay::QtTestQtBeastDisplay(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtTestQtBeastDisplay),
  m_display{new QtBeastDisplay(this)}
{
  ui->setupUi(this);
  assert(ui->area_content->layout());
  ui->area_content->layout()->addWidget(m_display);

  on_edit_beast_returnPressed();

  //Put the dialog in the screen center
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 8 / 10, screen.height() * 8 / 10);
    this->move( screen.center() - this->rect().center() );
  }
}

QtTestQtBeastDisplay::~QtTestQtBeastDisplay()
{
  delete ui;
}

void QtTestQtBeastDisplay::on_edit_beast_returnPressed()
{
  this->m_display->SetBeast(ui->edit_beast->text().toStdString());
}
