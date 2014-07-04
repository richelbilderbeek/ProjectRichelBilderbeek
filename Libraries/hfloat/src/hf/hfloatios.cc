
#include <fxt/fxtio.h>

#include "hfloat.h"

#include "workspace.h"


std::istream &
operator >> (std::istream& is, hfloat &h)
{
//#warning "FYI: operator >> (istream& is, hfloat& h)   uses workspace"
    char *str;
    workspace::get_ws(str, workspace::nbytes());
    is >> str;
    st2hfloat(str, h);
    workspace::let_ws();

    return is;
}
//-------------------


std::ostream &
operator << (std::ostream& os, const hfloat &h)
{
    save_nn(os,"",h,0);
    return os;
}
//-------------------
