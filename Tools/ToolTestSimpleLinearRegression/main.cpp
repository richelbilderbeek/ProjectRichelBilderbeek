#include <algorithm>
#include <cassert>
#include <iostream>

#include "tooltestsimplelinearregressionmaindialog.h"
#include "canvas.h"

int main()
{
  for (int i=1; i!=5; ++i) //Human-based counting, following the Ansombe's Quartet indices
  {
    const std::vector<double> xs
      = ToolTestSimpleLinearRegressionMainDialog::GetAnscombesQuartetX(i);
    const std::vector<double> ys
      = ToolTestSimpleLinearRegressionMainDialog::GetAnscombesQuartetY(i);

    const std::pair<double,double> p
      = ToolTestSimpleLinearRegressionMainDialog::CalculateSimpleLinearRegression(xs,ys);

    const double expected_regression_line_a = 0.500; //to 3 decimal places
    const double expected_regression_line_b = 3.00;  //to 2 decimal places

    const double e = 0.01;
    assert(expected_regression_line_a - e < p.first  && expected_regression_line_a + e > p.first);
    assert(expected_regression_line_b - e < p.second && expected_regression_line_b + e > p.second);

    //Plot the values
    const int max_x = 78;
    const int max_y = 20;
    Canvas c(max_x,max_y,Canvas::ColorSystem::invert,Canvas::CoordinatSystem::graph);
    c.DrawLine(0.0,0.0,max_x,0.0);
    c.DrawLine(0.0,0.0,0.0,max_y);
    assert(xs.size() == ys.size());
    const double ray = 1.0;
    const double max_x_co = ray + *std::max_element(xs.begin(),xs.end());
    const double stretch_x = static_cast<double>(max_x) / max_x_co;
    const double max_y_co = ray + *std::max_element(ys.begin(),ys.end());
    const double stretch_y = static_cast<double>(max_y) / max_y_co;

    const std::size_t n_values = xs.size();
    for (std::size_t i=0; i!=n_values; ++i)
    {
      //c.DrawDot(xs[i] * stretch_x,ys[i] * stretch_y);
      c.DrawCircle(xs[i] * stretch_x,ys[i] * stretch_y,ray);
    }
    c.DrawLine(
      stretch_x * 0.0,
      stretch_y * p.second,
      stretch_x * static_cast<double>(max_x),
      stretch_y * (p.second + static_cast<double>(max_x) * p.first)
    );
    std::cout << c << std::endl;
  }
}

/* Screen output

TRACE '"Starting ToolTestSimpleLinearRegressionMainDialog::Test"' line 155 in fi
le '../ToolTestSimpleLinearRegression/tooltestsimplelinearregressionmaindialog.c
pp': 'Starting ToolTestSimpleLinearRegressionMainDialog::Test'
TRACE '"Finished ToolTestSimpleLinearRegressionMainDialog::Test successfully"' l
ine 200 in file '../ToolTestSimpleLinearRegression/tooltestsimplelinearregressio
nmaindialog.cpp': 'Finished ToolTestSimpleLinearRegressionMainDialog::Test succe
ssfully'
.                                                            -o.
:                                                            s-+        `    `
:                                                            +o:       /hmooso
:                                             .               `  `-:+osmdm:`
:                                            :os`       .- .-:+os+/:.`  :-
:                                            :+s` `os:-+MMN+/-.`   .
:                             -/`        `    //:/hNNy//ho:       /oo
:                            `o/:       +hd/oso+:--o+`  `.        +:s
:                            `oo- `.:/osMhN-`                     `/.
:                       `oo.`-/ooso/:-` `+.
:                     `-smNdo/:.`  `/
:               .-/omdo//so`       s/+
:         .-/+so+/-o+s`            oo/
:  `.:/+so+:-.     -oo`             .
hoso+:-`            `
o`
:
:
:
s::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::.

`                                                  ``   `-    .     `.:/o+/-.`
-                                             -.  .++. `o/:  +o+-:+do:-`
-                                        .   :/o` .++. `oo+-/Mdd:.o/o   `
-                                       /+o  :+o`  -/-:/sy/-.-/`  //o  -++`
-                                  `:   /:o   ..-/+o+:-`           -   ::o`
-                                  o:/   /::/+o/:.`                     :-
-                             `.   oos:+o+/-.
-                            `sso/+os:-`
-                        `.-/sMds.`
-                   `-:/shy:.``-
-              .-/+o+:-`-+/.
-        `.:/+o/:.`     .++.
-   `-:+o+/-.       -`   ``
o/+o+:-`           :/o`
s.`                :+o`
-                   .`
-
-
-
o----------------------------------------------------------------------------`

.                                                                 -s/
:                                                                 +.o
:                                                                 .s:
:
:                                                                        `.-:/
:                                                                 `.-:+oho/:-.
:                                                          `.:o+os+/:-./+o`
:                                                  .-.:/dNy+/dyo       :/o`
:                                        .   -ys/+hMNo::y/:  s:+        :.
:                              .   -o-.-ymMoodyd:`-++-  +o.  `/
:                   `   `//` `syo:/MdN+/hoy  -o+   --
:                  -+o``/yhsoyMdy-.oo:   /`
:               `.-ydMy+odh:` .:    `
:        `.-/+oo+/::+-
: `.:/+oo+/:-.
do+/:.`
:
:
:
s::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::.

                                                                         .-``.
`                                                                     ``-/:-``
`                                                                ``.-..``..
`                                                           `..-..`
`                                                      `....``
`                              `                 ``....``
`                             //.           ``....`
`                            `hy/      `..-.``
`                            `dm+``..-.``
`                           `-MMy.``
`                      ``.-..-NN/
`                 `..-.``    `hy/
`           ``....``         `oo:
`      ``.-..`                `.
` `..-..`
:.``
`
`
`
-````````````````````````````````````````````````````````````````````````````

Press <RETURN> to close this window...

*/
