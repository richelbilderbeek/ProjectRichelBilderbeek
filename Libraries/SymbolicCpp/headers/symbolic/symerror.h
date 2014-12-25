/*
    SymbolicC++ : An object oriented computer algebra system written in C++

    Copyright (C) 2008 Yorick Hardy and Willi-Hans Steeb

    This library is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


// symerror.h

#ifndef SYMBOLIC_CPLUSPLUS_ERRORS

#include <string>

#ifdef  SYMBOLIC_FORWARD
#ifndef SYMBOLIC_CPLUSPLUS_ERRORS_FORWARD
#define SYMBOLIC_CPLUSPLUS_ERRORS_FORWARD

class SymbolicError;

#endif
#endif

#ifdef  SYMBOLIC_DECLARE
#ifndef SYMBOLIC_CPLUSPLUS_ERRORS_DECLARE
#define SYMBOLIC_CPLUSPLUS_ERRORS_DECLARE

class SymbolicError
{
 public: typedef enum {
                       IncompatibleNumeric,
                       IncompatibleVector,
                       NoMatch,
                       NotDouble,
                       NotInt,
                       NotMatrix,
                       NotNumeric,
                       NotVector,
                       UnsupportedNumeric
                      } error;

         error errornumber;
         SymbolicError(const error &e);
         string message() const;
};

#endif
#endif

#define LIBSYMBOLICCPLUSPLUS

#ifdef  SYMBOLIC_DEFINE
#ifndef SYMBOLIC_CPLUSPLUS_ERRORS_DEFINE
#define SYMBOLIC_CPLUSPLUS_ERRORS_DEFINE

SymbolicError::SymbolicError(const error &e) : errornumber(e) {}

string SymbolicError::message() const
{
 switch(errornumber)
 {
   case IncompatibleNumeric:
        return "Tried to use two incompatible number together";
   case IncompatibleVector:
        return "Tried to use two incompatible types in a vector operation";
   case NoMatch:
        return "No match found";
   case NotDouble:
        return "The value is not of type double";
   case NotInt:
        return "The value is not of type int";
   case NotMatrix:
        return "The value is not a matrix";
   case NotNumeric:
        return "The value is not numeric";
   case NotVector:
        return "The value is not a vector";
   case UnsupportedNumeric:
        return "The data type is not supprted by Numeric";
   default:
        return "Unknown error";
 }
}

#endif
#endif

#undef LIBSYMBOLICCPLUSPLUS

#endif
