#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"

#include "kalmanfilterermenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  START_TRACE();
  const std::vector<std::string> args { ribi::MenuDialog::ConvertArguments(argc,argv) };
  ribi::kalman::KalmanFiltererMenuDialog d;
  return d.Execute(args);
}
