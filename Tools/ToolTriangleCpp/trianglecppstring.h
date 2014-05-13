#ifndef TRIANGLECPPSTRING_H
#define TRIANGLECPPSTRING_H

namespace ribi {
namespace tricpp {

/*****************************************************************************/
/*                                                                           */
/*  findfield()   Find the next field of a string.                           */
/*                                                                           */
/*  Jumps past the current field by searching for whitespace, then jumps     */
/*  past the whitespace to find the next field.                              */
/*                                                                           */
/*****************************************************************************/
char * FindField(char * const string);

} //~namespace tricpp
} //~namespace ribi

#endif // TRIANGLECPPSTRING_H
