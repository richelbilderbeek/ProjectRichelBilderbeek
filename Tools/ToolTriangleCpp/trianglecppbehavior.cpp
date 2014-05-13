#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "trianglecppbehavior.h"

#include <cassert>
#include <cstring>
#include <stdexcept>
#include <cmath>

#include <boost/math/constants/constants.hpp>

#include "fileio.h"
#include "trianglecppinfo.h"
#include "trianglecppsyntax.h"

#pragma GCC diagnostic pop

ribi::tricpp::Behavior::Behavior(
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
    m_goodangle{0.0},
    m_incremental{0},
    m_inelefilename{},
    m_innodefilename{},
    m_inpolyfilename{},
    m_jettison{0},
    m_maxarea{-1.0},
    m_minangle{0.0},
    m_neighborfilename{},
    m_neighbors{0},
    m_nobisect{0},
    m_nobound{0},
    m_noelewritten{0},
    m_noexact{0},
    m_noholes{0},
    m_noiterationnum{0},
    m_nonodewritten{0},
    m_nopolywritten{0},
    m_offconstant{0.0},
    m_offfilename{},
    m_order{1},
    m_outelefilename{},
    m_outnodefilename{},
    m_outpolyfilename{},
    //m_poly{false},
    m_quality{0},
    m_quiet{0},
    m_regionattrib{0},
    m_splitseg{0},
    m_steiner{-1},
    m_sweepline{0},
    m_usertest{0},
    //m_usesegments{0},
    m_vararea{0},
    m_vedgefilename{},
    m_verbosity{0},
    m_vnodefilename{},
    m_voronoi{0}
    //m_weighted{0}
{
  const int argc = static_cast<int>(args.size());
  const int start_index = 1; //Because args[0] contains the filename
  int increment;
  int meshnumber;
  //static const int max_filename_size = 2048;
  std::string workstring; //[max_filename_size];

  for (int i = start_index; i < argc; i++)
  {
    if (args[i][0] == '-')
    {
      for (int j = start_index; args[i][j] != '\0'; j++)
      {
        if (args[i][j] == 'p')
        {
          static_assert(m_poly == true,"");
          //this->m_poly = true;
        }
        if (args[i][j] == 'r') {
          this->m_do_refine = 1;
        }
        if (args[i][j] == 'q') {
          this->m_quality = 1;
          if (((args[i][j + 1] >= '0') && (args[i][j + 1] <= '9')) ||
              (args[i][j + 1] == '.')) {
            int k = 0;
            while (((args[i][j + 1] >= '0') && (args[i][j + 1] <= '9')) ||
                   (args[i][j + 1] == '.')) {
              j++;
              workstring[k] = args[i][j];
              k++;
            }
            workstring[k] = '\0';
            this->m_minangle = boost::lexical_cast<double>(workstring);
          } else {
            this->m_minangle = 20.0;
          }
        }
        if (args[i][j] == 'a')
        {
          this->m_quality = 1;
          if (((args[i][j + 1] >= '0') && (args[i][j + 1] <= '9')) ||
              (args[i][j + 1] == '.')) {
            this->m_fixedarea = 1;
            int k = 0;
            while (((args[i][j + 1] >= '0') && (args[i][j + 1] <= '9')) ||
                   (args[i][j + 1] == '.')) {
              j++;
              workstring[k] = args[i][j];
              k++;
            }
            workstring[k] = '\0';
            this->m_maxarea = boost::lexical_cast<double>(workstring);
            if (this->m_maxarea <= 0.0) {
              throw std::logic_error("Triangle:  Maximum area must be greater than zero.\n");
            }
          } else {
            this->m_vararea = 1;
          }
        }
        if (args[i][j] == 'u') {
          this->m_quality = 1;
          this->m_usertest = 1;
        }
        if (args[i][j] == 'A') {
          this->m_regionattrib = 1;
        }
        if (args[i][j] == 'c') {
          this->m_convex = 1;
        }
        //if (args[i][j] == 'w') {
        //  this->m_weighted = 1;
        //}
        //if (args[i][j] == 'W') {
        //  this->m_weighted = 2;
        //}
        if (args[i][j] == 'j') {
          this->m_jettison = 1;
        }
        //if (args[i][j] == 'z') {
        //  this->m_firstnumber = 0;
        //}
        if (args[i][j] == 'e') {
          this->m_edgesout = 1;
        }
        if (args[i][j] == 'v') {
          this->m_voronoi = 1;
        }
        if (args[i][j] == 'n') {
          this->m_neighbors = 1;
        }
        if (args[i][j] == 'g') {
          this->m_geomview = 1;
        }
        if (args[i][j] == 'B') {
          this->m_nobound = 1;
        }
        if (args[i][j] == 'P') {
          this->m_nopolywritten = 1;
        }
        if (args[i][j] == 'N') {
          this->m_nonodewritten = 1;
        }
        if (args[i][j] == 'E') {
          this->m_noelewritten = 1;
        }
        if (args[i][j] == 'I') {
          this->m_noiterationnum = 1;
        }
        if (args[i][j] == 'O') {
          this->m_noholes = 1;
        }
        if (args[i][j] == 'X') {
          this->m_noexact = 1;
        }
        if (args[i][j] == 'o') {
          if (args[i][j + 1] == '2') {
            j++;
            this->m_order = 2;
          }
        }
        if (args[i][j] == 'Y') {
          this->m_nobisect++;
        }
        if (args[i][j] == 'S') {
          this->m_steiner = 0;
          while ((args[i][j + 1] >= '0') && (args[i][j + 1] <= '9')) {
            j++;
            this->m_steiner = this->m_steiner * 10 + (int) (args[i][j] - '0');
          }
        }
        if (args[i][j] == 'i') {
          this->m_incremental = 1;
        }
        if (args[i][j] == 'F') {
          this->m_sweepline = 1;
        }
        if (args[i][j] == 'l') {
          this->m_dwyer = 0;
        }
        if (args[i][j] == 's') {
          this->m_splitseg = 1;
        }
        if ((args[i][j] == 'D') || (args[i][j] == 'L')) {
          this->m_quality = 1;
          this->m_conformdel = 1;
        }
        if (args[i][j] == 'C') {
          this->m_do_check = true;
        }
        if (args[i][j] == 'Q') {
          this->m_quiet = 1;
        }
        if (args[i][j] == 'V') {
          ++m_verbosity;
        }
        if ((args[i][j] == 'h') || (args[i][j] == 'H') ||
            (args[i][j] == '?')) {
          info();
        }
      }
    } else {
      assert(i < argc); //RJCB
      m_innodefilename = args[i];
      //this->m_innodefilename[max_filename_size - 1] = '\0';
    }
  }
  if (this->m_innodefilename[0] == '\0')
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
    static_assert(m_poly == true,"");
    //this->m_poly = true;
  }
  if (ribi::fileio::FileIo().GetExtensionNoDot(m_innodefilename) == "ele"
    //!strcmp(&this->m_innodefilename[strlen(this->m_innodefilename) - 4], ".ele")
  )
  {
    m_innodefilename = ribi::fileio::FileIo().GetFileBasename(m_innodefilename);
    //this->m_innodefilename[strlen(this->m_innodefilename) - 4] = '\0';
    this->m_do_refine = 1;
  }
  if (
    ribi::fileio::FileIo().GetExtensionNoDot(m_innodefilename) == "area"
    //!strcmp(&this->m_innodefilename[strlen(this->m_innodefilename) - 5], ".area")
  )
  {
    m_innodefilename = ribi::fileio::FileIo().GetFileBasename(m_innodefilename);
    //this->m_innodefilename[strlen(this->m_innodefilename) - 5] = '\0';
    this->m_do_refine = 1;
    this->m_quality = 1;
    this->m_vararea = 1;
  }
  static_assert(this->m_poly,"");
  static_assert(this->m_poly || this->m_do_refine || this->m_quality || this->m_convex,"");
  static_assert(this->m_usesegments,"");
  //this->m_usesegments = this->m_poly || this->m_do_refine || this->m_quality || this->m_convex;

  this->m_goodangle = cos(this->m_minangle * boost::math::constants::pi<double>() / 180.0);
  if (this->m_goodangle == 1.0) {
    this->m_offconstant = 0.0;
  } else {
    this->m_offconstant = 0.475 * sqrt((1.0 + this->m_goodangle) / (1.0 - this->m_goodangle));
  }
  this->m_goodangle *= this->m_goodangle;
  if (this->m_do_refine && this->m_noiterationnum) {
    throw std::logic_error("Triangle: You cannot use the -I switch when refining a triangulation.\n");
  }
  /* Be careful not to allocate space for element area constraints that */
  /*   will never be assigned any value (other than the default -1.0).  */
  static_assert(this->m_poly,"");
  static_assert( (!this->m_do_refine && !this->m_poly) == false,"");
  if (!this->m_do_refine && !this->m_poly)
  {
    //this->m_vararea = 0;
  }

  /* Be careful not to add an extra attribute to each element unless the */
  /*   input supports it (PSLG in, but not refining a preexisting mesh). */
  if (this->m_do_refine || !this->m_poly) {
    this->m_regionattrib = 0;
  }
  /* Regular/weighted triangulations are incompatible with PSLGs */
  /*   and meshing.                                              */

  static_assert((this->m_weighted && (this->m_poly || this->m_quality)) == false,"");
  if (this->m_weighted && (this->m_poly || this->m_quality))
  {
    //this->m_weighted = 0;
    //if (!this->m_quiet) {
    //  printf("Warning:  weighted triangulations (-w, -W) are incompatible\n");
    //  printf("  with PSLGs (-p) and meshing (-q, -a, -u).  Weights ignored.\n"
    //         );
    //}
  }
  if (this->m_jettison && this->m_nonodewritten && !this->m_quiet) {
    printf("Warning:  -j and -N switches are somewhat incompatible.\n");
    printf("  If any vertices are jettisoned, you will need the output\n");
    printf("  .node file to reconstruct the new node indices.");
  }

  m_inpolyfilename = m_innodefilename;
  m_inelefilename = m_innodefilename;
  m_areafilename = m_innodefilename;

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
  m_innodefilename += ".node";
  m_inpolyfilename += ".poly";
  m_inelefilename += ".ele";
  m_areafilename += ".area";
}
