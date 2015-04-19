#include "qttestqtdnadisplay.h"

#include <QDesktopWidget>
#include <QPixmap>

#include <cassert>

#include "fileio.h"
#include "qtdnadisplay.h"
#include "ui_qttestqtdnadisplay.h"

QtTestQtDnaDisplay::QtTestQtDnaDisplay(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtTestQtDnaDisplay),
  m_display{new QtDnaDisplay(this)}
{
  ui->setupUi(this);
  assert(ui->area_content->layout());
  ui->area_content->layout()->addWidget(m_display);

  //Put the dialog in the screen center
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 8 / 10, screen.height() * 8 / 10);
    this->move( screen.center() - this->rect().center() );
  }
}

QtTestQtDnaDisplay::~QtTestQtDnaDisplay()
{
  delete ui;
}

