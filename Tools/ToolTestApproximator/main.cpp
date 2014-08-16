#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "testapproximatormenudialog.h"
#pragma GCC diagnostic pop

int main(int argc, char * argv[])
{
  const std::vector<std::string> args { ribi::MenuDialog::ConvertArguments(argc,argv) };
  return ribi::ToolTestApproximatorMenuDialog().Execute(args);
}

/* Screen output

-
o
o
o
o                            oo                  oo
o                           -dd-                -do
o                          -o--o-              -o-
o                         -o-  -o-            -o-
o                        -o-    -o-          -o-
o                       -o-      -o-        -o-
o                      -o-        -o-      -o-
o                     -o-          -o-    -o-
o                    -o-            -o-  -o-
o                   -o-              -o--o-
o                  od-                -dd-
o                  oo                  oo
o
o
o
Moooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo-

Press <RETURN> to close this window...

*/
