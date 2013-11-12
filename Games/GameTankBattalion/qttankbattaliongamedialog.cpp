#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttankbattaliongamedialog.h"
#include "qttankbattaliongamewidget.h"
#include "ui_qttankbattaliongamedialog.h"
#pragma GCC diagnostic pop

QtTankBattalionGameDialog::QtTankBattalionGameDialog(QWidget *parent)
  : QDialog(parent),
    m_game(new QtGameWidget),
    ui(new Ui::QtTankBattalionGameDialog)
{
  ui->setupUi(this);
  ui->layout->addWidget(m_game.get());
}

QtTankBattalionGameDialog::~QtTankBattalionGameDialog()
{
  delete ui;
}
