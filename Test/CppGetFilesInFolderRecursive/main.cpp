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

const std::string GetPathSeperator() noexcept
{
  #ifndef WIN32
  return "\\";
  #else
  return "/";
  #endif
}

const std::vector<std::string> GetFilesInFolder(const std::string& folder)
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

bool IsFolder(const std::string& filename) noexcept
{
  return QDir(filename.c_str()).exists();
}

bool IsRegularFile(const std::string& filename) noexcept
{
  return !QDir(filename.c_str()).exists() && QFile::exists(filename.c_str());
}

///Obtain all files in a folder including thos in a subfolder
//From http://www.richelbilderbeek.nl/CppGetFilesInFolder.htm
const std::vector<std::string> GetFilesInFolderRecursive(const std::string& root_folder)
{
  assert(IsFolder(root_folder));

  //Files in root_folder
  std::vector<std::string> v;
  {
    const std::vector<std::string> files_here {
      GetFilesInFolder(root_folder)
    };
    //Copy the files and folders with path added
    std::transform(files_here.begin(),files_here.end(),std::back_inserter(v),
      [root_folder](const std::string& filename)
      {
        const std::string filename_here {
          root_folder + GetPathSeperator() + filename
        };
        assert(IsRegularFile(filename_here));
        return filename_here;
      }
    );
  }
  //Folders in root_folder
  std::vector<std::string> folders_todo;
  {
    const std::vector<std::string> folders_here {
      GetFoldersInFolder(root_folder)
    };
    std::transform(folders_here.begin(),folders_here.end(),std::back_inserter(folders_todo),
      [root_folder](const std::string& foldername)
      {
        const std::string folder_here {
          root_folder + GetPathSeperator() + foldername
        };
        assert(IsFolder(folder_here));
        return folder_here;
      }
    );
  }

  //Search through all sub folders
  while (!folders_todo.empty())
  {
    const std::string folder_todo {
      folders_todo.back() //Read from the back, so push_back can be used
    };
    //Done with this folder
    folders_todo.pop_back();

    assert( (folders_todo.empty() || folders_todo.back() != folder_todo)
      && "Next folder must not be the one that is just processed");

    const std::vector<std::string> files_here {
      GetFilesInFolder(folder_todo)
    };

    const std::vector<std::string> folders_here {
      GetFoldersInFolder(folder_todo)
    };

    //Copy the files and folders with path added
    std::transform(files_here.begin(),files_here.end(),std::back_inserter(v),
      [folder_todo](const std::string& filename)
      {
        const std::string file_here {
          folder_todo + GetPathSeperator() + filename
        };
        assert(IsRegularFile(file_here));
        return file_here;
      }
    );
    std::transform(folders_here.begin(),folders_here.end(),std::back_inserter(folders_todo),
      [folder_todo](const std::string& foldername)
      {
        assert(!foldername.empty());
        const std::string subfolder_name {
          folder_todo + GetPathSeperator() + foldername
        };
        assert(subfolder_name != folder_todo);
        return subfolder_name;
      }
    );
  }
  return v;
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
    if (!IsRegularFile(local_filename))
    {
      const std::string filename { local_filename };
      std::ofstream f(filename.c_str());
    }
    assert(IsRegularFile(local_filename));
    if (!IsFolder(folder_name))
    {
      const std::string cmd = "mkdir " + folder_name;
      const int error = std::system(cmd.c_str());
      assert(!error || "Folder might already exist");
    }
    assert(IsFolder(folder_name));
    if (!IsRegularFile(folder_name + GetPathSeperator() + in_folder_filename))
    {
      const std::string filename {
          folder_name + GetPathSeperator()
        + in_folder_filename
      };
      std::ofstream f(filename.c_str());
    }
    assert(IsRegularFile(folder_name + GetPathSeperator() + in_folder_filename));

    if (!IsFolder(folder_name + GetPathSeperator() + subfolder_name))
    {
      const std::string cmd = "mkdir " + folder_name + GetPathSeperator() + subfolder_name;
      const int error = std::system(cmd.c_str());
      assert(!error || "Folder might already exist");
    }
    assert(IsFolder(folder_name + GetPathSeperator() + subfolder_name));
    assert(GetFoldersInFolder(folder_name).size() == 1);


    if(!
      IsRegularFile(folder_name
        + GetPathSeperator() + subfolder_name
        + GetPathSeperator() + in_subfolder_filename
        )
      )
    {
      const std::string filename {
          folder_name + GetPathSeperator()
        + subfolder_name + GetPathSeperator()
        + in_subfolder_filename
      };
      std::ofstream f(filename.c_str());
    }
    assert(GetFilesInFolder(folder_name).size() == 1);
    assert(
      IsRegularFile(
          folder_name + GetPathSeperator()
        + subfolder_name + GetPathSeperator()
        + in_subfolder_filename
      )
    );
  }

  //Reading of the files and folders created
  const std::vector<std::string> v {
    GetFilesInFolderRecursive(folder_name)
  };
  std::cout << "Files found: " << std::endl;
  std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
  assert(v.size() == 2);
  assert(
    std::count(
      v.begin(),v.end(),
        folder_name + GetPathSeperator()
      + in_folder_filename
    )
    == 1
  );
  assert(
    std::count(
      v.begin(),v.end(),
        folder_name + GetPathSeperator()
      + subfolder_name + GetPathSeperator()
      + in_subfolder_filename
    )
    == 1
  );
}

/* Screen output

Files found:
my_folder\in_folder.txt
my_folder\my_subfolder\in_subfolder.txt
Press <RETURN> to close this window...

*/
