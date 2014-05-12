#ifndef TRIANGLECPPBEHAVIOR_H
#define TRIANGLECPPBEHAVIOR_H

#include <string>
#include <vector>

namespace tricpp {

/// Data structure for command line switches and file names.  This structure
///   is used (instead of global variables) to allow reentrancy.
///
/// Switches for the triangulator.
///   poly: -p switch.  refine: -r switch.
///   quality: -q switch.
///     minangle: minimum angle bound, specified after -q switch.
///     goodangle: cosine squared of minangle.
///     offconstant: constant used to place off-center Steiner points.
///   vararea: -a switch without number.
///   fixedarea: -a switch with number.
///     maxarea: maximum area bound, specified after -a switch.
///   usertest: -u switch.
///   regionattrib: -A switch.  convex: -c switch.
///   weighted: 1 for -w switch, 2 for -W switch.  jettison: -j switch
///   firstnumber: inverse of -z switch.  All items are numbered starting
///     from `firstnumber'.
///   edgesout: -e switch.  voronoi: -v switch.
///   neighbors: -n switch.  geomview: -g switch.
///   nobound: -B switch.  nopolywritten: -P switch.
///   nonodewritten: -N switch.  noelewritten: -E switch.
///   noiterationnum: -I switch.  noholes: -O switch.
///   noexact: -X switch.
///   order: element order, specified after -o switch.
///   nobisect: count of how often -Y switch is selected.
///   steiner: maximum number of Steiner points, specified after -S switch.
///   incremental: -i switch.  sweepline: -F switch.
///   dwyer: inverse of -l switch.
///   splitseg: -s switch.
///   conformdel: -D switch.  docheck: -C switch.
///   quiet: -Q switch.  verbose: count of how often -V switch is selected.
///   usesegments: -p, -r, -q, or -c switch; determines whether segments are
///     used at all.
///
/// Read the instructions to find out the meaning of these switches.
struct Behavior {
  /// Maximum number of characters in a file name (including the null).
  static const int max_filename_size = 2048;

  /// Read the command line, identify switches, and set
  /// up options and file names.
  Behavior(const std::vector<std::string>& args);

  char areafilename[max_filename_size];
  int conformdel;
  int convex;
  int docheck;
  int dwyer;
  char edgefilename[max_filename_size];
  int edgesout;
  int firstnumber;
  int fixedarea;
  int geomview;
  double goodangle;
  int incremental;
  char inelefilename[max_filename_size];
  char innodefilename[max_filename_size];
  char inpolyfilename[max_filename_size];
  int jettison;
  double maxarea;
  double minangle;
  char neighborfilename[max_filename_size];
  int neighbors;
  int nobisect;
  int nobound;
  int noelewritten;
  int noexact;
  int noholes;
  int noiterationnum;
  int nonodewritten;
  int nopolywritten;
  double offconstant;
  char offfilename[max_filename_size];
  int order;
  char outelefilename[max_filename_size];
  char outnodefilename[max_filename_size];
  char outpolyfilename[max_filename_size];
  int poly;
  int quality;
  int quiet;
  int refine;
  int regionattrib;
  int splitseg;
  int steiner;
  int sweepline;
  int usertest;
  int usesegments;
  int vararea;
  char vedgefilename[max_filename_size];
  int verbose;
  char vnodefilename[max_filename_size];
  int voronoi;
  int weighted;
};

} //~namespace tricpp

#endif // TRIANGLECPPBEHAVIOR_H
