//Code copied from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Chapter 1.1.3, Figure 1-3, page 28.

//radio.h
#ifndef INCLUDED_RADIO
#define INCLUDED_RADIO

int z;                              // illegal: external data definition
extern int LENGTH = 10;             // illegal: external data definition
const int WIDTH = 5;                // avoid: constant data definition
static int y;                       // avoid: static data definition
static void func() {/*...*/}        // avoid: static function definition

class Radio
{
    static int s_count;             // fine: static member declaration
    static const double S_PI;       // fine: static const member declaration
    int d_size;                     // fine: member data definition
    // ...
  public:
    int size() const;               // fine: member function declaration
    // ...
};                                  // fine: class definition

inline int Radio::size() const
{
    return d_size;
}                                   // fine: inline function definition

int Radio::s_count;                 // illegal: static member definition

double Radio::S_PI = 3.14159265358; // illegal: static const member definition

int Radio::size() const { /*...*/ } // illegal: member function definition

#endif // INCLUDED_RADIO
