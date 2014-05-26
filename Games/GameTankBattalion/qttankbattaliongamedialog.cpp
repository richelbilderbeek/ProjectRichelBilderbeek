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
  setCursor(Qt::BlankCursor);

  ui->layout->addWidget(m_game.get());
  m_game->setGeometry(rect());
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

/*
void ribi::taba::QtTankBattalionGameDialog::paintEvent(QPaintEvent *)
{
  //QPainter painter(this);
  //m_game->render(&painter);

  //painter.draw(
  //painter.drawPixmap(rect(),p,p.rect());
}
*/
/*
void ribi::taba::QtTankBattalionGameDialog::resizeEvent(QResizeEvent *)
{
  m_game->setGeometry(rect());
  repaint();
}
*/
