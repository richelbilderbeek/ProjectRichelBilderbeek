#ifndef TRIANGLECPPSTRING_H
#define TRIANGLECPPSTRING_H

namespace tricpp {

/*****************************************************************************/
/*                                                                           */
/*  findfield()   Find the next field of a string.                           */
/*                                                                           */
/*  Jumps past the current field by searching for whitespace, then jumps     */
/*  past the whitespace to find the next field.                              */
/*                                                                           */
/*****************************************************************************/
char *findfield(char * const string);

} //~namespace tricpp

#endif // TRIANGLECPPSTRING_H
