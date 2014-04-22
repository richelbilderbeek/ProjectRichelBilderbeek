#include <iostream>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/filesystem.hpp>

#include <QDir>
#pragma GCC diagnostic pop

//From http://www.richelbilderbeek.nl/CppGetFilesInFolder.htm
const std::vector<std::string> GetFilesInFolderBoost(const std::string& folder)
{
  std::vector<std::string> v;

  const boost::filesystem::path my_folder
    = boost::filesystem::system_complete(
        boost::filesystem::path(folder));

  if (!boost::filesystem::is_directory(my_folder)) return v;

  const boost::filesystem::directory_iterator j;
  for ( boost::filesystem::directory_iterator i(my_folder);
        i != j;
        ++i)
  {
    if ( boost::filesystem::is_regular_file( i->status() ) )
    {
      const std::string filename = i->path().filename().string();

      //Works with older version of Boost.Filesystem:
      //const std::string filename = i->path().filename();
      v.push_back(filename);
    }
  }
  return v;
}

///GetFilesInFolder creates a std::vector of filenames in a certain folder.
//From http://www.richelbilderbeek.nl/CppGetFilesInFolder.htm
const std::vector<std::string> GetFilesInFolderQt(const std::string& folder)
{
  QDir dir(folder.c_str());
  dir.setFilter(QDir::Files);
  const QFileInfoList list = dir.entryInfoList();

  //Convert QFileInfoList to std::vector<std::string> of filenames
  std::vector<std::string> v;
  const int size = list.size();
  for (int i = 0; i != size; ++i)
  {
    const std::string file_name = list.at(i).fileName().toStdString();
    v.push_back(file_name);
  }
  return v;
}

int main()
{
  const std::string folder = ".";
  assert(GetFilesInFolderBoost(folder) == GetFilesInFolderQt(folder));
  const std::vector<std::string> v = GetFilesInFolderBoost(folder);
  std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
  std::cout << "Number of files: " << v.size() << '\n';
}

/* Screen output:

Makefile
Makefile.Debug
Makefile.Release
Number of files: 3

*/
