//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolCodeToHtml.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "codetohtmlinfo.h"

#include <cassert>
#include <ctime>

#include <boost/lexical_cast.hpp>

#include "codetohtmlheader.h"
#include "codetohtmlfooter.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::c2h::Info::Info()
  : m_page_info(CreatePageInfo())
{
  #ifndef NDEBUG
  Test();
  #endif
  //{
  //  const std::string s = "CodeToHtml info pages: "
  //  + boost::lexical_cast<std::string>(m_page_info.size());
  //  TRACE(s);
  //}
}

const std::map<std::string,std::vector<std::string> > ribi::c2h::Info::CreatePageInfo()
{
  //Do not create this map from a single huge initializer list: the compiler will choke on it after about 5000 lines
  typedef std::string Key;
  typedef std::vector<std::string> Value;
  typedef std::pair<Key,Value> Pair;
  std::vector<Pair> m;

  // sed -i "s/^.*$/       R\"\(&\)\"\,/g" tmp.txt

  m.push_back(
    {
      "CppAbcFile",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppAbcFile.htm\">AbcFile</a> is a",
        "<a href=\"CppClass.htm\">class</a> for an ABC music",
        "notation file.</p>"
      }
    }
  );
  m.push_back(
    { "CppAbout",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppAbout.htm\">About</a> is a",
        "<a href=\"CppClass.htm\">class</a> to display information",
        "about a program.</p>"
      }
    }
  );

  m.push_back(
    { "CppAlglibExample1",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppAlglibExample1.htm\">ALGLIB example 1: linear fit</a> is an <a href=\"CppAlglib.htm\">ALGLIB</a> <a href=\"CppExample.htm\">example</a>.",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppAlglibExample1.zip\">Download the Qt Creator project 'CppAlglibExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppAlglibExample2",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppAlglibExample2.htm\">ALGLIB example 2: linear fit</a> is an <a href=\"CppAlglib.htm\">ALGLIB</a> <a href=\"CppExample.htm\">example</a>.",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppAlglibExample2.zip\">Download the Qt Creator project 'CppAlglibExample2' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppApproximator",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppApproximator.htm\">Approximator</a> is a",
        "  <a href=\"CppClass.htm\">class</a> to perform an interpolation",
        "  on data. For example, when the supplied data consists of the coordinats",
        "  (1,1) and (2,2), it will estimate (the x value of) 1,5 to be (the value y value of) 1,5.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppApproximator.htm\">Approximator</a> does not support multiple",
        "  identical keys (for example the coordinats (1.0,2.0) and (1.0,3.0)),",
        "  similar to a <a href=\"CppMap.htm\">std::map</a>.",
        "  <a href=\"CppMultiApproximator.htm\">MultiApproximator</a> does",
        "  allow this."
        "</p>"
      }
    }
  );

  m.push_back(
    { "CppArduinoExample1",
      {
        "<p>"
        "  <img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicArduino.png\" alt=\"Arduino\"/>",
        "</p>"
        "<p>&nbsp;</p>",
        "<p><a href=\"CppArduinoExample1.htm\">Arduino example 1</a> is an <a href=\"CppArduino.htm\">Arduino</a> <a href=\"CppExample.htm\">example</a>.",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppArduinoExample1.zip\">Download the Qt Creator project 'CppArduinoExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppArrayExample1",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<h1>(<a href=\"Cpp.htm\">C++</a>) <a href=\"CppArrayExample1.htm\">array/std::array/boost::array example 1: comparison</a></h1>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppArrayExample1.htm\">array/std::array/boost::array example 1: comparison</a>",
        "  is a comparison between",
        "  a plain <a href=\"CppArray.htm\">array</a>, <a href=\"CppStdArray.htm\">std::array</a>,",
        "  <a href=\"CppTr1Array.htm\">std::tr1::array</a> ",
        "  and <a href=\"CppBoostArray.htm\">boost::array</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/> <a href=\"CppArrayExample1.zip\">Download the Qt Creator project 'CppArrayExample1' (zip)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><a href=\"CppArrayExample1Exe.zip\">Download the Windows executable of 'CppArrayExample1' (zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>The conclusions draws are (note that every 'Yes' is 'a good thing'):</p>",
        "<p>&nbsp;</p>",
        "<table summary=\"Comparison\" border = \"1\">",
        "  <tr>",
        "    <td>Property tested</td>",
        "    <td>Statically allocated plain array</td>",
        "    <td>Dynamically allocated plain array</td>",
        "    <td><a href=\"CppTr1Array.htm\">std::tr1::array</a></td>",
        "    <td><a href=\"CppStdArray.htm\">std::array</a></td>",
        "    <td><a href=\"CppBoostArray.htm\">boost::array</a></td>",
        "  </tr>",
        "  <tr><td>Initialization at creation</td><td>Yes</td><td>No</td><td>Yes</td><td>Yes</td><td>Yes</td></tr>",
        "  <tr><td>Initialization at creation checked against too few elements</td><td>No</td><td>N/A</td><td>No</td><td>No</td><td>No</td></tr>",
        "  <tr><td>Initialization at creation checked against too many elements</td><td>Yes</td><td>N/A</td><td>Yes</td><td>Yes</td><td>Yes</td></tr>",
        "  <tr><td>Size requestable at compile-time</td><td>Yes</td><td>No</td><td>No</td><td>Yes</td><td>No</td></tr>",
        "  <tr><td>Size requestable at run-time</td><td>Yes</td><td>No</td><td>Yes</td><td>Yes</td><td>Yes</td></tr>",
        "</table>"
      }
    }
  );
  m.push_back(
    { "CppAsciiArter",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppAsciiArter.htm\">AsciiArter</a> is a",
        "  GUI-independent <a href=\"CppClass.htm\">class</a> to",
        "  <a href=\"CppConvert.htm\">convert</a> images to",
        "  <a href=\"CppAsciiArt.htm\">ASCII art</a>.",
        "</p>"
      }
    }
  );
  m.push_back(
    { "CppAssertExample1",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppAssertExample1.htm\">assert example 1: basics</a> is an <a href=\"CppAssert.htm\">assert</a> <a href=\"CppExample.htm\">example</a>.",
        "<p>&nbsp;</p>",
        "<p>A division will only succeed if the denominator is unequal to zero. ",
        "In your code, you will have to take care that a division by zero never occurs. ",
        "Using <a href=\"CppAssert.htm\">assert</a>, as shown in the code below, will take you to the problem directly.",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppAssertExample1.zip\">Download the Qt Creator project 'CppAssertExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppAssertExample2",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppAssertExample2.htm\">assert example 2: basics with informative output</a> is an",
        "  <a href=\"CppAssert.htm\">assert</a> <a href=\"CppExample.htm\">example</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppAssertExample2.zip\">Download the Qt Creator project 'CppAssertExample2' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppAssertExample3",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppAssertExample3.htm\">assert example 3: a user-defined assert</a> is an",
        "  <a href=\"CppAssert.htm\">assert</a> <a href=\"CppExample.htm\">example</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppAssertExample3.zip\">Download the Qt Creator project 'CppAssertExample3' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppAutoExample1",
      {
        "<p><img src=\"PicCpp11.png\" alt=\"C++11\"/><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppAutoExample1.htm\">auto example 1: basics</a> is an <a href=\"CppAuto.htm\">auto</a> <a href=\"CppExample.htm\">example</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  A division will only succeed if the denominator is unequal to zero.",
        "  In your code, you will have to take care that a division by zero never occurs. ",
        "  Using <a href=\"CppAssert.htm\">assert</a>, as shown in the code below, will take you to the problem directly.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppAssertExample1.zip\">Download the Qt Creator project 'CppAssertExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );


  m.push_back(
    { "CppBimapExample1",
      {
        "<p>",
        "  <a href=\"CppBimapExample1.htm\">boost::bimap example 1: find</a> is a",
        "  <a href=\"CppBimap.htm\">boost::bimap</a> <a href=\"CppExample.htm\">example</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppBimapExample1.zip\">Download the Qt Creator project 'CppBimapExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppBimapExample2",
      {
        "<p>",
        "  <a href=\"CppBimapExample2.htm\">boost::bimap example 2: copy</a> is a",
        "  <a href=\"CppBimap.htm\">boost::bimap</a> <a href=\"CppExample.htm\">example</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppBimapExample2.zip\">Download the Qt Creator project 'CppBimapExample2' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppBinaryNewickVector",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppBinaryNewickVector.htm\">BinaryNewickVector</a> is a <a href=\"CppDataType.htm\">data type</a>",
        "  for storing phylogenies in the <a href=\"CppNewick.htm\">Newick</a> format.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  The <a href=\"Tools.htm\">tool</a> <a href=\"ToolTestBinaryNewickVector.htm\">TestBinaryNewickVector</a>",
        "  is a GUI to test and experiment with <a href=\"CppBinaryNewickVector.htm\">BinaryNewickVector</a>.",
        "</p>",
        "<p>&nbsp;</p>",
      }
    }
  );
  m.push_back(
    { "CppBoostFormatExample1",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppBoostFormatExample1.htm\">Boost.Format example 1</a>"
        "  is a <a href=\"CppBoostFormat.htm\">Boost.Format</a> <a href=\"CppExample.htm\">example</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppBoostFormatExample1.zip\">Download the Qt Creator project 'CppBoostFormatExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppBoostFormatExample2",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppBoostFormatExample2.htm\">Boost.Format example 2</a>",
        "  is a <a href=\"CppBoostFormat.htm\">Boost.Format</a> <a href=\"CppExample.htm\">example</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppBoostFormatExample2.zip\">Download the Qt Creator project 'CppBoostFormatExample2' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppBoostFunctionExample3",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppBoostFunctionExample3.htm\">Boost.Function example 3: calling a member function with an argument and reading its result</a>",
        "  is a <a href=\"CppBoostFunction.htm\">Boost.Function</a> example that shows how",
        "  to call a member function with an argument and how to read its result.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "CppBoostGeometryExample1",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppBoostGeometryExample1.htm\">Boost.Geometry example 1: determine if a point is within a polygon</a>",
        "  is a <a href=\"CppBoostGeometry.htm\">Boost.Geometry</a> <a href=\"CppExample.htm\">example</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "CppBoostGeometryExample2",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppBoostGeometryExample2.htm\">Boost.Geometry example 2: points to polygon and back, determine the area of a polygon</a>",
        "  is a <a href=\"CppBoostGeometry.htm\">Boost.Geometry</a> <a href=\"CppExample.htm\">example</a>.",
        "</p>"
      }
    }
  );


  m.push_back(
    { "CppBoostRegexExample1",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppBoostRegexExample1.htm\">Boost.Regex example 1</a>",
        "  is an <a href=\"CppExample.htm\">example</a> how to use the <a href=\"CppBoostRegex.htm\">Boost.Regex</a>",
        "  <a href=\"CppLibrary.htm\">library</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  The <a href=\"CppExample.htm\">example</a> below shows how to define a regular expression for a Dutch zip code,",
        "  how to check for it and how to search for it.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppBoostRegexExample1.zip\">Download the Qt Creator project 'CppBoostRegexExample1' (zip)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/> <a href=\"CppBoostRegexExample1Exe.zip\">Download the 'CppBoostRegexExample1' Windows executable (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppBoostRegexExample2",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppBoostRegexExample2.htm\">Boost.Regex example 2: replace</a>",
        "  is an <a href=\"CppExample.htm\">example</a> how to use the <a href=\"CppBoostRegex.htm\">Boost.Regex</a>",
        "  <a href=\"CppLibrary.htm\">library</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>The <a href=\"CppExample.htm\">example</a> below shows how to perform a replacement within a regular expression.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppBoostRegexExample2.zip\">Download the Qt Creator project 'CppBoostRegexExample2' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppBoostRegexExample3",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppBoostRegexExample3.htm\">Boost.Regex example 3</a>",
        "  is an <a href=\"CppExample.htm\">example</a> how to use the <a href=\"CppBoostRegex.htm\">Boost.Regex</a>",
        "  <a href=\"CppLibrary.htm\">library</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>The <a href=\"CppExample.htm\">example</a> below shows how to iterate through a text with a regular expression.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppBoostRegexExample3.zip\">Download the Qt Creator project 'CppBoostRegexExample3' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppBoostSignals2Example1",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppBoostSignals2Example1.htm\">Boost.Signals2 example 1: comparing Boost and Qt</a>",
        "  is a <a href=\"CppBoostSignals2.htm\">Boost.Signals2</a> example that shows",
        "  both the use of <a href=\"CppBoostSignals2.htm\">Boost.Signals2 signals</a> and",
        "  <a href=\"CppQtSignal.htm\">Qt signals</a>.</p>",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  The <a href=\"CppArticle.htm\">article</a> <a href=\"CppFromQtSignalToBoostSignal.htm\">From Qt signal to Boost signal</a>",
        "  describes why and how to move from using <a href=\"CppQtSignal.htm\">Qt signals</a> to using",
        "  <a href=\"CppBoostSignals2.htm\">Boost.Signal2 signals</a>.",
        "</p>"
      }
    }
  );


  m.push_back(
    { "CppBoostSignals2Example2",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppBoostSignals2Example2.htm\">Boost.Signals2 example 2: emitting this</a>",
        "  is a <a href=\"CppBoostSignals2.htm\">Boost.Signals2</a> example that shows how",
        "  to emit <a href=\"CppThis.htm\">this</a>.",
        "</p>"
      }
    }
  );


  m.push_back(
    { "CppBoostTestExample1",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppBoostTestExample1.htm\">Boost.Test example 1</a>",
        "  is a <a href=\"CppBoostTest.htm\">Boost.Test</a> <a href=\"CppExample.htm\">example</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppBoostTestExample1.zip\">Download the Qt Creator project 'CppBoostTestExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );


  m.push_back(
    { "CppBoostTupleExample1",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppBoostTupleExample1.htm\">Boost.Tuple example 1</a>",
        "  is a <a href=\"CppBoostTuple.htm\">Boost.Tuple</a> <a href=\"CppExample.htm\">example</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppBoostTupleExample1.zip\">Download the Qt Creator project 'CppBoostTupleExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppBoostUnitsExample1",
      {
        "<p>",
        "  <img src=\"PicCpp98.png\" alt=\"Cpp98\"/><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWindows.png\" alt=\"Windows\"/>",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppBoostUnitsExample1.htm\">Boost.Units example 1: example from Boost</a>",
        "  is a <a href=\"CppBoostUnits.htm\">Boost.Units</a> example.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppBoostUnitsExample1.zip\">Download the Qt Creator project 'CppBoostUnitsExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppBoostUnitsExample2",
      {
        "<p>",
        "  <img src=\"PicCpp98.png\" alt=\"Cpp98\"/><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWindows.png\" alt=\"Windows\"/>",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppBoostUnitsExample2.htm\">Boost.Units example 2: calculate the area from two lengths</a>",
        "  is a <a href=\"CppBoostUnits.htm\">Boost.Units</a> example.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppBoostUnitsExample2.zip\">Download the Qt Creator project 'CppBoostUnitsExample2' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppBoostUnitsExample3",
      {
        "<p>",
        "  <img src=\"PicCpp98.png\" alt=\"Cpp98\"/><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWindows.png\" alt=\"Windows\"/>",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppBoostUnitsExample3.htm\">Boost.Units example 3: creating a Length, Width and Area classes</a>",
        "  is a <a href=\"CppBoostUnits.htm\">Boost.Units</a> example.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppBoostUnitsExample3.zip\">Download the Qt Creator project 'CppBoostUnitsExample3' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppBoostUnitsExample4",
      {
        "<p>",
        "  <img src=\"PicCpp98.png\" alt=\"Cpp98\"/><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWindows.png\" alt=\"Windows\"/>",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppBoostUnitsExample4.htm\">Boost.Units example 4: creating a Length, Width and Area classes with some typedefs</a>",
        "  is a <a href=\"CppBoostUnits.htm\">Boost.Units</a> example.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppBoostUnitsExample4.zip\">Download the Qt Creator project 'CppBoostUnitsExample4' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppBoostUnitsExample5",
      {
        "<p>",
        "  <img src=\"PicCpp98.png\" alt=\"Cpp98\"/><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWindows.png\" alt=\"Windows\"/>",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppBoostUnitsExample5.htm\">Boost.Units example 5: averaging multiple lengths</a>",
        "  is a <a href=\"CppBoostUnits.htm\">Boost.Units</a> example.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppBoostUnitsExample5.zip\">Download the Qt Creator project 'CppBoostUnitsExample5' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppBoostUnitsExample6",
      {
        "<p>",
        "  <img src=\"PicCpp98.png\" alt=\"Cpp98\"/><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWindows.png\" alt=\"Windows\"/>",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppBoostUnitsExample6.htm\">Boost.Units example 6: using an angle</a>",
        "  is a <a href=\"CppBoostUnits.htm\">Boost.Units</a> example.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppBoostUnitsExample6.zip\">Download the Qt Creator project 'CppBoostUnitsExample6' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppBoostUnitsExample7",
      {
        "<p>",
        "  <img src=\"PicCpp98.png\" alt=\"Cpp98\"/><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWindows.png\" alt=\"Windows\"/>",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppBoostUnitsExample7.htm\">Boost.Units example 7: calculating a force from a mass and an acceleration</a>",
        "  is a <a href=\"CppBoostUnits.htm\">Boost.Units</a> example.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppBoostUnitsExample7.zip\">Download the Qt Creator project 'CppBoostUnitsExample7' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppBoostUnitsExample8",
      {
        "<p>",
        "  <img src=\"PicCpp98.png\" alt=\"Cpp98\"/><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWindows.png\" alt=\"Windows\"/>",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppBoostUnitsExample8.htm\">Boost.Units example 8: calculating mass from a volume and a mass density</a>",
        "  is a <a href=\"CppBoostUnits.htm\">Boost.Units</a> example.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppBoostUnitsExample8.zip\">Download the Qt Creator project 'CppBoostUnitsExample8' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppBoostUnitsExample9",
      {
        "<p>",
        "  <img src=\"PicCpp98.png\" alt=\"Cpp98\"/><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWindows.png\" alt=\"Windows\"/>",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppBoostUnitsExample9.htm\">Boost.Units example 9: calculating pressure from a force and an area</a>",
        "  is a <a href=\"CppBoostUnits.htm\">Boost.Units</a> example.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppBoostUnitsExample9.zip\">Download the Qt Creator project 'CppBoostUnitsExample9' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppBoostUnitsExample10",
      {
        "<p>",
        "  <img src=\"PicCpp98.png\" alt=\"Cpp98\"/><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWindows.png\" alt=\"Windows\"/>",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppBoostUnitsExample10.htm\">Boost.Units example 10: calculating angular acceleration and torque</a>",
        "  is a <a href=\"CppBoostUnits.htm\">Boost.Units</a> example.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppBoostUnitsExample10.zip\">Download the Qt Creator project 'CppBoostUnitsExample10' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppBoostUnitsExample11",
      {
        "<p>",
        "  <img src=\"PicCpp98.png\" alt=\"Cpp98\"/><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWindows.png\" alt=\"Windows\"/>",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppBoostUnitsExample11.htm\">Boost.Units example 11: creating the quantity volumetric flow</a>",
        "  is a <a href=\"CppBoostUnits.htm\">Boost.Units</a> example.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppBoostUnitsExample11.zip\">Download the Qt Creator project 'CppBoostUnitsExample11' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppBoostUnitsExample12",
      {
        "<p>",
        "  <img src=\"PicCpp98.png\" alt=\"Cpp98\"/><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWindows.png\" alt=\"Windows\"/>",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppBoostUnitsExample12.htm\">Boost.Units example 12: creating the quantity volumetric flow and mass flow</a>",
        "  is a <a href=\"CppBoostUnits.htm\">Boost.Units</a> example.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppBoostUnitsExample12.zip\">Download the Qt Creator project 'CppBoostUnitsExample12' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppBoostWeak_ptrExample1",
      {
        "<p>",
        "  <a href=\"CppBoostWeak_ptrExample1.htm\">boost::weak_ptr example 1</a> is a",
        "  <a href=\"CppBoostWeak_ptr.htm\">boost::weak_ptr example</a>",
        "</p>"
      }
    }
  );

  m.push_back(
    { "CppCallStackCounter",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppCallStackCounter.htm\">CallStackCounter</a> is a <a href=\"CppClass.htm\">class</a>",
        "  to probe the depth of the call stack, for example in a recursive function.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  The tool <a href=\"ToolTestCallStackCounter.htm\">TestCallStackCounter</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to demonstrate its use.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "CppCanvas",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppCanvas.htm\">Canvas</a> is the <a href=\"CppAbstractBaseClass.htm\">(abstract) base class</a>",
        "  of an ASCII art canvas. <a href=\"CppDerivedClass.htm\">derived classes</a> are, among others,",
        "  <a href=\"CppDrawCanvas.htm\">DrawCanvas</a>, <a href=\"CppImageCanvas.htm\">ImageCanvas</a>",
        "  and <a href=\"CppTextCanvas.htm\">TextCanvas</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "CppChecked_deleteExample1",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppChecked_deleteExample1.htm\">boost::checked_delete example 1</a>",
        "  is a <a href=\"CppChecked_delete.htm\">boost::checked_delete</a> <a href=\"CppExample.htm\">example</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppChecked_deleteExample1.zip\">Download the Qt Creator project 'CppChecked_deleteExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppChess",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppChess.htm\">Chess</a> has many chess <a href=\"CppClass.htm\">classes</a>",
        "</p>"
      }
    }
  );

  m.push_back(
    { "CppChessResources",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppChessResources.htm\">ChessResources</a> contains and manages",
        "  <a href=\"CppChess.htm\">chess</a> resources",
        "</p>"
      }
    }
  );

  m.push_back(
    { "CppCodeToHtml",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppCodeToHtml.htm\">CodeToHtml</a> contains <a href=\"CppClass.htm\">classes</a>",
        "  used especially by the <a href=\"Tools.htm\">tool</a> <a href=\"ToolCodeToHtml.htm\">CodeToHtml</a>",
        "</p>"
      }
    }
  );

  m.push_back(
    { "CppCompileErrorParseErrorAtBOOST_JOIN",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppCompileErrorParseErrorAtBOOST_JOIN.htm\">CppCompileErrorParseErrorAtBOOST_JOIN</a> is a <a href=\"CppBoost.htm\">Boost</a> <a href=\"CppCompileError.htm\">compile error</a>.",
        "<ul>",
        "  <li><a href=\"CppCompileErrorParseErrorAtBOOST_JOIN.zip\">Download the Qt Creator project 'CppCompileErrorParseErrorAtBOOST_JOIN' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppConceptMap",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppConceptMap.htm\">ConceptMap</a> is a <a href=\"CppClass.htm\">class</a>",
        "  for a concept map.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppConceptMap.htm\">ConceptMap</a> is used in, among others,",
        "  the <a href=\"Tools.htm\">tool</a> <a href=\"ToolTestConceptMap.htm\">TestConceptMap</a>",
        "  and the <a href=\"Projects.htm\">project</a> <a href=\"ProjectBrainweaver.htm\">Brainweaver</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "CppConnectThree",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppConnectThree.htm\">ConnectThree</a> is a <a href=\"CppClass.htm\">class</a>",
        "  for a <a href=\"GameConnectThree.htm\">ConnectThree game</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "CppConnectThreeWidget",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppConnectThreeWidget.htm\">ConnectThreeWidget</a> is a <a href=\"CppWidget.htm\">widget</a>",
        "for a <a href=\"GameConnectThree.htm\">ConnectThree game</a>.</p>"
      }
    }
  );

  m.push_back(
    { "CppContainer",
      {
        "<p>A <a href=\"CppContainer.htm\">container</a> is a <a href=\"CppClassType.htm\">class type</a> for containing zero, one or multiple instances of one or more <a href=\"CppDataType.htm\">data type</a>s.</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  Every <a href=\"CppContainer.htm\">container</a> has its own advantages and disadvantages. ",
        "  For example a <a href=\"CppVector.htm\">std::vector</a> has random-access reading/writing, ",
        "  but new elements can only be added at the begin and end of the <a href=\"CppContainer.htm\">container</a>. ",
        "  For a <a href=\"CppList.htm\">std::list</a>, this is the other way around.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"CppStl.htm\">STL</a> <a href=\"CppContainer.htm\">container</a>s (incomplete list)</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicCpp11.png\" alt=\"C++11\"/> <a href=\"CppBitset.htm\">std::bitset</a></li>",
        "  <li><img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicCpp11.png\" alt=\"C++11\"/><a href=\"CppDeque.htm\">std::deque</a></li>",
        "  <li><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicCpp11.png\" alt=\"C++11\"/><a href=\"CppForward_list.htm\">std::forward_list</a></li>",
        "  <li><img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicCpp11.png\" alt=\"C++11\"/><a href=\"CppList.htm\">std::list</a></li>",
        "  <li><img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicCpp11.png\" alt=\"C++11\"/><a href=\"CppMap.htm\">std::map</a></li>",
        "  <li><img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicCpp11.png\" alt=\"C++11\"/><a href=\"CppMultimap.htm\">std::multimap</a></li>",
        "  <li><img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicCpp11.png\" alt=\"C++11\"/><a href=\"CppMultiset.htm\">std::multiset</a></li>",
        "  <li><img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicCpp11.png\" alt=\"C++11\"/><a href=\"CppPair.htm\">std::pair</a></li>",
        "  <li><img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicCpp11.png\" alt=\"C++11\"/><a href=\"CppPriority_queue.htm\">std::priority_queue</a></li>",
        "  <li><img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicCpp11.png\" alt=\"C++11\"/><a href=\"CppSet.htm\">std::set</a></li>",
        "  <li><img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicCpp11.png\" alt=\"C++11\"/><a href=\"CppSlist.htm\">std::slist</a></li>",
        "  <li><img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicCpp11.png\" alt=\"C++11\"/><a href=\"CppStack.htm\">std::stack</a></li>",
        "  <li><img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicCpp11.png\" alt=\"C++11\"/><a href=\"CppString.htm\">std::string</a></li>",
        "  <li><img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicCpp11.png\" alt=\"C++11\"/><a href=\"CppQueue.htm\">std::queue</a></li>",
        "  <li><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicCpp11.png\" alt=\"C++11\"/><a href=\"CppUnordered_map.htm\">std::unordered_map</a></li>",
        "  <li><img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicCpp11.png\" alt=\"C++11\"/><a href=\"CppValarray.htm\">std::valarray</a></li>",
        "  <li><img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicCpp11.png\" alt=\"C++11\"/><a href=\"CppVector.htm\">std::vector</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>SGI extension <a href=\"CppContainer.htm\">containers</a> (incomplete list)</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>bit_vector</li>",
        "  <li><a href=\"CppHash_set.htm\">hash_set</a></li>",
        "  <li>hash_map</li>",
        "  <li>hash_multiset</li>",
        "  <li>hash_multimap</li>",
        "  <li>hash</li>",
        "  <li>rope</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"CppBoost.htm\">Boost</a> <a href=\"CppContainer.htm\">container</a>s (incomplete list)</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppAny.htm\">boost::any</a></li>",
        "  <li><a href=\"CppBoostArray.htm\">boost::array</a></li>",
        "  <li>boost::compressed_pair</li>",
        "  <li>boost::dynamic_bitset</li>",
        "  <li><a href=\"CppMulti_array.htm\">boost::multi_array</a></li>",
        "  <li>boost::ptr_array</li>",
        "  <li>boost::ptr_deque</li>",
        "  <li>boost::ptr_list</li>",
        "  <li>boost::ptr_map</li>",
        "  <li>boost::ptr_multimap</li>",
        "  <li>boost::ptr_multiset</li>",
        "  <li><a href=\"CppPtr_set.htm\">boost::ptr_set</a></li>",
        "  <li>boost::ptr_vector</li>",
        "  <li>boost::shared_array</li>",
        "  <li><a href=\"CppBoostTuple.htm\">boost::tuple</a></li>",
        "  <li>boost::variant</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"CppContainer.htm\">Container</a> <a href=\"CppCodeSnippets.htm\">code snippets</a></h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppContainerToStr.htm\">ContainerToStr, convert a container to a std::string</a></li>",
        "  <li><a href=\"CppContainerToStr.htm\">Convert a container to a std::string, ContainerToStr</a></li>",
        "  <li><a href=\"CppCopyFirst.htm\">Copy the first element of the std::pairs in a std::vector, CopyFirst</a></li>",
        "  <li><a href=\"CppCopySecond.htm\">Copy the second element of the std::pairs in a std::vector, CopySecond</a></li>",
        "  <li><a href=\"CppCopyFirst.htm\">CopyFirst, copy the first element of the std::pairs in a std::vector</a></li>",
        "  <li><a href=\"CppCopySecond.htm\">CopySecond, copy the second element of the std::pairs in a std::vector</a></li>",
        "  <li><a href=\"CppCoutContainer.htm\">CoutContainer, std::cout a container</a></li>",
        "  <li><a href=\"CppExtractIds.htm\">ExtractIds, extract the ID's for a std::vector of Persons</a></li>",
        "  <li><a href=\"CppExtractIds.htm\">Extract the ID's for a std::vector of Persons, ExtractIds</a></li>",
        "  <li><a href=\"CppGetMean.htm\">Get the mean value of all elements in a container, GetMean</a></li>",
        "  <li><a href=\"CppGetSum.htm\">Get the sum of all elements in a container, GetSum</a></li>",
        "  <li><a href=\"CppGetMinThree.htm\">Get the three lowest elements of a container, GetMinThree</a></li>",
        "  <li><a href=\"CppGetMean.htm\">GetMean, get the mean value of all elements in a container</a></li>",
        "  <li><a href=\"CppGetMinThree.htm\">GetMinThree, obtain the three lowest elements of a container</a></li>",
        "  <li><a href=\"CppGetSum.htm\">GetSum, get the sum of all elements in a container</a></li>",
        "  <li><a href=\"CppLoopReader.htm\">LoopReader, reading a container looped</a></li>",
        "  <li><a href=\"CppMatrix.htm\">Matrix</a></li>",
        "  <li><a href=\"CppLoopReader.htm\">Reading a container looped, LoopReader</a></li>",
        "  <li><a href=\"CppReciprocal.htm\">Reciprocal, replace all values in a container by their reciprocal</a></li>",
        "  <li><a href=\"CppReciprocal.htm\">Replace all values in a container by their reciprocal, Reciprocal</a></li>",
        "  <li><a href=\"CppSaveContainer.htm\">Save a container to file, SaveContainer</a></li>",
        "  <li><a href=\"CppSaveContainer.htm\">SaveContainer, save a container to file</a></li>",
        "  <li><a href=\"CppCoutContainer.htm\">std::cout a container, CoutContainer</a></li>",
        "  <li><a href=\"CppTriple.htm\">Triple all values in a container, Triple</a></li>",
        "  <li><a href=\"CppTriple.htm\">Triple, triple all values in a container</a></li>",
        "",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"CppAdvice.htm\">Advice</a></h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>",
        "    <a href=\"CppStl.htm\">STL</a> <a href=\"CppContainer.htm\">containers</a> are resource handles [6]",
        "  </li>",
        "  <li>",
        "    If a <a href=\"CppClass.htm\">class</a> is a <a href=\"CppContainer.htm\">container</a>, give it an <a href=\"CppInitializerList.htm\">initializer-list</a> <a href=\"CppContructor.htm\">constructor</a> [1]",
        "  </li>",
        "  <li>",
        "    Use <a href=\"CppTemplate.htm\">templates</a> to express <a href=\"CppContainer.htm\">containers</a> [2]",
        "  </li>",
        "  <li>",
        "    An <a href=\"CppStl.htm\">STL</a> <a href=\"CppContainer.htm\">container</a> defines a sequence [3]",
        "  </li>",
        "  <li>",
        "    Use <a href=\"CppVector.htm\">std::vector</a> as your default <a href=\"CppContainer.htm\">container</a> [4]",
        "  </li>",
        "  <li>",
        "    Insertion operators, such as insert() and push_back() are often more efficient on a <a href=\"CppVector.htm\">std::vector</a> than on a <a href=\"CppList.htm\">std::list</a> [5]",
        "  </li>",
        "  <li>",
        "    Pass a <a href=\"CppContainer.htm\">container</a> by <a href=\"CppReference.htm\">reference</a> and <a href=\"CppReturn.htm\">return</a> a <a href=\"CppContainer.htm\">container</a> by value [7]",
        "  </li>",
        "  <li>",
        "    For a <a href=\"CppContainer.htm\">container</a>, use the ()-syntax for sizes and the <a href=\"CppListInitialization.htm\">list initialization</a> syntax for lists of elements [8]",
        "  </li>",
        "  <li>",
        "    For simple traversal of a <a href=\"CppContainer.htm\">container</a>, use a <a href=\"CppRangeFor.htm\">range-for</a>-loop or a begin/end pair of <a href=\"CppIterator.htm\">iterators</a> [9]",
        "  </li>",
        "  <li>",
        "    Use push_back() or resize() on a <a href=\"CppContainer.htm\">container</a>, rather than <a href=\"CppRealloc.htm\">std::realloc</a> on an <a href=\"CppArray.htm\">array</a> [10]",
        "  </li>",
        "  <li>",
        "    Do not assume that <a href=\"CppOperatorIndex.htm\">operator[]</a> range checks [11]",
        "  </li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"CppReferences.htm\">References</a></h2>",
        "<p>&nbsp;</p>",
        "<ol>",
        "  <li><!--  1 --><a href=\"CppBjarneStroustrup.htm\">Bjarne Stroustrup</a>. The C++ Programming Language (4th edition). 2013. ISBN: 978-0-321-56384-2. Chapter 17.7. Advice. page 525: '[8] If a class is a container, give it an initializer-list constructor'</li>",
        "  <li><!--  2 --><a href=\"CppBjarneStroustrup.htm\">Bjarne Stroustrup</a>. The C++ Programming Language (4th edition). 2013. ISBN: 978-0-321-56384-2. Chapter 23.8, page 698: '[2] Use templates to express containers'</li>",
        "  <li><!--  3 --><a href=\"CppBjarneStroustrup.htm\">Bjarne Stroustrup</a>. The C++ Programming Language (4th edition). 2013. ISBN: 978-0-321-56384-2. Chapter 31.6. Advice. page 924: '[1] An STL container defines a sequence'</li>",
        "  <li><!--  4 --><a href=\"CppBjarneStroustrup.htm\">Bjarne Stroustrup</a>. The C++ Programming Language (4th edition). 2013. ISBN: 978-0-321-56384-2. Chapter 31.6. Advice. page 924: '[2] Use vector as your default container'</li>",
        "  <li><!--  5 --><a href=\"CppBjarneStroustrup.htm\">Bjarne Stroustrup</a>. The C++ Programming Language (4th edition). 2013. ISBN: 978-0-321-56384-2. Chapter 31.6. Advice. page 924: '[3] Insertion operators, such as insert() and push_back() are often more efficient on a vector than on a list'</li>",
        "  <li><!--  6 --><a href=\"CppBjarneStroustrup.htm\">Bjarne Stroustrup</a>. The C++ Programming Language (4th edition). 2013. ISBN: 978-0-321-56384-2. Chapter 31.6. Advice. page 924: '[7] STL containers are resource handles'</li>",
        "  <li><!--  7 --><a href=\"CppBjarneStroustrup.htm\">Bjarne Stroustrup</a>. The C++ Programming Language (4th edition). 2013. ISBN: 978-0-321-56384-2. Chapter 31.6. Advice. page 924: '[13] Pass a container by reference and return a container by value'</li>",
        "  <li><!--  8 --><a href=\"CppBjarneStroustrup.htm\">Bjarne Stroustrup</a>. The C++ Programming Language (4th edition). 2013. ISBN: 978-0-321-56384-2. Chapter 31.6. Advice. page 924: '[14] For a container, use the ()-syntax for sizes and the {}-initializer syntax for lists of elements'</li>",
        "  <li><!--  9 --><a href=\"CppBjarneStroustrup.htm\">Bjarne Stroustrup</a>. The C++ Programming Language (4th edition). 2013. ISBN: 978-0-321-56384-2. Chapter 31.6. Advice. page 924: '[15] For simple traversal of a container, use a range-for-loop or a begin/end pair of iterators'</li>",
        "  <li><!-- 10 --><a href=\"CppBjarneStroustrup.htm\">Bjarne Stroustrup</a>. The C++ Programming Language (4th edition). 2013. ISBN: 978-0-321-56384-2. Chapter 31.6. Advice. page 924: '[20] Use push_back() or resize() on a container, rather than realloc() on an array'</li>",
        "  <li><!-- 11 --><a href=\"CppBjarneStroustrup.htm\">Bjarne Stroustrup</a>. The C++ Programming Language (4th edition). 2013. ISBN: 978-0-321-56384-2. Chapter 31.6. Advice. page 924: '[23] Do not assume that [] range checks'</li>",
        "</ol>"
      }
    }
  );

  m.push_back(
    { "CppCoordinat",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppCoordinat.htm\">Coordinat</a> is a <a href=\"CppClass.htm\">class</a>",
        "  for a coordinat.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "CppCopy_if",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppCopy_if.htm\">copy_if</a> is an <a href=\"CppAlgorithm.htm\">algorithm</a> that was dropped ",
        "from the <a href=\"Cpp98.htm\">C++98</a> <a href=\"CppStl.htm\">STL</a> by accident, but added to the",
        "<a href=\"Cpp11.htm\">C++11</a> <a href=\"CppStl.htm\">STL</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><img src=\"PicCpp98.png\" alt=\"C++98\"/> <a href=\"CppCopy_if.htm\">std::copy_if</a></h2>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppCopy_if.htm\">std::copy_if</a> is an <a href=\"CppAlgorithm.htm\">algorithm</a> that was dropped ",
        "from the <a href=\"Cpp98.htm\">C++98</a> <a href=\"CppStl.htm\">STL</a> by accident.</p>",
        "<p>&nbsp;</p>",
        "<p>Prefer <a href=\"CppAlgorithm.htm\">algorithm</a> calls over hand-written loops [1][2].</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h3><img src=\"PicCpp98.png\" alt=\"C++98\"/> Example <a href=\"CppDefinition.htm\">definition</a> of <a href=\"CppCopy_if.htm\">copy_if</a></h3>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary = \"copy_if definition\" border = \"1\"><tr><td><code>",
        "<a href=\"CppComment.htm\">//</a><a href=\"CppCopy_if.htm\">Copy_if</a> was dropped from the standard library by accident.<br/>",
        "<b><a href=\"CppTemplate.htm\">template</a></b>&lt;<b><a href=\"CppTypename.htm\">typename</a></b> In, <b><a href=\"CppTypename.htm\">typename</a></b> Out, <b><a href=\"CppTypename.htm\">typename</a></b> Pred&gt;<br/>",
        "Out <a href=\"CppCopy_if.htm\">Copy_if</a>(In first, In last, Out res, Pred Pr)<br/>",
        "{<br/>",
        "&nbsp;&nbsp;<b><a href=\"CppWhile.htm\">while</a></b> (first <a href=\"CppOperatorNotEqual.htm\">!=</a> last)<br/>",
        "&nbsp;&nbsp;{<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;<b><a href=\"CppIf.htm\">if</a></b> (Pr(*first))<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*res<a href=\"CppOperatorIncrement.htm\">++</a> = *first;<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"CppOperatorIncrement.htm\">++</a>first;<br/>",
        "&nbsp;&nbsp;}<br/>",
        "&nbsp;&nbsp;<b><a href=\"CppReturn.htm\">return</a></b> res;<br/>",
        "}<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><img src=\"PicCpp11.png\" alt=\"C++11\"/> <a href=\"CppCopy_if.htm\">std::copy_if</a></h2>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppCopy_if.htm\">std::copy_if</a> is an <a href=\"CppAlgorithm.htm\">algorithm</a> similar to",
        "<a href=\"CppCopy.htm\">std::copy</a>, except that a <a href=\"CppPredicate.htm\">predicate</a> can also",
        "be supplied. <a href=\"CppCopy_if.htm\">std::copy_if</a> resides in the <a href=\"Cpp11.htm\">C++11</a> ",
        "<a href=\"CppStl.htm\">STL</a> <a href=\"CppHeaderFile.htm\">header file</a> <a href=\"CppAlgorithmH.htm\">algorithm</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppCopy_if.htm\">Download the Qt Creator project 'CppCopy_if' (zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary = \"CppCopy_if code\" border = \"1\"><tr><td><code>",
        "<a href=\"CppInclude.htm\">#include</a> &lt;<a href=\"CppAlgorithmH.htm\">algorithm</a>&gt;<br/>",
        "<a href=\"CppInclude.htm\">#include</a> &lt;<a href=\"CppCassertH.htm\">cassert</a>&gt;<br/>",
        "<a href=\"CppInclude.htm\">#include</a> &lt;<a href=\"CppVectorH.htm\">vector</a>&gt;<br/>",
        "<br/>",
        "<b><a href=\"CppInt.htm\">int</a></b> <a href=\"CppMain.htm\">main</a>()<br/>",
        "{<br/>",
        "&nbsp;&nbsp;<a href=\"CppComment.htm\">//</a><a href=\"Cpp11.htm\">C++11</a> <a href=\"CppInitializerList.htm\">initializer list</a><br/>",
        "&nbsp;&nbsp;<b><a href=\"CppConst.htm\">const</a></b> <a href=\"CppVector.htm\">std::vector</a>&lt;<b><a href=\"CppInt.htm\">int</a></b>&gt; v <a href=\"CppOperatorAssign.htm\">=</a> { 0,1,2,3,4,5,6 };<br/>",
        "<br/>",
        "&nbsp;&nbsp;<a href=\"CppComment.htm\">//</a>Only copy the even values to w<br/>",
        "&nbsp;&nbsp;<a href=\"CppComment.htm\">//</a><b><a href=\"CppUsing.htm\">using</a></b> <a href=\"Cpp11.htm\">C++11</a> <a href=\"CppLambdaExpression.htm\">lambda expression</a><br/>",
        "&nbsp;&nbsp;<a href=\"CppVector.htm\">std::vector</a>&lt;<b><a href=\"CppInt.htm\">int</a></b>&gt; w;<br/>",
        "&nbsp;&nbsp;<a href=\"CppCopy_if.htm\">std::copy_if</a>(v.begin(), v.end(),<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"CppBack_inserter.htm\">std::back_inserter</a>(w),<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;[](<b><a href=\"CppConst.htm\">const</a></b> <b><a href=\"CppInt.htm\">int</a></b> i) { <b><a href=\"CppReturn.htm\">return</a></b> i <a href=\"CppOperatorModulus.htm\">%</a> 2 <a href=\"CppOperatorEqual.htm\">==</a> 0; } ,<br/>",
        "<br/>",
        "&nbsp;&nbsp;<a href=\"CppComment.htm\">//</a>Check all even values are indeed copied<br/>",
        "&nbsp;&nbsp;<a href=\"CppComment.htm\">//</a><b><a href=\"CppUsing.htm\">using</a></b> another <a href=\"Cpp11.htm\">C++11</a> <a href=\"CppInitializerList.htm\">initializer list</a><br/>",
        "&nbsp;&nbsp;<a href=\"CppAssert.htm\">assert</a>(w <a href=\"CppOperatorEqual.htm\">==</a> <a href=\"CppVector.htm\">std::vector</a>&lt;<b><a href=\"CppInt.htm\">int</a></b>&gt;( { 0,2,4,6 } ) ,<br/>",
        "}<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>Prefer <a href=\"CppAlgorithm.htm\">algorithm</a> calls over hand-written loops [1][2].</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"CppReferences.htm\">References</a></h2>",
        "<p>&nbsp;</p>",
        "<ol>",
        "  <li><a href=\"CppBjarneStroustrup.htm\">Bjarne Stroustrup</a>. The C++ Programming Language (3rd edition). 1997. ISBN: 0-201-88954-4. Chapter 18.12.1: 'Prefer algorithms to loops.</li>",
        "  <li><a href=\"CppScottMeyers.htm\">Scott Meyers</a>. Effective STL. ISBN: 0-201-74962-9. Item 43: 'Prefer algorithm calls over hand-written loops'</li>",
        "</ol>"
      }
    }
  );

  m.push_back(
    { "CppCopyFile",
      {
        "<p><a href=\"CppCopyFile.htm\">CopyFile</a> is a <a href=\"CppFileIo.htm\">file I/O</a> <a href=\"CppCodeSnippets.htm\">code snippet</a> to copy a file.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppCopyFile.zip\">Download the Qt Creator project 'CppCopyFile' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppCounter",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppCounter.htm\">Counter</a> is a <a href=\"CppClass.htm\">class</a>",
        "  for tallying.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "CppDial",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppDial.htm\">Dial</a> is a <a href=\"CppClass.htm\">class</a> for a dial.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppDial.htm\">Dial</a> is displayed by ",
        "<a href=\"CppQtDialWidget.htm\">QtDialWidget</a> and <a href=\"CppWtDialWidget.htm\">WtDialWidget</a>.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppDial.htm\">Dial</a> is used in (among others) the <a href=\"Tools.htm\">tool</a>",
        "<a href=\"ToolTestDial.htm\">TestDial</a>.</p>"
      }
    }
  );

  m.push_back(
    { "CppDialWidget",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppDialWidget.htm\">DialWidget</a> is a <a href=\"CppDial.htm\">Dial</a> <a href=\"CppWidget.htm\">widget</a>.</p>"
      }
    }
  );

  m.push_back(
    { "CppDotMatrix",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppDotMatrix.htm\">DotMatrix</a> is a <a href=\"CppClass.htm\">class</a>",
        "  for creating dot matrix texts.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "CppDrawCanvas",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppDrawCanvas.htm\">DrawCanvas</a> is a <a href=\"CppCanvas.htm\">Canvas</a>",
        "  to draw on.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "CppEncranger",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppEncranger.htm\">Encranger</a> is one of my own",
        "<a href=\"CppCryptography.htm\">cryptography</a> <a href=\"CppClass.htm\">classes</a>.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppEncranger.htm\">Encranger</a> is used in, among others:</p>",
        "<ul>",
        "  <li><a href=\"ToolEncranger.htm\">Encranger</a></li>",
        "  <li><a href=\"ProjectWtWebsite.htm\">ProjectWtWebsite</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppExercise",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  On this page you can find some exercises about correct programming,",
        "  inspired by <a href=\"CppHerbSutter.htm\">Herb Sutter</a>'s 'Guru Of The Week' pages.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  These <a href=\"CppExercise.htm\">exercises</a> are suitable for experienced beginners, ",
        "  that want to learn to think in the C++ way. As a side-result they will learn more ",
        "  advanced concepts in a playful way. I try to work on the same difficulty ",
        "  scale as <a href=\"CppHerbSutter.htm\">Herb Sutter</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>",
        "    <img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppExerciseDivide.htm\">Exercise #0: A correct Divide function</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppExerciseFoolproofFunction.htm\">Exercise #1: A foolproof function</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppExerciseCorrectFunctionDeclarations.htm\">Exercise #2: Correct function declarations</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppExerciseDontGiveAwayYourInternals.htm\">Exercise #3: Don't give away your internals</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppExerciseReadingFromAvectorSafely.htm\">Exercise #4: Reading from a std::vector safely</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppExerciseTheManyTypesOfConst.htm\">Exercise #5: The many types of const</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppExerciseRefactoringQuadraticSolver.htm\">Exercise #6: refactoring quadratic solver</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppExerciseAddOne.htm\">Exercise #7: add one</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/>",
        "    <a href=\"CppExerciseLibraryTrouble.htm\">Exercise #8: library trouble</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppExerciseNoForLoops.htm\">Exercise #9: no for-loops</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppExerciseReadonlyPointer.htm\">Exercise #10: Obtaining a read-only (smart?) pointer</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppExerciseReadonlyVectorOfPointers.htm\">Exercise #11: Obtaining a std::vector of read-only (smart?) pointers</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicQt.png\" alt=\"Qt\"/>",
        "    <a href=\"CppExerciseQtHideAndShow1.htm\">Exercise #12: Qt hide and show #1: intro</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicQt.png\" alt=\"Qt\"/>",
        "    <a href=\"CppExerciseQtHideAndShow2.htm\">Exercise #13: Qt hide and show #2: the real problem</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicQt.png\" alt=\"Qt\"/>",
        "    <a href=\"CppExerciseQtHideAndShow3.htm\">Exercise #14: Qt hide and show #3: refactoring</a>",
        "  </li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>External links</h2>",
        "<p>&nbsp;</p>",
        "<ol>",
        "  <li><a href=\"http://www.gotw.ca/gotw/\">Herb Sutter's Guru Of The Week archive</a></li>",
        "</ol>",
        "<p>",
        "  Additionally, <a href=\"CppExercise.htm\">Exercise</a> is a",
        "  <a href=\"CppClass.htm\">class</a> for an",
        "  exercise.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "CppFileIo",
      {
        "<p><a href=\"CppFileIo.htm\">File I/O</a> is working with files, like saving, reading, copying and searching.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"CppFileIo.htm\">File I/O</a> <a href=\"CppStl.htm\">STL</a> <a href=\"CppFunction.htm\">functions</a> and <a href=\"CppDataType.htm\">data types</a></h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppFstream.htm\">std::fstream</a>: file <a href=\"CppStream.htm\">stream</a></li>",
        "  <li><a href=\"CppRemove.htm\">std::remove</a>: remove a file</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"CppFileIo.htm\">File I/O</a> <a href=\"CppCodeSnippets.htm\">code snippets</a></h2>",
        "<p>&nbsp;</p>",
        "<ol>",
        "  <li>",
        "    <img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppCopy_file.htm\">boost::filesystem::copy_file, copy a file</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppIsRegularFile.htm\">Check if a file exists, IsRegularFile</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/> ",
        "    <a href=\"CppCopy_file.htm\">Copy a file, boost::filesystem::copy_file</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppCopyFile.htm\">Copy a file, CopyFile</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppCopyFile.htm\">CopyFile, copy a file</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppDeleteFile.htm\">DeleteFile, delete a file</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppDeleteFile.htm\">Delete a file, DeleteFile</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppFileToStringList.htm\">FileToStringList, read a file in a TStringList</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppFileToVector.htm\">FileToVector, read a file in a std::vector</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppGetPath.htm\">Get a file's path, GetPath</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppGetCppFilesInFolder.htm\">Get all C++ filenames in a folder, GetCppFilesInFolder</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppGetFilesInFolder.htm\">Get all filenames in a folder, GetFilesInFolder</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppGetExtension.htm\">Get the extension of a filename, GetExtension</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppGetCurrentFolder.htm\">Get the name of the folder your application runs in, GetCurrentFolder</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppGetCppFilesInFolder.htm\">GetCppFilesInFolder, get all C++ filenames in a folder</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppGetCurrentFolder.htm\">GetCurrentFolder, get the name of the folder your application runs in</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppGetFoldersInFolder.htm\">Get the names of the folders in a folder, GetFoldersInFolder</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppGetExtension.htm\">GetExtension, get the extension of a filename</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppGetFilesInFolder.htm\">GetFilesInFolder, get all filenames in a folder</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppGetFoldersInFolder.htm\">GetFoldersInFolder, get all the names of the folders in a folder</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppGetPath.htm\">GetPath, get a file's path</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppIsFolder.htm\">IsFolder, check if a path is a folder</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppIsRegularFile.htm\">IsRegularFile, check if a file is a regular file</a>",
        "  </li>",
        "",
        "  <li>",
        "    <img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppReadDoubleFromFile.htm\">ReadDoubleFromFile, read a double from file</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppReadDoubleFromFile.htm\">Read a double from file, ReadDoubleFromFile</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppFileToVector.htm\">Read a file in a std::vector, FileToVector</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppFileToStringList.htm\">Read a file in a TStringList, FileToStringList</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppRemoveExtension.htm\">Remove the extension of a filename, RemoveExtension</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppRemoveExtension.htm\">RemoveExtension, remove the extension of a filename</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppRunOtherProgram.htm\">Run another program and use its output</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppSaveContainer.htm\">Save a container to file, SaveContainer</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppSaveContainer.htm\">SaveContainer, save a container to file</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"CppSimplifyPath.htm\">SimplifyPath, simplify a path</a>",
        "  </li>",
        "</ol>"
      }
    }
  );

  m.push_back(
    { "CppFuzzy_equal_to",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppFuzzy_equal_to.htm\">fuzzy_equal_to</a> is a <a href=\"CppPredicate.htm\">predicate</a>",
        "  to test two <a href=\"CppDouble.htm\">doubles</a> for equality with a certain tolerance.",
        "  A tolerance of 0.0 denotes that an exact match is requested.",
        "</p>"
      }
    }
  );
  m.push_back(
    { "CppGaborFilter",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppGaborFilter.htm\">GaborFilter</a> is a",
        "  <a href=\"CppClass.htm\">class</a> for a",
        "  Gabor filter.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "CppGaborFilterWidget",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppGaborFilterWidget.htm\">GaborFilterWidget</a> is a",
        "  <a href=\"CppClass.htm\">class</a> for a",
        "  <a href=\"CppGaborFilter.htm\">Gabor filter</a> <a href=\"CppWidget.htm\">widget</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "CppGetCombinations",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppGetCombinations.htm\">GetCombinations</a> is a <a href=\"CppCodeSnippets.htm\">code snippet</a>",
        "  to obtain all combinations of a <a href=\"CppVector.htm\">std::vector</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppGetPermutations.htm\">GetPermutations</a> is a <a href=\"CppCodeSnippets.htm\">code snippet</a>",
        "  to obtain all permutations of a <a href=\"CppVector.htm\">std::vector</a>.",
        "</p>"
      }
    }
  );


  m.push_back(
    { "CppGetExtension",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppGetExtension.htm\">GetExtension</a> is a",
        "  <a href=\"CppFileIo.htm\">file I/O</a> <a href=\"CppString.htm\">std::string</a>",
        "  <a href=\"CppCodeSnippets.htm\">code snippet</a> to get a filename's extension.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  Thanks goes to Curtis Krauskopf, who supported me to improve the",
        "  (terrible and error-prone) STL version GetExtension.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppGetExtension.zip\">Download the Qt Creator project 'CppGetExtension' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppGetFilesInFolder",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppGetFilesInFolder.htm\">GetFilesInFolder</a> is a <a href=\"CppFileIo.htm\">file I/O</a> <a href=\"CppCodeSnippets.htm\">code snippet</a> to obtain all filenames in a folder.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppGetFilesInFolder.zip\">Download the Qt Creator project 'CppGetFilesInFolder' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppGetPath",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppGetPath.htm\">GetPath</a> is a <a href=\"CppFileIo.htm\">file I/O</a> <a href=\"CppString.htm\">std::string</a> <a href=\"CppCodeSnippets.htm\">code snippet</a> to get a filename's path.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppGetPath.zip\">Download the Qt Creator project 'CppGetPath' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppGetPermutations",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppGetPermutations.htm\">GetPermutations</a> is a <a href=\"CppCodeSnippets.htm\">code snippet</a>",
        "  to obtain all permutations of a <a href=\"CppVector.htm\">std::vector</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppGetCombinations.htm\">GetCombinations</a> is a <a href=\"CppCodeSnippets.htm\">code snippet</a>",
        "  to obtain all combinations of a <a href=\"CppVector.htm\">std::vector</a>.",
        "</p>"
      }
    }
  );
  m.push_back(
    { "CppGetRegexMatches",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppGetRegexMatches.htm\">GetRegexMatches</a> is a <a href=\"CppRegex.htm\">Regex</a> <a href=\"CppCodeSnippets.htm\">code snippet</a> to obtain",
        "all <a href=\"CppString.htm\">std::strings</a> in a <a href=\"CppString.htm\">std::string</a> that satisfy a regular expression.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppGetRegexMatches.htm\">GetRegexMatches</a> is demonstrated in the <a href=\"Tools.htm\">tool</a> <a href=\"ToolRegexTester.htm\">RegexTester</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppGetRegexMatches.zip\">Download the Qt Creator project 'GetRegexMatches' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppGetTime",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppGetTime.htm\">GetTime</a> is a <a href=\"CppTime.htm\">time</a>",
        "  <a href=\"CppCodeSnippets.htm\">code snippet</a> to obtain now's time.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppGetTime.htm\">GetTime</a> can depend on two different <a href=\"CppLibrary.htm\">libraries</a>:",
        "</p>",
        "<ul>",
        "  <li><img src=\"PicBoost.png\" alt=\"Boost\"> <a href=\"CppBoost.htm\">Boost</a> version of <a href=\"CppGetTime.htm\">GetTime</a></li>",
        "  <li><img src=\"PicStl.png\" alt=\"STL\"> <a href=\"CppStl.htm\">STL</a> version of <a href=\"CppGetTime.htm\">GetTime</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppGetTxtFilesInFolder",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppGetTxtFilesInFolder.htm\">GetFilesInFolder</a> is a <a href=\"CppFileIo.htm\">file I/O</a> <a href=\"CppCodeSnippets.htm\">code snippet</a> to obtain all text filenames in a folder.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppGetTxtFilesInFolder.zip\">Download the Qt Creator project 'CppGetTxtFilesInFolder' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppGnuplotInterface",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppGnuplotInterface.htm\">GnuplotInterface</a> is a <a href=\"CppClass.htm\">class</a> ",
        "that enables the user to easily plot values in <a href=\"CppGnuplot.htm\">Gnuplot</a>. It handles ",
        "both the connection to <a href=\"CppGnuplot.htm\">Gnuplot</a> and performs the window management as well. ",
        "It creates a text-file in which the location of the <a href=\"CppGnuplot.htm\">Gnuplot</a> executable can ",
        "be entered (without recompiling the program).</p>",
        "<p>&nbsp;</p>",
        "<p>The <a href=\"Tools.htm\">tool</a> <a href=\"ToolTestGnuplotInterface.htm\">TestGnuplotInterface</a> tests ",
        "the <a href=\"CppGnuplotInterface.htm\">GnuplotInterface</a> <a href=\"CppClass.htm\">class</a>.",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"Note: only tested under MacOS\" border = \"1\"><tr><td><code>",
        "I only got this interface to work under MacOS<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>The one function that this <a href=\"CppClass.htm\">class</a> is built around is the popen function. This is a non-standard function to open a pipe. If this function is unknown under your programming environment, try either std::popen, std::_popen, std::__popen, popen, _popen or __popen.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppGnuplotInterface.png\">View a screenshot of a graph created with Gnuplot interface</a>. Thanks to Roger Wehage for submitting this image and allowing me to use it.</li>",
        "  <li><a href=\"CppGnuplotInterfaceSource.zip\">Download the 'Gnuplot Interface' source code (zip)</a>.</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Known <a href=\"CppCompileError.htm\">compile errors</a></h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppCompileError_popenIsNotAmemberOfStd.htm\">_popen is not a member of std</a></li>",
        "  <li><a href=\"CppCompileErrorCLK_TCKwasNotDeclaredInThisScope.htm\">CLK_TCK was not declared in this scope</a></li>",
        "  <li><a href=\"CppCompileErrorDuplicateSymbol.htm\">Duplicate symbol Gnuplot::SetLineStyles()</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppGprofQtCreatorExample1",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppGprofQtCreatorExample1.htm\">Qt Creator gprof example 1: profiling a simple console application in Qt Creator, using Build Settings</a> is a",
        "<a href=\"CppGprof.htm\">gprof</a> <a href=\"CppExample.htm\">example</a> that shows how to profile a simple console application in  <a href=\"CppQt.htm\">Qt Creator</a>,",
        "using the Build Settings.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppGprofQtCreatorExample1.zip\">Download the Qt Project of 'CppGprofQtCreatorExample1' (zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>Here follows a step-by-step guide to use <a href=\"CppGprof.htm\">gprof</a> to do the profiling of a simple <a href=\"CppQt.htm\">Qt Creator</a> project:</p>",
        "<p>&nbsp;</p>",
        "<ol>",
        "  <li>Go to 'Projects -> Build Settings' and add a custom Build step. Fill in the information as in the screenshot below</li>",
        "  <li><a href=\"CppGprofQtCreatorExample1_1.png\">View screenshot</a></li>",
        "  <li>View your project folder. There will be few files</li>",
        "  <li><a href=\"CppGprofQtCreatorExample1_2.png\">View screenshot</a></li>",
        "  <li>Run the program. The executable 'profile_main' has been created in your project folder</li>",
        "  <li><a href=\"CppGprofQtCreatorExample1_3.png\">View screenshot</a></li>",
        "  <li>Run 'profile_main' and the file 'gmon.out' is created</li>",
        "  <li><a href=\"CppGprofQtCreatorExample1_4.png\">View screenshot</a></li>",
        "  <li>Start a Terminal, go to the project folder and use the command 'gprof profile_main > profile.txt'</li>",
        "  <li><a href=\"CppGprofQtCreatorExample1_5.png\">View screenshot</a></li>",
        "  <li>The file 'profile.txt' will be created</li>",
        "  <li><a href=\"CppGprofQtCreatorExample1_6.png\">View screenshot</a></li>",
        "  <li>The file 'profile.txt' will contain the profiling information</li>",
        "</ol>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Profiling results</h2>",
        "<p>&nbsp;</p>",
        "<p>Here I show the results comparing the five functions, copied from the results file:</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"Profiling result\"border = \"1\"><tr><td><code>",
        "Flat profile:<br/>",
        "<br/>",
        "&nbsp;&nbsp;%&nbsp;&nbsp; cumulative&nbsp;&nbsp; self&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;self&nbsp;&nbsp;&nbsp;&nbsp; total<br/>",
        " time&nbsp;&nbsp; seconds&nbsp;&nbsp; seconds&nbsp;&nbsp;&nbsp;&nbsp;calls&nbsp;&nbsp;ms/call&nbsp;&nbsp;ms/call&nbsp;&nbsp;name<br/>",
        " 13.59&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1.54&nbsp;&nbsp;&nbsp;&nbsp; 0.28&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1&nbsp;&nbsp; 280.00&nbsp;&nbsp; 700.00&nbsp;&nbsp;void BubbleSort&lt;int&gt;(std::vector&lt;int, std::allocator&lt;int&gt; &gt;&amp;)<br/>",
        " 12.14&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1.79&nbsp;&nbsp;&nbsp;&nbsp; 0.25&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1&nbsp;&nbsp; 250.00&nbsp;&nbsp; 670.00&nbsp;&nbsp;void InsertionSort&lt;int&gt;(std::vector&lt;int, std::allocator&lt;int&gt; &gt;&amp;)<br/>",
        " 11.65&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2.03&nbsp;&nbsp;&nbsp;&nbsp; 0.24&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1&nbsp;&nbsp; 240.00&nbsp;&nbsp; 660.00&nbsp;&nbsp;void SelectionSort&lt;int&gt;(std::vector&lt;int, std::allocator&lt;int&gt; &gt;&amp;)<br/>",
        "&nbsp;&nbsp;0.00&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2.06&nbsp;&nbsp;&nbsp;&nbsp; 0.00&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1&nbsp;&nbsp;&nbsp;&nbsp; 0.00&nbsp;&nbsp;&nbsp;&nbsp;24.98&nbsp;&nbsp;void SortVector&lt;int&gt;(std::vector&lt;int, std::allocator&lt;int&gt; &gt;&amp;)<br/>",
        "&nbsp;&nbsp;0.00&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2.06&nbsp;&nbsp;&nbsp;&nbsp; 0.00&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1&nbsp;&nbsp;&nbsp;&nbsp; 0.00&nbsp;&nbsp;&nbsp;&nbsp; 5.02&nbsp;&nbsp;CreateShuffledVector(unsigned int)<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>Conclusion: as expected, SortVector (a QuickSort) is by far the quickest <a href=\"CppSort.htm\">sorting</a> <a href=\"CppAlgorithm.htm\">algorithm</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppGprofQtCreatorExample2",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppGprofQtCreatorExample2.htm\">gprof example 2: profiling a simple console application in Qt Creator, using Qt project file</a> is a",
        "<a href=\"CppGprof.htm\">gprof</a> <a href=\"CppExample.htm\">example</a> to  profile a simple console application under <a href=\"CppQt.htm\">Qt Creator</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppGprofQtCreatorExample2.zip\">Download the Qt Project of 'CppGprofQtCreatorExample2' (zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>To be able to use <a href=\"CppGprof.htm\">gprof</a> to profile a project, add the following lines to a ",
        "<a href=\"CppQtProjectFile.htm\">Qt project file</a>:</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"Qt Creator project file\" border = \"1\"><tr><td><code>",
        "QMAKE_CXXFLAGS_DEBUG += -pg<br/>",
        "QMAKE_LFLAGS_DEBUG += -pg<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>then, for a terminal, type the following lines:</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"Terminal commands needed for gprof\"border = \"1\"><tr><td><code>",
        "qmake -config debug<br/>",
        "make clean<br/>",
        "make<br/>",
        "./Cpp<a href=\"CppGprof.htm\">Gprof</a><a href=\"CppQtCreator.htm\">QtCreator</a>Example2<br/>",
        "<a href=\"CppGprof.htm\">gprof</a> Cpp<a href=\"CppGprof.htm\">Gprof</a><a href=\"CppQtCreator.htm\">QtCreator</a>Example2 &gt; <a href=\"CppGprof.htm\">gprof</a>.txt<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>Or easier, run the script profile.sh:</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"Start profiling command\" border = \"1\"><tr><td><code>",
        "./profile.sh<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Profiling results</h2>",
        "<p>&nbsp;</p>",
        "<p>Here I show the results comparing the five functions, copied from the results file:</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"Profiling result\" border = \"1\"><tr><td><code>",
        "Each sample counts as 0.01 seconds.<br/>",
        "&nbsp;&nbsp;<a href=\"CppOperatorModulus.htm\">%</a>&nbsp;&nbsp; cumulative&nbsp;&nbsp; self&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;self&nbsp;&nbsp;&nbsp;&nbsp; total&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; <br/>",
        " <a href=\"CppTime.htm\">time</a>&nbsp;&nbsp; seconds&nbsp;&nbsp; seconds&nbsp;&nbsp;&nbsp;&nbsp;calls&nbsp;&nbsp; s/call&nbsp;&nbsp; s/call&nbsp;&nbsp;name&nbsp;&nbsp;&nbsp;&nbsp;<br/>",
        " 12.51&nbsp;&nbsp;&nbsp;&nbsp;172.28&nbsp;&nbsp;&nbsp;&nbsp;29.52&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1&nbsp;&nbsp;&nbsp;&nbsp;29.52&nbsp;&nbsp;&nbsp;&nbsp;77.11&nbsp;&nbsp;<b><a href=\"CppVoid.htm\">void</a></b> <a href=\"CppBubbleSort.htm\">BubbleSort</a>&lt;<b><a href=\"CppInt.htm\">int</a></b>&gt;(<a href=\"CppVector.htm\">std::vector</a>&lt;<b><a href=\"CppInt.htm\">int</a></b>, <a href=\"CppStd.htm\">std</a>::allocator&lt;<b><a href=\"CppInt.htm\">int</a></b>&gt; &gt;&amp;)<br/>",
        " 12.39&nbsp;&nbsp;&nbsp;&nbsp;201.51&nbsp;&nbsp;&nbsp;&nbsp;29.23&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1&nbsp;&nbsp;&nbsp;&nbsp;29.23&nbsp;&nbsp;&nbsp;&nbsp;76.82&nbsp;&nbsp;<b><a href=\"CppVoid.htm\">void</a></b> <a href=\"CppInsertionSort.htm\">InsertionSort</a>&lt;<b><a href=\"CppInt.htm\">int</a></b>&gt;(<a href=\"CppVector.htm\">std::vector</a>&lt;<b><a href=\"CppInt.htm\">int</a></b>, <a href=\"CppStd.htm\">std</a>::allocator&lt;<b><a href=\"CppInt.htm\">int</a></b>&gt; &gt;&amp;)<br/>",
        " 12.06&nbsp;&nbsp;&nbsp;&nbsp;229.97&nbsp;&nbsp;&nbsp;&nbsp;28.45&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1&nbsp;&nbsp;&nbsp;&nbsp;28.45&nbsp;&nbsp;&nbsp;&nbsp;76.04&nbsp;&nbsp;<b><a href=\"CppVoid.htm\">void</a></b> <a href=\"CppSelectionSort.htm\">SelectionSort</a>&lt;<b><a href=\"CppInt.htm\">int</a></b>&gt;(<a href=\"CppVector.htm\">std::vector</a>&lt;<b><a href=\"CppInt.htm\">int</a></b>, <a href=\"CppStd.htm\">std</a>::allocator&lt;<b><a href=\"CppInt.htm\">int</a></b>&gt; &gt;&amp;)<br/>",
        "&nbsp;&nbsp;0.00&nbsp;&nbsp;&nbsp;&nbsp;235.89&nbsp;&nbsp;&nbsp;&nbsp; 0.00&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1&nbsp;&nbsp;&nbsp;&nbsp; 0.00&nbsp;&nbsp;&nbsp;&nbsp; 0.52&nbsp;&nbsp;<b><a href=\"CppVoid.htm\">void</a></b> <a href=\"CppSortVector.htm\">SortVector</a>&lt;<b><a href=\"CppInt.htm\">int</a></b>&gt;(<a href=\"CppVector.htm\">std::vector</a>&lt;<b><a href=\"CppInt.htm\">int</a></b>, <a href=\"CppStd.htm\">std</a>::allocator&lt;<b><a href=\"CppInt.htm\">int</a></b>&gt; &gt;&amp;)<br/>",
        "&nbsp;&nbsp;0.00&nbsp;&nbsp;&nbsp;&nbsp;235.89&nbsp;&nbsp;&nbsp;&nbsp; 0.00&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1&nbsp;&nbsp;&nbsp;&nbsp; 0.00&nbsp;&nbsp;&nbsp;&nbsp; 0.09&nbsp;&nbsp;CreateShuffledVector(<b><a href=\"CppUnsigned.htm\">unsigned</a></b> <b><a href=\"CppInt.htm\">int</a></b>)<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>Conclusion: as expected, SortVector (a QuickSort) is by far the quickest <a href=\"CppSort.htm\">sorting</a> <a href=\"CppAlgorithm.htm\">algorithm</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppHeaderFileExample1",
      {
         "<p><a href=\"CppHeaderFileExample1.htm\">Header file example 1</a> shows what does and what does not belong in a header file [1].</p>",
         "<p>&nbsp;</p>",
         "<ul>",
         "  <li><a href=\"CppHeaderFileExample1.zip\">Download the Qt Creator project 'CppHeaderFileExample1' (zip)</a></li>",
         "</ul>",
         "<p>&nbsp;</p>",
         "<p>&nbsp;</p>",
         "<p>&nbsp;</p>",
         "<p>&nbsp;</p>",
         "<p>&nbsp;</p>",
         "<h2><a href=\"CppReferences.htm\">References</a></h2>",
         "<p>&nbsp;</p>",
         "<ol>",
         "  <li><!--  1 --> <a href=\"CppJohnLakos.htm\">John Lakos</a>. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Chapter 1.1.3, figure 1-3, page 28</li>",
         "</ol>",
         "<p>&nbsp;</p>)"

      }
    }
  );
  m.push_back(
    { "CppHelloBoostLexical_CastQtCreatorCygwin",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicCygwin.png\" alt=\"Cygwin\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostLexical_CastQtCreatorCygwin.htm\">Hello Boost.Lexical_cast using Qt Creator under Cygwin</a>",
        "  is a <a href=\"CppHelloBoostLexical_Cast.htm\">Hello Boost.Lexical_cast</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostLexical_CastQtCreatorCygwin.zip\">Download the Qt Creator project 'CppHelloBoostLexical_CastQtCreatorCygwin' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostLexical_CastQtCreatorLubuntu",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostLexical_CastQtCreatorLubuntu.htm\">Hello Boost.Lexical_cast using Qt Creator under Lubuntu</a>",
        "  is a <a href=\"CppHelloBoostLexical_Cast.htm\">Hello Boost.Lexical_cast</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostLexical_CastQtCreatorLubuntu.zip\">Download the Qt Creator project 'CppHelloBoostLexical_CastQtCreatorLubuntu' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostLexical_CastQtCreatorLubuntuToWindows",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicTo.png\" alt=\"To\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostLexical_CastQtCreatorLubuntuToWindows.htm\">Hello Boost.Lexical_cast using Qt Creator under Lubuntu, crosscompiled to Windows</a>",
        "  is a <a href=\"CppHelloBoostLexical_Cast.htm\">Hello Boost.Lexical_cast</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostLexical_CastQtCreatorLubuntuToWindows.zip\">Download the Qt Creator project 'CppHelloBoostLexical_CastQtCreatorLubuntuToWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostLexical_CastQtCreatorSliTaz",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicSliTaz.png\" alt=\"SliTaz\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostLexical_CastQtCreatorSliTaz.htm\">Hello Boost.Lexical_cast using Qt Creator under SliTaz</a>",
        "  is a <a href=\"CppHelloBoostLexical_Cast.htm\">Hello Boost.Lexical_cast</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostLexical_CastQtCreatorSliTaz.zip\">Download the Qt Creator project 'CppHelloBoostLexical_CastQtCreatorSliTaz' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostLexical_CastQt4QtCreatorLubuntuToWindows",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQt4.png\" alt=\"Qt4\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicTo.png\" alt=\"To\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostLexical_CastQt4QtCreatorLubuntuToWindows.htm\">Hello Boost.Lexical_cast using Qt4 under Qt Creator under Lubuntu, crosscompiled to Windows</a>",
        "  is a <a href=\"CppHelloBoostLexical_Cast.htm\">Hello Boost.Lexical_cast</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostLexical_CastQt4QtCreatorLubuntuToWindows.zip\">Download the Qt Creator project 'CppHelloBoostLexical_CastQt4QtCreatorLubuntuToWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostLexical_CastQt5QtCreatorLubuntuToWindows",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQt5.png\" alt=\"Qt5\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicTo.png\" alt=\"To\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostLexical_CastQt5QtCreatorLubuntuToWindows.htm\">Hello Boost.Lexical_cast using Qt5 under Qt Creator under Lubuntu, crosscompiled to Windows</a>",
        "  is a <a href=\"CppHelloBoostLexical_Cast.htm\">Hello Boost.Lexical_cast</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostLexical_CastQt5QtCreatorLubuntuToWindows.zip\">Download the Qt Creator project 'CppHelloBoostLexical_CastQt5QtCreatorLubuntuToWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostLexical_CastQtCreatorWindows",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostLexical_CastQtCreatorWindows.htm\">Hello Boost.Lexical_cast using Qt Creator under Windows</a>",
        "  is a <a href=\"CppHelloBoostLexical_Cast.htm\">Hello Boost.Lexical_cast</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostLexical_CastQtCreatorWindows.zip\">Download the Qt Creator project 'CppHelloBoostLexical_CastQtCreatorWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostQtCreatorLubuntu",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoost.htm\">Hello Boost</a> is an extension of <a href=\"CppHelloWorld.htm\">Hello World</a>.",
        "  Like <a href=\"CppHelloWorld.htm\">Hello World</a>, <a href=\"CppHelloBoost.htm\">Hello Boost</a> is a simple console",
        "  application. <a href=\"CppHelloBoost.htm\">Hello Boost</a>, however, also requires multiple <a href=\"CppBoost.htm\">Boost</a> ",
        "  <a href=\"CppLibrary.htm\">libraries</a> to <a href=\"CppLink.htm\">link</a> against.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostQtCreatorLubuntu.zip\">Download the Qt Creator project 'CppHelloBoostQtCreatorLubuntu' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostRegexQtCreatorCygwin",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicCygwin.png\" alt=\"Cygwin\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostRegexQtCreatorCygwin.htm\">Hello Boost.Regex using Qt Creator under Cygwin</a>",
        "  is a <a href=\"CppHelloBoostRegex.htm\">Hello Boost.Regex</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostRegexQtCreatorCygwin.zip\">Download the Qt Creator project 'CppHelloBoostRegexQtCreatorCygwin' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostRegexQtCreatorLubuntu",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostRegexQtCreatorLubuntu.htm\">Hello Boost.Regex using Qt Creator under Lubuntu</a>",
        "  is a <a href=\"CppHelloBoostRegex.htm\">Hello Boost.Regex</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostRegexQtCreatorLubuntu.zip\">Download the Qt Creator project 'CppHelloBoostRegexQtCreatorLubuntu' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostRegexQtCreatorLubuntuToWindows",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicTo.png\" alt=\"To\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostRegexQtCreatorLubuntuToWindows.htm\">Hello Boost.Regex using Qt Creator under Lubuntu, crosscompiled to Windows</a>",
        "  is a <a href=\"CppHelloBoostRegex.htm\">Hello Boost.Regex</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostRegexQtCreatorLubuntuToWindows.zip\">Download the Qt Creator project 'CppHelloBoostRegexQtCreatorLubuntuToWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostRegexQtCreatorSliTaz",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicSliTaz.png\" alt=\"SliTaz\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostRegexQtCreatorSliTaz.htm\">Hello Boost.Regex using Qt Creator under SliTaz</a>",
        "  is a <a href=\"CppHelloBoostRegex.htm\">Hello Boost.Regex</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostRegexQtCreatorSliTaz.zip\">Download the Qt Creator project 'CppHelloBoostRegexQtCreatorSliTaz' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostRegexQt4QtCreatorLubuntuToWindows",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQt4.png\" alt=\"Qt4\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicTo.png\" alt=\"To\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostRegexQt4QtCreatorLubuntuToWindows.htm\">Hello Boost.Regex using Qt4 under Qt Creator under Lubuntu, crosscompiled to Windows</a>",
        "  is a <a href=\"CppHelloBoostRegex.htm\">Hello Boost.Regex</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostRegexQt4QtCreatorLubuntuToWindows.zip\">Download the Qt Creator project 'CppHelloBoostRegexQt4QtCreatorLubuntuToWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostRegexQt5QtCreatorLubuntuToWindows",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQt5.png\" alt=\"Qt5\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicTo.png\" alt=\"To\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostRegexQt5QtCreatorLubuntuToWindows.htm\">Hello Boost.Regex using Qt5 under Qt Creator under Lubuntu, crosscompiled to Windows</a>",
        "  is a <a href=\"CppHelloBoostRegex.htm\">Hello Boost.Regex</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostRegexQt5QtCreatorLubuntuToWindows.zip\">Download the Qt Creator project 'CppHelloBoostRegexQt5QtCreatorLubuntuToWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostRegexQtCreatorWindows",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostRegexQtCreatorWindows.htm\">Hello Boost.Regex using Qt Creator under Windows</a>",
        "  is a <a href=\"CppHelloBoostRegex.htm\">Hello Boost.Regex</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostRegexQtCreatorWindows.zip\">Download the Qt Creator project 'CppHelloBoostRegexQtCreatorWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostSignalsQtCreatorCygwin",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicCygwin.png\" alt=\"Cygwin\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostSignalsQtCreatorCygwin.htm\">Hello Boost.Signals using Qt Creator under Cygwin</a>",
        "  is a <a href=\"CppHelloBoostSignals.htm\">Hello Boost.Signals</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostSignalsQtCreatorCygwin.zip\">Download the Qt Creator project 'CppHelloBoostSignalsQtCreatorCygwin' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostSignalsQtCreatorLubuntu",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostSignalsQtCreatorLubuntu.htm\">Hello Boost.Signals using Qt Creator under Lubuntu</a>",
        "  is a <a href=\"CppHelloBoostSignals.htm\">Hello Boost.Signals</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostSignalsQtCreatorLubuntu.zip\">Download the Qt Creator project 'CppHelloBoostSignalsQtCreatorLubuntu' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostSignalsQtCreatorLubuntuToWindows",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicTo.png\" alt=\"To\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostSignalsQtCreatorLubuntuToWindows.htm\">Hello Boost.Signals using Qt Creator under Lubuntu, crosscompiled to Windows</a>",
        "  is a <a href=\"CppHelloBoostSignals.htm\">Hello Boost.Signals</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostSignalsQtCreatorLubuntuToWindows.zip\">Download the Qt Creator project 'CppHelloBoostSignalsQtCreatorLubuntuToWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostSignalsQtCreatorSliTaz",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicSliTaz.png\" alt=\"SliTaz\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostSignalsQtCreatorSliTaz.htm\">Hello Boost.Signals using Qt Creator under SliTaz</a>",
        "  is a <a href=\"CppHelloBoostSignals.htm\">Hello Boost.Signals</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostSignalsQtCreatorSliTaz.zip\">Download the Qt Creator project 'CppHelloBoostSignalsQtCreatorSliTaz' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostSignalsQt4QtCreatorLubuntuToWindows",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQt4.png\" alt=\"Qt4\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicTo.png\" alt=\"To\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostSignalsQt4QtCreatorLubuntuToWindows.htm\">Hello Boost.Signals using Qt4 under Qt Creator under Lubuntu, crosscompiled to Windows</a>",
        "  is a <a href=\"CppHelloBoostSignals.htm\">Hello Boost.Signals</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostSignalsQt4QtCreatorLubuntuToWindows.zip\">Download the Qt Creator project 'CppHelloBoostSignalsQt4QtCreatorLubuntuToWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostSignalsQt5QtCreatorLubuntuToWindows",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQt5.png\" alt=\"Qt5\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicTo.png\" alt=\"To\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostSignalsQt5QtCreatorLubuntuToWindows.htm\">Hello Boost.Signals using Qt5 under Qt Creator under Lubuntu, crosscompiled to Windows</a>",
        "  is a <a href=\"CppHelloBoostSignals.htm\">Hello Boost.Signals</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostSignalsQt5QtCreatorLubuntuToWindows.zip\">Download the Qt Creator project 'CppHelloBoostSignalsQt5QtCreatorLubuntuToWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostSignalsQtCreatorWindows",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostSignalsQtCreatorWindows.htm\">Hello Boost.Signals using Qt Creator under Windows</a>",
        "  is a <a href=\"CppHelloBoostSignals.htm\">Hello Boost.Signals</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostSignalsQtCreatorWindows.zip\">Download the Qt Creator project 'CppHelloBoostSignalsQtCreatorWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostUblasQtCreatorCygwin",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicCygwin.png\" alt=\"Cygwin\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostUblasQtCreatorCygwin.htm\">Hello Boost.uBLAS using Qt Creator under Cygwin</a>",
        "  is a <a href=\"CppHelloBoostUblas.htm\">Hello Boost.uBLAS</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostUblasQtCreatorCygwin.zip\">Download the Qt Creator project 'CppHelloBoostUblasQtCreatorCygwin' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostUblasQtCreatorLubuntu",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostUblasQtCreatorLubuntu.htm\">Hello Boost.uBLAS using Qt Creator under Lubuntu</a>",
        "  is a <a href=\"CppHelloBoostUblas.htm\">Hello Boost.uBLAS</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostUblasQtCreatorLubuntu.zip\">Download the Qt Creator project 'CppHelloBoostUblasQtCreatorLubuntu' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostUblasQtCreatorLubuntuToWindows",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicTo.png\" alt=\"To\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostUblasQtCreatorLubuntuToWindows.htm\">Hello Boost.uBLAS using Qt Creator under Lubuntu, crosscompiled to Windows</a>",
        "  is a <a href=\"CppHelloBoostUblas.htm\">Hello Boost.uBLAS</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostUblasQtCreatorLubuntuToWindows.zip\">Download the Qt Creator project 'CppHelloBoostUblasQtCreatorLubuntuToWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostUblasQtCreatorSliTaz",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicSliTaz.png\" alt=\"SliTaz\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostUblasQtCreatorSliTaz.htm\">Hello Boost.uBLAS using Qt Creator under SliTaz</a>",
        "  is a <a href=\"CppHelloBoostUblas.htm\">Hello Boost.uBLAS</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostUblasQtCreatorSliTaz.zip\">Download the Qt Creator project 'CppHelloBoostUblasQtCreatorSliTaz' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostUblasQt4QtCreatorLubuntuToWindows",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQt4.png\" alt=\"Qt4\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicTo.png\" alt=\"To\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostUblasQt4QtCreatorLubuntuToWindows.htm\">Hello Boost.uBLAS using Qt4 under Qt Creator under Lubuntu, crosscompiled to Windows</a>",
        "  is a <a href=\"CppHelloBoostUblas.htm\">Hello Boost.uBLAS</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>"
        "  <li><a href=\"CppHelloBoostUblasQt4QtCreatorLubuntuToWindows.zip\">Download the Qt Creator project 'CppHelloBoostUblasQt4QtCreatorLubuntuToWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostUblasQt5QtCreatorLubuntuToWindows",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQt5.png\" alt=\"Qt5\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicTo.png\" alt=\"To\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostUblasQt5QtCreatorLubuntuToWindows.htm\">Hello Boost.uBLAS using Qt5 under Qt Creator under Lubuntu, crosscompiled to Windows</a>",
        "  is a <a href=\"CppHelloBoostUblas.htm\">Hello Boost.uBLAS</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostUblasQt5QtCreatorLubuntuToWindows.zip\">Download the Qt Creator project 'CppHelloBoostUblasQt5QtCreatorLubuntuToWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostUblasQtCreatorWindows",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostUblasQtCreatorWindows.htm\">Hello Boost.uBLAS using Qt Creator under Windows</a>",
        "  is a <a href=\"CppHelloBoostUblas.htm\">Hello Boost.uBLAS</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostUblasQtCreatorWindows.zip\">Download the Qt Creator project 'CppHelloBoostUblasQtCreatorWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostXpressiveQtCreatorCygwin",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicCygwin.png\" alt=\"Cygwin\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostXpressiveQtCreatorCygwin.htm\">Hello Boost.Xpressive using Qt Creator under Cygwin</a>",
        "  is a <a href=\"CppHelloBoostXpressive.htm\">Hello Boost.Xpressive</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostXpressiveQtCreatorCygwin.zip\">Download the Qt Creator project 'CppHelloBoostXpressiveQtCreatorCygwin' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostXpressiveQtCreatorLubuntu",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostXpressiveQtCreatorLubuntu.htm\">Hello Boost.Xpressive using Qt Creator under Lubuntu</a>",
        "  is a <a href=\"CppHelloBoostXpressive.htm\">Hello Boost.Xpressive</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostXpressiveQtCreatorLubuntu.zip\">Download the Qt Creator project 'CppHelloBoostXpressiveQtCreatorLubuntu' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostXpressiveQtCreatorLubuntuToWindows",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicTo.png\" alt=\"To\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostXpressiveQtCreatorLubuntuToWindows.htm\">Hello Boost.Xpressive using Qt Creator under Lubuntu, crosscompiled to Windows</a>",
        "  is a <a href=\"CppHelloBoostXpressive.htm\">Hello Boost.Xpressive</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostXpressiveQtCreatorLubuntuToWindows.zip\">Download the Qt Creator project 'CppHelloBoostXpressiveQtCreatorLubuntuToWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostXpressiveQtCreatorSliTaz",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicSliTaz.png\" alt=\"SliTaz\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostXpressiveQtCreatorSliTaz.htm\">Hello Boost.Xpressive using Qt Creator under SliTaz</a>",
        "  is a <a href=\"CppHelloBoostXpressive.htm\">Hello Boost.Xpressive</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostXpressiveQtCreatorSliTaz.zip\">Download the Qt Creator project 'CppHelloBoostXpressiveQtCreatorSliTaz' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostXpressiveQt4QtCreatorLubuntuToWindows",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQt4.png\" alt=\"Qt4\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicTo.png\" alt=\"To\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostXpressiveQt4QtCreatorLubuntuToWindows.htm\">Hello Boost.Xpressive using Qt4 under Qt Creator under Lubuntu, crosscompiled to Windows</a>",
        "  is a <a href=\"CppHelloBoostXpressive.htm\">Hello Boost.Xpressive</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostXpressiveQt4QtCreatorLubuntuToWindows.zip\">Download the Qt Creator project 'CppHelloBoostXpressiveQt4QtCreatorLubuntuToWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostXpressiveQt5QtCreatorLubuntuToWindows",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQt5.png\" alt=\"Qt5\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicTo.png\" alt=\"To\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostXpressiveQt5QtCreatorLubuntuToWindows.htm\">Hello Boost.Xpressive using Qt5 under Qt Creator under Lubuntu, crosscompiled to Windows</a>",
        "  is a <a href=\"CppHelloBoostXpressive.htm\">Hello Boost.Xpressive</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostXpressiveQt5QtCreatorLubuntuToWindows.zip\">Download the Qt Creator project 'CppHelloBoostXpressiveQt5QtCreatorLubuntuToWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloBoostXpressiveQtCreatorWindows",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloBoostXpressiveQtCreatorWindows.htm\">Hello Boost.Xpressive using Qt Creator under Windows</a>",
        "  is a <a href=\"CppHelloBoostXpressive.htm\">Hello Boost.Xpressive</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloBoostXpressiveQtCreatorWindows.zip\">Download the Qt Creator project 'CppHelloBoostXpressiveQtCreatorWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloCpp0xQtCreatorLubuntu",
      {
        "<p><img src=\"PicCpp0x.png\" alt=\"C++0x\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloCpp0xQtCreatorLubuntu.htm\">'HelloC++0x' using Qt Creator under Lubuntu</a>",
        "  is a <a href=\"CppHelloCpp0x.htm\">HelloC++0x</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloCpp0xQtCreatorLubuntu.zip\">Download the Qt Creator project 'CppHelloCpp0xQtCreatorLubuntu' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloCpp0xQtCreatorSliTaz",
      {
        "<p><img src=\"PicCpp0x.png\" alt=\"C++0x\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicSliTaz.png\" alt=\"SliTaz\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloCpp0xQtCreatorSliTaz.htm\">'HelloC++0x' using Qt Creator under SliTaz</a> is a ",
        "  <a href=\"CppHelloCpp0x.htm\">HelloC++0x</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloCpp0xQtCreatorSliTaz.zip\">Download the Qt Creator project 'CppHelloCpp0xQtCreatorSliTaz' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloCpp11QtCreatorCygwin",
      {
        "<p><img src=\"PicCpp11.png\" alt=\"C++11\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicCygwin.png\" alt=\"Cygwin\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloCpp11QtCreatorCygwin.htm\">Hello C++11 using Qt Creator under Cygwin</a>",
        "  is a <a href=\"CppHelloCpp11.htm\">Hello C++11</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloCpp11QtCreatorCygwin.zip\">Download the Qt Creator project 'CppHelloCpp11QtCreatorCygwin' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloCpp11QtCreatorLubuntu",
      {
        "<p><img src=\"PicCpp11.png\" alt=\"C++11\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloCpp11QtCreatorLubuntu.htm\">Hello C++11 using Qt Creator under Lubuntu</a>",
        "  is a <a href=\"CppHelloCpp11.htm\">Hello C++11</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloCpp11QtCreatorLubuntu.zip\">Download the Qt Creator project 'CppHelloCpp11QtCreatorLubuntu' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloCpp11QtCreatorLubuntuToWindows",
      {
        "<p><img src=\"PicCpp11.png\" alt=\"C++11\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicTo.png\" alt=\"To\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloCpp11QtCreatorLubuntuToWindows.htm\">Hello C++11 using Qt Creator under Lubuntu, crosscompiled to Windows</a>",
        "  is a <a href=\"CppHelloCpp11.htm\">Hello C++11</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloCpp11QtCreatorLubuntuToWindows.zip\">Download the Qt Creator project 'CppHelloCpp11QtCreatorLubuntuToWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloCpp11QtCreatorSliTaz",
      {
        "<p><img src=\"PicCpp11.png\" alt=\"C++11\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicSliTaz.png\" alt=\"SliTaz\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloCpp11QtCreatorSliTaz.htm\">Hello C++11 using Qt Creator under SliTaz</a>",
        "  is a <a href=\"CppHelloCpp11.htm\">Hello C++11</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloCpp11QtCreatorSliTaz.zip\">Download the Qt Creator project 'CppHelloCpp11QtCreatorSliTaz' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloCpp11Qt4QtCreatorLubuntuToWindows",
      {
        "<p><img src=\"PicCpp11.png\" alt=\"C++11\"/><img src=\"PicQt4.png\" alt=\"Qt4\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicTo.png\" alt=\"To\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloCpp11Qt4QtCreatorLubuntuToWindows.htm\">Hello C++11 using Qt4 under Qt Creator under Lubuntu, crosscompiled to Windows</a>",
        "  is a <a href=\"CppHelloCpp11.htm\">Hello C++11</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloCpp11Qt4QtCreatorLubuntuToWindows.zip\">Download the Qt Creator project 'CppHelloCpp11Qt4QtCreatorLubuntuToWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloCpp11Qt5QtCreatorLubuntuToWindows",
      {
        "<p><img src=\"PicCpp11.png\" alt=\"C++11\"/><img src=\"PicQt5.png\" alt=\"Qt5\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicTo.png\" alt=\"To\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloCpp11Qt5QtCreatorLubuntuToWindows.htm\">Hello C++11 using Qt5 under Qt Creator under Lubuntu, crosscompiled to Windows</a>",
        "  is a <a href=\"CppHelloCpp11.htm\">Hello C++11</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloCpp11Qt5QtCreatorLubuntuToWindows.zip\">Download the Qt Creator project 'CppHelloCpp11Qt5QtCreatorLubuntuToWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloCpp11QtCreatorWindows",
      {
        "<p><img src=\"PicCpp11.png\" alt=\"C++11\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloCpp11QtCreatorWindows.htm\">Hello C++11 using Qt Creator under Windows</a>",
        "  is a <a href=\"CppHelloCpp11.htm\">Hello C++11</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloCpp11QtCreatorWindows.zip\">Download the Qt Creator project 'CppHelloCpp11QtCreatorWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloQtQtCreatorCygwin",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicCygwin.png\" alt=\"Cygwin\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloQtQtCreatorCygwin.htm\">Hello Qt using Qt Creator under Cygwin</a>",
        "  is a <a href=\"CppHelloQt.htm\">Hello Qt</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloQtQtCreatorCygwin.zip\">Download the Qt Creator project 'CppHelloQtQtCreatorCygwin' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloQtQtCreatorLubuntu",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloQtQtCreatorLubuntu.htm\">Hello Qt using Qt Creator under Lubuntu</a>",
        "  is a <a href=\"CppHelloQt.htm\">Hello Qt</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloQtQtCreatorLubuntu.zip\">Download the Qt Creator project 'CppHelloQtQtCreatorLubuntu' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloQtQtCreatorLubuntuToWindows",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicTo.png\" alt=\"To\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloQtQtCreatorLubuntuToWindows.htm\">Hello Qt using Qt Creator under Lubuntu, crosscompiled to Windows</a>",
        "  is a <a href=\"CppHelloQt.htm\">Hello Qt</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloQtQtCreatorLubuntuToWindows.zip\">Download the Qt Creator project 'CppHelloQtQtCreatorLubuntuToWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloQtQtCreatorSliTaz",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicSliTaz.png\" alt=\"SliTaz\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloQtQtCreatorSliTaz.htm\">Hello Qt using Qt Creator under SliTaz</a>",
        "  is a <a href=\"CppHelloQt.htm\">Hello Qt</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloQtQtCreatorSliTaz.zip\">Download the Qt Creator project 'CppHelloQtQtCreatorSliTaz' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloQtQt4QtCreatorLubuntuToWindows",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQt4.png\" alt=\"Qt4\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicTo.png\" alt=\"To\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloQtQt4QtCreatorLubuntuToWindows.htm\">Hello Qt using Qt4 under Qt Creator under Lubuntu, crosscompiled to Windows</a>",
        "  is a <a href=\"CppHelloQt.htm\">Hello Qt</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloQtQt4QtCreatorLubuntuToWindows.zip\">Download the Qt Creator project 'CppHelloQtQt4QtCreatorLubuntuToWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloQtQt5QtCreatorLubuntuToWindows",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQt5.png\" alt=\"Qt5\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicTo.png\" alt=\"To\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloQtQt5QtCreatorLubuntuToWindows.htm\">Hello Qt using Qt5 under Qt Creator under Lubuntu, crosscompiled to Windows</a>",
        "  is a <a href=\"CppHelloQt.htm\">Hello Qt</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloQtQt5QtCreatorLubuntuToWindows.zip\">Download the Qt Creator project 'CppHelloQtQt5QtCreatorLubuntuToWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloQtQtCreatorWindows",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloQtQtCreatorWindows.htm\">Hello Qt using Qt Creator under Windows</a>",
        "  is a <a href=\"CppHelloQt.htm\">Hello Qt</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloQtQtCreatorWindows.zip\">Download the Qt Creator project 'CppHelloQtQtCreatorWindows' (zip)</a></li>",
        "</ul>"
      }

    }
  );
  m.push_back(
    { "CppHelloQwtQtCreatorCygwin",
      {
        "<p><img src=\"PicQwt.png\" alt=\"Qwt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicCygwin.png\" alt=\"Cygwin\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloQwtQtCreatorCygwin.htm\">Hello Qwt using Qt Creator under Cygwin</a>",
        "  is a <a href=\"CppHelloQwt.htm\">Hello Qwt</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloQwtQtCreatorCygwin.zip\">Download the Qt Creator project 'CppHelloQwtQtCreatorCygwin' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloQwtQtCreatorLubuntu",
      {
        "<p><img src=\"PicQwt.png\" alt=\"Qwt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloQwtQtCreatorLubuntu.htm\">Hello Qwt using Qt Creator under Lubuntu</a>",
        "  is a <a href=\"CppHelloQwt.htm\">Hello Qwt</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloQwtQtCreatorLubuntu.zip\">Download the Qt Creator project 'CppHelloQwtQtCreatorLubuntu' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloQwtQtCreatorLubuntuToWindows",
      {
        "<p><img src=\"PicQwt.png\" alt=\"Qwt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicTo.png\" alt=\"To\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloQwtQtCreatorLubuntuToWindows.htm\">Hello Qwt using Qt Creator under Lubuntu, crosscompiled to Windows</a>",
        "  is a <a href=\"CppHelloQwt.htm\">Hello Qwt</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloQwtQtCreatorLubuntuToWindows.zip\">Download the Qt Creator project 'CppHelloQwtQtCreatorLubuntuToWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloQwtQtCreatorSliTaz",
      {
        "<p><img src=\"PicQwt.png\" alt=\"Qwt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicSliTaz.png\" alt=\"SliTaz\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloQwtQtCreatorSliTaz.htm\">Hello Qwt using Qt Creator under SliTaz</a>",
        "  is a <a href=\"CppHelloQwt.htm\">Hello Qwt</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloQwtQtCreatorSliTaz.zip\">Download the Qt Creator project 'CppHelloQwtQtCreatorSliTaz' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloQwtQt4QtCreatorLubuntuToWindows",
      {
        "<p><img src=\"PicQwt.png\" alt=\"Qwt\"/><img src=\"PicQt4.png\" alt=\"Qt4\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicTo.png\" alt=\"To\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloQwtQt4QtCreatorLubuntuToWindows.htm\">Hello Qwt using Qt4 under Qt Creator under Lubuntu, crosscompiled to Windows</a>",
        "  is a <a href=\"CppHelloQwt.htm\">Hello Qwt</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloQwtQt4QtCreatorLubuntuToWindows.zip\">Download the Qt Creator project 'CppHelloQwtQt4QtCreatorLubuntuToWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloQwtQt5QtCreatorLubuntuToWindows",
      {
        "<p><img src=\"PicQwt.png\" alt=\"Qwt\"/><img src=\"PicQt5.png\" alt=\"Qt5\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicTo.png\" alt=\"To\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloQwtQt5QtCreatorLubuntuToWindows.htm\">Hello Qwt using Qt5 under Qt Creator under Lubuntu, crosscompiled to Windows</a>",
        "  is a <a href=\"CppHelloQwt.htm\">Hello Qwt</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloQwtQt5QtCreatorLubuntuToWindows.zip\">Download the Qt Creator project 'CppHelloQwtQt5QtCreatorLubuntuToWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloQwtQtCreatorWindows",
      {
        "<p><img src=\"PicQwt.png\" alt=\"Qwt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloQwtQtCreatorWindows.htm\">Hello Qwt using Qt Creator under Windows</a>",
        "  is a <a href=\"CppHelloQwt.htm\">Hello Qwt</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloQwtQtCreatorWindows.zip\">Download the Qt Creator project 'CppHelloQwtQtCreatorWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloWorld64QtCreatorLubuntu",
      {
        "<p>",
        "  <a href=\"CppHelloWorl64QtCreatorLubuntu.htm\">Hello World (64-bit) using Qt Creator under Lubuntu</a>",
        "  is a <a href=\"CppHelloWorld64.htm\">Hello World (64-bit)</a> program using the",
        "  <a href=\"CppQtCreator.htm\">Qt Creator</a> <a href=\"CppIde.htm\">IDE</a> under",
        "  the <a href=\"CppLubuntu.htm\">Lubuntu</a> <a href=\"CppOs.htm\">operating system</a>.",
        "</p>",
        "<ul>",
        "  <li><a href=\"CppHelloWorld64QtCreatorLubuntu.zip\">Download the Qt Creator project 'CppHelloWorl64QtCreatorLubuntu' (zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>Compiling the code results in the following error:</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"Compile error\" border = \"1\"><tr><td><code>",
        "/usr/include/c++/4.5/iostream:39: error: bits/c++config.h: No such file or directory<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->"
      }
    }
  );
  m.push_back(
    { "CppHelloWorldQtCreatorCygwin",
      {
        "<p><a href=\"CppHelloWorldQtCreatorCygwin.htm\">Hello World using Qt Creator under Cygwin</a> is <a href=\"CppHelloWorld.htm\">Hello World</a> program",
        "using the <a href=\"CppQtCreator.htm\">Qt Creator</a>",
        "<a href=\"CppIde.htm\">IDE</a> under <a href=\"CppCygwin.htm\">Cygwin</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloWorldQtCreatorCygwin.zip\">Download the Qt Creator project 'CppHelloWorldQtCreatorCygwin' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloWorldQtCreatorLubuntu",
      {
        "<p><a href=\"CppHelloWorldQtCreatorLubuntu.htm\">Hello World using Qt Creator under Lubuntu</a> is <a href=\"CppHelloWorld.htm\">Hello World</a> program",
        "using the <a href=\"CppQtCreator.htm\">Qt Creator</a>",
        "<a href=\"CppIde.htm\">IDE</a> under <a href=\"CppLubuntu.htm\">Lubuntu</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloWorldQtCreatorLubuntu.zip\">Download the Qt Creator project 'CppHelloWorldQtCreatorLubuntu' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloWorldQtCreatorLubuntuToWindows",
      {
        "<p><img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicTo.png\" alt=\"to\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppHelloWorldQtCreatorLubuntuToWindows.htm\">'Hello World' using Qt Creator under Lubuntu, crosscompile to Windows</a> is a",
        "<a href=\"CppHelloWorld.htm\">Hello World</a> program using the <a href=\"CppQtCreator.htm\">Qt Creator</a>",
        "<a href=\"CppIde.htm\">IDE</a> under the <a href=\"CppLubuntu.htm\">Lubuntu</a> <a href=\"CppOs.htm\">operating system</a>,",
        "<a href=\"CppCrossCompile.htm\">cross compiled</a> using <a href=\"CppMxe.htm\">MXE</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloWorldQtCreatorLubuntuToWindows.zip\">Download the Qt Creator project 'CppHelloWorldQtCreatorLubuntuToWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloWorldQtCreatorSliTaz",
      {
        "<p><a href=\"CppHelloWorldQtCreatorSliTaz.htm\">Hello World using Qt Creator under SliTaz</a> is <a href=\"CppHelloWorld.htm\">Hello World</a> program",
        "using the <a href=\"CppQtCreator.htm\">Qt Creator</a>",
        "<a href=\"CppIde.htm\">IDE</a> under <a href=\"CppSliTaz.htm\">SliTaz</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloWorldQtCreatorSliTaz.zip\">Download the Qt Creator project 'CppHelloWorldQtCreatorSliTaz' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloWorldQtCreatorUbuntu",
      {
        "<p><a href=\"CppHelloWorldQtCreatorUbuntu.htm\">Hello World using Qt Creator under Ubuntu</a> is <a href=\"CppHelloWorld.htm\">Hello World</a> program",
        "using the <a href=\"CppQtCreator.htm\">Qt Creator</a>",
        "<a href=\"CppIde.htm\">IDE</a> under <a href=\"CppUbuntu.htm\">Ubuntu</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloWorldQtCreatorUbuntu.zip\">Download the Qt Creator project 'CppHelloWorldQtCreatorUbuntu' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloWorldQtCreatorWindows",
      {
        "<p><a href=\"CppHelloWorldQtCreatorWindows.htm\">Hello World using Qt Creator under Windows</a> is <a href=\"CppHelloWorld.htm\">Hello World</a> program",
        "using the <a href=\"CppQtCreator.htm\">Qt Creator</a>",
        "<a href=\"CppIde.htm\">IDE</a> under <a href=\"CppWindows.htm\">Windows</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloWorldQtCreatorWindows.zip\">Download the Qt Creator project 'CppHelloWorldQtCreatorWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloQwtQtCreatorLubuntu",
      {

        "<p><a href=\"CppHelloQwtQtCreatorLubuntu.htm\">'Hello Qwt' using Qt Creator under Lubuntu</a> is a <a href=\"CppHelloQwt.htm\">Hello Qwt</a>",
        "program using the <a href=\"CppQtCreator.htm\">Qt Creator</a> <a href=\"CppIde.htm\">IDE</a> under the <a href=\"CppLubuntu.htm\">Lubuntu</a>",
        "<a href=\"CppOs.htm\">operating system</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloQwtQtCreatorLubuntu.png\">View a screenshot of 'CppHelloQwtQtCreatorLubuntu' (png)</a></li>",
        "  <li><a href=\"CppHelloQwtQtCreatorLubuntu.zip\">Download the Qt Creator project 'CppHelloQwtQtCreatorLubuntu' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloQwtQtCreatorUbuntu",
      {

        "<p><a href=\"CppHelloQwtQtCreatorUbuntu.htm\">'Hello Qwt' using Qt Creator under Ubuntu</a> is a <a href=\"CppHelloQwt.htm\">Hello Qwt</a>",
        "program using the <a href=\"CppQtCreator.htm\">Qt Creator</a> <a href=\"CppIde.htm\">IDE</a> under",
        "the <a href=\"CppUbuntu.htm\">Ubuntu</a> <a href=\"CppOs.htm\">operating system</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloQwtQtCreatorUbuntu.png\">View a screenshot of 'CppHelloQwtQtCreatorUbuntu' (png)</a></li>",
        "  <li><a href=\"CppHelloQwtQtCreatorUbuntu.zip\">Download the Qt Creator project 'CppHelloQwtQtCreatorUbuntu' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloQwtQtCreatorWindows",
      {
        "<p><a href=\"CppHelloQwtQtCreatorWindows.htm\">'Hello Qwt' using Qt Creator under Windows</a> is a <a href=\"CppHelloQwt.htm\">Hello Qwt</a>",
        "program using the <a href=\"CppQtCreator.htm\">Qt Creator</a> <a href=\"CppIde.htm\">IDE</a> under",
        "the <a href=\"CppWindows.htm\">Windows</a> <a href=\"CppOs.htm\">operating system</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloQwtQtCreatorWindows.png\">View a screenshot of 'CppHelloQwtQtCreatorWindows' (png)</a></li>",
        "  <li><a href=\"CppHelloQwtQtCreatorWindows.zip\">Download the Qt Creator project 'CppHelloQwtQtCreatorWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloWorldQtCreatorCygwin",
      {
        "<p><img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicCygwin.png\" alt=\"Cygwin\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloWorldQtCreatorCygwin.htm\">Hello World using Qt Creator under Cygwin</a>",
        "  is a <a href=\"CppHelloWorld.htm\">Hello World</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloWorldQtCreatorCygwin.zip\">Download the Qt Creator project 'CppHelloWorldQtCreatorCygwin' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloWorldQtCreatorLubuntu",
      {
        "<p><img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelloWorldQtCreatorLubuntu.htm\">Hello World using Qt Creator under Lubuntu</a>",
        "  is a <a href=\"CppHelloWorld.htm\">Hello World</a> program.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloWorldQtCreatorLubuntu.zip\">Download the Qt Creator project 'CppHelloWorldQtCreatorLubuntu' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloWorldQtCreatorLubuntuToWindows",
      {
        "<p><img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicTo.png\" alt=\"To\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppHelloWorldQtCreatorLubuntuToWindows.htm\">Hello World using Qt Creator under Lubuntu, crosscompiled to Windows</a> is a <a href=\"CppHelloWorld.htm\">Hello World</a> program.",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloWorldQtCreatorLubuntuToWindows.zip\">Download the Qt Creator project 'CppHelloWorldQtCreatorLubuntuToWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloWorldQtCreatorSliTaz",
      {
        "<p><img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicSliTaz.png\" alt=\"SliTaz\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppHelloWorldQtCreatorSliTaz.htm\">Hello World using Qt Creator under SliTaz</a> is a <a href=\"CppHelloWorld.htm\">Hello World</a> program.",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloWorldQtCreatorSliTaz.zip\">Download the Qt Creator project 'CppHelloWorldQtCreatorSliTaz' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloWorldQt4QtCreatorLubuntuToWindows",
      {
        "<p><img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicQt4.png\" alt=\"Qt4\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicTo.png\" alt=\"To\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppHelloWorldQt4QtCreatorLubuntuToWindows.htm\">Hello World using Qt4 under Qt Creator under Lubuntu, crosscompiled to Windows</a> is a <a href=\"CppHelloWorld.htm\">Hello World</a> program.",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloWorldQt4QtCreatorLubuntuToWindows.zip\">Download the Qt Creator project 'CppHelloWorldQt4QtCreatorLubuntuToWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloWorldQt5QtCreatorLubuntuToWindows",
      {
        "<p><img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicQt5.png\" alt=\"Qt5\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicTo.png\" alt=\"To\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppHelloWorldQt5QtCreatorLubuntuToWindows.htm\">Hello World using Qt5 under Qt Creator under Lubuntu, crosscompiled to Windows</a> is a <a href=\"CppHelloWorld.htm\">Hello World</a> program.",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloWorldQt5QtCreatorLubuntuToWindows.zip\">Download the Qt Creator project 'CppHelloWorldQt5QtCreatorLubuntuToWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppHelloWorldQtCreatorWindows",
      {
        "<p><img src=\"PicCpp98.png\" alt=\"C++98\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppHelloWorldQtCreatorWindows.htm\">Hello World using Qt Creator under Windows</a> is a <a href=\"CppHelloWorld.htm\">Hello World</a> program.",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppHelloWorldQtCreatorWindows.zip\">Download the Qt Creator project 'CppHelloWorldQtCreatorWindows' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppHelp",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppHelp.htm\">Help</a> is a",
        "  <a href=\"CppClass.htm\">class</a> to display help information",
        "  in a command-line application.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "CppHtmlPage",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppHtmlPage.htm\">HtmlPage</a> is a <a href=\"CppClass.htm\">class</a>",
        "for processing an HTML page.</p>"
      }
    }
  );

  m.push_back(
    { "CppIfExample1",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppIfExample1.htm\">if example 1: basics</a> is an <a href=\"CppIf.htm\">if</a> <a href=\"CppExample.htm\">example</a>.",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppIfExample1.zip\">Download the Qt Creator project 'CppIfExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppImageCanvas",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppImageCanvas.htm\">ImageCanvas</a> is a <a href=\"CppCanvas.htm\">Canvas</a>",
        "  to load images.",
        "</p>"
      }
    }
  );
  m.push_back(
    { "CppIpAddress",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppIpAddress.htm\">IpAddress</a> is a <a href=\"CppClass.htm\">class</a>",
        "  for containing an IP address.",
        "</p>"
      }
    }
  );
  m.push_back(
    { "CppIrcBot",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppIrcBot.htm\">IrcBot</a> is a <a href=\"CppClass.htm\">class</a>",
        "for an IRC bot. Its default name is 'lambda'.</p>"
      }
    }
  );

  m.push_back(
    { "CppIsRegularFile",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppIsRegularFile.htm\">IsRegularFile</a> is a <a href=\"CppFileIo.htm\">file I/O</a>  <a href=\"CppCodeSnippets.htm\">code snippet</a> to determine if a filename is a regular file.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppIsRegularFile.zip\">Download the Qt Creator project 'CppIsRegularFile' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppKalmanFilter",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>The <a href=\"CppKalmanFilter.htm\">Kalman filter</a> is a way to do predictions from noisy measurements. For a (far) more precise",
        "definition, see [1].</p>",
        "<p>&nbsp;</p>",
        "<p>The <a href=\"Tools.htm\">tool</a> <a href=\"ToolKalmanFilterer.htm\">KalmanFilterer</a> allows one to work with <a href=\"CppKalmanFilter.htm\">Kalman filters</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Examples</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppKalmanFilterExample1.htm\">Kalman filter example 1: single state, from adapted C code</a></li>",
        "  <li><a href=\"CppKalmanFilterExample2.htm\">Kalman filter example 2: single state, use of classes</a></li>",
        "  <li><a href=\"CppKalmanFilterExample3.htm\">Kalman filter example 3: single state, use of 1x1 boost::numeric::ublas::matrix</a></li>",
        "  <li><a href=\"CppKalmanFilterExample4.htm\">Kalman filter example 4: single state, use of 1x1 boost::numeric::ublas::matrix and boost::numeric::ublas::vector</a></li>",
        "  <li><a href=\"CppKalmanFilterExample5.htm\">Kalman filter example 5</a></li>",
        "  <li><a href=\"CppKalmanFilterExample6.htm\">Kalman filter example 6</a></li>",
        "  <li><a href=\"CppKalmanFilterExample7.htm\">Kalman filter example 7</a></li>",
        "  <li><a href=\"CppKalmanFilterExample8.htm\">Kalman filter example 8: displaying the graphs (initial)</a></li>",
        "  <li><a href=\"CppKalmanFilterExample9.htm\">Kalman filter example 9: displaying the graphs (better)</a></li>",
        "  <li><a href=\"CppKalmanFilterExample10.htm\">Kalman filter example 10: displaying the graphs (even better)</a></li>",
        "  <li><a href=\"CppKalmanFilterExample11.htm\">Kalman filter example 11: displaying the graphs (best)</a></li>",
        "  <li><a href=\"CppKalmanFilterExample12.htm\">Kalman filter example 12: displaying the equations</a></li>",
        "  <li><a href=\"CppKalmanFilterExample13.htm\">Kalman filter example 13: displaying the equations only</a></li>",
        "  <li><a href=\"ToolKalmanFilterer.htm\">KalmanFilterer</a>: <a href=\"Tools.htm\">tool</a> to work with <a href=\"CppKalmanFilter.htm\">Kalman filters</a></li>",
        "  <li><a href=\"CppKalmanFilterEquations.png\">Kalman filter equations</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"CppReferences.htm\">References</a></h2>",
        "<p>&nbsp;</p>",
        "<ol>",
        "  <li><a href=\"https://en.wikipedia.org/wiki/Kalman_filter\">Wikipedia page about the Kalman filter</a></li>",
        "  <li><a href=\"http://academic.csuohio.edu/simond/estimation\">Kalman filter examples (in Matlab)</a></li>",
        "  <li><a href=\"http://greg.czerniak.info/guides/kalman1/\">Kalman filter tutorial by Greg Czerniak</a></li>",
        "</ol>"
      }
    }
  );
  m.push_back(
    { "CppLazy_init",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppLazy_init.htm\">Lazy_init</a> is a <a href=\"CppClass.htm\">class</a></p>",
        "<p>with lazy initialization.</p>"
      }
    }
  );
  m.push_back(
    { "CppLed",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppLed.htm\">Led</a> is a <a href=\"CppClass.htm\">class</a> for an LED light.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppLed.htm\">Led</a> is used in the <a href=\"Tools.htm\">tool</a> <a href=\"ToolTestLed.htm\">TestLed</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppLedWidget",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppLedWidget.htm\">LedWidget</a> is a <a href=\"CppLed.htm\">Led</a>",
        "  <a href=\"CppWidget.htm\">widget</a>.",
        "</p>"
      }
    }
  );
  m.push_back(
    { "CppLinkErrorCannotFindLgstapp",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppLinkErrorCannotFindLgstapp.htm\">cannot find -lgstapp-0.10</a> is a",
        "<a href=\"CppLinkError.htm\">link error</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppLinkErrorCannotFindLgstapp.zip\">Download the Qt Creator project 'CppLinkErrorCannotFindLgstapp' (zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>This bug is reported with this <a href=\"https://bugs.launchpad.net/ubuntu/+source/qtwebkit-opensource-src/+bug/1134745\">Launchpad bug report</a>",
        "and another <a href=\"https://bugs.launchpad.net/ubuntu/+source/qtbase-opensource-src/+bug/1165250\">Launchpad bug report</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Solution</h2>",
        "<p>&nbsp;</p>",
        "<p>Install some gstreamer packages:</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"fileMMYf2H.txt\" border = \"1\"><tr><td><code>",
        "sudo apt-get install libgstreamer1.0-dev <br/>",
        "sudo apt-get install libgstreamer0.10-dev <br/>",
        "sudo apt-get install libgstreamer-plugins-base1.0-dev <br/>",
        "sudo apt-get install libgstreamer-plugins-base0.10-dev <br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->"
      }
    }
  );

  m.push_back(
    { "CppLibcvautomationExample1",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppLibcvautomationExample1.htm\">libcvautomation example 1: using an example</a> is a",
        "<a href=\"CppLibcvautomation.htm\">libcvautomation</a> <a href=\"CppExample.htm\">example</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppLibcvautomationExample1.zip\">Download the code 'CppLibcvautomationExample1' (zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>After successfully building libcvautomation, there will be two executables in [YOURPATH]/libcvautomation/examples. An executable",
        "called 'cva-input' will be used by the shell script. Copy the script to [YOURPATH]/libcvautomation/examples and run it.</p>",
        "<p>&nbsp;</p>",
        "<p>The script performs a left-mouse click on coordinat (100,100).</p>",
        "<p>&nbsp;</p>",
        "<table summary=\"libcvautomation example 1: using an example example 1\" border = \"1\"><tr><td><code>",
        "#!/bin/sh<br/>",
        "./cva-input -s \"mouselocation\" <br/>",
        "./cva-input -s \"mousexy 100 100\" <br/>",
        "./cva-input -s \"mouseclick\"<br/>",
        "./cva-input -s \"mouselocation\"<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->"
      }
    }
  );
  m.push_back(
    { "CppLibcvautomationExample2",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppLibcvautomationExample2.htm\">libcvautomation example 2: Qt Creator project around example (using C)</a> is a",
        "<a href=\"CppLibcvautomation.htm\">libcvautomation</a> example of a <a href=\"CppQtCreator.htm\">Qt Creator</a> project around",
        "an example supplied by Bradlee Speice (the author of libcvautomation). Note that the project is set to compile C code, instead of C++.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppLibcvautomationExample2.zip\">Download the Qt Creator project 'CppLibcvautomationExample2' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppLibcvautomationExample3",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppLibcvautomationExample3.htm\">libcvautomation example 3: Qt Creator project around example</a> is a",
        "<a href=\"CppLibcvautomation.htm\">libcvautomation</a> example of a <a href=\"CppQtCreator.htm\">Qt Creator</a> project around",
        "an example supplied by Bradlee Speice (the author of libcvautomation). This example uses C++, but does not compile cleanly and uses tabs.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppLibcvautomationExample3.zip\">Download the Qt Creator project 'CppLibcvautomationExample3' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppLibcvautomationExample4",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppLibcvautomationExample4.htm\">libcvautomation example 4: Qt Creator project around adapted example</a> is a",
        "<a href=\"CppLibcvautomation.htm\">libcvautomation</a> example of a <a href=\"CppQtCreator.htm\">Qt Creator</a> project around",
        "an example supplied by Bradlee Speice (the author of libcvautomation). This example uses C++ and compiles cleanly and has the tabs replaced by spaces.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppLibcvautomationExample4.zip\">Download the Qt Creator project 'CppLibcvautomationExample4' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppLibcvautomationExample5",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppLibcvautomationExample5.htm\">libcvautomation example 5: basic Qt GUI</a> is a",
        "<a href=\"CppLibcvautomation.htm\">libcvautomation</a> example of a <a href=\"CppQtCreator.htm\">Qt Creator</a> project with",
        "a basic GUI to give commands.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppLibcvautomationExample5.png\">View a screenshot of 'CppLibcvautomationExample5' (png)</a></li>",
        "  <li><a href=\"CppLibcvautomationExample5.zip\">Download the Qt Creator project 'CppLibcvautomationExample5' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppLibcvautomationExample6",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppLibcvautomationExample6.htm\">libcvautomation example 6: test a simple Qt desktop application</a> is a",
        "<a href=\"CppLibcvautomation.htm\">libcvautomation</a> example with a simple Qt desktop application and a ",
        "<a href=\"CppLibcvautomation.htm\">libcvautomation</a> test script. The application is called from the script, and has three",
        "buttons: two labeled 'Press me' and one labeled 'DON'T PRESS ME'. The test presses both 'Press me' buttons (their text will change",
        "to 'OK') and then click the 'DON'T PRESS ME' button, which causes an error.</p>",
        "<p>&nbsp;</p>",
        "<p>For the testing script, I have supplied part of screenshots of the application. I guess that would I change my desktop theme (for example: using",
        "a black theme), the test will not find the buttons anymore.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppLibcvautomationExample6.png\">View a screenshot of 'CppLibcvautomationExample6' (png)</a></li>",
        "  <li><a href=\"CppLibcvautomationExample6.zip\">Download the Qt Creator project 'CppLibcvautomationExample6' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppLibcvautomationExample7",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppLibcvautomationExample7.htm\">libcvautomation example 7: test a simple Qt desktop application by sending keys</a> is a",
        "<a href=\"CppLibcvautomation.htm\">libcvautomation</a> example with a simple Qt desktop application and a ",
        "<a href=\"CppLibcvautomation.htm\">libcvautomation</a> test script. The application is called from the script, and has three",
        "buttons: two labeled 'Press me' and one labeled 'DON'T PRESS ME'. The test presses the tab and space keys, which causes that the upper 'Press me' button",
        "its text will change to OK, after which the 'DON'T PRESS ME' button is pressed, which causes an error.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppLibcvautomationExample7.zip\">Download the Qt Creator project 'CppLibcvautomationExample7' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppLinkErrorUndefinedReferenceToWebCore",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppLinkErrorUndefinedReferenceToWebCore.htm\">CppLinkErrorUndefinedReferenceToWebCore</a> is a",
        "<a href=\"CppLinkError.htm\">link error</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppLinkErrorUndefinedReferenceToWebCore.zip\">Download the Qt Creator project 'CppLinkErrorUndefinedReferenceToWebCore' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppLoopReader",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppLoopReader.htm\">LoopReader</a> is a",
        "  <a href=\"CppTemplateClass.htm\">template class</a> to iterate",
        "  through a <a href=\"CppContainer.htm\">container</a>. If the",
        "  <a href=\"CppContainer.htm\">container</a>'s end is",
        "  reached, however, <a href=\"CppLoopReader.htm\">LoopReader</a> starts reading",
        "  from the beginning again.",
        "</p>"
      }
    }
  );
  m.push_back(
    { "CppManyDigitNewick",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  A <a href=\"CppNewick.htm\">Newick</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );
  m.push_back(
    { "CppMatrix",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppMatrix.htm\">matrix</a> is a two-dimensional <a href=\"CppContainer.htm\">container</a>",
        "  (that is a <a href=\"CppContainer.htm\">container</a> in which two values",
        "  are needed to retrieve an element). For one-dimensional containers,",
        "  <a href=\"CppContainer.htm\">go to the container page</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>There exists no std::matrix (yet).</p>",
        "<p>&nbsp;</p>",
        "<p>Possibilities are:</p>",
        "<ol>",
        "  <li><img src=\"PicStl.png\" alt=\"STL\"/> <a href=\"CppVector.htm\">std::vector</a>&lt;<a href=\"CppVector.htm\">std::vector</a>&lt;<b><a href=\"CppInt.htm\">int</a></b>&gt; &gt;</li>",
        "  <li><img src=\"PicBoost.png\" alt=\"Boost\"/> <a href=\"CppMulti_array.htm\">boost::multi_array</a></li>",
        "  <li><img src=\"PicBoost.png\" alt=\"Boost\"/> <a href=\"CppUblasMatrix.htm\">boost::numeric::ublas::matrix</a></li>",
        "  <li><img src=\"PicSpacer.png\" alt=\" \"/>blitz::Array</li>",
        "  <li><img src=\"PicSpacer.png\" alt=\" \"/><a href=\"http://www.techsoftpl.com/matrix\">Techsoft</a>'s matrix</li>",
        "  <li><img src=\"PicSpacer.png\" alt=\" \"/>Flood::Matrix</li>",
        "</ol>",
        "<p>&nbsp;</p>",
        "<p>These possibilities are described below in more detail.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><img src=\"PicStl.png\" alt=\"STL\"/> <a href=\"CppVector.htm\">std::vector</a>&lt;<a href=\"CppVector.htm\">std::vector</a>&lt;<b><a href=\"CppInt.htm\">int</a></b>&gt; &gt;</h2>",
        "<p>&nbsp;</p>",
        "<p>",
        "  A <a href=\"CppVector.htm\">std::vector</a> can contain a collection of",
        "  <a href=\"CppVector.htm\">std::vector</a>s. If all",
        "  <a href=\"CppVector.htm\">std::vector</a>s in this collection are of the same",
        "  size, one has a matrix.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>When using <a href=\"CppVector.htm\">std::vector</a>&lt;<a href=\"CppVector.htm\">std::vector</a>&lt;<b><a href=\"CppInt.htm\">int</a></b>&gt; &gt; for a two-dimensional matrix, the choice between x-y-ordering or y-x-ordering must be made. The run-time speed difference does not reside in individual element read/write, but when obtaining a row or collumn: in a y-x-ordered <a href=\"CppVector.htm\">std::vector</a>&lt;<a href=\"CppVector.htm\">std::vector</a>&lt;<b><a href=\"CppInt.htm\">int</a></b>&gt; &gt; an individual row can be obtained, in an x-y-ordered <a href=\"CppVector.htm\">std::vector</a>&lt;<a href=\"CppVector.htm\">std::vector</a>&lt;<b><a href=\"CppInt.htm\">int</a></b>&gt; &gt; an individual collumn can be obtained.</p>",
        "<p>&nbsp;</p>",
        "<p>Below is an example of a y-x-ordered <a href=\"CppVector.htm\">std::vector</a>&lt;<a href=\"CppVector.htm\">std::vector</a>&lt;<b><a href=\"CppInt.htm\">int</a></b>&gt; &gt;.</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"2D vector example\" border = \"1\"><tr><td><code>",
        "<a href=\"CppInclude.htm\">#include</a> &lt;<a href=\"CppCassertH.htm\">cassert</a>&gt;<br/>",
        "<a href=\"CppInclude.htm\">#include</a> &lt;<a href=\"CppVectorH.htm\">vector</a>&gt;<br/>",
        "<br/>",
        "<b><a href=\"CppInt.htm\">int</a></b> <a href=\"CppMain.htm\">main</a>()<br/>",
        "{<br/>",
        "&nbsp;&nbsp;<b><a href=\"CppConst.htm\">const</a></b> <b><a href=\"CppInt.htm\">int</a></b> n_rows <a href=\"CppOperatorAssign.htm\">=</a> 5;<br/>",
        "&nbsp;&nbsp;<b><a href=\"CppConst.htm\">const</a></b> <b><a href=\"CppInt.htm\">int</a></b> n_cols <a href=\"CppOperatorAssign.htm\">=</a> 10;<br/>",
        "&nbsp;&nbsp;<a href=\"CppComment.htm\">//</a>Create the y-x-ordered 2D-vector<br/>",
        "&nbsp;&nbsp;<a href=\"CppVector.htm\">std::vector</a>&lt;<a href=\"CppVector.htm\">std::vector</a>&lt;<b><a href=\"CppInt.htm\">int</a></b>&gt; &gt; v(n_rows, <a href=\"CppVector.htm\">std::vector</a>&lt;<b><a href=\"CppInt.htm\">int</a></b>&gt;(n_cols,0),<br/>",
        "&nbsp;&nbsp;<b><a href=\"CppConst.htm\">const</a></b> <b><a href=\"CppInt.htm\">int</a></b> y <a href=\"CppOperatorAssign.htm\">=</a> n_rows <a href=\"CppOperatorMinus.htm\">-</a> 1;<br/>",
        "&nbsp;&nbsp;<b><a href=\"CppConst.htm\">const</a></b> <b><a href=\"CppInt.htm\">int</a></b> x <a href=\"CppOperatorAssign.htm\">=</a> n_cols <a href=\"CppOperatorMinus.htm\">-</a> 1;<br/>",
        "&nbsp;&nbsp;<a href=\"CppAssert.htm\">assert</a>(y &lt; <b><a href=\"CppStatic_cast.htm\">static_cast</a></b>&lt;<b><a href=\"CppInt.htm\">int</a></b>&gt;(v.size()),<br/>",
        "&nbsp;&nbsp;<a href=\"CppAssert.htm\">assert</a>(x &lt; <b><a href=\"CppStatic_cast.htm\">static_cast</a></b>&lt;<b><a href=\"CppInt.htm\">int</a></b>&gt;(v[y].size()),<br/>",
        "&nbsp;&nbsp;v[y][x] <a href=\"CppOperatorAssign.htm\">=</a> 10; <a href=\"CppComment.htm\">//</a>y-x-ordered<br/>",
        "}<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h3><a href=\"CppVector.htm\">std::vector</a>&lt;<a href=\"CppVector.htm\">std::vector</a>&lt;<a href=\"CppInt.htm\">int</a>&gt; &gt; <a href=\"CppCodeSnippets.htm\">code snippets</a></h3>",
        "<p>&nbsp;</p>",
        "<p>Note that some of these <a href=\"CppCodeSnippets.htm\">code snippets</a> also work on other <a href=\"CppContainer.htm\">containers</a>.</p>",
        "<p>&nbsp;</p>",
        "<ol>",
        "  <li><a href=\"CppConvertMatrix.htm\">Convert Matrix&lt;X&gt; to Matrix&lt;Y&gt;, ConvertMatrix</a></li>",
        "  <li><a href=\"CppConvertMatrix.htm\">Convert std::vector&lt;std::vector&lt;X&gt; &gt; to std::vector&lt;std::vector&lt;Y&gt; &gt;, ConvertMatrix</a></li>",
        "  <li><a href=\"CppConvertMatrix.htm\">Convert two 2D std::vector&lt;X&gt; to 2D std::vector&lt;Y&gt;, ConvertMatrix</a></li>",
        "  <li><a href=\"CppConvertMatrix.htm\">ConvertMatrix, convert Matrix&lt;X&gt; to Matrix&lt;Y&gt;</a></li>",
        "  <li><a href=\"CppConvertMatrix.htm\">ConvertMatrix, convert std::vector&lt;std::vector&lt;X&gt; &gt; to std::vector&lt;std::vector&lt;Y&gt; &gt;</a></li>",
        "  <li><a href=\"CppConvertMatrix.htm\">ConvertMatrix, convert two 2D std::vector&lt;X&gt; to 2D std::vector&lt;Y&gt;</a></li>",
        "  <li><a href=\"CppMaxElement.htm\">Get the maximal element of a 2D container, MaxElement</a></li>",
        "  <li><a href=\"CppMinElement.htm\">Get the minimum element of a 2D container, MinElement</a></li>",
        "  <li><a href=\"CppGetSizes.htm\">Get the sizes of the std::vectors in a 2D std::vector, GetSizes</a></li>",
        "  <li><a href=\"CppGetSumMatrix.htm\">Get the sum of a 2D std::vector, GetSum</a></li>",
        "  <li><a href=\"CppGetSizes.htm\">GetSizes, get the sizes of the std::vectors in a 2D std::vector</a></li>",
        "  <li><a href=\"CppGetSumMatrix.htm\">GetSum, get the sum of a 2D std::vector</a></li>",
        "  <li><a href=\"CppMaxElement.htm\">MaxElement, get the maximal element of a 2D container</a></li>",
        "  <li><a href=\"CppMinElement.htm\">MinElement, get the minimum element of a 2D container</a></li>",
        "</ol>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><img src=\"PicBoost.png\" alt=\"Boost\"/> <a href=\"CppMulti_array.htm\">boost::multi_array</a></h2>",
        "<p>&nbsp;</p>",
        "<p>The <a href=\"CppMulti_array.htm\">boost::multi_array</a> (part of the <a href=\"CppBoost.htm\">Boost</a> library) is not only support a two-dimensional matrix, but to many more dimensions.</p>",
        "<p>&nbsp;</p>",
        "<p>When using <a href=\"CppBuilder.htm\">C++ Builder</a> 6.0, this does not <a href=\"CppCompile.htm\">compile</a> (it results in the <a href=\"CppCompileError.htm\">compile error</a> <a href=\"CppCompileErrorBorlandHppOnlyMemberFunctionsMayBeConstOrVolatile.htm\">borland.hpp: Only member functions may be 'const' or 'volatile'</a>).</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><img src=\"PicBoost.png\" alt=\"Boost\"/> <a href=\"CppUblasMatrix.htm\">boost::numeric::ublas::matrix</a></h2>",
        "<p>&nbsp;</p>",
        "<p>The <a href=\"CppUblasMatrix.htm\">boost::numeric::ublas::matrix</a> (part of the ",
        "<a href=\"CppUblas.htm\">Boost.uBLAS</a> <a href=\"CppLibrary.htm\">library</a>) support a two-dimensional matrix.</p>",
        "<p>&nbsp;</p>",
        "<p>See <a href=\"CppUblasMatrix.htm\">boost::numeric::ublas::matrix</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicGreen.png\" alt=\"OKAY\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/> In <a href=\"CppQtCreator.htm\">Qt Creator</a> <a href=\"CppUblasMatrix.htm\">boost::numeric::ublas::matrix</a> works fine</li>",
        "  <li><img src=\"PicRed.png\" alt=\"FAIL\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/> In <a href=\"CppBuilder.htm\">C++ Builder</a> 6.0, this does not <a href=\"CppCompile.htm\">compile</a> (it results in the <a href=\"CppCompileError.htm\">compile error</a> <a href=\"CppCompileErrorYourCompilerAndOrConfigurationIsUnsupportedByThisVerionsOfUblas.htm\">Your compiler and/or configuration is unsupported by this verions of uBLAS</a>)</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>blitz::Array</h2>",
        "<p>&nbsp;</p>",
        "<p>The blitz::Array (part of the <a href=\"CppBlitzpp.htm\">Blitz++</a> <a href=\"CppLibrary.htm\">library</a>) is not only support a two-dimensional matrix, but to many more dimensions.</p>",
        "<p>&nbsp;</p>",
        "<p>When using <a href=\"CppBuilder.htm\">C++ Builder</a> 6.0, this does not <a href=\"CppCompile.htm\">compile</a> (it results in the <a href=\"CppCompileError.htm\">compile error</a> <a href=\"CppCompileErrorBzconfigHunknownCompiler.htm\">bzconfig.h: Unknown compiler</a>).</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"http://www.techsoftpl.com/matrix\">Techsoft</a>'s matrix</h2>",
        "<p>&nbsp;</p>",
        "<p><a href=\"http://www.techsoftpl.com/matrix\">Techsoft</a>'s matrix supports a x-y-ordered two-dimensional matrix.</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"Techsoft matrix example\" border = \"1\"><tr><td><code>",
        "<a href=\"CppInclude.htm\">#include</a> &lt;<a href=\"CppCassertH.htm\">cassert</a>&gt;<br/>",
        "<a href=\"CppInclude.htm\">#include</a> &lt;techsoft/matrix.h&gt;<br/>",
        "<br/>",
        "<b><a href=\"CppInt.htm\">int</a></b> <a href=\"CppMain.htm\">main</a>()<br/>",
        "{<br/>",
        "&nbsp;&nbsp;<b><a href=\"CppConst.htm\">const</a></b> <b><a href=\"CppInt.htm\">int</a></b> n_rows <a href=\"CppOperatorAssign.htm\">=</a> 5;<br/>",
        "&nbsp;&nbsp;<b><a href=\"CppConst.htm\">const</a></b> <b><a href=\"CppInt.htm\">int</a></b> n_cols <a href=\"CppOperatorAssign.htm\">=</a> 10;<br/>",
        "&nbsp;&nbsp;math::matrix&lt;<b><a href=\"CppInt.htm\">int</a></b>&gt; v(n_rows,n_cols,<br/>",
        "&nbsp;&nbsp;<b><a href=\"CppConst.htm\">const</a></b> <b><a href=\"CppInt.htm\">int</a></b> y <a href=\"CppOperatorAssign.htm\">=</a> n_rows <a href=\"CppOperatorMinus.htm\">-</a> 1;<br/>",
        "&nbsp;&nbsp;<b><a href=\"CppConst.htm\">const</a></b> <b><a href=\"CppInt.htm\">int</a></b> x <a href=\"CppOperatorAssign.htm\">=</a> n_cols <a href=\"CppOperatorMinus.htm\">-</a> 1;<br/>",
        "&nbsp;&nbsp;<a href=\"CppAssert.htm\">assert</a>(v(x,y)<a href=\"CppOperatorEqual.htm\">==</a>0,<br/>",
        "&nbsp;&nbsp;v(x,y) <a href=\"CppOperatorAssign.htm\">=</a> 10;<br/>",
        "&nbsp;&nbsp;<a href=\"CppAssert.htm\">assert</a>(v(x,y)<a href=\"CppOperatorEqual.htm\">==</a>10,<br/>",
        "}<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Flood::Matrix</h2>",
        "<p>&nbsp;</p>",
        "<p>The Flood::Matrix (from the <a href=\"CppFlood.htm\">Flood</a> library) supports a x-y-ordered two-dimensional matrix.</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"Flood::Matrix example\" border = \"1\"><tr><td><code>",
        "<a href=\"CppInclude.htm\">#include</a> &lt;<a href=\"CppCassertH.htm\">cassert</a>&gt;<br/>",
        "<a href=\"CppInclude.htm\">#include</a> &lt;flood/utilities/matrix.h&gt;<br/>",
        "&nbsp;<br/>",
        "<b><a href=\"CppInt.htm\">int</a></b> <a href=\"CppMain.htm\">main</a>()<br/>",
        "{<br/>",
        "&nbsp;&nbsp;<b><a href=\"CppConst.htm\">const</a></b> <b><a href=\"CppInt.htm\">int</a></b> n_rows <a href=\"CppOperatorAssign.htm\">=</a> 5;<br/>",
        "&nbsp;&nbsp;<b><a href=\"CppConst.htm\">const</a></b> <b><a href=\"CppInt.htm\">int</a></b> n_cols <a href=\"CppOperatorAssign.htm\">=</a> 10;<br/>",
        "&nbsp;&nbsp;Flood::Matrix&lt;<b><a href=\"CppInt.htm\">int</a></b>&gt; v(n_rows,n_cols,<br/>",
        "&nbsp;&nbsp;<b><a href=\"CppConst.htm\">const</a></b> <b><a href=\"CppInt.htm\">int</a></b> y <a href=\"CppOperatorAssign.htm\">=</a> n_rows <a href=\"CppOperatorMinus.htm\">-</a> 1;<br/>",
        "&nbsp;&nbsp;<b><a href=\"CppConst.htm\">const</a></b> <b><a href=\"CppInt.htm\">int</a></b> x <a href=\"CppOperatorAssign.htm\">=</a> n_cols <a href=\"CppOperatorMinus.htm\">-</a> 1;<br/>",
        "&nbsp;&nbsp;<a href=\"CppAssert.htm\">assert</a>( x &lt; v.getNumberOfRows(),<br/>",
        "&nbsp;&nbsp;<a href=\"CppAssert.htm\">assert</a>( y &lt; v.getNumberOfColumns(),<br/>",
        "&nbsp;&nbsp;<a href=\"CppAssert.htm\">assert</a>(v[x][y]<a href=\"CppOperatorEqual.htm\">==</a>0,<br/>",
        "&nbsp;&nbsp;v[x][y] <a href=\"CppOperatorAssign.htm\">=</a> 10;<br/>",
        "&nbsp;&nbsp;<a href=\"CppAssert.htm\">assert</a>(v[x][y]<a href=\"CppOperatorEqual.htm\">==</a>10,<br/>",
        "}<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>External links</h2>",
        "<p>&nbsp;</p>",
        "<ol>",
        "  <li><a href=\"http://en.wikipedia.org/wiki/Matrix_%28mathematics%29\">Wikipedia page about matrices</a></li>",
        "  <li><a href=\"http://www.boost.org/doc/libs/1_42_0/libs/multi_array/doc/index.html\">Boost page about boost::multi_array</a></li>",
        "  <li><a href=\"http://www.oonumerics.org/blitz\">Blitz++ homepage</a></li>",
        "  <li><a href=\"http://www.techsoftpl.com/matrix\">Techsoft homepage</a></li>",
        "</ol>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"CppReferences.htm\">References</a></h2>",
        "<p>&nbsp;</p>",
        "<ol>",
        "  <li><a href=\"http://en.wikipedia.org/wiki/Matrix_%28mathematics%29\">Wikipedia page about matrices</a></li>",
        "</ol>"
      }
    }
  );

  m.push_back(
    { "CppMemberFunctionExample1",
      {
        "<p><img src=\"PicCpp11.png\" alt=\"C++11\"/><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppMemberFunctionExample1.htm\">member function example 1: Hello World</a>",
        "  is a <a href=\"CppMemberFunction.htm\">member function</a> <a href=\"CppExample.htm\">example</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  The class 'HelloWorld' has a single <a href=\"CppConstMemberFunction.htm\">const member function</a> called",
        "  'SayHelloWorld'. It is called in <a href=\"CppMain.htm\">main</a>, producing the same output as",
        "  a <a href=\"CppHelloWorld.htm\">Hello World program</a>."
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppMemberFunctionExample1.zip\">Download the Qt Creator project 'CppMemberFunctionExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppMemberFunctionExample2",
      {
        "<p><img src=\"PicCpp11.png\" alt=\"C++11\"/><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppMemberFunctionExample2.htm\">member function example 2: pointer to member functions</a> is a <a href=\"CppMemberFunction.htm\">member function</a> <a href=\"CppExample.htm\">example</a>.",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppMemberFunctionExample2.zip\">Download the Qt Creator project 'CppMemberFunctionExample2' (zip)</a></li>",
        "</ul>"
      }
    }
  );


  m.push_back(
    { "CppMemcheckExample1",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppMemcheckExample1.htm\">memcheck example 1: Hello World</a> is a <a href=\"CppMemcheck.htm\">memcheck</a> example shows how ",
        "to check a <a href=\"CppHelloWorld.htm\">Hello world</a>",
        "program for, among others, <a href=\"CppMemoryLeak.htm\">memory leaks</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppMemcheckExample1.zip\">Download the Qt Creator project 'CppMemcheckExample1' (zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppValgrind.htm\">valgrind</a> can be used from command line:</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"Command to start memgrind\" border = \"1\"><tr><td><code>",
        "<a href=\"CppValgrind.htm\">valgrind</a> --leak-check=full -v --show-reachable=yes --log-file=my_log_filename.txt ./my_executable_filename<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>valgrind_memcheck.txt</h2>",
        "<p>&nbsp;</p>",
        "<p>I got the following output:</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"memcheck result\" border = \"1\"><tr><td><code>",
        "==13471== Memcheck, a memory error detector<br/>",
        "==13471== Copyright (C) 2002-2010, and GNU GPL'd, by Julian Seward et al.<br/>",
        "==13471== Using Valgrind-3.6.1 and LibVEX; rerun with -h for copyright info<br/>",
        "==13471== Command: ../CppMemcheckExample1-build-desktop/./CppMemcheckExample1<br/>",
        "==13471== Parent PID: 13470<br/>",
        "==13471== <br/>",
        "--13471-- <br/>",
        "--13471-- Valgrind options:<br/>",
        "--13471--&nbsp;&nbsp;&nbsp;&nbsp;--suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp<br/>",
        "--13471--&nbsp;&nbsp;&nbsp;&nbsp;--leak-check=full<br/>",
        "--13471--&nbsp;&nbsp;&nbsp;&nbsp;-v<br/>",
        "--13471--&nbsp;&nbsp;&nbsp;&nbsp;--show-reachable=yes<br/>",
        "--13471--&nbsp;&nbsp;&nbsp;&nbsp;--log-file=valgrind_memcheck.txt<br/>",
        "--13471-- Contents of /proc/version:<br/>",
        "--13471--&nbsp;&nbsp; Linux version 2.6.38-8-generic-pae (buildd@vernadsky) (gcc version 4.5.2 (Ubuntu/Linaro 4.5.2-8ubuntu3) ) #42-Ubuntu SMP Mon Apr 11 05:17:09 UTC 2011<br/>",
        "--13471-- Arch and hwcaps: X86, x86-sse1-sse2<br/>",
        "--13471-- Page sizes: currently 4096, max supported 4096<br/>",
        "--13471-- Valgrind library directory: /usr/lib/valgrind<br/>",
        "--13471-- Reading syms from /lib/i386-linux-gnu/ld-2.13.so (0x4000000)<br/>",
        "--13471--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/ld-2.13.so ..<br/>",
        "--13471--&nbsp;&nbsp; .. CRC mismatch (computed 2a2c2799 wanted 1e351f1f)<br/>",
        "--13471--&nbsp;&nbsp; Considering /usr/lib/debug/lib/i386-linux-gnu/ld-2.13.so ..<br/>",
        "--13471--&nbsp;&nbsp; .. CRC is valid<br/>",
        "--13471-- Reading syms from /home/richel/Projects/Website/CppMemcheckExample1-build-desktop/CppMemcheckExample1 (0x8048000)<br/>",
        "--13471-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)<br/>",
        "--13471--&nbsp;&nbsp;&nbsp;&nbsp;object doesn't have a dynamic symbol table<br/>",
        "--13471-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp<br/>",
        "--13471-- Reading suppressions file: /usr/lib/valgrind/default.supp<br/>",
        "--13471-- REDIR: 0x4016a80 (index) redirected to 0x3803f82b (vgPlain_x86_linux_REDIR_FOR_index)<br/>",
        "--13471-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x4020000)<br/>",
        "--13471-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4023000)<br/>",
        "==13471== WARNING: new redirection conflicts with existing -- ignoring it<br/>",
        "--13471--&nbsp;&nbsp;&nbsp;&nbsp; new: 0x04016a80 (index&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ) R-&gt; 0x04026c78 index<br/>",
        "--13471-- REDIR: 0x4016c20 (strlen) redirected to 0x4027048 (strlen)<br/>",
        "--13471-- Reading syms from /usr/lib/libQtCore.so.4.7.2 (0x4043000)<br/>",
        "--13471--&nbsp;&nbsp; Considering /usr/lib/libQtCore.so.4.7.2 ..<br/>",
        "--13471--&nbsp;&nbsp; .. CRC mismatch (computed 0c8a8d9d wanted ce78deb8)<br/>",
        "--13471--&nbsp;&nbsp; Considering /usr/lib/debug/usr/lib/libQtCore.so.4.7.2 ..<br/>",
        "--13471--&nbsp;&nbsp; .. CRC is valid<br/>",
        "--13471-- Reading syms from /lib/i386-linux-gnu/libpthread-2.13.so (0x42d6000)<br/>",
        "--13471--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/libpthread-2.13.so ..<br/>",
        "--13471--&nbsp;&nbsp; .. CRC mismatch (computed 87269ed5 wanted 7df95f2f)<br/>",
        "--13471--&nbsp;&nbsp; Considering /usr/lib/debug/lib/i386-linux-gnu/libpthread-2.13.so ..<br/>",
        "--13471--&nbsp;&nbsp; .. CRC is valid<br/>",
        "--13471-- Reading syms from /usr/lib/i386-linux-gnu/libstdc++.so.6.0.14 (0x42ef000)<br/>",
        "--13471--&nbsp;&nbsp;&nbsp;&nbsp;object doesn't have a symbol table<br/>",
        "--13471-- Reading syms from /lib/i386-linux-gnu/libm-2.13.so (0x43da000)<br/>",
        "--13471--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/libm-2.13.so ..<br/>",
        "--13471--&nbsp;&nbsp; .. CRC mismatch (computed e686ed93 wanted a0f1e52c)<br/>",
        "--13471--&nbsp;&nbsp; Considering /usr/lib/debug/lib/i386-linux-gnu/libm-2.13.so ..<br/>",
        "--13471--&nbsp;&nbsp; .. CRC is valid<br/>",
        "--13471-- Reading syms from /lib/i386-linux-gnu/libgcc_s.so.1 (0x4400000)<br/>",
        "--13471--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/libgcc_s.so.1 ..<br/>",
        "--13471--&nbsp;&nbsp; .. CRC mismatch (computed 3fa6d24f wanted 8b2bf89f)<br/>",
        "--13471--&nbsp;&nbsp;&nbsp;&nbsp;object doesn't have a symbol table<br/>",
        "--13471-- Reading syms from /lib/i386-linux-gnu/libc-2.13.so (0x441c000)<br/>",
        "--13471--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/libc-2.13.so ..<br/>",
        "--13471--&nbsp;&nbsp; .. CRC mismatch (computed 97e88cd2 wanted 4635a554)<br/>",
        "--13471--&nbsp;&nbsp; Considering /usr/lib/debug/lib/i386-linux-gnu/libc-2.13.so ..<br/>",
        "--13471--&nbsp;&nbsp; .. CRC is valid<br/>",
        "--13471-- Reading syms from /lib/i386-linux-gnu/libz.so.1.2.3.4 (0x457e000)<br/>",
        "--13471--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/libz.so.1.2.3.4 ..<br/>",
        "--13471--&nbsp;&nbsp; .. CRC mismatch (computed 995eb12f wanted 33a06a21)<br/>",
        "--13471--&nbsp;&nbsp;&nbsp;&nbsp;object doesn't have a symbol table<br/>",
        "--13471-- Reading syms from /lib/i386-linux-gnu/libdl-2.13.so (0x4593000)<br/>",
        "--13471--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/libdl-2.13.so ..<br/>",
        "--13471--&nbsp;&nbsp; .. CRC mismatch (computed 608d0daf wanted 983d6578)<br/>",
        "--13471--&nbsp;&nbsp; Considering /usr/lib/debug/lib/i386-linux-gnu/libdl-2.13.so ..<br/>",
        "--13471--&nbsp;&nbsp; .. CRC is valid<br/>",
        "--13471-- Reading syms from /usr/lib/i386-linux-gnu/libgthread-2.0.so.0.2800.6 (0x4597000)<br/>",
        "--13471--&nbsp;&nbsp; Considering /usr/lib/i386-linux-gnu/libgthread-2.0.so.0.2800.6 ..<br/>",
        "--13471--&nbsp;&nbsp; .. CRC mismatch (computed 244482a3 wanted 61a9cd3c)<br/>",
        "--13471--&nbsp;&nbsp;&nbsp;&nbsp;object doesn't have a symbol table<br/>",
        "--13471-- Reading syms from /lib/i386-linux-gnu/librt-2.13.so (0x459c000)<br/>",
        "--13471--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/librt-2.13.so ..<br/>",
        "--13471--&nbsp;&nbsp; .. CRC mismatch (computed 680ec6ea wanted 247d4d27)<br/>",
        "--13471--&nbsp;&nbsp; Considering /usr/lib/debug/lib/i386-linux-gnu/librt-2.13.so ..<br/>",
        "--13471--&nbsp;&nbsp; .. CRC is valid<br/>",
        "--13471-- Reading syms from /lib/i386-linux-gnu/libglib-2.0.so.0.2800.6 (0x45a5000)<br/>",
        "--13471--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/libglib-2.0.so.0.2800.6 ..<br/>",
        "--13471--&nbsp;&nbsp; .. CRC mismatch (computed 2312631e wanted e21a44de)<br/>",
        "--13471--&nbsp;&nbsp;&nbsp;&nbsp;object doesn't have a symbol table<br/>",
        "--13471-- Reading syms from /lib/i386-linux-gnu/libpcre.so.3.12.1 (0x467d000)<br/>",
        "--13471--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/libpcre.so.3.12.1 ..<br/>",
        "--13471--&nbsp;&nbsp; .. CRC mismatch (computed 9e5ab3c1 wanted 29aaf7e3)<br/>",
        "--13471--&nbsp;&nbsp;&nbsp;&nbsp;object doesn't have a symbol table<br/>",
        "--13471-- REDIR: 0x448ffb0 (strncmp) redirected to 0x4020479 (_vgnU_ifunc_wrapper)<br/>",
        "--13471-- REDIR: 0x4497140 (strstr) redirected to 0x4020479 (_vgnU_ifunc_wrapper)<br/>",
        "--13471-- REDIR: 0x4496db0 (__GI_strstr) redirected to 0x4028ef1 (strstr)<br/>",
        "--13471-- REDIR: 0x44900b0 (rindex) redirected to 0x4026acc (rindex)<br/>",
        "--13471-- REDIR: 0x439b650 (operator new(unsigned int)) redirected to 0x4026398 (operator new(unsigned int))<br/>",
        "--13471-- REDIR: 0x448bef0 (malloc) redirected to 0x40267df (malloc)<br/>",
        "--13471-- REDIR: 0x448fd80 (__GI_strlen) redirected to 0x402702d (__GI_strlen)<br/>",
        "--13471-- REDIR: 0x448f740 (strcmp) redirected to 0x4020479 (_vgnU_ifunc_wrapper)<br/>",
        "--13471-- REDIR: 0x4538cb0 (__strcmp_ssse3) redirected to 0x40279d0 (strcmp)<br/>",
        "--13471-- REDIR: 0x43994b0 (operator delete(void*)) redirected to 0x4025882 (operator delete(void*))<br/>",
        "--13471-- REDIR: 0x448c3b0 (free) redirected to 0x4025b6b (free)<br/>",
        "==13471== <br/>",
        "==13471== HEAP SUMMARY:<br/>",
        "==13471==&nbsp;&nbsp;&nbsp;&nbsp; in use at exit: 0 bytes in 0 blocks<br/>",
        "==13471==&nbsp;&nbsp; total heap usage: 8 allocs, 8 frees, 336 bytes allocated<br/>",
        "==13471== <br/>",
        "==13471== All heap blocks were freed -- no leaks are possible<br/>",
        "==13471== <br/>",
        "==13471== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 33 from 6)<br/>",
        "--13471-- <br/>",
        "--13471-- used_suppression:&nbsp;&nbsp;&nbsp;&nbsp; 33 U1004-ARM-_dl_relocate_object<br/>",
        "==13471== <br/>",
        "==13471== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 33 from 6)<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>Zero errors, excellent!</p>"
      }
    }
  );
  m.push_back(
    { "CppMemcheckExample2",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppMemcheckExample2.htm\">memcheck example 2: a small memory leak</a> is a ",
        "<a href=\"CppMemcheck.htm\">memcheck</a> example that shows how <a href=\"CppMemcheck.htm\">memcheck</a>",
        "reports a <a href=\"CppMemoryLeak.htm\">memory leak</a> we put in on purpose.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppMemcheckExample2.zip\">Download the Qt Creator project 'CppMemcheckExample2' (zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>valgrind_memcheck.txt</h2>",
        "<p>&nbsp;</p>",
        "<p>Running the script valgrind_memcheck.sh resulted in the following output file:</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"memcheck result\" border = \"1\"><tr><td><code>",
        "==13939== Memcheck, a memory error detector<br/>",
        "==13939== Copyright (C) 2002-2010, and GNU GPL'd, by Julian Seward et al.<br/>",
        "==13939== Using Valgrind-3.6.1 and LibVEX; rerun with -h for copyright info<br/>",
        "==13939== Command: ../CppMemcheckExample2-build-desktop/./CppMemcheckExample2<br/>",
        "==13939== Parent PID: 13938<br/>",
        "==13939== <br/>",
        "--13939-- <br/>",
        "--13939-- Valgrind options:<br/>",
        "--13939--&nbsp;&nbsp;&nbsp;&nbsp;--suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp<br/>",
        "--13939--&nbsp;&nbsp;&nbsp;&nbsp;--leak-check=full<br/>",
        "--13939--&nbsp;&nbsp;&nbsp;&nbsp;-v<br/>",
        "--13939--&nbsp;&nbsp;&nbsp;&nbsp;--show-reachable=yes<br/>",
        "--13939--&nbsp;&nbsp;&nbsp;&nbsp;--log-file=valgrind_memcheck.txt<br/>",
        "--13939-- Contents of /proc/version:<br/>",
        "--13939--&nbsp;&nbsp; Linux version 2.6.38-8-generic-pae (buildd@vernadsky) (gcc version 4.5.2 (Ubuntu/Linaro 4.5.2-8ubuntu3) ) #42-Ubuntu SMP Mon Apr 11 05:17:09 UTC 2011<br/>",
        "--13939-- Arch and hwcaps: X86, x86-sse1-sse2<br/>",
        "--13939-- Page sizes: currently 4096, max supported 4096<br/>",
        "--13939-- Valgrind library directory: /usr/lib/valgrind<br/>",
        "--13939-- Reading syms from /lib/i386-linux-gnu/ld-2.13.so (0x4000000)<br/>",
        "--13939--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/ld-2.13.so ..<br/>",
        "--13939--&nbsp;&nbsp; .. CRC mismatch (computed 2a2c2799 wanted 1e351f1f)<br/>",
        "--13939--&nbsp;&nbsp; Considering /usr/lib/debug/lib/i386-linux-gnu/ld-2.13.so ..<br/>",
        "--13939--&nbsp;&nbsp; .. CRC is valid<br/>",
        "--13939-- Reading syms from /home/richel/Projects/Website/CppMemcheckExample2-build-desktop/CppMemcheckExample2 (0x8048000)<br/>",
        "--13939-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)<br/>",
        "--13939--&nbsp;&nbsp;&nbsp;&nbsp;object doesn't have a dynamic symbol table<br/>",
        "--13939-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp<br/>",
        "--13939-- Reading suppressions file: /usr/lib/valgrind/default.supp<br/>",
        "--13939-- REDIR: 0x4016a80 (index) redirected to 0x3803f82b (vgPlain_x86_linux_REDIR_FOR_index)<br/>",
        "--13939-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x4020000)<br/>",
        "--13939-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4023000)<br/>",
        "==13939== WARNING: new redirection conflicts with existing -- ignoring it<br/>",
        "--13939--&nbsp;&nbsp;&nbsp;&nbsp; new: 0x04016a80 (index&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ) R-&gt; 0x04026c78 index<br/>",
        "--13939-- REDIR: 0x4016c20 (strlen) redirected to 0x4027048 (strlen)<br/>",
        "--13939-- Reading syms from /usr/lib/libQtCore.so.4.7.2 (0x4043000)<br/>",
        "--13939--&nbsp;&nbsp; Considering /usr/lib/libQtCore.so.4.7.2 ..<br/>",
        "--13939--&nbsp;&nbsp; .. CRC mismatch (computed 0c8a8d9d wanted ce78deb8)<br/>",
        "--13939--&nbsp;&nbsp; Considering /usr/lib/debug/usr/lib/libQtCore.so.4.7.2 ..<br/>",
        "--13939--&nbsp;&nbsp; .. CRC is valid<br/>",
        "--13939-- Reading syms from /lib/i386-linux-gnu/libpthread-2.13.so (0x42d6000)<br/>",
        "--13939--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/libpthread-2.13.so ..<br/>",
        "--13939--&nbsp;&nbsp; .. CRC mismatch (computed 87269ed5 wanted 7df95f2f)<br/>",
        "--13939--&nbsp;&nbsp; Considering /usr/lib/debug/lib/i386-linux-gnu/libpthread-2.13.so ..<br/>",
        "--13939--&nbsp;&nbsp; .. CRC is valid<br/>",
        "--13939-- Reading syms from /usr/lib/i386-linux-gnu/libstdc++.so.6.0.14 (0x42ef000)<br/>",
        "--13939--&nbsp;&nbsp;&nbsp;&nbsp;object doesn't have a symbol table<br/>",
        "--13939-- Reading syms from /lib/i386-linux-gnu/libm-2.13.so (0x43da000)<br/>",
        "--13939--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/libm-2.13.so ..<br/>",
        "--13939--&nbsp;&nbsp; .. CRC mismatch (computed e686ed93 wanted a0f1e52c)<br/>",
        "--13939--&nbsp;&nbsp; Considering /usr/lib/debug/lib/i386-linux-gnu/libm-2.13.so ..<br/>",
        "--13939--&nbsp;&nbsp; .. CRC is valid<br/>",
        "--13939-- Reading syms from /lib/i386-linux-gnu/libgcc_s.so.1 (0x4400000)<br/>",
        "--13939--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/libgcc_s.so.1 ..<br/>",
        "--13939--&nbsp;&nbsp; .. CRC mismatch (computed 3fa6d24f wanted 8b2bf89f)<br/>",
        "--13939--&nbsp;&nbsp;&nbsp;&nbsp;object doesn't have a symbol table<br/>",
        "--13939-- Reading syms from /lib/i386-linux-gnu/libc-2.13.so (0x441c000)<br/>",
        "--13939--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/libc-2.13.so ..<br/>",
        "--13939--&nbsp;&nbsp; .. CRC mismatch (computed 97e88cd2 wanted 4635a554)<br/>",
        "--13939--&nbsp;&nbsp; Considering /usr/lib/debug/lib/i386-linux-gnu/libc-2.13.so ..<br/>",
        "--13939--&nbsp;&nbsp; .. CRC is valid<br/>",
        "--13939-- Reading syms from /lib/i386-linux-gnu/libz.so.1.2.3.4 (0x457e000)<br/>",
        "--13939--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/libz.so.1.2.3.4 ..<br/>",
        "--13939--&nbsp;&nbsp; .. CRC mismatch (computed 995eb12f wanted 33a06a21)<br/>",
        "--13939--&nbsp;&nbsp;&nbsp;&nbsp;object doesn't have a symbol table<br/>",
        "--13939-- Reading syms from /lib/i386-linux-gnu/libdl-2.13.so (0x4593000)<br/>",
        "--13939--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/libdl-2.13.so ..<br/>",
        "--13939--&nbsp;&nbsp; .. CRC mismatch (computed 608d0daf wanted 983d6578)<br/>",
        "--13939--&nbsp;&nbsp; Considering /usr/lib/debug/lib/i386-linux-gnu/libdl-2.13.so ..<br/>",
        "--13939--&nbsp;&nbsp; .. CRC is valid<br/>",
        "--13939-- Reading syms from /usr/lib/i386-linux-gnu/libgthread-2.0.so.0.2800.6 (0x4597000)<br/>",
        "--13939--&nbsp;&nbsp; Considering /usr/lib/i386-linux-gnu/libgthread-2.0.so.0.2800.6 ..<br/>",
        "--13939--&nbsp;&nbsp; .. CRC mismatch (computed 244482a3 wanted 61a9cd3c)<br/>",
        "--13939--&nbsp;&nbsp;&nbsp;&nbsp;object doesn't have a symbol table<br/>",
        "--13939-- Reading syms from /lib/i386-linux-gnu/librt-2.13.so (0x459c000)<br/>",
        "--13939--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/librt-2.13.so ..<br/>",
        "--13939--&nbsp;&nbsp; .. CRC mismatch (computed 680ec6ea wanted 247d4d27)<br/>",
        "--13939--&nbsp;&nbsp; Considering /usr/lib/debug/lib/i386-linux-gnu/librt-2.13.so ..<br/>",
        "--13939--&nbsp;&nbsp; .. CRC is valid<br/>",
        "--13939-- Reading syms from /lib/i386-linux-gnu/libglib-2.0.so.0.2800.6 (0x45a5000)<br/>",
        "--13939--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/libglib-2.0.so.0.2800.6 ..<br/>",
        "--13939--&nbsp;&nbsp; .. CRC mismatch (computed 2312631e wanted e21a44de)<br/>",
        "--13939--&nbsp;&nbsp;&nbsp;&nbsp;object doesn't have a symbol table<br/>",
        "--13939-- Reading syms from /lib/i386-linux-gnu/libpcre.so.3.12.1 (0x467d000)<br/>",
        "--13939--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/libpcre.so.3.12.1 ..<br/>",
        "--13939--&nbsp;&nbsp; .. CRC mismatch (computed 9e5ab3c1 wanted 29aaf7e3)<br/>",
        "--13939--&nbsp;&nbsp;&nbsp;&nbsp;object doesn't have a symbol table<br/>",
        "--13939-- REDIR: 0x448ffb0 (strncmp) redirected to 0x4020479 (_vgnU_ifunc_wrapper)<br/>",
        "--13939-- REDIR: 0x4497140 (strstr) redirected to 0x4020479 (_vgnU_ifunc_wrapper)<br/>",
        "--13939-- REDIR: 0x4496db0 (__GI_strstr) redirected to 0x4028ef1 (strstr)<br/>",
        "--13939-- REDIR: 0x44900b0 (rindex) redirected to 0x4026acc (rindex)<br/>",
        "--13939-- REDIR: 0x439b650 (operator new(unsigned int)) redirected to 0x4026398 (operator new(unsigned int))<br/>",
        "--13939-- REDIR: 0x448bef0 (malloc) redirected to 0x40267df (malloc)<br/>",
        "--13939-- REDIR: 0x43994b0 (operator delete(void*)) redirected to 0x4025882 (operator delete(void*))<br/>",
        "--13939-- REDIR: 0x448c3b0 (free) redirected to 0x4025b6b (free)<br/>",
        "==13939== <br/>",
        "==13939== HEAP SUMMARY:<br/>",
        "==13939==&nbsp;&nbsp;&nbsp;&nbsp; in use at exit: 4 bytes in 1 blocks<br/>",
        "==13939==&nbsp;&nbsp; total heap usage: 9 allocs, 8 frees, 340 bytes allocated<br/>",
        "==13939== <br/>",
        "==13939== Searching for pointers to 1 not-freed blocks<br/>",
        "==13939== Checked 150,724 bytes<br/>",
        "==13939== <br/>",
        "==13939== 4 bytes in 1 blocks are definitely lost in loss record 1 of 1<br/>",
        "==13939==&nbsp;&nbsp;&nbsp;&nbsp;at 0x402641D: operator new(unsigned int) (vg_replace_malloc.c:255)<br/>",
        "==13939==&nbsp;&nbsp;&nbsp;&nbsp;by 0x8048544: main (in /home/richel/Projects/Website/CppMemcheckExample2-build-desktop/CppMemcheckExample2)<br/>",
        "==13939== <br/>",
        "==13939== LEAK SUMMARY:<br/>",
        "==13939==&nbsp;&nbsp;&nbsp;&nbsp;definitely lost: 4 bytes in 1 blocks<br/>",
        "==13939==&nbsp;&nbsp;&nbsp;&nbsp;indirectly lost: 0 bytes in 0 blocks<br/>",
        "==13939==&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;possibly lost: 0 bytes in 0 blocks<br/>",
        "==13939==&nbsp;&nbsp;&nbsp;&nbsp;still reachable: 0 bytes in 0 blocks<br/>",
        "==13939==&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; suppressed: 0 bytes in 0 blocks<br/>",
        "==13939== <br/>",
        "==13939== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 33 from 6)<br/>",
        "--13939-- <br/>",
        "--13939-- used_suppression:&nbsp;&nbsp;&nbsp;&nbsp; 33 U1004-ARM-_dl_relocate_object<br/>",
        "==13939== <br/>",
        "==13939== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 33 from 6)<br/>",
        "<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppValgrind.htm\">valgrind</a> did detect the <a href=\"CppMemoryLeak.htm\">memory leak</a> in ",
        "<a href=\"CppMain.htm\">main</a>, but does not report exactly which line caused this.</p>"
      }
    }
  );
  m.push_back(
    { "CppMemcheckExample3",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppMemcheckExample3.htm\">memcheck example 3: deleting an array the wrong way</a> is a ",
        "<a href=\"CppMemcheck.htm\">memcheck</a> example shows how <a href=\"CppMemcheck.htm\">memcheck</a>",
        "reports a <a href=\"CppMemoryLeak.htm\">memory leak</a> we put in on purpose.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppMemcheckExample3.zip\">Download the Qt Creator project 'CppMemcheckExample3' (zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>valgrind_memcheck.txt</h2>",
        "<p>&nbsp;</p>",
        "<p>Running the script valgrind_memcheck.sh resulted in the following output file:</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"memcheck result\" border = \"1\"><tr><td><code>",
        "==14146== Memcheck, a memory error detector<br/>",
        "==14146== Copyright (C) 2002-2010, and GNU GPL'd, by Julian Seward et al.<br/>",
        "==14146== Using Valgrind-3.6.1 and LibVEX; rerun with -h for copyright info<br/>",
        "==14146== Command: ../CppMemcheckExample3-build-desktop/./CppMemcheckExample3<br/>",
        "==14146== Parent PID: 14145<br/>",
        "==14146== <br/>",
        "--14146-- <br/>",
        "--14146-- Valgrind options:<br/>",
        "--14146--&nbsp;&nbsp;&nbsp;&nbsp;--suppressions=/usr/lib/valgrind/debian-libc6-dbg.supp<br/>",
        "--14146--&nbsp;&nbsp;&nbsp;&nbsp;--leak-check=full<br/>",
        "--14146--&nbsp;&nbsp;&nbsp;&nbsp;-v<br/>",
        "--14146--&nbsp;&nbsp;&nbsp;&nbsp;--show-reachable=yes<br/>",
        "--14146--&nbsp;&nbsp;&nbsp;&nbsp;--log-file=valgrind_memcheck.txt<br/>",
        "--14146-- Contents of /proc/version:<br/>",
        "--14146--&nbsp;&nbsp; Linux version 2.6.38-8-generic-pae (buildd@vernadsky) (gcc version 4.5.2 (Ubuntu/Linaro 4.5.2-8ubuntu3) ) #42-Ubuntu SMP Mon Apr 11 05:17:09 UTC 2011<br/>",
        "--14146-- Arch and hwcaps: X86, x86-sse1-sse2<br/>",
        "--14146-- Page sizes: currently 4096, max supported 4096<br/>",
        "--14146-- Valgrind library directory: /usr/lib/valgrind<br/>",
        "--14146-- Reading syms from /lib/i386-linux-gnu/ld-2.13.so (0x4000000)<br/>",
        "--14146--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/ld-2.13.so ..<br/>",
        "--14146--&nbsp;&nbsp; .. CRC mismatch (computed 2a2c2799 wanted 1e351f1f)<br/>",
        "--14146--&nbsp;&nbsp; Considering /usr/lib/debug/lib/i386-linux-gnu/ld-2.13.so ..<br/>",
        "--14146--&nbsp;&nbsp; .. CRC is valid<br/>",
        "--14146-- Reading syms from /home/richel/Projects/Website/CppMemcheckExample3-build-desktop/CppMemcheckExample3 (0x8048000)<br/>",
        "--14146-- Reading syms from /usr/lib/valgrind/memcheck-x86-linux (0x38000000)<br/>",
        "--14146--&nbsp;&nbsp;&nbsp;&nbsp;object doesn't have a dynamic symbol table<br/>",
        "--14146-- Reading suppressions file: /usr/lib/valgrind/debian-libc6-dbg.supp<br/>",
        "--14146-- Reading suppressions file: /usr/lib/valgrind/default.supp<br/>",
        "--14146-- REDIR: 0x4016a80 (index) redirected to 0x3803f82b (vgPlain_x86_linux_REDIR_FOR_index)<br/>",
        "--14146-- Reading syms from /usr/lib/valgrind/vgpreload_core-x86-linux.so (0x4020000)<br/>",
        "--14146-- Reading syms from /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so (0x4023000)<br/>",
        "==14146== WARNING: new redirection conflicts with existing -- ignoring it<br/>",
        "--14146--&nbsp;&nbsp;&nbsp;&nbsp; new: 0x04016a80 (index&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ) R-&gt; 0x04026c78 index<br/>",
        "--14146-- REDIR: 0x4016c20 (strlen) redirected to 0x4027048 (strlen)<br/>",
        "--14146-- Reading syms from /usr/lib/libQtCore.so.4.7.2 (0x4043000)<br/>",
        "--14146--&nbsp;&nbsp; Considering /usr/lib/libQtCore.so.4.7.2 ..<br/>",
        "--14146--&nbsp;&nbsp; .. CRC mismatch (computed 0c8a8d9d wanted ce78deb8)<br/>",
        "--14146--&nbsp;&nbsp; Considering /usr/lib/debug/usr/lib/libQtCore.so.4.7.2 ..<br/>",
        "--14146--&nbsp;&nbsp; .. CRC is valid<br/>",
        "--14146-- Reading syms from /lib/i386-linux-gnu/libpthread-2.13.so (0x42d6000)<br/>",
        "--14146--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/libpthread-2.13.so ..<br/>",
        "--14146--&nbsp;&nbsp; .. CRC mismatch (computed 87269ed5 wanted 7df95f2f)<br/>",
        "--14146--&nbsp;&nbsp; Considering /usr/lib/debug/lib/i386-linux-gnu/libpthread-2.13.so ..<br/>",
        "--14146--&nbsp;&nbsp; .. CRC is valid<br/>",
        "--14146-- Reading syms from /usr/lib/i386-linux-gnu/libstdc++.so.6.0.14 (0x42ef000)<br/>",
        "--14146--&nbsp;&nbsp;&nbsp;&nbsp;object doesn't have a symbol table<br/>",
        "--14146-- Reading syms from /lib/i386-linux-gnu/libm-2.13.so (0x43da000)<br/>",
        "--14146--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/libm-2.13.so ..<br/>",
        "--14146--&nbsp;&nbsp; .. CRC mismatch (computed e686ed93 wanted a0f1e52c)<br/>",
        "--14146--&nbsp;&nbsp; Considering /usr/lib/debug/lib/i386-linux-gnu/libm-2.13.so ..<br/>",
        "--14146--&nbsp;&nbsp; .. CRC is valid<br/>",
        "--14146-- Reading syms from /lib/i386-linux-gnu/libgcc_s.so.1 (0x4400000)<br/>",
        "--14146--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/libgcc_s.so.1 ..<br/>",
        "--14146--&nbsp;&nbsp; .. CRC mismatch (computed 3fa6d24f wanted 8b2bf89f)<br/>",
        "--14146--&nbsp;&nbsp;&nbsp;&nbsp;object doesn't have a symbol table<br/>",
        "--14146-- Reading syms from /lib/i386-linux-gnu/libc-2.13.so (0x441c000)<br/>",
        "--14146--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/libc-2.13.so ..<br/>",
        "--14146--&nbsp;&nbsp; .. CRC mismatch (computed 97e88cd2 wanted 4635a554)<br/>",
        "--14146--&nbsp;&nbsp; Considering /usr/lib/debug/lib/i386-linux-gnu/libc-2.13.so ..<br/>",
        "--14146--&nbsp;&nbsp; .. CRC is valid<br/>",
        "--14146-- Reading syms from /lib/i386-linux-gnu/libz.so.1.2.3.4 (0x457e000)<br/>",
        "--14146--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/libz.so.1.2.3.4 ..<br/>",
        "--14146--&nbsp;&nbsp; .. CRC mismatch (computed 995eb12f wanted 33a06a21)<br/>",
        "--14146--&nbsp;&nbsp;&nbsp;&nbsp;object doesn't have a symbol table<br/>",
        "--14146-- Reading syms from /lib/i386-linux-gnu/libdl-2.13.so (0x4593000)<br/>",
        "--14146--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/libdl-2.13.so ..<br/>",
        "--14146--&nbsp;&nbsp; .. CRC mismatch (computed 608d0daf wanted 983d6578)<br/>",
        "--14146--&nbsp;&nbsp; Considering /usr/lib/debug/lib/i386-linux-gnu/libdl-2.13.so ..<br/>",
        "--14146--&nbsp;&nbsp; .. CRC is valid<br/>",
        "--14146-- Reading syms from /usr/lib/i386-linux-gnu/libgthread-2.0.so.0.2800.6 (0x4597000)<br/>",
        "--14146--&nbsp;&nbsp; Considering /usr/lib/i386-linux-gnu/libgthread-2.0.so.0.2800.6 ..<br/>",
        "--14146--&nbsp;&nbsp; .. CRC mismatch (computed 244482a3 wanted 61a9cd3c)<br/>",
        "--14146--&nbsp;&nbsp;&nbsp;&nbsp;object doesn't have a symbol table<br/>",
        "--14146-- Reading syms from /lib/i386-linux-gnu/librt-2.13.so (0x459c000)<br/>",
        "--14146--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/librt-2.13.so ..<br/>",
        "--14146--&nbsp;&nbsp; .. CRC mismatch (computed 680ec6ea wanted 247d4d27)<br/>",
        "--14146--&nbsp;&nbsp; Considering /usr/lib/debug/lib/i386-linux-gnu/librt-2.13.so ..<br/>",
        "--14146--&nbsp;&nbsp; .. CRC is valid<br/>",
        "--14146-- Reading syms from /lib/i386-linux-gnu/libglib-2.0.so.0.2800.6 (0x45a5000)<br/>",
        "--14146--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/libglib-2.0.so.0.2800.6 ..<br/>",
        "--14146--&nbsp;&nbsp; .. CRC mismatch (computed 2312631e wanted e21a44de)<br/>",
        "--14146--&nbsp;&nbsp;&nbsp;&nbsp;object doesn't have a symbol table<br/>",
        "--14146-- Reading syms from /lib/i386-linux-gnu/libpcre.so.3.12.1 (0x467d000)<br/>",
        "--14146--&nbsp;&nbsp; Considering /lib/i386-linux-gnu/libpcre.so.3.12.1 ..<br/>",
        "--14146--&nbsp;&nbsp; .. CRC mismatch (computed 9e5ab3c1 wanted 29aaf7e3)<br/>",
        "--14146--&nbsp;&nbsp;&nbsp;&nbsp;object doesn't have a symbol table<br/>",
        "--14146-- REDIR: 0x448ffb0 (strncmp) redirected to 0x4020479 (_vgnU_ifunc_wrapper)<br/>",
        "--14146-- REDIR: 0x4497140 (strstr) redirected to 0x4020479 (_vgnU_ifunc_wrapper)<br/>",
        "--14146-- REDIR: 0x4496db0 (__GI_strstr) redirected to 0x4028ef1 (strstr)<br/>",
        "--14146-- REDIR: 0x44900b0 (rindex) redirected to 0x4026acc (rindex)<br/>",
        "--14146-- REDIR: 0x439b650 (operator new(unsigned int)) redirected to 0x4026398 (operator new(unsigned int))<br/>",
        "--14146-- REDIR: 0x448bef0 (malloc) redirected to 0x40267df (malloc)<br/>",
        "--14146-- REDIR: 0x439b790 (operator new[](unsigned int)) redirected to 0x4025ece (operator new[](unsigned int))<br/>",
        "--14146-- REDIR: 0x4399510 (operator delete[](void*)) redirected to 0x4025504 (operator delete[](void*))<br/>",
        "--14146-- REDIR: 0x43994b0 (operator delete(void*)) redirected to 0x4025882 (operator delete(void*))<br/>",
        "==14146== Mismatched free() / delete / delete []<br/>",
        "==14146==&nbsp;&nbsp;&nbsp;&nbsp;at 0x4025907: operator delete(void*) (vg_replace_malloc.c:387)<br/>",
        "==14146==&nbsp;&nbsp;&nbsp;&nbsp;by 0x80485D9: Bad() (in /home/richel/Projects/Website/CppMemcheckExample3-build-desktop/CppMemcheckExample3)<br/>",
        "==14146==&nbsp;&nbsp;&nbsp;&nbsp;by 0x80485EF: main (in /home/richel/Projects/Website/CppMemcheckExample3-build-desktop/CppMemcheckExample3)<br/>",
        "==14146==&nbsp;&nbsp;Address 0x46be360 is 0 bytes inside a block of size 40 alloc'd<br/>",
        "==14146==&nbsp;&nbsp;&nbsp;&nbsp;at 0x4025F53: operator new[](unsigned int) (vg_replace_malloc.c:299)<br/>",
        "==14146==&nbsp;&nbsp;&nbsp;&nbsp;by 0x80485D1: Bad() (in /home/richel/Projects/Website/CppMemcheckExample3-build-desktop/CppMemcheckExample3)<br/>",
        "==14146==&nbsp;&nbsp;&nbsp;&nbsp;by 0x80485EF: main (in /home/richel/Projects/Website/CppMemcheckExample3-build-desktop/CppMemcheckExample3)<br/>",
        "==14146== <br/>",
        "==14146== Mismatched free() / delete / delete []<br/>",
        "==14146==&nbsp;&nbsp;&nbsp;&nbsp;at 0x4025907: operator delete(void*) (vg_replace_malloc.c:387)<br/>",
        "==14146==&nbsp;&nbsp;&nbsp;&nbsp;by 0x80485D9: Bad() (in /home/richel/Projects/Website/CppMemcheckExample3-build-desktop/CppMemcheckExample3)<br/>",
        "==14146==&nbsp;&nbsp;&nbsp;&nbsp;by 0x80485F9: main (in /home/richel/Projects/Website/CppMemcheckExample3-build-desktop/CppMemcheckExample3)<br/>",
        "==14146==&nbsp;&nbsp;Address 0x46be410 is 0 bytes inside a block of size 40 alloc'd<br/>",
        "==14146==&nbsp;&nbsp;&nbsp;&nbsp;at 0x4025F53: operator new[](unsigned int) (vg_replace_malloc.c:299)<br/>",
        "==14146==&nbsp;&nbsp;&nbsp;&nbsp;by 0x80485D1: Bad() (in /home/richel/Projects/Website/CppMemcheckExample3-build-desktop/CppMemcheckExample3)<br/>",
        "==14146==&nbsp;&nbsp;&nbsp;&nbsp;by 0x80485F9: main (in /home/richel/Projects/Website/CppMemcheckExample3-build-desktop/CppMemcheckExample3)<br/>",
        "==14146== <br/>",
        "--14146-- REDIR: 0x448c3b0 (free) redirected to 0x4025b6b (free)<br/>",
        "==14146== <br/>",
        "==14146== HEAP SUMMARY:<br/>",
        "==14146==&nbsp;&nbsp;&nbsp;&nbsp; in use at exit: 0 bytes in 0 blocks<br/>",
        "==14146==&nbsp;&nbsp; total heap usage: 12 allocs, 12 frees, 496 bytes allocated<br/>",
        "==14146== <br/>",
        "==14146== All heap blocks were freed -- no leaks are possible<br/>",
        "==14146== <br/>",
        "==14146== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 33 from 6)<br/>",
        "==14146== <br/>",
        "==14146== 1 errors in context 1 of 2:<br/>",
        "==14146== Mismatched free() / delete / delete []<br/>",
        "==14146==&nbsp;&nbsp;&nbsp;&nbsp;at 0x4025907: operator delete(void*) (vg_replace_malloc.c:387)<br/>",
        "==14146==&nbsp;&nbsp;&nbsp;&nbsp;by 0x80485D9: Bad() (in /home/richel/Projects/Website/CppMemcheckExample3-build-desktop/CppMemcheckExample3)<br/>",
        "==14146==&nbsp;&nbsp;&nbsp;&nbsp;by 0x80485F9: main (in /home/richel/Projects/Website/CppMemcheckExample3-build-desktop/CppMemcheckExample3)<br/>",
        "==14146==&nbsp;&nbsp;Address 0x46be410 is 0 bytes inside a block of size 40 alloc'd<br/>",
        "==14146==&nbsp;&nbsp;&nbsp;&nbsp;at 0x4025F53: operator new[](unsigned int) (vg_replace_malloc.c:299)<br/>",
        "==14146==&nbsp;&nbsp;&nbsp;&nbsp;by 0x80485D1: Bad() (in /home/richel/Projects/Website/CppMemcheckExample3-build-desktop/CppMemcheckExample3)<br/>",
        "==14146==&nbsp;&nbsp;&nbsp;&nbsp;by 0x80485F9: main (in /home/richel/Projects/Website/CppMemcheckExample3-build-desktop/CppMemcheckExample3)<br/>",
        "==14146== <br/>",
        "==14146== <br/>",
        "==14146== 1 errors in context 2 of 2:<br/>",
        "==14146== Mismatched free() / delete / delete []<br/>",
        "==14146==&nbsp;&nbsp;&nbsp;&nbsp;at 0x4025907: operator delete(void*) (vg_replace_malloc.c:387)<br/>",
        "==14146==&nbsp;&nbsp;&nbsp;&nbsp;by 0x80485D9: Bad() (in /home/richel/Projects/Website/CppMemcheckExample3-build-desktop/CppMemcheckExample3)<br/>",
        "==14146==&nbsp;&nbsp;&nbsp;&nbsp;by 0x80485EF: main (in /home/richel/Projects/Website/CppMemcheckExample3-build-desktop/CppMemcheckExample3)<br/>",
        "==14146==&nbsp;&nbsp;Address 0x46be360 is 0 bytes inside a block of size 40 alloc'd<br/>",
        "==14146==&nbsp;&nbsp;&nbsp;&nbsp;at 0x4025F53: operator new[](unsigned int) (vg_replace_malloc.c:299)<br/>",
        "==14146==&nbsp;&nbsp;&nbsp;&nbsp;by 0x80485D1: Bad() (in /home/richel/Projects/Website/CppMemcheckExample3-build-desktop/CppMemcheckExample3)<br/>",
        "==14146==&nbsp;&nbsp;&nbsp;&nbsp;by 0x80485EF: main (in /home/richel/Projects/Website/CppMemcheckExample3-build-desktop/CppMemcheckExample3)<br/>",
        "==14146== <br/>",
        "--14146-- <br/>",
        "--14146-- used_suppression:&nbsp;&nbsp;&nbsp;&nbsp; 33 U1004-ARM-_dl_relocate_object<br/>",
        "==14146== <br/>",
        "==14146== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 33 from 6)<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppValgrind.htm\">valgrind</a> did detect the <a href=\"CppMemoryLeak.htm\">memory leak</a> in ",
        "<a href=\"CppMain.htm\">main</a>, but does not report exactly which line caused this.</p>"
      }
    }
  );
  m.push_back(
    { "CppMemcheckExample4",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppMemcheckExample4.htm\">memcheck example 4: Hello Qt</a> is a <a href=\"CppMemcheck.htm\">memcheck</a> example ",
        "  that tests a <a href=\"CppHelloQtQtCreatorUbuntu.htm\">'Hello Qt' program using Qt Creator under Ubuntu</a> for possible problems.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppMemcheckExample4.zip\">Download the Qt Creator project 'CppMemcheckExample4' (zip)</a></li>",
        "  <li><a href=\"CppMemcheckExample4.txt\">View the valgrind output of 'CppMemcheckExample4' (txt)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"CppMemcheckExample4.txt\">valgrind_memcheck.txt</a></h2>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppValgrind.htm\">valgrind</a> finds a lot of problems! Because the output is too big to display here, you can",
        "<a href=\"CppMemcheckExample4.txt\">view valgrind_memcheck.txt here</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppMemcheckExample5",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppMemcheckExample5.htm\">memcheck example 5: Hello Qt</a> is a <a href=\"CppMemcheck.htm\">memcheck</a> example ",
        "that tests a <a href=\"CppHelloQtQtCreatorUbuntu.htm\">'Hello Qt' program using Qt Creator under Ubuntu</a> for possible problems.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppMemcheckExample5.zip\">Download the Qt Creator project 'CppMemcheckExample5' (zip)</a></li>",
        "  <li><a href=\"CppMemcheckExample5.txt\">View the valgrind output of 'CppMemcheckExample5' (txt)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"CppMemcheckExample5.txt\">valgrind_memcheck.txt</a></h2>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppValgrind.htm\">valgrind</a> finds a lot of problems! Because the output is too big to display here, you can",
        "<a href=\"CppMemcheckExample4.txt\">view valgrind_memcheck.txt here</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppMemcheckExample6",
      {
        "<p><img src=\"PicWt.png\" alt=\"Wt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppMemcheckExample6.htm\">memcheck example 6: how to stop a Wt server</a> is a ",
        "<a href=\"CppMemcheck.htm\">memcheck</a> example that tests how to stop a <a href=\"CppWt.htm\">Wt</a> server cleanly.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppMemcheckExample6.zip\">Download the Qt Creator project 'CppMemcheckExample6' (zip)</a></li>",
        "  <li><a href=\"CppMemcheckExample6_ctrl_c.txt\">View the valgrind output of 'CppMemcheckExample6' and pressing CTRL-C (txt)</a></li>",
        "  <li><a href=\"CppMemcheckExample6_exit.txt\">View the valgrind output of 'CppMemcheckExample6' and calling std::exit(0) (txt)</a></li>",
        "  <li><a href=\"CppMemcheckExample6_throw.txt\">View the valgrind output of 'CppMemcheckExample6' and calling throw (txt)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>This example was developed, because tools like <a href=\"CppValgrind.htm\">valgrind</a> ",
        "and the <a href=\"CppProfiler.htm\">profiler</a> <a href=\"CppGprof.htm\">gprof</a> require a program to quit without errors.</p>",
        "<p>&nbsp;</p>",
        "<p>This web application creates four buttons, that each use a different way to let <a href=\"CppMain.htm\">main</a> ",
        "<a href=\"CppReturn.htm\">return</a>. Of these four buttons, two are disabled: these call methods that do not cause",
        "the application to terminate (yet). When starting the web application from command line, pressing CTRL-C ",
        "is another option to cleanly terminate it.</p>"
      }
    }
  );

  m.push_back(
    { "CppMenuDialog",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppMenuDialog.htm\">MenuDialog</a> is a",
        "  <a href=\"CppClass.htm\">class</a>",
        "  for a menu dialog.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "CppMultiApproximator",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppMultiApproximator.htm\">MultiApproximator</a> is a",
        "  <a href=\"CppClass.htm\">class</a> to perform an interpolation",
        "  on data. For example, when the supplied data consists of the coordinats",
        "  (1,1) and (2,2), it will estimate (the x value of) 1,5 to be (the value y value of) 1,5.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppMultiApproximator.htm\">MultiApproximator</a> supports multiple",
        "  identical keys (for example the coordinats (1.0,2.0) and (1.0,3.0)),",
        "  similar to a <a href=\"CppMulti_map.htm\">std::multi_map</a>.",
        "  <a href=\"CppApproximator.htm\">Approximator</a> does not",
        "  allow this."
        "</p>"
      }
    }
  );

  m.push_back(
    { "CppMultipleChoiceQuestion",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppMultipleChoiceQuestion.htm\">MultipleChoiceQuestion</a> is a",
        "  <a href=\"CppClass.htm\">class</a>",
        "  for a multiple choice <a href=\"CppQuestion.htm\">question</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "CppMultipleChoiceQuestionDialog",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppMultipleChoiceQuestionDialog.htm\">MultipleChoiceQuestionDialog</a> is a dialog",
        "  for <a href=\"CppMultipleChoiceQuestion.htm\">MultipleChoiceQuestion</a>.",
        "</p>"
      }
    }
  );
  m.push_back(
    { "CppMultiVector",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppMultiVector.htm\">MultiVector</a> is a <a href=\"CppContainer.htm\">container</a> ",
        "<a href=\"CppClass.htm\">class</a> to store elements at indices of any dimensionality.</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppMultiVector.htm\">MultiVector</a> is demonstrated/tested with the ",
        "  <a href=\"Tools.htm\">tool</a> <a href=\"ToolTestMultiVector.htm\">TestMultiVector</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "CppMusic",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppMusic.htm\">Music</a> contains music <a href=\"CppClass.htm\">classes</a>.",
        "</p>",
      }
    }
  );

  m.push_back(
    { "CppMusicChord",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppMusicChord.htm\">MusicChord</a> is a <a href=\"CppClass.htm\">class</a> ",
        "for a music chord.</p>",
      }
    }
  );

  m.push_back(
    { "CppMusicNote",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppMusicNote.htm\">MusicChord</a> is a <a href=\"CppClass.htm\">class</a> ",
        "for a music note.</p>"
      }
    }
  );

  m.push_back(
    { "CppMxeExample4",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppMxeExample4.htm\">MXE example 4: Hello Boost</a> is an <a href=\"CppMxe.htm\">MXE</a> example",
        "to <a href=\"CppCrossCompile.htm\">cross-compile</a> a <a href=\"CppHelloBoost.htm\">Hello Boost</a> program from",
        "<a href=\"CppLinux.htm\">GNU/Linux</a> to <a href=\"CppWindows.htm\">Windows</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppMxeExample4.zip\">Download the Qt Creator project 'CppMxeExample4' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppMxeExample5",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppMxeExample5.htm\">MXE example 5: Hello Boost.Regex</a> is an <a href=\"CppMxe.htm\">MXE</a> example",
        "to <a href=\"CppCrossCompile.htm\">cross-compile</a> a <a href=\"CppHelloBoost.htm\">Hello Boost</a> program from",
        "<a href=\"CppLinux.htm\">GNU/Linux</a> to <a href=\"CppWindows.htm\">Windows</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>Note that for me, this code does not cross-compile.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppMxeExample5.zip\">Download the Qt Creator project 'CppMxeExample5' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppMysteryMachine",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppMysteryMachine.htm\">MysteryMachine</a> is a <a href=\"CppClass.htm\">class</a> to simulate",
        "my mystery machine.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppMysteryMachine.htm\">MysteryMachine</a> is used in the  ",
        "<a href=\"Tools.htm\">tool</a> <a href=\"ToolSimMysteryMachine.htm\">SimMysteryMachine</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppMysteryMachineWidget",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppMysteryMachineWidget.htm\">MysteryMachineWidget</a> is a <a href=\"CppMysteryMachineWidget.htm\">MysteryMachineWidget</a> <a href=\"CppWidget.htm\">widget</a>.</p>"
      }
    }
  );

  m.push_back(
    { "CppNamespaceExample1",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppNamespaceExample1.htm\">namespace example 1: scopes</a> is a",
        "  <a href=\"CppNamespace.htm\">namespace</a> <a href=\"CppExample.htm\">example</a>.",
        "</p>",
        "<p>",
        "  In the example, three versions of the function SayHello reside in different",
        "  <a href=\"CppNamespace.htm\">namespaces</a>: loud, soft and the <a href=\"CppGlobal.htm\">global</a>",
        "  <a href=\"CppNamespace.htm\">namespace</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppNamespaceExample1.zip\">Download the Qt Creator project 'CppNamespaceExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );



  m.push_back(
    { "CppNarmedBanditLearner",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<a href=\"CppArtificialIntelligence.htm\">Artificial Intelligence</a> <a href=\"CppCodeSnippets.htm\">code snippet</a>",
        "how to implement a Learner class that has to optimize its"
        "reward from an N-armed bandit. As one would expect, the Learner class knows nothing"
        "about the N-Armed Bandit class' internals.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  Give a Learner a set of actions, with every action having a certain expected reward.",
        "  Actions taken are evaluated by adjusting the expected rewards. The chance an",
        "  action is equal to its expected reward of the sum of expected rewards.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  The Learner class has an internal <a href=\"CppDesignPatternStrategy.htm\">Strategy</a>",
        "  <a href=\"CppDesignPattern.htm\">Design Pattern</a>, which enables the user to",
        "  select a different Learning Strategy at run-time. In the example main, this",
        "  Strategy is set randomly.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppNarmedBanditLearnerSource.zip\">Download the 'NarmedBanditLearner' source code (zip)</a></li>",
        "  <li><a href=\"CppNarmedBanditLearnerExe.zip\">Download the 'NarmedBanditLearner' Windows executable (zip)</a></li>",
        "</ul>"
      }
    }
  );



  m.push_back(
    { "CppNewick",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>A <a href=\"CppNewick.htm\">Newick</a> is a way to write down a phylogeny as a <a href=\"CppString.htm\">std::string</a>. This page shows how to check this <a href=\"CppString.htm\">std::string</a> and how to store a <a href=\"CppNewick.htm\">Newick</a> more efficiently.</p>",
        "<p>&nbsp;</p>",
        "<p>Because personally, I only work with <a href=\"CppNewick.htm\">Newicks</a> in the form '(((A,B),(C,D)),E)', these algorithms will so as well.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"CppNewick.htm\">Newick</a> <a href=\"CppCodeSnippets.htm\">code snippets</a></h2>",
        "<p>&nbsp;</p>",
        "<ol>",
        "  <li><a href=\"CppCalcComplexity.htm\">CalcComplexity</a></li>",
        "  <li><a href=\"CppCalcNumOfCombinations.htm\">CalcNumOfCombinations</a></li>",
        "  <li><a href=\"CppCalcNumOfSymmetries.htm\">CalcNumOfSymmetries</a></li>",
        "  <li><a href=\"CppCheckNewick.htm\">CheckNewick</a></li>",
        "  <li><a href=\"CppCreateInvalidNewicks.htm\">CreateInvalidNewicks</a></li>",
        "  <li><a href=\"CppCreateValidNewicks.htm\">CreateValidNewicks</a></li>",
        "  <li><a href=\"CppDumbNewickToString.htm\">DumbNewickToString</a></li>",
        "  <li><a href=\"CppGetRootBranches.htm\">GetRootBranches</a></li>",
        "  <li><a href=\"CppGetSimplerNewicks.htm\">GetSimplerNewicks</a></li>",
        "  <li><a href=\"CppInspectInvalidNewick.htm\">InspectInvalidNewick</a></li>",
        "  <li><a href=\"CppIsBinaryNewick.htm\">IsBinaryNewick</a></li>",
        "  <li><a href=\"CppIsNewick.htm\">IsNewick</a></li>",
        "  <li><a href=\"CppNewickToString.htm\">NewickToString</a></li>",
        "  <li><a href=\"CppBinaryNewickVector.htm\">BinaryNewickVector</a></li>",
        "  <li><a href=\"CppStringToNewick.htm\">StringToNewick</a></li>",
        "</ol>"
      }
    }
  );
  m.push_back(
    { "CppNewickVector",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppNewickVector.htm\">NewickVector</a> is a <a href=\"CppNewick.htm\">Newick</a> <a href=\"CppClass.htm\">class</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppOpenQuestion",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppOpenQuestion.htm\">OpenQuestion</a> is a",
        "  <a href=\"CppClass.htm\">class</a> for an open",
        "  <a href=\"CppQuestion.htm\">question</a>.",
        "</p>"
      }
    }
  );
  m.push_back(
    { "CppOpenQuestionDialog",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppOpenQuestionDialog.htm\">OpenQuestionDialog</a> is a dialog for",
        "  <a href=\"CppOpenQuestion.htm\">OpenQuestion</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "CppPdcursesExample1",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppPdcursesExample1.htm\">PDCurses example 1: tutorial</a> is a",
        "  <a href=\"CppPdcurses.htm\">PDCurses</a> example that is a slight modification",
        "  of a tutorial its code.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "CppPdcursesExample2",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppPdcursesExample2.htm\">PDCurses example 2: first modification</a> is a",
        "  <a href=\"CppPdcurses.htm\">PDCurses</a> example that is a modification",
        "  of a tutorial its code.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "CppPdcursesExample3",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppPdcursesExample3.htm\">PDCurses example 3: text editor</a> is a",
        "  <a href=\"CppPdcurses.htm\">PDCurses</a> example that tries to behave a bit like",
        "  a text editor.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "CppPredicateExample1",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  In the example below, it is shown how to replace negative values",
        "  by zero. The predicate is if an integer is less then zero.",
        "</p>"
      }

    }
  );
  m.push_back(
    { "CppPreprocessorSwitchGccVersion",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppPreprocessorSwitchGccVersion.htm\">CppPreprocessorSwitchGccVersion</a> displays",
        "how to switch on the <a href=\"CppGcc.htm\">GCC</a> version.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppPreprocessorSwitchGccVersion.zip\">Download the Qt Creator project 'CppPreprocessorSwitchGccVersion' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppPrimeExpert",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppPrimeExpert.htm\">PrimeExpert</a> is a <a href=\"CppClass.htm\">class</a> with only one important",
        "<a href=\"CppMemberFunction.htm\">member function</a> called <a href=\"CppIsPrime.htm\">IsPrime</a>,",
        "which calculates whether a number is prime.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppPrimeExpert.htm\">PrimeExpert</a> is a trade-off between the speed of",
        "determining whether a number is prime (for multiple times) and memory consumption:",
        "to determine whether a number is prime quicker, <a href=\"CppPrimeExpert.htm\">PrimeExpert</a>",
        "maintains a <a href=\"CppVector.htm\">std::vector</a> of known primes (but of known primes only).</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppPrimeExpert.htm\">PrimeExpert</a> can be tested using the <a href=\"Tools.htm\">tool</a> ",
        "<a href=\"ToolTestPrimeExpert.htm\">TestPrimeExpert</a>.</p>"
      }

    }
  );
  m.push_back(
    { "CppPylos",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  The <a href=\"CppPylos.htm\">Pylos</a> <a href=\"CppClass.htm\">classes</a>",
        "  are used for the",
        "  <a href=\"Games.htm\">game</a> <a href=\"GamePylos.htm\">Pylos</a>",
        "  (also called 'Pyraos').",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  The <a href=\"CppPylos.htm\">Pylos</a> <a href=\"CppClass.htm\">classes</a>",
        "  are tested by <a href=\"ToolTestPylos.htm\">TestPylos page</a>.",
        "</p>"
      }
    }
  );
  m.push_back(
    { "CppQFileExample1",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQFileExample1.htm\">QFile example 1: copying file and checking if the copy exists</a> is a",
        "<a href=\"CppQFile.htm\">QFile</a> <a href=\"CppExample.htm\">example</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQFileExample1.zip\">Download the Qt Creator project 'CppQFileExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQFileDialogExample1",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQFileDialogExample1.htm\">QFileDialog example 1: crafting a QFileDialog to select a file</a> is a",
        "<a href=\"CppQFileDialog.htm\">QFileDialog</a> <a href=\"CppExample.htm\">example</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQFileDialogExample1.png\">View a screenshot of 'CppQFileDialogExample1' (png)</a></li>",
        "  <li><a href=\"CppQFileDialogExample1.zip\">Download the Qt Creator project 'CppQFileDialogExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQFileDialogExample2",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQFileDialogExample2.htm\">QFileDialog example 2: using QFileDialog::getOpenFileNames</a> is a",
        "<a href=\"CppQFileDialog.htm\">QFileDialog</a> <a href=\"CppExample.htm\">example</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQFileDialogExample2.png\">View a screenshot of 'CppQFileDialogExample2' (png)</a></li>",
        "  <li><a href=\"CppQFileDialogExample2.zip\">Download the Qt Creator project 'CppQFileDialogExample2' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQFileDialogExample3",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQFileDialogExample3.htm\">QFileDialog example 3: compare class and convenience function from GUI</a> is a",
        "<a href=\"CppQFileDialog.htm\">QFileDialog</a> <a href=\"CppExample.htm\">example</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQFileDialogExample3.png\">View a screenshot of 'CppQFileDialogExample3' (png)</a></li>",
        "  <li><a href=\"CppQFileDialogExample3.zip\">Download the Qt Creator project 'CppQFileDialogExample3' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQFileDialogExample4",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQFileDialogExample4.htm\">QFileDialog example 4: crafting a QFileDialog to save a file</a> is a",
        "<a href=\"CppQFileDialog.htm\">QFileDialog</a> <a href=\"CppExample.htm\">example</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQFileDialogExample4.png\">View a screenshot of 'CppQFileDialogExample4' (png)</a></li>",
        "  <li><a href=\"CppQFileDialogExample4.zip\">Download the Qt Creator project 'CppQFileDialogExample4' (zip)</a></li>",
        "</ul>"
      }

    }
  );
  m.push_back(
    { "CppQmakeErrorUnknownModulesInQtLocationSensors",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQmakeErrorUnknownModulesInQtLocationSensors.htm\">Unknown module(s) in QT: location sensors</a> is a",
        "<a href=\"CppQmakeError.htm\">qmake error</a>.</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"Qmake output\" border = \"1\"><tr><td><code>",
        "# :-1: error: Unknown module(s) in QT: location sensors<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQmakeErrorUnknownModulesInQtLocationSensors.htm\">Download the Qt Creator project 'CppQmakeErrorUnknownModulesInQtLocationSensors' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQPrintDialogExample1",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQPrintDialogExample1.htm\">QPrintDialog example 1</a> is a",
        "<a href=\"CppQPrintDialog.htm\">QPrintDialog</a> <a href=\"CppExample.htm\">example</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQPrintDialogExample1.png\">View a screenshot of 'CppQPrintDialogExample1' (png)</a></li>",
        "  <li><a href=\"CppQPrintDialogExample1.zip\">Download the Qt Creator project 'CppQPrintDialogExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQrcFile",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppQrcFile.htm\">QrcFile</a> is a",
        "  <a href=\"CppClass.htm\">class</a> for a <a href=\"CppQt.htm\">Qt</a>",
        "  resources file.",
        "</p>"
      }
    }
  );
  m.push_back(
    { "CppQSqlTableModelExample1",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQSqlTableModelExample1.htm\">QSqlTableModel example 1</a> is a",
        "<a href=\"CppQSqlTableModel.htm\">QSqlTableModel</a> <a href=\"CppExample.htm\">example</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQSqlTableModelExample1.png\">View a screenshot of 'CppQSqlTableModelExample1' (png)</a></li>",
        "  <li><a href=\"CppQSqlTableModelExample1.zip\">Download the Qt Creator project 'CppQSqlTableModelExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQSqlTableModelExample2",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQSqlTableModelExample2.htm\">QSqlTableModel example 2</a> is a",
        "<a href=\"CppQSqlTableModel.htm\">QSqlTableModel</a> <a href=\"CppExample.htm\">example</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQSqlTableModelExample2.png\">View a screenshot of 'CppQSqlTableModelExample2' (png)</a></li>",
        "  <li><a href=\"CppQSqlTableModelExample2.zip\">Download the Qt Creator project 'CppQSqlTableModelExample2' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQSqlTableModelExample3",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQSqlTableModelExample3.htm\">QSqlTableModel example 3</a> is a",
        "<a href=\"CppQSqlTableModel.htm\">QSqlTableModel</a> <a href=\"CppExample.htm\">example</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQSqlTableModelExample3.png\">View a screenshot of 'CppQSqlTableModelExample3' (png)</a></li>",
        "  <li><a href=\"CppQSqlTableModelExample3.zip\">Download the Qt Creator project 'CppQSqlTableModelExample3' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQTableViewExample1",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQTableViewExample1.htm\">QTableView example 1: table with three columns, one with an X</a> is a",
        "<a href=\"CppQTableView.htm\">QTableView</a> <a href=\"CppExample.htm\">example</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQTableViewExample1.png\">View a screenshot of 'QTableViewExample1' (png)</a></li>",
        "  <li><a href=\"CppQTableViewExample1.zip\">Download the Qt Creator project 'QTableViewExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQTableViewExample2",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQTableViewExample2.htm\">QTableView example 2: table with ten columns of checkboxes</a> is a",
        "<a href=\"CppQTableView.htm\">QTableView</a> <a href=\"CppExample.htm\">example</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQTableViewExample2.png\">View a screenshot of 'QTableViewExample2' (png)</a></li>",
        "  <li><a href=\"CppQTableViewExample2.zip\">Download the Qt Creator project 'QTableViewExample2' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQTableViewExample3",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQTableViewExample3.htm\">QTableView example 3: table with checkboxes and editable text</a> is a",
        "<a href=\"CppQTableView.htm\">QTableView</a> <a href=\"CppExample.htm\">example</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQTableViewExample3.png\">View a screenshot of 'QTableViewExample3' (png)</a></li>",
        "  <li><a href=\"CppQTableViewExample3.zip\">Download the Qt Creator project 'QTableViewExample3' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQTableViewExample4",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQTableViewExample4.htm\">QTableView example 4: custom data</a> is a",
        "<a href=\"CppQTableView.htm\">QTableView</a> <a href=\"CppExample.htm\">example</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQTableViewExample4.png\">View a screenshot of 'QTableViewExample4' (png)</a></li>",
        "  <li><a href=\"CppQTableViewExample4.zip\">Download the Qt Creator project 'QTableViewExample4' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQTableViewExample5",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQTableViewExample5.htm\">QTableView example 5: simple custom data</a> is a",
        "<a href=\"CppQTableView.htm\">QTableView</a> <a href=\"CppExample.htm\">example</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQTableViewExample5.png\">View a screenshot of 'QTableViewExample5' (png)</a></li>",
        "  <li><a href=\"CppQTableViewExample5.zip\">Download the Qt Creator project 'QTableViewExample5' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQTableViewExample6",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQTableViewExample6.htm\">QTableView example 6: two views on one model</a> is a",
        "<a href=\"CppQTableView.htm\">QTableView</a> <a href=\"CppExample.htm\">example</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>This was to demonstrate that if two tables must remain identical, the model/view architecture is an easy way to do so: because",
        "the two views work on the same model, they cannot be different.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQTableViewExample6.png\">View a screenshot of 'QTableViewExample6' (png)</a></li>",
        "  <li><a href=\"CppQTableViewExample6.zip\">Download the Qt Creator project 'QTableViewExample6' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQTableViewExample7",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQTableViewExample7.htm\">QTableView example 7: two views on one model with a custom data type</a> is a",
        "<a href=\"CppQTableView.htm\">QTableView</a> <a href=\"CppExample.htm\">example</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQTableViewExample7.png\">View a screenshot of 'QTableViewExample7' (png)</a></li>",
        "  <li><a href=\"CppQTableViewExample7.zip\">Download the Qt Creator project 'QTableViewExample7' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQTableViewExample8",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQTableViewExample8.htm\">QTableView example 8: table with checkboxes and editable text using a custom model</a> is a",
        "<a href=\"CppQTableView.htm\">QTableView</a> <a href=\"CppExample.htm\">example</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQTableViewExample8.png\">View a screenshot of 'QTableViewExample8' (png)</a></li>",
        "  <li><a href=\"CppQTableViewExample8.zip\">Download the Qt Creator project 'QTableViewExample8' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQTableViewExample9",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQTableViewExample9.htm\">QTableView example 9: two tables with checkboxes and editable text using a custom model</a> is a",
        "<a href=\"CppQTableView.htm\">QTableView</a> <a href=\"CppExample.htm\">example</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQTableViewExample9.png\">View a screenshot of 'QTableViewExample9' (png)</a></li>",
        "  <li><a href=\"CppQTableViewExample9.zip\">Download the Qt Creator project 'QTableViewExample9' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQTableViewExample10",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQTableViewExample10.htm\">QTableView example 10: two tables with checkboxes and editable text using a custom model and a custom data type</a> is a",
        "<a href=\"CppQTableView.htm\">QTableView</a> <a href=\"CppExample.htm\">example</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQTableViewExample10.png\">View a screenshot of 'QTableViewExample10' (png)</a></li>",
        "  <li><a href=\"CppQTableViewExample10.zip\">Download the Qt Creator project 'QTableViewExample10' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQTableWidgetExample1",
      {
         "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQTableWidgetExample1.htm\">QTableWidget example 1: display text</a> is a",
        "<a href=\"CppQTableWidget.htm\">QTableWidget</a> <a href=\"CppExample.htm\">example</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQTableWidgetExample1.png\">View a screenshot of 'QTableWidgetExample1' (png)</a></li>",
        "  <li><a href=\"CppQTableWidgetExample1.zip\">Download the Qt Creator project 'QTableWidgetExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQTableWidgetExample2",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQTableWidgetExample2.htm\">QTableWidget example 2: checkboxes and text</a> is a",
        "<a href=\"CppQTableWidget.htm\">QTableWidget</a> <a href=\"CppExample.htm\">example</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQTableWidgetExample1.png\">View a screenshot of 'QTableWidgetExample1' (png)</a></li>",
        "  <li><a href=\"CppQTableWidgetExample1.zip\">Download the Qt Creator project 'QTableWidgetExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQTableWidgetExample3",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQTableWidgetExample3.htm\">QTableWidget example 3: checkboxes and text modifying external data</a> is a",
        "<a href=\"CppQTableView.htm\">QTableView</a> <a href=\"CppExample.htm\">example</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQTableWidgetExample3.png\">View a screenshot of 'QTableWidgetExample3' (png)</a></li>",
        "  <li><a href=\"CppQTableWidgetExample3.zip\">Download the Qt Creator project 'QTableWidgetExample3' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtAboutDialog",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtAboutDialog.htm\">QtAboutDialog</a> is a <a href=\"CppQt.htm\">Qt</a> dialog",
        "<a href=\"CppClass.htm\">class</a> to display an <a href=\"CppAbout.htm\">About</a>.</p>"
      }
    }
  );
  m.push_back(
    { "QtArrowItem",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtArrowItem.htm\">QtArrowItem</a> is a <a href=\"CppQt.htm\">Qt</a> ",
        "<a href=\"CppQGraphicsItem.htm\">QGraphicsItem</a> <a href=\"CppClass.htm\">class</a> that displays a straight arrow.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtChess",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppQtChess.htm\">QtChess</a> has many <a href=\"CppQt.htm\">Qt</a>",
        "  <a href=\"CppChess.htm\">chess</a> <a href=\"CppClass.htm\">classes</a>",
        "</p>"
      }
    }
  );
  m.push_back(
    { "CppQtConnectThreeWidget",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtConnectThreeWidget.htm\">QtConnectThreeWidget</a> is a <a href=\"CppQt.htm\">Qt</a> <a href=\"CppWidget.htm\">widget</a>",
        "<a href=\"CppClass.htm\">class</a> for a responsive connect-three game. <a href=\"CppQtConnectThreeWidget.htm\">QtConnectThreeWidget</a> is",
        "used in, among others, the <a href=\"Games.htm\">game</a> <a href=\"GameConnectThree.htm\">ConnectThree</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtCreator_5_1",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtCreator_5_1.htm\">Qt Creator 5.1 example 1</a> is a",
        "<a href=\"CppQtSql.htm\">Qt Creator 5.1</a> <a href=\"CppExample.htm\">example</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtCreator_5_1.png\">View a screenshot of 'CppQtCreator_5_1' (png)</a></li>",
        "  <li><a href=\"CppQtCreator_5_1.zip\">Download the Qt Creator project 'CppQtCreator_5_1' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtCreatorProFile",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppQtCreatorProFile.htm\">QtCreatorProFile</a>",
        "  is a <a href=\"CppQtProjectFile.htm\">Qt project file (.pro)</a>",
        "  <a href=\"CppClass.htm\">class</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppQtCreatorProFile.htm\">QtCreatorProFile</a> is tested by the",
        "  <a href=\"Tools.htm\">tool</a> ",
        "  <a href=\"ToolTestQtCreatorProFile.htm\">TestQtCreatorProFile</a>.",
        "</p>"
      }
    }
  );
  m.push_back(
    { "CppQtDialWidget",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppQtDialWidget.htm\">QtDialWidget</a> is a",
        "  <a href=\"CppQt.htm\">Qt</a>",
        "  <a href=\"CppClass.htm\">class</a> to display an",
        "  <a href=\"CppDial.htm\">Dial</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppQtDialWidget.htm\">QtDialWidget</a> is used in the",
        "  <a href=\"Tools.htm\">tool</a>",
        "  <a href=\"ToolTestDial.htm\">TestDial</a>.",
        "</p>"
      }
    }
  );
  m.push_back(
    { "CppQtDisplayPosItem",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppQtDisplayPosItem.htm\">QtDisplayPosItem</a> is a",
        "  <a href=\"CppQt.htm\">Qt</a>",
        "  <a href=\"CppQGraphicsItem.htm\">QGraphicsItem</a>",
        "  <a href=\"CppClass.htm\">class</a> that displays its position.",
        "</p>"
      }
    }
  );
  m.push_back(
    { "CppQtExample1",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtExample1.htm\">Qt example 1: moving a sprite over a background in 2D</a> is a <a href=\"CppQtExample.htm\">Qt example</a> that shows an image moving over a background image, like <a href=\"CppQtExample1.png\">this screenshot (png)</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtExample1.zip\">Download the Qt Creator project file 'CppQtExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtExample2",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtExample2.htm\">Qt example 2: moving many sprites over a background in 2D</a> is a <a href=\"CppQtExample.htm\">Qt example</a>  shows an 250 images moving over a background image, like <a href=\"CppQtExample2.png\">this screenshot (png)</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtExample2.zip\">Download the Qt Creator project file 'CppQtExample2' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtExample3",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppQtExample3.htm\">Qt example 3: a changing background in 2D</a>",
        "  is a <a href=\"CppQtExample.htm\">Qt example</a> that shows a changing background in 2D,",
        "  like <a href=\"CppQtExample3.png\">this screenshot (png)</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtExample3.zip\">Download the Qt Creator project file 'CppQtExample3' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtExample4",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppQtExample4.htm\">Qt example 4: moving many sprites over a changing background in 2D</a>",
        "  is a <a href=\"CppQtExample.htm\">Qt example</a> that shows how to move many sprites over a changing",
        "  background in 2D, like <a href=\"CppQtExample4.png\">this screenshot (png)</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtExample4.zip\">Download the Qt Creator project file 'CppQtExample4' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtExample5",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppQtExample5.htm\">Qt example 5: moving many changing sprites over a",
        "  changing background in 2D</a> is a",
        "  <a href=\"CppQtExample.htm\">Qt example</a> that shows how to move many changing sprites",
        " over a changing background in 2D, like <a href=\"CppQtExample5.png\">this screenshot (png)</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtExample5.zip\">Download the Qt Creator project file 'CppQtExample5' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtExample6",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppQtExample6.htm\">Qt example 6: moving customly-drawn and partially transparent sprites over a changing background in 2D</a>",
        "  is a <a href=\"CppQtExample.htm\">Qt example</a> that shows how to move customly-drawn",
        "  and partially transparent sprites over a changing background in 2D, like <a href=\"CppQtExample6.png\">this screenshot (png)</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtExample6.zip\">Download the Qt Creator project file 'CppQtExample6' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtExample7",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>This <a href=\"CppQt.htm\">Qt</a> example shows how to let customly-drawn and partially transparent sprites move and collide over a changing background in 2D, like <a href=\"CppQtExample7.png\">this screenshot (png)</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtExample7.zip\">Download the Qt Creator project file 'CppQtExample7' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtExample8",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>This <a href=\"CppQt.htm\">Qt</a> example shows how implement a simple 2D SIR simulation, like <a href=\"CppQtExample8.png\">this screenshot (png)</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtExample8.zip\">Download the Qt Creator project file 'CppQtExample8' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtExample9",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>This <a href=\"CppQt.htm\">Qt</a> example shows how to let custom sprites move over custom background, like <a href=\"CppQtExample9.png\">this screenshot (png)</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>There are multiple ways to do the same, for example, as shown in <a href=\"CppQtExample9_2.htm\">Qt example 9.2</a>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtExample9.zip\">Download the Qt Creator project file 'QtExample9' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtExample10",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>This <a href=\"CppQt.htm\">Qt</a> example shows how to change a QLabel when a QDialog is resized, like <a href=\"CppQtExample10.png\">this screenshot (png)</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtExample10.zip\">Download the Qt Project of 'QtExample10' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtExample11",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>This <a href=\"CppQt.htm\">Qt</a> example shows how to create a <a href=\"CppQDialog.htm\">QDialog</a> with <a href=\"CppQVBoxLayout.htm\">QVBoxLayout</a> on the fly, like <a href=\"CppQtExample11.png\">this screenshot (png)</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtExample11.zip\">Download the Qt Project of 'QtExample11' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtExample12",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>This <a href=\"CppQt.htm\">Qt</a> example shows how to create a custom QDialog with a custom slot, like <a href=\"CppQtExample12.png\">this screenshot (png)</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtExample12.zip\">Download the Qt Project of 'QtExample12' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtExample13",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>This <a href=\"CppQt.htm\">Qt</a> example shows how to create a more complete custom QDialog with a custom slot, like <a href=\"CppQtExample13.png\">this screenshot (png)</a>. This example elaborates on <a href=\"CppQtExample12.htm\">Qt example 12: creating a custom QDialog with slot</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtExample13.zip\">Download the Qt Project of 'QtExample13' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtExample14",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>This <a href=\"CppQt.htm\">Qt</a> example shows how to create a more complete custom QDialog with a custom slot with shorter compilation time, like <a href=\"CppQtExample14.png\">this screenshot (png)</a>. This example elaborates on <a href=\"CppQtExample13.htm\">Qt example 13: creating a more complete custom QDialog with slot</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtExample14.zip\">Download the Qt Project of 'QtExample14' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtExample15",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>This <a href=\"CppQt.htm\">Qt</a> example shows how to create pop-up windows from pop-up windows, like <a href=\"CppQtExample15.png\">this screenshot (png)</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtExample15.zip\">Download the Qt Project of 'QtExample15' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtExample16",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>This <a href=\"CppQt.htm\">Qt</a> example shows how to using resources, like <a href=\"CppQtExample16.png\">this screenshot (png)</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtExample16.zip\">Download the Qt Project of 'QtExample16' (zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Using resources in <a href=\"CppQt.htm\">Qt Creator</a> 2.0.0</h2>",
        "<p>&nbsp;</p>",
        "<p>Here follows a step-by-step guide to add a bitmap as a resource to a <a href=\"CppQt.htm\">Qt Creator</a> project:</p>",
        "<p>&nbsp;</p>",
        "<ol>",
        "  <li><a href=\"CppQtExample16_1.png\">View screenshot</a></li>",
        "  <li>In the Project Manager, right-click on the project name on on the 'Sources' folder. Click 'Add New'</li>",
        "  <li><a href=\"CppQtExample16_2.png\">View screenshot</a></li>",
        "  <li>In the 'New File' dialog, select to create a new 'Qt Resource file'</li>",
        "  <li><a href=\"CppQtExample16_3.png\">View screenshot</a></li>",
        "  <li>In the 'New Qt Resource file -> Location' dialog, give the resource file a name. For example, 'MyResources'</li>",
        "  <li><a href=\"CppQtExample16_4.png\">View screenshot</a></li>",
        "  <li>In the 'New Qt Resource file -> Project management' dialog, click 'Finish'</li>",
        "  <li><a href=\"CppQtExample16_5.png\">View screenshot</a></li>",
        "  <li>As you can see, 'MyResources.qrc' has now been added to the Project Manager. Double-click on 'MyResources.qrt' and click 'Add -> Add Prefix' (which is all there is to choose yet)</li>",
        "  <li><a href=\"CppQtExample16_6.png\">View screenshot</a></li>",
        "  <li>Change the prefix to a more fitting name, for example 'MyImages'.",
        "  <li><a href=\"CppQtExample16_7.png\">View screenshot</a></li>",
        "  <li>Click 'Add -> Add Files' and add an image. In this example, this is a file called 'BeerSmall.bmp' (a sprite from <a href=\"GameBeerWanter.htm\">BeerWanter</a>)</li>",
        "  <li><a href=\"CppQtExample16_8.png\">View screenshot</a></li>",
        "  <li>Now, the file has been added to your resources. The image can be accessed with the filename ':/MyImages/BeerSmall.bmp'</li>",
        "  <li><a href=\"CppQtExample16_9.png\">View screenshot</a></li>",
        "  <li>Copy-paste the example code below</li>",
        "  <li><a href=\"CppQtExample16.png\">View final screenshot</a></li>",
        "</ol>"
      }
    }
  );
  m.push_back(
    { "CppQtExample17",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>This <a href=\"CppQt.htm\">Qt</a> example shows how to modify a QLabel to make it clickable, resulting in a traffic light, like <a href=\"CppQtExample17.png\">this screenshot (png)</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtExample17.zip\">Download the Qt Project of 'QtExample17' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtExample18",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>This <a href=\"CppQtExample.htm\">Qt example</a> shows how to stretchdraw and rotate an image, like <a href=\"CppQtExample18.png\">this screenshot (png)</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtExample18.zip\">Download the Qt Project of 'QtExample18' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtExample19",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>This <a href=\"CppQt.htm\">Qt</a> example shows how to create a GUI around a program that displays a rotating image, like <a href=\"CppQtExample19.png\">this screenshot (png)</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtExample19.zip\">Download the Qt Project of 'QtExample19' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtExample20",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>This <a href=\"CppQtExample.htm\">Qt example</a> shows how to develop a sketch widget.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtExample20.zip\">Download the 'CppQtExample20' source code (zip)</a></li>",
        "  <li><a href=\"CppQtExample20.png\">View a screenshot of 'CppQtExample20' (desktop)(png)</a></li>",
        "  <li><a href=\"CppQtExample20Simulator.png\">View a screenshot of 'CppQtExample20' (mobile simulator)(png)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtExample21",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>This <a href=\"CppQtExample.htm\">Qt example</a> shows a way to develop a transparent-like dialog.",
        "The trick used is to take a screenshot of the desktop before the dialog is shown. The illusion",
        "fades if the dialog is moved.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtExample21.zip\">Download the 'CppQtExample21' source code (zip)</a></li>",
        "  <li><a href=\"CppQtExample21.png\">View a screenshot of 'CppQtExample21' (png)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtExample22",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>This <a href=\"CppQtExample.htm\">Qt example</a> shows a way to develop a transparent dialog.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtExample22.zip\">Download the 'CppQtExample22' source code (zip)</a></li>",
        "  <li><a href=\"CppQtExample22.png\">View a screenshot of 'CppQtExample22' (png)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtExample23",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>This <a href=\"CppQtExample.htm\">Qt example</a> shows a way to grab a widget as an image.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtExample23.zip\">Download the 'CppQtExample23' source code (zip)</a></li>",
        "  <li><a href=\"CppQtExample23.png\">View a screenshot of 'CppQtExample23' (png)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtExample24",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtExample24.htm\">Qt example 24: create a simple text positioning widget</a> is a <a href=\"CppQtExample.htm\">Qt Example</a>",
        "that uses <a href=\"CppQGraphicsView.htm\">QGraphicsView</a> to create a simple text positioning <a href=\"CppWidget.htm\">widget</a>:",
        "in the <a href=\"CppConstructor.htm\">constructor</a> the different <a href=\"CppString.htm\">std::strings</a> are specified, upon which",
        "the <a href=\"CppWidget.htm\">widget</a> puts these overlapping in the center. Then, the <a href=\"CppString.htm\">std::strings</a> can",
        "dragged.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtExample24.zip\">Download the source code for Qt example 24 (zip)</a></li>",
        "  <li><a href=\"CppQtExample24.png\">View a screenshot of Qt example 24 (png)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtExample25",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtExample25.htm\">Qt example 25: a transparent widget</a> shows a transparent sketch widget.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtExample26",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtExample26.htm\">Qt example 26: create a text positioning widget</a> is an elaboration of",
        "<a href=\"CppQtExample24.htm\">Qt example 24: create a simple text positioning widget</a>. This <a href=\"CppQtExample.htm\">Qt Example</a>",
        "that uses <a href=\"CppQGraphicsView.htm\">QGraphicsView</a> to create a simple text positioning <a href=\"CppWidget.htm\">widget</a>:",
        "in the <a href=\"CppConstructor.htm\">constructor</a> the different <a href=\"CppString.htm\">std::strings</a> are specified, upon which",
        "the <a href=\"CppWidget.htm\">widget</a> puts these overlapping in the center. Then, the <a href=\"CppString.htm\">std::strings</a> can",
        "dragged.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtExample26.zip\">Download the source code for Qt example 26 (zip)</a></li>",
        "  <li><a href=\"CppQtExample26.png\">View a screenshot of Qt example 26 (png)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtExample27",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtExample27.htm\">Qt example 27: create a simple gravity widget</a> is a <a href=\"CppQtExample.htm\">Qt Example</a>",
        "that uses <a href=\"CppQGraphicsView.htm\">QGraphicsView</a> to create a simple <a href=\"CppWidget.htm\">widget</a>",
        "in which the item (a ball) is responding as if there is gravity, bouncing perfectly elasticly.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtExample27.zip\">Download the source code for Qt example 27 (zip)</a></li>",
        "  <li><a href=\"CppQtExample27.png\">View a screenshot of Qt example 27 (png)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtExample28",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtExample28.htm\">Qt example 28: bouncing rectangles widget</a> is a <a href=\"CppQtExample.htm\">Qt Example</a>",
        "that uses <a href=\"CppQGraphicsView.htm\">QGraphicsView</a> to create a simple <a href=\"CppWidget.htm\">widget</a>",
        "in which the items (rectangles) respond to collision with others.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtExample28.zip\">Download the source code for Qt example 28 (zip)</a></li>",
        "  <li><a href=\"CppQtExample28.png\">View a screenshot of Qt example 28 (png)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtExample29",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtExample29.htm\">Qt example 29: bouncing balls widget</a> is a <a href=\"CppQtExample.htm\">Qt Example</a>",
        "that uses <a href=\"CppQGraphicsView.htm\">QGraphicsView</a> to create a simple <a href=\"CppWidget.htm\">widget</a>",
        "in which the items (ellipses) respond to collision with others.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtExample29.zip\">Download the source code for Qt example 29 (zip)</a></li>",
        "  <li><a href=\"CppQtExample29.png\">View a screenshot of Qt example 29 (png)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtExample30",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtExample30.htm\">Qt example 30: controlling program flow with a Singleton</a> is a <a href=\"CppQtExample.htm\">Qt Example</a>",
        "that uses <a href=\"CppSingleton.htm\">Singleton</a> to produce dialogs until it is told to quit.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtExample31",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtExample31.htm\">Qt example 31: moveable thin lines</a> is a <a href=\"CppQtExample.htm\">Qt example</a> to create some lines that are moveable. Note",
        "that because the lines are one pixel thin, it is difficult to really move them!",
        "<a href=\"CppQtExample32.htm\">QtExample32</a> solves this problem.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtExample32",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtExample32.htm\">Qt example 32: moveable and selectable thin lines</a> is a",
        "<a href=\"CppQtExample.htm\">Qt example</a> to create some lines that are moveable, yet",
        "selectable easy.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtExample33",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtExample33.htm\">Qt example 33: moveable and selectable arrows</a> is a",
        "<a href=\"CppQtExample.htm\">Qt example</a> to create some arrows that are (easily) selectable and moveable.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtExample34",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtExample34.htm\">Qt example 34: moveable, selectable and editable arrows</a> is a ",
        "<a href=\"CppQtExample.htm\">Qt example</a> to create some arrows that are (easily) selectable, moveable and editable.",
        "Arrows can be edited by mouse press and a keyboard press: whil holding shift, click the end of an arrow to have an arrowhead",
        "added or removed. When having selected an arrow, press 1,F1,the minus sign of 't' to have the tail arrowhead added or removed.",
        "Or, when having selected an arrow, press 2,F2,the plus sign of 'h' to have the head arrowhead added or removed.</p>",
        "<p>&nbsp;</p>",
        "<p>What I liked, is that it is possible to select multiple items while holding CTRL (which is standard",
        "GUI behavior) and edit these all at the same time using a key press!</p>"
      }
    }
  );
  m.push_back(
    { "CppQtExample35",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtExample35.htm\">Qt example 35: arrows with an angle</a> is a ",
        "<a href=\"CppQtExample.htm\">Qt example</a> elaborates on <a href=\"CppQtExample34.htm\">Qt example 34: moveable, selectable and editable arrows</a>,",
        "but has arrows with an angle in them instead.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtExample36",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtExample36.htm\">Qt example 36: arrows with multiple midpoints</a> is a ",
        "<a href=\"CppQtExample.htm\">Qt example</a> elaborates on <a href=\"CppQtExample34.htm\">Qt example 34: moveable, selectable and editable arrows</a>,",
        "but has arrows with an angle in them instead.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtExercise",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtExercise.htm\">QtExercise</a> is a <a href=\"CppQt.htm\">Qt</a>",
        "<a href=\"CppClass.htm\">class</a> to display an <a href=\"CppExercise.htm\">Exercise</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtGaborFilterWidget",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtGaborFilterWidget.htm\">QtGaborFilterWidget</a> is a",
        "<a href=\"CppQt.htm\">Qt</a> <a href=\"CppClass.htm\">class</a> to",
        "display a <a href=\"CppGaborFilterWidget.htm\">GaborFilterWidget</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtHideAndShowDialog",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtHideAndShowDialog.htm\">QtHideAndShowDialog</a> is a <a href=\"CppQt.htm\">Qt</a>",
        "<a href=\"CppClass.htm\">class</a> to allow a dialog display a new modal dialog, with the parent hiding.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtKeyboardFriendlyGraphicsView",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtKeyboardFriendlyGraphicsView.htm\">QtKeyboardFriendlyGraphicsView</a> is a <a href=\"CppQt.htm\">Qt</a>",
        "<a href=\"CppClass.htm\">class</a> for a keyboard friendly QGraphicsView.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtLabeledQuadBezierArrowItem",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtArrowItem.htm\">QtArrowItem</a> is a <a href=\"CppQt.htm\">Qt</a> ",
        "<a href=\"CppQGraphicsItem.htm\">QGraphicsItem</a> <a href=\"CppClass.htm\">class</a> that displays a curved arrow.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtLedDisplayWidget",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtLedWidget.htm\">QtLedWidget</a> is a <a href=\"CppQt.htm\">Qt</a> ",
        "<a href=\"CppClass.htm\">class</a> to display an <a href=\"CppLed.htm\">Led</a>.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtLedWidget.htm\">QtLedWidget</a> is used in the <a href=\"Tools.htm\">tool</a>",
        "<a href=\"ToolTestLed.htm\">TestLed</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtLedWidget",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtLedWidget.htm\">QtLedWidget</a> is a <a href=\"CppQt.htm\">Qt</a> ",
        "<a href=\"CppClass.htm\">class</a> to display an <a href=\"CppLed.htm\">Led</a>.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtLedWidget.htm\">QtLedWidget</a> is used in the <a href=\"Tools.htm\">tool</a>",
        "<a href=\"ToolTestLed.htm\">TestLed</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtLeftRightRectItem",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtLeftRightRectItem.htm\">QtLeftRightRectItem</a> is a <a href=\"CppQt.htm\">Qt</a> ",
        "<a href=\"CppQGraphicsItem.htm\">QGraphicsItem</a> <a href=\"CppClass.htm\">class</a> that has a left and right focus.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtMatrix",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtMatrix.htm\">QtMatrix</a> is a <a href=\"CppQt.htm\">Qt</a>",
        "<a href=\"CppClass.htm\">class</a> to display an <a href=\"CppMatrix.htm\">Matrix</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtModel",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtModel.htm\">QtModel</a> are some <a href=\"CppQt.htm\">Qt</a>",
        "model <a href=\"CppClass.htm\">classes</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtMultipleChoiceQuestionDialog",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtMultipleChoiceQuestionDialog.htm\">QtMultipleChoiceQuestionDialog</a> is a ",
        "<a href=\"CppQt.htm\">Qt</a> dialog for <a href=\"CppMultipleChoiceQuestion.htm\">MultipleChoiceQuestion</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtMysteryMachineWidget",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtMysteryMachineWidget.htm\">QtMysteryMachineWidget</a> is a <a href=\"CppQt.htm\">Qt</a> ",
        "<a href=\"CppClass.htm\">class</a> to display an <a href=\"CppMysteryMachineWidget.htm\">CppMysteryMachineWidget</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtOpenQuestionDialog",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtOpenQuestionDialog.htm\">QtOpenQuestionDialog</a> is a <a href=\"CppQt.htm\">Qt</a> dialog ",
        "for <a href=\"CppOpenQuestionDialog.htm\">OpenQuestionDialog</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtPathArrowItem",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtPathArrowItem.htm\">QtPathArrowItem</a> is a <a href=\"CppQt.htm\">Qt</a> ",
        "<a href=\"CppQGraphicsItem.htm\">QGraphicsItem</a> <a href=\"CppClass.htm\">class</a> that displays an arrow that can have a multiple straight-line body.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtPylos",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtPylos.htm\">CppQtPylos</a> is a <a href=\"CppQt.htm\">Qt</a>",
        "<a href=\"CppClass.htm\">class</a> for displaying a Pylos game.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtQuadBezierArrowItem",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtQuadBezierArrowItem.htm\">QtQuadBezierArrowItem</a> is a <a href=\"CppQGraphicsItem.htm\">QGraphicsItem</a> for displaying a arrow that has a quadratic Bezier curve as its body.</p>",
        "<p>&nbsp;</p>",
        "<p>For the math, see <a href=\"CppQGraphicsPathItemExample5.htm\">QGraphicsPathItem example 5: Bezier quadratic lines with arrow heads</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtQuestionDialog",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtQuestionDialog.htm\">QtQuestionDialog</a> is a <a href=\"CppQt.htm\">Qt</a> dialog for",
        "<a href=\"CppQuestionDialog.htm\">QuestionDialog</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtRichelBilderbeekGalleryDialog",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtRichelBilderbeekGalleryDialog.htm\">QtRichelBilderbeekGalleryDialog</a> is a <a href=\"CppQt.htm\">Qt</a> dialog for",
        "displaying the status of all ProjectRichelBilderbeek programs.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtRichelBilderbeekProgram",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtRichelBilderbeekProgram.htm\">QtRichelBilderbeekProgram</a> is a <a href=\"CppQt.htm\">Qt</a>",
        "<a href=\"CppClass.htm\">class</a> for a ProjectRichelBilderbeek class.</p>"
      }
    }
  );
  m.push_back(
    { "CppQTreeViewExample1",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQTreeViewExample1.htm\">QTreeView example 1: add a row</a> is an example to use",
        "a <a href=\"CppQTreeView.htm\">QTreeView</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQTreeViewExample1.png\">View a screenshot of 'CppQTreeViewExample1' (png)</a></li>",
        "  <li><a href=\"CppQTreeViewExample1.zip\">Download the Qt Creator project 'CppQTreeViewExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQTreeViewExample2",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQTreeViewExample2.htm\">QTreeView example 2: add a row and undo/redo this</a> is an example to use",
        "a <a href=\"CppQTreeView.htm\">QTreeView</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQTreeViewExample2.png\">View a screenshot of 'CppQTreeViewExample2' (png)</a></li>",
        "  <li><a href=\"CppQTreeViewExample2.zip\">Download the Qt Creator project 'CppQTreeViewExample2' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQTreeViewExample3",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQTreeViewExample3.htm\">QTreeView example 3: improved undo/redo and added drag/drop</a> is an example to use",
        "a <a href=\"CppQTreeView.htm\">QTreeView</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQTreeViewExample3.png\">View a screenshot of 'CppQTreeViewExample3' (png)</a></li>",
        "  <li><a href=\"CppQTreeViewExample3.zip\">Download the Qt Creator project 'CppQTreeViewExample3' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQTreeViewExample4",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQTreeViewExample4.htm\">QTreeView example 4: directory view</a> is an example to use",
        "a <a href=\"CppQTreeView.htm\">QTreeView</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQTreeViewExample4.png\">View a screenshot of 'CppQTreeViewExample4' (png)</a></li>",
        "  <li><a href=\"CppQTreeViewExample4.zip\">Download the Qt Creator project 'CppQTreeViewExample4' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtRoundedEditRectItem",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtRoundedEditRectItem.htm\">QtRoundedEditRectItem</a> is a <a href=\"CppQt.htm\">Qt</a> ",
        "<a href=\"CppQGraphicsItem.htm\">QGraphicsItem</a> <a href=\"CppClass.htm\">class</a> that displays a rounded rectangle with editable text.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtRoundedRectItem",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtRoundedEditRectItem.htm\">QtRoundedEditRectItem</a> is a <a href=\"CppQt.htm\">Qt</a> ",
        "<a href=\"CppQGraphicsItem.htm\">QGraphicsItem</a> <a href=\"CppClass.htm\">class</a> that displays a rounded rectangle.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtRoundedTextRectItem",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtRoundedEditRectItem.htm\">QtRoundedEditRectItem</a> is a <a href=\"CppQt.htm\">Qt</a> ",
        "<a href=\"CppQGraphicsItem.htm\">QGraphicsItem</a> <a href=\"CppClass.htm\">class</a> that displays a rounded rectangle with text.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtRubiksClockWidget",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtRubiksClockWidget.htm\">QtRubiksClockWidget</a> is a <a href=\"CppQt.htm\">Qt</a>",
        "<a href=\"CppClass.htm\">class</a> for displaying a Rubik's Clock.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtScopedDisable",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtScopedDisable.htm\">QtScopedDisable</a> is a <a href=\"CppQt.htm\">Qt</a>",
        "<a href=\"CppClass.htm\">class</a> for disabling a Qt class within a certain scope.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtShapeWidget",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtShapeWidget.htm\">QtShapeWidget</a> is a <a href=\"CppQt.htm\">Qt</a> <a href=\"CppWidget.htm\">widget</a>",
        "<a href=\"CppClass.htm\">class</a> to display an <a href=\"CppShapeWidget.htm\">ShapeWidget</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtShinyButtonWidget",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtShinyButtonWidget.htm\">QtShinyButtonWidget</a> is a <a href=\"CppQt.htm\">Qt</a>",
        "<a href=\"CppClass.htm\">class</a> for displaying a shiny button.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtSprites",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtSprites.htm\">QtSprites</a> is a <a href=\"CppClass.htm\">class</a>",
        "containing sprites.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtSqlExample1",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtSqlExample1.htm\">Qt SQL example 1</a> is a",
        "<a href=\"CppQtSql.htm\">Qt SQL</a> <a href=\"CppExample.htm\">example</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQtSqlExample1.png\">View a screenshot of 'CppQtSqlExample1' (png)</a></li>",
        "  <li><a href=\"CppQtSqlExample1.zip\">Download the Qt Creator project 'CppQtSqlExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtStateObserver",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtStateObserver.htm\">QtStateObserver</a> is a <a href=\"CppQt.htm\">Qt</a>",
        "<a href=\"CppClass.htm\">class</a> for displaying a state observer.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtSurfacePlotWidget",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtSurfacePlotWidget.htm\">QtSurfacePlotWidget</a> is a <a href=\"CppQt.htm\">Qt</a>",
        "<a href=\"CppClass.htm\">class</a> for displaying a surface plot.</p>"
      }
    }
  );
  m.push_back(
    { "CppQtTicTacToeWidget",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtTicTacToeWidget.htm\">QtTicTacToeWidget</a> is a <a href=\"CppQt.htm\">Qt</a> ",
        "<a href=\"CppClass.htm\">class</a> to display the <a href=\"CppTicTacToe.htm\">TicTacToe</a> <a href=\"CppClass.htm\">class</a>.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtTicTacToeWidget.htm\">QtTicTacToeWidget</a> is used by:</p>",
        "<ul>",
        "  <li><a href=\"GameTicTacToe.htm\">(Game) TicTacToe</a></li>",
        "  <li><a href=\"ToolTestTicTacToe.htm\">(Tool) TestTicTacToe</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppQtToggleButtonWidget",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQtToggleButtonWidget.htm\">QtToggleButtonWidget</a> is a <a href=\"CppQt.htm\">Qt</a> <a href=\"CppWidget.htm\">widget</a>",
        "<a href=\"CppClass.htm\">class</a> to display an <a href=\"CppToggleButtonWidget.htm\">ToggleButtonWidget</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppQuestion",
      {
        "<p><a href=\"CppQuestion.htm\">Question</a> is a <a href=\"CppClass.htm\">class</a> for a question.</p>"
      }
    }
  );
  m.push_back(
    { "CppQuestionDialog",
      {
        "<p><a href=\"CppQuestionDialog.htm\">QuestionDialog</a> is a dialog for <a href=\"CppQuestion.htm\">Question</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppQWebViewExample1",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppQWebViewExample1.htm\">QWebView example 1</a> is a <a href=\"CppQWebView.htm\">QWebView</a> <a href=\"CppExample.htm\">example</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppQWebViewExample1.png\">View a screenshot of CppQWebViewExample1 (png)</a></li>",
        "  <li><a href=\"CppQWebViewExample1.zip\">Download the Qt Creator project 'CppQWebViewExample1' (zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>This example might cause following errors:</p>",
        "<ul>",
        "  <li><img src=\"PicGreen.png\" alt=\"OK\"/> <a href=\"CppQmakeErrorUnknownModulesInQtLocationSensors.htm\">Unknown module(s) in QT: location sensors</a></li>",
        "  <li><img src=\"PicGreen.png\" alt=\"OK\"/> <a href=\"CppLinkErrorCannotFindLgstapp.htm\">cannot find -lgstapp-0.10</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppRainbow",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppRainbow.htm\">Rainbow</a> is a <a href=\"CppGraphics.htm\">graphics</a> <a href=\"CppClass.htm\">class</a> to create a rainbow.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppRainbow.png\">View a picture of the gradient created by the Rainbow function (upper row)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppRandomCode",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppRandomCode.htm\">RandomCode</a> is a <a href=\"CppClass.htm\">class</a>",
        "to generate random <a href=\"Cpp.htm\">C++</a> code.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppRandomCode.htm\">RandomCode</a> is used by the <a href=\"Tools.htm\">tool</a>",
        "<a href=\"ToolRandomCode.htm\">RandomCode</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppRaspberryPi",
      {
        "<p><img src=\"PicRpi.png\" alt=\"RPi\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppRaspberryPi.htm\">RaspberryPi</a> is a collection of <a href=\"CppClass.htm\">class</a> for working with a Raspberry Pi.</p>"
      }
    }
  );
  m.push_back(
    { "CppRectangle",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppRectangle.htm\">Rectangle</a> is a <a href=\"CppClass.htm\">class</a> for a rectangle.</p>"
      }
    }
  );
  m.push_back(
    { "CppRefExample2",
      {
        "<p>",
        "  <a href=\"CppRefExample2.htm\">Boost.Ref example 2: putting references in a vector</a> is"
        "   a <a href=\"CppRef.htm\">Boost.Ref</a> example showing",
        "  how to put references in a std::vector and how the values stay in sync.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppRefExample2.zip\">Download the Qt Creator project 'CppRefExample2' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppRichelBilderbeekProgram",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppRichelBilderbeekProgram.htm\">RichelBilderbeekProgram</a> is a",
        "<a href=\"CppClass.htm\">class</a> for a ProjectRichelBilderbeek class.</p>"
      }
    }
  );
  m.push_back(
    { "CppRpiExample1",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicRaspbian.png\" alt=\"Raspbian\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppRpiExample1.htm\">Raspberry Pi example 1: toggle all GPIO pins on and off</a> is a",
        "<a href=\"CppRpi.htm\">Raspberry Pi</a> example to toggle all GPIO pins on and off.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppRpiExample1.zip\">Download the Qt Creator project 'CppRpiExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppRpiExample2",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicRaspbian.png\" alt=\"Raspbian\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppRpiExample2.htm\">Raspberry Pi example 2: turn GPIO pins on and off</a> is a <a href=\"CppRpi.htm\">Raspberry Pi</a>",
        "example to turn the GPIO pins on and off from command line.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppRpiExample2.zip\">Download the Qt Creator project 'CppRpiExample2' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppRubiksClock",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppRubiksClock.htm\">RubiksClock</a> is a <a href=\"CppClass.htm\">class</a> for a Rubik's Clock.</p>"
      }
    }
  );
  m.push_back(
    { "CppRubiksClockWidget",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppRubiksClockWidget.htm\">RubiksClockWidget</a> is a <a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">class</a> for a <a href=\"CppRubiksClock.htm\">RubiksClock</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppRuntimeErrorAssertionFailedXpressiveDetailDynamicParse_charset201",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppRuntimeErrorAssertionFailedXpressiveDetailDynamicParse_charset201.png\">View this error message (png)</a></li>",
        "  <li><a href=\"CppRuntimeErrorAssertionFailedXpressiveDetailDynamicParse_charset201.zip\">Download the Qt Creator projectr 'RuntimeErrorAssertionFailedXpressiveDetailDynamicParse_charset201' (zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"s2l0.13.txt\" border = \"1\"><tr><td><code>",
        "Assertion failed!<br/>",
        "<br/>",
        "Program: myfolder/myexe.exe<br/>",
        "File: myfolder/boost_1_54_0/boost/xpressive/detail/dynamic/parse_charset.hpp, Line 201<br/>",
        "<br/>",
        "Expression: begin != end<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->"
      }
    }
  );
  m.push_back(
    { "CppSeperateString",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppSeperateString.htm\">SeperateString</a> is a <a href=\"CppString.htm\">std::string</a> <a href=\"CppCodeSnippets.htm\">code snippet</a> that seperates a <a href=\"CppString.htm\">std::string</a> into a multiple <a href=\"CppString.htm\">std::strings</a> (in a <a href=\"CppVector.htm\">std::vector</a>&lt;<a href=\"CppString.htm\">std::string</a>&gt;) by a certain seperator.</p>",
        "<p>&nbsp;</p>",
        "<p>I have multiple versions of SeperateString:</p>",
        "<ol>",
        "  <li><img src=\"PicBoost.png\" alt=\"Boost\"/> SeperateString #1: Seperator is a <a href=\"CppChar.htm\">char</a>, uses Boost String Algorithms Library</li>",
        "  <li><img src=\"PicStl.png\" alt=\"STL\"/> SeperateString #2: Seperator is a <a href=\"CppChar.htm\">char</a>, uses <a href=\"CppAlgorithm.htm\">algorithms</a>, short version</li>",
        "  <li><img src=\"PicStl.png\" alt=\"STL\"/>SeperateString #3: Seperator is a <a href=\"CppChar.htm\">char</a>, uses <a href=\"CppAlgorithm.htm\">algorithms</a>, long version</li>",
        "  <li><img src=\"PicStl.png\" alt=\"STL\"/>SeperateString #4: Seperator is a <a href=\"CppChar.htm\">char</a>, does not use algorithms</li>",
        "  <li><img src=\"PicStl.png\" alt=\"STL\"/>SeperateString #5: Seperator is a <a href=\"CppString.htm\">std::string</a>, uses algorithms</li>",
        "  <li><img src=\"PicStl.png\" alt=\"STL\"/>SeperateString #6: Seperator is a <a href=\"CppString.htm\">std::string</a>, does not use algorithms</li>",
        "</ol>",
        "<p>&nbsp;</p>",
        "<p>Of each version of <a href=\"CppSeperateString.htm\">SeperateString</a>, I also wrote some test code on it.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppSeperateString.zip\">Download the Qt Creator project 'CppSeperateString' (zip)</a></li>",
        "</ul>"
      }
    }
  );


  m.push_back(
    { "CppSet_difference",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppSet_difference.htm\">std::set_difference</a> is an <a href=\"CppStl.htm\">STL</a>",
        "  <a href=\"CppAlgorithm.htm\">algorithm</a> to create the subset of two sets of which the elements",
        "  are all present in the first and absent in the second set",
        "  (stored in any type of <a href=\"CppContainer.htm\">container</a>).",
        "</p>"
      }
    }
  );

  m.push_back(
    { "CppSet_union",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppSet_union.htm\">std::set_union</a> is an <a href=\"CppStl.htm\">STL</a>",
        "  <a href=\"CppAlgorithm.htm\">algorithm</a> to create the union set"
        "  of two sorted <a href=\"CppContainer.htm\">containers</a>, neither of which must hold duplicate entries."
        "</p>"
      }
    }
  );


  m.push_back(
    { "CppShape",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppShape.htm\">Shape</a> is a <a href=\"CppClass.htm\">class</a> for a shape.</p>"
      }
    }
  );
  m.push_back(
    { "CppShapeWidget",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppShapeWidget.htm\">ShapeWidget</a> is a <a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">class</a> for a <a href=\"CppShape.htm\">Shape</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppShinyButton",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppShinyButton.htm\">ShinyButton</a> is a <a href=\"CppClass.htm\">class</a> for a shiny button.</p>"
      }
    }
  );
  m.push_back(
    { "CppShinyButtonWidget",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppShinyButtonWidget.htm\">ShinyButtonWidget</a> is a <a href=\"CppClass.htm\">class</a> for a shiny button widget.</p>"
      }
    }
  );
  m.push_back(
    { "CppSortedBinaryNewickVector",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppSortedBinaryNewickVector.htm\">SortedBinaryNewickVector</a> is a <a href=\"CppNewick.htm\">Newick</a> <a href=\"CppClass.htm\">class</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppStateObserver",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppStateObserver.htm\">StateObserver</a> is a <a href=\"CppClass.htm\">class</a> for state observer.</p>"
      }
    }
  );

  m.push_back(
    { "CppStdFunctionExample1",
      {
        "<p><img src=\"PicCpp11.png\" alt=\"C++11\"/><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppStdFunctionExample1.htm\">std::function example 1: global functions</a> is"
        "  a <a href=\"CppStdFunction.htm\">std::function</a> <a href=\"CppExample.htm\">example</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppStdFunctionExample1.zip\">Download the Qt Creator project 'CppStdFunctionExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppStdFunctionExample2",
      {
        "<p><img src=\"PicCpp11.png\" alt=\"C++11\"/><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppStdFunctionExample2.htm\">std::function example 2: member functions</a> is",
        "  a <a href=\"CppStdFunction.htm\">std::function</a> <a href=\"CppExample.htm\">example</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppStdFunctionExample2.zip\">Download the Qt Creator project 'CppStdFunctionExample2' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppStdTupleExample1",
      {
        "<p><img src=\"PicCpp11.png\" alt=\"C++11\"/><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppStdTupleExample1.htm\">std::tuple example 1</a> is a <a href=\"CppStdTupleExample1.htm\">std::tuple</a> <a href=\"CppExample.htm\">example</a>.",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppStdTupleExample1.zip\">Download the Qt Creator project 'CppStdTupleExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppStopwatch",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppStopwatch.htm\">Stopwatch</a> is a <a href=\"CppClass.htm\">class</a> to do time measurements.</p>",
        "<p>&nbsp;</p>",
        "<p>The <a href=\"Tools.htm\">tool</a><a href=\"ToolTestStopwatch.htm\">TestStopwatch</a> tests and manages ",
        "<a href=\"CppStopwatch.htm\">Stopwatch</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppSurvey",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppSurvey.htm\">Survey</a> is a <a href=\"CppClass.htm\">class</a> for a survey.</p>"
      }
    }
  );
  m.push_back(
    { "CppTemplateClassExample1",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppTemplateClassExample1.htm\">Template class example 1: class holding a templated member variable</a>",
        "is a <a href=\"CppTemplateClass.htm\">template class</a> <a href=\"CppExample.htm\">example</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppTemplateClassExample1.zip\">Download the Qt Creator project 'CppTemplateClassExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppTemplateClassExample2",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppTemplateClassExample2.htm\">Template class example 2: class that must be specialized; compile-time polymorphism</a>",
        "is a <a href=\"CppTemplateClass.htm\">template class</a> <a href=\"CppExample.htm\">example</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppTemplateClassExample2.zip\">Download the Qt Creator project 'CppTemplateClassExample2' (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "CppTextCanvas",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppTextCanvas.htm\">TextCanvas</a> is a <a href=\"CppCanvas.htm\">Canvas</a>",
        "  to put text on.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "CppTicTacToe",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppTicTacToe.htm\">TicTacToe</a> is a <a href=\"CppClass.htm\">class</a> embodying",
        "the game logic of Tic-Tac-Toe.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppTicTacToe.htm\">TicTacToe</a> is used by, among others:</p>",
        "<ul>",
        "  <li><a href=\"ProjectWtWebsite.htm\">ProjectWtWebsite</a></li>",
        "  <li><a href=\"ToolTestTicTacToe.htm\">TestTicTacToe</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppToggleButton",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppToggleButton.htm\">ToggleButton</a> is a <a href=\"CppClass.htm\">class</a> for a toggle button.</p>"
      }
    }
  );
  m.push_back(
    { "CppToggleButtonWidget",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppToggleButtonWidget.htm\">ToggleButtonWidget</a> is a <a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">class</a> for a <a href=\"CppToggleButton.htm\">ToggleButton</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppTrace",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppTrace.htm\">To trace</a> something (for example, the value of a <a href=\"CppVariable.htm\">variable</a>),",
        "denotes displaying it while <a href=\"CppDebug.htm\">debugging</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppTwoDigitNewick",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppTwoDigitNewick.htm\">TwoDigitNewick</a> is a <a href=\"CppNewick.htm\">Newick</a> <a href=\"CppClass.htm\">class</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppUblasMatrixExample1",
      {
        "<p><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppUblasMatrixExample1.htm\">boost::numeric::ublas::matrix example 1: matrix creation, read and write to elements</a> is a",
        "<a href=\"CppUblas.htm\">Boost.uBLAS</a> <a href=\"CppLibrary.htm\">library</a> <a href=\"CppExample.htm\">example</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppUblasMatrixExample1.zip\">Download the Qt Creator project 'CppUblasMatrixExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppUnique_ptrExample1",
      {
        "<p>",
        "  <img src=\"PicCpp11.png\" alt=\"Cpp11\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/>",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppUnique_ptrExample1.htm\">std::unique_ptr example 1: basics</a>",
        "  is a <a href=\"CppUnique_ptr.htm\">std::unique_ptr</a> <a href=\"CppExample.htm\">example</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppUnique_ptrExample1.zip\">Download the Qt Creator project 'CppUnique_ptrExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppUnique_ptrExample2",
      {
        "<p>",
        "  <img src=\"PicCpp11.png\" alt=\"Cpp11\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/>",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppUnique_ptrExample2.htm\">std::unique_ptr example 2: custom deleter</a>",
        "  is a <a href=\"CppUnique_ptr.htm\">std::unique_ptr</a> example that shows how to use a",
        "  custom deleter (in this case <a href=\"CppChecked_delete.htm\">boost::checked_delete</a>)",
        "  with <a href=\"CppAuto.htm\">auto</a> and <a href=\"CppStdFunction.htm\">std::function</a>",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppUnique_ptrExample2.zip\">Download the Qt Creator project 'CppUnique_ptrExample2' (zip)</a></li>",
        "</ul>"
      }
    }
  );







  m.push_back(
    { "CppVectorExample1",
      {
        "<p>",
        "  <img src=\"PicCpp98.png\" alt=\"Cpp98\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWindows.png\" alt=\"Windows\"/>",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppVectorExample1.htm\">std::vector example 1: basics</a>",
        "  is a <a href=\"CppVector.htm\">std::vector</a> example that demonstrates",
        "  writing to and reading from a <a href=\"CppVector.htm\">std::vector</a>",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppVectorExample1.zip\">Download the Qt Creator project 'CppVectorExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppVectorExample2",
      {
        "<p>",
        "  <img src=\"PicCpp98.png\" alt=\"Cpp98\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWindows.png\" alt=\"Windows\"/>",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppVectorExample2.htm\">std::vector example 2: erase-remove idiom</a>",
        "  is a <a href=\"CppVector.htm\">std::vector</a> example that demonstrates",
        "  the erase-remove idiom.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppVectorExample2.zip\">Download the Qt Creator project 'CppVectorExample2' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppVectorExample3",
      {
        "<p>",
        "  <img src=\"PicCpp11.png\" alt=\"Cpp11\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWindows.png\" alt=\"Windows\"/>",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppVectorExample3.htm\">std::vector example 3: C++11 emplace member function</a>",
        "  is a <a href=\"CppVector.htm\">std::vector</a> example that demonstrates",
        "  the <a href=\"Cpp11.htm\">C++11</a> emplace <a href=\"CppMemberFunction.htm\">member function</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppVectorExample3.zip\">Download the Qt Creator project 'CppVectorExample3' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppVectorExample4",
      {
        "<p>",
        "  <img src=\"PicCpp98.png\" alt=\"Cpp98\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWindows.png\" alt=\"Windows\"/>",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"CppVectorExample4.htm\">std::vector example 4: remove an element with preserving the order</a>",
        "  is a <a href=\"CppVector.htm\">std::vector</a> example that demonstrates",
        "  how to remove an element with preserving the order.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppVectorExample4.zip\">Download the Qt Creator project 'CppVectorExample4' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
   { "CppVirtualBastard",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppVirtualBastard.htm\">VirtualBastard</a> is a class to do GUI testing.</p>"
      }
    }
  );
  m.push_back(
    { "CppWidget",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>A <a href=\"CppWidget.htm\">widget</a>/control is a user interface element, like a button or checkbox.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWidget.htm\">Widget</a> is a GUI independent <a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">class</a>",
        "and servers as a <a href=\"CppBaseClass.htm\">base class</a> for others (incomplete list):</p>",
        "<ul>",
        "  <li><a href=\"CppQtDialWidget.htm\">QtDialWidget</a></li>",
        "  <li><a href=\"CppQtLedWidget.htm\">QtLedWidget</a></li>",
        "  <li><a href=\"CppQtShapeWidget.htm\">QtShapeWidget</a></li>",
        "  <li><a href=\"CppDialWidget.htm\">DialWidget</a></li>",
        "  <li><a href=\"CppLedWidget.htm\">LedWidget</a></li>",
        "  <li><a href=\"CppShapeWidget.htm\">ShapeWidget</a></li>",
        "  <li><a href=\"CppWtDialWidget.htm\">WtDialWidget</a></li>",
        "  <li><a href=\"CppWtLedWidget.htm\">WtLedWidget</a></li>",
        "  <li><a href=\"CppWtShapeWidget.htm\">WtShapeWidget</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>Similar <a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">classes</a> are ",
        "<a href=\"CppQWidget.htm\">QWidget</a> and <a href=\"CppWWidget.htm\">Wt::WWidget</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppWilcoxonsSignedRankTest",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWilcoxonsSignedRankTest.htm\">Wilcoxon's signed rank test</a> is a <a href=\"CppMath.htm\">math</a> <a href=\"CppCodeSnippets.htm\">code snippet</a> that performs an example from [1].</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"CppReferences.htm\">References</a></h2>",
        "<p>&nbsp;</p>",
        "<ol>",
        "  <li>David Heath. An introduction to experimental design and statistics for biology. 1995. ISBN: 1-85728-132-2 PB.</li>",
        "</ol>"
      }
    }
  );
  m.push_back(
    { "CppWtAboutDialog",
      {
        "<p><img src=\"PicWt.png\" alt=\"Wt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtAboutDialog.htm\">WtAboutDialog</a> is a <a href=\"CppClass.htm\">class</a> for",
        "a <a href=\"CppWt.htm\">Wt</a> dialog displaying the <a href=\"CppAbout.htm\">About</a> <a href=\"CppClass.htm\">class</a>.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtAboutDialog.htm\">WtAboutDialog</a> is used in nearly all my web applications.</p>"
      }
    }
  );
  m.push_back(
    { "CppWtAutoConfig",
      {
        "<p><img src=\"PicWt.png\" alt=\"Wt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtAutoConfig.htm\">WtAutoConfig</a> is a <a href=\"CppWt.htm\">Wt</a> <a href=\"CppClass.htm\">class</a>",
        "that allows to start a <a href=\"CppWt.htm\">Wt</a> application without the need of a user giving ",
        "command-line parameters. It is a fine starting point for a <a href=\"CppWt.htm\">Wt</a> application.</p>"
      }
    }
  );
  m.push_back(
    { "CppWtBroadcastServer",
      {
        "<p><img src=\"PicWt.png\" alt=\"Wt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtBroadcastServer.htm\">WtBroadcastServer</a> has been abandoned, because it served two tasks. It is split up into and replaced",
        "by <a href=\"CppWtServerPusher.htm\">WtServerPusher</a> and <a href=\"CppWtTimedServerPusher.htm\">WtTimedServerPusher</a>.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtBroadcastServerClient.htm\">WtBroadcastServerClient</a> has been abandoned, because it served two tasks. It is split up into and replaced",
        "by <a href=\"CppWtServerPusherClient.htm\">WtServerPusherClient</a> and <a href=\"CppWtTimedServerPusherClient.htm\">WtTimedServerPusherClient</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppWtChess",
      {
        "<p><img src=\"PicWt.png\" alt=\"Wt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtChess.htm\">CppWtChess</a> is a <a href=\"CppWt.htm\">Wt</a> ",
        "<a href=\"CppClass.htm\">class</a> to display a chess game.</p>"
      }
    }
  );
  m.push_back(
    { "CppWtConnectThreeWidget",
      {
        "<p><img src=\"PicWt.png\" alt=\"Wt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtConnectThreeWidget.htm\">WtConnectThreeWidget</a> is a <a href=\"CppWt.htm\">Wt</a> ",
        "<a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">class</a> to display an <a href=\"CppConnectThreeWidget.htm\">ConnectThreeWidget</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppWtDialWidget",
      {
        "<p><img src=\"PicWt.png\" alt=\"Wt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtDialWidget.htm\">WtDialWidget</a> is a <a href=\"CppWt.htm\">Wt</a> ",
        "<a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">class</a> to display an <a href=\"CppDialWidget.htm\">DialWidget</a>.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtDialWidget.htm\">WtDialWidget</a> is used in the <a href=\"Tools.htm\">tool</a> ",
        "<a href=\"ToolTestDial.htm\">TestDial</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppWtEntrance",
      {
        "<p><img src=\"PicWt.png\" alt=\"Wt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtEntrance.htm\">WtEntrance</a> is a <a href=\"CppWt.htm\">Wt</a> ",
        "<a href=\"CppClass.htm\">class</a> to manage user logins.</p>"
      }
    }
  );
  m.push_back(
    { "CppWtExercise",
      {
        "<p><img src=\"PicWt.png\" alt=\"Wt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtChess.htm\">CppWtChess</a> is a <a href=\"CppWt.htm\">Wt</a> ",
        "<a href=\"CppClass.htm\">class</a> to display an exercise.</p>"
      }
    }
  );
  m.push_back(
    { "CppWtGroupWidget",
      {
        "<p><img src=\"PicWt.png\" alt=\"Wt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtGroupWidget.htm\">WtGroupWidget</a> is a <a href=\"CppWt.htm\">Wt</a> ",
        "<a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">class</a> to display an <a href=\"CppGroupWidget.htm\">GroupWidget</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppWtLedDisplayWidget",
      {
        "<p><img src=\"PicWt.png\" alt=\"Wt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtLedDisplayWidget.htm\">WtLedDisplayWidget</a> is a <a href=\"CppWt.htm\">Wt</a> ",
        "<a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">class</a> to display an <a href=\"CppLedWidget.htm\">CppLedWidget</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppWtLedWidget",
      {
        "<p><img src=\"PicWt.png\" alt=\"Wt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtLedWidget.htm\">WtLedWidget</a> is a <a href=\"CppWt.htm\">Wt</a> ",
        "<a href=\"CppClass.htm\">class</a> to display an <a href=\"CppLed.htm\">Led</a>.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtLedWidget.htm\">WtLedWidget</a> is used in the <a href=\"Tools.htm\">tool</a> ",
        "<a href=\"ToolTestLed.htm\">TestLed</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppWtMultipleChoiceQuestionDialog",
      {
        "<p><img src=\"PicWt.png\" alt=\"Wt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtMultipleChoiceQuestionDialog.htm\">WtMultipleChoiceQuestionDialog</a> is a <a href=\"CppWt.htm\">Wt</a> dialog ",
        "for <a href=\"CppMultipleChoiceQuestion.htm\">MultipleChoiceQuestion</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppWtMysteryMachineWidget",
      {
        "<p><img src=\"PicWt.png\" alt=\"Wt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtMysteryMachineWidget.htm\">WtMysteryMachineWidget</a> is a <a href=\"CppWt.htm\">Wt</a> ",
        "<a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">class</a> to display an <a href=\"CppMysteryMachineWidget.htm\">MysteryMachineWidget</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppWtOpenQuestionDialog",
      {
        "<p><img src=\"PicWt.png\" alt=\"Wt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtOpenQuestionDialog.htm\">WtOpenQuestionDialog</a> is a <a href=\"CppWt.htm\">Wt</a> dialog ",
        "for <a href=\"CppOpenQuestionDialog.htm\">OpenQuestionDialog</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppWtQuestionDialog",
      {
        "<p><img src=\"PicWt.png\" alt=\"Wt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtQuestionDialog.htm\">WtQuestionDialog</a> is a <a href=\"CppWt.htm\">Wt</a> dialog ",
        "for <a href=\"CppQuestionDialog.htm\">QuestionDialog</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppWtRichelBilderbeekGallery",
      {
        "<p><img src=\"PicWt.png\" alt=\"Wt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtRichelBilderbeekGallery.htm\">WtRichelBilderbeekGallery</a> is a <a href=\"CppWt.htm\">Wt</a> ",
        "<a href=\"CppClass.htm\">class</a> to display a gallery with all ProjectRichelBilderbeek programs' statuses.</p>"
      }
    }
  );
  m.push_back(
    { "CppWtRubiksClockWidget",
      {
        "<p><img src=\"PicWt.png\" alt=\"Wt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtRubiksClockWidget.htm\">WtRubiksClockWidget</a> is a <a href=\"CppWt.htm\">Wt</a> ",
        "<a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">class</a> to display an <a href=\"CppRubiksClockWidget.htm\">RubiksClockWidget</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppWtSafeTimer",
      {
        "<p><img src=\"PicWt.png\" alt=\"Wt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtSafeTimer.htm\">WtSafeTimer</a> is a <a href=\"CppForwardDeclaration.htm\">forward-declaration</a>-safe ",
        "<a href=\"CppWTimer.htm\">Wt::WTimer</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppWtSelectFileDialog",
      {
        "<p><img src=\"PicWt.png\" alt=\"Wt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtSelectFileDialog.htm\">WtSelectFileDialog</a> is a <a href=\"CppWt.htm\">Wt</a> ",
        "<a href=\"CppClass.htm\">class</a> to let a user select a file from the server. To let a user select a file from his/her",
        "computer, the <a href=\"CppWFileUpload.htm\">Wt::WFileUpload</a> <a href=\"CppClass.htm\">class</a> might be convenient.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ToolTestSelectFileDialog.htm\">TestSelectFileDialog</a> is a <a href=\"Tools.htm\">tool</a> to test ",
        "the <a href=\"CppWtSelectFileDialog.htm\">WtSelectFileDialog</a> <a href=\"CppClass.htm\">class</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppWtServerPusher",
      {
        "<p><img src=\"PicWt.png\" alt=\"Wt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtShapeGroupWidget.htm\">WtShapeGroupWidget</a> is a <a href=\"CppWt.htm\">Wt</a> ",
        "<a href=\"CppClass.htm\">class</a> used for notifying all clients from different IP addresses.</p>"
      }
    }
  );
  m.push_back(
    { "CppWtShapeGroupWidget",
      {
        "<p><img src=\"PicWt.png\" alt=\"Wt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtShapeGroupWidget.htm\">WtShapeGroupWidget</a> is a <a href=\"CppWt.htm\">Wt</a> ",
        "<a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">class</a> to display an <a href=\"CppShapeGroupWidget.htm\">ShapeGroupWidget</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppWtShapeWidget",
      {
        "<p><img src=\"PicWt.png\" alt=\"Wt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtShapeWidget.htm\">WtShapeWidget</a> is a <a href=\"CppWt.htm\">Wt</a> ",
        "<a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">class</a> to display an <a href=\"CppShapeWidget.htm\">ShapeWidget</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppWtTicTacToeWidget",
      {
        "<p><img src=\"PicWt.png\" alt=\"Wt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtTicTacToeWidget.htm\">WtTicTacToeWidget</a> is a <a href=\"CppWt.htm\">Wt</a> ",
        "<a href=\"CppClass.htm\">class</a> to display the <a href=\"CppTicTacToe.htm\">TicTacToe</a> <a href=\"CppClass.htm\">class</a>.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtTicTacToeWidget.htm\">WtTicTacToeWidget</a> is used by:</p>",
        "<ul>",
        "  <li><a href=\"GameTicTacToe.htm\">(Game) TicTacToe</a></li>",
        "  <li><a href=\"ToolTestTicTacToe.htm\">(Tool) TestTicTacToe</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppWtTimedServerPusher",
      {
        "<p><img src=\"PicWt.png\" alt=\"Wt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtShapeGroupWidget.htm\">WtShapeGroupWidget</a> is a <a href=\"CppWt.htm\">Wt</a> ",
        "<a href=\"CppClass.htm\">class</a> used for notifying all clients from different IP addresses.</p>"
      }
    }
  );
  m.push_back(
    { "CppWtToggleButtonWidget",
      {
        "<p><img src=\"PicWt.png\" alt=\"Wt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtToggleButtonWidget.htm\">WtToggleButtonWidget</a> is a <a href=\"CppWt.htm\">Wt</a> ",
        "<a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">class</a> to display an <a href=\"CppToggleButtonWidget.htm\">ToggleButtonWidget</a>.</p>"
      }
    }
  );
  m.push_back(
    { "CppWtWidgetsWidget",
      {
        "<p><img src=\"PicWt.png\" alt=\"Wt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppWtWidgetsWidget.htm\">WtWidgetsWidget</a> is a <a href=\"CppWt.htm\">Wt</a> ",
        "<a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">class</a> to display an <a href=\"CppWidgetsWidget.htm\">WidgetsWidget</a>.</p>"
      }
    }
  );

  m.push_back(
    { "CppXml",
      {
        "<p>'Extensible Markup Language (<a href=\"CppXml.htm\">XML</a>) is a set of rules for encoding documents in machine-readable form' [1].</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"CppXml.htm\">XML</a> <a href=\"CppCodeSnippets.htm\">code snippets</a></h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppSplitXml.htm\">SplitXml</a></li>",
        "  <li><a href=\"CppXmlToPretty.htm\">XmlToPretty</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"Cpp.htm\">C++</a> <a href=\"CppXml.htm\">XML</a> <a href=\"CppParser.htm\">parsers</a></h2>",
        "<p>&nbsp;</p>",
        "<p>Incomplete list.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppProperty_tree.htm\">boost::property_tree</a></li>",
        "  <li>RapidXML</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"CppReferences.htm\">References</a></h2>",
        "<p>&nbsp;</p>",
        "<ol>",
        "  <li><a href=\"http://en.wikipedia.org/wiki/XML\">Wikipedia page about XML</a></li>",
        "</ol>"
      }
    }
  );


  m.push_back(
    { "CppYodaConditionExample1",
      {
        "<p><img src=\"PicStl.png\" alt=\"STL\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppYodaConditionExample1.htm\">Yoda condition example 1: basics</a> is a <a href=\"CppYodaCondition.htm\">Yoda condition</a> <a href=\"CppExample.htm\">example</a>.",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppYodaConditionExample1.zip\">Download the Qt Creator project 'CppYodaConditionExample1' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameAminoAcidFighter",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  Amino Acid Fighter is a",
        "  <a href=\"Games.htm\">game</a> in which amino acids do battle to a maximum of",
        "  four players.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  Amino Acid Fighter has the following history:",
        "</p>",
        "<ul>",
        "  <li>2000: Quickbasic (code lost)</li>",
        "  <li>20xx: <a href=\"GameAminoAcidFighterVcl.htm\">Amino Acid Fighter (VCL)</a></li>",
        "  <li>201x: <a href=\"GameAminoAcidFighter.htm\">Amino Acid Fighter</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"GameAminoAcidFighter.wav\">Download the WAV with the theme music of 'Amino Acid Fighter'</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "GameAminoAcidFighterVcl",
      {
        "<p><img src=\"PicVcl.png\" alt=\"Vcl\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  Amino Acid Fighter is a",
        "  <a href=\"Games.htm\">game</a> in which amino acids do battle to a maximum of",
        "  four players.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  Amino Acid Fighter has the following history:",
        "</p>",
        "<ul>",
        "  <li>2000: Quickbasic (code lost)</li>",
        "  <li>20xx: <a href=\"GameAminoAcidFighterVcl.htm\">Amino Acid Fighter (VCL)</a></li>",
        "  <li>201x: <a href=\"GameAminoAcidFighter.htm\">Amino Acid Fighter</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"GameAminoAcidFighter_0_9.png\">View a screenshot of 'Amino Acid Fighter' (version 0.9)(png)</a></li>",
        "  <li><a href=\"GameAminoAcidFighterMenu_0_9.png\">View a screenshot of the 'Amino Acid Fighter' menu screen (version 0.9)(png)</a></li>",
        "  <li><a href=\"GameAminoAcidFighter.wav\">Download the WAV with the theme music of 'Amino Acid Fighter'</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "GameBeerGetter",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameBeerGetter.htm\">BeerGetter</a> is a simple <a href=\"Games.htm\">game</a>. Work in progress..</p>",
        "<ul>",
        "  <li><a href=\"GameBeerGetterScreenshot.png\">View a screenshot of 'BeerGetter'</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameBeerWanter",
      {
        "<p><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicNds.png\" alt=\"NDS\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameBeerWanter.htm\">BeerWanter</a> is a <a href=\"Games.htm\">game</a> in which the player must click on the beer.</p>",
        "<p>&nbsp;</p>",
         "<p><a href=\"GameBeerWanter.htm\">BeerWanter</a>, the successor of <a href=\"GameBeerWanterVcl.htm\">BeerWanterVcl</a>, uses the cross-platform <a href=\"CppQt.htm\">Qt</a> <a href=\"CppLibrary.htm\">library</a>.",
         "<p><a href=\"GameBeerWanterVcl.htm\">BeerWanterVcl</a>, the predecessor of <a href=\"GameBeerWanter.htm\">BeerWanter</a>, uses the Windows-only <a href=\"CppVcl.htm\">VCL</a> <a href=\"CppLibrary.htm\">library</a>.",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameBeerWanter.htm\">BeerWanter</a> can also be deployed as a <a href=\"CppWebApplication.htm\">web application</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>",
        "    <img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"GameBeerWanter5.png\">View a screenshot of 'BeerWanter' (version 5.0)(png)</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicNds.png\" alt=\"NDS\"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"GameBeerWanter_5_3.png\">View a screenshot of 'BeerWanter' (version 5.3)</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/> ",
        "    <a href=\"GameBeerWanter5Exe.zip\">Download the 'BeerWanter' Windows executable (version 5.0)(zip)</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicNds.png\" alt=\"NDS\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/> ",
        "    <a href=\"GameBeerWanterNds_5_3.zip\">Download the 'BeerWanter' NDS executable (version 5.3)(zip)</a>",
        "  </li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>",
        "    <img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicNds.png\" alt=\"NDS\"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"GameBeerWanter_5_1.png\">View a screenshot of 'BeerWanter' under NDS (version 5.1)</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"GameBeerWanter4.png\">View a screenshot of 'BeerWanter' (version 4.0)</a>",
        "  </li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameBeerWanterVcl",
      {
        "<p><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameBeerWanterVcl.htm\">BeerWanterVcl</a> is a <a href=\"Games.htm\">game</a> in which the player must click on the beer.</p>",
        "<p>&nbsp;</p>",
         "<p><a href=\"GameBeerWanterVcl.htm\">BeerWanterVcl</a>, the predecessor of <a href=\"GameBeerWanter.htm\">BeerWanter</a>, uses the Windows-only <a href=\"CppVcl.htm\">VCL</a> <a href=\"CppLibrary.htm\">library</a>.",
         "<p><a href=\"GameBeerWanter.htm\">BeerWanter</a>, the successor of <a href=\"GameBeerWanterVcl.htm\">BeerWanterVcl</a>, uses the cross-platform <a href=\"CppQt.htm\">Qt</a> <a href=\"CppLibrary.htm\">library</a>.",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>",
        "    <img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"GameBeerWanter3.png\">View a screenshot of 'BeerWanter' (version 3.0)</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicSpacer.png\" alt=\" \"/><img src=\"PicSpacer.png\" alt=\" \"/>",
        "    <a href=\"GameBeerWanter3Exe.zip\">Download the 'BeerWanter' Windows executable (version 3.0)(zip)</a>",
        "  </li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>The source code of BeerWanter 1.0 and 2.0 has been lost (but was very simular to version 3.0).</p>"
      }
    }
  );

  m.push_back(
    { "GameAthleticLand",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameAthleticLand.htm\">Athletic Land</a> is an unfinished <a href=\"Games.htm\">game</a> that is a PC clone of the MSX <a href=\"Games.htm\">game</a> 'Athletic Land'.</p>",
        "<p>&nbsp;</p>",
         "<p><a href=\"GameAthleticLand.htm\">Athletic Land</a>, the successor of <a href=\"GameAthleticLandVcl.htm\">Athletic Land (VCL)</a>, uses the cross-platform <a href=\"CppQt.htm\">Qt</a> <a href=\"CppLibrary.htm\">library</a>.",
         "<p><a href=\"GameAthleticLandVcl.htm\">Athletic Land (VCL)</a>, the predecessor of <a href=\"GameAthleticLand.htm\">Athletic Land</a>, uses the Windows-only <a href=\"CppVcl.htm\">VCL</a> <a href=\"CppLibrary.htm\">library</a>.",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"GameAthleticLand_0_9.png\">View a screenshot of 'AthleticLand' (version 0.9)(png)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>External links</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"http://www.youtube.com/watch?v=isjCc7CiSfM\">YouTube video of 'Athletic Land'</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameAthleticLandVcl",
      {
        "<p><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameAthleticLandVcl.htm\">Athletic Land (VCL)</a> is an unfinished <a href=\"Games.htm\">game</a> that is a PC clone of the MSX <a href=\"Games.htm\">game</a> 'Athletic Land'.</p>",
        "<p>&nbsp;</p>",
         "<p><a href=\"GameAthleticLand.htm\">Athletic Land</a>, the successor of <a href=\"GameAthleticLandVcl.htm\">Athletic Land (VCL)</a>, uses the cross-platform <a href=\"CppQt.htm\">Qt</a> <a href=\"CppLibrary.htm\">library</a>.",
         "<p><a href=\"GameAthleticLandVcl.htm\">Athletic Land (VCL)</a>, the predecessor of <a href=\"GameAthleticLand.htm\">Athletic Land</a>, uses the Windows-only <a href=\"CppVcl.htm\">VCL</a> <a href=\"CppLibrary.htm\">library</a>.",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"GameAthleticLand_0_9.png\">View a screenshot of 'AthleticLand' (version 0.9)(png)</a></li>",
        "  <li><a href=\"GameAthleticLandExe_0_9.zip\">Download a Windows executable of 'AthleticLand' (version 0.9)(zip)</a></li>",
        "  <li><a href=\"GameAthleticLandSource_0_9.zip\">Download the source code of 'AthleticLand' (version 0.9)(zip)</a></li>",
        "  <li><a href=\"GameAthleticLandSprites_0_9.zip\">Download the (.bmp) sprites of 'AthleticLand' (version 0.9)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>External links</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"http://www.youtube.com/watch?v=isjCc7CiSfM\">YouTube video of 'Athletic Land'</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameBinnenVolley",
      {
        "<p><img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameBinnenVolley.htm\">BinnenVolley</a> is a two-player Dutch <a href=\"Games.htm\">game</a> similar to <a href=\"http://en.wikipedia.org/wiki/Arcade_Volleyball\">Arcade Volleyball</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"GameBinnenVolley.htm\">BinnenVolley</a> is programmed in <a href=\"Cpp.htm\">C++</a> using the IDE <a href=\"CppBuilder.htm\">C++ Builder</a> 6.0. It uses the <a href=\"CppVcl.htm\">VCL</a> and <a href=\"CppBoost.htm\">Boost</a> library. The beta version (0.9) is released at the 18th of February of 2010.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"GameBinnenVolleyScreenshot.png\">View a screenshot of 'BinnenVolley' (v.0.9)(png)</a></li>",
        "  <li><a href=\"GameBinnenVolleyScreenshotMenu.png\">View a screenshot of the 'BinnenVolley' menu screen (v.0.9)(png)</a></li>",
        "  <li><a href=\"GameBinnenVolleyExe.zip\">Download the 'BinnenVolley' Windows executable (v.0.9)(zip)</a></li>",
        "  <li><a href=\"GameBinnenVolleySource.zip\">Download the 'BinnenVolley' source code (v.0.9)(zip)</a></li>",
        "  <li><a href=\"GameBinnenVolleySource_0_9.htm\">View the 'BinnenVolley' source code as web page (v.0.9)(htm)</a></li>",
        "  <li><a href=\"GameBinnenVolleySprites.zip\">Download the 'BinnenVolley' (.bmp) sprites (v.0.9)(zip)</a></li>",
        "<!--  <li><a href=\"GameBinnenVolleyCdFront.png\">View the CD artwork of 'BinnenVolley' (front)(png)</a></li> -->",
        "<!--  <li><a href=\"GameBinnenVolleyCdBack.png\">View the CD artwork of 'BinnenVolley' (back)(png)</a></li> -->",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameBoenken",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameBoenken.htm\">Boenken</a> is <a href=\"Games.htm\">game</a> that is a crossing-over between soccer and billiards and can be played with twenty players. The <a href=\"Games.htm\">game</a>'s name is Dutch, translating it to English would yield something like 'Bonking' (but if I would call the <a href=\"Games.htm\">game</a> like that, my website would attract other people). 'Boenk' is the phonetic word of the sound two colliding Dutch snooker balls make.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameBoenken.htm\">Boenken</a> can be played with twenty players at the same time (on the same single keyboard). Who said that video <a href=\"Games.htm\">games</a> could not be cosy?</p>",
        "<p>&nbsp;</p>",
        "<p>Before version 3.0, <a href=\"GameBoenken.htm\">Boenken</a> was called <a href=\"GameBoenkenVcl.htm\">BoenkenVcl</a> and was programmed in <a href=\"Cpp.htm\">C++</a> using the IDE ",
        "<p><a href=\"CppBuilder.htm\">C++ Builder</a> 6.0, with use of the <a href=\"CppVcl.htm\">VCL</a> and <a href=\"CppBoost.htm\">Boost</a> <a href=\"CppLibrary.htm\">libraries</a>.",
        "<p>&nbsp;</p>",
        "<p>The <a href=\"Games.htm\">game</a> relies heavily on the function <a href=\"CppDoPerfectElasticCollision.htm\">DoPerfectElasticCollision</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/> <a href=\"GameBoenken_4_1.png\">View a screenshot of 'Boenken' (version 4.1)(png)</a></li>",
        "  <li><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/> <a href=\"GameBoenkenMenu_4_1.png\">View a screenshot of the 'Boenken' menu screen (version 4.1)(png)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/> <a href=\"GameBoenkenExe_4_1.zip\">Download a Windows executable of 'Boenken' (version 4.1)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/> <a href=\"GameBoenken_3_1.png\">View a screenshot of 'Boenken' (version 3.1)(png)</a></li>",
        "  <li><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/> <a href=\"GameBoenkenMenu_3_1.png\">View a screenshot of the 'Boenken' menu screen (version 3.1)(png)</a></li>",
        "  <li><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/> <a href=\"GameBoenken_3_0.png\">View a screenshot of 'Boenken' (version 3.0)(png)</a></li>",
        "  <li>Older: <a href=\"GameBoenkenVcl.htm\">BoenkenVcl</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameBoenkenVcl",
      {
        "<p><img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicWindows.png\" alt=\"Windows\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameBoenkenVcl.htm\">BoenkenVcl)</a> is <a href=\"Games.htm\">game</a> that is a crossing-over between soccer and billiards and can be played with twenty players. The <a href=\"Games.htm\">game</a>'s name is Dutch, translating it to English would yield something like 'Bonking' (but if I would call the <a href=\"Games.htm\">game</a> like that, my website would attract other people). 'Boenk' is the phonetic word of the sound two colliding Dutch snooker balls make.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameBoenkenVcl.htm\">BoenkenVcl</a> can be played with twenty players at the same time (on the same single keyboard). Who said that video <a href=\"Games.htm\">games</a> could not be cosy?</p>",
        "<p>&nbsp;</p>",
        "<p>Since version 3.0, <a href=\"GameBoenkenVcl.htm\">BoenkenVcl</a> was renamed <a href=\"GameBoenken.htm\">Boenken</a> and ported to <a href=\"CppQtCreator.htm\">Qt Creator</a> to make use of the cross-platform",
        "<a href=\"CppQt.htm\">Qt</a> <a href=\"CppLibrary.htm\">library</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>Newer: <a href=\"GameBoenken.htm\">Boenken</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/> <a href=\"GameBoenkenMenu_2_0.png\">View a screenshot of the menu of 'Boenken' (version 2.0)(png)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/> <a href=\"GameBoenken_2_0.png\">View a screenshot of 'Boenken' (version 2.0)(png)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/> <a href=\"GameBoenken_1_0.png\">View a screenshot of 'Boenken' (version 1.0)(png)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/> <a href=\"GameBoenkenMenu_1_0.png\">View a screenshot of the menu of 'Boenken' (version 1.0)(png)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameConnectThree",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameConnectThree.htm\">ConnectThree</a> is a turn-based tic-tac-toe-like <a href=\"Games.htm\">game</a>.",
        "It can be played by one, two or three players.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"GameConnectThree_6_0.png\">View a screenshot of 'ConnectThree' (version 6.0)(png)</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"GameConnectThree_5_2.png\">View a screenshot of 'ConnectThree' (version 5.2)(png)</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"GameConnectThreeMenu_5_2.png\">View a screenshot of the 'ConnectThree' menu (version 5.2)(png)</a></li>",
        "  <li><a href=\"GameConnectThreeArchitecture_6_2.png\">View the architecture of 'ConnectThree' (version 6.2)(png)</a></li>",
        "  <li><a href=\"GameConnectThreeArchitecture_6_2.dia\">View the architecture of 'ConnectThree' (version 6.2)(dia)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"GameConnectThreeExeWindows_5_2.zip\">Download the 'ConnectThree' Windows executable (version 5.2)(zip)</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"GameConnectThreeSource_6_2.zip\">Download the 'ConnectThree' source code (version 6.2)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>The <a href=\"CppWindows.htm\">Windows</a> executable of version 5.2 is created following <a href=\"CppQtCrosscompileToWindowsExample15.htm\">how to cross-compile a Qt Creator project from Ubuntu to a windows executable: example 15: MinGW cross-compiling environment</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"GameConnectThreeSource_6_1.zip\">Download the 'ConnectThree' source code (version 6.1)(zip)</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"GameConnectThreeSource_6_0.zip\">Download the 'ConnectThree' source code (version 6.0)(zip)</a></li>",
        "  <li><a href=\"GameConnectThreeArchitecture_6_0.png\">View the architecture of 'ConnectThree' (version 6.0)(png)</a></li>",
        "  <li><a href=\"GameConnectThreeArchitecture_6_0.dia\">View the architecture of 'ConnectThree' (version 6.0)(dia)</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"GameConnectThreeSource_5_2.zip\">Download the 'ConnectThree' source code (version 5.2)(zip)</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"GameConnectThree_5_0.png\">View a screenshot of 'ConnectThree' (version 5.0)(png)</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"GameConnectThreeMenu_5_0.png\">View a screenshot of the 'ConnectThree' menu (version 5.0)(png)</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"GameConnectThreeSource_5_1.zip\">Download the 'ConnectThree' source code (version 5.1)(zip)</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"GameConnectThreeSource_5_0.zip\">Download the 'ConnectThree' source code (version 5.0)(zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameCorridor",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameCorridor.htm\">Corridor</a> is a <a href=\"Games.htm\">game</a> written by Or Dvory (also known as gnudles) in 2007 ",
        "and ported by me to a <a href=\"CppQtCreator.htm\">Qt Creator</a> project on the 17th September 2010.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"GameCorridor.png\">View a screenshot of 'Corridor' (png)</a></li>",
        "  <li><a href=\"GameCorridor.zip\">Download the source code of 'Corridor' (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameDasWahreSchlagerfest",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameDasWahreSchlagerfest.htm\">Das Wahre Schlagerfest</a> is a <a href=\"Games.htm\">game</a> that was programmed on the 30th September 2003 during a 'Spass programmieren' session.",
        "It is the one <a href=\"Games.htm\">game</a> that can be played on a theme party with theme 'Germany', or as a substitute for the Oktoberfest. ",
        "If you want a beer or bratwurst, you can just go fetching one without fear of losing the <a href=\"Games.htm\">game</a>!</p>",
        "<p>&nbsp;</p>",
        "<p>Before version 2.0, <a href=\"GameDasWahreSchlagerfest.htm\">Das Wahre Schlagerfest</a> was called <a href=\"GameDasWahreSchlagerfestVcl.htm\">Das Wahre Schlagerfest (VCL)</a> and programmed",
        "in <a href=\"Cpp.htm\">C++</a> using the <a href=\"CppBuilder.htm\">C++ Builder</a> 6.0 <a href=\"CppIde.htm\">IDE</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicConsole.png\" alt=\"Console\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/> <a href=\"GameDasWahreSchlagerfest_2_5.png\">View a screenshot of 'Das Wahre Schlagerfest' (version 2.5)(png)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/> <a href=\"GameDasWahreSchlagerfest_2_2.png\">View a screenshot of 'Das Wahre Schlagerfest' (version 2.2)(png)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/> <a href=\"GameDasWahreSchlagerfest_2_2_menu.png\">View a screenshot of 'Das Wahre Schlagerfest' its menu screen (version 2.2)(png)</a></li>",
        "  <li><img src=\"PicWeb.png\" alt=\"Web\"/><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/> <a href=\"GameDasWahreSchlagerfestExe_2_2.zip\">Download a windows executable of 'Das Wahre Schlagerfest' (version 2.2)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/> <a href=\"GameDasWahreSchlagerfest_2_1.png\">View a screenshot of 'Das Wahre Schlagerfest' (version 2.1)(png)</a></li>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/> <a href=\"GameDasWahreSchlagerfest_2_0.png\">View a screenshot of 'Das Wahre Schlagerfest' (version 2.0)(png)</a></li>",
        "  <li>Older: <a href=\"GameDasWahreSchlagerfestVcl.htm\">Das Wahre SchlagerfestVcl</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameDasWahreSchlagerfestVcl",
      {
        "<p><img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameDasWahreSchlagerfestVcl.htm\">Das Wahre Schlagerfest (VCL)</a> is a <a href=\"Games.htm\">game</a> that was programmed on the 30th September 2003 during a 'Spass programmieren' session.",
        "It is the one <a href=\"Games.htm\">game</a> that can be played on a theme party with theme 'Germany', or as a substitute for the Oktoberfest. ",
        "If you want a beer or bratwurst, you can just go fetching one without fear of losing the <a href=\"Games.htm\">game</a>!</p>",
        "<p>&nbsp;</p>",
        "<p>in 2012, <a href=\"GameDasWahreSchlagerfestVcl.htm\">Das Wahre Schlagerfest (VCL)</a> was renamed to <a href=\"GameDasWahreSchlagerfest.htm\">Das Wahre Schlagerfest</a> ported",
        "to <a href=\"CppQtCreator.htm\">Qt Creator</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>Newer: <a href=\"GameDasWahreSchlagerfest.htm\">Das Wahre Schlagerfest</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/> <a href=\"GameDasWahreSchlagerfestSource_1_0.zip\">Download the source code of 'Das Wahre Schlagerfest' (version 1.0)(zip)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/> <a href=\"GameDasWahreSchlagerfest_1_0.png\">View a screenshot of 'Das Wahre Schlagerfest' (version 1.0)(png)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/> <a href=\"GameDasWahreSchlagerfestExe_1_0.zip\">Download a windows executable of 'Das Wahre Schlagerfest' (version 1.0)(zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameEukaryote",
      {
        "<p><a href=\"GameEukaryote.htm\">Eukaryote</a> is a top-view strategy <a href=\"Games.htm\">game</a> in which the ",
        "units are cells and organelles. Check out the presentation...</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"GameEukaryote.ppt\">View the powerpoint presentation of 'Eukaryote'</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameEverythingToPiecesShooter",
      {
        "<p><img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameEverythingToPiecesShooter.htm\">EverythingToPiecesShooter</a> is a <a href=\"Games.htm\">game</a> made by Joost van den Bogaart in the year 2005, released under the GPL 3.0.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameEverythingToPiecesShooter.htm\">EverythingToPiecesShooter</a> is programmed in <a href=\"Cpp.htm\">C++</a> using the IDE <a href=\"CppBuilder.htm\">C++ Builder</a> 6.0. It uses the <a href=\"CppVcl.htm\">VCL</a> and <a href=\"CppBoost.htm\">Boost</a> libraries.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>...</li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameK3OpEenRij",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameK3OpEenRij.htm\">K3-Op-Een-Rij</a> is a <a href=\"Games.htm\">game</a> that is tribute to the Flemisch girlyband K3. ",
        "<a href=\"GameK3OpEenRij.htm\">K3-Op-Een-Rij</a> is a turn-based tic-tac-toe-like <a href=\"Games.htm\">game</a>. ",
        "It can be played by one, two or three players. The <a href=\"Games.htm\">game</a> is designed for this band's typical audience.</p>",
        "<p>&nbsp;</p>",
        "<p>Thanks to Mark Wiering, for reviving my interest in Kathleen: thanks to him you can choose both girls since version 5.0.</p>",
        "<p>&nbsp;</p>",
        "<p>Mark Wiering notified me of two variants to play the <a href=\"Games.htm\">game</a>:</p>",
        "<ul>",
        "  <li>Classic: win the <a href=\"Games.htm\">game</a> by getting three-in-a-row</li>",
        "  <li>Survivor: Win the <a href=\"Games.htm\">game</a> by filling the screen without anyone getting three-in-a-row</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>Currently, only the 'Classic' mode is supported.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ol>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"GameK3OpEenRij_6_0.png\">View a screenshot of 'K3-Op-Een-Rij' (version 6.0)(png)</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"GameK3OpEenRij_5_1Windows.png\">View a screenshot of 'K3-Op-Een-Rij' (version 5.1)(png)</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"GameK3OpEenRij_5_0.png\">View a screenshot of 'K3-Op-Een-Rij' (version 5.0)(png)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"GameK3OpEenRijDesktopExe_6_0.zip\">Download the 'K3-Op-Een-Rij' Windows executable (version 6.0)(zip)</a></li>",
        "</ol>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ol>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"GameK3OpEenRij_5_1Lubuntu.png\">View a screenshot of 'K3-Op-Een-Rij' (version 5.1)(png)</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"GameK3OpEenRijMenu_5_0.png\">View a screenshot of the 'K3-Op-Een-Rij' menu (version 5.0)(png)</a></li>",
        "  <li>Older: <a href=\"GameK3OpEenRijVcl.htm\">K3-Op-Een-Rij (VCL)</a></li>",
        "</ol>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>External links</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"http://www.k3.be/\">The official K3 website (Dutch)</a></li>",
        "  <li><a href=\"http://en.wikipedia.org/wiki/K3_%28band%29\">The K3 wikipedia page (English)</a></li>",
        "  <li><a href=\"http://nl.wikipedia.org/wiki/K3\">The K3 wikipedia page (Dutch)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameK3OpEenRijVcl",
      {
        "<p><img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameK3OpEenRijVcl.htm\">K3-Op-Een-Rij (VCL)</a> is a <a href=\"Games.htm\">game</a> that is tribute to the Flemisch girlyband K3.",
        "<a href=\"GameK3OpEenRij.htm\">K3-Op-Een-Rij</a> is a turn-based tic-tac-toe-like <a href=\"Games.htm\">game</a>.",
        "It can be played by one, two or three players. The <a href=\"Games.htm\">game</a> is designed for this band's typical audience.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ol>",
        "  <li>Newer: <a href=\"GameK3OpEenRij.htm\">K3-Op-Een-Rij</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"GameK3OpEenRijDesktopExe_6_0.zip\">Download the 'K3-Op-Een-Rij' Windows executable (version 6.0)(zip)</a></li>",
        "  <li><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"GameK3OpEenRij_4_0.png\">View a screenshot of 'K3-Op-Een-Rij' (version 4.0)(png)</a></li>",
        "  <li><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"GameK3OpEenRijMenu_4_0.png\">View a screenshot of the 'K3-Op-Een-Rij' menu (version 4.0)(png)</a></li>",
        "</ol>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ol>",
        "  <li><a href=\"GameK3OpEenRijSprites_4_0.zip\">Download the 'K3-Op-Een-Rij' sprites (version 4.0)(zip)</a></li>",
        "  <li><a href=\"GameK3OpEenRij_3_0.png\">View a screenshot of 'K3-Op-Een-Rij' (version 3.0)(png)</a></li>",
        "</ol>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>External links</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"http://www.k3.be/\">The official K3 website (Dutch)</a></li>",
        "  <li><a href=\"http://en.wikipedia.org/wiki/K3_%28band%29\">The K3 wikipedia page (English)</a></li>",
        "  <li><a href=\"http://nl.wikipedia.org/wiki/K3\">The K3 wikipedia page (Dutch)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameKnokfighter",
      {
        "<p><img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"GameKnokfighter.htm\">Knokfighter</a> is a <a href=\"Games.htm\">game</a>",
        "  programmed by me and Joost van den Bogaart. It is a ",
        "  Double Dragon clone with ourselves as the heroes.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"GameKnokfighterStory_1_0.zip\">Download the (.ppt) storyline of the final game (version 1.0)(zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "GameKnokfighterVcl",
      {
        "<p><img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"GameKnokfighterVcl.htm\">Knokfighter (VCL)</a> is a <a href=\"Games.htm\">game</a>",
        "  programmed by me and Joost van den Bogaart. It is a ",
        "  Double Dragon clone with ourselves as the heroes.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"GameKnokfighterVcl.htm\">Knokfighter (VCL)</a> is the predecessor",
        "  of <a href=\"GameKnokfighter.htm\">Knokfighter</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"GameKnokfighter_1_0.png\">View a screenshot of 'Knokfighter (VCL)' (version 1.0)(png)</a></li>",
        "  <li><a href=\"GameKnokfighterExe_1_0.zip\">Download the 'Knokfighter (VCL)' Windows executable (version 1.0)(zip)</a></li>",
        "  <li><a href=\"GameKnokfighterResources_1_0.zip\">Download the 'Knokfighter' resources (version 1.0)(bmp)(zip)</a></li>",
        "  <li><a href=\"GameKnokfighterExeNoResources_1_0.zip\">Download the 'Knokfighter (VCL)' Windows executable (without resources)(version 1.0)(zip)</a></li>",
        "</ul>"
      }
    }
  );


  m.push_back(
    { "GameMartianCafeTuinemaTycoon",
      {
        "<p><img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameMartianCafeTuinemaTycoon.htm\">Martian Cafe Tuinema Tycoon</a> is a <a href=\"Games.htm\">game</a> made by Joost van den Bogaart in the year 2005, released under the GPL 3.0.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameMartianCafeTuinemaTycoon.htm\">Martian Cafe Tuinema Tycoon</a> is programmed in <a href=\"Cpp.htm\">C++</a> using the IDE <a href=\"CppBuilder.htm\">C++ Builder</a> 6.0. It uses the <a href=\"CppVcl.htm\">VCL</a> and <a href=\"CppBoost.htm\">Boost</a> libraries.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"GameMartianCafeTuinemaTycoon_1_0.png\">View a screenshot of 'Martian Cafe Tuinema Tycoon' (version 1.0)(png)</a></li>",
        "  <li><a href=\"GameMartianCafeTuinemaTycoonExe_1_0.zip\">Download the 'Martian Cafe Tuinema Tycoon' Windows executable (version 1.0)(zip)</a></li>",
        "  <li><a href=\"GameMartianCafeTuinemaTycoonSource_1_0.zip\">Download the 'Martian Cafe Tuinema Tycoon' source code (version 1.0)(zip)</a></li>",
        "  <li><a href=\"GameMartianCafeTuinemaTycoonSource_1_0.htm\">View the C++ Builder source code of 'Martian Cafe Tuinema Tycoon' as a web page (version 1.0)(htm)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameMaziak",
      {
        "<p>Maziak is a simple maze retro <a href=\"Games.htm\">game</a> (and a clone of the Sinclair ZX Spectrum/MSX <a href=\"Games.htm\">game</a> Maziak/Maziacs/Mazoggs), in which you have to find a maze's exit. But there are also enemies in the maze that can be beaten by a sword. There are also prisoners, that temporarily show the way to the exit upon freeing them.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ol>",
        "  <li><a href=\"GameMaziak_2_0.png\">View a screenshot of 'Maziak' (v.2.0)(png)</a></li>",
        "  <li><a href=\"GameMaziakMenu_2_0.png\">View a screenshot of the 'Maziak' menu screen (v.2.0)(png)</a></li>",
        "  <li><a href=\"GameMaziakInstructions_2_0.png\">View a screenshot of the 'Maziak' instructions screen (v.2.0)(png)</a></li>",
        "  <li><a href=\"GameMaziakSprites_2_0.zip\">Download the 'Maziak' (png) sprites (v.2.0)(zip)</a></li>",
        "  <li>Older: <a href=\"GameMaziakVcl.htm\">Maziak (VCL)</a></li>",
        "</ol>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"GameMaziak.htm\">Maziak</a> history</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>YYYY-MM-DD: [description]</li>",
        "  <li>1987-xx-xx: Maziak was one of my favorite MSX games</li>",
        "  <li>2007-10-20: I wanted to developed a Windows clone of Maziak, because the original was nowhere to be found, so I programmed Maziak v. 1.0.</li>",
        "  <li>2010-02-05: Discovered that the original game name was 'Maziacs' or 'Mazogs'. And that my clone was not that identical at all</li>",
        "  <li>2010-02-16: Maziak v. 1.1: changed graphics to resemble original more</li>",
        "  <li>2010-02-17: Maziak v. 1.2: added animated sprites</li>",
        "  <li>2010-02-18: Maziak v. 1.3: added animated fights</li>",
        "  <li>2010-02-25: Maziak v. 1.4: small improvements</li>",
        "  <li>2010-07-31: Maziak v. 2.0: Maziak is now cross-platform!</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>External links</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"http://en.wikipedia.org/wiki/Maziacs\">View the WikiPedia page on the original Maziacs</a></li>",
        "  <li><a href=\"http://www.youtube.com/watch?v=MQE3VK1Bdh4\">View a YouTube video of the original Maziacs on the Sinclair ZX Spectrum</a></li>",
        "  <li><a href=\"http://www.classic-retro-games.com/Mazogs-%28and-Maziacs%29_124.html\">Another Maziacs PC clone</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameMaziakVcl",
      {
        "<p><img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>Maziak is a simple maze retro <a href=\"Games.htm\">game</a> (and a clone of the Sinclair ZX Spectrum/MSX <a href=\"Games.htm\">game</a> Maziak/Maziacs/Mazoggs), in which you have to find a maze's exit. But there are also enemies in the maze that can be beaten by a sword. There are also prisoners, that temporarily show the way to the exit upon freeing them.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ol>",
        "  <li>Newer: <a href=\"GameMaziak.htm\">Maziak</a></li>",
        "  <li><a href=\"GameMaziak_1_3.png\">View a screenshot of 'Maziak' (v.1.3)(png)</a></li>",
        "  <li><a href=\"GameMaziakInstructions_1_3.png\">View a screenshot of the 'Maziak' instructions screen (v.1.3)(png)</a></li>",
        "  <li><a href=\"GameMaziakMenu_1_3.png\">View a screenshot of the 'Maziak' menu screen (v.1.3)(png)</a></li>",
        "  <li><a href=\"GameMaziakSprites_1_4.zip\">Download the 'Maziak' (bmp) sprites (v.1.4)(zip)</a></li>",
        "  <li><a href=\"GameMaziakExe_1_4.zip\">Download the 'Maziak' Windows executable (v.1.4)(zip)</a></li>",
        "</ol>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ol>",
        "  <li><a href=\"GameMaziakSprites_1_3.zip\">Download the 'Maziak' (bmp) sprites (v.1.3)(zip)</a></li>",
        "  <li><a href=\"GameMaziak_1_2.png\">View a screenshot of 'Maziak' (v.1.2)(png)</a></li>",
        "  <li><a href=\"GameMaziakMenu_1_2.png\">View a screenshot of the 'Maziak' menu screen (v.1.2)(png)</a></li>",
        "  <li><a href=\"GameMaziak_1_1.png\">View a screenshot of 'Maziak' (v.1.1)(png)</a></li>",
        "  <li><a href=\"GameMaziakMenu_1_1.png\">View a screenshot of the 'Maziak' menu screen (v.1.1)(png)</a></li>",
        "  <li><a href=\"GameMaziak_1_0.png\">View a screenshot of 'Maziak' (v.1.0)(png)</a></li>",
        "  <li><a href=\"GameMaziakMenu_1_0.png\">View a screenshot of the 'Maziak' menu screen (v.1.0)(png)</a></li>",
        "</ol>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>External links</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"http://en.wikipedia.org/wiki/Maziacs\">View the WikiPedia page on the original Maziacs</a></li>",
        "  <li><a href=\"http://www.youtube.com/watch?v=MQE3VK1Bdh4\">View a YouTube video of the original Maziacs on the Sinclair ZX Spectrum</a></li>",
        "  <li><a href=\"http://www.classic-retro-games.com/Mazogs-%28and-Maziacs%29_124.html\">Another Maziacs PC clone</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameMetZnDrieen",
      {
        "<p><img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"GameMetZnDrieen.htm\">Met Z'n Drieen</a> is a Dutch turn-based tic-tac-toe-like",
        "  <a href=\"Games.htm\">game</a>. It can be played by one, two or three players. The",
        "  <a href=\"Games.htm\">game</a> is in the Dutch language.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>...</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>"
      }
    }
  );

  m.push_back(
    { "GameMetZnDrieenVcl",
      {
        "<p><img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"GameMetZnDrieenVcl.htm\">Met Z'n Drieen (VCL)</a> is a Dutch turn-based tic-tac-toe-like",
        "  <a href=\"Games.htm\">game</a>. It can be played by one, two or three players. The",
        "  <a href=\"Games.htm\">game</a> is in the Dutch language.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"GameMetZnDrieenVcl.htm\">Met Z'n Drieen (VCL)</a> is the predecessor",
        "  of <a href=\"GameMetZnDrieen.htm\">Met Z'n Drieen</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"GameMetZnDrieen_1_3.png\">View a screenshot of 'Met Z'n Drieen' (v.1.3)(png)</a></li>",
        "  <li><a href=\"GameMetZnDrieenMenu_1_3.png\">View a screenshot of the 'Met Z'n Drieen' menu screen (v.1.3)(png)</a></li>",
        "  <li><a href=\"GameMetZnDrieenExe_1_3.zip\">Download the 'Met Z'n Drieen' Windows executable (v.1.3)(zip)</a></li>",
        "  <li><a href=\"GameMetZnDrieenCdFront.png\">View the CD artwork of 'Met z'n Drieen' (front)(png)</a></li>",
        "  <li><a href=\"GameMetZnDrieenCdFront.bmp\">View the CD artwork of 'Met z'n Drieen' (front)(bmp)</a></li>",
        "  <li><a href=\"GameMetZnDrieenCdBack.png\">View the CD artwork of 'Met z'n Drieen' (back)(png)</a></li>",
        "  <li><a href=\"GameMetZnDrieenCdBack.bmp\">View the CD artwork of 'Met z'n Drieen' (back)(bmp)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"GameMetZnDrieenScreenshot_1_2.png\">View a screenshot of 'Met Z'n Drieen' (v.1.2)(png)</a></li>",
        "  <li><a href=\"GameMetZnDrieenScreenshotMenu_1_2.png\">View a screenshot of the 'Met Z'n Drieen' menu screen (v.1.2)(png)</a></li>",
        "  <li><a href=\"GameMetZnDrieenScreenshot_1_0.png\">View a screenshot of 'Met Z'n Drieen' (v.1.0)(png)</a></li>",
        "  <li><a href=\"GameMetZnDrieenExe_1_1.zip\">Download the 'Met Z'n Drieen' Windows executable (v.1.1)(zip)</a></li>",
        "  <li><a href=\"GameMetZnDrieenExe_1_0.zip\">Download the 'Met Z'n Drieen' Windows executable (v.1.0)(zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "GamePokeVolley",
      {
        "<p><img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GamePokeVolley.htm\">PokeVolley</a> is a <a href=\"Games.htm\">game</a> similar to <a href=\"http://en.wikipedia.org/wiki/Arcade_Volleyball\">Arcade Volleyball</a> with Pokemon graphics. It was born and its first version programmed at the 24th of September of 2005 during a session of 'Fun Programming' with Joost van den Bogaart.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GamePokeVolley.htm\">PokeVolley</a> is programmed in <a href=\"Cpp.htm\">C++</a> using the IDE <a href=\"CppBuilder.htm\">C++ Builder</a> 6.0. It uses the <a href=\"CppVcl.htm\">VCL</a> and <a href=\"CppBoost.htm\">Boost</a> libraries.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"GamePokeVolley_2_0.png\">View a screenshot of 'PokeVolley' (version 2.0)(png)</a></li>",
        "  <li><a href=\"GamePokeVolleyMenu_2_0.png\">View a screenshot of the 'PokeVolley' menu (version 2.0)(png)</a></li>",
        "  <li><a href=\"GamePokeVolleyExe_2_0.zip\">Download the 'PokeVolley' Windows executable (version 2.0)(zip)</a></li>",
        "  <li><a href=\"GamePokeVolleySource_2_0.zip\">Download the 'PokeVolley' source code (version 2.0)(zip)</a></li>",
        "  <li><a href=\"GamePokeVolleySource_2_0.htm\">View the C++ Builder source code of 'PokeVolley' as web page (version 2.0)(htm)</a></li>",
        "  <li><a href=\"GamePokeVolleyResources_2_0.zip\">Download the 'PokeVolley' resources (version 2.0)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"GamePokeVolleyExe_1_0.zip\">Download 'PokeVolley' (v1.0)(zip)</a>, complete</li>",
        "  <li><a href=\"GamePokeVolleyResources_1_0.rar\">Download the 'PokeVolley' resources (v1.0)(rar)</a></li>",
        "  <li><a href=\"GamePokeVolleyExe_1_0.rar\">Download the 'PokeVolley' Windows executable (v1.0)(rar)</a>, without the resources</li>",
        "  <li><a href=\"GamePokeVolleySource_1_0.rar\">Download the 'PokeVolley' source code (v1.0)(rar)</a>, without the resources</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h3>Controls</h3>",
        "<p>&nbsp;</p>",
        "<table summary=\"Pokevolley control\" border=\"1\">",
        "  <tr> <td><b>Action</b></td> <td><b>Key player 1</b></td> <td><b>Key player 2</b></td> </tr>",
        "  <tr> <td>Left</td> <td>A</td> <td>Key left</td> </tr>",
        "  <tr> <td>Right</td> <td>D</td> <td>Key right</td> </tr>",
        "  <tr> <td>Up/jump</td> <td>W</td> <td>Key up</td> </tr>",
        "  <tr> <td>Down</td> <td>S</td> <td>Key down</td> </tr>",
        "</table>"
      }
    }
  );

  m.push_back(
    { "GamePong",
      {
        "<p>",
        "  <a href=\"GamePong.htm\">Pong</a> is a Pong <a href=\"Games.htm\">game</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolPreDickAdvocaTor",
      {
        "<p>",
        "  <a href=\"ToolPreDickAdvocaTor.htm\">PreDickAdvocaTor</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to predict soccer world championship scores",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolPreDickAdvocaTor.png\">View a 'PreDickAdvocaTor' screenshot (v.1.0)(png)</a></li>",
        "  <li><a href=\"ToolPreDickAdvocaTorExe.zip\">Download the 'PreDickAdvocaTor' Windows executable (v.1.0)(zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "ToolPrimeExpert",
      {
        "<p>",
        "  <a href=\"ToolPrimeExpert.htm\">PrimeExpert</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to determine if a number is prime.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolQmakeWatcher",
      {
        "<p>",
        "  <a href=\"ToolQmakeWatcher.htm\">QmakeWatcher</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to show which qmake does with with the makefile it creates.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "GamePublicToiletManager5",
      {
        "<p><img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GamePublicToiletManager5.htm\">Public Toilet Manager 5 - The New Art Project</a> is a <a href=\"Games.htm\">game</a> made by Joost van den Bogaart, released under the GPL 3.0.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GamePublicToiletManager5.htm\">Public Toilet Manager 5 - The New Art Project</a> is programmed in <a href=\"Cpp.htm\">C++</a> using the IDE <a href=\"CppBuilder.htm\">C++ Builder</a> 6.0. It uses the <a href=\"CppVcl.htm\">VCL</a> library.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"GamePublicToiletManager_5_0.png\">View a screenshot of 'Public Toilet Manager 5'</a></li>",
        "  <li><a href=\"GamePublicToiletManagerExe_5_0.zip\">Download the 'Public Toilet Manager 5' Windows executable (zip)</a></li>",
        "  <li><a href=\"GamePublicToiletManagerSource_5_0.zip\">Download the 'Public Toilet Manager 5' source code (without resources)(zip)</a></li>",
        "  <li><a href=\"GamePublicToiletManagerResources_5_0.zip\">Download the 'Public Toilet Manager 5' resources (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GamePylos",
      {
        "<p><a href=\"GamePylos.htm\">Pylos</a> is the computer <a href=\"Games.htm\">game</a> of the board <a href=\"Games.htm\">game</a> called 'Pylos' or 'Pyraos'.",
        "<p>&nbsp;</p>",
        "<p><a href=\"GamePylos.htm\">Pylos</a> is programmed in <a href=\"Cpp.htm\">C++</a> using the ",
        "<a href=\"CppQtCreator.htm\">Qt Creator</a> <a href=\"CppIde.htm\">IDE</a> and uses the ",
        "<a href=\"CppBoost.htm\">Boost</a>, <a href=\"CppQt.htm\">Qt</a> and <a href=\"CppStl.htm\">STL</a> ",
        "<a href=\"CppLibrary.htm\">libraries</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"GamePylos_1_0.png\">View a screenshot of Pylos (version 1.0)(png)</a></li>",
        "  <li><a href=\"GamePylosMenu_1_0.png\">View a screenshot of the Pylos menu screen (version 1.0)(png)</a></li>",
        "  <li><a href=\"GamePylosInstructions_1_0.png\">View a screenshot of the Pylos instructions screen (version 1.0)(png)</a></li>",
        "  <li><a href=\"GamePylosSource_1_0.zip\">Download the source code of 'Pylos' (version 1.0)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Bugs to fix</h2>",
        "<p>&nbsp;</p>",
        "<p>If a player places his/her last marble, he/she has lost the <a href=\"Games.htm\">game</a>. This is true, except when this last marble ",
        "enables the player to remove one or two marbles. The <a href=\"Games.htm\">game</a> does not allow the player to remove these marbles,",
        "but states the victory of the other player.</p>"
      }
    }
  );
  m.push_back(
    { "GameReversi",
      {
        "<p><img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>I first programmed Reversi around the age of eighteen in QBasic. At the 24th of September 2007 in three hours time, I've programmed it in C++. Most of it is in STL, except for the graphical user interface, so it will be easily ported to any other graphics library.</p>",
        "<p>&nbsp;</p>",
        "<p>On the 30th March of 2008, I got an assignment to program a console version of Reversi. It can be found at my <a href=\"GameReversiConsole.htm\">Reversi Console</a> page. It made me improve the Reversi class also used in this version.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameReversi.htm\">Reversi</a> is programmed in <a href=\"Cpp.htm\">C++</a> using the IDE <a href=\"CppBuilder.htm\">C++ Builder</a> 6.0. It uses the <a href=\"CppVcl.htm\">VCL</a> and <a href=\"CppBoost.htm\">Boost</a> libraries.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"GameReversi_1_0.png\">View a screenshot of 'Reversi' (png)(version 1.0)</a></li>",
        "  <li><a href=\"GameReversiExe_1_0.zip\">Download the 'Reversi' Windows executable (zip)(version 1.0)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameReversiConsole",
      {
        "<p><img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>On the 30th March of 2008 I got an assignment to make a Console version of Reversi. Using and improving the same Reversi class as in my <a href=\"GameReversi.htm\">Reversi game with GUI of 2007</a> and using some of my <a href=\"CppCodeSnippets.htm\">code snippets</a> I finished the assignment in 64 minutes. View the source code to see what is possible in 64 minutes.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameReversiConsole.htm\">Reversi Console</a> is programmed in <a href=\"Cpp.htm\">C++</a> using the IDE <a href=\"CppBuilder.htm\">C++ Builder</a> 6.0. It uses the <a href=\"CppBoost.htm\">Boost</a> libraries.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"GameReversiConsole_1_0.png\">View a screenshot of 'Reversi Console' (version 1.0)(png)</a></li>",
        "  <li><a href=\"GameReversiConsoleExe_1_0.zip\">Download the 'Reversi Console' Windows executable (version 1.0)(zip)</a></li>",
        "  <li><a href=\"GameReversiConsoleSource_1_0.zip\">Download the 'Reversi Console' source code (version 1.0)(zip)</a></li>",
        "  <li><a href=\"GameReversiConsoleSource_1_0.htm\">View the C++ Builder source code of 'Reversi Console' as a web page (version 1.0)(htm)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameRubiksClock",
      {
        "<p><a href=\"GameRubiksClock.htm\">Rubik's Clock</a> is a Rubik's Clock <a href=\"Games.htm\">game</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"GameRubiksClockDesktop_2_2.png\">View a screenshot of 'Rubik's Clock' (version 2.2)(png)</a></li>",
        "  <li><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"GameRubiksClock_2_1.png\">View a screenshot of 'Rubik's Clock' (version 2.1)(png)</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"GameRubiksClockDesktopExe_2_2.zip\">Download a Windows executable of 'Rubik's Clock' (version 2.2)(zip)</a></li>",
        "  <li>Older: <a href=\"GameRubiksClockVcl.htm\">Rubik's Clock (VCL)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameRubiksClockVcl",
      {
        "<p><img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameRubiksClockVcl.htm\">Rubik's Clock (VCL)</a> is a Rubik's Clock <a href=\"Games.htm\">game</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>Newer: <a href=\"GameRubiksClock.htm\">Rubik's Clock</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"GameRubiksClock_1_0.png\">View a screenshot of 'Rubik's Clock' (version 1.0)(png)</a></li>",
        "  <li><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"GameRubiksClockExe_1_0.zip\">Download a Windows executable of 'Rubik's Clock' (version 1.0)(zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameSearchAndDestroyChess",
      {
        "<p><a href=\"GameSearchAndDestroyChess.htm\">SearchAndDestroyChess</a> is a variant on chess, also called <a href=\"http://en.wikipedia.org/wiki/Kriegspiel_(chess)\">Kriegspiel</a> or <a href=\"http://en.wikipedia.org/wiki/Dark_chess\">Dark Chess</a>. In <a href=\"GameSearchAndDestroyChess.htm\">SearchAndDestroyChess</a> you can only view that part of the board that is 'seen' by your pieces.</p>",
        "<p>&nbsp;</p>",
        "<p>There is also a console/MS-DOS version of <a href=\"GameSearchAndDestroyChess.htm\">SearchAndDestroyChess</a> called <a href=\"GameSearchAndDestroyChessConsole.htm\">SearchAndDestroyChessConsole</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>The following special rules apply to <a href=\"GameSearchAndDestroyChess.htm\">SearchAndDestroyChess</a>:</p>",
        "<ul>",
        "  <li>a player cannot be in chess, nor in checkmate. Instead, if the king is captured, the capturer wins. This is because it is possible for a king to be in check without knowing it</li>",
        "  <li>Normal rules to en passant capture apply. But when a pawn can be captured en passant, this pawn is visible. This makes a pawn look sideways for only one turn. This is because the attacker must be able to see that he/she can make an en passant capture</li>",
        "  <li>Normal rules to castling apply, except that castling can take place when in chess and through attacked squares. This is because it is possible for a king to be or getting in check without knowing it</li>",
        "  <li>a pawn always gets promoted to a queen</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameSearchAndDestroyChess.htm\">SearchAndDestroyChess</a> is programmed in <a href=\"Cpp.htm\">C++</a> using the IDE <a href=\"CppBuilder.htm\">C++ Builder</a> 6.0. It uses the <a href=\"CppStl.htm\">STL</a>, <a href=\"CppVcl.htm\">VCL</a> and <a href=\"CppBoost.htm\">Boost</a> libraries.</p>",
        "<p>&nbsp;</p>",
        "<p>One month after putting <a href=\"GameSearchAndDestroyChess.htm\">SearchAndDestroyChess</a> online, I found out I wasn't the first to have invented this variant :-(.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>Older: <a href=\"GameSearchAndDestroyChessVcl.htm\">SearchAndDestroyChess (VCL)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>External links</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"http://en.wikipedia.org/wiki/Kriegspiel_(chess)\">Wikipedia's page about Kriegspiel</a></li>",
        "  <li><a href=\"http://en.wikipedia.org/wiki/Dark_chess\">Wikipedia's page about Dark Chess</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameSearchAndDestroyChessConsole",
      {
        "<p><a href=\"GameSearchAndDestroyChess.htm\">SearchAndDestroyChessConsole</a> is a special kind of chess <a href=\"Games.htm\">game</a>. The difference with a regular chess <a href=\"Games.htm\">game</a> is, that is <a href=\"GameSearchAndDestroyChess.htm\">SearchAndDestroyChessConsole</a> you can only view that part of the board that is 'seen' by your pieces.</p>",
        "<p>&nbsp;</p>",
        "<p>There is also a graphical/Windows version of <a href=\"GameSearchAndDestroyChessConsole.htm\">SearchAndDestroyChessConsole</a> called <a href=\"GameSearchAndDestroyChess.htm\">SearchAndDestroyChess</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>The following special rules apply to <a href=\"GameSearchAndDestroyChessConsole.htm\">SearchAndDestroyChessConsole</a>:</p>",
        "<ul>",
        "  <li>a player cannot be in chess, nor in checkmate. Instead, if the king is captured, the capturer wins. This is because it is possible for a king to be in check without knowing it</li>",
        "  <li>Normal rules to en passant capture apply. But when a pawn can be captured en passant, this pawn is visible. This makes a pawn look sideways for only one turn. This is because the attacker must be able to see that he/she can make an en passant capture</li>",
        "  <li>Normal rules to castling apply, except that castling can take place when in chess and through attacked squares. This is because it is possible for a king to be or getting in check without knowing it</li>",
        "  <li>a pawn always gets promoted to a queen</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>The notation rules in <a href=\"GameSearchAndDestroyChessConsole.htm\">SearchAndDestroyChessConsole</a> follow the regular algebraic notation, except for the following:</p>",
        "<ul>",
        "  <li>The piece's type must be written in capital. For example: 'Nb1 c3', instead of 'nb1 c3'</li>",
        "  <li>You must always specify where is piece comes from, so instead of 'e4' you must write 'e2 e4'</li>",
        "  <li>You must correctly write whether a move is a capture or not: 'Nb1 c3' when it is no capture, 'Nb1xc3' when it is a capture</li>",
        "  <li>Because a pawn is always promoted to a queen, you only need to write the pawn move. For example: 'e7 e8'</li>",
        "  <li>For castling use the standard '0-0-0' or '0-0' notation, instead of the incorrect 'Ke1 g1'</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameSearchAndDestroyChessConsole.htm\">SearchAndDestroyChessConsole</a> is programmed in <a href=\"Cpp.htm\">C++</a> using the IDE <a href=\"CppBuilder.htm\">C++ Builder</a> 6.0. It uses the <a href=\"CppStl.htm\">STL</a> and <a href=\"CppBoost.htm\">Boost</a> libraries.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"GameSearchAndDestroyChessConsole_1_0.png\">View a screenshot of 'SearchAndDestroyChessConsole' (version 1.0)(png)</a></li>",
        "  <li><a href=\"GameSearchAndDestroyChessConsoleExe_1_0.zip\">Download the 'SearchAndDestroyChessConsole' Windows executable (version 1.0)(zip)</a></li>",
        "  <li><a href=\"GameSearchAndDestroyChessConsoleSource_1_0.zip\">Download the 'SearchAndDestroyChessConsole' source code (version 1.0)(zip)</a></li>",
        "  <li><a href=\"GameSearchAndDestroyChessConsoleSource_1_0.htm\">View the C++ Builder source code of 'SearchAndDestroyChessConsole' as a web page (version 1.0)(htm)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameSearchAndDestroyChessVcl",
      {
        "<p><img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameSearchAndDestroyChessVcl.htm\">SearchAndDestroyChess (VCL)</a> is a variant on chess, also called <a href=\"http://en.wikipedia.org/wiki/Kriegspiel_(chess)\">Kriegspiel</a> or <a href=\"http://en.wikipedia.org/wiki/Dark_chess\">Dark Chess</a>. In <a href=\"GameSearchAndDestroyChess.htm\">SearchAndDestroyChess</a> you can only view that part of the board that is 'seen' by your pieces.</p>",
        "<p>&nbsp;</p>",
        "<p>There is also a console/MS-DOS version of <a href=\"GameSearchAndDestroyChess.htm\">SearchAndDestroyChess</a> called <a href=\"GameSearchAndDestroyChessConsole.htm\">SearchAndDestroyChessConsole</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>The following special rules apply to <a href=\"GameSearchAndDestroyChess.htm\">SearchAndDestroyChess</a>:</p>",
        "<ul>",
        "  <li>a player cannot be in chess, nor in checkmate. Instead, if the king is captured, the capturer wins. This is because it is possible for a king to be in check without knowing it</li>",
        "  <li>Normal rules to en passant capture apply. But when a pawn can be captured en passant, this pawn is visible. This makes a pawn look sideways for only one turn. This is because the attacker must be able to see that he/she can make an en passant capture</li>",
        "  <li>Normal rules to castling apply, except that castling can take place when in chess and through attacked squares. This is because it is possible for a king to be or getting in check without knowing it</li>",
        "  <li>a pawn always gets promoted to a queen</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameSearchAndDestroyChessVcl.htm\">SearchAndDestroyChess (VCL)</a> is programmed in <a href=\"Cpp.htm\">C++</a> using the IDE <a href=\"CppBuilder.htm\">C++ Builder</a> 6.0. It uses the <a href=\"CppStl.htm\">STL</a>, <a href=\"CppVcl.htm\">VCL</a> and <a href=\"CppBoost.htm\">Boost</a> libraries.</p>",
        "<p>&nbsp;</p>",
        "<p>One month after putting <a href=\"GameSearchAndDestroyChess.htm\">SearchAndDestroyChess</a> online, I found out I wasn't the first to have invented this variant :-(.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>Newer: <a href=\"GameSearchAndDestroyChess.htm\">SearchAndDestroyChess</a></li>",
        "  <li><a href=\"GameSearchAndDestroyChess_2_0.png\">View a screenshot of 'SearchAndDestroyChess' (version 2.0)(png)</a></li>",
        "  <li><a href=\"http://youtube.com/watch?v=p4GdAncNEvk\">View a YouTube video about the progress of 'SearchAndDestroyChess version 2.0'</a></li>",
        "  <li><a href=\"http://youtube.com/watch?v=MaemR0pKyJQ\">View a YouTube video about 'SearchAndDestroyChess' (version 1.0)</a></li>",
        "  <li><a href=\"GameSearchAndDestroyChessExe_2_0.zip\">Download the 'SearchAndDestroyChess' Windows executable (version 2.0)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"GameSearchAndDestroyChess_1_0.png\">View a screenshot of 'SearchAndDestroyChess' (version 1.0)(png)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>External links</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"http://en.wikipedia.org/wiki/Kriegspiel_(chess)\">Wikipedia's page about Kriegspiel</a></li>",
        "  <li><a href=\"http://en.wikipedia.org/wiki/Dark_chess\">Wikipedia's page about Dark Chess</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameSimPredator",
      {
        "<p><img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameSimPredator.htm\">SimPredator</a> was programmed on some evenings from the 19th of May 2006 to the 18th off July 2006 for Dr. L.P.W.G.M. van de Zande for a practical for freshmen at the university.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameSimPredator.htm\">SimPredator</a> is programmed in <a href=\"Cpp.htm\">C++</a> using the IDE <a href=\"CppBuilder.htm\">C++ Builder</a> 6.0. It uses the <a href=\"CppVcl.htm\">VCL</a> and <a href=\"CppBoost.htm\">Boost</a> libraries.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"GameSimPredatorMenu_1_0.png\">View a screenshot of the menu of 'SimPredator' (version 1.0)(png)</a></li>",
        "  <li><a href=\"GameSimPredator_1_0.png\">View a screenshot of the game of 'SimPredator' (version 1.0)(png)</a></li>",
        "  <li><a href=\"GameSimPredatorExe_1_0.zip\">Download the 'SimPredator' Windows executable (version 1.0)(zip)</a></li>",
        "  <li><a href=\"GameSimPredatorSource_1_0.zip\">Download the 'SimPredator' source code (version 1.0)(zip)</a></li>",
        "  <li><a href=\"GameSimPredatorSource_1_0.htm\">View the C++ Builder source code of 'SimPredator' as a web page (version 1.0)(htm)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameSpaceHarry",
      {
        "<p><img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameSpaceHarry.htm\">Space Harry</a> is a simple 'Space Harrier' clone.</p>",
        "<p>&nbsp;</p>",
        "<p>Harry was one of my favorite bartenders in one of my favorite (now closed) pubs.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>...</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Game Controls</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>Arrows: move Harry</li>",
        "  <li>Space: fire</li>",
        "  <li>F1: toggle transparency mode</li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "GameSpaceHarryVcl",
      {
        "<p><img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameSpaceHarryVcl.htm\">Space Harry (VCL)</a> is a simple 'Space Harrier' clone.</p>",
        "<p>&nbsp;</p>",
        "<p>Harry was one of my favorite bartenders in one of my favorite (now closed) pubs.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"GameSpaceHarry_1_0.png\">View a screenshot of 'Space Harry' (version 1.0)(png)</a></li>",
        "  <li><a href=\"GameSpaceHarryMenu_1_0.png\">View a screenshot of the menu of 'Space Harry' (version 1.0)(png)</a></li>",
        "  <li><a href=\"GameSpaceHarryGameOver_1_0.png\">View a screenshot of the 'Space Harry' game over screen (version 1.0)(png)</a></li>",
        "  <li><a href=\"GameSpaceHarryExe_1_0.zip\">Download a Windows executable of 'Space Harry' (version 1.0)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Game Controls</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>Arrows: move Harry</li>",
        "  <li>Space: fire</li>",
        "  <li>F1: toggle transparency mode</li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "GameSuperNsanaBros",
      {
        "<p>",
        "  <a href=\"GameSuperNsanaBros.htm\">SuperNsanaBros</a> is a <a href=\"Games.htm\">game</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "GameTankBattalion",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"GameTankBattalion.htm\">Tank Battalion</a> is an unfinished <a href=\"Games.htm\">game</a>",
        "  that is a PC clone of the MSX <a href=\"Games.htm\">game</a> 'Tank Battalion'.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "GameTicTacToe",
      {
        "<p><a href=\"GameTicTacToe.htm\">TicTacToe</a> is a simple tic-tac-toe <a href=\"Games.htm\">game</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"GameTicTacToe_1_4.png\">View a screenshot of 'TicTacToe' (version 1.4)(png)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"GameTicTacToe_1_1.png\">View a screenshot of 'TicTacToe' (version 1.1)(png)</a></li>",
        "  <li><img src=\"PicConsole.png\" alt=\"Console\"/> <a href=\"GameTicTacToe_1_6.png\">View a screenshot of 'TicTacToe' (version 1.6)(png)</a></li>",
        "  <li><a href=\"GameTicTacToeArchitecture_1_5.png\">View the 'TicTacToe' class architecture (version 1.5)(png)</a></li>",
        "  <li><a href=\"GameTicTacToeArchitecture_1_5.dia\">View the 'TicTacToe' class architecture (version 1.5)(dia)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"GameTicTacToeDesktopExeWindows_1_4.zip\">Download the Windows executable of 'TicTacToe' (version 1.4)(zip)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"GameTicTacToeSource_1_5.zip\">Download the Qt Creator source code of 'TicTacToe' (version 1.5)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>The <a href=\"CppWindows.htm\">Windows</a> executable of version 1.4 is created following ",
        "<a href=\"CppQtCrosscompileToWindowsExample15.htm\">how to cross-compile a Qt Creator project from Ubuntu to a windows executable: example 15: MinGW cross-compiling environment</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"GameTicTacToeArchitecture_1_4.png\">View the 'TicTacToe' class architecture (version 1.4)(png)</a></li>",
        "  <li><a href=\"GameTicTacToeArchitecture_1_4.dia\">View the 'TicTacToe' class architecture (version 1.4)(dia)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"GameTicTacToeSource_1_4.zip\">Download the Qt Creator source code of 'TicTacToe' (version 1.4)(zip)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"GameTicTacToeSource_1_3.zip\">Download the Qt Creator source code of 'TicTacToe' (version 1.3)(zip)</a></li>",
        "  <li><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"GameTicTacToe_1_2.png\">View a screenshot of 'TicTacToe' (web application)(version 1.2)(png)</a></li>",
        "  <li><a href=\"GameTicTacToeSource_1_2.zip\">Download the Qt Creator source code of 'TicTacToe' (version 1.2)(zip)</a></li>",
        "  <li><a href=\"GameTicTacToeSource_1_1.zip\">Download the Qt Creator source code of 'TicTacToe' (version 1.1)(zip)</a></li>",
        "  <li><a href=\"GameTicTacToe_1_0.png\">View a screenshot of 'TicTacToe' (version 1.0)(png)</a></li>",
        "  <li><a href=\"GameTicTacToeMenu_1_0.png\">View a screenshot of the menu of 'TicTacToe' (version 1.0)(png)</a></li>",
        "  <li><a href=\"GameTicTacToeSource_1_0.zip\">Download the Qt Creator source code of 'TicTacToe' (version 1.0)(zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameTronCollection",
      {
        "<p>'Tron' was one of my first cool QBASIC <a href=\"Games.htm\">games</a> I've had programmed around 1995. It took twelve years of itching before I ported it to C++.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameTronCollection.htm\">The Tron Collection</a> consists out of three parts:</p>",
        "<ul>",
        "  <li>Classic Tron</li>",
        "  <li>Super Tron</li>",
        "  <li>Ultimate Tron</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>Until now, I've only finished 'Classic Tron' and it can be viewed and downloaded. <a href=\"GameTronCollection.htm\">The Tron Collection</a> is currently at version 0.9.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>Older: <a href=\"GameTronCollectionVcl.htm\">The Tron Collection (VCL)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameTronCollectionVcl",
      {
        "<p><img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>'Tron' was one of my first cool QBASIC <a href=\"Games.htm\">games</a> I've had programmed around 1995. It took twelve years of itching before I ported it to C++.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameTronCollection.htm\">The Tron Collection</a> consists out of three parts:</p>",
        "<ul>",
        "  <li>Classic Tron</li>",
        "  <li>Super Tron</li>",
        "  <li>Ultimate Tron</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>Until now, I've only finished 'Classic Tron' and it can be viewed and downloaded. <a href=\"GameTronCollection.htm\">The Tron Collection</a> is currently at version 0.9.</p>",
        "<p>&nbsp;</p>",
        "<p>Version 0.9 of <a href=\"GameTronCollection.htm\">The Tron Collection</a> is programmed in <a href=\"Cpp.htm\">C++</a> using the IDE <a href=\"CppBuilder.htm\">C++ Builder</a> 6.0. It uses the <a href=\"CppVcl.htm\">VCL</a> and <a href=\"CppBoost.htm\">Boost</a> <a href=\"CppLibrary.htm\">libraries</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>Newer: <a href=\"GameTronCollection.htm\">The Tron Collection</a></li>",
        "  <li><a href=\"GameTronCollectionClassicTron_0_9.png\">View a screenshot of 'Classic Tron' (version 0.9)</a></li>",
        "  <li><a href=\"GameTronCollectionSuperTron_0_9.png\">View a screenshot of 'Classic Tron' (version 0.9)</a></li>",
        "  <li><a href=\"GameTronCollectionClassicTronMenu_0_9.png\">View a screenshot of the menu of 'Classic Tron' (version 0.9)</a></li>",
        "  <li><a href=\"GameTronCollectionClassicTronExe_0_9.zip\">Download a Windows executable of 'Classic Tron' (version 0.9)(zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "GameWizardBattle",
      {
        "<p><img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameWizardBattle.htm\">Wizard Battle</a> is the first <a href=\"Games.htm\">game</a> made by Joost van den Bogaart, released under the GPL 3.0.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"GameWizardBattle.htm\">Wizard Battle</a> is programmed in <a href=\"Cpp.htm\">C++</a> using the IDE <a href=\"CppBuilder.htm\">C++ Builder</a> 6.0. It uses the <a href=\"CppVcl.htm\">VCL</a> and <a href=\"CppBoost.htm\">Boost</a> libraries.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"GameWizardBattle_1_0.png\">View a screenshot of 'Wizard Battle' (version 1.0)(png)</a></li>",
        "  <li><a href=\"GameWizardBattleExe_1_0.zip\">Download the 'Wizard Battle' Windows executable (version 1.0)(zip)</a></li>",
        "  <li><a href=\"GameWizardBattleSource_1_0.zip\">Download the 'Wizard Battle' source code (version 1.0)(zip)</a></li>",
        "  <li><a href=\"GameWizardBattleResources_1_0.zip\">Download the 'Wizard Battle' resources (version 1.0)(zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "GameXeNonZero",
      {
        "<p><img src=\"PicQt.png\" alt=\"Qt\"/><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"GameXeNonZero.htm\">XeNonZero</a> is an unfinished <a href=\"Games.htm\">game</a>",
        "  similar to Xenon 2, but then console based.",
        "</p>",
      }
    }
  );
  m.push_back(
    { "GameZork",
      {
        "<p><a href=\"GameZork.htm\">Zork</a> (also named as 'Dungeon') is a text adventure <a href=\"Games.htm\">game</a> written by ",
        "Tim Anderson, Marc Blank, Bruce Daniels, and Dave Lebling in 1980.",
        "I ported its C source code (without any modification) to be used under <a href=\"CppQtCreator.htm\">Qt Creator</a>. ",
        "Note that because the C standard has changed considerably and because I left the original code unmodified, ",
        "compiling will yield a lot of compile warnings (*).</p>",
        "<p>&nbsp;</p>",
        "<p>To start the program under <a href=\"CppLinux.htm\">linux</a>, libncurses5-dev might needs to be installed (*):</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"Commands to install Zork prerequisites\" border = \"1\"><tr><td><code>",
        "sudo apt-get install libncurses5-dev<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>(*) Thanks to Fatdroid for asking me to mention this</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"GameZork.png\">View a screenshot of 'Zork' (version 1.0)(png)</a></li>",
        "  <li><a href=\"GameZorkSource_1_0.zip\">Download the 'Zork' source code (version 1.0)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Compiling under OpenSUSE 12.1</h2>",
        "<p>&nbsp;</p>",
        "<p>John Lange agreed to share his experience compiling zork under OpenSUSE 12.1:</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"How to compile Zork under OpenSUSE 12.1\" border = \"1\"><tr><td><code>",
        "[...] and also let you know that I was quite easily<br/>",
        "able to <a href=\"CppCompile.htm\">compile</a> it under OpenSUSE 12.1 with only a few minor tweaks.<br/>",
        "<br/>",
        "The first problem is that the file names in the <a href=\"CppMakefile.htm\">makefile</a> are<br/>",
        "lowercase, but the files are all uppercase which was easily solved by<br/>",
        "renaming all the files to lower-case.<br/>",
        "<br/>",
        "Second problem is the termcap path. Under SUSE I had to set it to:<br/>",
        "<br/>",
        "LIBS <a href=\"CppOperatorAssign.htm\">=</a> <a href=\"CppOperatorDivide.htm\">/</a>usr/lib64/termcap/libtermcap.a<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"How to compile Zork under OpenSUSE 12.1\" border = \"1\"><tr><td><code>",
        "One last thing, in <a href=\"CppLinux.htm\">Linux</a> there is a \"file end\" <a href=\"CppChar.htm\">character</a> (shows as ^Z)<br/>",
        "on the very last line of the <a href=\"CppMakefile.htm\">makefile</a> that also needs to be removed or<br/>",
        "\"<a href=\"CppMake.htm\">make</a>\" generates an error <a href=\"CppAbout.htm\">about</a> a syntax error.<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>Thanks, John!</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>External links</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"http://en.wikipedia.org/wiki/Zork\">Wikipedia page about Zork</a></li>",
        "  <li><a href=\"http://www.infocom-if.org/games/zork1/zork1.html\">Infocom page about Zork</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"CppLicence.htm\">Licence</a></h2>",
        "<p>&nbsp;</p>",
        "<p>Zork's copyright is held by <a href=\"http://www.activision.com\">Activision</a>.</p>"
      }
    }
  );

  m.push_back(
    { "ToolOpenFoamExample1",
      {
        "<p>",
        "  <a href=\"ToolOpenFoamExample1.htm\">OpenFOAM example1</a> is an ",
        "  <a href=\"ToolOpenFoam.htm\">OpenFOAM</a> example that demonstrates",
        "  the minimum requirements to create a (uniform) mesh of a cube using the tool blockMesh.exe",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  blockMesh needs two files: constant/PolyMesh/blockMeshDict and system/controlDict",
        "  (no idea where it needs the second file for).",
        "  The file case.foam is an empty file, needed by ParaView to accept this folder.",
        "  See the files for comments",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  After calling blockMesh.exe, the files 'boundary', 'faces', 'neighbour', 'owner' and 'points'",
        "  are created, in the folder 'constants/polyMesh'. ParaView can be be used to open 'case.foam' and"
        "  display the resulting mesh. Click on 'Properties | Apply' on the left, to view the mesh."
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolOpenFoamExample1.zip\">Download all files of OpenFOAM example 1 (zip)</a></li>",
        "  <li><a href=\"ToolOpenFoamExample1.txt\">View the output given by blockMesh.exe (txt)</a></li>",
        "  <li><a href=\"ToolOpenFoamExample1.png\">View the resulting mesh as displayed by ParaView (png)</a></li>",
        "</ul>"
      }
    }
  );





  m.push_back(
    { "ToolOpenFoamExample5",
      {
        "<p>",
        "  <a href=\"ToolOpenFoamExample5.htm\">OpenFOAM example 5</a> is an ",
        "  <a href=\"ToolOpenFoam.htm\">OpenFOAM</a> example that tries to do the same",
        "  as OpenFOAM's first tutorial, under Windows",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  After running ToolOpenFoamExample5.bat, it can be be observed that no pressure",
        "  gradient is created. <a href=\"ToolOpenFoamExample6.htm\">OpenFOAM example 6</a>"
        "  tries to get the same result as the OpenFOAM tutorial."
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolOpenFoamExample5.zip\">Download all input files of OpenFOAM example 1 (zip)</a></li>",
        "  <li><a href=\"ToolOpenFoamExample5.txt\">View the output given by ToolOpenFoamExample5.bat (txt)</a></li>",
        "  <li><a href=\"ToolOpenFoamExample5.png\">View the result as displayed by ParaView (png)</a></li>",
        "</ul>"
      }
    }
  );


  m.push_back(
    { "ProjectBochum",
      {
        "<p><a href=\"ProjectBochum.htm\">The Bochum Project</a> was my second student project. It took place at the <a href=\"http://www.neuroinformatik.ruhr-uni-bochum.de/top.html\">Institut fuer Neuroinformatik</a> at the <a href=\"http://www.ruhr-uni-bochum.de/\">Ruhr Universitaet Bochum</a> in Germany.</p>",
        "<p>&nbsp;</p>",
        "<p>The goal of <a href=\"ProjectBochum.htm\">The Bochum Project</a> was to investigate the use of Gabor filtering and neural networks in autonomous navigation by robots.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectBochum.htm\">The Bochum Project</a> has been developed by (sorted alphabetically on first name):</p>",
        "<ul>",
        "  <li><a href=\"http://www.neuroinformatik.ruhr-uni-bochum.de/thbio/members/profil/Faubel/index.html\">Christian Faubel</a>: computer network manager and programming advice</li>",
        "  <li><a href=\"http://image.diku.dk/igel\">Christian Igel</a>: supervisor</li>",
        "  <li><a href=\"http://www.iossifidis.net\">Ioannis Iossifidis</a>: supervisor</li>",
        "  <li><a href=\"http://www.richelbilderbeek.nl/\">Richel Bilderbeek</a>: programming</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectBochum.htm\">The Bochum Project</a> lasted from about the first of October of 2004 to about the first of April of 2005</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ProjectBochumReport.pdf\">Download the 'The Bochum Project' report (pdf)</a></li>",
        "  <li><a href=\"ProjectBochumTitleImage.png\">View the 'The Bochum Project' report title image (png)</a></li>",
        "  <li><a href=\"ProjectBochumExperimentalSetup.png\">View the 'The Bochum Project' experimental setup (png)</a></li>",
        "  <li><a href=\"ProjectBochumGaborFiltersTestResultsMatrixMultiplication.png\">View the 'The Bochum Project' test results from matrix multiplication (png)</a></li>",
        "  <li><a href=\"ProjectBochumGaborFiltersTestResultsOpenCV.png\">View the 'The Bochum Project' test results from OpenCV (png)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ProjectBrainweaver",
      {
        "<p><a href=\"ProjectBrainweaver.htm\">Brainweaver</a> (formerly: <a href=\"ProjectVanDenBogaart.htm\">Project Van Den Bogaart</a>) is an open source concept mapping program with two additions:</p>",
        "<ol>",
        "  <li>the program not only supports the drawing of concept maps but (prior to this) also the gathering and sorting of concepts and examples</li>",
        "  <li>",
        "    the program enables the assessment of concept maps maps: the program calculates several parameters connected to ",
        "    concept maps, partly based on the human evaluation of these maps",
        "  </li>",
        "</ol>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/> <a href=\"ProjectBrainweaver_0_33.png\">View a screenshot of 'Brainweaver' (version 0.33)(png)</a></li>",
        "  <li><img src=\"PicWine.png\" alt=\"Wine\"/> <a href=\"ProjectBrainweaver_0_28Wine.png\">View a screenshot of 'Brainweaver' (version 0.28)(png)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/> <a href=\"ProjectBrainweaverExe_0_43.zip\">Download the 'Brainweaver' windows executable (version 0.43)(zip)</a></li>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/> <a href=\"ProjectBrainweaver20130725.mp4\">View Brainweaver being tested by libcvautomation (mp4)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/> <a href=\"ProjectBrainweaver_0_28.png\">View a screenshot of 'Brainweaver' (version 0.28)(png)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ProjectBristol",
      {
        "<p><a href=\"ProjectBristol.htm\">The Bristol Project</a> was my third student project. It took place at the <a href=\"http://www.bristol.ac.uk/biology/\">School of Biological Sciences</a> at the <a href=\"http://www.bristol.ac.uk/\">University of Bristol</a> in the UK.</p>",
        "<p>&nbsp;</p>",
        "<p>The goal of <a href=\"ProjectBristol.htm\">The Bristol Project</a> was to investigate the influence of phenotypic plasticity on population dynamics.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectBristol.htm\">The Bristol Project</a> has been developed by:</p>",
        "<ul>",
        "  <li><a href=\"http://seis.bris.ac.uk/~bzrjhp/index.html\">Robert JH Payne</a>: supervisor, expert knowledge</li>",
        "  <li><a href=\"http://www.richelbilderbeek.nl/\">Richel Bilderbeek</a>: student,programmer</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectBristol.htm\">The Bristol Project</a> lasted from about May 2005 to about the 12th of August of 2005.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ProjectBristolReport.pdf\">Download the 'The Bristol Project' report (pdf)</a></li>",
        "  <li><a href=\"ProjectBristolSource_1_0.zip\">Download the 'The Bristol Project' source code (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ProjectChrisWiley",
      {
        "<p><img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectChrisWiley.htm\">The Chris Wiley Project</a> is a simulation that investigates cross-species mating for different specie densities.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectChrisWiley.htm\">The Chris Wiley Project</a> has been developed for <a href=\"http://www.nbb.cornell.edu/shaw%20lab/wiley/wiley.html\">Chris Wiley</a>.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectChrisWiley.htm\">The Chris Wiley Project</a> has been developed by (sorted alphabetically on first name):</p>",
        "<ul>",
        "  <li><a href=\"http://www.nbb.cornell.edu/shaw%20lab/wiley/wiley.html\">Chris Wiley</a>: researcher</li>",
        "  <li><a href=\"http://www.richelbilderbeek.nl\">Richel Bilderbeek</a>: programming</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectChrisWiley.htm\">The Chris Wiley Project</a> was developed from about the 11th of November of 2005 to about the 14th of January of 2006.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ProjectChrisWiley_1_0.png\">View a screenshot of 'The Chris Wiley Project' (png)</a></li>",
        "  <li><a href=\"ProjectChrisWileyExe_1_0.zip\">Download the 'The Chris Wiley Project' Windows executable (zip)</a></li>",
        "  <li><a href=\"ProjectChrisWileySource_1_0.zip\">Download the 'The Chris Wiley Project' source code (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ProjectCrossPoll",
      {
        "<p><img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectCrossPoll.htm\">CrossPoll</a> is a simulation that investigates hybridization between two crop field.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectCrossPoll.htm\">CrossPoll</a> has been developed for the <a href=\"http://www.cogem.net/\">COGEM</a>.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectCrossPoll.htm\">CrossPoll</a> has been developed by (sorted alphabetically on first name):</p>",
        "<ul>",
        "  <li><a href=\"http://www.rug.nl/biologie/onderzoek/onderzoekgroepen/theoreticalbiology/peoplePages/franjoPage\">Franjo Weissing</a> (Head of <a href=\"http://www.rug.nl/biologie/onderzoek/onderzoekgroepen/theoreticalbiology/index\">the Theoretical Biology group</a>): expert advice</li>",
        "  <li><a href=\"http://www.rug.nl/biologie/onderzoek/onderzoekgroepen/evolutionarygenetics/people/kuke\">Kuke Bijlsma</a> (Head of the population and conservation genetics research programme of <a href=\"http://www.rug.nl/biologie/onderzoek/onderzoekgroepen/evolutionarygenetics/index\">the Evolutionary Genetics Group</a>): expert advice</li>",
        "  <li><a href=\"http://www.richelbilderbeek.nl\">Richel Bilderbeek</a>: programming</li>",
        "  <li><a href=\"http://www.rug.nl/biologie/onderzoek/onderzoekgroepen/evolutionarygenetics/people/cv/smithkleefsman\">Willemien Smith-Kleefsman</a> (PhD at <a href=\"http://www.rug.nl/biologie/onderzoek/onderzoekgroepen/evolutionarygenetics/index\">the Evolutionary Genetics Group</a>): literature</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>Because the licence of <a href=\"ProjectCrossPoll.htm\">CrossPoll</a> is in hands of the <a href=\"http://www.cogem.net/\">COGEM</a>, I cannot give the source code. Also have I been very selective in choosing the following screenshots:</p>",
        "<ul>",
        "  <li><a href=\"ProjectCrossPoll0.png\">View a screenshot of 'CrossPoll' #0 (PNG)</a></li>",
        "  <li><a href=\"ProjectCrossPoll1.png\">View a screenshot of 'CrossPoll' #1 (PNG)</a></li>",
        "  <li><a href=\"ProjectCrossPoll2.png\">View a screenshot of 'CrossPoll' #2 (PNG)</a></li>",
        "  <li><a href=\"ProjectCrossPoll3.png\">View a screenshot of 'CrossPoll' #3 (PNG)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectCrossPoll.htm\">CrossPoll</a> was developed from about the 5th of July of 2004 to about the 27th of December of 2004.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Project code info</h2>",
        "<p>&nbsp;</p>",
        "<p>Project code info generated using David A. Wheeler's 'SLOCCount'.</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"SLOCCount\" border = \"1\"><tr><td><code>",
        "Total Physical Source Lines of Code (SLOC)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;= 23,437<br/>",
        "Development Effort Estimate, Person-Years (Person-Months) = 5.49 (65.86)<br/>",
        " (Basic COCOMO model, Person-Months = 2.4 * (KSLOC**1.05))<br/>",
        "Schedule Estimate, Years (Months)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = 1.02 (12.27)<br/>",
        " (Basic COCOMO model, Months = 2.5 * (person-months**0.38))<br/>",
        "Estimated Average Number of Developers (Effort/Schedule)&nbsp;&nbsp;= 5.37<br/>",
        "Total Estimated Cost to Develop&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = $ 741,376<br/>",
        " (average salary = $56,286/year, overhead = 2.40).<br/>",
        "SLOCCount, Copyright (C) 2001-2004 David A. Wheeler<br/>",
        "SLOCCount is Open Source Software/Free Software, licensed under the GNU GPL.<br/>",
        "SLOCCount comes with ABSOLUTELY NO WARRANTY, and you are welcome to<br/>",
        "redistribute it under certain conditions as specified by the GNU GPL license;<br/>",
        "see the documentation for details.<br/>",
        "Please credit this data as \"generated using David A. Wheeler's 'SLOCCount'.\"<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->"
      }
    }
  );
  m.push_back(
    { "ProjectGtst",
      {
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Introduction</h2>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectGtst.htm\">GTST</a> ('Game Theory ServerT') is an open source program for performing game theory experiments. ",
        "When <a href=\"ProjectGtst.htm\">GTST</a>",
        "is started on a server, both administrators and participants can log in and do game theory experiments.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectGtst.htm\">GTST</a> has been developed by (sorted alphabetically on first name):</p>",
        "<ul>",
        "  <li><a href=\"http://www.rug.nl/biologie/onderzoek/onderzoekgroepen/theoreticalbiology/peoplePages/molleman\">Lucas Molleman</a>: researcher</li>",
        "  <li><a href=\"http://www.rug.nl/biologie/onderzoek/onderzoekgroepen/theoreticalbiology/peoplePages/vdBerg\">Piet van den Berg</a>: researcher</li>",
        "  <li><a href=\"http://www.richelbilderbeek.nl\">Richel Bilderbeek</a>: programming</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectGtst.htm\">GTST</a> started on the 9th of May 2011 and formally ended at the 27th of May 2011.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>The name GTST explained</h2>",
        "<p>&nbsp;</p>",
        "<p>The name GTST developed from the following steps:</p>",
        "<ul>",
        "  <li>The project is about game theorey and has 'ProjectGameTheory' as a working title, so a name with 'Game Theory' in it would be nice</li>",
        "  <li>The project is about setting up a server, so a name with 'Server' in it would be nice</li>",
        "  <li>A short name would be nice, so 'GTS' was a possibility</li>",
        "  <li>GTST is also an abbreviation of ",
        "    <a href=\"http://en.wikipedia.org/wiki/Goede_Tijden,_Slechte_Tijden\">Goede Tijden, Slechte Tijden</a>",
        "    ('Good Times, Bad Times), which is a Dutch soap series. In soap series, people often struggle with non-contributors.",
        "    Problem was: what would the 'T' mean?",
        "  </li>",
        "  <li>Appending a noun with a 'T' is a certain Dutch slang, resulting in 'Game Theory ServerT'</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ProjectGtst_1_2.png\">View a screenshot of GTST (version 1.2)(png)</a></li>",
        "  <li><a href=\"ProjectGtstSource_1_2.zip\">Download the GTST source code (version 1.2)(zip)</a></li>",
        "  <li><a href=\"ProjectGtstArchitectureMenuDialog.png\">View the GTST MenuDialog architecture (version 1.2)(png)</a></li>",
        "  <li><a href=\"ProjectGtstArchitectureMenuDialog.dia\">View the GTST MenuDialog architecture (version 1.2)(dia)</a></li>",
        "  <li><a href=\"ProjectGtstArchitectureServer.png\">View the GTST Server architecture (version 1.2)(png)</a></li>",
        "  <li><a href=\"ProjectGtstArchitectureServer.dia\">View the GTST Server architecture (version 1.2)(dia)</a></li>",
        "  <li><a href=\"ProjectGtstSloccount.txt\">View the GTST project details generated using David A. Wheeler's 'SLOCCount' (version 1.2)(txt)</a></li>",
        "  <li><a href=\"ProjectGtst.ppt\">Download a presentation given to the participants of the experiment (version 0.1)(ppt)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ProjectGtstSource_1_1.zip\">Download the GTST source code (version 1.1)(zip)</a></li>",
        "  <li><a href=\"ProjectGtstSource_1_0.zip\">Download the GTST source code (version 1.0)(zip)</a></li>",
        "  <li><a href=\"ProjectGtstSource_0_59.zip\">Download the GTST source code (version 0.58)(zip)</a></li>",
        "  <li><a href=\"ProjectGtstSource_0_58.zip\">Download the GTST source code (version 0.58)(zip)</a></li>",
        "  <li><a href=\"ProjectGtstSource_0_57.zip\">Download the GTST source code (version 0.57)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Similar software</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"http://www.iew.uzh.ch/ztree/index.php\">z-Tree</a>: closed source</li>",
        "<!--  <li><a href=\"http://en.wikipedia.org/wiki/Amazon_Mechanical_Turk\">Amazon Mechanical Turk</a>:</li> -->",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ProjectMuscaDomestica",
      {
        "<p><img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectMuscaDomestica.htm\">Project Musca Domestica</a> is a simulation that investigates the relationship between sexual determining systems for different dispersal scenarios.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectMuscaDomestica.htm\">Project Musca Domestica</a> has been developed in a course from the group of <a href=\"http://www.rug.nl/biologie/onderzoek/onderzoekgroepen/theoreticalbiology/index\">Theoretical Biology</a>.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectMuscaDomestica.htm\">Project Musca Domestica</a> has been developed by (sorted alphabetically on first name):</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"http://www.rug.nl/biologie/onderzoek/onderzoekgroepen/theoreticalbiology/peoplePages/idoPage?lang=en\">Ido Pen</a>: expert knowledge</li>",
        "  <li><a href=\"http://www.rug.nl/farmacie/onderzoek/basiseenheden/farmacokinetiekendrugdelivery/medewerkers/magdalena_kozielska?lang=en\">Magdalena Kozielska</a>: research</li>",
        "  <li>Marlies Westerhof: programming, testing</li>",
        "  <li><a href=\"http://www.richelbilderbeek.nl/\">Richel Bilderbeek</a>: programming, testing</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectMuscaDomestica.htm\">Project Musca Domestica</a> was developed from about the 2nd to the 18th of December of 2003.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ProjectMuscaDomestica_1_0.png\">View a screenshot of 'Project Musca Domestica' (png)</a></li>",
        "  <li><a href=\"ProjectMuscaDomesticaExe_1_0.zip\">Download the 'Project Musca Domestica' Windows executable (zip)</a></li>",
        "  <li><a href=\"ProjectMuscaDomesticaSource_1_0.zip\">Download the 'Project Musca Domestica' source code (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ProjectNewickVector",
      {
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Introduction</h2>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectNewickVector.htm\">Project NewickVector</a> is the successor <a href=\"Projects.htm\">Project</a> of ",
        "<a href=\"ProjectTwoDigitNewick.htm\">Project TwoDigitNewick</a>, with the goal of supporting Newicks of any arity.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectNewickVector.htm\">Project NewickVector</a> has been developed by (sorted alphabetically on first name):</p>",
        "<ul>",
        "  <li><a href=\"http://www.rug.nl/biologie/onderzoek/onderzoekgroepen/cocon/people/etienne/index\">Rampal Etienne</a>: researcher</li>",
        "  <li><a href=\"http://www.richelbilderbeek.nl/\">Richel Bilderbeek</a>: programming</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectNewickVector.htm\">Project NewickVector</a> started in February 2011.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Table of contents</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>Procedure</li>",
        "  <li>Same results for binary phylogenies</li>",
        "  <li>Validating results for phylogenies of any arity</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Procedure</h2>",
        "<p>&nbsp;</p>",
        "<p>The code of <a href=\"ProjectNewickVector.htm\">Project NewickVector</a> is compared to the previous projects in ",
        "result and speed.</p>",
        "<p>&nbsp;</p>",
        "<p>All measurements have been performed on the same computer. In all simulations, the value of parameter theta was set to 10.0.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Same results for binary phylogenies</h2>",
        "<p>&nbsp;</p>",
        "<p>In a previous projects, 162 different phylogenies, with complexities from 24 to 866052, were used ",
        "for comparison, valididating .</p>",
        "<p>&nbsp;</p>",
        "<p>These same phylogenies are used to test that ToolTwoDigitNewick (this project)",
        "calculates the same probabilities as ProjectRampal_EndVersion2.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ProjectNewickVectorResultsCompare.txt\">View these results as a text file (txt)</a></li>",
        "  <li><a href=\"ProjectNewickVectorResultsCompare.xls\">View these results (xls)</a></li>",
        "  <li><a href=\"ProjectNewickVectorResultsCompare.ods\">View these results (ods)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Validating results for phylogenies of any arity</h2>",
        "<p>&nbsp;</p>",
        "<p>The probabilities calculated for trinary phylogenies are validated from probabilities calculated for ",
        "validated binary phylogenies. The calculation is shown and generated by computer.</p>",
        "<p>&nbsp;</p>",
        "<p>Note that these phylogenies can be written down in different ways, for example '(1,(2,3))' is the",
        "same phylogeny as '((3,2),1)'. In the simulation at startup, all the results below are checked in",
        "all their possible notations.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h3>#1: (1,1,(1,1))</h3>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "N = the phylogeny = (1,1,(1,1))<br/>",
        "t = theta = 10<br/>",
        "p(N,t) = probability = SUM(c_i * p_i)<br/>",
        "c(N,t) = coefficient<br/>",
        "D(N,t) = denominator = 12<br/>",
        "N'1 = (2,(1,1))<br/>",
        "N'2 = (2,(1,1))<br/>",
        "N'3 = (1,1,2)<br/>",
        "N'4 = (1,1,2)<br/>",
        " <br/>",
        "For t = 10:<br/>",
        " <br/>",
        "p'1 = 0.019425019425019428 (calculated at once with NewickVector)<br/>",
        "p'2 = 0.019425019425019428 (calculated at once with NewickVector)<br/>",
        "p'3 = 0.058275058275058272 (calculated at once with NewickVector)<br/>",
        "p'4 = 0.058275058275058272 (calculated at once with NewickVector)<br/>",
        "c'1 = t / d = 10 / 12 = 0.83333333333333337 (as f equals 1)<br/>",
        "c'2 = t / d = 10 / 12 = 0.83333333333333337 (as f equals 1)<br/>",
        "c'3 = t / d = 10 / 12 = 0.83333333333333337 (as f equals 1)<br/>",
        "c'4 = t / d = 10 / 12 = 0.83333333333333337 (as f equals 1)<br/>",
        "p(N,t) = SUM(c_i * p_i)<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; =&nbsp;&nbsp; ( 0.83333333333333337 * 0.019425019425019428 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.83333333333333337 * 0.019425019425019428 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.83333333333333337 * 0.058275058275058272 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.83333333333333337 * 0.058275058275058272 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = 0.12950012950012951 (hand-calculated)<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = 0.12950012950012951 (calculated at once by NewickVector)<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h3>#2: (1,(1,1,1))</h3>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "N = the phylogeny = (1,(1,1,1))<br/>",
        "t = theta = 10<br/>",
        "p(N,t) = probability = SUM(c_i * p_i)<br/>",
        "c(N,t) = coefficient<br/>",
        "D(N,t) = denominator = 12<br/>",
        "N'1 = (1,(2,1))<br/>",
        "N'2 = (1,(1,2))<br/>",
        "N'3 = (1,(2,1))<br/>",
        "N'4 = (1,(1,2))<br/>",
        "N'5 = (1,(1,2))<br/>",
        "N'6 = (1,(2,1))<br/>",
        " <br/>",
        "For t = 10:<br/>",
        " <br/>",
        "p'1 = 0.019425019425019428 (calculated at once with NewickVector)<br/>",
        "p'2 = 0.019425019425019428 (calculated at once with NewickVector)<br/>",
        "p'3 = 0.019425019425019428 (calculated at once with NewickVector)<br/>",
        "p'4 = 0.019425019425019428 (calculated at once with NewickVector)<br/>",
        "p'5 = 0.019425019425019428 (calculated at once with NewickVector)<br/>",
        "p'6 = 0.019425019425019428 (calculated at once with NewickVector)<br/>",
        "c'1 = t / d = 10 / 12 = 0.83333333333333337 (as f equals 1)<br/>",
        "c'2 = t / d = 10 / 12 = 0.83333333333333337 (as f equals 1)<br/>",
        "c'3 = t / d = 10 / 12 = 0.83333333333333337 (as f equals 1)<br/>",
        "c'4 = t / d = 10 / 12 = 0.83333333333333337 (as f equals 1)<br/>",
        "c'5 = t / d = 10 / 12 = 0.83333333333333337 (as f equals 1)<br/>",
        "c'6 = t / d = 10 / 12 = 0.83333333333333337 (as f equals 1)<br/>",
        "p(N,t) = SUM(c_i * p_i)<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; =&nbsp;&nbsp; ( 0.83333333333333337 * 0.019425019425019428 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.83333333333333337 * 0.019425019425019428 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.83333333333333337 * 0.019425019425019428 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.83333333333333337 * 0.019425019425019428 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.83333333333333337 * 0.019425019425019428 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.83333333333333337 * 0.019425019425019428 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = 0.097125097125097148 (hand-calculated)<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = 0.097125097125097148 (calculated at once by NewickVector)<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h3>#3: (1,1,(1,2))</h3>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "N = the phylogeny = (1,1,(1,2))<br/>",
        "t = theta = 10<br/>",
        "p(N,t) = probability = SUM(c_i * p_i)<br/>",
        "c(N,t) = coefficient<br/>",
        "D(N,t) = denominator = 40<br/>",
        "N'1 = (2,(1,2))<br/>",
        "N'2 = (2,(1,2))<br/>",
        "N'3 = (1,1,3)<br/>",
        "N'4 = (1,1,(1,1))<br/>",
        " <br/>",
        "For t = 10:<br/>",
        " <br/>",
        "p'1 = 0.0014337514337514339 (calculated at once with NewickVector)<br/>",
        "p'2 = 0.0014337514337514339 (calculated at once with NewickVector)<br/>",
        "p'3 = 0.0083250083250083241 (calculated at once with NewickVector)<br/>",
        "p'4 = 0.12950012950012951 (calculated at once with NewickVector)<br/>",
        "c'1 = t / d = 10 / 40 = 0.25 (as f equals 1)<br/>",
        "c'2 = t / d = 10 / 40 = 0.25 (as f equals 1)<br/>",
        "c'3 = t / d = 10 / 40 = 0.25 (as f equals 1)<br/>",
        "c'4 = (f*(f-1)) / d = 2 / 40 = 0.050000000000000003 (as f equals 2)<br/>",
        "p(N,t) = SUM(c_i * p_i)<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; =&nbsp;&nbsp; ( 0.25 * 0.0014337514337514339 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.25 * 0.0014337514337514339 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.25 * 0.0083250083250083241 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.050000000000000003 * 0.12950012950012951 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = 0.0092731342731342745 (hand-calculated)<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = 0.0092731342731342745 (calculated at once by NewickVector)<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h3>#4: (1,1,(1,1,1))</h3>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "N = the phylogeny = (1,1,(1,1,1))<br/>",
        "t = theta = 10<br/>",
        "p(N,t) = probability = SUM(c_i * p_i)<br/>",
        "c(N,t) = coefficient<br/>",
        "D(N,t) = denominator = 20<br/>",
        "N'1 = (2,(1,1,1))<br/>",
        "N'2 = (2,(1,1,1))<br/>",
        "N'3 = (1,1,(2,1))<br/>",
        "N'4 = (1,1,(1,2))<br/>",
        "N'5 = (1,1,(2,1))<br/>",
        "N'6 = (1,1,(1,2))<br/>",
        "N'7 = (1,1,(1,2))<br/>",
        "N'8 = (1,1,(2,1))<br/>",
        " <br/>",
        "For t = 10:<br/>",
        " <br/>",
        "p'1 = 0.0070068820068820096 (calculated at once with NewickVector)<br/>",
        "p'2 = 0.0070068820068820096 (calculated at once with NewickVector)<br/>",
        "p'3 = 0.0092731342731342745 (calculated at once with NewickVector)<br/>",
        "p'4 = 0.0092731342731342745 (calculated at once with NewickVector)<br/>",
        "p'5 = 0.0092731342731342745 (calculated at once with NewickVector)<br/>",
        "p'6 = 0.0092731342731342745 (calculated at once with NewickVector)<br/>",
        "p'7 = 0.0092731342731342745 (calculated at once with NewickVector)<br/>",
        "p'8 = 0.0092731342731342745 (calculated at once with NewickVector)<br/>",
        "c'1 = t / d = 10 / 20 = 0.5 (as f equals 1)<br/>",
        "c'2 = t / d = 10 / 20 = 0.5 (as f equals 1)<br/>",
        "c'3 = t / d = 10 / 20 = 0.5 (as f equals 1)<br/>",
        "c'4 = t / d = 10 / 20 = 0.5 (as f equals 1)<br/>",
        "c'5 = t / d = 10 / 20 = 0.5 (as f equals 1)<br/>",
        "c'6 = t / d = 10 / 20 = 0.5 (as f equals 1)<br/>",
        "c'7 = t / d = 10 / 20 = 0.5 (as f equals 1)<br/>",
        "c'8 = t / d = 10 / 20 = 0.5 (as f equals 1)<br/>",
        "p(N,t) = SUM(c_i * p_i)<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; =&nbsp;&nbsp; ( 0.5 * 0.0070068820068820096 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.5 * 0.0070068820068820096 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.5 * 0.0092731342731342745 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.5 * 0.0092731342731342745 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.5 * 0.0092731342731342745 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.5 * 0.0092731342731342745 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.5 * 0.0092731342731342745 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.5 * 0.0092731342731342745 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = 0.034826284826284831 (hand-calculated)<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = 0.034826284826284831 (calculated at once by NewickVector)<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h3>#5: (2,(1,1,1))</h3>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "N = the phylogeny = (2,(1,1,1))<br/>",
        "t = theta = 10<br/>",
        "p(N,t) = probability = SUM(c_i * p_i)<br/>",
        "c(N,t) = coefficient<br/>",
        "D(N,t) = denominator = 40<br/>",
        "N'1 = (1,(1,1,1))<br/>",
        "N'2 = (2,(2,1))<br/>",
        "N'3 = (2,(1,2))<br/>",
        "N'4 = (2,(2,1))<br/>",
        "N'5 = (2,(1,2))<br/>",
        "N'6 = (2,(1,2))<br/>",
        "N'7 = (2,(2,1))<br/>",
        " <br/>",
        "For t = 10:<br/>",
        " <br/>",
        "p'1 = 0.097125097125097148 (calculated at once with NewickVector)<br/>",
        "p'2 = 0.0014337514337514339 (calculated at once with NewickVector)<br/>",
        "p'3 = 0.0014337514337514339 (calculated at once with NewickVector)<br/>",
        "p'4 = 0.0014337514337514339 (calculated at once with NewickVector)<br/>",
        "p'5 = 0.0014337514337514339 (calculated at once with NewickVector)<br/>",
        "p'6 = 0.0014337514337514339 (calculated at once with NewickVector)<br/>",
        "p'7 = 0.0014337514337514339 (calculated at once with NewickVector)<br/>",
        "c'1 = (f*(f-1)) / d = 2 / 40 = 0.050000000000000003 (as f equals 2)<br/>",
        "c'2 = t / d = 10 / 40 = 0.25 (as f equals 1)<br/>",
        "c'3 = t / d = 10 / 40 = 0.25 (as f equals 1)<br/>",
        "c'4 = t / d = 10 / 40 = 0.25 (as f equals 1)<br/>",
        "c'5 = t / d = 10 / 40 = 0.25 (as f equals 1)<br/>",
        "c'6 = t / d = 10 / 40 = 0.25 (as f equals 1)<br/>",
        "c'7 = t / d = 10 / 40 = 0.25 (as f equals 1)<br/>",
        "p(N,t) = SUM(c_i * p_i)<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; =&nbsp;&nbsp; ( 0.050000000000000003 * 0.097125097125097148 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.25 * 0.0014337514337514339 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.25 * 0.0014337514337514339 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.25 * 0.0014337514337514339 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.25 * 0.0014337514337514339 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.25 * 0.0014337514337514339 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.25 * 0.0014337514337514339 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = 0.0070068820068820096 (hand-calculated)<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = 0.0070068820068820096 (calculated at once by NewickVector)<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h3>6#: (1,1,1,(1,1))</h3>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "N = the phylogeny = (1,1,1,(1,1))<br/>",
        "t = theta = 10<br/>",
        "p(N,t) = probability = SUM(c_i * p_i)<br/>",
        "c(N,t) = coefficient<br/>",
        "D(N,t) = denominator = 20<br/>",
        "N'1 = (2,1,(1,1))<br/>",
        "N'2 = (1,2,(1,1))<br/>",
        "N'3 = (2,1,(1,1))<br/>",
        "N'4 = (1,2,(1,1))<br/>",
        "N'5 = (1,2,(1,1))<br/>",
        "N'6 = (2,1,(1,1))<br/>",
        "N'7 = (1,1,1,2)<br/>",
        "N'8 = (1,1,1,2)<br/>",
        " <br/>",
        "For t = 10:<br/>",
        " <br/>",
        "p'1 = 0.0092222592222592232 (calculated at once with NewickVector)<br/>",
        "p'2 = 0.0092222592222592232 (calculated at once with NewickVector)<br/>",
        "p'3 = 0.0092222592222592232 (calculated at once with NewickVector)<br/>",
        "p'4 = 0.0092222592222592232 (calculated at once with NewickVector)<br/>",
        "p'5 = 0.0092222592222592232 (calculated at once with NewickVector)<br/>",
        "p'6 = 0.0092222592222592232 (calculated at once with NewickVector)<br/>",
        "p'7 = 0.041625041625041624 (calculated at once with NewickVector)<br/>",
        "p'8 = 0.041625041625041624 (calculated at once with NewickVector)<br/>",
        "c'1 = t / d = 10 / 20 = 0.5 (as f equals 1)<br/>",
        "c'2 = t / d = 10 / 20 = 0.5 (as f equals 1)<br/>",
        "c'3 = t / d = 10 / 20 = 0.5 (as f equals 1)<br/>",
        "c'4 = t / d = 10 / 20 = 0.5 (as f equals 1)<br/>",
        "c'5 = t / d = 10 / 20 = 0.5 (as f equals 1)<br/>",
        "c'6 = t / d = 10 / 20 = 0.5 (as f equals 1)<br/>",
        "c'7 = t / d = 10 / 20 = 0.5 (as f equals 1)<br/>",
        "c'8 = t / d = 10 / 20 = 0.5 (as f equals 1)<br/>",
        "p(N,t) = SUM(c_i * p_i)<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; =&nbsp;&nbsp; ( 0.5 * 0.0092222592222592232 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.5 * 0.0092222592222592232 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.5 * 0.0092222592222592232 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.5 * 0.0092222592222592232 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.5 * 0.0092222592222592232 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.5 * 0.0092222592222592232 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.5 * 0.041625041625041624 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.5 * 0.041625041625041624 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = 0.069291819291819295 (hand-calculated)<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = 0.069291819291819295 (calculated at once by NewickVector)<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h3>7#: (1,2,(1,1))</h3>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "N = the phylogeny = (1,2,(1,1))<br/>",
        "t = theta = 10<br/>",
        "p(N,t) = probability = SUM(c_i * p_i)<br/>",
        "c(N,t) = coefficient<br/>",
        "D(N,t) = denominator = 40<br/>",
        "N'1 = (3,(1,1))<br/>",
        "N'2 = (1,1,(1,1))<br/>",
        "N'3 = (1,2,2)<br/>",
        "N'4 = (1,2,2)<br/>",
        " <br/>",
        "For t = 10:<br/>",
        " <br/>",
        "p'1 = 0.0026640026640026644 (calculated at once with NewickVector)<br/>",
        "p'2 = 0.12950012950012951 (calculated at once with NewickVector)<br/>",
        "p'3 = 0.0041625041625041621 (calculated at once with NewickVector)<br/>",
        "p'4 = 0.0041625041625041621 (calculated at once with NewickVector)<br/>",
        "c'1 = t / d = 10 / 40 = 0.25 (as f equals 1)<br/>",
        "c'2 = (f*(f-1)) / d = 2 / 40 = 0.050000000000000003 (as f equals 2)<br/>",
        "c'3 = t / d = 10 / 40 = 0.25 (as f equals 1)<br/>",
        "c'4 = t / d = 10 / 40 = 0.25 (as f equals 1)<br/>",
        "p(N,t) = SUM(c_i * p_i)<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; =&nbsp;&nbsp; ( 0.25 * 0.0026640026640026644 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.050000000000000003 * 0.12950012950012951 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.25 * 0.0041625041625041621 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.25 * 0.0041625041625041621 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = 0.0092222592222592232 (hand-calculated)<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = 0.0092222592222592232 (calculated at once by NewickVector)<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h3>8#: (1,(1,1,1,1))</h3>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "N = the phylogeny = (1,(1,1,1,1))<br/>",
        "t = theta = 10<br/>",
        "p(N,t) = probability = SUM(c_i * p_i)<br/>",
        "c(N,t) = coefficient<br/>",
        "D(N,t) = denominator = 20<br/>",
        "N'1 = (1,(2,1,1))<br/>",
        "N'2 = (1,(1,2,1))<br/>",
        "N'3 = (1,(1,1,2))<br/>",
        "N'4 = (1,(2,1,1))<br/>",
        "N'5 = (1,(1,2,1))<br/>",
        "N'6 = (1,(1,1,2))<br/>",
        "N'7 = (1,(1,2,1))<br/>",
        "N'8 = (1,(2,1,1))<br/>",
        "N'9 = (1,(1,1,2))<br/>",
        "N'10 = (1,(1,1,2))<br/>",
        "N'11 = (1,(1,2,1))<br/>",
        "N'12 = (1,(2,1,1))<br/>",
        " <br/>",
        "For t = 10:<br/>",
        " <br/>",
        "p'1 = 0.006919006919006921 (calculated at once with NewickVector)<br/>",
        "p'2 = 0.006919006919006921 (calculated at once with NewickVector)<br/>",
        "p'3 = 0.006919006919006921 (calculated at once with NewickVector)<br/>",
        "p'4 = 0.006919006919006921 (calculated at once with NewickVector)<br/>",
        "p'5 = 0.006919006919006921 (calculated at once with NewickVector)<br/>",
        "p'6 = 0.006919006919006921 (calculated at once with NewickVector)<br/>",
        "p'7 = 0.006919006919006921 (calculated at once with NewickVector)<br/>",
        "p'8 = 0.006919006919006921 (calculated at once with NewickVector)<br/>",
        "p'9 = 0.006919006919006921 (calculated at once with NewickVector)<br/>",
        "p'10 = 0.006919006919006921 (calculated at once with NewickVector)<br/>",
        "p'11 = 0.006919006919006921 (calculated at once with NewickVector)<br/>",
        "p'12 = 0.006919006919006921 (calculated at once with NewickVector)<br/>",
        "c'1 = t / d = 10 / 20 = 0.5 (as f equals 1)<br/>",
        "c'2 = t / d = 10 / 20 = 0.5 (as f equals 1)<br/>",
        "c'3 = t / d = 10 / 20 = 0.5 (as f equals 1)<br/>",
        "c'4 = t / d = 10 / 20 = 0.5 (as f equals 1)<br/>",
        "c'5 = t / d = 10 / 20 = 0.5 (as f equals 1)<br/>",
        "c'6 = t / d = 10 / 20 = 0.5 (as f equals 1)<br/>",
        "c'7 = t / d = 10 / 20 = 0.5 (as f equals 1)<br/>",
        "c'8 = t / d = 10 / 20 = 0.5 (as f equals 1)<br/>",
        "c'9 = t / d = 10 / 20 = 0.5 (as f equals 1)<br/>",
        "c'10 = t / d = 10 / 20 = 0.5 (as f equals 1)<br/>",
        "c'11 = t / d = 10 / 20 = 0.5 (as f equals 1)<br/>",
        "c'12 = t / d = 10 / 20 = 0.5 (as f equals 1)<br/>",
        "p(N,t) = SUM(c_i * p_i)<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; =&nbsp;&nbsp; ( 0.5 * 0.006919006919006921 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.5 * 0.006919006919006921 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.5 * 0.006919006919006921 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.5 * 0.006919006919006921 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.5 * 0.006919006919006921 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.5 * 0.006919006919006921 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.5 * 0.006919006919006921 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.5 * 0.006919006919006921 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.5 * 0.006919006919006921 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.5 * 0.006919006919006921 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.5 * 0.006919006919006921 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.5 * 0.006919006919006921 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = 0.041514041514041512 (hand-calculated)<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = 0.041514041514041512 (calculated at once by NewickVector)<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h3>9#: (1,(1,1,2))</h3>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "N = the phylogeny = (1,(1,1,2))<br/>",
        "t = theta = 10<br/>",
        "p(N,t) = probability = SUM(c_i * p_i)<br/>",
        "c(N,t) = coefficient<br/>",
        "D(N,t) = denominator = 40<br/>",
        "N'1 = (1,(2,2))<br/>",
        "N'2 = (1,(1,3))<br/>",
        "N'3 = (1,(2,2))<br/>",
        "N'4 = (1,(1,3))<br/>",
        "N'5 = (1,(1,1,1))<br/>",
        " <br/>",
        "For t = 10:<br/>",
        " <br/>",
        "p'1 = 0.0012950012950012951 (calculated at once with NewickVector)<br/>",
        "p'2 = 0.0028305028305028309 (calculated at once with NewickVector)<br/>",
        "p'3 = 0.0012950012950012951 (calculated at once with NewickVector)<br/>",
        "p'4 = 0.0028305028305028309 (calculated at once with NewickVector)<br/>",
        "p'5 = 0.097125097125097148 (calculated at once with NewickVector)<br/>",
        "c'1 = t / d = 10 / 40 = 0.25 (as f equals 1)<br/>",
        "c'2 = t / d = 10 / 40 = 0.25 (as f equals 1)<br/>",
        "c'3 = t / d = 10 / 40 = 0.25 (as f equals 1)<br/>",
        "c'4 = t / d = 10 / 40 = 0.25 (as f equals 1)<br/>",
        "c'5 = (f*(f-1)) / d = 2 / 40 = 0.050000000000000003 (as f equals 2)<br/>",
        "p(N,t) = SUM(c_i * p_i)<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; =&nbsp;&nbsp; ( 0.25 * 0.0012950012950012951 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.25 * 0.0028305028305028309 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.25 * 0.0012950012950012951 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.25 * 0.0028305028305028309 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.050000000000000003 * 0.097125097125097148 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = 0.006919006919006921 (hand-calculated)<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = 0.006919006919006921 (calculated at once by NewickVector)<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h3>#10: (1,(1,1,1,1,1))</h3>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "N = the phylogeny = (1,(1,1,1,1,1))<br/>",
        "t = theta = 10<br/>",
        "p(N,t) = probability = SUM(c_i * p_i)<br/>",
        "c(N,t) = coefficient<br/>",
        "D(N,t) = denominator = 30<br/>",
        "N'1 = (1,(2,1,1,1))<br/>",
        "N'2 = (1,(1,2,1,1))<br/>",
        "N'3 = (1,(1,1,2,1))<br/>",
        "N'4 = (1,(1,1,1,2))<br/>",
        "N'5 = (1,(2,1,1,1))<br/>",
        "N'6 = (1,(1,2,1,1))<br/>",
        "N'7 = (1,(1,1,2,1))<br/>",
        "N'8 = (1,(1,1,1,2))<br/>",
        "N'9 = (1,(1,2,1,1))<br/>",
        "N'10 = (1,(2,1,1,1))<br/>",
        "N'11 = (1,(1,1,2,1))<br/>",
        "N'12 = (1,(1,1,1,2))<br/>",
        "N'13 = (1,(1,1,2,1))<br/>",
        "N'14 = (1,(1,2,1,1))<br/>",
        "N'15 = (1,(2,1,1,1))<br/>",
        "N'16 = (1,(1,1,1,2))<br/>",
        "N'17 = (1,(1,1,1,2))<br/>",
        "N'18 = (1,(1,1,2,1))<br/>",
        "N'19 = (1,(1,2,1,1))<br/>",
        "N'20 = (1,(2,1,1,1))<br/>",
        " <br/>",
        "For t = 10:<br/>",
        " <br/>",
        "p'1 = 0.0027573616859331157 (calculated at once with NewickVector)<br/>",
        "p'2 = 0.0027573616859331157 (calculated at once with NewickVector)<br/>",
        "p'3 = 0.0027573616859331153 (calculated at once with NewickVector)<br/>",
        "p'4 = 0.0027573616859331148 (calculated at once with NewickVector)<br/>",
        "p'5 = 0.0027573616859331157 (calculated at once with NewickVector)<br/>",
        "p'6 = 0.0027573616859331157 (calculated at once with NewickVector)<br/>",
        "p'7 = 0.0027573616859331153 (calculated at once with NewickVector)<br/>",
        "p'8 = 0.0027573616859331148 (calculated at once with NewickVector)<br/>",
        "p'9 = 0.0027573616859331157 (calculated at once with NewickVector)<br/>",
        "p'10 = 0.0027573616859331157 (calculated at once with NewickVector)<br/>",
        "p'11 = 0.0027573616859331153 (calculated at once with NewickVector)<br/>",
        "p'12 = 0.0027573616859331148 (calculated at once with NewickVector)<br/>",
        "p'13 = 0.0027573616859331153 (calculated at once with NewickVector)<br/>",
        "p'14 = 0.0027573616859331157 (calculated at once with NewickVector)<br/>",
        "p'15 = 0.0027573616859331157 (calculated at once with NewickVector)<br/>",
        "p'16 = 0.0027573616859331148 (calculated at once with NewickVector)<br/>",
        "p'17 = 0.0027573616859331148 (calculated at once with NewickVector)<br/>",
        "p'18 = 0.0027573616859331153 (calculated at once with NewickVector)<br/>",
        "p'19 = 0.0027573616859331157 (calculated at once with NewickVector)<br/>",
        "p'20 = 0.0027573616859331157 (calculated at once with NewickVector)<br/>",
        "c'1 = t / d = 10 / 30 = 0.33333333333333331 (as f equals 1)<br/>",
        "c'2 = t / d = 10 / 30 = 0.33333333333333331 (as f equals 1)<br/>",
        "c'3 = t / d = 10 / 30 = 0.33333333333333331 (as f equals 1)<br/>",
        "c'4 = t / d = 10 / 30 = 0.33333333333333331 (as f equals 1)<br/>",
        "c'5 = t / d = 10 / 30 = 0.33333333333333331 (as f equals 1)<br/>",
        "c'6 = t / d = 10 / 30 = 0.33333333333333331 (as f equals 1)<br/>",
        "c'7 = t / d = 10 / 30 = 0.33333333333333331 (as f equals 1)<br/>",
        "c'8 = t / d = 10 / 30 = 0.33333333333333331 (as f equals 1)<br/>",
        "c'9 = t / d = 10 / 30 = 0.33333333333333331 (as f equals 1)<br/>",
        "c'10 = t / d = 10 / 30 = 0.33333333333333331 (as f equals 1)<br/>",
        "c'11 = t / d = 10 / 30 = 0.33333333333333331 (as f equals 1)<br/>",
        "c'12 = t / d = 10 / 30 = 0.33333333333333331 (as f equals 1)<br/>",
        "c'13 = t / d = 10 / 30 = 0.33333333333333331 (as f equals 1)<br/>",
        "c'14 = t / d = 10 / 30 = 0.33333333333333331 (as f equals 1)<br/>",
        "c'15 = t / d = 10 / 30 = 0.33333333333333331 (as f equals 1)<br/>",
        "c'16 = t / d = 10 / 30 = 0.33333333333333331 (as f equals 1)<br/>",
        "c'17 = t / d = 10 / 30 = 0.33333333333333331 (as f equals 1)<br/>",
        "c'18 = t / d = 10 / 30 = 0.33333333333333331 (as f equals 1)<br/>",
        "c'19 = t / d = 10 / 30 = 0.33333333333333331 (as f equals 1)<br/>",
        "c'20 = t / d = 10 / 30 = 0.33333333333333331 (as f equals 1)<br/>",
        "p(N,t) = SUM(c_i * p_i)<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; =&nbsp;&nbsp; ( 0.33333333333333331 * 0.0027573616859331157 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.33333333333333331 * 0.0027573616859331157 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.33333333333333331 * 0.0027573616859331153 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.33333333333333331 * 0.0027573616859331148 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.33333333333333331 * 0.0027573616859331157 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.33333333333333331 * 0.0027573616859331157 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.33333333333333331 * 0.0027573616859331153 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.33333333333333331 * 0.0027573616859331148 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.33333333333333331 * 0.0027573616859331157 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.33333333333333331 * 0.0027573616859331157 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.33333333333333331 * 0.0027573616859331153 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.33333333333333331 * 0.0027573616859331148 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.33333333333333331 * 0.0027573616859331153 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.33333333333333331 * 0.0027573616859331157 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.33333333333333331 * 0.0027573616859331157 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.33333333333333331 * 0.0027573616859331148 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.33333333333333331 * 0.0027573616859331148 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.33333333333333331 * 0.0027573616859331153 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.33333333333333331 * 0.0027573616859331157 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; + ( 0.33333333333333331 * 0.0027573616859331157 )<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = 0.018382411239554104 (hand-calculated)<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = 0.018382411239554104 (calculated at once by NewickVector)<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->"
      }
    }
  );
  m.push_back(
    { "ProjectRampalEtienne",
      {
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Introduction</h2>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectRampalEtienne.htm\">The Rampal Etienne Project</a> is a <a href=\"Projects.htm\">project</a> about calculating the probability of a phylogeny. The algorithm to do so is described in [1].</p>",
        "<p>&nbsp;</p>",
        "<p>There already was a program that performs the same algorithm, programmed by Mr X. In <a href=\"ProjectRampalEtienne.htm\">The Rampal Etienne Project</a> I have improved the program to, relative to Mr X:</p>",
        "<ul>",
        "  <li>Solve ninety times higher complexities</li>",
        "  <li>Solve a phylogeny faster</li>",
        "  <li>Solve a more complex phylogeny exponentially faster</li>",
        "  <li>Use only the memory needed</li>",
        "  <li>Use memory more efficient</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectRampalEtienne.htm\">The Rampal Etienne Project</a> has been developed by (sorted alphabetically on first name):</p>",
        "<ul>",
        "  <li><a href=\"http://www.rug.nl/biologie/onderzoek/onderzoekgroepen/cocon/people/etienne/index\">Rampal Etienne</a>: researcher</li>",
        "  <li><a href=\"http://www.richelbilderbeek.nl/\">Richel Bilderbeek</a>: programming</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectRampalEtienne.htm\">The Rampal Etienne Project</a> was developed from May to about October 2009.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Table of contents</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>Procedure</li>",
        "  <li>Measurements</li>",
        "  <li>Same results</li>",
        "  <li>Solve higher complexities</li>",
        "  <li>Speed comparison</li>",
        "  <li>Memory use</li>",
        "  <li>Large values</li>",
        "  <li>Results</li>",
        "  <li>Downloads</li>",
        "  <li>References</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Procedure</h2>",
        "<p>&nbsp;</p>",
        "<p>The project started with the published C code of Mr X. The results of this program were assumed to be correct and used as a control during the entire project. Rampal Etienne supplied Richel Bilderbeek with expert knowledge.</p>",
        "<p>&nbsp;</p>",
        "<p>Richel Bilderbeek started to convert the code to standard-conform C++ code using the <a href=\"CppStl.htm\">STL</a>, <a href=\"CppBoost.htm\">Boost</a> and <a href=\"CppVcl.htm\">VCL</a> libraries using the <a href=\"CppBuilder.htm\">C++ Builder 6.0</a> and <a href=\"CppQt.htm\">Qt Creator</a> IDE's. Each version of the program by Richel Bilderbeek is tested to yield the same results as the program of Mr X. Using the <a href=\"CppShiny.htm\">Shiny C++ profiler</a> the code speed-critical sections have been improved. Measurements were performed in a handcrafted analysis tool and Excel and <a href=\"CppVcl.htm\">VCL's</a> TChart component were used for plotting.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Measurements</h2>",
        "<p>&nbsp;</p>",
        "<p>All measurements have been performed on two different computers. Comparisons in speed, however, were performed on the same computer. By default a theta of 10.0 was used.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Same results</h2>",
        "<p>&nbsp;</p>",
        "<p>For 162 different complexities (from 24 to 866052) the results between four kinds of simulations have been compared. The probabilities found do not differ much. Differences are attributed to differences in precision in the results: Mr X uses single precision floating point values, where Richel Bilderbeek uses double-precision.</p>",
        "<p>&nbsp;</p>",
        "<p>The four simulation types are:</p>",
        "<ul>",
        "  <li>MrXExecutable: MrX's Windows executable</li>",
        "  <li>MrXLinux: MrX's Linux executable</li> ",
        "  <li>Storage&lt;SortedNewick&gt;: Bilderbeek's Windows executable</li>",
        "  <li>Storage&lt;SortedNewick&gt; Linux: Bilderbeek's Linux executable</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ProjectRampalResultsCompare.xls\">View the comparisons between the four simulations (XLS)</a>.</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Solve higher complexities</h2>",
        "<p>&nbsp;</p>",
        "<p>The maximum complexity of the program by Mr X was exactly one million, because this is hard-coded.</p>",
        "<p>&nbsp;</p>",
        "<p>The maximum complexity of the program by Richel Bilderbeek is theoretically infinite. In practice, the program is limited by the computer's memory. The maximum complexity solved is 97,656,250 (in a memory use measurement).</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ProjectRampalMemoryUse.xls\">Maximal complexity for Richel Bilderbeek's version (XLS)</a>.</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Speed comparison</h2>",
        "<p>&nbsp;</p>",
        "<p>It takes more time to calculate the probability of more complex phylogenies.</p>",
        "<p>&nbsp;</p>",
        "<p>The relationship between complexity and execution time should be contant-time, logarithmic or linear, but not be exponential.</p>",
        "<p>&nbsp;</p>",
        "<p>The relationship found (which is dependent on the computer used) between complexity and execution time is:</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "T = 1.0543*C - 4.5147<br/>",
        "</code></td></tr></table>",
        "<!-- end of code -->",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "T = LOG10(time(sec))<br/>",
        "C = LOG10(complexity)<br/>",
        "</code></td></tr></table>",
        "<!-- end of code -->",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ProjectRampalSpeedBefore.png\">Execution speed for different complexities for Mr X's version (PNG)</a>.</li>",
        "  <li><a href=\"ProjectRampalSpeedBefore.xls\">Execution speed for different complexities for Mr X's version (XLS)</a>.</li>",
        "  <li><a href=\"ProjectRampalSpeedAfter.png\">Execution speed for different complexities for Richel Bilderbeek's version (PNG)</a>.</li>",
        "  <li><a href=\"ProjectRampalSpeedAfter.xls\">Execution speed for different complexities for Richel Bilderbeek's version (XLS)</a>.</li>",
        "  <li><a href=\"ProjectRampalSpeedCompare.png\">Comparison of execution speed for different complexities (PNG)</a>.</li>",
        "  <li><a href=\"ProjectRampalSpeedCompare.xls\">Comparison of execution speed for different complexities (XLS)</a>.</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Memory use</h2>",
        "<p>&nbsp;</p>",
        "<p>The memory used of the program by Mr X equals two hundred million byte, independent of the complexity of the phylogeny, because it is hard-coded to be so. The amount of memory used is about 200,000,000 byte.</p>",
        "<p>&nbsp;</p>",
        "<p>The memory used of the program by Richel Bilderbeek depends on the complexity of the phylogeny. The program is limited on the amount of memory that can be adressed. The maximum amount of memory used is 792,237,104 byte.</p>",
        "<p>&nbsp;</p>",
        "<p>The memory used to store a single phylogeny in memory also differs. Mr X has hard-coded a phylogeny to consist of 200 characters, independent of the actual phylogeny its size (note: the program of Mr X cannot handle complexities larger than this size). In the program by Richel Bilderbeek this memory use depends on the size of the phylogeny. In theory, the version of Richel Bilderbeek can handle infite-size phylogenies.</p>",
        "<p>&nbsp;</p>",
        "<p>The relationship found (which is independent on the computer used) between complexity and memory use is:</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "M = 1.0387*C + 0.6278",
        "</code></td></tr></table>",
        "<!-- end of code -->",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "M = LOG10(memory use(byte))<br/>",
        "C = LOG10(complexity)<br/>",
        "</code></td></tr></table>",
        "<!-- end of code -->",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ProjectRampalMemoryUse.png\">Memory use for different complexities for Richel Bilderbeek's version (PNG)</a>.</li>",
        "  <li><a href=\"ProjectRampalMemoryUse.xls\">Memory use for different complexities for Richel Bilderbeek's version (XLS)</a>.</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Large values</h2>",
        "<p>&nbsp;</p>",
        "<p>The program of Richel Bilderbeek was tested for large values. It was confirmed that the values in phylogenies do not matter, where the total complexity does.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ProjectRampalLargeValues.xls\">View the results for large values in Richel Bilderbeek's version (XLS)</a>.</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Results</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>The maximal complexity of phylogenies that can be solved is at least 97 times higher in the version by Richel Bilderbeek</li>",
        "  <li>The speed in the version by Mr X increases exponentially for increasing complexity</li>",
        "  <li>The speed in the version by Richel Bilderbeek increases linearly for increasing complexity</li>",
        "  <li>The memory used in the version of Mr X is always the same and about two-hundred-million bytes</li>",
        "  <li>The memory used by the version of Richel Bilderbeek is dependent on the phylogeny its complexity</li>",
        "  <li>The maximum amount of memory adressed is about four times higher in the version of Richel Bilderbeek</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<p>The source code will not be downloadable yet.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "<li><a href=\"ProjectRampal1.png\">View a screenshot of 'The Rampal Etienne Project' #1 (PNG)</a>.</li>",
        "<li><a href=\"ProjectRampal2.png\">View a screenshot of 'The Rampal Etienne Project' #2 (PNG)</a>.</li>",
        "<li><a href=\"ProjectRampalAllResults.xls\">Download all simulation results (XLS)</a>.</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>References</h2>",
        "<p>&nbsp;</p>",
        "<p>[1] I will not give the reference yet.</p>"

      }
    }
  );
  m.push_back(
    { "ProjectRichelBilderbeek",
      {
        "<p><a href=\"ProjectRichelBilderbeek.htm\">ProjectRichelBilderbeek</a> is a <a href=\"Projects.htm\">project</a> to",
        "display all my programs as:</p>",
        "<ul>",
        "  <li><img src=\"PicConsole.png\" alt=\"console\"/> a <a href=\"CppConsoleApplication.htm\">console application</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> a <a href=\"CppDesktopApplication.htm\">desktop application</a></li>",
        "  <li><img src=\"PicWeb.png\" alt=\"Web\"/> a <a href=\"CppWebApplication.htm\">web application</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectRichelBilderbeek.htm\">ProjectRichelBilderbeek</a> is the successor of <a href=\"ProjectWtWebsite.htm\">WtWebsite</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>The <a href=\"CppWindows.htm\">Windows</a> executables are created with MXE (see <a href=\"CppI686-pc-mingw32-qmake.htm\">i686-pc-mingw32-qmake</a>)",
        "following the approach discribed at <a href=\"CppQtCrosscompileToWindowsExample15.htm\">how to cross-compile a Qt Creator project from Ubuntu to a windows executable: example 15: MinGW cross-compiling environment</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ProjectRichelBilderbeek_1_7.png\">View a screenshot of 'ProjectRichelBilderbeek' (version 1.7)(png)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ProjectRichelBilderbeek_1_10.png\">View a screenshot of 'ProjectRichelBilderbeek' (version 1.10)(png)</a></li>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ProjectWtWebsite_0_38.png\">View a screenshot of 'ProjectRichelBilderbeek' (at that time called 'ProjectWtWebsite')(version 0.38)(png)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ProjectRichelBilderbeekExe_1_8.zip\">Download the 'ProjectRichelBilderbeek' Windows executable (version 1.8)(zip)</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/> <a href=\"ProjectRichelBilderbeekSource_1_8.zip\">Download the Qt creator project 'ProjectRichelBilderbeek' (version 1.8)(zip)</a></li>",
        "  <li><a href=\"ProjectRichelBilderbeekSloccount_1_8.txt\">View the SLOCcount of 'ProjectRichelBilderbeek' (version 1.8)(txt)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ProjectRichelBilderbeek_1_5.png\">View a screenshot of 'ProjectRichelBilderbeek' (version 1.5)(png)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ProjectRichelBilderbeekExe_1_7.zip\">Download the 'ProjectRichelBilderbeek' Windows executable (version 1.7)(zip)</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/> <a href=\"ProjectRichelBilderbeekSource_1_7.zip\">Download the Qt creator project 'ProjectRichelBilderbeek' (version 1.7)(zip)</a></li>",
        "  <li><a href=\"ProjectRichelBilderbeekSloccount_1_7.txt\">View the SLOCcount of 'ProjectRichelBilderbeek' (version 1.7)(txt)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ProjectRichelBilderbeekExe_1_6.zip\">Download the 'ProjectRichelBilderbeek' Windows executable (version 1.6)(zip)</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/> <a href=\"ProjectRichelBilderbeekSource_1_6.zip\">Download the Qt creator project 'ProjectRichelBilderbeek' (version 1.6)(zip)</a></li>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ProjectRichelBilderbeek_1_1.png\">View a screenshot of 'ProjectRichelBilderbeek' (version 1.1)(png)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ProjectRichelBilderbeekExe_1_5.zip\">Download the 'ProjectRichelBilderbeek' Windows executable (version 1.5)(zip)</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/> <a href=\"ProjectRichelBilderbeekSource_1_5.zip\">Download the Qt creator project 'ProjectRichelBilderbeek' (version 1.5)(zip)</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/> <a href=\"ProjectRichelBilderbeekSource_1_4.zip\">Download the 'ProjectRichelBilderbeek' source code (version 1.4)(zip)</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/> <a href=\"ProjectRichelBilderbeekSource_1_3.zip\">Download the 'ProjectRichelBilderbeek' source code (version 1.3)(zip)</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/> <a href=\"ProjectRichelBilderbeekSource_1_2.zip\">Download the 'ProjectRichelBilderbeek' source code (version 1.2)(zip)</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/> <a href=\"ProjectRichelBilderbeekSource_1_1.zip\">Download the 'ProjectRichelBilderbeek' source code (version 1.1)(zip)</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/> <a href=\"ProjectRichelBilderbeekSource_1_0.zip\">Download the 'ProjectRichelBilderbeek' source code (version 1.0)(zip)</a></li>",
        "</ul>"

      }
    }
  );
  m.push_back(
    { "ProjectThorVeen",
      {
        "<p><img src=\"PicVcl.png\" alt=\"VCL\"/><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/></p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectThorVeen.htm\">The Thor Veen Project</a> is a simulation <a href=\"Projects.htm\">project</a> that investigates costless and honest signalling using the Hawk-Dove game as its base.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectThorVeen.htm\">The Thor Veen Project</a> has been developed for <a href=\"http://biosciences.exeter.ac.uk/staff/index.php?web_id=thor_veen\">Thor Veen</a>.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectThorVeen.htm\">The Thor Veen Project</a> has been developed by (sorted alphabetically on first name):</p>",
        "<ul>",
        "  <li><a href=\"http://www.richelbilderbeek.nl\">Richel Bilderbeek</a>: programming</li>",
        "  <li><a href=\"http://biosciences.exeter.ac.uk/staff/index.php?web_id=thor_veen\">Thor Veen</a>: researcher</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectThorVeen.htm\">The Thor Veen Project</a> was developed from about the 9th of February of 2006 to about the 3rd of April of 2006.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectThorVeen.htm\">The Thor Veen Project</a> is licenced under GPL 3.0.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ProjectThorVeen_0_9.png\">View a screenshot of 'The Thor Veen Project' (version 0.9)(png)</a></li>",
        "  <li><a href=\"ProjectThorVeenExe_0_9.zip\">Download the 'The Thor Veen Project' Windows executable (version 0.9)(zip)</a></li>",
        "  <li><a href=\"ProjectThorVeenSource_0_9.zip\">Download the 'The Thor Veen Project' source code (version 0.9)(zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ProjectTwoDigitNewick",
      {
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Introduction</h2>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectTwoDigitNewick.htm\">Project TwoDigitNewick</a> is the successor <a href=\"Projects.htm\">project</a> of ",
        "<a href=\"ProjectRampalEtienne.htm\">The Rampal Etienne Project</a>, with the goal of improving run-time speed.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectTwoDigitNewick.htm\">Project TwoDigitNewick</a> has been developed by (sorted alphabetically on first name):</p>",
        "<ul>",
        "  <li><a href=\"http://www.rug.nl/biologie/onderzoek/onderzoekgroepen/cocon/people/etienne/index\">Rampal Etienne</a>: researcher</li>",
        "  <li><a href=\"http://www.richelbilderbeek.nl/\">Richel Bilderbeek</a>: programming</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectTwoDigitNewick.htm\">Project TwoDigitNewick</a> started in May 2010.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Table of contents</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>Procedure</li>",
        "  <li>Same results</li>",
        "  <li>Speed comparison</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Procedure</h2>",
        "<p>&nbsp;</p>",
        "<p>The code of <a href=\"ProjectRampalEtienne.htm\">The Rampal Etienne Project</a> is compared to the new code in ",
        "result and speed.</p>",
        "<p>&nbsp;</p>",
        "<p>All measurements have been performed on the same computer. In all simulations, the value of parameter theta was set to 10.0.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Same results</h2>",
        "<p>&nbsp;</p>",
        "<p>In a previous project, 162 different phylogenies, with complexities from 24 to 866052, were used ",
        "to compare ProjectRampal_EndVersion2 to someone else's simulation, and",
        "it was concluded that these simulations calculate identical probabilities ",
        "for identical phylogenies and theta's.</p>",
        "<p>&nbsp;</p>",
        "<p>These same phylogenies are used to test that ToolTwoDigitNewick (this project)",
        "calculates the same probabilities as ProjectRampal_EndVersion2.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ProjectTwoDigitNewickResultsCompare.htm\">View these results as a web page (htm)</a></li>",
        "  <li><a href=\"ProjectTwoDigitNewickResultsCompare.xls\">View these results (xls)</a></li>",
        "  <li><a href=\"ProjectTwoDigitNewickResultsCompare.ods\">View these results (ods)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Speed comparison</h2>",
        "<p>&nbsp;</p>",
        "<p>The goal of <a href=\"ProjectTwoDigitNewick.htm\">Project TwoDigitNewick</a> is to be able to determine",
        "a phylogeny's complexity faster for more biological phylogenies.</p>",
        "<p>&nbsp;</p>",
        "<p>Dr. Etienne delived a phylogeny measured in the field. Because the phylogeny's complexity was",
        "about 4.8 x 10^87, it was simplified to a range of complexities both simulations can handle. ",
        "These simplifications were performed by the <a href=\"Tools.htm\">tool</a> ",
        "<a href=\"ToolSimplifyNewick.htm\">SimplifyNewick</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ProjectTwoDigitNewickSpeedCompare.htm\">View these results as a web page (htm)</a></li>",
        "  <li><a href=\"ProjectTwoDigitNewickSpeedCompare.xls\">View these results (xls)</a></li>",
        "  <li><a href=\"ProjectTwoDigitNewickSpeedCompare.ods\">View these results (ods)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>The <a href=\"Projects.htm\">project</a> results of <a href=\"ProjectTwoDigitNewick.htm\">Project TwoDigitNewick</a> show that the probabilities of this and previous project match.</p>",
        "<p>&nbsp;</p>",
        "<table summary=\"TODO\" border=\"1\">",
        "  <tr><th>Test name</th> <th>Probability</th> <th>Time (sec)</th> <th>Phylogeny</th> <th>Theta</th> <th>Complexity</th></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.82639e-308</td> <td>252</td> <td>((90,1000),100)</td> <td>10</td> <td>27000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.82639e-308</td> <td>964</td> <td>((90,1000),100)</td> <td>10</td> <td>27000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>7.49634e-309</td> <td>138</td> <td>((90,100),1000)</td> <td>10</td> <td>27000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>7.49634e-309</td> <td>449</td> <td>((90,100),1000)</td> <td>10</td> <td>27000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.71375e-156</td> <td>13</td> <td>((90,100),100)</td> <td>10</td> <td>2700000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.71375e-156</td> <td>14</td> <td>((90,100),100)</td> <td>10</td> <td>2700000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>6.175e-297</td> <td>225</td> <td>((80,1000),100)</td> <td>10</td> <td>24000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>6.175e-297</td> <td>937</td> <td>((80,1000),100)</td> <td>10</td> <td>24000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>2.31766e-297</td> <td>132</td> <td>((80,100),1000)</td> <td>10</td> <td>24000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>2.31766e-297</td> <td>429</td> <td>((80,100),1000)</td> <td>10</td> <td>24000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>4.58979e-151</td> <td>12</td> <td>((80,100),100)</td> <td>10</td> <td>2400000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>4.58979e-151</td> <td>12</td> <td>((80,100),100)</td> <td>10</td> <td>2400000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>6.8052e-285</td> <td>194</td> <td>((70,1000),100)</td> <td>10</td> <td>21000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>6.8052e-285</td> <td>766</td> <td>((70,1000),100)</td> <td>10</td> <td>21000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>2.31643e-285</td> <td>128</td> <td>((70,100),1000)</td> <td>10</td> <td>21000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>2.31643e-285</td> <td>406</td> <td>((70,100),1000)</td> <td>10</td> <td>21000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>3.08009e-145</td> <td>12</td> <td>((70,100),100)</td> <td>10</td> <td>2100000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>3.08009e-145</td> <td>11</td> <td>((70,100),100)</td> <td>10</td> <td>2100000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>2.93438e-272</td> <td>168</td> <td>((60,1000),100)</td> <td>10</td> <td>18000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>2.93438e-272</td> <td>650</td> <td>((60,1000),100)</td> <td>10</td> <td>18000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>8.96952e-273</td> <td>116</td> <td>((60,100),1000)</td> <td>10</td> <td>18000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>8.96952e-273</td> <td>368</td> <td>((60,100),1000)</td> <td>10</td> <td>18000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>6.14611e-139</td> <td>11</td> <td>((60,100),100)</td> <td>10</td> <td>1800000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>6.14611e-139</td> <td>10</td> <td>((60,100),100)</td> <td>10</td> <td>1800000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>6.32472e-259</td> <td>141</td> <td>((50,1000),100)</td> <td>10</td> <td>15000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>6.32472e-259</td> <td>540</td> <td>((50,1000),100)</td> <td>10</td> <td>15000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.71525e-259</td> <td>104</td> <td>((50,100),1000)</td> <td>10</td> <td>15000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.71525e-259</td> <td>347</td> <td>((50,100),1000)</td> <td>10</td> <td>15000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>4.60266e-132</td> <td>9</td> <td>((50,100),100)</td> <td>10</td> <td>1500000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>4.60266e-132</td> <td>9</td> <td>((50,100),100)</td> <td>10</td> <td>1500000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>2.69507e-12</td> <td>0</td> <td>((5,5),5)</td> <td>10</td> <td>375</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>2.69507e-12</td> <td>0</td> <td>((5,5),5)</td> <td>10</td> <td>375</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>9.62987e-245</td> <td>115</td> <td>((40,1000),100)</td> <td>10</td> <td>12000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>9.62987e-245</td> <td>437</td> <td>((40,1000),100)</td> <td>10</td> <td>12000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>2.28226e-245</td> <td>86</td> <td>((40,100),1000)</td> <td>10</td> <td>12000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>2.28226e-245</td> <td>281</td> <td>((40,100),1000)</td> <td>10</td> <td>12000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.8049e-124</td> <td>8</td> <td>((40,100),100)</td> <td>10</td> <td>1200000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.8049e-124</td> <td>7</td> <td>((40,100),100)</td> <td>10</td> <td>1200000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.75257e-229</td> <td>83</td> <td>((30,1000),100)</td> <td>10</td> <td>9000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.75257e-229</td> <td>323</td> <td>((30,1000),100)</td> <td>10</td> <td>9000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>3.55885e-230</td> <td>68</td> <td>((30,100),1000)</td> <td>10</td> <td>9000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>3.55885e-230</td> <td>225</td> <td>((30,100),1000)</td> <td>10</td> <td>9000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>6.18942e-116</td> <td>7</td> <td>((30,100),100)</td> <td>10</td> <td>900000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>6.18942e-116</td> <td>5</td> <td>((30,100),100)</td> <td>10</td> <td>900000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.51144e-07</td> <td>0</td> <td>((3,3),3)</td> <td>10</td> <td>81</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.51144e-07</td> <td>0</td> <td>((3,3),3)</td> <td>10</td> <td>81</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>9.37565e-213</td> <td>55</td> <td>((20,1000),100)</td> <td>10</td> <td>6000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>9.37565e-213</td> <td>219</td> <td>((20,1000),100)</td> <td>10</td> <td>6000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.58746e-213</td> <td>49</td> <td>((20,100),1000)</td> <td>10</td> <td>6000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.58746e-213</td> <td>163</td> <td>((20,100),1000)</td> <td>10</td> <td>6000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>4.50697e-106</td> <td>4</td> <td>((20,100),100)</td> <td>10</td> <td>600000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>4.50697e-106</td> <td>4</td> <td>((20,100),100)</td> <td>10</td> <td>600000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.38747e-06</td> <td>0</td> <td>((2,3),3)</td> <td>10</td> <td>54</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.38747e-06</td> <td>0</td> <td>((2,3),3)</td> <td>10</td> <td>54</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.16699e-05</td> <td>0</td> <td>((2,2),3)</td> <td>10</td> <td>36</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.16699e-05</td> <td>0</td> <td>((2,2),3)</td> <td>10</td> <td>36</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>9.25001e-05</td> <td>0</td> <td>((2,2),2)</td> <td>10</td> <td>24</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>9.25001e-05</td> <td>0</td> <td>((2,2),2)</td> <td>10</td> <td>24</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.67464e-308</td> <td>251</td> <td>((1000,100),90)</td> <td>10</td> <td>27000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.67464e-308</td> <td>974</td> <td>((1000,100),90)</td> <td>10</td> <td>27000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>5.12967e-297</td> <td>218</td> <td>((1000,100),80)</td> <td>10</td> <td>24000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>5.12967e-297</td> <td>859</td> <td>((1000,100),80)</td> <td>10</td> <td>24000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>5.04473e-285</td> <td>193</td> <td>((1000,100),70)</td> <td>10</td> <td>21000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>5.04473e-285</td> <td>741</td> <td>((1000,100),70)</td> <td>10</td> <td>21000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.90312e-272</td> <td>162</td> <td>((1000,100),60)</td> <td>10</td> <td>18000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.90312e-272</td> <td>626</td> <td>((1000,100),60)</td> <td>10</td> <td>18000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>3.49336e-259</td> <td>133</td> <td>((1000,100),50)</td> <td>10</td> <td>15000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>3.49336e-259</td> <td>521</td> <td>((1000,100),50)</td> <td>10</td> <td>15000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>4.35688e-245</td> <td>106</td> <td>((1000,100),40)</td> <td>10</td> <td>12000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>4.35688e-245</td> <td>423</td> <td>((1000,100),40)</td> <td>10</td> <td>12000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>6.10859e-230</td> <td>79</td> <td>((1000,100),30)</td> <td>10</td> <td>9000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>6.10859e-230</td> <td>309</td> <td>((1000,100),30)</td> <td>10</td> <td>9000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>2.25125e-213</td> <td>52</td> <td>((1000,100),20)</td> <td>10</td> <td>6000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>2.25125e-213</td> <td>206</td> <td>((1000,100),20)</td> <td>10</td> <td>6000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.52869e-319</td> <td>272</td> <td>((1000,100),100)</td> <td>10</td> <td>30000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.52869e-319</td> <td>1076</td> <td>((1000,100),100)</td> <td>10</td> <td>30000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.27107e-194</td> <td>25</td> <td>((1000,100),10)</td> <td>10</td> <td>3000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.27107e-194</td> <td>101</td> <td>((1000,100),10)</td> <td>10</td> <td>3000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.68674e-156</td> <td>12</td> <td>((100,100),90)</td> <td>10</td> <td>2700000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.68674e-156</td> <td>12</td> <td>((100,100),90)</td> <td>10</td> <td>2700000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>4.41521e-151</td> <td>10</td> <td>((100,100),80)</td> <td>10</td> <td>2400000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>4.41521e-151</td> <td>10</td> <td>((100,100),80)</td> <td>10</td> <td>2400000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>2.86889e-145</td> <td>9</td> <td>((100,100),70)</td> <td>10</td> <td>2100000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>2.86889e-145</td> <td>8</td> <td>((100,100),70)</td> <td>10</td> <td>2100000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>5.47198e-139</td> <td>8</td> <td>((100,100),60)</td> <td>10</td> <td>1800000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>5.47198e-139</td> <td>7</td> <td>((100,100),60)</td> <td>10</td> <td>1800000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>3.84519e-132</td> <td>6</td> <td>((100,100),50)</td> <td>10</td> <td>1500000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>3.84519e-132</td> <td>6</td> <td>((100,100),50)</td> <td>10</td> <td>1500000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.37571e-124</td> <td>5</td> <td>((100,100),40)</td> <td>10</td> <td>1200000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.37571e-124</td> <td>5</td> <td>((100,100),40)</td> <td>10</td> <td>1200000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>4.10855e-116</td> <td>3</td> <td>((100,100),30)</td> <td>10</td> <td>900000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>4.10855e-116</td> <td>3</td> <td>((100,100),30)</td> <td>10</td> <td>900000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>2.38357e-106</td> <td>3</td> <td>((100,100),20)</td> <td>10</td> <td>600000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>2.38357e-106</td> <td>2</td> <td>((100,100),20)</td> <td>10</td> <td>600000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>6.81317e-320</td> <td>137</td> <td>((100,100),1000)</td> <td>10</td> <td>30000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>6.81317e-320</td> <td>466</td> <td>((100,100),1000)</td> <td>10</td> <td>30000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.40699e-161</td> <td>13</td> <td>((100,100),100)</td> <td>10</td> <td>3000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.40699e-161</td> <td>14</td> <td>((100,100),100)</td> <td>10</td> <td>3000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.58509e-94</td> <td>1</td> <td>((100,100),10)</td> <td>10</td> <td>300000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.58509e-94</td> <td>1</td> <td>((100,100),10)</td> <td>10</td> <td>300000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.01039e-193</td> <td>26</td> <td>((10,1000),100)</td> <td>10</td> <td>3000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.01039e-193</td> <td>111</td> <td>((10,1000),100)</td> <td>10</td> <td>3000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.3687e-194</td> <td>25</td> <td>((10,100),1000)</td> <td>10</td> <td>3000000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.3687e-194</td> <td>82</td> <td>((10,100),1000)</td> <td>10</td> <td>3000000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>4.73149e-94</td> <td>2</td> <td>((10,100),100)</td> <td>10</td> <td>300000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>4.73149e-94</td> <td>2</td> <td>((10,100),100)</td> <td>10</td> <td>300000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>7.55605e-18</td> <td>0</td> <td>(((5,5),5),5)</td> <td>10</td> <td>2500</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>7.55605e-18</td> <td>0</td> <td>(((5,5),5),5)</td> <td>10</td> <td>2500</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>6.30722e-11</td> <td>0</td> <td>(((3,3),3),3)</td> <td>10</td> <td>324</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>6.30722e-11</td> <td>0</td> <td>(((3,3),3),3)</td> <td>10</td> <td>324</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>6.94432e-10</td> <td>0</td> <td>(((2,3),3),3)</td> <td>10</td> <td>216</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>6.94432e-10</td> <td>0</td> <td>(((2,3),3),3)</td> <td>10</td> <td>216</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>6.84343e-09</td> <td>0</td> <td>(((2,2),3),3)</td> <td>10</td> <td>144</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>6.84343e-09</td> <td>0</td> <td>(((2,2),3),3)</td> <td>10</td> <td>144</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>6.42062e-08</td> <td>0</td> <td>(((2,2),2),3)</td> <td>10</td> <td>96</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>6.42062e-08</td> <td>0</td> <td>(((2,2),2),3)</td> <td>10</td> <td>96</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>5.66368e-07</td> <td>0</td> <td>(((2,2),2),2)</td> <td>10</td> <td>64</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>5.66368e-07</td> <td>0</td> <td>(((2,2),2),2)</td> <td>10</td> <td>64</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>5.44502e-24</td> <td>0</td> <td>((((5,5),5),5),5)</td> <td>10</td> <td>15625</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>5.44502e-24</td> <td>0</td> <td>((((5,5),5),5),5)</td> <td>10</td> <td>15625</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.04178e-14</td> <td>0</td> <td>((((3,3),3),3),3)</td> <td>10</td> <td>1215</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.04178e-14</td> <td>0</td> <td>((((3,3),3),3),3)</td> <td>10</td> <td>1215</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.34891e-13</td> <td>1</td> <td>((((2,3),3),3),3)</td> <td>10</td> <td>810</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.34891e-13</td> <td>0</td> <td>((((2,3),3),3),3)</td> <td>10</td> <td>810</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.52424e-12</td> <td>0</td> <td>((((2,2),3),3),3)</td> <td>10</td> <td>540</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.52424e-12</td> <td>0</td> <td>((((2,2),3),3),3)</td> <td>10</td> <td>540</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.67494e-11</td> <td>0</td> <td>((((2,2),2),3),3)</td> <td>10</td> <td>360</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.67494e-11</td> <td>0</td> <td>((((2,2),2),3),3)</td> <td>10</td> <td>360</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.70858e-10</td> <td>0</td> <td>((((2,2),2),2),3)</td> <td>10</td> <td>240</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.70858e-10</td> <td>0</td> <td>((((2,2),2),2),3)</td> <td>10</td> <td>240</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.66197e-09</td> <td>0</td> <td>((((2,2),2),2),2)</td> <td>10</td> <td>160</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.66197e-09</td> <td>0</td> <td>((((2,2),2),2),2)</td> <td>10</td> <td>160</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.28288e-30</td> <td>1</td> <td>(((((5,5),5),5),5),5)</td> <td>10</td> <td>93750</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.28288e-30</td> <td>0</td> <td>(((((5,5),5),5),5),5)</td> <td>10</td> <td>93750</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>8.05661e-19</td> <td>0</td> <td>(((((3,3),3),3),3),3)</td> <td>10</td> <td>4374</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>8.05661e-19</td> <td>0</td> <td>(((((3,3),3),3),3),3)</td> <td>10</td> <td>4374</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.20422e-17</td> <td>0</td> <td>(((((2,3),3),3),3),3)</td> <td>10</td> <td>2916</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.20422e-17</td> <td>0</td> <td>(((((2,3),3),3),3),3)</td> <td>10</td> <td>2916</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.52991e-16</td> <td>0</td> <td>(((((2,2),3),3),3),3)</td> <td>10</td> <td>1944</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.52991e-16</td> <td>0</td> <td>(((((2,2),3),3),3),3)</td> <td>10</td> <td>1944</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.94894e-15</td> <td>0</td> <td>(((((2,2),2),3),3),3)</td> <td>10</td> <td>1296</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.94894e-15</td> <td>0</td> <td>(((((2,2),2),3),3),3)</td> <td>10</td> <td>1296</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>2.28426e-14</td> <td>0</td> <td>(((((2,2),2),2),3),3)</td> <td>10</td> <td>864</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>2.28426e-14</td> <td>0</td> <td>(((((2,2),2),2),3),3)</td> <td>10</td> <td>864</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>2.52818e-13</td> <td>0</td> <td>(((((2,2),2),2),2),3)</td> <td>10</td> <td>576</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>2.52818e-13</td> <td>0</td> <td>(((((2,2),2),2),2),3)</td> <td>10</td> <td>576</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>2.68866e-12</td> <td>0</td> <td>(((((2,2),2),2),2),2)</td> <td>10</td> <td>384</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>2.68866e-12</td> <td>0</td> <td>(((((2,2),2),2),2),2)</td> <td>10</td> <td>384</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.1798e-37</td> <td>7</td> <td>((((((5,5),5),5),5),5),5)</td> <td>10</td> <td>546875</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.1798e-37</td> <td>0</td> <td>((((((5,5),5),5),5),5),5)</td> <td>10</td> <td>546875</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>3.30594e-23</td> <td>0</td> <td>((((((3,3),3),3),3),3),3)</td> <td>10</td> <td>15309</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>3.30594e-23</td> <td>0</td> <td>((((((3,3),3),3),3),3),3)</td> <td>10</td> <td>15309</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>5.60673e-22</td> <td>1</td> <td>((((((2,3),3),3),3),3),3)</td> <td>10</td> <td>10206</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>5.60673e-22</td> <td>0</td> <td>((((((2,3),3),3),3),3),3)</td> <td>10</td> <td>10206</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>7.86212e-21</td> <td>0</td> <td>((((((2,2),3),3),3),3),3)</td> <td>10</td> <td>6804</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>7.86212e-21</td> <td>0</td> <td>((((((2,2),3),3),3),3),3)</td> <td>10</td> <td>6804</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.1482e-19</td> <td>0</td> <td>((((((2,2),2),3),3),3),3)</td> <td>10</td> <td>4536</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.1482e-19</td> <td>0</td> <td>((((((2,2),2),3),3),3),3)</td> <td>10</td> <td>4536</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.5392e-18</td> <td>0</td> <td>((((((2,2),2),2),3),3),3)</td> <td>10</td> <td>3024</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.5392e-18</td> <td>0</td> <td>((((((2,2),2),2),3),3),3)</td> <td>10</td> <td>3024</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.92877e-17</td> <td>0</td> <td>((((((2,2),2),2),2),3),3)</td> <td>10</td> <td>2016</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.92877e-17</td> <td>0</td> <td>((((((2,2),2),2),2),3),3)</td> <td>10</td> <td>2016</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>2.30606e-16</td> <td>0</td> <td>((((((2,2),2),2),2),2),3)</td> <td>10</td> <td>1344</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>2.30606e-16</td> <td>0</td> <td>((((((2,2),2),2),2),2),3)</td> <td>10</td> <td>1344</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>2.66166e-15</td> <td>0</td> <td>((((((2,2),2),2),2),2),2)</td> <td>10</td> <td>896</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>2.66166e-15</td> <td>0</td> <td>((((((2,2),2),2),2),2),2)</td> <td>10</td> <td>896</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>4.86659e-45</td> <td>48</td> <td>(((((((5,5),5),5),5),5),5),5)</td> <td>10</td> <td>3125000</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>4.86659e-45</td> <td>2</td> <td>(((((((5,5),5),5),5),5),5),5)</td> <td>10</td> <td>3125000</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>7.95526e-28</td> <td>1</td> <td>(((((((3,3),3),3),3),3),3),3)</td> <td>10</td> <td>52488</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>7.95526e-28</td> <td>0</td> <td>(((((((3,3),3),3),3),3),3),3)</td> <td>10</td> <td>52488</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.50701e-26</td> <td>1</td> <td>(((((((2,3),3),3),3),3),3),3)</td> <td>10</td> <td>34992</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.50701e-26</td> <td>0</td> <td>(((((((2,3),3),3),3),3),3),3)</td> <td>10</td> <td>34992</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>2.29203e-25</td> <td>0</td> <td>(((((((2,2),3),3),3),3),3),3)</td> <td>10</td> <td>23328</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>2.29203e-25</td> <td>0</td> <td>(((((((2,2),3),3),3),3),3),3)</td> <td>10</td> <td>23328</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>3.7932e-24</td> <td>1</td> <td>(((((((2,2),2),3),3),3),3),3)</td> <td>10</td> <td>15552</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>3.7932e-24</td> <td>0</td> <td>(((((((2,2),2),3),3),3),3),3)</td> <td>10</td> <td>15552</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>5.7835e-23</td> <td>0</td> <td>(((((((2,2),2),2),3),3),3),3)</td> <td>10</td> <td>10368</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>5.7835e-23</td> <td>0</td> <td>(((((((2,2),2),2),3),3),3),3)</td> <td>10</td> <td>10368</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>8.18699e-22</td> <td>0</td> <td>(((((((2,2),2),2),2),3),3),3)</td> <td>10</td> <td>6912</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>8.18699e-22</td> <td>0</td> <td>(((((((2,2),2),2),2),3),3),3)</td> <td>10</td> <td>6912</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.09617e-20</td> <td>1</td> <td>(((((((2,2),2),2),2),2),3),3)</td> <td>10</td> <td>4608</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.09617e-20</td> <td>0</td> <td>(((((((2,2),2),2),2),2),3),3)</td> <td>10</td> <td>4608</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.40905e-19</td> <td>0</td> <td>(((((((2,2),2),2),2),2),2),3)</td> <td>10</td> <td>3072</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.40905e-19</td> <td>0</td> <td>(((((((2,2),2),2),2),2),2),3)</td> <td>10</td> <td>3072</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.75415e-18</td> <td>0</td> <td>(((((((2,2),2),2),2),2),2),2)</td> <td>10</td> <td>2048</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.75415e-18</td> <td>0</td> <td>(((((((2,2),2),2),2),2),2),2)</td> <td>10</td> <td>2048</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.00738e-52</td> <td>320</td> <td>((((((((5,5),5),5),5),5),5),5),5)</td> <td>10</td> <td>17578125</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.00738e-52</td> <td>12</td> <td>((((((((5,5),5),5),5),5),5),5),5)</td> <td>10</td> <td>17578125</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.21889e-32</td> <td>4</td> <td>((((((((3,3),3),3),3),3),3),3),3)</td> <td>10</td> <td>177147</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.21889e-32</td> <td>0</td> <td>((((((((3,3),3),3),3),3),3),3),3)</td> <td>10</td> <td>177147</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>2.54374e-31</td> <td>3</td> <td>((((((((2,3),3),3),3),3),3),3),3)</td> <td>10</td> <td>118098</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>2.54374e-31</td> <td>0</td> <td>((((((((2,3),3),3),3),3),3),3),3)</td> <td>10</td> <td>118098</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>4.12913e-30</td> <td>2</td> <td>((((((((2,2),3),3),3),3),3),3),3)</td> <td>10</td> <td>78732</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>4.12913e-30</td> <td>0</td> <td>((((((((2,2),3),3),3),3),3),3),3)</td> <td>10</td> <td>78732</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>7.65623e-29</td> <td>2</td> <td>((((((((2,2),2),3),3),3),3),3),3)</td> <td>10</td> <td>52488</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>7.65623e-29</td> <td>0</td> <td>((((((((2,2),2),3),3),3),3),3),3)</td> <td>10</td> <td>52488</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.31836e-27</td> <td>1</td> <td>((((((((2,2),2),2),3),3),3),3),3)</td> <td>10</td> <td>34992</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.31836e-27</td> <td>0</td> <td>((((((((2,2),2),2),3),3),3),3),3)</td> <td>10</td> <td>34992</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>2.10152e-26</td> <td>1</td> <td>((((((((2,2),2),2),2),3),3),3),3)</td> <td>10</td> <td>23328</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>2.10152e-26</td> <td>0</td> <td>((((((((2,2),2),2),2),3),3),3),3)</td> <td>10</td> <td>23328</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>3.14722e-25</td> <td>0</td> <td>((((((((2,2),2),2),2),2),3),3),3)</td> <td>10</td> <td>15552</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>3.14722e-25</td> <td>1</td> <td>((((((((2,2),2),2),2),2),3),3),3)</td> <td>10</td> <td>15552</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>4.4918e-24</td> <td>0</td> <td>((((((((2,2),2),2),2),2),2),3),3)</td> <td>10</td> <td>10368</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>4.4918e-24</td> <td>0</td> <td>((((((((2,2),2),2),2),2),2),3),3)</td> <td>10</td> <td>10368</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>6.17986e-23</td> <td>0</td> <td>((((((((2,2),2),2),2),2),2),2),3)</td> <td>10</td> <td>6912</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>6.17986e-23</td> <td>0</td> <td>((((((((2,2),2),2),2),2),2),2),3)</td> <td>10</td> <td>6912</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>8.25436e-22</td> <td>0</td> <td>((((((((2,2),2),2),2),2),2),2),2)</td> <td>10</td> <td>4608</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>8.25436e-22</td> <td>0</td> <td>((((((((2,2),2),2),2),2),2),2),2)</td> <td>10</td> <td>4608</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.14556e-60</td> <td>2087</td> <td>(((((((((5,5),5),5),5),5),5),5),5),5)</td> <td>10</td> <td>97656250</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.14556e-60</td> <td>75</td> <td>(((((((((5,5),5),5),5),5),5),5),5),5)</td> <td>10</td> <td>97656250</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>2.88918e-36</td> <td>13</td> <td>(((((((((2,3),3),3),3),3),3),3),3),3)</td> <td>10</td> <td>393660</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>2.88918e-36</td> <td>0</td> <td>(((((((((2,3),3),3),3),3),3),3),3),3)</td> <td>10</td> <td>393660</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>4.93661e-35</td> <td>8</td> <td>(((((((((2,2),3),3),3),3),3),3),3),3)</td> <td>10</td> <td>262440</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>4.93661e-35</td> <td>0</td> <td>(((((((((2,2),3),3),3),3),3),3),3),3)</td> <td>10</td> <td>262440</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.01483e-33</td> <td>6</td> <td>(((((((((2,2),2),3),3),3),3),3),3),3)</td> <td>10</td> <td>174960</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.01483e-33</td> <td>1</td> <td>(((((((((2,2),2),3),3),3),3),3),3),3)</td> <td>10</td> <td>174960</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.95763e-32</td> <td>4</td> <td>(((((((((2,2),2),2),3),3),3),3),3),3)</td> <td>10</td> <td>116640</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.95763e-32</td> <td>0</td> <td>(((((((((2,2),2),2),3),3),3),3),3),3)</td> <td>10</td> <td>116640</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>3.49543e-31</td> <td>3</td> <td>(((((((((2,2),2),2),2),3),3),3),3),3)</td> <td>10</td> <td>77760</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>3.49543e-31</td> <td>0</td> <td>(((((((((2,2),2),2),2),3),3),3),3),3)</td> <td>10</td> <td>77760</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>5.8418e-30</td> <td>2</td> <td>(((((((((2,2),2),2),2),2),3),3),3),3)</td> <td>10</td> <td>51840</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>5.8418e-30</td> <td>0</td> <td>(((((((((2,2),2),2),2),2),3),3),3),3)</td> <td>10</td> <td>51840</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>9.25045e-29</td> <td>1</td> <td>(((((((((2,2),2),2),2),2),2),3),3),3)</td> <td>10</td> <td>34560</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>9.25045e-29</td> <td>0</td> <td>(((((((((2,2),2),2),2),2),2),3),3),3)</td> <td>10</td> <td>34560</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.40317e-27</td> <td>1</td> <td>(((((((((2,2),2),2),2),2),2),2),3),3)</td> <td>10</td> <td>23040</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.40317e-27</td> <td>0</td> <td>(((((((((2,2),2),2),2),2),2),2),3),3)</td> <td>10</td> <td>23040</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>2.93541e-25</td> <td>0</td> <td>(((((((((2,2),2),2),2),2),2),2),2),2)</td> <td>10</td> <td>10240</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>2.93541e-25</td> <td>0</td> <td>(((((((((2,2),2),2),2),2),2),2),2),2)</td> <td>10</td> <td>10240</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>4.14754e-40</td> <td>31</td> <td>((((((((((2,2),3),3),3),3),3),3),3),3),3)</td> <td>10</td> <td>866052</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>4.14754e-40</td> <td>1</td> <td>((((((((((2,2),3),3),3),3),3),3),3),3),3)</td> <td>10</td> <td>866052</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>9.36675e-39</td> <td>23</td> <td>((((((((((2,2),2),3),3),3),3),3),3),3),3)</td> <td>10</td> <td>577368</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>9.36675e-39</td> <td>1</td> <td>((((((((((2,2),2),3),3),3),3),3),3),3),3)</td> <td>10</td> <td>577368</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>2.00731e-37</td> <td>16</td> <td>((((((((((2,2),2),2),3),3),3),3),3),3),3)</td> <td>10</td> <td>384912</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>2.00731e-37</td> <td>0</td> <td>((((((((((2,2),2),2),3),3),3),3),3),3),3)</td> <td>10</td> <td>384912</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>3.98673e-36</td> <td>11</td> <td>((((((((((2,2),2),2),2),3),3),3),3),3),3)</td> <td>10</td> <td>256608</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>3.98673e-36</td> <td>1</td> <td>((((((((((2,2),2),2),2),3),3),3),3),3),3)</td> <td>10</td> <td>256608</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>7.40082e-35</td> <td>7</td> <td>((((((((((2,2),2),2),2),2),3),3),3),3),3)</td> <td>10</td> <td>171072</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>7.40082e-35</td> <td>0</td> <td>((((((((((2,2),2),2),2),2),3),3),3),3),3)</td> <td>10</td> <td>171072</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.29751e-33</td> <td>4</td> <td>((((((((((2,2),2),2),2),2),2),3),3),3),3)</td> <td>10</td> <td>114048</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.29751e-33</td> <td>1</td> <td>((((((((((2,2),2),2),2),2),2),3),3),3),3)</td> <td>10</td> <td>114048</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>2.16857e-32</td> <td>2</td> <td>((((((((((2,2),2),2),2),2),2),2),3),3),3)</td> <td>10</td> <td>76032</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>2.16857e-32</td> <td>1</td> <td>((((((((((2,2),2),2),2),2),2),2),3),3),3)</td> <td>10</td> <td>76032</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>8.23525e-29</td> <td>0</td> <td>((((((((((2,2),2),2),2),2),2),2),2),2),2)</td> <td>10</td> <td>22528</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>8.23525e-29</td> <td>0</td> <td>((((((((((2,2),2),2),2),2),2),2),2),2),2)</td> <td>10</td> <td>22528</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>3.25954e-41</td> <td>41</td> <td>(((((((((((2,2),2),2),2),3),3),3),3),3),3),3)</td> <td>10</td> <td>839808</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>3.25954e-41</td> <td>1</td> <td>(((((((((((2,2),2),2),2),3),3),3),3),3),3),3)</td> <td>10</td> <td>839808</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>6.67768e-40</td> <td>27</td> <td>(((((((((((2,2),2),2),2),2),3),3),3),3),3),3)</td> <td>10</td> <td>559872</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>6.67768e-40</td> <td>1</td> <td>(((((((((((2,2),2),2),2),2),3),3),3),3),3),3)</td> <td>10</td> <td>559872</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.29039e-38</td> <td>17</td> <td>(((((((((((2,2),2),2),2),2),2),3),3),3),3),3)</td> <td>10</td> <td>373248</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.29039e-38</td> <td>1</td> <td>(((((((((((2,2),2),2),2),2),2),3),3),3),3),3)</td> <td>10</td> <td>373248</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>2.37113e-37</td> <td>11</td> <td>(((((((((((2,2),2),2),2),2),2),2),3),3),3),3)</td> <td>10</td> <td>248832</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>2.37113e-37</td> <td>1</td> <td>(((((((((((2,2),2),2),2),2),2),2),3),3),3),3)</td> <td>10</td> <td>248832</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.87735e-32</td> <td>2</td> <td>(((((((((((2,2),2),2),2),2),2),2),2),2),2),2)</td> <td>10</td> <td>49152</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.87735e-32</td> <td>0</td> <td>(((((((((((2,2),2),2),2),2),2),2),2),2),2),2)</td> <td>10</td> <td>49152</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>1.8879e-42</td> <td>42</td> <td>((((((((((((2,2),2),2),2),2),2),2),3),3),3),3),3)</td> <td>10</td> <td>808704</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>1.8879e-42</td> <td>1</td> <td>((((((((((((2,2),2),2),2),2),2),2),3),3),3),3),3)</td> <td>10</td> <td>808704</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>3.54371e-36</td> <td>5</td> <td>((((((((((((2,2),2),2),2),2),2),2),2),2),2),2),2)</td> <td>10</td> <td>106496</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>3.54371e-36</td> <td>0</td> <td>((((((((((((2,2),2),2),2),2),2),2),2),2),2),2),2)</td> <td>10</td> <td>106496</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>5.60561e-40</td> <td>12</td> <td>(((((((((((((2,2),2),2),2),2),2),2),2),2),2),2),2),2)</td> <td>10</td> <td>229376</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>5.60561e-40</td> <td>0</td> <td>(((((((((((((2,2),2),2),2),2),2),2),2),2),2),2),2),2)</td> <td>10</td> <td>229376</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>7.49429e-44</td> <td>28</td> <td>((((((((((((((2,2),2),2),2),2),2),2),2),2),2),2),2),2),2)</td> <td>10</td> <td>491520</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>7.49429e-44</td> <td>0</td> <td>((((((((((((((2,2),2),2),2),2),2),2),2),2),2),2),2),2),2)</td> <td>10</td> <td>491520</td></tr>",
        "</table>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ProjectTwoDigitNewick.htm\">Project TwoDigitNewick</a> its <a href=\"Projects.htm\">project</a> results show that the newer version between one and two",
        "orders of magnitude faster.</p>",
        "<p>&nbsp;</p>",
        "<table summary=\"TODO\" border=\"1\">",
        "  <tr><td>Light</td> <td></td> <td></td> <td>Speed_improvement</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((2,2),2)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((2,2),2)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>(((2,2),2),2)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>(((2,2),2),2)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((((2,2),2),2),2)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((((2,2),2),2),2)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>(((((2,2),2),2),2),2)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>(((((2,2),2),2),2),2)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((((((2,2),2),2),2),2),2)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((((((2,2),2),2),2),2),2)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>(((((((2,2),2),2),2),2),2),2)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>(((((((2,2),2),2),2),2),2),2)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((((((((2,2),2),2),2),2),2),2),2)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((((((((2,2),2),2),2),2),2),2),2)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>(((((((((2,2),2),2),2),2),2),2),2),2)</td> <td>1</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>(((((((((2,2),2),2),2),2),2),2),2),2)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((((((((((2,2),2),2),2),2),2),2),2),2),2)</td> <td>1</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((((((((((2,2),2),2),2),2),2),2),2),2),2)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>(((((((((((2,2),2),2),2),2),2),2),2),2),2),2)</td> <td>2</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>(((((((((((2,2),2),2),2),2),2),2),2),2),2),2)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((((((((((((2,2),2),2),2),2),2),2),2),2),2),2),2)</td> <td>5</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((((((((((((2,2),2),2),2),2),2),2),2),2),2),2),2)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>(((((((((((((2,2),2),2),2),2),2),2),2),2),2),2),2),2)</td> <td>12</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>(((((((((((((2,2),2),2),2),2),2),2),2),2),2),2),2),2)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((((((((((((((2,2),2),2),2),2),2),2),2),2),2),2),2),2),2)</td> <td>29</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((((((((((((((2,2),2),2),2),2),2),2),2),2),2),2),2),2),2)</td> <td>1</td> <td>29</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>(((((((((((((((2,2),2),2),2),2),2),2),2),2),2),2),2),2),2),2)</td> <td>68</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>(((((((((((((((2,2),2),2),2),2),2),2),2),2),2),2),2),2),2),2)</td> <td>1</td> <td>68</td></tr>",
        "  <tr><td>Average_speed_improvement</td> <td></td> <td></td> <td>48,5</td></tr>",
        "  <tr><td></td> <td></td> <td></td> <td></td></tr>",
        "  <tr><td>Medium</td> <td></td> <td></td> <td>Speed_improvement</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((3,3),3)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((3,3),3)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>(((3,3),3),3)</td> <td>1</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>(((3,3),3),3)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((((3,3),3),3),3)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((((3,3),3),3),3)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>(((((3,3),3),3),3),3)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>(((((3,3),3),3),3),3)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((((((3,3),3),3),3),3),3)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((((((3,3),3),3),3),3),3)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>(((((((3,3),3),3),3),3),3),3)</td> <td>1</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>(((((((3,3),3),3),3),3),3),3)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((((((((3,3),3),3),3),3),3),3),3)</td> <td>4</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((((((((3,3),3),3),3),3),3),3),3)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>(((((((((3,3),3),3),3),3),3),3),3),3)</td> <td>14</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>(((((((((3,3),3),3),3),3),3),3),3),3)</td> <td>1</td> <td>14</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((((((((((3,3),3),3),3),3),3),3),3),3),3)</td> <td>56</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((((((((((3,3),3),3),3),3),3),3),3),3),3)</td> <td>1</td> <td>56</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>(((((((((((3,3),3),3),3),3),3),3),3),3),3),3)</td> <td>208</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>(((((((((((3,3),3),3),3),3),3),3),3),3),3),3)</td> <td>5</td> <td>41,6</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((((((((((((3,3),3),3),3),3),3),3),3),3),3),3),3)</td> <td>755</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((((((((((((3,3),3),3),3),3),3),3),3),3),3),3),3)</td> <td>21</td> <td>35,9523809524</td></tr>",
        "  <tr><td>Average_speed_improvement</td> <td></td> <td></td> <td>36,8880952381</td></tr>",
        "  <tr><td></td> <td></td> <td></td> <td></td></tr>",
        "  <tr><td>Hard</td> <td></td> <td></td> <td>Speed_improvement</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((4,4),4)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((4,4),4)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>(((4,4),4),4)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>(((4,4),4),4)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((((4,4),4),4),4)</td> <td>1</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((((4,4),4),4),4)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>(((((4,4),4),4),4),4)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>(((((4,4),4),4),4),4)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((((((4,4),4),4),4),4),4)</td> <td>1</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((((((4,4),4),4),4),4),4)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>(((((((4,4),4),4),4),4),4),4)</td> <td>9</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>(((((((4,4),4),4),4),4),4),4)</td> <td>0</td> <td>-</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((((((((4,4),4),4),4),4),4),4),4)</td> <td>47</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((((((((4,4),4),4),4),4),4),4),4)</td> <td>1</td> <td>47</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>(((((((((4,4),4),4),4),4),4),4),4),4)</td> <td>237</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>(((((((((4,4),4),4),4),4),4),4),4),4)</td> <td>7</td> <td>33,8571428571</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((((((((((4,4),4),4),4),4),4),4),4),4),4)</td> <td>1201</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((((((((((4,4),4),4),4),4),4),4),4),4),4)</td> <td>35</td> <td>34,3142857143</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>(((((((((((4,4),4),4),4),4),4),4),4),4),4),4)</td> <td>5932</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>(((((((((((4,4),4),4),4),4),4),4),4),4),4),4)</td> <td>21</td> <td>282,4761904762</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((((((((((((4,4),4),4),4),4),4),4),4),4),4),4),4)</td> <td>7276</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((((((((((((4,4),4),4),4),4),4),4),4),4),4),4),4)</td> <td>21</td> <td>346,4761904762</td></tr>",
        "  <tr><td>Average_speed_improvement</td> <td></td> <td></td> <td>148,8247619048</td></tr>",
        "  <tr><td></td> <td></td> <td></td> <td></td></tr>",
        "  <tr><td>Biological_(light)</td> <td></td> <td></td> <td>Speed_improvement</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,((((((1,1),(1,1)),1),((((1,((1,(1,(10,3))),((3,2),1))),1),2),1)),1),1))),1)</td> <td>8</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,((((((1,1),(1,1)),1),((((1,((1,(1,(10,3))),((3,2),1))),1),2),1)),1),1))),1)</td> <td>1</td> <td>8</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,(2,1))),1),((((1,((1,(1,(18,3))),((1,(2,2)),2))),1),1),1)),1),1))),(1,1))</td> <td>67</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,(2,1))),1),((((1,((1,(1,(18,3))),((1,(2,2)),2))),1),1),1)),1),1))),(1,1))</td> <td>5</td> <td>13,4</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,(1,((1,(1,4)),1)))),1),((((1,((1,(2,(11,5))),((1,1),1))),1),2),1)),1),1))),(1,1))</td> <td>147</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,(1,((1,(1,4)),1)))),1),((((1,((1,(2,(11,5))),((1,1),1))),1),2),1)),1),1))),(1,1))</td> <td>8</td> <td>18,375</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,(1,((1,1),1)))),1),((((1,((1,((1,1),(12,6))),(4,1))),1),(1,2)),2)),1),1))),((1,1),1))</td> <td>2232</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,(1,((1,1),1)))),1),((((1,((1,((1,1),(12,6))),(4,1))),1),(1,2)),2)),1),1))),((1,1),1))</td> <td>71</td> <td>31,4366197183</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,((2,1),(1,1)))),1),((((1,((1,(2,(32,6))),((1,2),(1,1)))),1),(1,1)),1)),1),1))),1)</td> <td>453</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,((2,1),(1,1)))),1),((((1,((1,(2,(32,6))),((1,2),(1,1)))),1),(1,1)),1)),1),1))),1)</td> <td>63</td> <td>7,1904761905</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,2),1),((((1,((1,((1,1),(17,3))),(4,1))),1),7),1)),1),1))),(1,1))</td> <td>184</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,2),1),((((1,((1,((1,1),(17,3))),(4,1))),1),7),1)),1),1))),(1,1))</td> <td>11</td> <td>16,7272727273</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,((((((1,1),(1,(1,2))),1),((((1,((1,(1,(29,3))),((5,1),1))),1),(2,1)),1)),1),1))),(1,1))</td> <td>893</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,((((((1,1),(1,(1,2))),1),((((1,((1,(1,(29,3))),((5,1),1))),1),(2,1)),1)),1),1))),(1,1))</td> <td>66</td> <td>13,5303030303</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,1)),1),((((1,((1,((1,1),(30,7))),((6,(1,1)),(1,2)))),1),(1,1)),(1,1))),1),1))),1)</td> <td>5600</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,1)),1),((((1,((1,((1,1),(30,7))),((6,(1,1)),(1,2)))),1),(1,1)),(1,1))),1),1))),1)</td> <td>22</td> <td>254,5454545455</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,(1,1))),1),((((1,((1,(2,(19,3))),(4,1))),1),3),1)),1),1))),(2,1))</td> <td>167</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,(1,1))),1),((((1,((1,(2,(19,3))),(4,1))),1),3),1)),1),1))),(2,1))</td> <td>8</td> <td>20,875</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,(1,(1,1)))),1),((((1,((1,((1,1),(18,4))),((2,2),1))),1),7),1)),1),1))),2)</td> <td>423</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,(1,(1,1)))),1),((((1,((1,((1,1),(18,4))),((2,2),1))),1),7),1)),1),1))),2)</td> <td>30</td> <td>14,1</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,(1,2))),1),((((1,((1,(1,(11,7))),((4,(2,1)),1))),1),3),1)),1),1))),1)</td> <td>64</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,(1,2))),1),((((1,((1,(1,(11,7))),((4,(2,1)),1))),1),3),1)),1),1))),1)</td> <td>12</td> <td>5,3333333333</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((2,(1,((1,2),1))),1),((((1,((1,(2,(22,4))),((1,2),(1,1)))),1),(1,1)),1)),1),1))),2)</td> <td>559</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((2,(1,((1,2),1))),1),((((1,((1,(2,(22,4))),((1,2),(1,1)))),1),(1,1)),1)),1),1))),2)</td> <td>40</td> <td>13,975</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,((((2,1),((((1,((1,(1,(16,9))),((2,4),1))),1),2),1)),1),1))),((1,1),1))</td> <td>74</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,((((2,1),((((1,((1,(1,(16,9))),((2,4),1))),1),2),1)),1),1))),((1,1),1))</td> <td>3</td> <td>24,6666666667</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((2,(1,(1,(1,1)))),1),((((1,((1,(3,(37,12))),((2,1),1))),1),(1,1)),1)),1),1))),((1,1),1))</td> <td>4020</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((2,(1,(1,(1,1)))),1),((((1,((1,(3,(37,12))),((2,1),1))),1),(1,1)),1)),1),1))),((1,1),1))</td> <td>15</td> <td>268</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,(2,(1,1)))),1),((((1,((1,((1,1),(19,3))),((3,1),1))),1),(3,3)),(1,1))),1),1))),1)</td> <td>1363</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,(2,(1,1)))),1),((((1,((1,((1,1),(19,3))),((3,1),1))),1),(3,3)),(1,1))),1),1))),1)</td> <td>159</td> <td>8,572327044</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((((1,1),1),(1,(1,((1,1),1)))),1),((((1,((1,(1,(27,5))),((4,2),1))),1),3),1)),1),1))),1)</td> <td>522</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((((1,1),1),(1,(1,((1,1),1)))),1),((((1,((1,(1,(27,5))),((4,2),1))),1),3),1)),1),1))),1)</td> <td>74</td> <td>7,0540540541</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,(2,2))),1),((((1,((1,(2,(37,5))),((2,(2,1)),1))),1),(1,1)),1)),1),1))),(1,1))</td> <td>932</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,(2,2))),1),((((1,((1,(2,(37,5))),((2,(2,1)),1))),1),(1,1)),1)),1),1))),(1,1))</td> <td>78</td> <td>11,9487179487</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,(1,((1,1),2)))),1),((((1,((1,(1,(23,8))),((3,3),1))),1),(1,2)),1)),1),1))),1)</td> <td>239</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,(1,((1,1),2)))),1),((((1,((1,(1,(23,8))),((3,3),1))),1),(1,2)),1)),1),1))),1)</td> <td>34</td> <td>7,0294117647</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,(1,(1,2)))),1),((((1,((1,((1,1),(26,4))),((2,3),1))),1),3),1)),1),1))),2)</td> <td>475</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,(1,(1,2)))),1),((((1,((1,((1,1),(26,4))),((2,3),1))),1),3),1)),1),1))),2)</td> <td>36</td> <td>13,1944444444</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,((((((1,1),(1,(1,((1,(2,1)),1)))),1),((((1,((1,(1,(13,7))),((2,3),3))),1),(1,2)),1)),1),1))),(1,1))</td> <td>3302</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,((((((1,1),(1,(1,((1,(2,1)),1)))),1),((((1,((1,(1,(13,7))),((2,3),3))),1),(1,2)),1)),1),1))),(1,1))</td> <td>191</td> <td>17,2879581152</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,(2,((1,1),1)))),1),((((1,((1,(2,(28,5))),((2,1),2))),1),1),2)),1),1))),2)</td> <td>313</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,(2,((1,1),1)))),1),((((1,((1,(2,(28,5))),((2,1),2))),1),1),2)),1),1))),2)</td> <td>26</td> <td>12,0384615385</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(2,((1,1),2))),1),((((1,((1,(1,(23,7))),((3,2),1))),1),(1,1)),1)),1),1))),(2,1))</td> <td>740</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(2,((1,1),2))),1),((((1,((1,(1,(23,7))),((3,2),1))),1),(1,1)),1)),1),1))),(2,1))</td> <td>37</td> <td>20</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,(2,((1,(1,1)),1)))),1),((((1,((1,((1,1),(35,7))),((5,1),1))),1),2),1)),1),1))),((1,1),1))</td> <td>5220</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,(2,((1,(1,1)),1)))),1),((((1,((1,((1,1),(35,7))),((5,1),1))),1),2),1)),1),1))),((1,1),1))</td> <td>248</td> <td>21,0483870968</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,(1,1))),1),((((1,((1,((2,1),(24,4))),((3,3),1))),1),3),1)),1),1))),2)</td> <td>414</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,(1,1))),1),((((1,((1,((2,1),(24,4))),((3,3),1))),1),3),1)),1),1))),2)</td> <td>29</td> <td>14,275862069</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,(1,(3,1)))),1),((((1,((1,(1,(34,7))),(1,2))),1),7),(1,1))),1),1))),(1,1))</td> <td>1811</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,(1,(3,1)))),1),((((1,((1,(1,(34,7))),(1,2))),1),7),(1,1))),1),1))),(1,1))</td> <td>149</td> <td>12,1543624161</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,(1,(1,1)))),1),((((1,((1,(2,(26,8))),((4,3),1))),1),1),1)),2),1))),(1,1))</td> <td>581</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,(1,(1,1)))),1),((((1,((1,(2,(26,8))),((4,3),1))),1),1),1)),2),1))),(1,1))</td> <td>37</td> <td>15,7027027027</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,(1,2))),1),((((1,((1,(2,(31,7))),((3,2),1))),1),2),1)),1),1))),((1,1),1))</td> <td>884</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,(1,2))),1),((((1,((1,(2,(31,7))),((3,2),1))),1),2),1)),1),1))),((1,1),1))</td> <td>40</td> <td>22,1</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,(1,1))),1),((((1,((1,(1,(29,9))),((3,(1,1)),1))),1),(1,3)),2)),1),2))),1)</td> <td>1197</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,(1,1))),1),((((1,((1,(1,(29,9))),((3,(1,1)),1))),1),(1,3)),2)),1),2))),1)</td> <td>156</td> <td>7,6730769231</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((2,(1,(2,2))),1),((((1,((1,(1,(13,7))),((3,1),2))),1),1),1)),1),1))),(2,1))</td> <td>141</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((2,(1,(2,2))),1),((((1,((1,(1,(13,7))),((3,1),2))),1),1),1)),1),1))),(2,1))</td> <td>6</td> <td>23,5</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,(2,((1,1),1)))),1),((((1,((1,(1,(35,11))),((3,(1,1)),1))),1),(1,2)),1)),1),1))),2)</td> <td>1352</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,(2,((1,1),1)))),1),((((1,((1,(1,(35,11))),((3,(1,1)),1))),1),(1,2)),1)),1),1))),2)</td> <td>121</td> <td>11,173553719</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,2)),1),((((1,((1,(1,(32,10))),((3,3),1))),1),1),1)),1),1))),((1,2),1))</td> <td>312</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,2)),1),((((1,((1,(1,(32,10))),((3,3),1))),1),1),1)),1),1))),((1,2),1))</td> <td>16</td> <td>19,5</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,(1,((1,2),1)))),1),((((1,((1,(1,(31,9))),((1,3),1))),1),3),2)),1),1))),((1,(1,1)),1))</td> <td>4860</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,(1,((1,2),1)))),1),((((1,((1,(1,(31,9))),((1,3),1))),1),3),2)),1),1))),((1,(1,1)),1))</td> <td>209</td> <td>23,2535885167</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,(1,((1,2),1)))),1),((((1,((1,(1,(27,3))),((3,3),1))),1),(1,2)),(1,1))),1),2))),(2,1))</td> <td>31757</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,(1,((1,2),1)))),1),((((1,((1,(1,(27,3))),((3,3),1))),1),(1,2)),(1,1))),1),2))),(2,1))</td> <td>17</td> <td>1868,0588235294</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,(2,(2,1)))),1),((((1,((1,(2,(23,4))),((3,2),1))),1),3),1)),1),1))),1)</td> <td>154</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,(2,(2,1)))),1),((((1,((1,(2,(23,4))),((3,2),1))),1),3),1)),1),1))),1)</td> <td>21</td> <td>7,3333333333</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,(1,(1,1)))),1),((((1,((1,(2,(16,3))),((2,2),(1,1)))),1),(2,3)),3)),1),1))),(2,1))</td> <td>5840</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,(1,(1,1)))),1),((((1,((1,(2,(16,3))),((2,2),(1,1)))),1),(2,3)),3)),1),1))),(2,1))</td> <td>23</td> <td>253,9130434783</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,(2,2))),1),((((1,((1,(1,(19,7))),((2,2),2))),1),(1,1)),1)),1),1))),2)</td> <td>152</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,(2,2))),1),((((1,((1,(1,(19,7))),((2,2),2))),1),(1,1)),1)),1),1))),2)</td> <td>12</td> <td>12,6666666667</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,(1,((1,(1,1)),1)))),1),((((1,((1,((1,1),(32,5))),((3,6),(1,1)))),1),2),1)),1),1))),(2,1))</td> <td>8018</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,(1,((1,(1,1)),1)))),1),((((1,((1,((1,1),(32,5))),((3,6),(1,1)))),1),2),1)),1),1))),(2,1))</td> <td>18</td> <td>445,4444444444</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,((1,1),((1,(1,1)),1)))),1),((((1,((1,(1,(32,13))),((1,(2,2)),1))),1),(3,2)),1)),1),1))),1)</td> <td>1854</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,((1,1),((1,(1,1)),1)))),1),((((1,((1,(1,(32,13))),((1,(2,2)),1))),1),(3,2)),1)),1),1))),1)</td> <td>19</td> <td>97,5789473684</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,((((((1,1),(1,(2,1))),1),((((1,((1,(1,(23,4))),((3,4),2))),1),2),1)),1),1))),2)</td> <td>379</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,((((((1,1),(1,(2,1))),1),((((1,((1,(1,(23,4))),((3,4),2))),1),2),1)),1),1))),2)</td> <td>30</td> <td>12,6333333333</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((((1,1),1),(1,(2,1))),1),((((1,((1,((4,2),(25,2))),((2,1),2))),1),(1,3)),1)),1),1))),1)</td> <td>2829</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((((1,1),1),(1,(2,1))),1),((((1,((1,((4,2),(25,2))),((2,1),2))),1),(1,3)),1)),1),1))),1)</td> <td>21</td> <td>134,7142857143</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,((1,1),((1,1),1)))),1),((((1,((1,((4,1),(30,9))),((4,3),1))),1),1),1)),1),1))),(1,1))</td> <td>3407</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,((1,1),((1,1),1)))),1),((((1,((1,((4,1),(30,9))),((4,3),1))),1),1),1)),1),1))),(1,1))</td> <td>17</td> <td>200,4117647059</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,(1,2))),1),((((1,((1,(2,19)),((5,2),2))),1),4),(1,1))),1),1))),2)</td> <td>609</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,(1,2))),1),((((1,((1,(2,19)),((5,2),2))),1),4),(1,1))),1),1))),2)</td> <td>46</td> <td>13,2391304348</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,((((((2,1),(1,(1,(2,1)))),1),((((1,((1,(4,(44,6))),((1,(1,1)),3))),1),(1,1)),(1,1))),1),1))),(1,1))</td> <td>8370</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,((((((2,1),(1,(1,(2,1)))),1),((((1,((1,(4,(44,6))),((1,(1,1)),3))),1),(1,1)),(1,1))),1),1))),(1,1))</td> <td>20</td> <td>418,5</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((2,(1,((1,1),((1,(1,1)),1)))),1),((((1,((1,(1,(31,8))),((6,1),1))),1),1),2)),1),2))),1)</td> <td>1316</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((2,(1,((1,1),((1,(1,1)),1)))),1),((((1,((1,(1,(31,8))),((6,1),1))),1),1),2)),1),2))),1)</td> <td>154</td> <td>8,5454545455</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,(1,3))),1),((((1,((1,(2,(23,6))),(4,1))),1),2),1)),1),1))),(2,1))</td> <td>350</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,(1,3))),1),((((1,((1,(2,(23,6))),(4,1))),1),2),1)),1),1))),(2,1))</td> <td>17</td> <td>20,5882352941</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,(1,((1,(1,1)),2)))),1),((((1,((1,(1,(27,8))),(4,2))),1),5),1)),1),1))),1)</td> <td>290</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,(1,((1,(1,1)),2)))),1),((((1,((1,(1,(27,8))),(4,2))),1),5),1)),1),1))),1)</td> <td>52</td> <td>5,5769230769</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((((1,2),1),(1,3)),1),((((1,((1,(2,(23,9))),((4,1),1))),1),(1,2)),1)),1),1))),1)</td> <td>990</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((((1,2),1),(1,3)),1),((((1,((1,(2,(23,9))),((4,1),1))),1),(1,2)),1)),1),1))),1)</td> <td>128</td> <td>7,734375</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,((((((1,1),(1,((1,1),(2,1)))),1),((((1,((1,(2,(40,10))),((2,4),1))),1),1),1)),1),1))),((1,1),1))</td> <td>4497</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,((((((1,1),(1,((1,1),(2,1)))),1),((((1,((1,(2,(40,10))),((2,4),1))),1),1),1)),1),1))),((1,1),1))</td> <td>332</td> <td>13,5451807229</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,(1,(1,1)))),1),((((1,((1,((2,2),(35,8))),((2,2),1))),1),(1,4)),1)),1),1))),1)</td> <td>1917</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,(1,(1,1)))),1),((((1,((1,((2,2),(35,8))),((2,2),1))),1),(1,4)),1)),1),1))),1)</td> <td>16</td> <td>119,8125</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((1,(1,(1,((1,2),1)))),1),((((1,((1,((1,2),(27,7))),((2,2),2))),1),(1,1)),1)),1),1))),(2,1))</td> <td>5475</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((1,(1,(1,((1,2),1)))),1),((((1,((1,((1,2),(27,7))),((2,2),2))),1),(1,1)),1)),1),1))),(2,1))</td> <td>16</td> <td>342,1875</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,((((((1,1),(1,(1,((1,2),1)))),1),((((1,((1,((2,1),(33,5))),((1,(2,1)),1))),1),(2,6)),1)),1),1))),(1,1))</td> <td>7585</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,((((((1,1),(1,(1,((1,2),1)))),1),((((1,((1,((2,1),(33,5))),((1,(2,1)),1))),1),(2,6)),1)),1),1))),(1,1))</td> <td>22</td> <td>344,7727272727</td></tr>",
        "  <tr><td>TestProjectRampal_Endversion2</td> <td>((1,(1,(((((2,(1,((1,1),((1,1),1)))),1),((((1,((1,(1,(38,4))),((2,3),(1,3)))),1),(1,3)),(1,1))),1),1))),1)</td> <td>16742</td> <td>-</td></tr>",
        "  <tr><td>TestTwoDigitNewickRelease</td> <td>((1,(1,(((((2,(1,((1,1),((1,1),1)))),1),((((1,((1,(1,(38,4))),((2,3),(1,3)))),1),(1,3)),(1,1))),1),1))),1)</td> <td>26</td> <td>643,9230769231</td></tr>",
        "  <tr><td>Average_speed_improvement</td> <td></td> <td></td> <td>176,2204639336</td></tr>",
        "</table>"
      }
    }
  );
  m.push_back(
    { "ProjectVanDenBogaart",
      {
        "<p><a href=\"ProjectProjectVanDenBogaart.htm\">Project Van Den Bogaart</a> is the former name of the <a href=\"ProjectBrainweaver.htm\">Brainweaver</a> <a href=\"Projects.htm\">project</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>For current downloads, go to <a href=\"ProjectBrainweaver.htm\">Brainweaver</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/> <a href=\"ProjectVanDenBogaart_0_27.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.27)(png)</a></li>",
        "  <li><img src=\"PicWine.png\" alt=\"Wine\"/> <a href=\"ProjectVanDenBogaart_0_27Wine.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.27)(png)</a></li>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/> <a href=\"ProjectVanDenBogaart_0_26.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.26)(png)</a></li>",
        "  <li><img src=\"PicWine.png\" alt=\"Wine\"/> <a href=\"ProjectVanDenBogaart_0_26Wine.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.26)(png)</a></li>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/> <a href=\"ProjectVanDenBogaart_0_25.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.25)(png)</a></li>",
        "  <li><img src=\"PicWine.png\" alt=\"Wine\"/> <a href=\"ProjectVanDenBogaart_0_25Wine.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.25)(png)</a></li>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/> <a href=\"ProjectVanDenBogaart_0_24.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.24)(png)</a></li>",
        "  <li><img src=\"PicWine.png\" alt=\"Wine\"/> <a href=\"ProjectVanDenBogaart_0_24Wine.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.24)(png)</a></li>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/> <a href=\"ProjectVanDenBogaart_0_23.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.23)(png)</a></li>",
        "  <li><img src=\"PicWine.png\" alt=\"Wine\"/> <a href=\"ProjectVanDenBogaart_0_23Wine.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.23)(png)</a></li>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/> <a href=\"ProjectVanDenBogaart_0_22.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.22)(png)</a></li>",
        "  <li><img src=\"PicWine.png\" alt=\"Wine\"/> <a href=\"ProjectVanDenBogaart_0_22Wine.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.22)(png)</a></li>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/> <a href=\"ProjectVanDenBogaart_0_20.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.20)(png)</a></li>",
        "  <li><img src=\"PicWine.png\" alt=\"Wine\"/> <a href=\"ProjectVanDenBogaart_0_20Wine.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.20)(png)</a></li>",
        "  <li><a href=\"ProjectVanDenBogaart_0_19.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.19)(png)</a></li>",
        "  <li><a href=\"ProjectVanDenBogaart_0_18.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.18)(png)</a></li>",
        "  <li><a href=\"ProjectVanDenBogaart_0_17.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.17)(png)</a></li>",
        "  <li><a href=\"ProjectVanDenBogaart_0_16.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.16)(png)</a></li>",
        "  <li><a href=\"ProjectVanDenBogaart_0_15.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.15)(png)</a></li>",
        "  <li><a href=\"ProjectVanDenBogaart_0_14.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.14)(png)</a></li>",
        "  <li><a href=\"ProjectVanDenBogaart_0_13.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.13)(png)</a></li>",
        "  <li><a href=\"ProjectVanDenBogaart_0_12.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.12)(png)</a></li>",
        "  <li><a href=\"ProjectVanDenBogaart_0_11.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.11)(png)</a></li>",
        "  <li><a href=\"ProjectVanDenBogaart_0_10.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.10)(png)</a></li>",
        "  <li><a href=\"ProjectVanDenBogaart_0_9.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.9)(png)</a></li>",
        "  <li><a href=\"ProjectVanDenBogaart_0_8.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.8)(png)</a></li>",
        "  <li><a href=\"ProjectVanDenBogaart_0_7.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.7)(png)</a></li>",
        "  <li><a href=\"ProjectVanDenBogaart_0_6.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.6)(png)</a></li>",
        "  <li><a href=\"ProjectVanDenBogaart_0_5.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.5)(png)</a></li>",
        "  <li><a href=\"ProjectVanDenBogaart_0_4.png\">View a screenshot of 'Project Van Den Bogaart' (version 0.4)(png)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ProjectWtWebsite",
      {
        "<p><a href=\"ProjectWtWebsite.htm\">WtWebsite</a> is a <a href=\"Projects.htm\">project</a> to",
        "display all my programs as a <a href=\"CppWt.htm\">Wt</a> dynamic website.</p>",
        "<p>&nbsp;</p>",
        "<p><img src=\"PicTo.png\" alt=\"To\"/> <a href=\"ProjectRichelBilderbeek.htm\">ProjectRichelBilderbeek</a> is the successor of <a href=\"ProjectWtWebsite.htm\">WtWebsite</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicTo.png\" alt=\"To\"/> <a href=\"ProjectRichelBilderbeek.htm\">Go to ProjectRichelBilderbeek</a></li>",
        "  <li><a href=\"ProjectWtWebsite_0_38.png\">View a screenshot of 'WtWebsite' (version 0.38)(png)</a></li>",
        "  <li><a href=\"ProjectWtWebsite_0_34.png\">View a screenshot of 'WtWebsite' (version 0.34)(png)</a></li>",
        "  <li><a href=\"ProjectWtWebsite_0_25.png\">View a screenshot of 'WtWebsite' (version 0.25)(png)</a></li>",
        "  <li><a href=\"ProjectWtWebsite_0_23.png\">View a screenshot of 'WtWebsite' (version 0.23)(png)</a></li>",
        "  <li><a href=\"ProjectWtWebsite_0_17.png\">View a screenshot of 'WtWebsite' (version 0.17)(png)</a></li>",
        "  <li><a href=\"ProjectWtWebsite_0_14.png\">View a screenshot of 'WtWebsite' (version 0.14)(png)</a></li>",
        "  <li><a href=\"ProjectWtWebsite_0_12.png\">View a screenshot of 'WtWebsite' (version 0.12)(png)</a></li>",
        "  <li><a href=\"ProjectWtWebsite_0_8.png\">View a screenshot of 'WtWebsite' (version 0.8)(png)</a></li>",
        "  <li><a href=\"ProjectWtWebsite_0_7.png\">View a screenshot of 'WtWebsite' (version 0.7)(png)</a></li>",
        "  <li><a href=\"ProjectWtWebsite_0_6.png\">View a screenshot of 'WtWebsite' (version 0.6)(png)</a></li>",
        "  <li><a href=\"ProjectWtWebsite_0_5.png\">View a screenshot of 'WtWebsite' (version 0.5)(png)</a></li>",
        "  <li><a href=\"ProjectWtWebsite_0_4.png\">View a screenshot of 'WtWebsite' (version 0.4)(png)</a></li>",
        "  <li><a href=\"ProjectWtWebsite_0_3.png\">View a screenshot of 'WtWebsite' (version 0.3)(png)</a></li>",
        "  <li><a href=\"ProjectWtWebsite_0_2.png\">View a screenshot of 'WtWebsite' (version 0.2)(png)</a></li>",
        "  <li><a href=\"ProjectWtWebsite_0_1.png\">View a screenshot of 'WtWebsite' (version 0.1)(png)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ToolAsciiArter",
      {
        "<p><a href=\"ToolAsciiArter.htm\">AsciiArter</a> is a <a href=\"Tools.htm\">tool</a> to convert images to <a href=\"CppAsciiArt.htm\">ASCII art</a>.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ToolAsciiArter.htm\">AsciiArter</a> is the successor of <a href=\"ToolAsciiArterVcl.htm\">AsciiArterVcl</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>",
        "    <img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWeb.png\" alt=\"Web\"/><img src=\"PicSpacer.png\" alt=\" \"/> ",
        "    <a href=\"ToolAsciiArter_5_2.png\">View a screenshot of 'AsciiArter' (version 5.2)(png)</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicUbuntu.png\" alt=\"Lubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicSpacer.png\" alt=\" \"/> ",
        "    <a href=\"ToolAsciiArter_5_1.png\">View a screenshot of 'AsciiArter' (version 5.1)(png)</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicSpacer.png\" alt=\" \"/> ",
        "    <a href=\"ToolAsciiArterDesktopExe_5_1.zip\">Download the 'AsciiArter' Windows executable (version 5.1)(zip)</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicWeb.png\" alt=\"Web\"/> ",
        "    <a href=\"ToolAsciiArterSource_5_1.zip\">Download the 'AsciiArter' source code (version 5.1)(zip)</a>",
        "  </li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>The <a href=\"CppWindows.htm\">Windows</a> executables are created following <a href=\"CppQtCrosscompileToWindowsExample15.htm\">how to cross-compile a Qt Creator project from Ubuntu to a windows executable: example 15: MinGW cross-compiling environment</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>",
        "    <img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicWeb.png\" alt=\"Web\"/><img src=\"PicSpacer.png\" alt=\" \"/> ",
        "    <a href=\"ToolTestAsciiArter_4_1.png\">View a screenshot of 'AsciiArter' (version 4.1)(png)</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicSpacer.png\" alt=\" \"/> ",
        "    <a href=\"ToolTestAsciiArter_4_0.png\">View a screenshot of 'AsciiArter' (version 4.0)(png)</a>",
        "  </li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ToolAsciiArterVcl",
      {
        "<p><a href=\"ToolAsciiArterVcl.htm\">AsciiArterVcl</a> is a <a href=\"Tools.htm\">tool</a> to convert images to <a href=\"CppAsciiArt.htm\">ASCII art</a>.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ToolAsciiArterVcl.htm\">AsciiArterVcl</a> is superseded by <a href=\"ToolAsciiArter.htm\">AsciiArter</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>",
        "    <img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicSpacer.png\" alt=\" \"/> ",
        "    <a href=\"ToolTestAsciiArter_1_0.png\">View a screenshot of 'AsciiArterVcl' (version 1.0)(png)</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicSpacer.png\" alt=\" \"/> ",
        "    <a href=\"ToolTestAsciiArterExeWindows_1_0.zip\">Download the 'AsciiArterVcl' Windows executable (version 1.0)(zip)</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicSpacer.png\" alt=\" \"/> ",
        "    <a href=\"ToolAsciiArterVclSource_1_0.zip\">Download the 'AsciiArterVcl' source code (version 1.0)(zip)</a>",
        "  </li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ToolBarbaImage",
      {
        "<p><a href=\"ToolBarbaImage.htm\">BarbaImage</a> is a <a href=\"Tools.htm\">tool</a> to perform operations on images. It creates a new window after each image operation, so you never loose your intermediates.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolBarbaImage_1_3.png\">View a screenshot of 'BarbaImage' (version 1.3)(png)</a></li>",
        "  <li><a href=\"ToolBarbaImageExe_1_3.zip\">Download the 'BarbaImage' Windows executable (version 1.3)(zip)</a></li>",
        "  <li><a href=\"ToolBarbaImageSource_1_3.zip\">Download the 'BarbaImage' source code (version 1.3)(zip)</a></li>",
        "  <li><a href=\"ToolBarbaImageSource_1_3.htm\">View the 'BarbaImage' C++ Builder source code as a web page (version 1.3)(htm)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolBarbaImageExe_1_2.zip\">Download the 'BarbaImage' Windows executable (version 1.2)(zip)</a></li>",
        "  <li><a href=\"ToolBarbaImageSource_1_2.zip\">Download the 'BarbaImage' source code (version 1.2)(zip)</a></li>",
        "  <li><a href=\"ToolBarbaImageExe_1_0.zip\">Download the 'BarbaImage' Windows executable (version 1.0)(zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "CppCallStackCounter",
      {
        "<p>",
        "  <a href=\"CppCallStackCounter.htm\">CallstackCounter</a> is a",
        "  <a href=\"class.htm\">class</a> to track the size of the call stack.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  Construct <a href=\"CppCallStackCounter.htm\">CallstackCounter</a> in the",
        "  functions you want to track. This must be done before the first return statement.",
        "  You can obtain the history from any",
        "  <a href=\"CppCallStackCounter.htm\">CallstackCounter</a> in any function.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppCallStackCounterSource_1_0.zip\">Download the 'CallstackCounter' source code (version 1.0)(zip)</a></li>",
        "  <li><a href=\"CppCallStackCounterSource_1_0.htm\">View the C++ Builder source code of 'CallstackCounter' as a web page (version 1.0)(htm)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ToolCnd",
      {
        "<p><a href=\"ToolCnd.htm\">Color Number Determinator</a> is one of my first self-written tool. It shows the color of a certain red, green and blue value.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolCndScreenshot.png\">View a screenshot of 'Color Number Determinator' (png)</a></li>",
        "  <li><a href=\"ToolCndSource.rar\">Download the 'Color Number Determinator' source code (rar)</a></li>",
        "  <li><a href=\"ToolCndExe.rar\">Download the 'Color Number Determinator' Windows executable (rar)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ToolCodeToHtml",
      {
        "<p><a href=\"ToolCodeToHtml.htm\">CodeToHtml</a> is a <a href=\"Tools.htm\">tool</a> to convert plain ",
        "<a href=\"Cpp.htm\">C++</a> code to its heavily-linked HTML counterpart for my website.</p>",
        "<p>&nbsp;</p>",
        "<p>Note: the <a href=\"ToolCodeToHtml.htm\">CodeToHtml</a> source code on this website is converted to HTML by ",
        "<a href=\"ToolCodeToHtml.htm\">CodeToHtml</a>, of course!</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolCodeToHtml_2_3.png\">View a screenshot of 'CodeToHtml' (version 2.3)(png)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolCodeToHtml_2_3.png\">View a screenshot of the menu screen of 'CodeToHtml' (version 2.3)(png)</a></li>",
        "  <li><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolCodeToHtml_2_0.png\">View a screenshot of 'CodeToHtml' (version 2.0)(png)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolCodeToHtmlSource_2_5.zip\">Download the 'CodeToHtml' source code (version 2.5)(zip)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolCodeToHtmlSource_2_5.htm\">View the 'CodeToHtml' source code as web page (version 2.5)(htm)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Pages created by <a href=\"ToolCodeToHtml.htm\">CodeToHtml</a></h2>",
        "<p>&nbsp;</p>",
        "<p>This is an incomplete list.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppAbout.htm\">About</a></li>",
        "  <li><a href=\"CppAsciiArter.htm\">AsciiArter</a></li>",
        "  <li><a href=\"CppAssert.htm\">Assert</a></li>",
        "  <li><a href=\"CppBinaryNewickVector.htm\">BinaryNewickVector</a></li>",
        "  <li><a href=\"CppConnectThree.htm\">ConnectThree</a></li>",
        "  <li><a href=\"CppConnectThreeWidget.htm\">ConnectThreeWidget</a></li>",
        "  <li><a href=\"CppCopy_if.htm\">Copy_if</a></li>",
        "  <li><a href=\"CppCounter.htm\">Counter</a></li>",
        "  <li><a href=\"CppDial.htm\">Dial</a></li>",
        "  <li><a href=\"CppDialWidget.htm\">DialWidget</a></li>",
        "  <li><a href=\"CppEncranger.htm\">Encranger</a></li>",
        "  <li><a href=\"CppFuzzy_equal_to.htm\">Fuzzy_equal_to</a></li>",
        "  <li><a href=\"CppHtmlPage.htm\">HtmlPage</a></li>",
        "  <li><a href=\"CppIpAddress.htm\">IpAddress</a></li>",
        "  <li><a href=\"CppLed.htm\">Led</a></li>",
        "  <li><a href=\"CppLedWidget.htm\">LedWidget</a></li>",
        "  <li><a href=\"CppLoopReader.htm\">LoopReader</a></li>",
        "  <li><a href=\"CppMultipleChoiceQuestion.htm\">MultipleChoiceQuestion</a></li>",
        "  <li><a href=\"CppMultipleChoiceQuestionDialog.htm\">MultipleChoiceQuestionDialog</a></li>",
        "  <li><a href=\"CppMultiVector.htm\">MultiVector</a></li>",
        "  <li><a href=\"CppMysteryMachine.htm\">MysteryMachine</a></li>",
        "  <li><a href=\"CppNewick.htm\">Newick</a></li>",
        "  <li><a href=\"CppNewick.htm\">Newick</a>Ravindran</li>",
        "  <li><a href=\"CppNewickVector.htm\">NewickVector</a></li>",
        "  <li><a href=\"CppOpenQuestion.htm\">OpenQuestion</a></li>",
        "  <li><a href=\"CppOpenQuestionDialog.htm\">OpenQuestionDialog</a></li>",
        "  <li><a href=\"CppPrimeExpert.htm\">PrimeExpert</a></li>",
        "  <li><a href=\"CppProFile.htm\">ProFile</a></li>",
        "  <li><a href=\"CppQtAboutDialog.htm\">QtAboutDialog</a></li>",
        "  <li><a href=\"CppQtConnectThreeWidget.htm\">QtConnectThreeWidget</a></li>",
        "  <li><a href=\"CppQtDialWidget.htm\">QtDialWidget</a></li>",
        "  <li><a href=\"CppQtLedDisplayWidget.htm\">QtLedDisplayWidget</a></li>",
        "  <li><a href=\"CppQtLedWidget.htm\">QtLedWidget</a></li>",
        "  <li><a href=\"CppQtMultipleChoiceQuestionDialog.htm\">QtMultipleChoiceQuestionDialog</a></li>",
        "  <li><a href=\"CppQtOpenQuestionDialog.htm\">QtOpenQuestionDialog</a></li>",
        "  <li><a href=\"CppQtShapeWidget.htm\">QtShapeWidget</a></li>",
        "  <li><a href=\"CppQtTicTacToeWidget.htm\">QtTicTacToeWidget</a></li>",
        "  <li><a href=\"CppQuestion.htm\">Question</a></li>",
        "  <li><a href=\"CppQuestionDialog.htm\">QuestionDialog</a></li>",
        "  <li><a href=\"CppRainbow.htm\">Rainbow</a></li>",
        "  <li><a href=\"CppRandomCode.htm\">RandomCode</a></li>",
        "  <li><a href=\"CppRectangle.htm\">Rectangle</a></li>",
        "  <li><a href=\"CppRubiksClock.htm\">RubiksClock</a></li>",
        "  <li><a href=\"CppRubiksClockWidget.htm\">RubiksClockWidget</a></li>",
        "  <li><a href=\"CppShape.htm\">Shape</a></li>",
        "  <li><a href=\"CppShapeWidget.htm\">ShapeWidget</a></li>",
        "  <li><a href=\"CppSortedBinaryNewickVector.htm\">SortedBinaryNewickVector</a></li>",
        "  <li><a href=\"CppStopwatch.htm\">Stopwatch</a></li>",
        "  <li><a href=\"CppSurvey.htm\">Survey</a></li>",
        "  <li><a href=\"CppTicTacToe.htm\">TicTacToe</a></li>",
        "  <li><a href=\"CppToggleButton.htm\">ToggleButton</a></li>",
        "  <li><a href=\"CppTrace.htm\">Trace</a></li>",
        "  <li><a href=\"CppTwoDigitNewick.htm\">TwoDigitNewick</a></li>",
        "  <li><a href=\"CppWidget.htm\">Widget</a></li>",
        "  <li><a href=\"CppWtAboutDialog.htm\">WtAboutDialog</a></li>",
        "  <li><a href=\"CppWtAutoConfig.htm\">WtAutoConfig</a></li>",
        "  <li><a href=\"CppWtBroadcastServer.htm\">WtBroadcastServer</a></li>",
        "  <li><a href=\"CppWtConnectThreeWidget.htm\">WtConnectThreeWidget</a></li>",
        "  <li><a href=\"CppWtDialWidget.htm\">WtDialWidget</a></li>",
        "  <li><a href=\"CppWtGroupWidget.htm\">WtGroupWidget</a></li>",
        "  <li><a href=\"CppWtLedDisplayWidget.htm\">WtLedDisplayWidget</a></li>",
        "  <li><a href=\"CppWtLedWidget.htm\">WtLedWidget</a></li>",
        "  <li><a href=\"CppWtMultipleChoiceQuestionDialog.htm\">WtMultipleChoiceQuestionDialog</a></li>",
        "  <li><a href=\"CppWtOpenQuestionDialog.htm\">WtOpenQuestionDialog</a></li>",
        "  <li><a href=\"CppWtRubiksClockWidget.htm\">WtRubiksClockWidget</a></li>",
        "  <li><a href=\"CppWtSafeTimer.htm\">WtSafeTimer</a></li>",
        "  <li><a href=\"CppWtSelectFileDialog.htm\">WtSelectFileDialog</a></li>",
        "  <li><a href=\"CppWtServerPusher.htm\">WtServerPusher</a></li>",
        "  <li><a href=\"CppWtShapeGroupWidget.htm\">WtShapeGroupWidget</a></li>",
        "  <li><a href=\"CppWtShapeWidget.htm\">WtShapeWidget</a></li>",
        "  <li><a href=\"CppWtTicTacToeWidget.htm\">WtTicTacToeWidget</a></li>",
        "  <li><a href=\"CppWtTimedServerPusher.htm\">WtTimedServerPusher</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolCodeToHtml_2_2.png\">View a screenshot of 'CodeToHtml' (version 2.2)(png)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolCodeToHtml_2_1.png\">View a screenshot of the menu screen of 'CodeToHtml' (version 2.1)(png)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolCodeToHtml_1_9.png\">View a screenshot of 'CodeToHtml' (version 1.9)(png)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolCodeToHtml_1_8.png\">View a screenshot of 'CodeToHtml' (version 1.8)(png)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolCodeToHtml_1_7.png\">View a screenshot of 'CodeToHtml' (version 1.7)(png)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolCodeToHtml_1_6.png\">View a screenshot of 'CodeToHtml' (version 1.6)(png)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolCodeToHtml_1_5.png\">View a screenshot of 'CodeToHtml' (version 1.5)(png)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolCodeToHtml_1_4.png\">View a screenshot of 'CodeToHtml' (version 1.4)(png)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ToolCombinator",
      {
        "<p>If you have a set of numbers, what are the subsets which have the sum of x?</p>",
        "<p>&nbsp;</p>",
        "<p>If you have ever pondered this for whole numbers, <a href=\"ToolCombinator.htm\">Combinator</a> is the tool for you!</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolCombinatorScreenshot.png\">View a screenshot of 'Combinator'</a></li>",
        "  <li><a href=\"ToolCombinatorExe.rar\">Download the 'Combinator' Windows executable</a></li>",
        "  <li><a href=\"ToolCombinatorSource.rar\">Download the 'Combinator' source code</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ToolCoutChildWindows",
      {
        "<p><a href=\"ToolCoutChildWindows.htm\">CoutChildWindows</a> shows all (child)windows' text.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ToolCoutChildWindows.htm\">CoutChildWindows</a> is   released at the 2nd of February of 2010 and programmed in <a",
        "href=\"Cpp.htm\">C++</a> using the IDE <a href=\"CppBuilder.htm\">C++ Builder</a>",
        "6.0. It uses the <a href=\"CppStl.htm\">STL</a> and <a href=\"CppBoost.htm\">Boost</a>",
        "library.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolCoutChildWindowsScreenshot.png\">View a screenshot of 'CoutChildWindows'</a></li>",
        "  <li><a href=\"ToolCoutChildWindowsExe.zip\">Download the 'CoutChildWindows' Windows executable (zip)</a></li>",
        "  <li><a href=\"ToolCoutChildWindowsSource.zip\">Download the 'CoutChildWindows' source code (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ToolCreateGlossary",
      {
        "<p>",
        "  <a href=\"ToolCreateGlossary.htm\">CreateGlossary</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to generate the glossaries of this website.",
        "</p>"
      }
    }
  );
  m.push_back(
    { "ToolCreateQtProjectZipFile",
      {
        "<p><a href=\"ToolCreateQtProjectZipFile.htm\">CreateQtProjectZipFile</a> is a <a href=\"Tools.htm\">tool</a> to generate",
        "a .sh script from a <a href=\"CppQtCreator.htm\">Qt Creator</a> project file. This script will zip the entire project.",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolCreateQtProjectZipFile_2_0.png\">View a screenshot of 'CreateQtProjectZipFile' (version 2.0)(png)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolCreateQtProjectZipFileSource_2_0.zip\">Download the 'CreateQtProjectZipFile' source code (version 2.0)(zip)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolCreateQtProjectZipFileSource_2_0.htm\">View the 'CreateQtProjectZipFile' source code as web page (version 2.0)(htm)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolCreateQtProjectZipFileSource_1_3.zip\">Download the 'CreateQtProjectZipFile' source code (version 1.3)(zip)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolCreateQtProjectZipFileSource_1_2.htm\">View the 'CreateQtProjectZipFile' source code as web page (version 1.2)(htm)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolCreateQtProjectZipFileSource_1_2.zip\">Download the 'CreateQtProjectZipFile' source code (version 1.2)(zip)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolCreateQtProjectZipFileSource_1_0.zip\">Download the 'CreateQtProjectZipFile' source code (version 1.0)(zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ToolDotMatrix",
      {
        "<p>",
        "  <a href=\"ToolDotMatrix.htm\">DotMatrix</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to display text as dot-matrix",
        "  characters (5 (width) x 7 (height) pixels, without spacer pixels),",
        "  like on your microwave display.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolDotMatrix_2_1.png\">View a screenshot of 'DotMatrix' (2.1)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ToolDotMatrixVcl",
      {
        "<p>",
        "  <a href=\"ToolDotMatrixVcl.htm\">DotMatrix (VCL)</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to display text as dot-matrix ",
        "  characters (5 (width) x 7 (height) pixels, without spacer pixels),",
        "  like on your microwave display.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"ToolDotMatrixVcl.htm\">DotMatrix (VCL)</a> is the predecessor",
        "  of <a href=\"ToolDotMatrix.htm\">DotMatrix</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolDotMatrix_1_0.png\">View a screenshot of 'DotMatrix (VCL)' (1.0)</a></li>",
        "  <li><a href=\"ToolDotMatrixExe.zip\">Download the 'DotMatrix' Windows executable (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ToolEmptyTextLinesRemover",
      {
        "<p>I've noticed that when I copy code from my page, I get a lot of added extra empty",
        "lines when pasting. So, I've written <a href=\"ToolEmptyTextLinesRemover.htm\">Empty Text Lines Remover</a>. I wanted to",
        "use it, but at first it did not work! So, I've added 'plain text pages' to my",
        "site. And now, the 19th of October 2007, it seems to work... Whatever...</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolEmptyTextLinesRemoverScreenshot.png\">View a screenshot of 'Empty Text Lines Remover'</a></li>",
        "  <li><a href=\"ToolEmptyTextLinesRemoverSource.rar\">Download the 'Empty Text Lines Remover' source code</a></li>",
        "  <li><a href=\"ToolEmptyTextLinesRemoverExe.rar\">Download the 'Empty Text Lines Remover' Windows executable</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ToolEncrypter",
      {
        "<p>Using <a href=\"CppCryptography.htm\">my simple cryptography algorithms</a> I made two console",
        "applications and a single GUI shell.</p>",
        "<p>&nbsp;</p>",
        "<p>Do not use <a href=\"ToolEncrypter.htm\">Encrypter</a>, but prefer using <a href=\"ToolEncranger.htm\">Encranger</a>:",
        "it is a better tool in all aspects.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolEncrypterScreenshot.png\">View a screenshot of the Encrypter GUI shell</a></li>",
        "  <li><a href=\"ToolEncrypterSource.rar\">Download the Encrypter source code</a></li>",
        "  <li><a href=\"ToolEncrypterExe.rar\">Download the Encrypter Windows executables</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ToolFilterOperationer",
      {
        "<p>",
        "  <a href=\"ToolFilterOperationer.htm\">FilterOperationer</a> is a <a href=\"Tools.htm\">tool</a>",
        "  that do a filter operation type called a convolution an images.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppDoFilterOperation.png\">View an example image of 'DoFilterOperation'</a></li>",
        "  <li><a href=\"ToolFilterOperationer_2_0.png\">View a screenshot of 'FilterOperationer' (2.0)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ToolFilterOperationerVcl",
      {
        "<p>",
        "  <a href=\"ToolFilterOperationer.htm\">FilterOperationer (VCL)</a> is a <a href=\"Tools.htm\">tool</a>",
        "  that do a filter operation type called a convolution an images.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"ToolFilterOperationer.htm\">FilterOperationer (VCL)</a> is the predecessor of",
        "  <a href=\"ToolFilterOperationer.htm\">FilterOperationer</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppDoFilterOperation.png\">View an example image of 'DoFilterOperation'</a></li>",
        "  <li><a href=\"ToolFilterOperationer_1_0.png\">View a screenshot of 'FilterOperationer (VCL)'</a> (1.0)</li>",
        "  <li><a href=\"ToolFilterOperationerExe.zip\">Download the 'FilterOperationer (VCL)' Windows executable (zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "ToolFakeEvy",
      {
        "<p>",
        "  <a href=\"ToolFakeEvy.htm\">FakeEvy</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to generate 'Start To Run' episodes.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolFryskLeareLieder",
      {
        "<p>",
        "  <a href=\"ToolFryskLeareLieder.htm\">Frysk Leare Lieder</a> is a <a href=\"Tools.htm\">tool</a>",
        "  programmed on the 10th February 2007 to practice my Frysian (a language spoken in",
        "  the Northwest of Holland). This first version contains only seven verbs,",
        "  but for me it is still very tough! As my Frysian knowledge increase,",
        "  I will improve it and add more words to it.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolFryskLeareLieder_1_0.png\">View a screenshot of 'Frysk Leare Lieder' (version 1.0)(png)</a></li>",
        "  <li><a href=\"ToolFryskLeareLiederExe_1_0.zip\">Download the 'Frysk Leare Lieder' Windows executable (version 1.0)(zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ToolFunctionPlotter",
      {
        "<p>",
        "  <a href=\"ToolFunctionPlotter.htm\">FunctionPlotter</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to demonstrate <a href=\"http://warp.povusers.org/FunctionParser\">Warp's FunctionParser class</a>:",
        "</p>",
        "<p>",
        "  The user can input a function in the for 'y=f(x)' and a range for x.",
        "  <a href=\"ToolFunctionPlotter.htm\">FunctionPlotter</a> then plots the values of y.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolFunctionPlotter_2_0.png\">View a screenshot of 'FunctionPlotter' (v.2.0)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>External links</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"http://warp.povusers.org/FunctionParser\">Homepage of Warp's FunctionParser class</a></li>",
        "</ul>",
      }
    }
  );

  m.push_back(
    { "ToolFunctionPlotterVcl",
      {
        "<p>",
        "  <a href=\"ToolFunctionPlotterVcl.htm\">FunctionPlotter (VCL)</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to demonstrate <a href=\"http://warp.povusers.org/FunctionParser\">Warp's FunctionParser class</a>:",
        "</p>",
        "<p>",
        "  <a href=\"ToolFunctionPlotterVcl.htm\">FunctionPlotter (VCL)</a> is the predecessor of",
        "  <a href=\"ToolFunctionPlotter.htm\">FunctionPlotter</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  Note that this program uses",
        "  <a href=\"http://warp.povusers.org/FunctionParser\">Warp's FunctionParser class</a>",
        "  version 2.7, where the current version (of February 2010) exceeds 4.0. This is due",
        "  to compilation problems under <a href=\"CppBuilder.htm\">C++ Builder</a> 6.0.",
        "  Small changes have been made to",
        "  <a href=\"http://warp.povusers.org/FunctionParser\">Warp's FunctionParser class</a>",
        "  to get it to compile.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolFunctionPlotter_1_1.png\">View a screenshot of 'FunctionPlotter (VCL)' (v.1.1)</a></li>",
        "  <li><a href=\"ToolFunctionPlotterExe.zip\">Download the 'FunctionPlotter (VCL)' Windows executable (v.1.1)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>External links</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"http://warp.povusers.org/FunctionParser\">Homepage of Warp's FunctionParser class</a></li>",
        "</ul>",
      }
    }
  );



  m.push_back(
    { "ToolGaborFilter",
      {
        "<p>",
        "  <a href=\"ToolGaborFilter.htm\">GaborFilter</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to perform Gabor filtering on images.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  I learned about Gabor filters while working on",
        "  <a href=\"ProjectBochum.htm\">my Bochum Project</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolGaborFilterExample.png\">View an example image of 'GaborFilter' (png)</a></li>",
        "  <li><a href=\"ToolGaborFilter_2_0.png\">View a screenshot of 'GaborFilter' (png)(version 2.0)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>The Gabor filter</h2>",
        "<p>&nbsp;</p>",
        "<p>A Gabor filter can have any number of dimension. Below the formula (and a bit of derivation) for the one-dimensional and two-dimensional Gabor filters are described.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>The one-dimensional Gabor filter formula</h2>",
        "<p>&nbsp;</p>",
        "<p>The function of a one-dimensional Gabor filter is:</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "f_Gabor(x) = cos(frequency*x) * exp(-(x*x)/(sigma*sigma))<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>In the range [-5,5] a nice combination of values is frequency = 4.0 and sigma = 2.0:</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "f_Gabor = cos(4.0*x) * exp(-(x*x)/(2.0*2.0))",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>The one-dimensional Gabor filter formula consists out of three parts:</p>",
        "<ol>",
        "  <li>the cosine part</li>",
        "  <li>the Gaussian function part</li>",
        "  <li>a constant</li>",
        "</ol>",
        "<p>&nbsp;</p>",
        "<p>These three parts are described in detail below.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h3>1. the cosine part</h3>",
        "<p>&nbsp;</p>",
        "<p>The cosine part of a Gabor function is dependent on distance and frequency</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h3>2. the Gaussian function part</h3>",
        "<p>&nbsp;</p>",
        "<p><a href=\"http://en.wikipedia.org/wiki/Gaussian_function\">the Gaussian function</a> part of a Gabor function is dependent on distance and sigma.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"http://en.wikipedia.org/wiki/Gaussian_function\">A Gaussian function</a> has the form</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "F_Gauss(x) <br/>",
        "&nbsp;&nbsp;= a * exp(-((x-b)*(x-b))/(2*c*c))<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p><a href=\"http://en.wikipedia.org/wiki/Gaussian_function\">The Gaussian function</a> used in the one-dimensional Gabor filter has</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "a = 1<br/>",
        "b = 0 <br/>",
        "c = sigma <br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>which results in</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "f_Gabor_part2<br/>",
        "&nbsp;&nbsp;= 1.0 * exp(-((x-0.0) * (x-0.0))/(2.0 * sigma * sigma))<br/>",
        "&nbsp;&nbsp;= exp(-(x * x)/(2.0 * sigma * sigma))<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h3>3. a constant</h3>",
        "<p>&nbsp;</p>",
        "<p>The third term of a Gabor function is a constant that might be used to make the <a href=\"http://en.wikipedia.org/wiki/Gaussian_integral\">Gaussian integral</a> (that is, the surface underneath <a href=\"http://en.wikipedia.org/wiki/Gaussian_function\">the Gaussian function</a>) equal to 1.0.</p>",
        "<p>&nbsp;</p>",
        "<p>I have set this term to one, because in my case, the <a href=\"http://en.wikipedia.org/wiki/Gaussian_integral\">Gaussian integral</a> does not matter, due to <a href=\"CppRescale.htm\">rescaling</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>Continue reading to find out how to make the <a href=\"http://en.wikipedia.org/wiki/Gaussian_integral\">Gaussian integral</a> (that is, the surface underneath <a href=\"http://en.wikipedia.org/wiki/Gaussian_function\">the Gaussian function</a>) equal to 1.0:</p>",
        "<p>&nbsp;</p>",
        "<p>A <a href=\"http://en.wikipedia.org/wiki/Gaussian_function\">Gaussian function</a> has the form</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "f_Gauss(x)<br/>",
        "&nbsp;&nbsp;= a * exp(-((x-b)*(x-b))/(2*c*c))<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>and has the <a href=\"http://en.wikipedia.org/wiki/Integral_of_a_Gaussian_function\">Gaussian integral</a> of</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "F_Gauss(x) = a * c * sqrt(pi)",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>Because in the Gabor filter</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "a = 1<br/>",
        "b = 0 <br/>",
        "c = sigma<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>the integral becomes</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "F_Gabor_part2(x) <br/>",
        "&nbsp;&nbsp;= 1 * sigma * sqrt(pi)<br/>",
        "&nbsp;&nbsp;= sigma * sqrt(pi)<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>This integral denotes the surface underneath a one-dimensional <a href=\"http://en.wikipedia.org/wiki/Gaussian_function\">Gaussian function</a>. To make the surface underneath the one-dimensional <a href=\"http://en.wikipedia.org/wiki/Gaussian_function\">Gaussian function</a> 1.0, one needs multiply the <a href=\"http://en.wikipedia.org/wiki/Gaussian_function\">Gaussian function</a> by the reciprocal of the integral.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>The two-dimensional Gabor filter formula</h2>",
        "<p>&nbsp;</p>",
        "<p>The function of a two-dimensional Gabor filter is:</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "f_Gabor(x)<br/>",
        "&nbsp;&nbsp;= cos(frequency*x)<br/>",
        "&nbsp;&nbsp;* exp(-(x*x)/(sigma*sigma))<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>In the range [-5,5] a nice combination of values is frequency = 4.0 and sigma = 1.5:</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "F_Gabor<br/>",
        "&nbsp;&nbsp;= cos(4*x) * exp(-(x*x)/(1.5*1.5)) * (1 / (1.5 * sqrt(3.14159265)))<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>The two-dimensional Gabor filter formula consists out of three parts:</p>",
        "<ol>",
        "  <li>the cosine part</li>",
        "  <li>the Gaussian function part</li>",
        "  <li>a constant</li>",
        "</ol>",
        "<p>&nbsp;</p>",
        "<p>These three parts are described in detail below.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h3>1. the cosine part</h3>",
        "<p>&nbsp;</p>",
        "<p>The cosine part of the two-dimensional Gabor filter formula is dependent on distance and frequency.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h3>2. the Gaussian function part</h3>",
        "<p>&nbsp;</p>",
        "<p>The Gaussian function part of the two-dimensional Gabor filter formula is dependent on distance and sigma.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"http://en.wikipedia.org/wiki/Gaussian_function\">A Gaussian function</a> has the form</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "F_Gauss(x,y)<br/>",
        "&nbsp;&nbsp;= a * exp(- <br/>",
        "&nbsp;&nbsp;( ( (x-mid_x)*(x-mid_x))/(2*sigma_x * sigma_x) ) <br/>",
        "&nbsp;&nbsp;+ ( (y-mid_y)*(y-mid_y))/(2*sigma_y * sigma_y) ) )<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p><a href=\"http://en.wikipedia.org/wiki/Gaussian_function\">The Gaussian function</a> used in the two-dimensional Gabor filter has</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "a = 1<br/>",
        "sigma_x = sigma_y = sigma <br/>",
        "mid_x = midy = 0<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>which results in</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "F_Gabor_part2(x,y) <br/>",
        "&nbsp;&nbsp;= exp(- <br/>",
        "&nbsp;&nbsp;( ( (x*x)/(2 * sigma * sigma) ) <br/>",
        "&nbsp;&nbsp;+ ( (y*y)/(2 * sigma * sigma) ) )<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h3>3. a constant</h3>",
        "<p>&nbsp;</p>",
        "<p>The third term is a constant that might make the two-dimensional <a href=\"http://en.wikipedia.org/wiki/Gaussian_integral\">Gaussian integral</a> (that is, the volume underneath the <a href=\"http://en.wikipedia.org/wiki/Gaussian_function\">the Gaussian function</a>) equal to 1.0.</p>",
        "<p>&nbsp;</p>",
        "<p>I have set this term to one, because in my case, the <a href=\"http://en.wikipedia.org/wiki/Gaussian_integral\">Gaussian integral</a> does not matter, due to <a href=\"CppRescale.htm\">rescaling</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>Furthermore, there is no formula (known to me) that allows the calculate the two-dimensional <a href=\"http://en.wikipedia.org/wiki/Gaussian_integral\">Gaussian integral</a>. Therefore, only by approximation this value's constant can be found.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Calculating sigma</h2>",
        "<p>&nbsp;</p>",
        "<p>For the one-dimensional and two-dimensional Gabor filters I calculate a value of sigma for the filter's size. Sigma determines how fast the <a href=\"http://en.wikipedia.org/wiki/Gaussian_function\">Gaussian function</a> starts approaching zero.</p>",
        "<p>&nbsp;</p>",
        "<p>If a filter has a size of s pixels, it would be inefficient to have the <a href=\"http://en.wikipedia.org/wiki/Gaussian_function\">Gaussian function</a> already approaching zero at s/2. It would be strange that at the edges of a filter, the <a href=\"http://en.wikipedia.org/wiki/Gaussian_function\">Gaussian function</a> still have high values.</p>",
        "<p>&nbsp;</p>",
        "<p>In this part, I calculate sigma from the filter's size, that the <a href=\"http://en.wikipedia.org/wiki/Gaussian_function\">Gaussian function</a> yields a value of 1/510 at the edges. I choose the value of 1/510, because in viewing a filter as a bitmap (with grey values from [0,255], these values will appear as black/zero due to rounding off.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>The one-dimensional Gabor filter formula</h2>",
        "<p>&nbsp;</p>",
        "<p>The <a href=\"http://en.wikipedia.org/wiki/Gaussian_function\">Gaussian function</a> part (part 2, as described above) of a Gabor filter, has the following formula:</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "f_Gabor_part2(x) = exp(-(x * x)/(2.0 * sigma * sigma))<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>Assume a filter size and halve it to obtain s (s is like a radius), then</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "x = s<br/>",
        "f_Gabor_part2(x = s) <br/>",
        "&nbsp;&nbsp;= exp(-(s * s)/(2.0 * sigma * sigma))<br/>",
        "&nbsp;&nbsp;= 1/510<br/>",
        "<br/>",
        "exp(-(s * s)/(2.0 * sigma * sigma)) = 1/510<br/>",
        "-(s * s)/(2.0 * sigma * sigma) = ln(1/510)<br/>",
        "-(s * s)/ln(1/510) = 2.0 * sigma * sigma<br/>",
        "-(s * s)/(2.0*ln(1/510)) = sigma * sigma<br/>",
        "sigma = sqrt(-(s * s) / (2.0*ln(1/510)))<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>Which, by approximation is:</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "sigma = sqrt(-(s * s) / -12.46882145143674291132554261896)<br/>",
        "sigma = sqrt( (s * s) /  12.46882145143674291132554261896)<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>External links</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"http://en.wikipedia.org/wiki/Gabor_filter\">Wikipedia page about Gabor filters</a></li>",
        "</ul>"
      }
    }
  );



  m.push_back(
    { "ToolGaborFilterVcl",
      {
        "<p>",
        "  <a href=\"ToolGaborFilterVcl.htm\">GaborFilter (VCL)</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to perform Gabor filtering on images.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"ToolGaborFilterVcl.htm\">GaborFilter (VCL)</a> is programmed with the ",
        "  <a href=\"CppBuilder.htm\">C++ Builder</a> 6.0 <a href=\"CppIde.htm\">IDE</a>",
        "  and is the predecessor of <a href=\"ToolGaborFilter.htm\">GaborFilter</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolGaborFilter_1_0.png\">View a screenshot of 'GaborFilter (VCL)' (png)(version 1.0)</a></li>",
        "  <li><a href=\"ToolGaborFilterExe.zip\">Download the 'GaborFilter (VCL)' Windows executable (zip)(version 1.0)</a></li>",
        "</ul>",
      }
    }
  );


  m.push_back(
    { "ToolTestGnuplotInterface",
      {
        "<p><a href=\"CppGnuplotInterface.htm\">GnuplotInterface</a> is a <a href=\"CppClass.htm\">class</a> ",
        "that enables the user to easily plot values in <a href=\"CppGnuplot.htm\">Gnuplot</a>. It handles ",
        "both the connection to <a href=\"CppGnuplot.htm\">Gnuplot</a> and performs the window management as well. ",
        "It creates a text-file in which the location of the <a href=\"CppGnuplot.htm\">Gnuplot</a> executable can ",
        "be entered (without recompiling the program).</p>",
        "<p>&nbsp;</p>",
        "<p>The <a href=\"Tools.htm\">tool</a> <a href=\"ToolTestGnuplotInterface.htm\">TestGnuplotInterface</a> tests ",
        "the <a href=\"CppGnuplotInterface.htm\">GnuplotInterface</a> <a href=\"CppClass.htm\">class</a>.",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"Note: only tested under MacOS\" border = \"1\"><tr><td><code>",
        "I only got this interface to work under MacOS<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>The one function that this <a href=\"CppClass.htm\">class</a> is built around is the popen function. This is a non-standard function to open a pipe. If this function is unknown under your programming environment, try either std::popen, std::_popen, std::__popen, popen, _popen or __popen.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppGnuplotInterface.png\">View a screenshot of a graph created with Gnuplot interface</a>. Thanks to Roger Wehage for submitting this image and allowing me to use it.</li>",
        "  <li><a href=\"CppGnuplotInterfaceSource.zip\">Download the 'Gnuplot Interface' source code (zip)</a>.</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Known <a href=\"CppCompileError.htm\">compile errors</a></h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"CppCompileError_popenIsNotAmemberOfStd.htm\">_popen is not a member of std</a></li>",
        "  <li><a href=\"CppCompileErrorCLK_TCKwasNotDeclaredInThisScope.htm\">CLK_TCK was not declared in this scope</a></li>",
        "  <li><a href=\"CppCompileErrorDuplicateSymbol.htm\">Duplicate symbol Gnuplot::SetLineStyles()</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ToolGrayCoder",
      {

        "<p>",
        "  <a href=\"ToolGrayCoder.htm\">GrayCoder</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to convert integer values to Gray codes and",
        "  vice versa.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolGrayCoder_2_1.png\"> View a screenshot of 'GrayCoder' (version 2.1)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>External links</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"http://en.wikipedia.org/wiki/Gray_code\">Wikipedia s page about Gray Codes</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "ToolGrayCoderVcl",
      {

        "<p>",
        "  <a href=\"ToolGrayCoderVcl.htm\">GrayCoder (VCL)</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to convert integer values to Gray codes and",
        "  vice versa.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"ToolGrayCoderVcl.htm\">GrayCoder (VCL)</a> is the predecessor of",
        "  <a href=\"ToolGrayCoder.htm\">GrayCoder</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolGrayCoder_1_0.png\"> View a screenshot of 'GrayCoder (VCL)' (version 1.0)</a></li>",
        "  <li><a href=\"ToolGrayCoderExe_1_0.zip\">Download the 'GrayCoder (VCL)' Windows executable (version 1.0)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>External links</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"http://en.wikipedia.org/wiki/Gray_code\">Wikipedia s page about Gray Codes</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ToolHaaifsKiller",
      {
        "<p><a href=\"ToolHaaifsKiller.htm\">HaaifsKiller</a> is an anti-<a href=\"http://www.hyves.nl/\">Hyves</a>-<a href=\"Tools.htm\">tool</a> that can be",
        "used by system administrators: it hides itself after five seconds, after which it automatically minimizes webbrowsers that are used to view <a href=\"http://www.hyves.nl/\">Hyves</a>.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ToolHaaifsKiller.htm\">HaaifsKiller</a> can be fooled. FathersEye recognizes webpages visually and is more difficult to fool.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ToolHaaifsKiller.htm\">HaaifsKiller</a> is released at the 31st of January of 2010 and programmed in <a href=\"Cpp.htm\">C++</a>",
        "using the IDE <a href=\"CppBuilder.htm\">C++ Builder</a> 6.0. It uses the <a href=\"CppStl.htm\">STL</a>, <a href=\"CppVcl.htm\">VCL</a> and <a href=\"CppBoost.htm\">Boost</a> library.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolHaaifsKillerScreenshot.png\">View a screenshot of 'HaaifsKiller'</a> (before it hides itself)</li>",
        "  <li><a href=\"ToolHaaifsKillerExe.zip\">Download the 'HaaifsKiller' Windows executable (v. 1.0)(zip)</a></li>",
        "  <li><a href=\"ToolHaaifsKillerSource.zip\">Download the 'HaaifsKiller' source code (v. 1.0)(zip)</a></li>",
        "</ul>",
      }
    }
  );
  m.push_back(
    { "ToolHistogramEqualizationer",
      {
        "<p>",
        "  <a href=\"ToolHistogramEqualizationer.htm\">HistogramEqualizationer</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to perform a <a href=\"CppDoHistogramEqualization.htm\">histogram equalization</a> on an image.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolHistogramEqualizationer_2_0.png\">View a screenshot of HistogramEqualizationer' (2.0)(png)</a></li>",
        "</ul>",
      }
    }
  );

  m.push_back(
    { "ToolHistogramEqualizationerVcl",
      {
        "<p>",
        "  <a href=\"ToolHistogramEqualizationerVcl.htm\">HistogramEqualizationer (VCL)</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to perform a <a href=\"CppDoHistogramEqualization.htm\">histogram equalization</a> on an image.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"ToolHistogramEqualizationerVcl.htm\">HistogramEqualizationer (VCL)</a> the predecessor",
        "  of <a href=\"ToolHistogramEqualizationer.htm\">HistogramEqualizationer</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolHistogramEqualizationer_1_0.png\">View a screenshot of HistogramEqualizationer (VCL)' (1.0)(png)</a></li>",
        "  <li><a href=\"ToolHistogramEqualizationerExe.zip\">Download the 'HistogramEqualizationer' Windows executable (zip)</a></li>",
        "</ul>",
      }
    }
  );


  m.push_back(
    { "ToolHometrainer",
      {
        "<p><a href=\"ToolHometrainer.htm\">Hometrainer</a> is <a href=\"CppDesktopApplication.htm\">desktop</a> <a href=\"Tools.htm\">tool</a> ",
        "to train self-made exercises with open questions and multiple choice questions, ",
        "with or without images. The exercises can created by use of a simple text editor (Notepad, for example). ",
        "<a href=\"ToolHometrainer.htm\">Hometrainer</a> can also be used for examination.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Simple example of Hometrainer in creating exercises</h2>",
        "<p>&nbsp;</p>",
        "<p>Supply the program with a text file like shown below (note that the first line is obligatory):</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "Hometrainer (C) 2009-2014 Richel Bilderbeek<br/>",
        "Humanbody.bmp,Which line points to the liver?,1,2,3,4<br/>",
        "Humanbody.bmp,Which line points to the liver?,1/one/One<br/>",
        "Humanbody.bmp,Which organ does line 1 point to?,The liver/the liver/Liver/liver<br/>",
        "-,In which organ is ethanol detoxified?,The liver/the liver/Liver/liver<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>The program will show you the image, the question and the (shuffled) answers. You have to click the right answer. Great to train yourself in nearly anything!</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Screenshots</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolHometrainer_2_0.png\">View a screenshot of 'Hometrainer' (version 2.0)(png)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Hometrainer executable and source</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>...</li>",
        "  <li>Older: <a href=\"ToolHometrainerVcl.htm\">Hometrainer (VCL)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Hometrainer manual</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolHometrainerManual.doc\">Download the 'Hometrainer' manual (English)(version 0.5)(doc)</a></li>",
        "  <li>Download the 'Hometrainer' manual (Dutch)(doc)</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>English Hometrainer exercises</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>None yet</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Dutch Hometrainer exercises</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolHometrainer_BiBb1_1_0.zip\">Nectar BB hoofdstuk 1: Vier Rijken (version 1.0)</a></li>",
        "  <li><a href=\"ToolHometrainer_BiBb5_1_1.zip\">Nectar BB hoofdstuk 5: Mens En Milieu (version 1.1)</a></li>",
        "  <li><a href=\"ToolHometrainer_BiBb6_1_0.zip\">Nectar BB hoofdstuk 6: Eten (version 1.0)</a></li>",
        "  <li><a href=\"ToolHometrainer_BiBk1_1_1.zip\">Nectar KB hoofdstuk 1: Vier Rijken Vergelijken (version 1.1)</a></li>",
        "  <li><a href=\"ToolHometrainer_BiKb6_1_2.zip\">Nectar KB hoofdstuk 6: Ademen en eten (version 1.2)</a></li>",
        "  <li><a href=\"ToolHometrainer_BiKb7_1_0.zip\">Nectar KB hoofdstuk 7: Bloed (version 1.2)</a></li>",
        "  <li><a href=\"ToolHometrainer_NaskTl1_v1_3.zip\">Nova 3TL hoofdstuk 1: Electriciteit (version 1.3)(zip)</a></li>",
        "  <li><a href=\"ToolHometrainer_TtBasis_1_2.zip\">Theatertechniek: Basis (version 1.2)(zip)</a></li>",
        "  <li><a href=\"ToolHometrainer_TtGeluid_0_9.zip\">Theatertechniek: Geluidstechniek (version 0.9)(zip)</a></li>",
        "  <li><a href=\"ToolHometrainer_TtLicht_0_9.zip\">Theatertechniek: Lichttechniek (version 0.9)(zip)</a></li>",
        "  <li><a href=\"ToolHometrainer_WijkenArnhem_1_0.zip\">Wijken van Arnhem (version 1.0)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Old versions of Dutch Hometrainer exercises</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolHometrainer_BiBb5_1_0.zip\">Nectar BB hoofdstuk 5: Mens En Milieu (version 1.0)</a></li>",
        "  <li><a href=\"ToolHometrainer_BiKb6_0_3.zip\">Nectar KB hoofdstuk 6: Ademen en eten (version 0.3)</a></li>",
        "  <li><a href=\"ToolHometrainer_BiKb6_1_0.zip\">Nectar KB hoofdstuk 6: Ademen en eten (version 1.0)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older Hometrainer versions</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolHometrainerExe_1_7.zip\">Download the 'Hometrainer' Windows executable (version 1.7)(zip)</a></li>",
        "  <li><a href=\"ToolHometrainerSource_1_7.zip\">Download the 'Hometrainer' source code (version 1.7)(zip)</a></li>",
        "  <li><a href=\"ToolHometrainerExe_1_6.zip\">Download the 'Hometrainer' Windows executable (version 1.6)(zip)</a></li>",
        "  <li><a href=\"ToolHometrainerSource_1_6.zip\">Download the 'Hometrainer' source code (version 1.6)(zip)</a></li>",
        "  <li><a href=\"ToolHometrainerExe_1_5.zip\">Download the 'Hometrainer' Windows executable (version 1.5)(zip)</a></li>",
        "  <li><a href=\"ToolHometrainerSource_1_5.zip\">Download the 'Hometrainer' source code (version 1.5)(zip)</a></li>",
        "  <li><a href=\"ToolHometrainerExe_1_4.zip\">Download the 'Hometrainer' Windows executable (version 1.4)(zip)</a></li>",
        "  <li><a href=\"ToolHometrainerSource_1_4.zip\">Download the 'Hometrainer' source code (version 1.4)(zip)</a></li>",
        "  <li><a href=\"ToolHometrainerExe_1_3.zip\">Download the 'Hometrainer' Windows executable (version 1.3)(zip)</a></li>",
        "  <li><a href=\"ToolHometrainerSource_1_3.zip\">Download the 'Hometrainer' source code (version 1.3)(zip)</a></li>",
        "  <li><a href=\"ToolHometrainerExe_1_2.zip\">Download the 'Hometrainer' Windows executable (version 1.2)(zip)</a></li>",
        "  <li><a href=\"ToolHometrainerSource_1_2.zip\">Download the 'Hometrainer' source code (version 1.2)(zip)</a></li>",
        "  <li><a href=\"ToolHometrainerExe_1_1.zip\">Download the 'Hometrainer' Windows executable (version 1.1)(zip)</a></li>",
        "  <li><a href=\"ToolHometrainerSource_1_1.zip\">Download the 'Hometrainer' source code (version 1.1)(zip)</a></li>",
        "  <li><a href=\"ToolHometrainerExe_1_0.zip\">Download the 'Hometrainer' Windows executable (version 1.0)(zip)</a></li>",
        "  <li><a href=\"ToolHometrainerSource_1_0.zip\">Download the 'Hometrainer' source code (version 1.0)(zip)</a></li>",
        "  <li><a href=\"ToolHometrainerExe_0_9.zip\">Download the 'Hometrainer' Windows executable (version 0.9)(zip)</a></li>",
        "  <li><a href=\"ToolHometrainerSource_0_9.zip\">Download the 'Hometrainer' source code (version 0.9)(zip)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/> <a href=\"ToolHometrainer_0_9.png\">View a screenshot of 'Hometrainer' (version 0.9)(png)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Hometrainer manual versions</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>Version X.Y: DD-MM-YYYY</li>",
        "  <li>Version 0.5: 23-09-2009</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Links to similar freeware programs</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolHometrainer.htm\">Hometrainer</a> (my previous version of Hometrainer)</li>",
        "  <li><a href=\"http://wordfox.byethost17.com/wordfox/index.php\">WordFox</a></li>",
        "  <li><a href=\"http://www.efkasoft.com/drillassistant/drillassistant.html\">Drill Assistant</a></li>",
        "  <li><a href=\"http://www.efkasoft.com/overhoor/overhoor.html\">Overhoor</a>: Dutch</li>",
        "  <li><a href=\"http://www.luziusschneider.com/QuizHome.htm\">Quiz</a>: for multiple-choice questions only</li>",
        "  <li><a href=\"http://www.questiontools.org/\">Questiontools Suite</a>: extensive test generation suite, but commercial for companies</li>",
        "</ul>",
      }
    }
  );
  m.push_back(
    { "ToolHometrainerVcl",
      {
        "<p><a href=\"ToolHometrainerVcl.htm\">Hometrainer (VCL)</a> is <a href=\"CppDesktopApplication.htm\">desktop</a> <a href=\"Tools.htm\">tool</a> ",
        "to train self-made exercises with open questions and multiple choice questions, ",
        "with or without images. The exercises can created by use of a simple text editor (Notepad, for example). ",
        "<a href=\"ToolHometrainerVcl.htm\">Hometrainer (VCL)</a> can also be used for examination.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Simple example of Hometrainer in creating exercises</h2>",
        "<p>&nbsp;</p>",
        "<p>Supply the program with a text file like shown below (note that the first line is obligatory):</p>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "Hometrainer (C) 2009-2014 Richel Bilderbeek<br/>",
        "Humanbody.bmp,Which line points to the liver?,1,2,3,4<br/>",
        "Humanbody.bmp,Which line points to the liver?,1/one/One<br/>",
        "Humanbody.bmp,Which organ does line 1 point to?,The liver/the liver/Liver/liver<br/>",
        "-,In which organ is ethanol detoxified?,The liver/the liver/Liver/liver<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p>The program will show you the image, the question and the (shuffled) answers. You have to click the right answer. Great to train yourself in nearly anything!</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Screenshots</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolHometrainer_1_8.png\">View a screenshot of 'Hometrainer' (version 1.8)(png)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolHometrainerMenu_1_8.png\">View a screenshot of 'Hometrainer' its main menu (version 1.8)(png)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolHometrainerTestCreater_1_8.png\">View a screenshot of 'Hometrainer Test Creater' (version 1.8)(png)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolHometrainerResult_1_8.png\">View a screenshot of 'Hometrainer' its generated test result (version 1.8)(png)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolHometrainerTestScorer_1_8.png\">View a screenshot of 'Hometrainer Test Scorer' (version 1.8)(png)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolHometrainerTestScorer_1_8_2.png\">View another screenshot of 'Hometrainer Test Scorer' (version 1.8)(png)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolHometrainerCreateDoc_1_8.png\">View a screenshot of 'Hometrainer Doc Creater' (version 1.8)(png)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Hometrainer executable and source</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>Newer: <a href=\"ToolHometrainer.htm\">Hometrainer</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/> <a href=\"ToolHometrainerExe_1_8.zip\">Download the 'Hometrainer' executable (version 1.8)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Hometrainer manual</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolHometrainerManual.doc\">Download the 'Hometrainer' manual (English)(version 0.5)(doc)</a></li>",
        "  <li>Download the 'Hometrainer' manual (Dutch)(doc)</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>English Hometrainer exercises</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>None yet</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Dutch Hometrainer exercises</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolHometrainer_BiBb1_1_0.zip\">Nectar BB hoofdstuk 1: Vier Rijken (version 1.0)</a></li>",
        "  <li><a href=\"ToolHometrainer_BiBb5_1_1.zip\">Nectar BB hoofdstuk 5: Mens En Milieu (version 1.1)</a></li>",
        "  <li><a href=\"ToolHometrainer_BiBb6_1_0.zip\">Nectar BB hoofdstuk 6: Eten (version 1.0)</a></li>",
        "  <li><a href=\"ToolHometrainer_BiBk1_1_1.zip\">Nectar KB hoofdstuk 1: Vier Rijken Vergelijken (version 1.1)</a></li>",
        "  <li><a href=\"ToolHometrainer_BiKb6_1_2.zip\">Nectar KB hoofdstuk 6: Ademen en eten (version 1.2)</a></li>",
        "  <li><a href=\"ToolHometrainer_BiKb7_1_0.zip\">Nectar KB hoofdstuk 7: Bloed (version 1.2)</a></li>",
        "  <li><a href=\"ToolHometrainer_NaskTl1_v1_3.zip\">Nova 3TL hoofdstuk 1: Electriciteit (version 1.3)(zip)</a></li>",
        "  <li><a href=\"ToolHometrainer_TtBasis_1_2.zip\">Theatertechniek: Basis (version 1.2)(zip)</a></li>",
        "  <li><a href=\"ToolHometrainer_TtGeluid_0_9.zip\">Theatertechniek: Geluidstechniek (version 0.9)(zip)</a></li>",
        "  <li><a href=\"ToolHometrainer_TtLicht_0_9.zip\">Theatertechniek: Lichttechniek (version 0.9)(zip)</a></li>",
        "  <li><a href=\"ToolHometrainer_WijkenArnhem_1_0.zip\">Wijken van Arnhem (version 1.0)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Old versions of Dutch Hometrainer exercises</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolHometrainer_BiBb5_1_0.zip\">Nectar BB hoofdstuk 5: Mens En Milieu (version 1.0)</a></li>",
        "  <li><a href=\"ToolHometrainer_BiKb6_0_3.zip\">Nectar KB hoofdstuk 6: Ademen en eten (version 0.3)</a></li>",
        "  <li><a href=\"ToolHometrainer_BiKb6_1_0.zip\">Nectar KB hoofdstuk 6: Ademen en eten (version 1.0)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older Hometrainer versions</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/> <a href=\"ToolHometrainer_0_9.png\">View a screenshot of 'Hometrainer' (version 0.9)(png)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Hometrainer manual versions</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>Version X.Y: DD-MM-YYYY</li>",
        "  <li>Version 0.5: 23-09-2009</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Links to similar freeware programs</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolHometrainer.htm\">Hometrainer</a> (my previous version of Hometrainer)</li>",
        "  <li><a href=\"http://wordfox.byethost17.com/wordfox/index.php\">WordFox</a></li>",
        "  <li><a href=\"http://www.efkasoft.com/drillassistant/drillassistant.html\">Drill Assistant</a></li>",
        "  <li><a href=\"http://www.efkasoft.com/overhoor/overhoor.html\">Overhoor</a>: Dutch</li>",
        "  <li><a href=\"http://www.luziusschneider.com/QuizHome.htm\">Quiz</a>: for multiple-choice questions only</li>",
        "  <li><a href=\"http://www.questiontools.org/\">Questiontools Suite</a>: extensive test generation suite, but commercial for companies</li>",
        "</ul>",
      }
    }
  );
  m.push_back(
    { "ToolImageRotater",
      {
        "<p>",
        "  Finally, after 17 years of trying once-in-a-while, I've managed to create a",
        "  simple <a href=\"Tools.htm\">tool</a> to rotate an image under any angle.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  There are multiple editions:",
        "</p>",
        "<ul>",
        "  <li><a href=\"ToolImageRotater.htm\">ImageRotater</a></li>",
        "  <li><a href=\"ToolImageRotaterClx.htm\">ImageRotater (CLX)</a></li>",
        "  <li><a href=\"ToolImageRotaterVcl.htm\">ImageRotater (VCL)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolImageRotater_2_0.png\">View a screenshot of Image Rotater (png)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>And, yes, the spelling error is intended: I wanted to Dutchify the name of the program.</p>",
      }
    }
  );
  m.push_back(
    { "ToolImageRotaterClx",
      {
        "<p>",
        "  Finally, after 17 years of trying once-in-a-while, I've managed to create a",
        "  simple <a href=\"Tools.htm\">tool</a> to rotate an image under any angle.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  There are multiple editions:",
        "</p>",
        "<ul>",
        "  <li><a href=\"ToolImageRotater.htm\">ImageRotater</a></li>",
        "  <li><a href=\"ToolImageRotaterClx.htm\">ImageRotater (CLX)</a></li>",
        "  <li><a href=\"ToolImageRotaterVcl.htm\">ImageRotater (VCL)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolImageRotaterClx_1_0.png\">View a screenshot of Image Rotater (CLX edition)(png)</a></li>",
        "  <li><a href=\"ToolImageRotaterClxExe.zip\">Download the 'Image Rotater (CLX edition)' Windows executable (zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>",
        "  And, yes, the spelling error is intended: I wanted to Dutchify the name of the program.",
        "</p>",
      }
    }
  );
  m.push_back(
    { "ToolImageRotaterVcl",
      {
        "<p>",
        "  Finally, after 17 years of trying once-in-a-while, I've managed to create a",
        "  simple <a href=\"Tools.htm\">tool</a> to rotate an image under any angle.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  There are multiple editions:",
        "</p>",
        "<ul>",
        "  <li><a href=\"ToolImageRotater.htm\">ImageRotater</a></li>",
        "  <li><a href=\"ToolImageRotaterClx.htm\">ImageRotater (CLX)</a></li>",
        "  <li><a href=\"ToolImageRotaterVcl.htm\">ImageRotater (VCL)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolImageRotaterVcl_1_0.png\">View a screenshot of Image Rotater (VCL edition)(png)</a></li>",
        "  <li><a href=\"ToolImageRotaterVclExe.zip\">Download the 'Image Rotater (VCL edition)' Windows executable (zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>And, yes, the spelling error is intended: I wanted to Dutchify the name of the program.</p>",
      }
    }
  );

  m.push_back(
    { "ToolItsBelcampo",
      {
        "<p>A simple tool that converts It's Learning email adresses to Belcampo email adresses (as used in GroupWise).</p>",
        "<p>&nbsp;</p>",
        "<p>* <a href=\"ToolItsBelcampoScreenshot.png\">View a screenshot of 'It's Belcampo'</a>.</p>",
        "<p>* <a href=\"ToolItsBelcampoSource.rar\">Download the 'It's Belcampo' source code</a>.</p>",
        "<p>* <a href=\"ToolItsBelcampoExe.rar\">Download the 'It's Belcampo' Windows executable (rar)</a>.</p>",
        "<p>* <a href=\"ToolItsBelcampoExe.zip\">Download the 'It's Belcampo' Windows executable (zip)</a>.</p>",
      }
    }
  );
  m.push_back(
    { "ToolKalmanFilterer",
      {
        "<p><a href=\"ToolKalmanFilterer.htm\">KalmanFilterer</a> is a <a href=\"Tools.htm\">tool</a> to learn to work",
        "with <a href=\"CppKalmanFilter.htm\">Kalman filters</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolKalmanFilterer_1_11.png\">View a screenshot of 'KalmanFilterer' (version 1.11)(png)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolKalmanFilterer_1_4.png\">View a screenshot of 'KalmanFilterer' (version 1.4)(png)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolKalmanFiltererExe_1_9.zip\">Download a Windows executable of 'KalmanFilterer' (version 1.9)(zip)</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/> <a href=\"ToolKalmanFiltererSource_1_11.zip\">Download the 'KalmanFilterer' source code (version 1.11)(zip)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolKalmanFiltererSource_1_11.htm\">View the 'KalmanFilterer' source code as web page (version 1.11)(htm)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolKalmanFilterer_1_9.png\">View a screenshot of 'KalmanFilterer' (version 1.9)(png)</a></li>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolKalmanFilterer_1_6.png\">View a screenshot of 'KalmanFilterer' (version 1.6)(png)</a></li>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolKalmanFilterer_1_5.png\">View a screenshot of 'KalmanFilterer' (version 1.5)(png)</a></li>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolKalmanFilterer_1_3.png\">View a screenshot of 'KalmanFilterer' (version 1.3)(png)</a></li>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolKalmanFilterer_1_2.png\">View a screenshot of 'KalmanFilterer' (version 1.2)(png)</a></li>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolKalmanFilterer_1_1.png\">View a screenshot of 'KalmanFilterer' (version 1.1)(png)</a></li>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolKalmanFilterer_1_0.png\">View a screenshot of 'KalmanFilterer' (version 1.0)(png)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"CppReferences.htm\">References</a></h2>",
        "<p>&nbsp;</p>",
        "<ol>",
        "  <li><a href=\"https://en.wikipedia.org/wiki/Kalman_filter\">Wikipedia page about the Kalman filter</a></li>",
        "  <li><a href=\"http://academic.csuohio.edu/simond/estimation\">Kalman filter examples (in Matlab)</a></li>",
        "  <li><a href=\"http://greg.czerniak.info/guides/kalman1/\">Kalman filter tutorial by Greg Czerniak</a></li>",
        "</ol>",
      }
    }
  );
  m.push_back(
    { "ToolKeySender",
      {
        "<p><a href=\"ToolKeySender.htm\">KeySender</a> is a demonstration tool of ",
        "<a href=\"http://www.codeproject.com/KB/cpp/sendkeys_cpp_Article.aspx\">Lallous' CSendKey class</a> ",
        "with which you can send virtual key presses to any window. ",
        "For example, you can let <a href=\"ToolKeySender.htm\">KeySender</a> type a",
        "notepad document for you (as seen in the screenshot).</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolKeySender_1_0.png\">View a screenshot of 'KeySender' (version 1.0)(png)</a></li>",
        "  <li><a href=\"ToolKeySenderExe_1_0.zip\">Download the 'KeySender' Windows executable (zip)</a></li>",
        "  <li><a href=\"ToolKeySenderSource_1_0.zip\">Download the 'KeySender' source code (zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>External links</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"http://www.codeproject.com/Articles/6819/SendKeys-in-C\">Lallous' article about his CSendKey class</a></li>",
        "</ul>",
      }
    }
  );
  m.push_back(
    { "ToolKTouchLectureCreator",
      {
        "<p><a href=\"ToolKTouchLectureCreator.htm\">KTouchLectureCreator</a> is a <a href=\"Tools.htm\">tool</a> to create random ",
        "KTouch lectures for a C++ programmer.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolKTouchLectureCreatorLecture.zip\">Download a lecture created by 'KTouchLectureCreator' (zip)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolKTouchLectureCreatorSource_1_0.zip\">Download the 'KTouchLectureCreator' source code (version 1.0)(zip)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolKTouchLectureCreatorSource_1_0.htm\">View the 'KTouchLectureCreator' source code as web page (version 1.0)(htm)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>External links</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"http://ktouch.sourceforge.net\">KTouch homepage</a></li>",
        "</ul>",
      }
    }
  );

  m.push_back(
    { "ToolLambdaBot",
      {
        "<p>",
        "  <a href=\"ToolLambdaBot.htm\">LambdaBot</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to demonstrate an IRC bot.",
        "</p>",
      }
    }
  );
  m.push_back(
    { "ToolLearyCircumplex",
      {
        "<p><a href=\"ToolLearyCircumplex.htm\">LearyCircumplex</a> is a <a href=\"Tools.htm\">tool</a> to ",
        "generate an image of a Leary circumplex (also called 'Interpersonal circumplex' or 'Leary circle' or ",
        "(in Dutch) 'Roos van Leary') after having scored the results of a questionaire.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolLearyCircumplex_1_0.png\">View a screenshot of 'Leary Circumplex' (version 1.0)(png)</a></li>",
        "  <li><a href=\"ToolLearyCircumplexExe_1_0.zip\">Download the 'Leary Circumplex' Windows executable (version 1.0)(zip)</a></li>",
        "  <li><a href=\"ToolLearyCircumplexSource_1_0.zip\">Download the 'Leary Circumplex' source code (version 1.0)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>External links</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"http://en.wikipedia.org/wiki/Interpersonal_Circumplex\">Wikipedia's page on 'Interpersonal Circumplex'</a></li>",
        "</ul>",
      }
    }
  );
  m.push_back(
    { "ToolLogisticGrowthSimulator",
      {
        "<p><a href=\"ToolLogisticGrowthSimulator.htm\">Logistic Growth Simulator</a> shows population",
        "sizes in time for the logistic growth equation. On the press of a button, it also",
        "shows a Feigenbaum diagram.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolLogisticGrowthSimulator_1_0.png\">View a screenshot of 'Logistic Growth Simulator' (version 1.0)(png)</a></li>",
        "  <li><a href=\"ToolLogisticGrowthSimulatorExe_1_0.zip\"> Download the 'Logistic Growth Simulator' Windows executable (version 1.0)(zip)</a></li>",
        "  <li><a href=\"ToolLogisticGrowthSimulatorSource_1_0.zip\"> Download the 'Logistic Growth Simulator' source code (version 1.0)(zip)</a></li>",
        "</ul>",
      }
    }
  );
  m.push_back(
    { "ToolLoose",
      {
        "<p><a href=\"ToolLoose.htm\">Loose</a> is a <a href=\"Tools.htm\">tool</a> to redirect any email adress name ",
        "to the limited number of email addresses an email host has. In its current demonstrational form, ",
        "the company 'frameless.com' is used with four virtual email recipients.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Download</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolLoose_2_0.png\">View a 'Loose' screenshot (version 2.0)(png)</a></li>",
        "  <li><a href=\"ToolLooseSource_2_0.zip\">Download the 'Loose' Qt Creator project (version 2.0)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolLoose_1_0.png\">View a 'Loose' screenshot (version 1.0)(png)</a></li>",
        "  <li><a href=\"ToolLoose.ogv\">View a 'Loose' demonstration (version 1.0)(ogv (works in Google Chrome))</a></li>",
        "  <li><a href=\"ToolLooseSource_1_1.zip\">Download the 'Loose' Qt Creator project (version 1.1)(zip)</a></li>",
        "  <li><a href=\"ToolLooseSource_1_0.zip\">Download the 'Loose' Qt Creator project (version 1.0)(zip)</a></li>",
        "</ul>",
      }
    }
  );
  m.push_back(
    { "ToolMazeCreator",
      {
        "<p>",
        "  <a href=\"ToolMazeCreator.htm\">MazeCreator</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to demonstrate <a href=\"CppCreateMaze.htm\">my simple maze generation algorithm</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/> <a href=\"ToolMazeCreator_2_0.png\">View a screenshot of 'Maze Creator' (v. 2.0)</a></li>",
        "</ul>",
      }
    }
  );
  m.push_back(
    { "ToolMazeCreatorVcl",
      {
        "<p>",
        "  <a href=\"ToolMazeCreatorVcl.htm\">MazeCreator (VCL)</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to demonstrate <a href=\"CppCreateMaze.htm\">my simple maze generation algorithm</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"ToolMazeCreatorVcl.htm\">MazeCreator (VCL)</a> is the predecessor of",
        "  <a href=\"ToolMazeCreator.htm\">MazeCreator</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/> <a href=\"ToolMazeCreator_1_0.png\">View a screenshot of 'Maze Creator (VCL)' (v. 1.0)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/> <a href=\"ToolMazeCreatorExe_1_0.zip\">Download the 'Maze Creator (VCL)' Windows executable (v. 1.0)(zip)</a></li>",
        "</ul>",
      }
    }
  );

  m.push_back(
    { "ToolMidiLessonCreator",
      {
        "<p>",
        "  <a href=\"ToolMidiLessonCreator.htm\">MidiLessonCreator</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to create MIDI lessons.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolMorpher",
      {
        "<p><a href=\"ToolMorpher.htm\">Morpher</a> is a <a href=\"Tools.htm\">tool</a> to generate intermediate images between two",
        "images, <a href=\"ToolMorpherExample.png\">as shown in this example</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolMorpherExample.png\">View an example of a morphed image (png)</a></li>",
        "  <li><a href=\"ToolMorpher_1_0.png\">View a screenshot of 'Morpher' (version 1.0)(png)</a></li>",
        "  <li><a href=\"ToolMorpherExe_1_0.zip\">Download the 'Morpher' Windows executable (version 1.0)(zip)</a></li>",
        "  <li><a href=\"ToolMorpherSource_1_0.zip\">Download the 'Morpher' source code (version 1.0)(zip)</a></li>",
        "</ul>",
      }
    }
  );
  m.push_back(
    { "ToolMultiEncranger",
      {
        "<p>",
        "  <a href=\"ToolMultiEncranger.htm\">MultiEncranger</a> is a <a href=\"Tools.htm\">tool</a>",
        "  and a multi-line version of <a href=\"ToolEncranger.htm\">Encranger</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>...</li>",
        "</ul>",
      }
    }
  );
  m.push_back(
    { "ToolMultiEncrangerVcl",
      {
        "<p>",
        "  <a href=\"ToolMultiEncrangerVcl.htm\">MultiEncranger (VCL)</a> is a <a href=\"Tools.htm\">tool</a>",
        "  and a multi-line version of <a href=\"ToolEncranger.htm\">Encranger</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"ToolMultiEncrangerVcl.htm\">MultiEncranger (VCL)</a> is the predecessor of",
        "  <a href=\"ToolMultiEncranger.htm\">MultiEncranger</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolMultiEncranger_1_0.png\">View a screenshot of 'MultiEncranger' (version 1.0)(png)</a></li>",
        "  <li><a href=\"ToolMultiEncrangerExe_1_0.zip\">Download the 'MultiEncranger' Windows executable (version 1.0)(zip)</a></li>",
        "</ul>",
      }
    }
  );
  m.push_back(
    { "ToolMusicTheory",
      {
        "<p><a href=\"ToolMusicTheory.htm\">MusicTheory</a> is a <a href=\"Tools.htm\">tool</a> to visualize my music theory.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/> <a href=\"ToolMusicTheory_1_0.png\">View a screenshot of 'MusicTheory' (version 1.0)(png)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicWindows.png\" alt=\"Windows\"/> <a href=\"ToolMusicTheoryExe_1_1.zip\">Download the Windows executable of 'MusicTheory' (version 1.1)(zip)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolMusicTheorySource_1_1.zip\">Download the 'MusicTheory' source code (version 1.1)(zip)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolMusicTheorySource_1_0.htm\">View the 'MusicTheory' source code as web page (version 1.0)(htm)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolMusicTheory_0_1.png\">View a screenshot of the menu screen of 'MusicTheory' (version 0.1)(png)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolMusicTheorySource_1_1.zip\">Download the 'MusicTheory' source code (version 1.1)(zip)</a></li>",
        "</ul>",
      }
    }
  );
  m.push_back(
    { "ToolNdsmake",
      {
        "<p><a href=\"ToolNdsmake.htm\">ndsmake</a> is a <a href=\"Tools.htm\">tool</a> ",
        "to generate an <a href=\"CppNds.htm\">NDS</a> <a href=\"CppMakefile.htm\">makefile</a> ",
        "from a <a href=\"CppQtCreator.htm\">Qt Creator</a> <a href=\"CppQtProjectFile.htm\">project file</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolNdsmakeUse_1_0.png\">Where to call ndsmake in Qt Creator (version 1.0)(png)</a></li>",
        "  <li><a href=\"ToolNdsmakeSource_1_2.zip\">Download the Qt Creator project 'ndsmake' (version 1.2)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolNdsmakeSource_1_1.zip\">Download the Qt Creator project 'ndsmake' (version 1.1)(zip)</a></li>",
        "  <li><a href=\"ToolNdsmakeSource_1_0.zip\">Download the Qt Creator project 'ndsmake' (version 1.0)(zip)</a></li>",
        "  <li><a href=\"ToolNdsmakeQtCreator.png\">Where to call ndsmake in Qt Creator (png)</a></li>",
        "  <li><a href=\"ToolNdsmakeSource_0_1.zip\">Download the Qt Creator project 'Ndsmake' (version 0.1)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"ToolNdsmake.htm\">ndsmake</a> history</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>YYYY-MM-DD: version X.Y: [description]</li>",
        "  <li>2010-12-19: version 1.2: use of Ndsmake class</li>",
        "  <li>2010-12-19: version 1.1: added extra commands, use of ProFile class</li>",
        "  <li>2010-10-13: version 1.0: initial release, works from Qt Creator, tested by TestNdsmake</li>",
        "  <li>2010-10-10: version 0.1: incomplete, could not be run from Qt Creator</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"ToolNdsmake.htm\">ndsmake</a> wishlist</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>Calling <a href=\"ToolNdsmake.htm\">ndsmake</a> from Qt Creator project file</li>",
        "  <li>Support multi-unit projects</li>",
        "  <li>Support multi-folder projects</li>",
        "  <li>Support graphics compiling (with devkitPro's grit)</li>",
        "  <li>Support debugging from Qt Creator IDE</li>",
        "</ul>",
      }
    }
  );

  m.push_back(
    { "ToolNdsPaint",
      {
        "<p>",
        "  <a href=\"ToolNdsPaint.htm\">NdsPaint</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to draw images on an NDS.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>...</li>",
        "</ul>",
      }
    }
  );

  m.push_back(
    { "ToolPaperRockScissors", // || m_page_name == "CppPaperRockScissors",
      {
        "<p>This simulation shows pure paper-rock-scissors players competing on a",
        "two-dimensional grid (a donut-shaped world). Each time step, a random pixel is",
        "chosen (that is, either a paper, rock or scissors player) and a random",
        "neighbor. If one beats the other, the winner's strategy replaces the loser's",
        "pixel.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolPaperRockScissorsScreenshot.png\">View a screenshot of 'ToolPaperRockScissors' (png)</a></li>",
        "  <li><a href=\"ToolPaperRockScissorsExe.zip\">Download the Windows executable of 'ToolPaperRockScissors' (zip)</a></li>",
        "  <li><a href=\"ToolPaperRockScissorsSource.zip\">Download the 'ToolPaperRockScissors' source code (zip)</a>.</li>",
        "</ul>",
      }
    }
  );
  m.push_back(
    { "ToolPause",
      {
        "<p><a href=\"ToolPause.htm\">Pause</a> is a <a href=\"Tools.htm\">tool</a> whose purpose it is to do nothing.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ToolPause.htm\">Pause</a> is programmed in <a href=\"Cpp.htm\">C++</a> using <a href=\"CppQt.htm\">Qt Creator</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolPause_1_0.png\">View a screenshot of 'Pause' (version 1.0)(png)</a></li>",
        "  <li><a href=\"ToolPauseSource_1_0.zip\">Download the 'Pause' source code (version 1.0)(zip)</a></li>",
        "  <li><a href=\"ToolPauseSource_1_0.htm\">View the 'Pause' source code as web page (version 1.0)(htm)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Version history</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>V X.Y: YYYY-MM-DD: description</li>",
        "  <li>V 1.0: 2010-08-18: initial version</li>",
        "</ul>",
      }
    }
  );
  m.push_back(
    { "ToolPerfectElasticCollision",
      {
        "<p><a href=\"ToolPerfectElasticCollision.htm\">PerfectElasticCollision</a> is a <a href=\"Tools.htm\">tool</a> to investigate the impulses of a perfect elastic collision.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ToolPerfectElasticCollision.htm\">PerfectElasticCollision</a> is programmed using the <a href=\"CppQt.htm\">Qt Creator</a> <a href=\"CppIde.htm\">IDE</a>, using the <a href=\"CppBoost.htm\">Boost</a>, <a href=\"CppQt.htm\">QT</a> and <a href=\"CppStl.htm\">STL</a> <a href=\"CppLibrary.htm\">libraries</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolPerfectElasticCollision_1_0.png\">View a 'PerfectElasticCollision' screenshot (v.1.0)(png)</a></li>",
        "  <li><a href=\"ToolPerfectElasticCollisionSource_1_0.zip\">Download the 'PerfectElasticCollision' source code (v.1.0)(zip)</a></li>",
        "  <li><a href=\"ToolPerfectElasticCollisionSourceExeWindows_1_0.zip\">Download the 'PerfectElasticCollision' Windows executable (v.1.0)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>The <a href=\"CppWindows.htm\">Windows</a> executable of version 1.0 is created following ",
        "<a href=\"CppQtCrosscompileToWindowsExample15.htm\">how to cross-compile a Qt Creator project from Ubuntu to a windows executable: example 15: MinGW cross-compiling environment</a>.</p>",
      }
    }
  );
  m.push_back(
    { "ToolPicToCode",
      {
        "<p><a href=\"ToolPicToCode.htm\">PicToCode</a> is a <a href=\"Tools.htm\">tool</a> to convert pictures to ",
        "<a href=\"Cpp.htm\">C++</a> code.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolPicToCode_1_3.png\">View a 'PicToCode' screenshot (version 1.3)(png)</a></li>",
        "  <li><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolPicToCode_1_2.png\">View a 'PicToCode' screenshot (version 1.2)(png)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolPicToCodeSource_1_3.zip\">Download the 'PicToCode' source code (version 1.3)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolPicToCodeSource_1_2.zip\">Download the 'PicToCode' source code (version 1.2)(zip)</a></li>",
        "  <li><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolPicToCode_1_0.png\">View a 'PicToCode' screenshot (version 1.0)(png)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolPicToCodeSource_1_1.zip\">Download the 'PicToCode' source code (version 1.1)(zip)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolPicToCodeSource_1_0.zip\">Download the 'PicToCode' source code (version 1.0)(zip)</a></li>",
        "</ul>",
      }
    }
  );
  m.push_back(
    { "ToolPixelator",
      {
        "<p>",
        "  <a href=\"ToolPixelator.htm\">Pixelator</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to 'pixelate' images.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>...</li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ToolPixelatorVcl",
      {
        "<p>",
        "  <a href=\"ToolPixelatorVcl.htm\">Pixelator (VCL)</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to 'pixelate' images.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"ToolPixelatorVcl.htm\">Pixelator (VCL)</a> is the predecessor of",
        "  <a href=\"ToolPixelator.htm\">Pixelator</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolPixelator_1_0.png\">View a screenshot of 'Pixelator'</a></li>",
        "  <li><a href=\"ToolPixelatorExe.zip\">Download the 'Pixelator' Windows executable (zip)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ToolQuadraticSolver",
      {
        "<p><a href=\"ToolQuadraticSolver.htm\">QuadraticSolver</a> is a (console) <a href=\"Tools.htm\">tool</a> to solve quadratic equations.</p>",
        "<p>&nbsp;</p>",
        "<p>I felt obliged to program this <a href=\"Tools.htm\">tool</a>, as a counterweight",
        "to <a href=\"http://www.perpetualpc.net/quadsolv_c.html\">PerpetualPC's terribly",
        "coded quadratic solver</a>.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ToolQuadraticSolver.htm\">QuadraticSolver</a> uses the ",
        "<a href=\"CppFunction.htm\">function</a> <a href=\"CppSolveQuadratic.htm\">SolveQuadratic</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolQuadraticSolver_1_0.png\">View a screenshot of 'QuadraticSolver'</a></li>",
        "  <li><a href=\"ToolQuadraticSolverExe_1_0.zip\">Download the 'QuadraticSolver' Windows executable (zip)</a></li>",
        "  <li><a href=\"ToolQuadraticSolverSource_1_0.zip\">Download the 'QuadraticSolver' source code (zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>External links</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"http://en.wikipedia.org/wiki/Quadratic_equation\">Wikipedia's page about quadratic equations</a></li>",
        "  <li><a href=\"http://www.perpetualpc.net/quadsolv_c.html\">PerpetualPC showing how NOT to do it</a></li>",
        "</ul>",
      }
    }
  );
  m.push_back(
    { "ToolRandomCode",
      {
        "<p>",
        "  <a href=\"ToolRandomCode.htm\">RandomCode</a> is a simple <a href=\"Tools.htm\">tool</a>",
        "  that creates random C++ code. I wrote it for the forums I visited: when",
        "  somebody was begging for code ('Coult u pleaz gimme code 4 peer2peer programm?'), I",
        "  posted a piece of random generated code with the comment 'Here it is, it just",
        "  needs to have some bugs fixed!'. Programmers' humor is great, isn't it?",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolRandomCode_3_0.png\">View a screenshot of 'Random Code' (Web application)(version 3.0)(png)</a></li>",
        "  <li><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/> <a href=\"ToolRandomCode_2_0.png\">View a screenshot of 'Random Code' (version 2.0)(png)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/> <a href=\"ToolRandomCodeExeWindows_3_0.zip\">Download the 'Random Code' Windows executable (version 3.0)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>The <a href=\"CppWindows.htm\">Windows</a> executable of version 3.0 is created following ",
        "<a href=\"CppQtCrosscompileToWindowsExample15.htm\">how to cross-compile a Qt Creator project from Ubuntu to a windows executable: example 15: MinGW cross-compiling environment</a>.</p>"
      }
    }
  );

  m.push_back(
    { "ToolRandomCodeVcl",
      {
        "<p>",
        "  <a href=\"ToolRandomCodeVcl.htm\">RandomCode (VCL)</a> is a simple <a href=\"Tools.htm\">tool</a>",
        "  that creates random C++ code and is the predecessor of <a href=\"ToolRandomCode.htm\">RandomCode</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/> <a href=\"ToolRandomCode_1_0.png\">View a screenshot of 'Random Code' (version 1.0)(png)</a></li>",
        "  <li><a href=\"ToolRandomCodeExeWindows_1_0.zip\">Download the 'Random Code' Windows executable (version 1.0)(zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "ToolRasper",
      {
        "<p><a href=\"ToolRasper.htm\">Rasper</a> is a web application <a href=\"Tools.htm\">tool</a> to toggle the ",
        "<a href=\"CppRpi.htm\">Raspberry Pi</a> its GPIO ports.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicRaspbian.png\" alt=\"Raspbian\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolRasper_0_3.png\">View a screenshot of 'Rasper' (version 0.3)(png)</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/> <a href=\"ToolRasperSource_0_3.zip\">Download the 'Rasper' source code (version 0.3)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/> <a href=\"ToolRasperSource_0_2.zip\">Download the 'Rasper' source code (version 0.2)(zip)</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/> <a href=\"ToolRasperSource_0_1.zip\">Download the 'Rasper' source code (version 0.1)(zip)</a></li>",
        "</ul>",
      }
    }
  );
  m.push_back(
    { "ToolRectFitter",
      {
        "<p><a href=\"ToolRectFitter.htm\">RectFitter</a> is a <a href=\"Tools.htm\">tool</a> to demonstrate how to fit rectangles within a rectangle.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ToolRectFitter.htm\">RectFitter</a> is programmed in <a href=\"Cpp.htm\">C++</a> using the <a href=\"CppIde.htm\">IDE</a> <a href=\"CppBuilder.htm\">C++ Builder</a> 6.0. It uses the <a href=\"CppStl.htm\">STL</a>, <a href=\"CppVcl.htm\">VCL</a> and <a href=\"CppBoost.htm\">Boost</a> <a href=\"CppLibrary.htm\">libraries</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolRectFitter_1_0.png\">View a screenshot of 'RectFitter' (version 1.0)</a></li>",
        "  <li><a href=\"ToolRectFitterExe_1_0.zip\">Download the 'RectFitter' Windows executable (version 1.0)(zip)</a></li>",
        "  <li><a href=\"ToolRectFitterSource_1_0.zip\">Download the 'RectFitter' source code (version 1.0)(zip)</a></li>",
        "  <li><a href=\"ToolRectFitterSource_1_0.htm\">View the 'RectFitter' source code as a web page (version 1.0)(htm)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"ToolRectFitter.htm\">RectFitter</a> history</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>Version X.Y: YYYY-MM-DD: [description]</li>",
        "  <li>Version 1.0: 2008-12-02: initial version</li>",
        "</ul>",
      }
    }
  );
  m.push_back(
    { "ToolRefrigeratorPuzzleSolver",
      {
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "This type of puzzle is also called a monkey puzzle [1].<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p><a href=\"ToolRefrigeratorPuzzleSolver.htm\">Refrigerator Puzzle Solver</a> was programmed to solve a puzzle on my refrigerator. I had a bet with my girlfriend that I could find the solution quicker by writing a program, than her trying by hand. I won (as one would expect, see 'Calcalute the number of configurations to test').</p>",
        "<p>&nbsp;</p>",
        "<ol>",
        "  <li><a href=\"ToolRefrigeratorPuzzleSolverPuzzle.png\">View a photo of the refrigerator puzzle (png)</a></li>",
        "  <li><a href=\"ToolRefrigeratorPuzzleSolver_1_0.png\">View a screenshot of 'Refrigerator Puzzle Solver' (png)</a></li>",
        "  <li><a href=\"ToolRefrigeratorPuzzleSolverExe_1_0.zip\">Download the 'Refrigerator Puzzle Solver' Windows executable (version 1.0)(zip)</a>.</li>",
        "  <li><a href=\"ToolRefrigeratorPuzzleSolverSource_1_0.zip\">Download the 'Refrigerator Puzzle Solver' source code (version 1.0)(zip)</a>.</li>",
        "</ol>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ToolRefrigeratorPuzzleSolver.htm\">Refrigerator Puzzle Solver</a> was programmed at the 28th of December of 2008 in <a href=\"Cpp.htm\">C++</a> using the IDE <a href=\"CppBuilder.htm\">C++ Builder</a> 6.0. It uses the <a href=\"CppStl.htm\">STL</a>, <a href=\"CppVcl.htm\">VCL</a> and <a href=\"CppBoost.htm\">Boost</a> <a href=\"CppLibrary.htm\">libraries</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Calculate the number of configurations to test</h2>",
        "<p>&nbsp;</p>",
        "<p>The nine puzzle pieces can be put in 9*8*7*6*5*4*3*2*1 = 9! = 362880 sequences.</p>",
        "<p>&nbsp;</p>",
        "<p>One puzzle piece has four orientations.</p>",
        "<p>&nbsp;</p>",
        "<p>For a certain sequence of the nine pieces, there are 4^9=262144 configurations.</p>",
        "<p>&nbsp;</p>",
        "<p>Therefore, the number of possibilities to test equals 362880 * 262144 = 95126814720.</p>",
        "<p>&nbsp;</p>",
        "<p>Because there four solutions of the puzzle (due to rotation) one expects to need to test 95126814720 / 4 = 23781703680 configurations. That is more then 23 billion configurations!</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>How the program solves the puzzle</h2>",
        "<p>&nbsp;</p>",
        "<p>The program starts with an ordering of the nine puzzle pieces.</p>",
        "<p>&nbsp;</p>",
        "<p>First, one or more puzzle pieces are rotated in a systematic way, as systematic as adding one to a four-digit number system.</p>",
        "<p>&nbsp;</p>",
        "<p>Second, these (rotated) puzzle pieces are put in a recursive function. This function takes a set of used and fitting puzzle pieces and a set of unused puzzle pieces. It tries to put an unused puzzle piece in the next place, trying all unused pieces. If successful, the function calls itself with the (new) set of used puzzle pieces and the (new) set of unused puzzle pieces. If the function fails, it returns an empty solution.</p>",
        "<p>&nbsp;</p>",
        "<p>Click on 'Display current' in the program to see the computer do this. Every try is shown for about 100 milliseconds, so one can actually see what happens.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"CppReferences.htm\">References</a></h2>",
        "<p>&nbsp;</p>",
        "<ol>",
        "  <li>David Harel. Computers Ltd.: What They Really Can't Do. 2000. ISBN-10: 0198505558.</li>",
        "</ol>",
      }
    }
  );
  m.push_back(
    { "ToolRegexTester",
      {
        "<p><a href=\"ToolRegexTester.htm\">RegexTester</a> is a <a href=\"Tools.htm\">tool</a> to test regular expressions ",
        "(using its <a href=\"CppGui.htm\">GUI</a>) and to demonstrate how to use the ",
        "<a href=\"CppRegex.htm\">boost::regex</a>, <a href=\"CppQRegExp.htm\">QRegExp</a> and <a href=\"CppRegex.htm\">std::regex</a>",
        "<a href=\"CppClass.htm\">classes</a> (in its code).</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<ul>",
        "  <li>",
        "    <img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQt.png\" alt=\"Qt\"/> ",
        "    <a href=\"ToolRegexTester_1_6.png\">View a screenshot of 'RegexTester' (version 1.6)(png)</a>",
        "  </li>",
        "  <li>",
        "    <img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQt.png\" alt=\"Qt\"/> ",
        "    <a href=\"ToolRegexTesterSource_1_6.zip\">Download the 'RegexTester' source code (version 1.6)(zip)</a>",
        "  </li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<ul>",
        "  <li><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQt.png\" alt=\"Qt\"/> <a href=\"ToolRegexTester_1_5.png\">View a screenshot of 'RegexTester' (version 1.5)(png)</a></li>",
        "  <li><img src=\"PicBoost.png\" alt=\"Boost\"/><img src=\"PicQt.png\" alt=\"Qt\"/> <a href=\"ToolRegexTesterSource_1_5.zip\">Download the 'RegexTester' source code (version 1.5)(zip)</a></li>",
        "  <li><img src=\"PicBoost.png\" alt=\"Boost\"/> <a href=\"ToolRegexTester_1_1.png\">View a screenshot of 'RegexTester' (version 1.1)(png)</a></li>",
        "  <li><img src=\"PicBoost.png\" alt=\"Boost\"/> <a href=\"ToolRegexTesterSource_1_2.zip\">Download the 'RegexTester' source code (version 1.2)(zip)</a></li>",
        "  <li><a href=\"ToolRegexTesterSource_1_1.zip\">Download the 'RegexTester' source code (version 1.1)(zip)</a></li>",
        "  <li><a href=\"ToolRegexTester_1_0.png\">View a screenshot of 'RegexTester' (version 1.0)(png)</a></li>",
        "  <li><a href=\"ToolRegexTesterSource_1_0.zip\">Download the 'RegexTester' source code (version 1.0)(zip)</a></li>",
        "</ul>",
      }
    }
  );

  m.push_back(
    { "ToolRichelBilderbeekGallery",
      {
        "<p>",
        "  <a href=\"ToolRichelBilderbeekGallery.htm\">RichelBilderbeekGallery</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to create the galleries on this website.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolRichelbilderbeekNlSitemapGenerator",
      {
        "<p><a href=\"ToolRichelbilderbeekNlSitemapGenerator.htm\">RichelbilderbeekNlSitemapGenerator</a> is a <a href=\"Tools.htm\">tool</a> to generate the sitemap of my site.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ToolRichelbilderbeekNlSitemapGenerator.htm\">RichelbilderbeekNlSitemapGenerator</a> is programmed in <a href=\"Cpp.htm\">C++</a> using <a href=\"CppQtCreator.htm\">Qt Creator</a> 2.0.0. It uses the <a href=\"CppBoost.htm\">Boost</a>, <a href=\"CppQt.htm\">Qt</a> and <a href=\"CppStl.htm\">STL</a> <a href=\"CppLibrary.htm\">libraries</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>Version 1.0 of <a href=\"ToolRichelbilderbeekNlSitemapGenerator.htm\">RichelbilderbeekNlSitemapGenerator</a> was programmed in <a href=\"Cpp.htm\">C++</a> using  <a href=\"CppBuilder.htm\">C++ Builder</a> 6.0. It uses the <a href=\"CppStl.htm\">STL</a>, <a href=\"CppVcl.htm\">VCL</a> and <a href=\"CppBoost.htm\">Boost</a> <a href=\"CppLibrary.htm\">libraries</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolRichelbilderbeekNlSitemapGenerator_2_0.png\">View a screenshot of RichelbilderbeekNlSitemapGenerator' (v. 2.0)</a></li>",
        "  <li><a href=\"ToolRichelbilderbeekNlSitemapGeneratorSource_2_0.zip\">Download the 'RichelbilderbeekNlSitemapGenerator' source code (v. 2.0)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"ToolRichelbilderbeekNlSitemapGenerator.htm\">RichelbilderbeekNlSitemapGenerator</a> history</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>YYYY-MM-DD: version X.Y: [description]</li>",
        "  <li>2009-08-26: version 1.0: Initial Windows version, programmed in <a href=\"CppBuilder.htm\">C++ Builder</a></li>",
        "  <li>2010-08-08: version 2.0: <a href=\"ToolRichelbilderbeekNlSitemapGenerator.htm\">RichelbilderbeekNlSitemapGenerator</a> is now cross-platform, programmed in <a href=\"CppQtCreator.htm\">Qt Creator</a> and generates the files it needs itself</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"ToolRichelbilderbeekNlSitemapGenerator.htm\">RichelbilderbeekNlSitemapGenerator</a> older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolRichelbilderbeekNlSitemapGeneratorExe_1_0.zip\">Download the 'RichelbilderbeekNlSitemapGenerator' Windows executable (v. 1.0)(zip)</a></li>",
        "  <li><a href=\"ToolRichelbilderbeekNlSitemapGeneratorSource_1_0.zip\">Download the 'RichelbilderbeekNlSitemapGenerator' source code (v. 1.0)(zip)</a></li>",
        "</ul>",
      }
    }
  );
  m.push_back(
    { "ToolSecretMessage",
      {
        "<p>",
        "  <a href=\"ToolSecretMessage.htm\">SecretMessage</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to add a secret message to an image. These secret messages",
        "  can also be extracted again.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>...</li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "ToolSecretMessageVcl",
      {
        "<p>",
        "  <a href=\"ToolSecretMessageVcl.htm\">SecretMessage (VCL)</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to add a secret message to a 24-bit bitmap. These secret messages",
        "  can also be extracted again.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  <a href=\"ToolSecretMessageVcl.htm\">SecretMessage (VCL)</a> is the predecessor",
        "  of <a href=\"ToolSecretMessage.htm\">SecretMessage</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolSecretMessage_1_0.png\">View a screenshot of SecretMessage' (version 1.0)(png)</a></li>",
        "  <li><a href=\"ToolSecretMessageExample.png\">View an example image with a secret message (version 1.1)(png)</a></li>",
        "  <li><a href=\"ToolSecretMessageExe_1_0.zip\">Download the 'SecretMessage' Windows executable (version 1.0)(zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "ToolSimBrainiac",
      {
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "This computerprogram has nothing to do with the TV-program 'Brainiac'<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->",
        "<p>&nbsp;</p>",
        "<p><a href=\"ToolSimBrainiac.htm\">SimBrainiac</a> is a simulator of the",
        "Brainiac teaching form as used in the",
        "education of biology and science by Richel Bilderbeek (<a",
        "href=\"TeachBrainiac.htm\">Go to the 'Brainiac' page</a>).</p>",
        "<p>&nbsp;</p>",
        "<p>In <a href=\"ToolSimBrainiac.htm\">SimBrainiac</a>, students are simulated playing Brainiac.</p>",
        "<p>&nbsp;</p>",
        "<p>Every simulated student (a 'Brainiac') has:</p>",
        "<ul>",
        "  <li>a chance to correctly answer a question</li>",
        "  <li>a chance to make up a new question</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>The simulation demonstrates that both parameters are relevant to obtain a higher rank. ",
        "The chance to correctly answer a question is the most relevant.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ToolSimBrainiac.htm\">SimBrainiac</a> is programmed in <a href=\"Cpp.htm\">C++</a> ",
        "using the IDE <a href=\"CppBuilder.htm\">C++ Builder</a> 6.0. ",
        "It uses the <a href=\"CppStl.htm\">STL</a>, <a href=\"CppVcl.htm\">VCL</a>",
        "and <a href=\"CppBoost.htm\">Boost</a> libraries.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolSimBrainiac_1_0.png\">View a screenshot of 'SimBrainiac'</a></li>",
        "  <li><a href=\"ToolSimBrainiacSource.zip\">Download the 'SimBrainiac' source code (zip)</a></li>",
        "  <li><a href=\"ToolSimBrainiacExe.zip\">Download the 'SimBrainiac' Windows executable (zip)</a></li>",
        "</ul>",
      }
    }
  );
  m.push_back(
    { "ToolSimImmuneResponse",
      {
        "<p><a href=\"ToolSimImmuneResponse.htm\">SimImmuneResponse</a> is an active simulation in which the user is in control of the immune system.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ToolSimImmuneResponse.htm\">SimImmuneResponse</a> is programmed in <a href=\"Cpp.htm\">C++</a> using the IDE <a href=\"CppBuilder.htm\">C++ Builder</a> 6.0. It uses the <a href=\"CppStl.htm\">STL</a>, <a href=\"CppVcl.htm\">VCL</a> and <a href=\"CppBoost.htm\">Boost</a> libraries.</p>",
        "<p>&nbsp;</p>",
        "<p>I used it for <a href=\"Teaching.htm\">teaching</a> as well (<a href=\"TeachSimImmuneResponse.htm\">go to my SimImmuneResponse teaching page</a>).</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolSimImmuneResponse_1_0.png\">View a screenshot of 'SimImmuneResponse' (png)</a></li>",
        "  <li><a href=\"ToolSimImmuneResponseExe.zip\">Download the 'SimImmuneResponse' Windows executable (zip)</a></li>",
        "  <li><a href=\"ToolSimImmuneResponseSource.zip\">Download the 'SimImmuneResponse' source code (zip)</a></li>",
        "</ul>",
      }
    }
  );
  m.push_back(
    { "ToolSimMysteryMachine",
      {
        "<p><a href=\"ToolSimMysteryMachine.htm\">SimMysteryMachine</a> is a <a href=\"Tools.htm\">tool</a> to simulate",
        "my mystery machine.</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  If you think you know what this machine does, order me a drink, guess and I will tell you if your answer was",
        "  correct or not."
        "</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"ToolSimMysteryMachine.htm\">SimMysteryMachine</a> downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolSimMysteryMachine_1_2.png\">View a screenshot of 'SimMysteryMachine' (version 1.2)(png)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolSimMysteryMachineMenu_1_2.png\">View a screenshot of 'SimMysteryMachine' its main menu (version 1.2)(png)</a></li>",
        "  <li><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolSimMysteryMachine_1_1_web.png\">View a screenshot of 'SimMysteryMachine' (version 1.1)(png)</a></li>",
        "  <li><a href=\"ToolSimMysteryMachine.png\">View the real MysteryMachine (png)</a></li>",
        "  <li><a href=\"ToolSimMysteryMachinePrototype.png\">View the real MysteryMachine (prototope)(png)</a></li>",
        "  <li><a href=\"ToolSimMysteryMachineArchitecture_1_0.png\">View the architecture of 'SimMysteryMachine' (version 1.0)(png)</a></li>",
        "  <li><a href=\"ToolSimMysteryMachineArchitecture_1_0.dia\">View the architecture of 'SimMysteryMachine' (version 1.0)(dia)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolSimMysteryMachineDesktopExeWindows_1_0.zip\">Download the Windows executable of 'SimMysteryMachine' (version 1.0)(zip)</a></li>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolSimMysteryMachineSource_1_2.zip\">Download the 'SimMysteryMachine' source code (version 1.2)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>The <a href=\"CppWindows.htm\">Windows</a> executable of version 1.0 is created following ",
        "<a href=\"CppQtCrosscompileToWindowsExample15.htm\">how to cross-compile a Qt Creator project from Ubuntu to a windows executable: example 15: MinGW cross-compiling environment</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older <a href=\"ToolSimMysteryMachine.htm\">SimMysteryMachine</a> downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolSimMysteryMachineSource_1_1.zip\">Download the 'SimMysteryMachine' source code (version 1.1)(zip)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolSimMysteryMachine_1_1_desktop.png\">View a screenshot of 'SimMysteryMachine' (version 1.1)(png)</a></li>",
        "  <li><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolSimMysteryMachine_1_0.png\">View a screenshot of 'SimMysteryMachine' (version 1.0)(png)</a></li>",
        "  <li><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolSimMysteryMachineSource_1_0.zip\">Download the 'SimMysteryMachine' source code (version 1.0)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>The <a href=\"CppWindows.htm\">Windows</a> executable of version 1.0 is created following ",
        "<a href=\"CppQtCrosscompileToWindowsExample15.htm\">how to cross-compile a Qt Creator project from Ubuntu to a windows executable: example 15: MinGW cross-compiling environment</a>.</p>",
      }
    }
  );
  m.push_back(
    { "ToolSimplifyNewick",
      {
        "<p><a href=\"ToolSimplifyNewick.htm\">SimplifyNewick</a> is a <a href=\"Tools.htm\">tool</a> to randomly simplify <a href=\"CppNewick.htm\">Newicks</a>.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ToolSimplifyNewick.htm\">SimplifyNewick</a> is programmed in <a href=\"Cpp.htm\">C++</a> ",
        "using the <a href=\"CppIde.htm\">IDE</a> <a href=\"CppQtCreator.htm\">Qt Creator</a>. ",
        "It uses the  <a href=\"CppBoost.htm\">Boost</a>, <a href=\"CppCln.htm\">CLN</a>, <a href=\"CppQt.htm\">Qt</a> ",
        "and <a href=\"CppStl.htm\">STL</a> <a href=\"CppLibrary.htm\">libraries</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolSimplifyNewick_1_2.png\">View a screenshot of 'SimplifyNewick' (version 1.2)(png)</a></li>",
        "  <li><a href=\"ToolSimplifyNewickSource_2_0.zip\">Download the 'SimplifyNewick' source code (version 2.0)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolSimplifyNewickSource_1_2.zip\">Download the 'SimplifyNewick' source code (version 1.2)(zip)</a></li>",
        "  <li><a href=\"ToolSimplifyNewick_1_1.png\">View a screenshot of 'SimplifyNewick' (version 1.1)(png)</a></li>",
        "  <li><a href=\"ToolSimplifyNewick_1_0.png\">View a screenshot of 'SimplifyNewick' (version 1.0)(png)</a></li>",
        "</ul>",
      }
    }
  );
  m.push_back(
    { "ToolSimStagecraft",
      {
        "<p><a href=\"ToolSimStagecraft.htm\">SimStagecraft</a> is a <a href=\"Tools.htm\">tool</a> that ",
        "simulates the connecting and use of stagecraft equipment. For example, how to connect a microphone to ",
        "a sound table and speaker.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ToolSimStagecraft.htm\"></a> is programmed in <a href=\"Cpp.htm\">C++</a> using the IDE <a",
        "href=\"CppBuilder.htm\">C++ Builder</a> 6.0. It uses the <a href=\"CppStl.htm\">STL</a>,",
        "<a href=\"CppVcl.htm\">VCL</a> and <a href=\"CppBoost.htm\">Boost</a> library.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolSimStagecraft_1_1.png\">View a screenshot of 'SimStagecraft' (version 1.1)</a></li>",
        "  <li><a href=\"ToolSimStagecraftSource_1_1.htm\">View the 'SimStagecraft' source code as a web page (version 1.1)(htm)</a></li>",
        "  <li><a href=\"ToolSimStagecraftSource.zip\">Download the 'SimStagecraft' source code (version 1.1)(zip)</a></li>",
        "  <li><a href=\"ToolSimStagecraftExe.zip\">Download the 'SimStagecraft' Windows executable (version 1.1)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Version history</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>Version X.Y: DD-MM-YYYY</li>",
        "  <li>Version 1.1: 07-05-2009</li>",
        "  <li>Version 1.0: 10-02-2009</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolSimStagecraftSource_1_0.zip\">Download the 'SimStagecraft' source code v1.0 (zip)</a></li>",
        "  <li><a href=\"ToolSimStagecraftExe_1_0.zip\">Download the 'SimStagecraft' Windows executable v1.0 (zip)</a></li>",
        "</ul>",
      }
    }
  );
  m.push_back(
    { "ToolSoaSim",
      {
        "<p><a href=\"ToolSoaSim.htm\">SoaSim</a> is a simulation program to",
        "see the spread of a sexually transmitted disease in a small population.</p>",
        "<p>&nbsp;</p>",
        "<p>The program is called <a href=\"ToolSoaSim.htm\">SoaSim</a> as 'SOA' is the Dutch",
        "abbreviation of 'Sexually Transitted Disease'.</p>",
        "<p>&nbsp;</p>",
        "<p>I have used the simulation for a practical. You can also download the assignment",
        "I've made for this practical.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ToolSoaSim.htm\">SoaSim</a> is",
        "programmed in <a href=\"Cpp.htm\">C++</a> using the IDE <a href=\"CppBuilder.htm\">C++",
        "Builder</a> 6.0. It uses the <a href=\"CppStl.htm\">STL</a>, <a href=\"CppVcl.htm\">VCL</a>",
        "and <a href=\"CppBoost.htm\">Boost</a> library.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolSoaSim_1_0.png\">View a screenshot of 'SoaSim' (png)</a></li>",
        "  <li><a href=\"ToolSoaSimExe.zip\">Download the 'SoaSim' Windows executable (zip)</a></li>",
        "  <li><a href=\"ToolSoaSimSource.zip\">Download the 'SoaSim' source code (zip)</a></li>",
        "  <li><a href=\"ToolSoaSimAssignment.doc\">Download the 'SoaSim' assignment (doc)</a></li>",
        "</ul>",
      }
    }
  );

  m.push_back(
    { "ToolSolvePuzzleX",
      {
        "<p>",
        "  <a href=\"ToolSolvePuzzleX.htm\">SolvePuzzleX</a> is a <a href=\"Tools.htm\">tool</a>",
        "  solve a puzzle given to me by a girl I initially named 'X'.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolStaircaseCardCreator",
      {
        "<p>",
        "  <a href=\"ToolStaircaseCardCreator.htm\">StaircaseCardCreator</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to create staircase cards.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolStyleSheetSetter",
      {
        "<p>",
        "  <a href=\"ToolStyleSheetSetter.htm\">StyleSheetSetter</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to experiment with a Qt application its style sheet.",
        "</p>"
      }
    }
  );


  m.push_back(
    { "ToolStateObserver",
      {
        "<p>",
        "  <a href=\"ToolStateObserver.htm\">StateObserver</a> is a <a href=\"Tools.htm\">tool</a> to examine different state observers.",
        "</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolStateObserver_1_1.png\">View a screenshot of 'StateObserver' (version 1.1)(png)</a></li>",
        "  <li><a href=\"ToolStateObserver_1_0.png\">View a screenshot of 'StateObserver' (version 1.0)(png)</a></li>",
        "  <li><a href=\"ToolStateObserverExe_1_0.zip\">Download the 'StateObserver' Windows executable (version 1.0)(zip)</a></li>",
        "  <li><a href=\"ToolStateObserverSource_1_0.zip\">Download the 'StateObserver' source code (version 1.0)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>"
        //"      <math xmlns=\"http://www.w3.org/1998/Math/MathML\">",
        //"        <mrow>",
        //"          <mi>a</mi>",
        //"          <mo>&#x2062;<!-- &InvisibleTimes; --></mo>",
        //"          <msup>",
        //"            <mi>x</mi>",
        //"            <mn>2</mn>",
        //"          </msup>",
        //"          <mo>+</mo>",
        //"          <mi>b</mi>",
        //"          <mo>&#x2062;<!-- &InvisibleTimes; --></mo>",
        //"          <mi>x</mi>",
        //"          <mo>+</mo>",
        //"          <mi>c</mi>",
        //"          <mo>=</mo>",
        //"          <mi>0</mi>",
        //"        </mrow>",
        //"      </math>"
      }
    }
  );

  m.push_back(
    { "ToolSurfacePlotter",
      {
        "<p>",
        "  <a href=\"ToolSurfacePlotter.htm\">SurfacePlotter</a> is a <a href=\"Tools.htm\">tool</a>"
        "  to make a surface plot.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolSurfacePlotter_2_0.png\">View a screenshot of 'SurfacePlotter' (2.0)(png)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>External links</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"http://warp.povusers.org/FunctionParser\">Homepage of Warp's FunctionParser class</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ToolSurfacePlotterVcl",
      {
        "<p>",
        "  <a href=\"ToolSurfacePlotterVcl.htm\">SurfacePlotter (VCL)</a> is a <a href=\"Tools.htm\">tool</a>"
        "  to make a surface plot and is the predecessor of <a href=\"ToolSurfacePlotter.htm\">SurfacePlotter</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>",
        "  Note that this program uses <a href=\"http://warp.povusers.org/FunctionParser\">Warp's FunctionParser class</a>",
        "  version 2.7, where the current version (of February 2010) exceeds 4.0. This is due to",
        "  compilation problems under <a href=\"CppBuilder.htm\">C++ Builder</a> 6.0.",
        "  Small changes have been made to <a href=\"http://warp.povusers.org/FunctionParser\">Warp's FunctionParser class</a>",
        "  to get it to compile.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolSurfacePlotter_1_2.png\">View a screenshot of 'SurfacePlotter' (v.1.2)(png)</a></li>",
        "  <li><a href=\"ToolSurfacePlotterExe_1_2.zip\">Download the 'SurfacePlotter' Windows executable (v.1.2)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolSurfacePlotter_1_1.png\">View a screenshot of 'SurfacePlotter' (v.1.1)(png)</a></li>",
        "  <li><a href=\"ToolSurfacePlotterExe_1_1.zip\">Download the 'SurfacePlotter' Windows executable (v.1.1)(zip)</a></li>",
        "  <li><a href=\"ToolSurfacePlotter_1_0.png\">View a screenshot of 'SurfacePlotter' (v.1.0)(png)</a></li>",
        "  <li><a href=\"ToolSurfacePlotterExe_1_0.zip\">Download the 'SurfacePlotter' Windows executable (v.1.0)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>External links</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"http://warp.povusers.org/FunctionParser\">Homepage of Warp's FunctionParser class</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "ToolTestAbout",
      {
        "<p>",
        "  <a href=\"ToolTestAbout.htm\">TestAbout</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppAbout.htm\">About</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolTestApproximator",
      {
        "<p>",
        "  <a href=\"ToolTestApproximator.htm\">TestApproximator</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppApproximator.htm\">Approximator</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolTestBinaryNewickVector",
      {
        "<p>",
        "  <a href=\"ToolTestBinaryNewickVector.htm\">TestBinaryNewickVector</a> is a <a href=\"Tools.htm\">tool</a> to test",
        "  the <a href=\"CppBinaryNewickVector.htm\">BinaryNewickVector</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"ToolTestBinaryNewickVector.htm\">TestBinaryNewickVector</a> downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolTestBinaryNewickVector_1_5.png\">View a screenshot of 'TestBinaryNewickVector' (version 1.5)(png)</a></li>",
        "  <li><a href=\"ToolTestBinaryNewickVectorSource_3_1.zip\">Download the 'TestBinaryNewickVector' source code (version 3.1)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older <a href=\"ToolTestBinaryNewickVector.htm\">TestBinaryNewickVector</a> downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolTestBinaryNewickVector_1_3.png\">View a screenshot of 'TestBinaryNewickVector' (version 1.3)(png)</a></li>",
        "  <li><a href=\"ToolTestBinaryNewickVector_1_2.png\">View a screenshot of 'TestBinaryNewickVector' (version 1.2)(png)</a></li>",
        "  <li><a href=\"ToolTestBinaryNewickVector_1_1.png\">View a screenshot of 'TestBinaryNewickVector' (version 1.1)(png)</a></li>",
        "  <li><a href=\"ToolTestBinaryNewickVector_1_0.png\">View a screenshot of 'TestBinaryNewickVector' (version 1.0)(png)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "ToolTestBouncingBallsWidget",
      {
        "<p>",
        "  <a href=\"ToolTestBouncingBallsWidget.htm\">TestBouncingBallsWidget</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppBouncingBallsWidget.htm\">BouncingBallsWidget</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolTestBouncingRectsWidget",
      {
        "<p>",
        "  <a href=\"ToolTestBouncingRectsWidget.htm\">TestBouncingRectsWidget</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppBouncingRectsWidget.htm\">BouncingRectsWidget</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolTestBroadcastServer",
      {
        "<p><a href=\"ToolTestBroadcastServer.htm\">TestBroadcastServer</a> is a ",
        "<a href=\"CppWebApplication.htm\">web application</a>",
        "to test the <a href=\"CppWtBroadcastServer.htm\">WtBroadcastServer</a> and <a href=\"CppWtBroadcastServerClient.htm\">WtBroadcastServerClient</a>",
        "in the form of an edit widget, that can be viewed and edited by multiple visitors at the same time.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ToolTestBroadcastServer.htm\">TestBroadcastServer</a> is rendered obsolete by ",
        "<a href=\"ToolTestServerPusher.htm\">TestServerPusher</a> and <a href=\"ToolTestTimedServerPusher.htm\">TestTimedServerPusher</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolTestBroadcastServer_1_0.png\">View a screenshot of 'TestBroadcastServer' (version 1.0)(png)</a></li>",
        "  <li><a href=\"ToolTestBroadcastServerSource_1_2.zip\">Download the 'TestBroadcastServer' source code (version 1.2)(zip)</a></li>",
        "  <li><a href=\"ToolTestBroadcastServerSource_1_1.htm\">View the 'TestBroadcastServer' source code as web page (version 1.1)(htm)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolTestBroadcastServerSource_1_1.zip\">Download the 'TestBroadcastServer' source code (version 1.1)(zip)</a></li>",
        "  <li><a href=\"ToolTestBroadcastServer_1_0.png\">View a screenshot of 'TestBroadcastServer' (version 1.0)(png)</a></li>",
        "  <li><a href=\"ToolTestBroadcastServerSource_1_0.zip\">Download the 'TestBroadcastServer' source code (version 1.0)(zip)</a></li>",
        "</ul>",
      }
    }
  );

  m.push_back(
    { "ToolTestChess",
      {
        "<p>",
        "  <a href=\"ToolTestChess.htm\">TestChess</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppChess.htm\">Chess</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolTestConceptMap",
      {
        "<p>",
        "  <a href=\"ToolTestConceptMap.htm\">TestConceptMap</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppConceptMap.htm\">ConceptMap</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolTestDial",
      {
        "<p><a href=\"ToolTestDial.htm\">TestDial</a> is a <a href=\"Tools.htm\">tool</a> to test ",
        "the <a href=\"CppDial.htm\">Dial</a>, <a href=\"CppQtDialWidget.htm\">QtDialWidget</a> ",
        "and <a href=\"CppWtDialWidget.htm\">WtDialWidget</a> <a href=\"CppClass.htm\">classes</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"ToolTestDial.htm\">TestDial</a> downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolTestDial_1_1.png\">View a screenshot of 'TestDial' (version 1.1)(png)</a></li>",
        "  <li><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolTestDial_1_0.png\">View a screenshot of 'TestDial' (version 1.0)(png)</a></li>",
        "  <li><a href=\"ToolTestDialArchitecture.png\">View the architecture of 'TestDial' (version 2.1)(png)</a></li>",
        "  <li><a href=\"ToolTestDialArchitecture.dia\">View the architecture of 'TestDial' (version 2.1)(dia)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolTestDialDesktopExeWindows_1_0.zip\">Download the Windows executable of 'TestDial' (version 1.0)(zip)</a></li>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolTestDialSource_2_1.zip\">Download the 'TestDial' source code (version 2.1)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>The <a href=\"CppWindows.htm\">Windows</a> executable of version 1.0 is created following ",
        "<a href=\"CppQtCrosscompileToWindowsExample15.htm\">how to cross-compile a Qt Creator project from Ubuntu to a windows executable: example 15: MinGW cross-compiling environment</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older <a href=\"ToolTestDial.htm\">TestDial</a> downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolTestDialSource_2_0.zip\">Download the 'TestDial' source code (version 2.0)(zip)</a></li>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolTestDialSource_1_2.zip\">Download the 'TestDial' source code (version 1.2)(zip)</a></li>",
        "  <li><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolTestDialSource_1_1.zip\">Download the 'TestDial' source code (version 1.1)(zip)</a></li>",
        "  <li><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolTestDialSource_1_0.zip\">Download the 'TestDial' source code (version 1.0)(zip)</a></li>",
        "</ul>",
      }
    }
  );

  m.push_back(
    { "ToolTestDrawCanvas",
      {
        "<p>",
        "  <a href=\"ToolTestDrawCanvas.htm\">TestDrawCanvas</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppDrawCanvas.htm\">DrawCanvas</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolEncranger",
      {
        "<p><a href=\"ToolEncranger.htm\">Encranger</a>, short for 'ENCryption by RAndom",
        "Number GeneratoR' is a   <a href=\"Tools.htm\">tool</a> to encrypt en de-encrypt",
        "single-line text messages.   <a",
        "href=\"ToolMultiEncranger.htm\">MultiEncranger</a> is the multi-line version",
        "of <a href=\"ToolEncranger.htm\">Encranger</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolEncranger_2_1.png\">View a screenshot of 'Encranger' (version 2.1)(png)</a></li>",
        "  <li><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolEncranger_2_0.png\">View a screenshot of 'Encranger' (version 2.0)(png)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolEncranger_1_0.png\">View a screenshot of 'Encranger' (version 1.0)(png)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolEncrangerExe_1_0.zip\">Download the 'Encranger' Windows executable (version 1.0)(zip)</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolEncrangerSource_2_4.zip\">Download the 'Encranger' source code (version 2.4)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"ToolEncranger.htm\">Encranger</a> encryption algorithm</h2>",
        "<p>&nbsp;</p>",
        "<p>The <a href=\"CppEncranger.htm\">Encranger</a> encryption algorithm is a form of the ",
        "<a href=\"http://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher\">Vigenere cipher</a>.",
        "In the <a href=\"http://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher\">Vigenere",
        "cipher</a> the shift of letters differs per position and are determined by the",
        "letters in a keyword. In the <a href=\"CppEncranger.htm\">Encranger</a> ",
        "algorithm these shifts are determined by a random number generator, set by a key.</p>",
        "<p>&nbsp;</p>",
        "<p>To make this clear, I will first briefly explain <a",
        "href=\"http://en.wikipedia.org/wiki/Caesar_cipher\">Caesar cipher</a>, then I ll",
        "explain <a href=\"http://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher\">Vigenere",
        "cipher</a> and finally show the difference between the <a",
        "href=\"http://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher\">Vigenere cipher</a>",
        "and the <a href=\"CppEncranger.htm\">Encranger</a> algorithm.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"http://en.wikipedia.org/wiki/Caesar_cipher\">Caesar cipher</a> encrypts",
        "text by adding a value to each letter in a word. This value is the key or",
        "password. For example, the text  AAAAA  with the key  +1  becomes  BBBBB .</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"http://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher\">Vigenere",
        "cipher</a> encrypts text by adding a value to each letter in a word, in which",
        "the shift changes per letter. For example, the key  ABCDE  might hold the",
        "shifts  +1 +2 +3 +4 +5 . The plaintext  AAAAA  encrypted by the key  ABCDE ",
        "then becomes BCDEF .</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"CppEncranger.htm\">Encranger</a>, as <a",
        "href=\"http://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher\">Vigenere cipher</a>,",
        "encrypts text by adding a value to each letter in a word, in which the shift",
        "changes per letter. These shifts are not determined by a word, but are",
        "generated randomly using a value (the key). For example,",
        "using an alphabet of only five letters, the value of 123 generates a shift",
        "sequence of  +5 +3 +1 +2 +4. The plaintext  AAAAA  encrypted by the value 123 then",
        "becomes  ADBCE. <a href=\"CppEncranger.htm\">Encranger</a> uses <em>n</em> (about fifty)",
        "characters, consisting of letters and punctuation characters. ",
        "For a certain <a href=\"CppEncranger.htm\">Encranger</a>",
        "key, it is theoretically possible to calculate the <a",
        "href=\"http://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher\">Vigenere cipher</a>",
        "key (also of <em>n</em> characters). Because <a href=\"CppEncranger.htm\">Encranger</a>",
        "uses the <a href=\"Cpp.htm\">C++</a> random number generator to generate a random",
        "sequence of letter shifts, it is estimated that <a href=\"CppEncranger.htm\">Encranger</a>",
        "only has 32768 (<a href=\"CppRAND_MAX.htm\">RAND_MAX</a>)",
        "or 4294967296 (2^32, the maximal <a href=\"CppInt.htm\">integer</a> value) different",
        "keys, instead of the highest possible, which would be the factorial of <em>n</em>.</p>",
      }
    }
  );
  m.push_back(
    { "ToolTestEntrance",
      {
        "<p><a href=\"ToolTestEntrance.htm\">TestEntrance</a> is a <a href=\"Tools.htm\">tool</a> to test the <a href=\"CppWtEntrance.htm\">WtEntrance</a>",
        "<a href=\"CppClass.htm\">class</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolTestEntrance_1_0.png\">View a screenshot of 'TestEntrance' (version 1.0)(png)</a></li>",
        "  <li><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolTestEntranceSource_1_0.zip\">Download the 'TestEntrance' source code (version 1.0)(zip)</a></li>",
        "  <li><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolTestEntranceSource_1_0.htm\">View the 'TestEntrance' source code as web page (version 1.0)(htm)</a></li>",
        "</ul>",

      }
    }
  );

  m.push_back(
    { "ToolTestExercise",
      {
        "<p>",
        "  <a href=\"ToolTestExercise.htm\">TestExercise</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppExercise.htm\">Exercise</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolTestFunctionParser",
      {
        "<p><a href=\"ToolTestFunctionParser.htm\">TestFunctionParser</a> is a demonstration tool of <a ",
        "href=\"http://warp.povusers.org/FunctionParser\">Warp's FunctionParser class</a>:</p>",
        "<p>&nbsp;</p>",
        "<p>The user can input a function in the for 'y=f(x)' and a certain value of x. <a href=\"ToolTestFunctionParser.htm\">TestFunctionParser</a> then calculates the value",
        "of y. The <a href=\"Tools.htm\">tool</a> <a href=\"ToolFunctionPlotter.htm\">FunctionPlotter</a> plots the values of y over a range of x values.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolTestFunctionParser_2_1.png\">View a screenshot of 'FunctionParser (version 2.1)(png)'</a></li>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolTestFunctionParser_2_2.png\">View a screenshot of 'FunctionParser (version 2.2)(png)'</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolTestFunctionParser_2_3.png\">View a screenshot of 'FunctionParser (version 2.3)(png)'</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolTestFunctionParserExe_2_3.zip\">Download the 'FunctionParser' Windows executable (version 2.3)(zip)</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolTestFunctionParserSource_2_3.zip\">Download the 'FunctionParser' source code (version 2.3)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolTestFunctionParser_1_0.png\">View a screenshot of 'FunctionParser (version 1.0)(png)'</a></li>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolTestFunctionParser_2_0.png\">View a screenshot of 'FunctionParser (version 2.0)(png)'</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolTestFunctionParserSource_2_0.zip\">Download the 'FunctionParser' source code (version 2.0)(zip)</a></li>",
        "  <li><img src=\"PicCppBuilder.png\" alt=\"C++ Builder\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolTestFunctionParserSource_1_0.zip\">Download the 'FunctionParser' source code (version 1.0)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>External links</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"http://warp.povusers.org/FunctionParser\">Homepage of Warp's FunctionParser class</a></li>",
        "</ul>",
      }
    }
  );


  m.push_back(
    { "ToolTestGraphicsProxyWidget",
      {
        "<p>",
        "  <a href=\"ToolTestGraphicsProxyWidget.htm\">TestGraphicsProxyWidget</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppGraphicsProxyWidget.htm\">GraphicsProxyWidget</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );


  m.push_back(
    { "ToolTestGravityWidget",
      {
        "<p>",
        "  <a href=\"ToolTestGravityWidget.htm\">ToolTestGravityWidget</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppGravityWidget.htm\">GravityWidget</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );



  m.push_back(
    { "ToolTestGroupWidget",
      {
        "<p><a href=\"ToolTestGroupWidget.htm\">TestGroupWidget</a> is a <a href=\"Tools.htm\">tool</a> to test ",
        "the <a href=\"CppWtGroupWidget.htm\">WtGroupWidget</a> <a href=\"CppClass.htm\">classes</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"ToolTestGroupWidget.htm\">TestGroupWidget</a> downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolTestGroupWidget_1_0.png\">View a screenshot of 'TestGroupWidget' (version 1.0)(png)</a></li>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolTestGroupWidgetSource_1_3.zip\">Download the 'TestGroupWidget' source code (version 1.3)(zip)</a></li>",
        "</ul>",
      }
    }
  );

  m.push_back(
    { "ToolTestHugeVector",
      {
        "<p>",
        "  <a href=\"ToolTestHugeVector.htm\">ToolTestHugeVector</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppHugeVector.htm\">HugeVector</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolTestImageCanvas",
      {
        "<p>",
        "  <a href=\"ToolTestImageCanvas.htm\">TestImageCanvas</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppImageCanvas.htm\">ImageCanvas</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolTestLazy_init",
      {
        "<p>",
        "  <a href=\"ToolTestLazy_init.htm\">ToolTestLazy_init</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppLazy_init.htm\">Lazy_init</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolTestLed",
      {
        "<p><a href=\"ToolTestLed.htm\">TestLed</a> is a <a href=\"Tools.htm\">tool</a> to test ",
        "the <a href=\"CppLed.htm\">Led</a>, <a href=\"CppQtLedWidget.htm\">QtLedWidget</a> ",
        "and <a href=\"CppWtLedWidget.htm\">WtLedWidget</a> <a href=\"CppClass.htm\">classes</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"ToolTestLed.htm\">TestLed</a> downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolTestLed_1_1.png\">View a screenshot of 'TestLed' (version 1.1)(png)</a></li>",
        "  <li><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolTestLed_1_0.png\">View a screenshot of 'TestLed' (version 1.0)(png)</a></li>",
        "  <li><a href=\"ToolTestLedArchitecture.png\">View the architecture of 'TestLed' (version 1.2)(png)</a></li>",
        "  <li><a href=\"ToolTestLedArchitecture.dia\">View the architecture of 'TestLed' (version 1.2)(dia)</a></li>",
        "  <li><img src=\"PicWindows.png\" alt=\"Windows\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolTestLedExeWindows_1_0.zip\">Download the Windows executable of 'TestLed' (version 1.0)(zip)</a></li>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolTestLedSource_1_3.zip\">Download the 'TestLed' source code (version 1.3)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>The <a href=\"CppWindows.htm\">Windows</a> executable of version 1.0 is created following ",
        "<a href=\"CppQtCrosscompileToWindowsExample15.htm\">how to cross-compile a Qt Creator project from Ubuntu to a windows executable: example 15: MinGW cross-compiling environment</a>.</p>",
      }
    }
  );

  m.push_back(
    { "ToolTestManyDigitNewick",
      {
        "<p>",
        "  <a href=\"ToolTestManyDigitNewick.htm\">ToolTestManyDigitNewick</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppManyDigitNewick.htm\">ManyDigitNewick</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolTestMultiApproximator",
      {
        "<p>",
        "  <a href=\"ToolTestMultiApproximator.htm\">TestMultiApproximator</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppMultiApproximator.htm\">MultiApproximator</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolTestMultiCanvas",
      {
        "<p>",
        "  <a href=\"ToolTestMultiCanvas.htm\">TestMultiCanvas</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppMultiCanvas.htm\">MultiCanvas</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolTestMultipleChoiceQuestion",
      {
        "<p>",
        "  <a href=\"ToolTestMultipleChoiceQuestion.htm\">TestMultipleChoiceQuestion</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppMultipleChoiceQuestion.htm\">MultipleChoiceQuestion</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolTestMultiVector",
      {
        "<p><a href=\"ToolTestMultiVector.htm\">TestMultiVector</a> is a <a href=\"Tools.htm\">tool</a> to test ",
        "the <a href=\"CppMultiVector.htm\">MultiVector</a> <a href=\"CppClass.htm\">class</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"ToolTestMultiVector.htm\">TestMultiVector</a> downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolTestMultiVectorSource_1_0.zip\">Download the 'TestMultiVector' source code (version 1.0)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<!--",
        "<h2>Older <a href=\"ToolTestMultiVector.htm\">TestMultiVector</a> downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolTestMultiVectorSource_2_0.zip\">Download the 'TestMultiVector' source code (version 2.0)(zip)</a></li>",
        "</ul>",
        "-->"
      }
    }
  );
  m.push_back(
    { "ToolTestNdsmake",
      {
        "<p><a href=\"ToolTestNdsmake.htm\">TestNdsmake</a> tests the <a href=\"Tools.htm\">tool</a> ",
        "<a href=\"ToolNdsmake.htm\">ndsmake</a>. <a href=\"ToolNdsmake.htm\">ndsmake</a> is a <a href=\"Tools.htm\">tool</a>",
        "to generate an <a href=\"CppNds.htm\">NDS</a> <a href=\"CppMakefile.htm\">Makefile</a> from ",
        "<a href=\"CppQtCreator.htm\">Qt Creator</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolTestNdsmake_1_0.png\">View a screenshot of 'TestNdsmake' (version 1.0)(png)</a></li>",
        "  <li><a href=\"ToolTestNdsmakeUse_1_0.png\">View how TestNdsmake uses ndsmake (version 1.0)(png)</a></li>",
        "  <li><a href=\"ToolTestNdsmakeSource_1_0.zip\">Download the source code of 'TestNdsmake' (version 1.0)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<!-- <h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolTestNdsmake_1_1.png\">View a screenshot of 'TestNdsmake' (v.1.1)(png)</a></li>",
        "  <li><a href=\"ToolTestNdsmake_1_0.png\">View a screenshot of 'TestNdsmake' (v.1.0)(png)</a></li>",
        "</ul>",
        "-->"
      }
    }
  );
  m.push_back(
    { "ToolTestNeuralNet",
      {
        "<p><a href=\"ToolTestNeuralNet.htm\">TestNeuralNet</a> is a <a href=\"Tools.htm\">tool</a> to test the ",
        "<a href=\"CppNeuralNet.htm\">NeuralNet</a> <a href=\"CppClass.htm\">class</a>.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ToolTestNeuralNet.htm\">TestNeuralNet</a> is programmed in <a href=\"Cpp.htm\">C++</a> ",
        "using the <a href=\"CppIde.htm\">IDE</a> <a href=\"CppQtCreator.htm\">Qt Creator</a>. ",
        "It uses the  <a href=\"CppBoost.htm\">Boost</a>, <a href=\"CppQt.htm\">Qt</a>, <a href=\"CppShark.htm\">Shark</a>",
        "and <a href=\"CppStl.htm\">STL</a> <a href=\"CppLibrary.htm\">libraries</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolTestNeuralNet_0_1.png\">View a screenshot of 'TestNeuralNet' (version 0.1)(png)</a></li>",
        "  <li><a href=\"ToolTestNeuralNetSource_0_1.zip\">Download the 'TestNeuralNet' source code (version 0.1)(zip)</a></li>",
        "</ul>",
      }
    }
  );

  m.push_back(
    { "ToolTestNewick",
      {
        "<p>",
        "  <a href=\"ToolTestNewick.htm\">TestNewick</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppNewick.htm\">Newick</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolTestNewickVector",
      {
        "<p>",
        "  <a href=\"ToolTestNewickVector.htm\">TestNewickVector</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppNewickVector.htm\">NewickVector</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolTestOpenQuestion",
      {
        "<p>",
        "  <a href=\"ToolTestOpenQuestion.htm\">TestOpenQuestion</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppOpenQuestion.htm\">OpenQuestion</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolTestPrimeExpert",
      {
        "<p><a href=\"ToolTestPrimeExpert.htm\">TestPrimeExpert</a> is a <a href=\"Tools.htm\">tool</a> to test ",
        "the <a href=\"CppPrimeExpert.htm\">PrimeExpert</a> <a href=\"CppClass.htm\">class</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"ToolTestPrimeExpert.htm\">TestPrimeExpert</a> downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolTestPrimeExpert_1_0.png\">View a screenshot of 'TestPrimeExpert' (version 1.0)(png)</a></li>",
        "  <li><a href=\"ToolTestPrimeExpertSource_2_0.zip\">Download the 'TestPrimeExpert' source code (version 2.0)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older <a href=\"ToolTestPrimeExpert.htm\">TestPrimeExpert</a> downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolTestPrimeExpertSource_1_0.zip\">Download the 'TestPrimeExpert' source code (version 1.0)(zip)</a></li>",
        "</ul>",
      }
    }
  );
  m.push_back(
    { "ToolTestProFile",
      {
        "<p><a href=\"ToolTestProFile.htm\">TestProFile</a> is a (very simple) <a href=\"Tools.htm\">tool</a>",
        "to test the <a href=\"CppProFile.htm\">ProFile</a> <a href=\"CppClass.htm\">class</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolTestProFileSource_1_0.zip\">Download the 'TestProFile' source code (version 1.0)(zip)</a></li>",
        "</ul>",
      }
    }
  );
  m.push_back(
    { "ToolTestPylos",
      {
        "<p><a href=\"ToolTestPylos.htm\">TestPylos</a> is a <a href=\"Tools.htm\">tool</a> to test the ",
        "<a href=\"CppPylos.htm\">Pylos</a> (also called 'Pyraos') and ",
        "<a href=\"CppPylosWidget.htm\">PylosWidget</a> <a href=\"CppClass.htm\">classes</a>.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ToolTestPylos.htm\">TestPylos</a> was the start of my ",
        "<a href=\"GamePylos.htm\">Pylos</a> <a href=\"Games.htm\">game</a>.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ToolTestPylos.htm\">TestPylos</a> is programmed in <a href=\"Cpp.htm\">C++</a> ",
        "using the <a href=\"CppIde.htm\">IDE</a> <a href=\"CppQtCreator.htm\">Qt Creator</a>. ",
        "It uses the  <a href=\"CppBoost.htm\">Boost</a>, <a href=\"CppQt.htm\">Qt</a>",
        "and <a href=\"CppStl.htm\">STL</a> <a href=\"CppLibrary.htm\">libraries</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolTestPylos_1_0.png\">View a screenshot of 'TestPylos' (version 1.0)(png)</a></li>",
        "  <li><a href=\"ToolTestPylosSource_1_2.zip\">Download the 'TestPylos' source code (version 1.1)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolTestPylos_0_3.png\">View a screenshot of 'TestPylos' (version 0.3)(png)</a></li>",
        "  <li><a href=\"ToolTestPylos_0_2.png\">View a screenshot of 'TestPylos' (version 0.2)(png)</a></li>",
        "  <li><a href=\"ToolTestPylos_0_1.png\">View a screenshot of 'TestPylos' (version 0.1)(png)</a></li>",
        "</ul>",
      }
    }
  );

  m.push_back(
    { "ToolTestQtKeyboardFriendlyGraphicsView",
      {
        "<p>",
        "  <a href=\"ToolTestQtKeyboardFriendlyGraphicsView.htm\">TestQtKeyboardFriendlyGraphicsView</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppQtKeyboardFriendlyGraphicsView.htm\">QtKeyboardFriendlyGraphicsView</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolTestQrcFile",
      {
        "<p>",
        "  <a href=\"ToolTestQrcFile.htm\">TestQrcFile</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppQrcFile.htm\">QrcFile</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolTestQtArrowItems",
      {
        "<p>",
        "  <a href=\"ToolTestQtArrowItems.htm\">TestQtArrowItems</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppQtArrowItems.htm\">QtArrowItems</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolTestQtCreatorProFile",
      {
        "<p>",
        "  <a href=\"ToolTestQtCreatorProFile.htm\">TestQtCreatorProFile</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppQtCreatorProFile.htm\">QtCreatorProFile</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolTestQtHideAndShowDialog",
      {
        "<p>",
        "  <a href=\"ToolTestQtHideAndShowDialog.htm\">TestQtHideAndShowDialog</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppQtHideAndShowDialog.htm\">QtHideAndShowDialog</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );


  m.push_back(
    { "ToolTestQtModels",
      {
        "<p><a href=\"ToolTestQtModels.htm\">TestQtModels</a> is a <a href=\"Tools.htm\">tool</a> to test my model classes.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolTestQtModels_1_0.png\">View a screenshot of 'TestQtModels' (version 1.0)(png)</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/> <a href=\"ToolTestQtModelsSource_1_0.zip\">Download the 'TestQtModels' source code (version 1.0)(zip)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolTestQtModelsSource_1_0.htm\">View the 'TestQtModels' source code as web page (version 1.0)(htm)</a></li>",
        "</ul>",
      }
    }
  );


  m.push_back(
    { "ToolTestQtOcrWidget",
      {
        "<p>",
        "  <a href=\"ToolTestQtOcrWidget.htm\">TestQtOcrWidget</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppQtOcrWidget.htm\">QtOcrWidget</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolTestQtRoundedEditRectItem",
      {
        "<p>",
        "  <a href=\"ToolTestQtRoundedEditRectItem.htm\">TestQtRoundedEditRectItem</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppQtRoundedEditRectItem.htm\">QtRoundedEditRectItem</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolTestQtRoundedRectItem",
      {

        "<p><a href=\"ToolTestQtRoundedRectItem.htm\">TestQtRoundedRectItem</a> is a <a href=\"Tools.htm\">tool</a> to",
        "test my QtRoundedRectItem class.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolTestQtRoundedRectItem_1_1.png\">View a screenshot of 'TestQtRoundedRectItem' (version 1.1)(png)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolTestQtRoundedRectItemSource_1_1.zip\">Download the 'TestQtRoundedRectItem' source code (version 1.1)(zip)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolTestQtRoundedRectItemSource_1_1.htm\">View the 'TestQtRoundedRectItem' source code as web page (version 1.1)(htm)</a></li>",
        "</ul>",
      }
    }
  );

  m.push_back(
    { "ToolTestQtRoundedTextRectItem",
      {
        "<p>",
        "  <a href=\"ToolTestQtRoundedTextRectItem.htm\">TestQtRoundedTextRectItem</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppQtRoundedTextRectItem.htm\">QtRoundedTextRectItem</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolTestQuestion",
      {
        "<p><a href=\"ToolTestQuestion.htm\">TestQuestion</a> is a <a href=\"Tools.htm\">tool</a> to test ",
        "many <a href=\"CppClass.htm\">classes</a> related to questions.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolTestQuestion_2_1.png\">View a screenshot of TestQuestion (version 2.1)(png)</a></li>",
        "  <li><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolTestQuestion_1_0.png\">View a screenshot of TestQuestion (version 1.0)(png)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolTestQuestionArchitecture.png\">View the architecture of TestQuestion (version 1.0)(png)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolTestQuestionArchitecture.dia\">View the architecture of TestQuestion (version 1.0)(dia)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolTestQuestionSource_2_1.zip\">Download the TestQuestion source code (version 2.1)(zip)</a></li>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicWindows.png\" alt=\"Windows\"/> <a href=\"ToolTestQuestionDesktopExe_2_1.zip\">Download a Windows executable of TestQuestion (version 2.1)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolTestQuestion_0_9.png\">View a screenshot of TestQuestion (version 0.9)(png)</a></li>",
        "</ul>",
      }
    }
  );

  m.push_back(
    { "ToolTestReversi",
      {
        "<p>",
        "  <a href=\"ToolTestReversi.htm\">TestReversi</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppReversi.htm\">Reversi</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolTestSelectFileDialog",
      {
        "<p><a href=\"ToolTestSelectFileDialog.htm\">TestSelectFileDialog</a> is a <a href=\"Tools.htm\">tool</a> to test ",
        "the <a href=\"CppWtSelectFileDialog.htm\">WtSelectFileDialog</a> <a href=\"CppClass.htm\">class</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolTestSelectFileDialog_1_1.png\">View a screenshot of TestSelectFileDialog (version 1.1)(png)</a></li>",
        "  <li><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolTestSelectFileDialogSource_1_1.zip\">Download the TestSelectFileDialog source code (version 1.1)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolTestSelectFileDialog_1_0.png\">View a screenshot of TestSelectFileDialog (version 1.0)(png)</a></li>",
        "  <li><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolTestSelectFileDialogSource_1_0.zip\">Download the TestSelectFileDialog source code (version 1.0)(zip)</a></li>",
        "</ul>",
      }
    }
  );
  m.push_back(
    { "ToolTestServerPusher",
      {
        "<p><a href=\"ToolTestServerPusher.htm\">TestServerPusher</a> is a ",
        "<a href=\"CppWebApplication.htm\">web application</a>",
        "to test the <a href=\"CppWtServerPusher.htm\">WtServerPusher</a> and <a href=\"CppWtServerPusherClient.htm\">WtServerPusherClient</a>",
        "in the form of an edit widget, that can be viewed and edited by multiple visitors at the same time.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolTestServerPusher_1_0.png\">View a screenshot of 'TestServerPusher' (version 1.0)(png)</a></li>",
        "  <li><a href=\"ToolTestServerPusherSource_1_0.zip\">Download the 'TestServerPusher' source code (version 1.2)(zip)</a></li>",
        "  <li><a href=\"ToolTestServerPusherSource_1_0.htm\">View the 'TestServerPusher' source code as web page (version 1.1)(htm)</a></li>",
        "</ul>",
      }
    }
  );
  m.push_back(
    { "ToolTestShape",
      {
        "<p><a href=\"ToolTestShape.htm\">TestShape</a> is a <a href=\"Tools.htm\">tool</a> to tool to test the <a href=\"CppShape.htm\">Shape</a> ",
        "and <a href=\"CppShapeWidget.htm\">ShapeWidget</a> <a href=\"CppClass.htm\">classes</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolTestShape_1_0_web.png\">View a screenshot of 'TestShape' (version 1.0)(png)</a></li>",
        "  <li><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolTestShape_1_0_desktop.png\">View a screenshot of 'TestShape' (version 1.0)(png)</a></li>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolTestShapeSource_2_0.zip\">Download the 'TestShape' source code (version 2.0)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicQtCreator.png\" alt=\"Qt Creator\"/><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolTestShapeSource_1_0.zip\">Download the 'TestShape' source code (version 1.0)(zip)</a></li>",
        "</ul>",
      }
    }
  );
  m.push_back(
    { "ToolTestShinyButton",
      {
        "<p><a href=\"ToolTestShinyButton.htm\">TestShinyButton</a> is a <a href=\"Tools.htm\">tool</a> to test ",
        "the <a href=\"CppShinyButton.htm\">ShinyButton</a>, <a href=\"CppShinyButtonWidget.htm\">ShinyButtonWidget</a>, ",
        "and <a href=\"CppWtShinyButtonWidget.htm\">WtShinyButtonWidget</a> <a href=\"CppClass.htm\">classes</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"ToolTestShinyButton.htm\">TestShinyButton</a> downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> <a href=\"ToolTestShinyButton_2_0_desktop.png\">View a screenshot of 'TestShinyButton' (version 2.0)(png)</a></li>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolTestShinyButtonSource_2_0_web.png\">View a screenshot of 'TestShinyButton' (version 2.0)(png)</a></li>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolTestShinyButtonSource_1_0.zip\">Download the 'TestShinyButton' source code (version 1.0)(zip)</a></li>",
        "</ul>",
      }
    }
  );

  m.push_back(
    { "ToolTestSimpleLinearRegression",
      {
        "<p>",
        "  <a href=\"ToolTestSimpleLinearRegression.htm\">TestSimpleLinearRegression</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppSimpleLinearRegression.htm\">SimpleLinearRegression</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolTestStopwatch",
      {
        "<p><a href=\"ToolTestStopwatch.htm\">TestStopwatch</a> is a <a href=\"Tools.htm\">tool</a> to test the ",
        "<a href=\"CppStopwatch.htm\">Stopwatch</a> <a href=\"CppClass.htm\">class</a>.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ToolTestStopwatch.htm\">TestStopwatch</a> is programmed in <a href=\"Cpp.htm\">C++</a> ",
        "using the <a href=\"CppIde.htm\">IDE</a> <a href=\"CppQtCreator.htm\">Qt Creator</a>. ",
        "It uses the  <a href=\"CppBoost.htm\">Boost</a>, <a href=\"CppQt.htm\">Qt</a>",
        "and <a href=\"CppStl.htm\">STL</a> <a href=\"CppLibrary.htm\">libraries</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolTestStopwatchSource_1_1.zip\">Download the 'TestStopwatch' source code (version 1.1)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>...</li>",
        "</ul>",
      }
    }
  );

  m.push_back(
    { "ToolTestTextCanvas",
      {
        "<p>",
        "  <a href=\"ToolTestTextCanvas.htm\">TestTextCanvas</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppTextCanvas.htm\">TextCanvas</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolTestTextPositionWidget",
      {
        "<p>",
        "  <a href=\"ToolTestTextPositionWidget.htm\">TestTextPositionWidget</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test the <a href=\"CppTextPositionWidget.htm\">TextPositionWidget</a> <a href=\"CppClass.htm\">class</a>.",
        "</p>"
      }
    }
  );


  m.push_back(
    { "ToolTestTicTacToe",
      {
        "<p><a href=\"ToolTestTicTacToe.htm\">TestTicTacToe</a> is a <a href=\"Tools.htm\">tool</a> to test the ",
        "<a href=\"CppTicTacToe.htm\">TicTacToe</a> <a href=\"CppClass.htm\">class</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolTestTicTacToe_1_1.png\">View a screenshot of 'TestTicTacToe' (desktop application)(version 1.1)(png)</a></li>",
        "  <li><a href=\"ToolTestTicTacToe_1_2.png\">View a screenshot of 'TestTicTacToe' (web application)(version 1.2)(png)</a></li>",
        "  <li><a href=\"ToolTestTicTacToeSource_1_3.zip\">Download the 'TestTicTacToe' source code (version 1.3)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolTestTicTacToe_1_0.png\">View a screenshot of 'TestTicTacToe' (version 1.0)(png)</a></li>",
        "  <li><a href=\"ToolTestTicTacToe_0_1.png\">View a screenshot of 'TestTicTacToe' (version 0.1)(png)</a></li>",
        "</ul>",
      }
    }
  );
  m.push_back(
    { "ToolTestTimedServerPusher",
      {
        "<p><a href=\"ToolTestTimedServerPusher.htm\">TestTimedServerPusher</a> is a ",
        "<a href=\"CppWebApplication.htm\">web application</a>",
        "to test the <a href=\"CppWtTimedServerPusher.htm\">WtTimedServerPusher</a> and <a href=\"CppWtTimedServerPusherClient.htm\">WtTimedServerPusherClient</a>",
        "in the form of an edit widget, that can be viewed and edited by multiple visitors at the same time.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolTestTimedServerPusher_1_0.png\">View a screenshot of 'TestTimedServerPusher' (version 1.0)(png)</a></li>",
        "  <li><a href=\"ToolTestTimedServerPusherSource_1_0.zip\">Download the 'TestTimedServerPusher' source code (version 1.2)(zip)</a></li>",
        "  <li><a href=\"ToolTestTimedServerPusherSource_1_0.htm\">View the 'TestTimedServerPusher' source code as web page (version 1.1)(htm)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ToolTestToggleButton",
      {
        "<p><a href=\"ToolTestToggleButton.htm\">TestToggleButton</a> is a <a href=\"Tools.htm\">tool</a> to test ",
        "the <a href=\"CppToggleButton.htm\">ToggleButton</a>, <a href=\"CppToggleButtonWidget.htm\">ToggleButtonWidget</a>, ",
        "<a href=\"CppQtToggleButtonWidget.htm\">QtToggleButtonWidget</a> ",
        "and <a href=\"CppWtToggleButtonWidget.htm\">WtToggleButtonWidget</a> <a href=\"CppClass.htm\">classes</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2><a href=\"ToolTestToggleButton.htm\">TestToggleButton</a> downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicLubuntu.png\" alt=\"Lubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/><img src=\"PicWeb.png\" alt=\"Web\"/> <a href=\"ToolTestToggleButtonSource_1_1.zip\">Download the 'TestToggleButton' source code (version 1.1)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older <a href=\"ToolTestToggleButton.htm\">TestToggleButton</a> downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><img src=\"PicUbuntu.png\" alt=\"Ubuntu\"/><img src=\"PicDesktop.png\" alt=\"Desktop\"/> Download the 'TestToggleButton' source code (version 1.0)(zip)(lost)</li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ToolTestTwoDigitNewick",
      {
        "<p><a href=\"ToolTestTwoDigitNewick.htm\">TestTwoDigitNewick</a> is a demonstration <a href=\"Tools.htm\">tool</a> of the two-digit-<a href=\"CppNewick.htm\">Newick</a>.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolTestTwoDigitNewick_0_6.png\">View a 'TestTwoDigitNewick' screenshot (version 0.6)(png)</a></li>",
        "<!--",
        "  <li><a href=\"CppTwoDigitNewickAlgorithm.htm\">Read the TwoDigitNewick algorithm</a></li>",
        "  <li><a href=\"ToolTestTwoDigitNewickSource_2_3.zip\">Download the 'TestTwoDigitNewick' source code (version 2.3)(zip)</a></li>",
        "  <li><a href=\"ToolTestTwoDigitNewickSource_2_2.zip\">Download the 'TestTwoDigitNewick' source code (version 2.2)(zip)</a></li>",
        "  <li><a href=\"ToolTestTwoDigitNewickSource_2_1.zip\">Download the 'TestTwoDigitNewick' source code (version 2.1)(zip)</a></li>",
        "  <li><a href=\"ToolTestTwoDigitNewickSource_2_0.zip\">Download the 'TestTwoDigitNewick' source code (version 2.0)(zip)</a></li>",
        "  <li><a href=\"ToolTestTwoDigitNewickSource_1_1.zip\">Download the 'TestTwoDigitNewick' source code (version 1.1)(zip)</a></li>",
        "  <li><a href=\"ToolTestTwoDigitNewickSource_1_0.zip\">Download the 'TestTwoDigitNewick' source code (version 1.0)(zip)</a></li>",
        "-->",
        "  <li><a href=\"ToolTestTwoDigitNewickSource_0_6.zip\">Download the 'TestTwoDigitNewick' source code (version 0.6)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolTestTwoDigitNewick_0_5.png\">View a 'TestTwoDigitNewick' screenshot (version 0.5)(png)</a></li>",
        "  <li><a href=\"ToolTestTwoDigitNewick_0_4.png\">View a 'TestTwoDigitNewick' screenshot (version 0.4)(png)</a></li>",
        "  <li><a href=\"ToolTestTwoDigitNewick_0_3.png\">View a 'TestTwoDigitNewick' screenshot (version 0.3)(png)</a></li>",
        "  <li><a href=\"ToolTestTwoDigitNewick_0_2.png\">View a 'TestTwoDigitNewick' screenshot (version 0.2)(png)</a></li>",
        "  <li><a href=\"ToolTestTwoDigitNewick_0_1.png\">View a 'TestTwoDigitNewick' screenshot (version 0.1)(png)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ToolThresholdFilterer",
      {
        "<p>",
        "  <a href=\"ToolThresholdFilterer.htm\">ThresholdFilterer</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to perform threshold filter operations.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>...</li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "ToolThresholdFiltererVcl",
      {
        "<p>",
        "  <a href=\"ToolThresholdFiltererVcl.htm\">ThresholdFilterer (VCL)</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to perform threshold filter operations and is the predecessor of",
        "  <a href=\"ToolThresholdFilterer.htm\">ThresholdFilterer</a>.",
        "</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolThresholdFilterer_1_0.png\">View a screenshot of 'ThresholdFilterer' (version 1.0)(png)</a></li>",
        "  <li><a href=\"ToolThresholdFiltererExe_1_0.zip\">Download the 'ThresholdFilterer' Windows executable (version 1.0)(zip)</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "ToolTicTacToeLearner",
      {
        "<p><a href=\"ToolTicTacToeLearner.htm\">TicTacToeLearner</a> is a <a href=\"Tools.htm\">tool</a> to demonstrate machine learning.</p>",
        "<p>&nbsp;</p>",
        "<p>The current (version 0.3) problem is, that the learners do not get smarter at playing tic-tac-toe...</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ToolTicTacToeLearner.htm\">TicTacToeLearner</a> uses the following <a href=\"CppLibrary.htm\">libraries</a>:</p>",
        "<ul>",
        "  <li><a href=\"CppBoost.htm\">Boost</a>: version 1.40</li>",
        "  <li><a href=\"CppQt.htm\">Qt</a>: version 4.7.0 (32 bit)</li>",
        "  <li><a href=\"CppQtSvg.htm\">QtSvg</a>: version 4:4.6.2-0ubuntu5</li>",
        "  <li><a href=\"CppQwt.htm\">Qwt</a>: version 5.2.0-1build1</li>",
        "  <li><a href=\"CppStl.htm\">STL</a>: from <a href=\"CppGcc.htm\">GCC</a>, shipped with <a href=\"CppQt.htm\">Qt Creator</a> 2.0.0</li>",
        "  <li><a href=\"CppShark.htm\">Shark</a>: version 2.3.2</li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolTicTacToeLearner_0_3.png\">View a screenshot of 'TicTacToeLearner' (version 0.3)(png)</a></li>",
        "  <li><a href=\"ToolTicTacToeLearnerSource_0_4.zip\">Download the 'TicTacToeLearner' source code (version 0.4)(zip)</a></li>",
        "  <li><a href=\"ToolTicTacToeLearnerSource_0_4.htm\">View the 'TicTacToeLearner' source code as web page (version 0.4)(htm)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Version history</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li>V X.Y: YYYY-MM-DD: description</li>",
        "  <li>V 0.1: 2010-08-16: initial neural network class passed the tests</li>",
        "  <li>V 0.2: 2010-08-16: neural networks are rated on playing tic-tac-toe, added minimal GUI, improved the neural network class</li>",
        "  <li>V 0.3: 2010-08-16: small GUI improvements, added conditional NDEBUG</li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ToolTicTacToeValuer",
      {
        "<p><a href=\"ToolTicTacToeValuer.htm\">TicTacToeValuer</a> is a <a href=\"Tools.htm\">tool</a> to demonstrate machine learning.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ToolTicTacToeValuer.htm\">TicTacToeValuer</a> uses a state-value graph to value each state.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolTicTacToeValuer_0_7.png\">View a screenshot of 'TicTacToeValuer' (version 0.7)(png)</a></li>",
        "  <li><a href=\"ToolTicTacToeValuerSource_0_7.zip\">Download the 'TicTacToeValuer' source code (version 0.7)(zip)</a></li>",
        "  <li><a href=\"ToolTicTacToeValuerSource_0_7.htm\">View the 'TicTacToeValuer' source code as web page (version 0.7)(htm)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolTicTacToeValuer_0_6.png\">View a screenshot of 'TicTacToeValuer' (version 0.6)(png)</a></li>",
        "  <li><a href=\"ToolTicTacToeValuer_0_5.png\">View a screenshot of 'TicTacToeValuer' (version 0.5)(png)</a></li>",
        "  <li><a href=\"ToolTicTacToeValuer_0_4.png\">View a screenshot of 'TicTacToeValuer' (version 0.4)(png)</a></li>",
        "  <li><a href=\"ToolTicTacToeValuer_0_3.png\">View a screenshot of 'TicTacToeValuer' (version 0.3)(png)</a></li>",
        "  <li><a href=\"ToolTicTacToeValuer_0_2.png\">View a screenshot of 'TicTacToeValuer' (version 0.2)(png)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ToolTimePoll",
      {
        "<p><a href=\"ToolTimePoll.htm\">TimePoll</a> is a <a href=\"CppWebApplication.htm\">web application</a> that allows to do a time poll:",
        "a poll that is determined by the time an option is selected, where every visitor can change the selected option.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolTimePoll_4_1.png\">View a screenshot of 'TimePoll' (version 4.1)(png)</a></li>",
        "  <li><a href=\"ToolTimePollSource_5_0.zip\">Download the 'TimePoll' source code (version 5.0)(zip)</a></li>",
        "  <li><a href=\"ToolTimePollSource_5_0.htm\">View the 'TimePoll' source code as web page (version 5.0)(htm)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Older downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolTimePoll_1_0.png\">View a screenshot of 'TimePoll' (version 1.0)(png)</a></li>",
        "  <li><a href=\"ToolTimePoll_0_2.png\">View a screenshot of 'TimePoll' (version 0.2)(png)</a></li>",
        "  <li><a href=\"ToolTimePoll_0_1.png\">View a screenshot of 'TimePoll' (version 0.1)(png)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ToolUbuntuOneWatcher",
      {
        "<p><a href=\"ToolUbuntuOneWatcher.htm\">UbuntuOneWatcher</a> is a <a href=\"Tools.htm\">tool</a> to view",
        "what Ubuntu One is doing.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolUbuntuOneWatcher_1_0.png\">View a screenshot of 'UbuntuOneWatcher' (version 1.0)(png)</a></li>",
        "  <li><a href=\"ToolUbuntuOneWatcherSource_1_0.zip\">Download the 'UbuntuOneWatcher' source code (version 1.0)(zip)</a></li>",
        "  <li><a href=\"ToolUbuntuOneWatcherSource_1_0.htm\">View the 'UbuntuOneWatcher' source code as web page (version 1.0)(htm)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>External links</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"https://one.ubuntu.com/dashboard\">UbuntuOne homepage</a></li>",
        "  <li><a href=\"http://en.wikipedia.org/wiki/Ubuntu_One\">Wikipedia page about UbuntuOne</a></li>",
        "</ul>"
      }
    }
  );

  m.push_back(
    { "ToolVirtualBastard",
      {
        "<p>",
        "  <a href=\"ToolVirtualBastard.htm\">VirtualBastard</a> is a <a href=\"Tools.htm\">tool</a>",
        "  to test graphical user interfaces.",
        "</p>"
      }
    }
  );

  m.push_back(
    { "ToolVisualAbc",
      {
        "<p><a href=\"ToolVisualAbc.htm\">Visual ABC</a> is an application to work with ABC notation files:",
        "it allows to view the generated sheet music by a single click and to </p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Downloads</h2>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolVisualAbc_1_0.png\">View a screenshot of 'Visual ABC' (version 1.0)(png)</a></li>",
        "  <li><a href=\"ToolVisualAbcSource_1_0.zip\">Download the 'Visual ABC' source code (version 1.0)(zip)</a></li>",
        "  <li><a href=\"ToolVisualAbcSource_1_0.htm\">View the 'Visual ABC' source code as web page (version 1.0)(htm)</a></li>",
        "</ul>"
      }
    }
  );
  m.push_back(
    { "ToolWindowViewer",
      {
        "<p><a href=\"ToolWindowViewer.htm\">WindowViewer</a> is a failed attempt to capture all windows as bitmaps.</p>",
        "<p>&nbsp;</p>",
        "<p><a href=\"ToolWindowViewer.htm\">WindowViewer</a> was released on the 6th of Fubruary of 2010 and programmed in <a href=\"Cpp.htm\">C++</a> using the <a href=\"CppIde.htm\">IDE</a> <a href=\"CppBuilder.htm\">C++ Builder</a> 6.0. It uses the <a href=\"CppStl.htm\">STL</a>, <a href=\"CppBoost.htm\">Boost</a> and <a href=\"CppVcl.htm\">VCL</a> <a href=\"CppLibrary.htm\">libraries</a>.</p>",
        "<p>&nbsp;</p>",
        "<ul>",
        "  <li><a href=\"ToolWindowViewerScreenshot.png\">View a screenshot of 'WindowViewer'</a></li>",
        "  <li><a href=\"ToolWindowViewerExe.zip\">Download the 'WindowViewer' Windows executable (version 1.0)(zip)</a></li>",
        "  <li><a href=\"ToolWindowViewerSource.zip\">Download the 'WindowViewer' source code (version 1.0)(zip)</a></li>",
        "</ul>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Why did it fail?</h2>",
        "<p>&nbsp;</p>",
        "<p>I attempted to use <a href=\"ToolWindowViewer.htm\">WindowViewer</a> to view all the hidden windows the Windows Task Manager makes you aware of. <a href=\"ToolWindowViewer.htm\">WindowViewer</a> does not show those: at the location of where this hidden window is, it obtains the bitmap of what is visible there.</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<p>&nbsp;</p>",
        "<h2>Core code</h2>",
        "<p>&nbsp;</p>",
        "<!-- start of code -->",
        "<table summary=\"TODO\" border = \"1\"><tr><td><code>",
        "<a href=\"CppComment.htm\">//</a><a href=\"CppVector.htm\">std::vector</a>&lt;<a href=\"CppShared_ptr.htm\">boost::shared_ptr</a>&lt;TFormImage&gt; &gt; m_v<br/>",
        "<a href=\"CppComment.htm\">//</a>TFormImage has one member, a <a href=\"CppTImage.htm\">TImage</a> called Image<br/>",
        "&nbsp;<br/>",
        "HWND handle <a href=\"CppOperatorAssign.htm\">=</a> GetWindow(GetForegroundWindow(),GW_HWNDFIRST,<br/>",
        "<b><a href=\"CppInt.htm\">int</a></b> index <a href=\"CppOperatorAssign.htm\">=</a> 0;<br/>",
        "&nbsp;<br/>",
        "<b><a href=\"CppWhile.htm\">while</a></b>(handle)<br/>",
        "{<br/>",
        "&nbsp;&nbsp;<b><a href=\"CppConst.htm\">const</a></b> <b><a href=\"CppInt.htm\">int</a></b> sz <a href=\"CppOperatorAssign.htm\">=</a> 256;<br/>",
        "&nbsp;&nbsp;<b><a href=\"CppChar.htm\">char</a></b> buffer[sz];<br/>",
        "&nbsp;&nbsp;GetWindowText(handle,buffer,sz,<br/>",
        "&nbsp;&nbsp;<b><a href=\"CppConst.htm\">const</a></b> <a href=\"CppString.htm\">std::string</a> text(buffer,<br/>",
        "&nbsp;&nbsp;<b><a href=\"CppIf.htm\">if</a></b> (text.empty())<br/>",
        "&nbsp;&nbsp;{<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;handle <a href=\"CppOperatorAssign.htm\">=</a> GetNextWindow(handle,GW_HWNDNEXT,<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;<b><a href=\"CppContinue.htm\">continue</a></b>;<br/>",
        "&nbsp;&nbsp;}<br/>",
        "&nbsp;<br/>",
        "&nbsp;&nbsp;<b><a href=\"CppIf.htm\">if</a></b> (index <a href=\"CppOperatorEqual.htm\">==</a> <b><a href=\"CppStatic_cast.htm\">static_cast</a></b>&lt;<b><a href=\"CppInt.htm\">int</a></b>&gt;(m_v.size()))<br/>",
        "&nbsp;&nbsp;{<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"CppShared_ptr.htm\">boost::shared_ptr</a>&lt;TFormImage&gt; i(<b><a href=\"CppNew.htm\">new</a></b> TFormImage(0),<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;i-&gt;Image-&gt;Picture-&gt;Bitmap-&gt;PixelFormat <a href=\"CppOperatorAssign.htm\">=</a> pf32bit;<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;i-&gt;Caption <a href=\"CppOperatorAssign.htm\">=</a> \"\";<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;m_v.push_back(i,<br/>",
        "&nbsp;&nbsp;}<br/>",
        "&nbsp;<br/>",
        "&nbsp;&nbsp;RECT rect;<br/>",
        "&nbsp;&nbsp;GetWindowRect(handle,&amp;rect,<br/>",
        "&nbsp;&nbsp;<b><a href=\"CppConst.htm\">const</a></b> <b><a href=\"CppInt.htm\">int</a></b> width  <a href=\"CppOperatorAssign.htm\">=</a> rect.right  <a href=\"CppOperatorMinus.htm\">-</a> rect.left;<br/>",
        "&nbsp;&nbsp;<b><a href=\"CppConst.htm\">const</a></b> <b><a href=\"CppInt.htm\">int</a></b> height <a href=\"CppOperatorAssign.htm\">=</a> rect.bottom <a href=\"CppOperatorMinus.htm\">-</a> rect.top;<br/>",
        "&nbsp;<br/>",
        "&nbsp;&nbsp;Graphics::TBitmap * b <a href=\"CppOperatorAssign.htm\">=</a> m_v[index]-&gt;Image-&gt;Picture-&gt;Bitmap;<br/>",
        "&nbsp;&nbsp;<a href=\"CppAssert.htm\">assert</a>(b,<br/>",
        "&nbsp;&nbsp;<a href=\"CppAssert.htm\">assert</a> (b-&gt;PixelFormat <a href=\"CppOperatorEqual.htm\">==</a> pf32bit,<br/>",
        "&nbsp;<br/>",
        "&nbsp;&nbsp;HDC dc <a href=\"CppOperatorAssign.htm\">=</a> GetDC(handle,<br/>",
        "&nbsp;&nbsp;<b><a href=\"CppIf.htm\">if</a></b> (!dc)<br/>",
        "&nbsp;&nbsp;{<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;handle <a href=\"CppOperatorAssign.htm\">=</a> GetNextWindow(handle,GW_HWNDNEXT,<br/>",
        "&nbsp;&nbsp;&nbsp;&nbsp;<b><a href=\"CppContinue.htm\">continue</a></b>;<br/>",
        "&nbsp;&nbsp;}<br/>",
        "&nbsp;<br/>",
        "&nbsp;&nbsp;m_v[index]-&gt;ClientWidth <a href=\"CppOperatorAssign.htm\">=</a> width;<br/>",
        "&nbsp;&nbsp;m_v[index]-&gt;ClientHeight <a href=\"CppOperatorAssign.htm\">=</a> height;<br/>",
        "&nbsp;&nbsp;b-&gt;Width  <a href=\"CppOperatorAssign.htm\">=</a> width;<br/>",
        "&nbsp;&nbsp;b-&gt;Height <a href=\"CppOperatorAssign.htm\">=</a> height;<br/>",
        "&nbsp;<br/>",
        "&nbsp;&nbsp;BitBlt(b-&gt;Canvas-&gt;Handle, 0, 0, b-&gt;Width, b-&gt;Height, dc, 0, 0, SRCCOPY,<br/>",
        "&nbsp;&nbsp;b-&gt;Modified <a href=\"CppOperatorAssign.htm\">=</a> <b><a href=\"CppTrue.htm\">true</a></b>;<br/>",
        "&nbsp;<br/>",
        "&nbsp;&nbsp;ReleaseDC(handle,dc,<br/>",
        "&nbsp;&nbsp;handle <a href=\"CppOperatorAssign.htm\">=</a> GetNextWindow(handle,GW_HWNDNEXT,<br/>",
        "&nbsp;&nbsp;<a href=\"CppOperatorIncrement.htm\">++</a>index;<br/>",
        "}<br/>",
        "<br/>",
        "</code></td></tr></table>",
        "<!-- end of the code -->"
      }
    }
  );

  m.push_back(
    { "ZZZ_I_MUST_FAIL",
      {
        "<p><ul>This incorrect HTML should be detected in debugging"
      }
    }
  );
  std::map<Key,Value> n;
  std::copy(m.begin(),m.end(),std::inserter(n,n.begin()));
  return n;
}

const std::string ribi::c2h::Info::GetTime() noexcept
{
  const std::time_t t = std::time(0);
  const std::string s = std::ctime( &t);
  return s;
}


const std::string ribi::c2h::Info::GetVersion() noexcept
{
  return "1.1";
}

const std::vector<std::string> ribi::c2h::Info::GetVersionHistory() noexcept
{
  return {
    "2013-09-20: version 1.0: initial versioning, added tests",
    "2013-10-04: version 1.1: added display of when the program is executed"
  };
}

#ifndef NDEBUG
void ribi::c2h::Info::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::c2h::Info::Test");
  {
    const c2h::Info t;
    #ifndef _WIN32
    const std::map<std::string,std::vector<std::string> >& m = t.m_page_info;
    for (const std::pair<std::string,std::vector<std::string> >& p: m)
    {
      std::vector<std::string> v;

      //Add header
      {
        const std::vector<std::string> w { Header::ToHtml(HeaderType::cpp,"TestTitle") };
        std::copy(w.begin(),w.end(),std::back_inserter(v));
      }
      //Text about this page (if known)
      {
        const std::vector<std::string> w = p.second;
        std::copy(w.begin(),w.end(),std::back_inserter(v));
      }
      //Add footer
      {
        const std::vector<std::string> w = Footer::ToHtml(FooterType::cpp);
        std::copy(w.begin(),w.end(),std::back_inserter(v));
      }

      assert(IsTidyInstalled());
      if(!IsCleanHtml(v))
      {
        TRACE("ERROR: invalid HTML in the following c2h::info page");
        TRACE(p.first);
        TRACE("SOLUTION: Clean HTML in ribi::c2h::Info::CreatePageInfo");

        if (p.first == std::string("ZZZ_I_MUST_FAIL")) continue;
      }
      assert(IsCleanHtml(v) && p.first != std::string("ZZZ_I_MUST_FAIL"));
    }
    #endif
    assert(!t.ToHtml("").empty());
  }
  TRACE("Finished ribi::c2h::Info::Test successfully");

}
#endif

const std::vector<std::string> ribi::c2h::Info::ToHtml(const std::string page_name) const
{
  assert(page_name.find('/') == std::string::npos
    && "A c2h::Info page must not contain a slash");
  assert(page_name.find('\\') == std::string::npos
    && "A c2h::Info page must not contain a backslash");

  std::vector<std::string> v;
  {
    const std::string s
      = "<!-- This page is generated by CodeToHtml version "
      + GetVersion()
      + "." + boost::lexical_cast<std::string>(m_page_info.size())
      + " at "
      + GetTime()
      + " -->";
    v.push_back(s);
  }
  if (m_page_info.count(page_name) == 1)
  {
    const std::vector<std::string> w { m_page_info.find(page_name)->second };
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  else
  {
    assert(!v.empty());
    assert(v.size() == 1);
    v[0] = "<!-- No CodeToHtmlInfo about this class with page name " + page_name + "-->";
  }
  return v;
}
