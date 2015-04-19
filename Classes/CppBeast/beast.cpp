#include "beast.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "fileio.h"

const std::string Beast::sm_beast_path{"../../../../Programs/BEAST/bin"};

Beast::Beast()
{
  #ifndef NDEBUG
  Test();
  #endif
  const std::string executable{sm_beast_path + "/beast"};
  if (!ribi::fileio::FileIo().IsRegularFile(executable))
  {
    std::stringstream s;
    s
      << "Error: BEAST executable '" << executable << "' not found\n"
      << "Please change the path\n"
    ;
    throw std::logic_error(s.str().c_str());
  }
}

void Beast::Run(
  const std::string& xml_input_filename,
  const std::string& log_output_filename,
  const std::string& trees_output_filename
) const noexcept
{
  const ribi::fileio::FileIo fileio;
  const std::string executable{sm_beast_path + "/beast"};
  assert(ribi::fileio::FileIo().IsRegularFile(executable)
    && "Checked in constructor");

  const std::string cmd{executable + " -overwrite " + xml_input_filename};
  std::system(cmd.c_str());

  assert(fileio.IsRegularFile(xml_input_filename));


  if (fileio.IsRegularFile("alignment.log"))
  {
    fileio.CopyFile("alignment.log",log_output_filename);
    //fileio.CopyFile("alignment.log",file_basename+".log");
    fileio.DeleteFile("alignment.log");
  }
  if (fileio.IsRegularFile("alignment.trees"))
  {
    fileio.CopyFile("alignment.trees",trees_output_filename);
    //fileio.CopyFile("alignment.trees",file_basename+".trees");
    fileio.DeleteFile("alignment.trees");
  }
}
