#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtreversimaindialog.h"
#include "reversiwidget.h"
#include "ui_qtreversimaindialog.h"
#pragma GCC diagnostic pop

ribi::QtReversiMainDialog::QtReversiMainDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtReversiMainDialog),
  m_reversi(new ReversiWidget)
{
  ui->setupUi(this);

  ui->layout->addWidget(m_reversi.get());
}

ribi::QtReversiMainDialog::~QtReversiMainDialog()
{
  delete ui;
}


