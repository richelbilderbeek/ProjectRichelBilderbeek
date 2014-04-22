#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QDir>
#pragma GCC diagnostic pop

///Obtain all files in a folder including thos in a subfolder
//From http://www.richelbilderbeek.nl/CppGetFoldersInFolder.htm
const std::vector<std::string> GetFoldersInFolder(const std::string& folder)
{
  QDir dir(folder.c_str());
  dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot   );
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

const std::string GetPathSeperator() noexcept
{
  #ifndef WIN32
  return "\\";
  #else
  return "/";
  #endif
}

bool IsFolder(const std::string& filename) noexcept
{
  return QDir(filename.c_str()).exists();
}

bool IsRegularFile(const std::string& filename) noexcept
{
  return !QDir(filename.c_str()).exists() && QFile::exists(filename.c_str());
}

int main()
{
  //Use the following structure:
  // - local.txt
  // - my_folder/in_folder.txt
  // - my_folder/my_subfolder/in_subfolder.txt
  const std::string local_filename { "local.txt" };
  const std::string folder_name { "my_folder" };
  const std::string in_folder_filename { "in_folder.txt" };
  const std::string subfolder_name { "my_subfolder" };
  const std::string in_subfolder_filename { "in_subfolder.txt" };
  //File and folder creation
  {
    {
      const std::string filename { local_filename };
      std::ofstream f(filename.c_str());
    }
    assert(IsRegularFile(local_filename));
    {
      const std::string cmd = "mkdir " + folder_name;
      const int error = std::system(cmd.c_str());
      assert(!error);
    }
    assert(IsFolder(folder_name));
    {
      const std::string filename {
          folder_name + GetPathSeperator()
        + in_folder_filename
      };
      std::ofstream f(filename.c_str());
    }
    assert(IsRegularFile(folder_name + GetPathSeperator() + in_folder_filename));
    {
      const std::string cmd = "mkdir " + folder_name + GetPathSeperator() + subfolder_name;
      const int error = std::system(cmd.c_str());
      assert(!error);
    }
    assert(IsFolder(folder_name + GetPathSeperator() + subfolder_name));
    {
      const std::string filename {
          folder_name + GetPathSeperator()
        + subfolder_name + GetPathSeperator()
        + in_subfolder_filename
      };
      std::ofstream f(filename.c_str());
    }
    assert(
      IsRegularFile(
          folder_name + GetPathSeperator()
        + subfolder_name + GetPathSeperator()
        + in_subfolder_filename
      )
    );
  }
  //Reading of the folder created
  {
    const std::vector<std::string> v {
      GetFoldersInFolder(folder_name)
    };
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
    assert(v.size() == 1);
    assert(
      std::count(
        v.begin(),v.end(),
          subfolder_name
      )
      == 1
    );
  }
  {
    const std::vector<std::string> v {
      GetFoldersInFolder(folder_name + GetPathSeperator() + subfolder_name)
    };
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
    assert(v.size() == 0);
  }
}
