#ifndef NDEBUG
#include "qtmutualismbreakdownerparameterswidget.h"

#include <cassert>
#include <fstream>
#include <iostream>

#include "fileio.h"

#include "ui_qtmutualismbreakdownerparameterswidget.h"

void QtMutualismBreakdownerParametersWidget::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  using ribi::fileio::FileIo;
  {
    const QtMutualismBreakdownerParametersWidget d;
    const auto p = d.GetParameters();
    const auto q = d.GetParameters();
    assert(p == q);
  }
  //Initial Loripes density
  {
    QtMutualismBreakdownerParametersWidget d;
    const auto p = d.GetParameters();
    d.ui->box_initial_loripes_density->setValue(
      d.ui->box_initial_loripes_density->value() + 1.0
    );
    const auto q = d.GetParameters();
    assert(p != q);
  }
  //Organic material breakdown
  {
    QtMutualismBreakdownerParametersWidget d;
    const auto p = d.GetParameters();
    d.ui->box_organic_matter_addition->setValue(
      d.ui->box_organic_matter_addition->value() + 1.0
    );
    const auto q = d.GetParameters();
    assert(p != q);
  }
  //organic_matter_to_sulfide_factor
  {
    QtMutualismBreakdownerParametersWidget d;
    const auto p = d.GetParameters();
    d.ui->box_organic_matter_to_sulfide_factor->setValue(
      d.ui->box_organic_matter_to_sulfide_factor->value() + 1.0
    );
    const auto q = d.GetParameters();
    assert(p != q);
  }
  //organic_matter_to_sulfide_rate
  {
    QtMutualismBreakdownerParametersWidget d;
    const auto p = d.GetParameters();
    d.ui->box_organic_matter_to_sulfide_rate->setValue(
      d.ui->box_organic_matter_to_sulfide_rate->value() + 1.0
    );
    const auto q = d.GetParameters();
    assert(p != q);
  }
}
#endif



