#ifndef TRIANGLECPPFILE_H
#define TRIANGLECPPFILE_H

struct _iobuf;

namespace ribi {
namespace tricpp {

/*****************************************************************************/
/*                                                                           */
/*  readline()   Read a nonempty line from a file.                           */
/*                                                                           */
/*  A line is considered "nonempty" if it contains something that looks like */
/*  a number.  Comments (prefaced by `#') are ignored.                       */
/*                                                                           */
/*****************************************************************************/
char * readline(char * const string, _iobuf * const infile);

} //~namespace tricpp
} //~namespace ribi

#endif // TRIANGLECPPFILE_H
