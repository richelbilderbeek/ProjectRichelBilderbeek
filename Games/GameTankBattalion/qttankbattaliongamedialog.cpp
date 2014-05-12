#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttankbattaliongamedialog.h"

#include <QPainter>

#include "qttankbattaliongamewidget.h"
#include "ui_qttankbattaliongamedialog.h"
#pragma GCC diagnostic pop

ribi::taba::QtTankBattalionGameDialog::QtTankBattalionGameDialog(QWidget *parent)
  : QDialog(parent),
    m_game(new QtGameWidget),
    ui(new Ui::QtTankBattalionGameDialog)
{
  ui->setupUi(this);
  ui->layout->addWidget(m_game.get());
}

ribi::taba::QtTankBattalionGameDialog::~QtTankBattalionGameDialog()
{
  delete ui;
}

void ribi::taba::QtTankBattalionGameDialog::keyPressEvent(QKeyEvent * e)
{
  m_game->keyPressEvent(e);
}

void ribi::taba::QtTankBattalionGameDialog::keyReleaseEvent(QKeyEvent * e)
{
  m_game->keyReleaseEvent(e);
}

void ribi::taba::QtTankBattalionGameDialog::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  QPixmap p;

  m_game->render(&p);
  painter.drawPixmap(rect(),p);
}
