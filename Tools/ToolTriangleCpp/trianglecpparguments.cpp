#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "trianglecpparguments.h"

#include <cassert>
#include <cstring>
#include <stdexcept>
#include <cmath>

#include <boost/limits.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/units/systems/angle/degrees.hpp>
#include "fileio.h"
#include "trianglecppinfo.h"
#include "trianglecppsyntax.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::tricpp::Arguments::Arguments(
  const std::vector<std::string>& args
)
  : m_areafilename{},
    m_conformdel{0},
    m_convex{0},
    m_do_check{false},
    m_do_refine{false},
    m_dwyer{1},
    m_edgefilename{},
    m_edgesout{0},
    //m_firstnumber{1},
    m_fixedarea{0},
    m_geomview{0},
    m_goodangle{0.0 * boost::units::si::radian},
    m_incremental{0},
    m_inelefilename{},
    m_innodefilename{},
    m_inpolyfilename{},
    m_do_jettison{false},
    m_maxarea{0.0 * boost::units::si::meter * boost::units::si::meter},
    m_minangle{
      20.0
      * (boost::math::constants::two_pi<double>() / 360.0) //degrees -> radian
      * boost::units::si::radian
    },
    m_neighborfilename{},
    m_neighbors{0},
    m_nobisect{0},
    m_nobound{0},
    m_noelewritten{0},
    m_noexact{false},
    m_noholes{0},
    m_noiterationnum{0},
    m_nonodewritten{0},
    m_nopolywritten{0},
    m_offconstant{0.0},
    m_offfilename{},
    //m_order{1},
    m_outelefilename{},
    m_outnodefilename{},
    m_outpolyfilename{},
    //m_poly{false},
    m_quality{true},
    m_quiet{0},
    m_regionattrib{0},
    m_splitseg{0},
    m_max_added_steiner_points{boost::numeric::bounds<int>::highest()},
    m_sweepline{0},
    m_usertest{0},
    //m_usesegments{0},
    m_vararea{false},
    m_vedgefilename{},
    m_verbosity{0},
    m_vnodefilename{},
    m_voronoi{0}
    //m_weighted{0}
{
  const int argc = static_cast<int>(args.size());
  //const int start_index = 1; //Because args[0] contains the filename
  //int increment;
  //int meshnumber;
  //static const int max_filename_size = 2048;
  //std::string workstring; //[max_filename_size];

  for (int i = 1; i != argc; ++i)
  {
    const std::string line = args[i];
    assert(!line.empty());
    if (line[0] == '-')
    {
      const std::string s = line.substr(1,line.size() - 1);
      if (s == "p")
      {
        TRACE("p is a useless flag, always set to on");
        continue;
      }
      if (s == "r")
      {
        m_do_refine = true;
      }
      if (s[0] == 'q')
      {
        const std::string t = line.substr(1,s.size() - 1);
        m_minangle = boost::lexical_cast<double>(t);
        /*
        m_quality = 1;
        if (((line[j + 1] >= '0') && (line[j + 1] <= '9')) ||
            (line[j + 1] == '.')) {
          int k = 0;
          while (((line[j + 1] >= '0') && (line[j + 1] <= '9')) ||
                 (line[j + 1] == '.')) {
            j++;
            workstring[k] = line[j];
            k++;
          }
          workstring[k] = '\0';
          this->m_minangle = boost::lexical_cast<double>(workstring);
        } else {
          this->m_minangle = 20.0;
        }
        */
      }
      if (s[0] == 'a')
      {
        const std::string t = s.substr(1,s.size());
        if (t.empty())
        {
          m_vararea = true;
        }
        else
        {
          using boost::units::si::meter;
          m_maxarea = Area(boost::lexical_cast<double>(t) * meter * meter);
          if (this->m_maxarea <= 0.0  * meter * meter)
          {
            throw std::logic_error("Triangle:  Maximum area must be greater than zero");
          }
        }
        /*
        this->m_quality = 1;
        if (((line[j + 1] >= '0') && (line[j + 1] <= '9')) ||
            (line[j + 1] == '.'))
        {
          this->m_fixedarea = 1;
          int k = 0;
          while (((line[j + 1] >= '0') && (line[j + 1] <= '9')) ||
                 (line[j + 1] == '.')) {
            j++;
            workstring[k] = line[j];
            k++;
          }
          workstring[k] = '\0';
          this->m_maxarea = boost::lexical_cast<double>(workstring);
          if (this->m_maxarea <= 0.0) {
            throw std::logic_error("Triangle:  Maximum area must be greater than zero.\n");
          }
        }
        else
        {
          this->m_vararea = true;
        }
        */
      }
      if (s[0] == 'u')
      {
        //m_quality = 1;
        m_usertest = 1;
      }
      if (s[0] == 'A')
      {
        m_regionattrib = 1;
      }
      if (s[0] == 'c')
      {
        m_convex = 1;
      }
      //if (line[j] == 'w') {
      //  this->m_weighted = 1;
      //}
      //if (line[j] == 'W') {
      //  this->m_weighted = 2;
      //}
      if (s[0] == 'j')
      {
        m_do_jettison = true;
      }
      //if (line[j] == 'z') {
      //  this->m_firstnumber = 0;
      //}
      if (s[0] == 'e')
      {
        m_edgesout = 1;
      }
      if (s[0] == 'v')
      {
        m_voronoi = 1;
      }
      if (s[0] == 'n')
      {
        m_neighbors = 1;
      }
      if (s[0] == 'g')
      {
        m_geomview = 1;
      }
      if (s[0] == 'B')
      {
        m_nobound = 1;
      }
      if (s[0] == 'P')
      {
        m_nopolywritten = 1;
      }
      if (s[0] == 'N')
      {
        m_nonodewritten = 1;
      }
      if (s[0] == 'E')
      {
        m_noelewritten = 1;
      }
      if (s[0] == 'I')
      {
        m_noiterationnum = 1;
      }
      if (s[0] == 'O')
      {
        m_noholes = 1;
      }
      if (s[0] == 'X')
      {
        m_noexact = 1;
      }
      /*
      RJCB: I don't use it
      if (s[0] == 'o')
      {
        const std::string t = s.substr(1,s.size());
        if (!t.empty() && t[0] == '2')
        //if (line[j + 1] == '2')
        {
          //j++;
          m_order = 2;
        }
      }
      */
      if (s[0] == 'Y')
      {
        m_nobisect++;
      }
      if (s[0] == 'S')
      {
        const std::string t = s.substr(1,s.size());
        m_max_added_steiner_points = boost::lexical_cast<int>(t);
        if (m_max_added_steiner_points < 0)
        {
          std::stringstream s;
          s << "Max added Steiner points cannot be " << m_max_added_steiner_points
            << ", use a positive value instead";
          TRACE(s.str());
          throw std::runtime_error(s.str());
        }
        /*
        m_steiner = 0;
        while ((line[j + 1] >= '0') && (line[j + 1] <= '9'))
        {
          j++;
          m_steiner = m_steiner * 10 + (int) (s[0] - '0');
        }
        */
      }
      if (s[0] == 'i')
      {
        m_incremental = 1;
      }
      if (s[0] == 'F')
      {
        m_sweepline = 1;
      }
      if (s[0] == 'l')
      {
        m_dwyer = 0;
      }
      if (s[0] == 's')
      {
        m_splitseg = 1;
      }
      if ((s[0] == 'D') || (s[0] == 'L'))
      {
        //m_quality = 1;
        m_conformdel = 1;
      }
      if (s[0] == 'C')
      {
        m_do_check = true;
      }
      if (s[0] == 'Q')
      {
        m_quiet = 1;
      }
      if (s[0] == 'V')
      {
        ++m_verbosity;
      }
      if (s[0] == 'h' || s[0] == 'H' || s[0] == '?')
      {
        info();
      }
    }
    else
    {
      assert(i < argc); //RJCB
      m_innodefilename = line;
      //m_innodefilename[max_filename_size - 1] = '\0';
    }
  }
  if (m_innodefilename.empty())
  //if (m_innodefilename[0] == '\0')
  {
    Syntax();
  }
  if (ribi::fileio::FileIo().GetExtensionNoDot(m_innodefilename) == "node"
    //!strcmp(&this->m_innodefilename[strlen(this->m_innodefilename) - 5], ".node")
  )
  {
    m_innodefilename = ribi::fileio::FileIo().GetFileBasename(m_innodefilename);
    //this->m_innodefilename[strlen(this->m_innodefilename) - 5] = '\0';
  }
  if (ribi::fileio::FileIo().GetExtensionNoDot(m_innodefilename) == "poly"
    //!strcmp(&this->m_innodefilename[strlen(this->m_innodefilename) - 5], ".poly")
  )
  {
    m_innodefilename = ribi::fileio::FileIo().GetFileBasename(m_innodefilename);
    //this->m_innodefilename[strlen(this->m_innodefilename) - 5] = '\0';
  }
  if (ribi::fileio::FileIo().GetExtensionNoDot(m_innodefilename) == "ele"
    //!strcmp(&this->m_innodefilename[strlen(this->m_innodefilename) - 4], ".ele")
  )
  {
    m_innodefilename = ribi::fileio::FileIo().GetFileBasename(m_innodefilename);
    //this->m_innodefilename[strlen(this->m_innodefilename) - 4] = '\0';
    this->m_do_refine = true;
  }
  if (
    ribi::fileio::FileIo().GetExtensionNoDot(m_innodefilename) == "area"
    //!strcmp(&this->m_innodefilename[strlen(this->m_innodefilename) - 5], ".area")
  )
  {
    m_innodefilename = ribi::fileio::FileIo().GetFileBasename(m_innodefilename);
    //this->m_innodefilename[strlen(this->m_innodefilename) - 5] = '\0';
    //this->m_do_refine = true;
    this->m_quality = 1;
    this->m_vararea = 1;
  }
  //static_assert(this->m_usesegments,"");
  //this->m_usesegments = this->m_poly || this->m_do_refine || this->m_quality || this->m_convex;

  const Angle temp_angle = std::cos(m_minangle.value()) * radians;
  //m_goodangle = std::cos(m_minangle.value()) * radians; //Hmmm, why is this?
  //this->m_goodangle = cos(this->m_minangle * boost::math::constants::pi<double>() / 180.0);

  if (temp_angle == 1.0 * radians) //?Why?
  {
    m_offconstant = 0.0;
  }
  else
  {
    m_offconstant = 0.475 * std::sqrt((1.0 + temp_angle.value()) / (1.0 - temp_angle.value()));
    //this->m_offconstant = 0.475 * sqrt((1.0 + this->m_goodangle) / (1.0 - this->m_goodangle));
  }

  m_goodangle = Angle(std::cos(m_minangle.value()) * std::cos(m_minangle.value()) * radians);
  //this->m_goodangle *= this->m_goodangle;

  if (m_do_refine && m_noiterationnum)
  {
    throw std::logic_error("Triangle: You cannot use the -I switch when refining a triangulation.\n");
  }
  /* Be careful not to allocate space for element area constraints that */
  /*   will never be assigned any value (other than the default -1.0).  */

  /* Be careful not to add an extra attribute to each element unless the */
  /*   input supports it (PSLG in, but not refining a preexisting mesh). */
  if (m_do_refine)
  {
    this->m_regionattrib = 0;
  }
  /* Regular/weighted triangulations are incompatible with PSLGs */
  /*   and meshing.                                              */

  //if (this->m_weighted)
  {
    //this->m_weighted = 0;
    //if (!this->m_quiet) {
    //  printf("Warning:  weighted triangulations (-w, -W) are incompatible\n");
    //  printf("  with PSLGs (-p) and meshing (-q, -a, -u).  Weights ignored.\n"
    //         );
    //}
  }
  if (m_do_jettison && m_nonodewritten && !m_quiet)
  {
    std::cout
      << "Warning:  -j and -N switches are somewhat incompatible."
      << "If any vertices are jettisoned, you will need the output"
      << " .node file to reconstruct the new node indices."
    ;
  }

  m_inpolyfilename = m_innodefilename;
  m_inelefilename = m_innodefilename;
  m_areafilename = m_innodefilename;

  /*
  increment = 0;
  workstring = m_innodefilename;
  int j = 1;
  while (workstring[j] != '\0') {
    if ((workstring[j] == '.') && (workstring[j + 1] != '\0')) {
      increment = j + 1;
    }
    j++;
  }
  meshnumber = 0;
  if (increment > 0)
  {
    j = increment;
    do
    {
      if ((workstring[j] >= '0') && (workstring[j] <= '9'))
      {
        meshnumber = meshnumber * 10 + (int) (workstring[j] - '0');
      } else {
        increment = 0;
      }
      j++;
    } while (workstring[j] != '\0');
  }
  if (this->m_noiterationnum)
  {
    m_outnodefilename = m_innodefilename + ".node";
    m_outelefilename = m_innodefilename + ".ele";
    m_edgefilename = m_innodefilename + ".edge";
    m_vnodefilename = m_innodefilename + ".v.node";
    m_vedgefilename = m_innodefilename + ".v.edge";
    m_neighborfilename = m_innodefilename + ".neigh";
    m_offfilename = m_innodefilename + ".off";
  }
  else if (increment == 0)
  */
  {
    m_outnodefilename = m_innodefilename + ".1.node";
    m_outpolyfilename = m_innodefilename + ".1.poly";
    m_outelefilename = m_innodefilename + ".1.ele";
    m_edgefilename = m_innodefilename + ".1.edge";
    m_vnodefilename = m_innodefilename + ".1.v.node";
    m_vedgefilename = m_innodefilename + ".1.v.edge";
    m_neighborfilename = m_innodefilename + ".1.neigh";
    m_offfilename = m_innodefilename + ".1.off";
  }
  /*
  else
  {
    const std::string s = boost::lexical_cast<std::string>(meshnumber + 1);
    m_outnodefilename = m_innodefilename + "." + s + ".node";
    m_outpolyfilename = m_innodefilename + "." + s + ".poly";
    m_outelefilename = m_innodefilename + "." + s + ".ele";
    m_edgefilename = m_innodefilename + "." + s + ".edge";
    m_vnodefilename = m_innodefilename + "." + s + ".v.node";
    m_vedgefilename = m_innodefilename + "." + s + ".v.edge";
    m_neighborfilename = m_innodefilename + "." + s + ".neigh";
    m_offfilename = m_innodefilename + "." + s + ".off";
  }
  */
  m_innodefilename += ".node";
  m_inpolyfilename += ".poly";
  m_inelefilename += ".ele";
  m_areafilename += ".area";

  assert(m_do_refine == true);  //Which one is it?
  assert(m_do_refine == false); //Which one is it?
}
