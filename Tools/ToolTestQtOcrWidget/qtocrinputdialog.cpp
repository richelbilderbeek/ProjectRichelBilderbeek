#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtocrinputdialog.h"

#include <algorithm>
#include <numeric>
#include <string>

#include <QDesktopWidget>
#include <QPainter>

#include <cassert>

#include "qtocrwidget.h"
#include "ui_qtocrinputdialog.h"
#pragma GCC diagnostic pop

QtOcrInputDialog::QtOcrInputDialog(
  const std::string& path,
  const std::string& whitelist,
  QWidget *parent)
  : QDialog(parent),
    ui(new Ui::QtOcrInputDialog),
    m_ocr_widget(new QtOcrWidget(path,whitelist))
{
  ui->setupUi(this);

  {
    assert(!ui->ocr_widget_placeholder->layout());
    QLayout * const layout = new QGridLayout;
    ui->ocr_widget_placeholder->setLayout(layout);
    layout->addWidget(m_ocr_widget.get());
    assert(ui->ocr_widget_placeholder->layout());
  }

  m_ocr_widget->resize(m_ocr_widget->size());
}

QtOcrInputDialog::~QtOcrInputDialog()
{
  delete ui;
}

void QtOcrInputDialog::paintEvent(QPaintEvent *)
{
  assert(m_ocr_widget);

  std::string s = m_ocr_widget->Read();

  ///Remove trailing '\n' and '\r'
  while (1)
  {
    if (s.empty()) break;
    const char last_char = s.substr(s.size()-1,1)[0];
    if (last_char == '\r' || last_char == '\n')
    {
      s.resize(s.size() - 1);
    }
    else
    {
      break;
    }
  }
  this->setWindowTitle(s.c_str());
}

void QtOcrInputDialog::on_button_clear_clicked()
{
  m_ocr_widget->clear();
}
