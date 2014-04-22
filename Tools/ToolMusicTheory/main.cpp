#include "musictheorymenudialog.h"

int main(int argc, char* argv[])
{
  const std::vector<std::string> args { ribi::MenuDialog::ConvertArguments(argc,argv) };
  ribi::MusicTheoryMenuDialog d;
  d.Execute(args);
}
