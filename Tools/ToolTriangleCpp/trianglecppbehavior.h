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

  char m_areafilename[max_filename_size];
  int m_conformdel;
  int m_convex;
  bool m_do_check;
  bool m_do_refine;
  int m_dwyer;
  char m_edgefilename[max_filename_size];
  int m_edgesout;
  int m_firstnumber;
  int m_fixedarea;
  int m_geomview;
  double m_goodangle;
  int m_incremental;
  char m_inelefilename[max_filename_size];
  char m_innodefilename[max_filename_size];
  char m_inpolyfilename[max_filename_size];
  int m_jettison;
  double m_maxarea;
  double m_minangle;
  char m_neighborfilename[max_filename_size];
  int m_neighbors;
  int m_nobisect;
  int m_nobound;
  int m_noelewritten;
  int m_noexact;
  int m_noholes;
  int m_noiterationnum;
  int m_nonodewritten;
  int m_nopolywritten;
  double m_offconstant;
  char m_offfilename[max_filename_size];
  int m_order;
  char m_outelefilename[max_filename_size];
  char m_outnodefilename[max_filename_size];
  char m_outpolyfilename[max_filename_size];
  bool m_poly;
  int m_quality;
  int m_quiet;
  int m_regionattrib;
  int m_splitseg;
  int m_steiner;
  int m_sweepline;
  int m_usertest;
  int m_usesegments;
  int m_vararea;
  char m_vedgefilename[max_filename_size];
  int m_verbosity; ///0: no verbosity, 1: verbose, +1: more verbose
  char m_vnodefilename[max_filename_size];
  int m_voronoi;
  int m_weighted;
};

} //~namespace tricpp

#endif // TRIANGLECPPBEHAVIOR_H
