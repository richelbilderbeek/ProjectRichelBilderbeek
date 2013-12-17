#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttestreversimaindialog.h"
#include "reversiwidget.h"
#include "ui_qttestreversimaindialog.h"
#pragma GCC diagnostic pop

ribi::QtTestReversiMainDialog::QtTestReversiMainDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestReversiMainDialog),
  m_reversi(new ReversiWidget)
{
  ui->setupUi(this);

  ui->layout->addWidget(m_reversi.get());
}

ribi::QtTestReversiMainDialog::~QtTestReversiMainDialog()
{
  delete ui;
}


