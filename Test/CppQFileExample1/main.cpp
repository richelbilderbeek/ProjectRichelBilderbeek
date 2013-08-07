#include <cassert>
#include <cstdio>
#include <QFile>

int main(int /* argc */, char* argv[])
{
  //Copy executable (argv[0] is this executable its full path)
  QFile me(argv[0]);
  const std::string temp_filename = "tmp";
  me.copy(temp_filename.c_str());

  //Check that copy exists
  assert(QFile::exists(temp_filename.c_str()));

  //Delete the copy
  std::remove(temp_filename.c_str());
  assert(!QFile::exists(temp_filename.c_str()));
}
