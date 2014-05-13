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

#include "trianglecppinfo.h"
#include "trianglecppsyntax.h"

#pragma GCC diagnostic pop

tricpp::Behavior::Behavior(
  const std::vector<std::string>& args
)
  :
    m_conformdel{0},
    m_convex{0},
    m_do_check{false},
    m_do_refine{false},
    m_dwyer{1},
    m_edgesout{0},
    m_firstnumber{1},
    m_fixedarea{0},
    m_geomview{0},
    m_goodangle{0.0},
    m_incremental{0},
    m_innodefilename{},
    m_jettison{0},
    m_maxarea{-1.0},
    m_minangle{0.0},
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
    m_order{1},
    //m_poly{false},
    m_quality{0},
    m_quiet{0},
    m_regionattrib{0},
    m_splitseg{0},
    m_steiner{-1},
    m_sweepline{0},
    m_usertest{0},
    m_usesegments{0},
    m_vararea{0},
    m_verbosity{0},
    m_voronoi{0},
    m_weighted{0}
{
  const int argc = static_cast<int>(args.size());
  const int start_index = 1; //Because args[0] contains the filename
  int increment;
  int meshnumber;
  char workstring[max_filename_size];

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
            this->m_minangle = (double) strtod(workstring, (char **) NULL);
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
            this->m_maxarea = (double) strtod(workstring, (char **) NULL);
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
        if (args[i][j] == 'w') {
          this->m_weighted = 1;
        }
        if (args[i][j] == 'W') {
          this->m_weighted = 2;
        }
        if (args[i][j] == 'j') {
          this->m_jettison = 1;
        }
        if (args[i][j] == 'z') {
          this->m_firstnumber = 0;
        }
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
      strncpy(this->m_innodefilename, args[i].c_str(), max_filename_size - 1);
      this->m_innodefilename[max_filename_size - 1] = '\0';
    }
  }
  if (this->m_innodefilename[0] == '\0') {
    Syntax();
  }
  if (!strcmp(&this->m_innodefilename[strlen(this->m_innodefilename) - 5], ".node")) {
    this->m_innodefilename[strlen(this->m_innodefilename) - 5] = '\0';
  }
  if (!strcmp(&this->m_innodefilename[strlen(this->m_innodefilename) - 5], ".poly")) {
    this->m_innodefilename[strlen(this->m_innodefilename) - 5] = '\0';
    static_assert(m_poly == true,"");
    //this->m_poly = true;
  }
  if (!strcmp(&this->m_innodefilename[strlen(this->m_innodefilename) - 4], ".ele")) {
    this->m_innodefilename[strlen(this->m_innodefilename) - 4] = '\0';
    this->m_do_refine = 1;
  }
  if (!strcmp(&this->m_innodefilename[strlen(this->m_innodefilename) - 5], ".area")) {
    this->m_innodefilename[strlen(this->m_innodefilename) - 5] = '\0';
    this->m_do_refine = 1;
    this->m_quality = 1;
    this->m_vararea = 1;
  }
  this->m_usesegments = this->m_poly || this->m_do_refine || this->m_quality || this->m_convex;
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
  if (!this->m_do_refine && !this->m_poly) {
    this->m_vararea = 0;
  }
  /* Be careful not to add an extra attribute to each element unless the */
  /*   input supports it (PSLG in, but not refining a preexisting mesh). */
  if (this->m_do_refine || !this->m_poly) {
    this->m_regionattrib = 0;
  }
  /* Regular/weighted triangulations are incompatible with PSLGs */
  /*   and meshing.                                              */
  if (this->m_weighted && (this->m_poly || this->m_quality)) {
    this->m_weighted = 0;
    if (!this->m_quiet) {
      printf("Warning:  weighted triangulations (-w, -W) are incompatible\n");
      printf("  with PSLGs (-p) and meshing (-q, -a, -u).  Weights ignored.\n"
             );
    }
  }
  if (this->m_jettison && this->m_nonodewritten && !this->m_quiet) {
    printf("Warning:  -j and -N switches are somewhat incompatible.\n");
    printf("  If any vertices are jettisoned, you will need the output\n");
    printf("  .node file to reconstruct the new node indices.");
  }

  strcpy(this->m_inpolyfilename, this->m_innodefilename);
  strcpy(this->m_inelefilename, this->m_innodefilename);
  strcpy(this->m_areafilename, this->m_innodefilename);
  increment = 0;
  strcpy(workstring, this->m_innodefilename);
  int j = 1;
  while (workstring[j] != '\0') {
    if ((workstring[j] == '.') && (workstring[j + 1] != '\0')) {
      increment = j + 1;
    }
    j++;
  }
  meshnumber = 0;
  if (increment > 0) {
    j = increment;
    do {
      if ((workstring[j] >= '0') && (workstring[j] <= '9')) {
        meshnumber = meshnumber * 10 + (int) (workstring[j] - '0');
      } else {
        increment = 0;
      }
      j++;
    } while (workstring[j] != '\0');
  }
  if (this->m_noiterationnum) {
    strcpy(this->m_outnodefilename, this->m_innodefilename);
    strcpy(this->m_outelefilename, this->m_innodefilename);
    strcpy(this->m_edgefilename, this->m_innodefilename);
    strcpy(this->m_vnodefilename, this->m_innodefilename);
    strcpy(this->m_vedgefilename, this->m_innodefilename);
    strcpy(this->m_neighborfilename, this->m_innodefilename);
    strcpy(this->m_offfilename, this->m_innodefilename);
    strcat(this->m_outnodefilename, ".node");
    strcat(this->m_outelefilename, ".ele");
    strcat(this->m_edgefilename, ".edge");
    strcat(this->m_vnodefilename, ".v.node");
    strcat(this->m_vedgefilename, ".v.edge");
    strcat(this->m_neighborfilename, ".neigh");
    strcat(this->m_offfilename, ".off");
  }
  else if (increment == 0)
  {
    strcpy(this->m_outnodefilename, this->m_innodefilename);
    strcpy(this->m_outpolyfilename, this->m_innodefilename);
    strcpy(this->m_outelefilename, this->m_innodefilename);
    strcpy(this->m_edgefilename, this->m_innodefilename);
    strcpy(this->m_vnodefilename, this->m_innodefilename);
    strcpy(this->m_vedgefilename, this->m_innodefilename);
    strcpy(this->m_neighborfilename, this->m_innodefilename);
    strcpy(this->m_offfilename, this->m_innodefilename);
    strcat(this->m_outnodefilename, ".1.node");
    strcat(this->m_outpolyfilename, ".1.poly");
    strcat(this->m_outelefilename, ".1.ele");
    strcat(this->m_edgefilename, ".1.edge");
    strcat(this->m_vnodefilename, ".1.v.node");
    strcat(this->m_vedgefilename, ".1.v.edge");
    strcat(this->m_neighborfilename, ".1.neigh");
    strcat(this->m_offfilename, ".1.off");
  } else {
    workstring[increment] = '%';
    workstring[increment + 1] = 'd';
    workstring[increment + 2] = '\0';
    sprintf(this->m_outnodefilename, workstring, meshnumber + 1);
    strcpy(this->m_outpolyfilename, this->m_outnodefilename);
    strcpy(this->m_outelefilename, this->m_outnodefilename);
    strcpy(this->m_edgefilename, this->m_outnodefilename);
    strcpy(this->m_vnodefilename, this->m_outnodefilename);
    strcpy(this->m_vedgefilename, this->m_outnodefilename);
    strcpy(this->m_neighborfilename, this->m_outnodefilename);
    strcpy(this->m_offfilename, this->m_outnodefilename);
    strcat(this->m_outnodefilename, ".node");
    strcat(this->m_outpolyfilename, ".poly");
    strcat(this->m_outelefilename, ".ele");
    strcat(this->m_edgefilename, ".edge");
    strcat(this->m_vnodefilename, ".v.node");
    strcat(this->m_vedgefilename, ".v.edge");
    strcat(this->m_neighborfilename, ".neigh");
    strcat(this->m_offfilename, ".off");
  }
  strcat(this->m_innodefilename, ".node");
  strcat(this->m_inpolyfilename, ".poly");
  strcat(this->m_inelefilename, ".ele");
  strcat(this->m_areafilename, ".area");
}
