#include "trianglefile.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/make_shared.hpp>
#include <boost/units/io.hpp>

#include <QFile>

#include "fileio.h"
#include "geometry.h"
#include "polyfile.h"
#include "polyfilefrompolygons.h"
#include "testtimer.h"
#include "trace.h"

//#define TODO_ISSUE_207
#ifdef  TODO_ISSUE_207
#include "trianglecppmain.h"
#endif

#pragma GCC diagnostic pop

ribi::TriangleFile::TriangleFile(
  const Polygons& polygons,
  const Linestrings& linestrings
) : m_polyfile(boost::make_shared<PolyFileFromPolygons>(polygons,linestrings))
{
  #ifndef NDEBUG
  Test();
  #endif
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
  const std::string filename { fileio::FileIo().GetTempFileNameSimple(".poly") };
  const bool delete_poly_file{false}; //True does not leave files scattered around
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
    f << (*m_polyfile);
    //f << std::fixed << std::setprecision(11) << (*m_polyfile);
  }

  assert(fileio::FileIo().IsRegularFile(filename));
  #ifdef _WIN32
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

  //Prevent a '1.0e-5' notation as Triangle cannot handle it
  //Convert it to 0.00001 instead
  std::string area_str = "";
  {
    std::stringstream s;
    s << std::fixed
      //<< std::setprecision(20) //Works
      << std::setprecision(99) //Works
      << triangle_max_area.value()
    ;
    area_str = s.str();
  }

  assert(quality_str.find(',') == std::string::npos && "No Dutch please");
  assert(area_str.find(',')    == std::string::npos && "No Dutch please");
  if (!fileio::FileIo().IsRegularFile(exe_filename))
  {
    QFile file( (":/trianglefile/files/" + exe_filename).c_str() );
    file.copy(exe_filename.c_str());
  }
  assert(fileio::FileIo().IsRegularFile(exe_filename));

  #ifndef _WIN32
  {
    //Do chmod +x in Linux
    std::stringstream chmod;
    chmod
      << "chmod +x "
      << exe_filename;
    if (verbose) { std::cout << "Starting command '" << chmod.str() << "'" << std::endl; }
    const bool error = std::system(chmod.str().c_str());
    if (error)
    {
      if (verbose)
      {
        std::cout << "Finished command with an error (" << __FILE__ << "," << __LINE__ << ")" << std::endl
          << *m_polyfile << std::endl;
      }
      std::stringstream s;
      s << "Error: '" << chmod.str() << "' failed (" << __FILE__ << "," << __LINE__ << "), with error code " << error;
      throw std::runtime_error(s.str());
    }

  }
  #endif

  std::stringstream command;
  command
  #ifndef _WIN32
    << "./"
  #endif
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
      std::cout << "Finished command with an error (" << __FILE__ << "," << __LINE__ << ")" << std::endl
        << *m_polyfile << std::endl;
    }
    std::stringstream s;
    s << "Error: '" << command.str() << "' failed (" << __FILE__ << "," << __LINE__ << "), with error code " << error;
    throw std::runtime_error(s.str());
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

int ribi::TriangleFile::GetTriangleInputNedges() const noexcept
{
  return m_polyfile ? m_polyfile->GetNedges() : 0;
}

int ribi::TriangleFile::GetTriangleInputNvertices() const noexcept
{
  return m_polyfile ? m_polyfile->GetNvertices() : 0;
}


const ribi::TriangleFile::Polygons& ribi::TriangleFile::GetShapes() const noexcept
{
  assert(m_polyfile);
  return m_polyfile->GetPolygons();
}


std::string ribi::TriangleFile::GetVersion() noexcept
{
  return "1.8";
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
    "2014-06-02: Version 1.6: split of sections to PolyFileFromPolygons",
    "2014-06-25: Version 1.7: use fixed notation instead of scientific, as Triangle converts it incorrectly it",
    "2014-06-26: Version 1.8: added GetNvertices and GetNedges"
  };
}

#ifndef NDEBUG
void ribi::TriangleFile::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);

  #ifdef FIX_ISSUE_231
  const bool verbose{false};
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
    const Polygons polygons = { v };
    const Linestrings linestrings = {};
    const Shapes shapes = std::make_pair(polygons,linestrings);
    try
    {
      TriangleFile f(shapes);
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
      std::stringstream s;
      s
        << "TriangleFile::Test: "
        << "Triangle.exe failed: " << e.what()
      ;
      TRACE(s.str());
      std::exit(0); //TEMP for profiling
      assert(!"Should not get here");
    }
  }
  #endif // FIX_ISSUE_231

}
#endif

std::string ribi::TriangleFile::ToStr() const noexcept
{
  std::stringstream s;
  s << (*this);
  return s.str();
  //assert(m_polyfile);
  //return m_polyfile->ToStr();
}

std::ostream& ribi::operator<<(std::ostream& os, const TriangleFile& f) noexcept
{
  assert(f.m_polyfile);
  os << (*f.m_polyfile);
  return os;
}
