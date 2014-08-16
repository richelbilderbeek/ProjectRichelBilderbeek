#include <sstream>
#include <string>
#include <iomanip>
#include "ap.h"


using namespace std;


// The xxxxxxxx.ap filename function

const char *filename (int fno)
{
    static string f;
    ostringstream s;

    s << setw (8) << setfill ('0') << fno << ".ap";

    f = s.str();

    return f.c_str();
}
