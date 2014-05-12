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
    conformdel{0},
    convex{0},
    docheck{0},
    dwyer{1},
    edgesout{0},
    firstnumber{1},
    fixedarea{0},
    geomview{0},
    goodangle{0.0},
    incremental{0},
    innodefilename{},
    jettison{0},
    maxarea{-1.0},
    minangle{0.0},
    neighbors{0},
    nobisect{0},
    nobound{0},
    noelewritten{0},
    noexact{0},
    noholes{0},
    noiterationnum{0},
    nonodewritten{0},
    nopolywritten{0},
    offconstant{0.0},
    order{1},
    poly{0},
    quality{0},
    quiet{0},
    refine{0},
    regionattrib{0},
    splitseg{0},
    steiner{-1},
    sweepline{0},
    usertest{0},
    usesegments{0},
    vararea{0},
    verbose{0},
    voronoi{0},
    weighted{0}
{
  const int argc = static_cast<int>(args.size());
  const int start_index = 1; //Because args[0] contains the filename
  int increment;
  int meshnumber;
  char workstring[max_filename_size];

  for (int i = start_index; i < argc; i++) {
    if (args[i][0] == '-') {
      for (int j = start_index; args[i][j] != '\0'; j++) {
        if (args[i][j] == 'p') {
          this->poly = 1;
        }
        if (args[i][j] == 'r') {
          this->refine = 1;
        }
        if (args[i][j] == 'q') {
          this->quality = 1;
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
            this->minangle = (double) strtod(workstring, (char **) NULL);
          } else {
            this->minangle = 20.0;
          }
        }
        if (args[i][j] == 'a') {
          this->quality = 1;
          if (((args[i][j + 1] >= '0') && (args[i][j + 1] <= '9')) ||
              (args[i][j + 1] == '.')) {
            this->fixedarea = 1;
            int k = 0;
            while (((args[i][j + 1] >= '0') && (args[i][j + 1] <= '9')) ||
                   (args[i][j + 1] == '.')) {
              j++;
              workstring[k] = args[i][j];
              k++;
            }
            workstring[k] = '\0';
            this->maxarea = (double) strtod(workstring, (char **) NULL);
            if (this->maxarea <= 0.0) {
              throw std::logic_error("Triangle:  Maximum area must be greater than zero.\n");
            }
          } else {
            this->vararea = 1;
          }
        }
        if (args[i][j] == 'u') {
          this->quality = 1;
          this->usertest = 1;
        }
        if (args[i][j] == 'A') {
          this->regionattrib = 1;
        }
        if (args[i][j] == 'c') {
          this->convex = 1;
        }
        if (args[i][j] == 'w') {
          this->weighted = 1;
        }
        if (args[i][j] == 'W') {
          this->weighted = 2;
        }
        if (args[i][j] == 'j') {
          this->jettison = 1;
        }
        if (args[i][j] == 'z') {
          this->firstnumber = 0;
        }
        if (args[i][j] == 'e') {
          this->edgesout = 1;
        }
        if (args[i][j] == 'v') {
          this->voronoi = 1;
        }
        if (args[i][j] == 'n') {
          this->neighbors = 1;
        }
        if (args[i][j] == 'g') {
          this->geomview = 1;
        }
        if (args[i][j] == 'B') {
          this->nobound = 1;
        }
        if (args[i][j] == 'P') {
          this->nopolywritten = 1;
        }
        if (args[i][j] == 'N') {
          this->nonodewritten = 1;
        }
        if (args[i][j] == 'E') {
          this->noelewritten = 1;
        }
        if (args[i][j] == 'I') {
          this->noiterationnum = 1;
        }
        if (args[i][j] == 'O') {
          this->noholes = 1;
        }
        if (args[i][j] == 'X') {
          this->noexact = 1;
        }
        if (args[i][j] == 'o') {
          if (args[i][j + 1] == '2') {
            j++;
            this->order = 2;
          }
        }
        if (args[i][j] == 'Y') {
          this->nobisect++;
        }
        if (args[i][j] == 'S') {
          this->steiner = 0;
          while ((args[i][j + 1] >= '0') && (args[i][j + 1] <= '9')) {
            j++;
            this->steiner = this->steiner * 10 + (int) (args[i][j] - '0');
          }
        }
        if (args[i][j] == 'i') {
          this->incremental = 1;
        }
        if (args[i][j] == 'F') {
          this->sweepline = 1;
        }
        if (args[i][j] == 'l') {
          this->dwyer = 0;
        }
        if (args[i][j] == 's') {
          this->splitseg = 1;
        }
        if ((args[i][j] == 'D') || (args[i][j] == 'L')) {
          this->quality = 1;
          this->conformdel = 1;
        }
        if (args[i][j] == 'C') {
          this->docheck = 1;
        }
        if (args[i][j] == 'Q') {
          this->quiet = 1;
        }
        if (args[i][j] == 'V') {
          this->verbose++;
        }
        if ((args[i][j] == 'h') || (args[i][j] == 'H') ||
            (args[i][j] == '?')) {
          info();
        }
      }
    } else {
      assert(i < argc); //RJCB
      strncpy(this->innodefilename, args[i].c_str(), max_filename_size - 1);
      this->innodefilename[max_filename_size - 1] = '\0';
    }
  }
  if (this->innodefilename[0] == '\0') {
    syntax();
  }
  if (!strcmp(&this->innodefilename[strlen(this->innodefilename) - 5], ".node")) {
    this->innodefilename[strlen(this->innodefilename) - 5] = '\0';
  }
  if (!strcmp(&this->innodefilename[strlen(this->innodefilename) - 5], ".poly")) {
    this->innodefilename[strlen(this->innodefilename) - 5] = '\0';
    this->poly = 1;
  }
  if (!strcmp(&this->innodefilename[strlen(this->innodefilename) - 4], ".ele")) {
    this->innodefilename[strlen(this->innodefilename) - 4] = '\0';
    this->refine = 1;
  }
  if (!strcmp(&this->innodefilename[strlen(this->innodefilename) - 5], ".area")) {
    this->innodefilename[strlen(this->innodefilename) - 5] = '\0';
    this->refine = 1;
    this->quality = 1;
    this->vararea = 1;
  }
  this->usesegments = this->poly || this->refine || this->quality || this->convex;
  this->goodangle = cos(this->minangle * boost::math::constants::pi<double>() / 180.0);
  if (this->goodangle == 1.0) {
    this->offconstant = 0.0;
  } else {
    this->offconstant = 0.475 * sqrt((1.0 + this->goodangle) / (1.0 - this->goodangle));
  }
  this->goodangle *= this->goodangle;
  if (this->refine && this->noiterationnum) {
    throw std::logic_error("Triangle: You cannot use the -I switch when refining a triangulation.\n");
  }
  /* Be careful not to allocate space for element area constraints that */
  /*   will never be assigned any value (other than the default -1.0).  */
  if (!this->refine && !this->poly) {
    this->vararea = 0;
  }
  /* Be careful not to add an extra attribute to each element unless the */
  /*   input supports it (PSLG in, but not refining a preexisting mesh). */
  if (this->refine || !this->poly) {
    this->regionattrib = 0;
  }
  /* Regular/weighted triangulations are incompatible with PSLGs */
  /*   and meshing.                                              */
  if (this->weighted && (this->poly || this->quality)) {
    this->weighted = 0;
    if (!this->quiet) {
      printf("Warning:  weighted triangulations (-w, -W) are incompatible\n");
      printf("  with PSLGs (-p) and meshing (-q, -a, -u).  Weights ignored.\n"
             );
    }
  }
  if (this->jettison && this->nonodewritten && !this->quiet) {
    printf("Warning:  -j and -N switches are somewhat incompatible.\n");
    printf("  If any vertices are jettisoned, you will need the output\n");
    printf("  .node file to reconstruct the new node indices.");
  }

  strcpy(this->inpolyfilename, this->innodefilename);
  strcpy(this->inelefilename, this->innodefilename);
  strcpy(this->areafilename, this->innodefilename);
  increment = 0;
  strcpy(workstring, this->innodefilename);
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
  if (this->noiterationnum) {
    strcpy(this->outnodefilename, this->innodefilename);
    strcpy(this->outelefilename, this->innodefilename);
    strcpy(this->edgefilename, this->innodefilename);
    strcpy(this->vnodefilename, this->innodefilename);
    strcpy(this->vedgefilename, this->innodefilename);
    strcpy(this->neighborfilename, this->innodefilename);
    strcpy(this->offfilename, this->innodefilename);
    strcat(this->outnodefilename, ".node");
    strcat(this->outelefilename, ".ele");
    strcat(this->edgefilename, ".edge");
    strcat(this->vnodefilename, ".v.node");
    strcat(this->vedgefilename, ".v.edge");
    strcat(this->neighborfilename, ".neigh");
    strcat(this->offfilename, ".off");
  }
  else if (increment == 0)
  {
    strcpy(this->outnodefilename, this->innodefilename);
    strcpy(this->outpolyfilename, this->innodefilename);
    strcpy(this->outelefilename, this->innodefilename);
    strcpy(this->edgefilename, this->innodefilename);
    strcpy(this->vnodefilename, this->innodefilename);
    strcpy(this->vedgefilename, this->innodefilename);
    strcpy(this->neighborfilename, this->innodefilename);
    strcpy(this->offfilename, this->innodefilename);
    strcat(this->outnodefilename, ".1.node");
    strcat(this->outpolyfilename, ".1.poly");
    strcat(this->outelefilename, ".1.ele");
    strcat(this->edgefilename, ".1.edge");
    strcat(this->vnodefilename, ".1.v.node");
    strcat(this->vedgefilename, ".1.v.edge");
    strcat(this->neighborfilename, ".1.neigh");
    strcat(this->offfilename, ".1.off");
  } else {
    workstring[increment] = '%';
    workstring[increment + 1] = 'd';
    workstring[increment + 2] = '\0';
    sprintf(this->outnodefilename, workstring, meshnumber + 1);
    strcpy(this->outpolyfilename, this->outnodefilename);
    strcpy(this->outelefilename, this->outnodefilename);
    strcpy(this->edgefilename, this->outnodefilename);
    strcpy(this->vnodefilename, this->outnodefilename);
    strcpy(this->vedgefilename, this->outnodefilename);
    strcpy(this->neighborfilename, this->outnodefilename);
    strcpy(this->offfilename, this->outnodefilename);
    strcat(this->outnodefilename, ".node");
    strcat(this->outpolyfilename, ".poly");
    strcat(this->outelefilename, ".ele");
    strcat(this->edgefilename, ".edge");
    strcat(this->vnodefilename, ".v.node");
    strcat(this->vedgefilename, ".v.edge");
    strcat(this->neighborfilename, ".neigh");
    strcat(this->offfilename, ".off");
  }
  strcat(this->innodefilename, ".node");
  strcat(this->inpolyfilename, ".poly");
  strcat(this->inelefilename, ".ele");
  strcat(this->areafilename, ".area");
}
