#include "qtdnadisplay.h"

#include <cassert>
#include <functional>
#include <QLabel>

#include "fileio.h"
#include "ui_qtdnadisplay.h"
#include "dna_r.h"

const std::string QtDnaDisplay::sm_fail{":-("};

QtDnaDisplay::QtDnaDisplay(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtDnaDisplay)
{
  ui->setupUi(this);
}

QtDnaDisplay::~QtDnaDisplay()
{
  delete ui;
}
