#ifndef NDEBUG
#include "beaststatefile.h"

#include <cassert>
#include <sstream>

#include <QFile>

#include "fileio.h"


void BeastStateFile::Test() noexcept
{
  {
    static bool is_tested {false};
    if (is_tested) return;
    is_tested = true;
  }
  const ribi::fileio::FileIo fileio;
  const std::string birth_death{"birthdeath_birthdeath.xml.state"};
  const std::string coalecent{"coalescent_coalescent.xml.state"};
  const std::vector<std::string> resource_filenames
    =
    {
      birth_death,
      coalecent
    };
  //Create resources
  {

    for (const auto& s: resource_filenames)
    {
      //Delete previous version
      if (fileio.IsRegularFile(s))
      {
        std::remove(s.c_str());
        assert(!fileio.IsRegularFile(s));
      }
      if (!fileio.IsRegularFile(s))
      {
        QFile((std::string(":/files/") + s).c_str()).copy(s.c_str());
      }
      assert(fileio.IsRegularFile(s));
    }
  }
  {
    const BeastStateFile f(birth_death);
    const std::string tree_expected{"((((0:0.6806332581800597,(1:0.14146171723485418,6:0.14146171723485418)14:0.5391715409452056)11:0.22332014485665863,(2:0.01756816581268059,5:0.01756816581268059)10:0.8863852372240377)13:2.3462146599375355,(3:2.245410556417966,7:2.245410556417966)16:1.0047575065562877)17:5.369857849107417,((4:0.8273959320640695,9:0.8273959320640695)12:1.9329777335399343,8:2.760373665604004)15:5.859652246477667)18:0.0"};
    assert(f.GetTree() == tree_expected);
  }
  {
    const BeastStateFile f(coalecent);
    const std::string tree_expected{"((((0:1.9731487278617976,(2:0.02385862495086483,5:0.02385862495086483)12:1.9492901029109329)17:0.5602600580639896,(1:0.15558418773033483,6:0.15558418773033483)10:2.377824598195452)13:3.54396556997399,(3:0.8046576734483606,9:0.8046576734483606)16:5.272716682451416)11:6.921407992888125,((4:0.6362512899069979,8:0.6362512899069979)14:2.317725193372067,7:2.9539764832790647)15:10.044805865508838)18:0.0"};
    assert(f.GetTree() == tree_expected);
  }
}
#endif

/* Parameters used:

  const int dna_length{20};
  const double mutation_rate{0.1};
  const int n_generations{1};
  const int pop_size{10};
  const int seed{42};

*/

/* birthdeath_birthdeath.xml.state:

<itsabeastystatewerein version='2.0' sample='10000'>
<statenode id='Tree.t:birthdeath_birthdeath'>((((0:0.6806332581800597,(1:0.14146171723485418,6:0.14146171723485418)14:0.5391715409452056)11:0.22332014485665863,(2:0.01756816581268059,5:0.01756816581268059)10:0.8863852372240377)13:2.3462146599375355,(3:2.245410556417966,7:2.245410556417966)16:1.0047575065562877)17:5.369857849107417,((4:0.8273959320640695,9:0.8273959320640695)12:1.9329777335399343,8:2.760373665604004)15:5.859652246477667)18:0.0</statenode>
<statenode id='RBcount.s:birthdeath_birthdeath'>RBcount.s:birthdeath_birthdeath[1 1] (0,5): 0 </statenode>
<statenode id='RBrates.s:birthdeath_birthdeath'>RBrates.s:birthdeath_birthdeath[5 1] (0.01,100.0): 1.159671691142549 0.3424863379792815 0.19162007658050476 0.834973477181565 0.953933440001739 </statenode>
<statenode id='birthRate2.t:birthdeath_birthdeath'>birthRate2.t:birthdeath_birthdeath[1 1] (0.0,10000.0): 0.3336938635250574 </statenode>
<statenode id='relativeDeathRate2.t:birthdeath_birthdeath'>relativeDeathRate2.t:birthdeath_birthdeath[1 1] (0.0,1.0): 0.08450560553928697 </statenode>
</itsabeastystatewerein>
<!--
{operators:[
{id:"treeScaler.t:birthdeath_birthdeath", p:0.5, accept:157, reject:210, acceptFC:0, rejectFC:0, rejectIv:0, rejectOp:0},
{id:"treeRootScaler.t:birthdeath_birthdeath", p:0.5, accept:108, reject:242, acceptFC:0, rejectFC:0, rejectIv:59, rejectOp:59},
{id:"UniformOperator.t:birthdeath_birthdeath", p:NaN, accept:2250, reject:1472, acceptFC:0, rejectFC:0, rejectIv:0, rejectOp:0},
{id:"SubtreeSlide.t:birthdeath_birthdeath", p:1.0, accept:914, reject:1003, acceptFC:0, rejectFC:0, rejectIv:447, rejectOp:447},
{id:"narrow.t:birthdeath_birthdeath", p:NaN, accept:1256, reject:647, acceptFC:0, rejectFC:0, rejectIv:0, rejectOp:0},
{id:"wide.t:birthdeath_birthdeath", p:NaN, accept:88, reject:311, acceptFC:0, rejectFC:0, rejectIv:208, rejectOp:208},
{id:"WilsonBalding.t:birthdeath_birthdeath", p:NaN, accept:57, reject:318, acceptFC:0, rejectFC:0, rejectIv:129, rejectOp:129},
{id:"RBOperator.s:birthdeath_birthdeath", p:NaN, accept:47, reject:78, acceptFC:0, rejectFC:0, rejectIv:43, rejectOp:43},
{id:"RBratescaler.s:birthdeath_birthdeath", p:0.5, accept:59, reject:66, acceptFC:0, rejectFC:0, rejectIv:32, rejectOp:32},
{id:"BirthRateScaler.t:birthdeath_birthdeath", p:0.75, accept:291, reject:69, acceptFC:0, rejectFC:0, rejectIv:0, rejectOp:0},
{id:"DeathRateScaler.t:birthdeath_birthdeath", p:0.75, accept:299, reject:59, acceptFC:0, rejectFC:0, rejectIv:1, rejectOp:1}
]}
-->

*/

/* Parameters used:

  const int dna_length{20};
  const double mutation_rate{0.1};
  const int n_generations{1};
  const int pop_size{10};
  const int seed{42};

*/

/* coalescent_coalescent.xml.state:


<itsabeastystatewerein version='2.0' sample='10000'>
<statenode id='Tree.t:coalescent_coalescent'>((((0:1.9731487278617976,(2:0.02385862495086483,5:0.02385862495086483)12:1.9492901029109329)17:0.5602600580639896,(1:0.15558418773033483,6:0.15558418773033483)10:2.377824598195452)13:3.54396556997399,(3:0.8046576734483606,9:0.8046576734483606)16:5.272716682451416)11:6.921407992888125,((4:0.6362512899069979,8:0.6362512899069979)14:2.317725193372067,7:2.9539764832790647)15:10.044805865508838)18:0.0</statenode>
<statenode id='RBcount.s:coalescent_coalescent'>RBcount.s:coalescent_coalescent[1 1] (0,5): 1 </statenode>
<statenode id='RBrates.s:coalescent_coalescent'>RBrates.s:coalescent_coalescent[5 1] (0.01,100.0): 0.23132701641187525 1.657609536938711 0.439309067785706 0.8175615492373255 0.5083458236172506 </statenode>
<statenode id='popSize.t:coalescent_coalescent'>popSize.t:coalescent_coalescent[1 1] (-Infinity,Infinity): 8.965749070849592 </statenode>
</itsabeastystatewerein>
<!--
{operators:[
{id:"treeScaler.t:coalescent_coalescent", p:0.5, accept:145, reject:260, acceptFC:0, rejectFC:0, rejectIv:0, rejectOp:0},
{id:"treeRootScaler.t:coalescent_coalescent", p:0.5, accept:203, reject:202, acceptFC:0, rejectFC:0, rejectIv:45, rejectOp:45},
{id:"UniformOperator.t:coalescent_coalescent", p:NaN, accept:1970, reject:1955, acceptFC:0, rejectFC:0, rejectIv:0, rejectOp:0},
{id:"SubtreeSlide.t:coalescent_coalescent", p:1.0, accept:991, reject:997, acceptFC:0, rejectFC:0, rejectIv:440, rejectOp:440},
{id:"narrow.t:coalescent_coalescent", p:NaN, accept:1245, reject:599, acceptFC:0, rejectFC:0, rejectIv:0, rejectOp:0},
{id:"wide.t:coalescent_coalescent", p:NaN, accept:81, reject:312, acceptFC:0, rejectFC:0, rejectIv:207, rejectOp:207},
{id:"WilsonBalding.t:coalescent_coalescent", p:NaN, accept:54, reject:333, acceptFC:0, rejectFC:0, rejectIv:108, rejectOp:108},
{id:"RBOperator.s:coalescent_coalescent", p:NaN, accept:50, reject:94, acceptFC:0, rejectFC:0, rejectIv:57, rejectOp:57},
{id:"RBratescaler.s:coalescent_coalescent", p:0.5, accept:43, reject:70, acceptFC:0, rejectFC:0, rejectIv:46, rejectOp:46},
{id:"PopSizeScaler.t:coalescent_coalescent", p:0.75, accept:325, reject:72, acceptFC:0, rejectFC:0, rejectIv:0, rejectOp:0}
]}
-->

*/

