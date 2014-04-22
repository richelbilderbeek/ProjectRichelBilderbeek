#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#include "histogramequalizationermenudialog.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  const std::vector<std::string> args {
    ribi::HistogramEqualizationerMenuDialog::ConvertArguments(argc,argv)
  };
  ribi::HistogramEqualizationerMenuDialog d;
  return d.Execute(args);
}
