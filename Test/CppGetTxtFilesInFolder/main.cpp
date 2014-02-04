#include <string>
#include <vector>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <boost/xpressive/xpressive.hpp>
#pragma GCC diagnostic pop

const std::vector<std::string> GetFilesInFolder(const std::string& folder)
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
      //const std::string full_filename = folder + "/" + filename;
      v.push_back(filename);
    }
  }
  return v;
}

const std::vector<std::string> GetFilesInFolderBoostRegex(const std::string& folder, const boost::regex& regex)
{
  //Get all filenames
  const std::vector<std::string> v = GetFilesInFolder(folder);

  //Create the resulting std::vector
  std::vector<std::string> w;

  //Copy all filenames matching the regex in the resulting std::vector
  for(const std::string& s: v)
  {
    if (boost::regex_match(s,regex)) w.push_back(s);
  }

  return w;
}

const std::vector<std::string> GetFilesInFolderBoostXpressive(
  const std::string& folder,
  const boost::xpressive::sregex& regex)
{
  //Get all filenames
  const std::vector<std::string> v = GetFilesInFolder(folder);

  //Create the resulting std::vector
  std::vector<std::string> w;

  //Copy all filenames matching the regex in the resulting std::vector
  for(const std::string& s: v)
  {
    if (boost::xpressive::regex_match(s,regex))
    {
      w.push_back(s);
    }
  }
  return w;
}

const std::vector<std::string> GetTxtFilesInFolder(const std::string& folder)
{
  const std::string regex_str("(.*\\.txt)");
  const boost::xpressive::sregex xpressive_regex(boost::xpressive::sregex::compile(regex_str));
  const std::vector<std::string> files = GetFilesInFolderBoostXpressive(folder,xpressive_regex);

  #ifndef NDEBUG
  const boost::regex regex_regex(regex_str);
  const std::vector<std::string> files_regex = GetFilesInFolderBoostRegex(folder,regex_regex);
  assert(files == files_regex);
  #endif
  return files;
}

#include <fstream>

int main()
{
  const std::string folder = ".";
  const std::string tmp_txt_filename = "tmp.txt";

  //Delete the temp file (if present)
  std::remove(tmp_txt_filename.c_str());

  const int n_before = static_cast<int>(GetTxtFilesInFolder(folder).size());

  //Create a .txt file
  {
    std::ofstream f(tmp_txt_filename.c_str());
  }
  const int n_after = static_cast<int>(GetTxtFilesInFolder(folder).size());
  assert(n_before + 1 == n_after);

  //Delete the temp file
  std::remove(tmp_txt_filename.c_str());
}

