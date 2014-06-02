#include "trianglefile.h"

#include <cassert>
#include <fstream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/make_shared.hpp>

#include <QFile>

#include "fileio.h"
#include "geometry.h"
#include "polyfile.h"
#include "polyfilefrompolygons.h"
#include "trace.h"

//#include "triangle.h"

//#define TODO_ISSUE_207
#ifdef  TODO_ISSUE_207
#include "trianglecppmain.h"
#endif

#pragma GCC diagnostic pop

ribi::TriangleFile::TriangleFile(
  const Polygons& shapes
) : m_polyfile{boost::make_shared<PolyFileFromPolygons>(shapes)}
{
  #ifndef NDEBUG
  Test();
  #endif

  //assert(holes.empty() && "Adding holes is not implemented yet");
}

std::pair<int,char **> ribi::TriangleFile::CreateArgv(const std::vector<std::string>& v) noexcept
{
  typedef char* String;
  typedef String* Strings;
  const int argc = static_cast<int>(v.size());
  const int buffer_sz = 256; //Will leak
  Strings argv = new String[256];
  for (int i=0; i!=argc; ++i)
  {
    argv[i] = new char[v[i].size() + 1];
    std::strcpy(argv[i],&v[i][0]);
  }
  for (int i=argc; i!=buffer_sz; ++i)
  {
    argv[i] = nullptr;
  }
  std::pair<int,char **> p = std::make_pair(argc,argv);
  return p;
}

void ribi::TriangleFile::DeleteArgv(const std::pair<int,char **>& p) noexcept
{
  const int argc = p.first;
  for(int i = 0; i != argc; ++i)
  {
    delete[] p.second[i];
  }
  delete[] p.second;
}

//#define TODO_ISSUE_207
#ifdef  TODO_ISSUE_207
void ribi::TriangleFile::ExecuteTriangle(
  std::string& node_filename,
  std::string& ele_filename,
  std::string& poly_filename,
  const double quality,
  const double area,
  const bool verbose) const
{
  const std::string filename { fileio::FileIo().GetTempFileName(".poly") };
  node_filename = "";
  ele_filename = "";
  poly_filename = "";

  {
    std::ofstream f(filename.c_str());
    m_polyfile << this->ToStr();
  }

  const std::string exe_filename { "triangle.exe" };


  //Specific
  const std::string quality_str = boost::lexical_cast<std::string>(quality);
  const std::string area_str = boost::lexical_cast<std::string>(area);
  assert(quality_str.find(',') == std::string::npos && "No Dutch please");
  assert(area_str.find(',')    == std::string::npos && "No Dutch please");
  std::vector<std::string> cmd {
    exe_filename,
    "-j",
    "-z",
    "-q",
    quality_str,
    "-a",
    area_str,
    filename
  };
  if (!verbose)
  {
    cmd.push_back("-Q");
    std::swap(cmd[cmd.size() - 1], cmd[cmd.size() - 2]);
  }
  const std::pair<int,char **> p = CreateArgv(cmd);
  triangle_main(p.first,p.second);
  DeleteArgv(p);
  //End of specific part

  const std::string filename_base(fileio::FileIo().GetFileBasename(filename));
  node_filename = filename_base + ".1.node";
  ele_filename = filename_base + ".1.ele";
  poly_filename = filename_base + ".1.poly";
  assert(fileio::FileIo().IsRegularFile(node_filename));
  assert(fileio::FileIo().IsRegularFile(ele_filename));
  assert(fileio::FileIo().IsRegularFile(poly_filename));
  fileio::FileIo().DeleteFile(filename);
}

void ribi::TriangleFile::ExecuteTriangleCpp(
  std::string& node_filename,
  std::string& ele_filename,
  std::string& poly_filename,
  const double quality,
  const double area,
  const bool verbose) const
{
  const std::string filename { fileio::FileIo().GetTempFileName(".poly") };
  node_filename = "";
  ele_filename = "";
  poly_filename = "";

  {
    std::ofstream f(filename.c_str());
    m_polyfile << this->ToStr();
  }

  assert(fileio::FileIo().IsRegularFile(filename));
  const std::string exe_filename { "triangle.exe" };

  //Specific
  const std::string quality_str = boost::lexical_cast<std::string>(quality);
  const std::string area_str = boost::lexical_cast<std::string>(area);
  assert(quality_str.find(',') == std::string::npos && "No Dutch please");
  assert(area_str.find(',')    == std::string::npos && "No Dutch please");
  std::vector<std::string> cmd {
    exe_filename,
    "-j",
    "-z",
    "-q",
    quality_str,
    "-a",
    area_str,
    filename
  };
  if (!verbose)
  {
    cmd.push_back("-Q");
    std::swap(cmd[cmd.size() - 1], cmd[cmd.size() - 2]);
  }
  tricpp::triangle_cpp_main(cmd);
  //End of specific part

  const std::string filename_base(fileio::FileIo().GetFileBasename(filename));
  node_filename = filename_base + ".1.node";
  ele_filename = filename_base + ".1.ele";
  poly_filename = filename_base + ".1.poly";
  assert(fileio::FileIo().IsRegularFile(node_filename));
  assert(fileio::FileIo().IsRegularFile(ele_filename));
  assert(fileio::FileIo().IsRegularFile(poly_filename));
  fileio::FileIo().DeleteFile(filename);
}
#endif // TODO_ISSUE_207

void ribi::TriangleFile::ExecuteTriangleExe(
  std::string& node_filename,
  std::string& ele_filename,
  std::string& poly_filename,
  const Angle triangle_min_angle, //Triangle calls this the 'quality' parameter
  const Area triangle_max_area,   //Triangle calls this the 'area' parameter
  const bool verbose) const
{
  const std::string filename { fileio::FileIo().GetTempFileName(".poly") };
  const bool delete_poly_file = false;
  node_filename = "";
  ele_filename = "";
  poly_filename = "";

  if (verbose)
  {
    std::stringstream s;
    s << "Writing .poly file to '" << filename << "'";
    std::clog << s.str() << std::endl;
  }
  {
    std::ofstream f(filename.c_str());
    f << m_polyfile->ToStr();
  }

  assert(fileio::FileIo().IsRegularFile(filename));
  #ifdef _WIN32
  //const std::string exe_filename { "triangle.exe" };
  const std::string exe_filename { "ToolTriangleConsole.exe" };
  #else
  const std::string exe_filename { "ToolTriangleConsole" };
  #endif

  //Specific
  const std::string quality_str
    = boost::lexical_cast<std::string>(
        triangle_min_angle.value()
      * 360.0 / boost::math::constants::two_pi<double>() //Triangle uses degrees
    );
  const std::string area_str
    = boost::lexical_cast<std::string>(triangle_max_area.value());
  assert(quality_str.find(',') == std::string::npos && "No Dutch please");
  assert(area_str.find(',')    == std::string::npos && "No Dutch please");
  if (!fileio::FileIo().IsRegularFile(exe_filename))
  {
    QFile file( (":/trianglefile/files/" + exe_filename).c_str() );
    file.copy(exe_filename.c_str());
  }
  assert(fileio::FileIo().IsRegularFile(exe_filename));

  std::stringstream command;
  command
    << exe_filename
    << " -j -z -q"
    << quality_str
    << " -a"
    << area_str
    << (verbose ? "" : " -Q")
    << " "
    << filename
  ;
  if (verbose) { std::cout << "Starting command '" << command.str() << "'" << std::endl; }
  const bool error = std::system(command.str().c_str());

  //Delete input file directly after running the program,
  //so that independent of a possible error this behavior occurs
  {
    if (delete_poly_file)
    {
      if (verbose) { std::cout << "Deleted file " << filename << std::endl; }
      fileio::FileIo().DeleteFile(filename);
    }
    else
    {
      if (verbose) { std::cout << "Kept file " << filename << " for inspection" << std::endl; }
    }
  }

  //Respond to errors
  if (error)
  {
    if (verbose)
    {
      std::cout << "Finished command with an error" << std::endl;
      TRACE(m_polyfile->ToStr());
    }
    std::stringstream s;
    s << "Error: '" << command << "' failed, with error code " << error;
    throw std::runtime_error(s.str().c_str());
  }
  if (verbose) { std::cout << "Finished command without errors" << std::endl; }
  //End of specific

  const std::string filename_base(fileio::FileIo().GetFileBasename(filename));
  node_filename = filename_base + ".1.node";
  ele_filename = filename_base + ".1.ele";
  poly_filename = filename_base + ".1.poly";
  assert(fileio::FileIo().IsRegularFile(node_filename));
  assert(fileio::FileIo().IsRegularFile(ele_filename));
  assert(fileio::FileIo().IsRegularFile(poly_filename));
}

const ribi::TriangleFile::Polygons& ribi::TriangleFile::GetShapes() const noexcept
{
  assert(m_polyfile);
  return m_polyfile->GetPolygons();
}


std::string ribi::TriangleFile::GetVersion() noexcept
{
  return "1.6";
}

std::vector<std::string> ribi::TriangleFile::GetVersionHistory() noexcept
{
  return {
    "2014-02-07: Version 1.0: initial version, use of Windows executable only",
    "2014-04-04: Version 1.1: allow to call Triangle its code directly",
    "2014-05-18: Version 1.2: allow use of a Linux executable"
    "2014-05-19: Version 1.3: use of non-freezing Windows executable",
    "2014-05-26: Version 1.4: use of units in Triangle 'area' (the maximum area of a triangle) and 'quality' (the minimum angle of a triangle's corner) parameters"
    "2014-05-27: Version 1.5: split of sections to PolyFile",
    "2014-06-02: Version 1.6: split of sections to PolyFileFromPolygons"
  };
}

#ifndef NDEBUG
void ribi::TriangleFile::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::TriangleFile::Test");
  const bool verbose = true;
  //Call Triangle with simple shapes
  {
    const std::vector<Coordinat> points {
      {0.5, 2.0}, //0
      {1.0, 1.0}, //1
      {1.0, 0.0}, //2
      {0.0, 0.0}, //3
      {0.0, 1.0}  //4
    };
    Polygon v;
    boost::geometry::append(v, points);
    try
    {
      TriangleFile f( {v} );
      //TRACE(f.ToStr());
      std::string filename_node;
      std::string filename_ele;
      std::string filename_poly;
      const Angle min_angle
        = 20.0 //Default used by Triangle, in degrees
        * (boost::math::constants::two_pi<double>() / 360.0)
        * boost::units::si::radian
      ;
      const Area max_area = 1.0 * boost::units::si::square_meter;
      //#define TODO_ISSUE_207
      #ifdef  TODO_ISSUE_207
      f.ExecuteTriangle(filename_node,filename_ele,filename_poly,min_angle,max_area,verbose);
      #else
      f.ExecuteTriangleExe(filename_node,filename_ele,filename_poly,min_angle,max_area,verbose);
      #endif // TODO_ISSUE_207
      assert(fileio::FileIo().IsRegularFile(filename_node));
      assert(fileio::FileIo().IsRegularFile(filename_ele));
      assert(fileio::FileIo().IsRegularFile(filename_poly));
    }
    catch (std::exception& e)
    {
      TRACE(e.what());
      assert(!"Should not get here");
    }
    TRACE("Finished ribi::TriangleFile::Test successfully");
  }
}
#endif
