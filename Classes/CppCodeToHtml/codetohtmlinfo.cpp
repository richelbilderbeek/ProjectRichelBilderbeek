//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2013  Richel Bilderbeek

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
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "codetohtmlinfo.h"

#include <cassert>

#include <boost/filesystem.hpp>

//#include "trace.h"

namespace c2h {

Info::Info(const std::string& source)
  : m_page_name(boost::filesystem::basename(source))
{

}

const std::vector<std::string> Info::ToHtml() const
{
  std::vector<std::string> v;
  if (m_page_name == "CppAbout")
  {
    v.push_back("<p><a href=\"CppAbout.htm\">About</a> is a");
    v.push_back("<a href=\"CppClass.htm\">class</a> to display information");
    v.push_back("about a program.</p>");
  }
  else if (m_page_name == "CppAssert")
  {
    v.push_back("<p><a href=\"CppAssert.htm\">assert</a> is a <a href=\"CppMacro.htm\">macro</a> to do run-time <a href=\"CppDebug.htm\">debugging</a> checks. ");
    v.push_back("After <a href=\"CppDebug.htm\">debugging</a>, <a href=\"CppDefine.htm\">#define</a> <a href=\"CppNDEBUG.htm\">NDEBUG</a> ");
    v.push_back("to let the <a href=\"CppPreprocessor.htm\">preprocessor</a> remove all <a href=\"CppAssert.htm\">assert</a>s from your code.</p> ");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>Make use of <a href=\"CppAssert.htm\">assert</a> [1-5].");
    v.push_back("The use of <a href=\"CppAssert.htm\">assert</a> statements can help to ");
    v.push_back("<a href=\"CppDocumentation.htm\">document</a> the assumptions you make when implementing your code [6].</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p><a href=\"CppAssert.htm\">assert</a> is <a href=\"CppDefine.htm\">#define</a>d in <a href=\"CppCassertH.htm\">cassert.h</a>.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<h2>Example</h2>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>A division will only succeed if the denominator is unequal to zero. In your code, you will have to take care that a division by zero never occurs. Using assert, as shown in the code below, will take you to the problem directly.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<!-- start of code -->");
    v.push_back("<table summary = \"assert example\" border = \"1\"><tr><td><code>");
    v.push_back("<a href=\"CppInclude.htm\">#include</a> &lt;<a href=\"CppCassertH.htm\">cassert</a>&gt;<br/>");
    v.push_back("<br/>");
    v.push_back("<b><a href=\"CppInt.htm\">int</a></b> <a href=\"CppMain.htm\">main</a>()<br/>");
    v.push_back("{<br/>");
    v.push_back("&nbsp;&nbsp;<b><a href=\"CppConst.htm\">const</a></b> <b><a href=\"CppDouble.htm\">double</a></b> x = <a href=\"CppComment.htm\">/* something */</a>;<br/>");
    v.push_back("&nbsp;&nbsp;<b><a href=\"CppConst.htm\">const</a></b> <b><a href=\"CppDouble.htm\">double</a></b> y = <a href=\"CppComment.htm\">/* something */</a>;<br/>");
    v.push_back("<br/>");
    v.push_back("&nbsp;&nbsp;<a href=\"CppAssert.htm\">assert</a>(y!=0.0); <a href=\"CppComment.htm\">//</a>Cannot divide by zero<br/>");
    v.push_back("<br/>");
    v.push_back("&nbsp;&nbsp;<b><a href=\"CppConst.htm\">const</a></b> <b><a href=\"CppDouble.htm\">double</a></b> z = x / y;<br/>");
    v.push_back("}<br/>");
    v.push_back("</code></td></tr></table>");
    v.push_back("<!-- end of the code -->");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<h2>Example user-defined <a href=\"CppAssert.htm\">assert</a></h2>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<!-- start of code -->");
    v.push_back("<table summary = \"example code of user-defined assert\" border = \"1\"><tr><td><code>");
    v.push_back("<a href=\"CppComment.htm\">//</a>---------------------------------------------------------------------------<br/>");
    v.push_back("<a href=\"CppComment.htm\">/*</a><br/>");
    v.push_back("Assert, a custom <a href=\"CppAssert.htm\">assert</a> macro<br/>");
    v.push_back("Copyright (C) 2011 Richel Bilderbeek<br/>");
    v.push_back("<br/>");
    v.push_back("This program is free software: you can redistribute it and/or modify<br/>");
    v.push_back("it under the terms of the GNU General Public License as published by<br/>");
    v.push_back("the Free Software Foundation, either version 3 of the License, or<br/>");
    v.push_back("(at your option) any later version.<br/>");
    v.push_back("<br/>");
    v.push_back("This program is distributed in the hope that it will be useful,<br/>");
    v.push_back("but WITHOUT ANY WARRANTY; without even the implied warranty of<br/>");
    v.push_back("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the<br/>");
    v.push_back("GNU General Public License for more details.<br/>");
    v.push_back("<br/>");
    v.push_back("You should have received a copy of the GNU General Public License<br/>");
    v.push_back("along with this program. If not, see &lt;http://www.gnu.org/licenses/&gt;.<br/>");
    v.push_back("<a href=\"CppComment.htm\">*/</a><br/>");
    v.push_back("<a href=\"CppComment.htm\">//</a>---------------------------------------------------------------------------<br/>");
    v.push_back("<a href=\"CppComment.htm\">//</a>From http://www.richelbilderbeek.nl/CppAssert.htm<br/>");
    v.push_back("<a href=\"CppComment.htm\">//</a>---------------------------------------------------------------------------<br/>");
    v.push_back("<a href=\"CppIfndef.htm\">#ifndef</a> BILDERBIKKEL_ASSERT_H<br/>");
    v.push_back("<a href=\"CppDefine.htm\">#define</a> BILDERBIKKEL_ASSERT_H<br/>");
    v.push_back("<a href=\"CppComment.htm\">//</a>---------------------------------------------------------------------------<br/>");
    v.push_back("<a href=\"CppComment.htm\">//</a>From http://www.richelbilderbeek.nl/CppAssert.htm<br/>");
    v.push_back("<a href=\"CppIfdef.htm\">#ifdef</a> <a href=\"CppNDEBUG.htm\">NDEBUG</a>_BILDERBIKKEL<br/>");
    v.push_back("&nbsp;&nbsp;<a href=\"CppDefine.htm\">#define</a> Assert(x) ((<b><a href=\"CppVoid.htm\">void</a></b>)0)<br/>");
    v.push_back("<a href=\"CppPreElse.htm\">#else</a><br/>");
    v.push_back("&nbsp;&nbsp;<a href=\"CppInclude.htm\">#include</a> &lt;<a href=\"CppFstreamH.htm\">fstream</a>&gt;<br/>");
    v.push_back("&nbsp;&nbsp;<a href=\"CppInclude.htm\">#include</a> &lt;<a href=\"CppIostreamH.htm\">iostream</a>&gt;<br/>");
    v.push_back("&nbsp;&nbsp;<a href=\"CppInclude.htm\">#include</a> &lt;<a href=\"CppStdexceptH.htm\">stdexcept</a>&gt;<br/>");
    v.push_back("<br/>");
    v.push_back("&nbsp;&nbsp;<a href=\"CppDefine.htm\">#define</a> Assert(x)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\\<br/>");
    v.push_back("&nbsp;&nbsp;<b><a href=\"CppIf.htm\">if</a></b> (!(x))&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\\<br/>");
    v.push_back("&nbsp;&nbsp;{&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\\<br/>");
    v.push_back("&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"CppCout.htm\">std::cout</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\\<br/>");
    v.push_back("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"CppOperatorStreamOut.htm\">&lt;&lt;</a> \"ERROR!! Assertion \"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\\<br/>");
    v.push_back("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"CppOperatorStreamOut.htm\">&lt;&lt;</a>&nbsp;&nbsp;<a href=\"CppString.htm\">std::string</a> (#x)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; \\<br/>");
    v.push_back("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"CppOperatorStreamOut.htm\">&lt;&lt;</a>&nbsp;&nbsp;\" failed\n on line \"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; \\<br/>");
    v.push_back("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"CppOperatorStreamOut.htm\">&lt;&lt;</a>&nbsp;&nbsp;(__LINE__)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; \\<br/>");
    v.push_back("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"CppOperatorStreamOut.htm\">&lt;&lt;</a>&nbsp;&nbsp;\"\n in file \"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\\<br/>");
    v.push_back("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"CppOperatorStreamOut.htm\">&lt;&lt;</a>&nbsp;&nbsp;__FILE__&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; \\<br/>");
    v.push_back("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"CppOperatorStreamOut.htm\">&lt;&lt;</a> <a href=\"CppEndl.htm\">std::endl</a>;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\\<br/>");
    v.push_back("&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"CppOfstream.htm\">std::ofstream</a> f(\"<a href=\"CppAssert.htm\">assert</a>_out.txt\");&nbsp;&nbsp; \\<br/>");
    v.push_back("&nbsp;&nbsp;&nbsp;&nbsp;f&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\\<br/>");
    v.push_back("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"CppOperatorStreamOut.htm\">&lt;&lt;</a> \"ERROR!! Assertion \"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\\<br/>");
    v.push_back("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"CppOperatorStreamOut.htm\">&lt;&lt;</a>&nbsp;&nbsp;<a href=\"CppString.htm\">std::string</a> (#x)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; \\<br/>");
    v.push_back("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"CppOperatorStreamOut.htm\">&lt;&lt;</a>&nbsp;&nbsp;\" failed\n on line \"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; \\<br/>");
    v.push_back("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"CppOperatorStreamOut.htm\">&lt;&lt;</a>&nbsp;&nbsp;(__LINE__)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; \\<br/>");
    v.push_back("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"CppOperatorStreamOut.htm\">&lt;&lt;</a>&nbsp;&nbsp;\"\n in file \"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\\<br/>");
    v.push_back("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"CppOperatorStreamOut.htm\">&lt;&lt;</a>&nbsp;&nbsp;__FILE__&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; \\<br/>");
    v.push_back("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"CppOperatorStreamOut.htm\">&lt;&lt;</a> <a href=\"CppEndl.htm\">std::endl</a>;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\\<br/>");
    v.push_back("&nbsp;&nbsp;&nbsp;&nbsp;f.close();&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; \\<br/>");
    v.push_back("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b><a href=\"CppThrow.htm\">throw</a></b> <a href=\"CppLogic_error.htm\">std::logic_error</a>(&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\\<br/>");
    v.push_back("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\"Assertion failed\");&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; \\<br/>");
    v.push_back("&nbsp;&nbsp;}<br/>");
    v.push_back("<br/>");
    v.push_back("<a href=\"CppEndif.htm\">#endif</a><br/>");
    v.push_back("<a href=\"CppComment.htm\">//</a>---------------------------------------------------------------------------<br/>");
    v.push_back("<a href=\"CppEndif.htm\">#endif</a> <a href=\"CppOperatorDivide.htm\">/</a><a href=\"CppOperatorDivide.htm\">/</a> BILDERBIKKEL_ASSERT_H<br/>");
    v.push_back("</code></td></tr></table>");
    v.push_back("<!-- end of the code -->");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<h2>User-defined <a href=\"CppAssert.htm\">assert</a>s for specific <a href=\"CppIde.htm\">IDE</a>'s</h2>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<ol>");
    v.push_back("  <li><a href=\"CppBuilderAssert.htm\">Assert in a C++ Builder console Application</a></li>");
    v.push_back("  <li><a href=\"CppQtAssert.htm\">Assert in a Qt Creator console Application</a></li>");
    v.push_back("</ol>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<h2><a href=\"CppReferences.htm\">References</a></h2>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<ol>");
    v.push_back("  <li><a href=\"CppHerbSutter.htm\">Herb Sutter</a>, <a href=\"CppAndreiAlexandrescu.htm\">Andrei Alexandrescu</a>. C++ coding standards: 101 rules, guidelines, and best practices. ISBN: 0-32-111358-6. Chapter 68: 'Assert liberally to document internal assumptions and invariants'</li>");
    v.push_back("  <li><a href=\"CppBjarneStroustrup.htm\">Bjarne Stroustrup</a>. The C++ Programming Language (3rd edition). 1997. ISBN: 0-201-88954-4. Advice 24.5.18: 'Explicitly express preconditions, postconditions, and other assertions as assertions'</li>");
    v.push_back("  <li>Steve McConnell. Code Complete (2nd edition). 2004. ISBN: -735619670. Chapter 8.2 'Assertions', paragraph 'Guidelines for using asserts': 'Use assertions to document and verify preconditions and postconditions'</li>");
    v.push_back("  <li>Steve McConnell. Code Complete (2nd edition). 2004. ISBN: -735619670. Chapter 8.2 'Assertions', paragraph 'Guidelines for using asserts': 'Use assertions for conditions that should never occur'.</li>");
    v.push_back("  <li><a href=\"CppJesseLiberty.htm\">Jesse Liberty</a>. Sams teach yourself C++ in 24 hours. ISBN: 0-672-32224-2. Hour 24, chapter 'assert()': 'Use assert freely'</li>");
    v.push_back("  <li><a href=\"CppJohnLakos.htm\">John Lakos</a>. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Chapter 2.6: 'The use of assert statements can help to document the assumptions you make when implementing your code<'/li>");
    v.push_back("</ol>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
  }
  else if (m_page_name == "CppAsciiArter")
  {
    v.push_back("<p><a href=\"CppAsciiArter.htm\">AsciiArter</a> is a");
    v.push_back("GUI-independent <a href=\"CppClass.htm\">class</a> to");
    v.push_back("<a href=\"CppConvert.htm\">convert</a> images to");
    v.push_back("<a href=\"CppAsciiArt.htm\">ASCII art</a>.</p>");
  }
  else if (m_page_name == "CppBinaryNewickVector")
  {
    v.push_back("<p><a href=\"CppBinaryNewickVector.htm\">BinaryNewickVector</a> is a <a href=\"CppDataType.htm\">data type</a> ");
    v.push_back("for storing phylogenies in the <a href=\"CppNewick.htm\">Newick</a> format.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>The <a href=\"Tools.htm\">tool</a> <a href=\"ToolTestBinaryNewickVector.htm\">TestBinaryNewickVector</a> ");
    v.push_back("is a GUI to test and experiment with <a href=\"CppBinaryNewickVector.htm\">BinaryNewickVector</a>.</p>");
    v.push_back("<p>&nbsp;</p>");
  }
  else if (m_page_name == "CppChess")
  {
    v.push_back("<p><a href=\"CppChess.htm\">Chess</a> has many chess <a href=\"CppClass.htm\">classes</a></p>");
  }
  else if (m_page_name == "CppConnectThree")
  {
    v.push_back("<p><a href=\"CppConnectThree.htm\">ConnectThree</a> is a <a href=\"CppClass.htm\">class</a>");
    v.push_back("for a <a href=\"GameConnectThree.htm\">ConnectThree game</a>.</p>");
  }
  else if (m_page_name == "CppConnectThreeWidget")
  {
    v.push_back("<p><a href=\"CppConnectThreeWidget.htm\">ConnectThreeWidget</a> is a <a href=\"CppWidget.htm\">widget</a>");
    v.push_back("for a <a href=\"GameConnectThree.htm\">ConnectThree game</a>.</p>");
  }
  else if (m_page_name == "CppCopy_if")
  {
    v.push_back("<p><a href=\"CppCopy_if.htm\">copy_if</a> is an <a href=\"CppAlgorithm.htm\">algorithm</a> that was dropped ");
    v.push_back("from the <a href=\"Cpp98.htm\">C++98</a> <a href=\"CppStl.htm\">STL</a> by accident, but added to the");
    v.push_back("<a href=\"Cpp11.htm\">C++11</a> <a href=\"CppStl.htm\">STL</a>.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<h2><img src=\"PicCpp98.png\" alt=\"C++98\"/> <a href=\"CppCopy_if.htm\">std::copy_if</a></h2>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p><a href=\"CppCopy_if.htm\">std::copy_if</a> is an <a href=\"CppAlgorithm.htm\">algorithm</a> that was dropped ");
    v.push_back("from the <a href=\"Cpp98.htm\">C++98</a> <a href=\"CppStl.htm\">STL</a> by accident.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>Prefer <a href=\"CppAlgorithm.htm\">algorithm</a> calls over hand-written loops [1][2].</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<h3><img src=\"PicCpp98.png\" alt=\"C++98\"/> Example <a href=\"CppDefinition.htm\">definition</a> of <a href=\"CppCopy_if.htm\">copy_if</a></h3>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<!-- start of code -->");
    v.push_back("<table summary = \"copy_if definition\" border = \"1\"><tr><td><code>");
    v.push_back("<a href=\"CppComment.htm\">//</a><a href=\"CppCopy_if.htm\">Copy_if</a> was dropped from the standard library by accident.<br/>");
    v.push_back("<b><a href=\"CppTemplate.htm\">template</a></b>&lt;<b><a href=\"CppTypename.htm\">typename</a></b> In, <b><a href=\"CppTypename.htm\">typename</a></b> Out, <b><a href=\"CppTypename.htm\">typename</a></b> Pred&gt;<br/>");
    v.push_back("Out <a href=\"CppCopy_if.htm\">Copy_if</a>(In first, In last, Out res, Pred Pr)<br/>");
    v.push_back("{<br/>");
    v.push_back("&nbsp;&nbsp;<b><a href=\"CppWhile.htm\">while</a></b> (first <a href=\"CppOperatorNotEqual.htm\">!=</a> last)<br/>");
    v.push_back("&nbsp;&nbsp;{<br/>");
    v.push_back("&nbsp;&nbsp;&nbsp;&nbsp;<b><a href=\"CppIf.htm\">if</a></b> (Pr(*first))<br/>");
    v.push_back("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*res<a href=\"CppOperatorIncrement.htm\">++</a> = *first;<br/>");
    v.push_back("&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"CppOperatorIncrement.htm\">++</a>first;<br/>");
    v.push_back("&nbsp;&nbsp;}<br/>");
    v.push_back("&nbsp;&nbsp;<b><a href=\"CppReturn.htm\">return</a></b> res;<br/>");
    v.push_back("}<br/>");
    v.push_back("</code></td></tr></table>");
    v.push_back("<!-- end of the code -->");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<h2><img src=\"PicCpp11.png\" alt=\"C++11\"/> <a href=\"CppCopy_if.htm\">std::copy_if</a></h2>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p><a href=\"CppCopy_if.htm\">std::copy_if</a> is an <a href=\"CppAlgorithm.htm\">algorithm</a> similar to");
    v.push_back("<a href=\"CppCopy.htm\">std::copy</a>, except that a <a href=\"CppPredicate.htm\">predicate</a> can also");
    v.push_back("be supplied. <a href=\"CppCopy_if.htm\">std::copy_if</a> resides in the <a href=\"Cpp11.htm\">C++11</a> ");
    v.push_back("<a href=\"CppStl.htm\">STL</a> <a href=\"CppHeaderFile.htm\">header file</a> <a href=\"CppAlgorithmH.htm\">algorithm</a>.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<ul>");
    v.push_back("  <li><a href=\"CppCopy_if.htm\">Download the Qt Creator project 'CppCopy_if' (zip)</a></li>");
    v.push_back("</ul>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<!-- start of code -->");
    v.push_back("<table summary = \"CppCopy_if code\" border = \"1\"><tr><td><code>");
    v.push_back("<a href=\"CppInclude.htm\">#include</a> &lt;<a href=\"CppAlgorithmH.htm\">algorithm</a>&gt;<br/>");
    v.push_back("<a href=\"CppInclude.htm\">#include</a> &lt;<a href=\"CppCassertH.htm\">cassert</a>&gt;<br/>");
    v.push_back("<a href=\"CppInclude.htm\">#include</a> &lt;<a href=\"CppVectorH.htm\">vector</a>&gt;<br/>");
    v.push_back("<br/>");
    v.push_back("<b><a href=\"CppInt.htm\">int</a></b> <a href=\"CppMain.htm\">main</a>()<br/>");
    v.push_back("{<br/>");
    v.push_back("&nbsp;&nbsp;<a href=\"CppComment.htm\">//</a><a href=\"Cpp11.htm\">C++11</a> <a href=\"CppInitializerList.htm\">initializer list</a><br/>");
    v.push_back("&nbsp;&nbsp;<b><a href=\"CppConst.htm\">const</a></b> <a href=\"CppVector.htm\">std::vector</a>&lt;<b><a href=\"CppInt.htm\">int</a></b>&gt; v <a href=\"CppOperatorAssign.htm\">=</a> { 0,1,2,3,4,5,6 };<br/>");
    v.push_back("<br/>");
    v.push_back("&nbsp;&nbsp;<a href=\"CppComment.htm\">//</a>Only copy the even values to w<br/>");
    v.push_back("&nbsp;&nbsp;<a href=\"CppComment.htm\">//</a><b><a href=\"CppUsing.htm\">using</a></b> <a href=\"Cpp11.htm\">C++11</a> <a href=\"CppLambdaExpression.htm\">lambda expression</a><br/>");
    v.push_back("&nbsp;&nbsp;<a href=\"CppVector.htm\">std::vector</a>&lt;<b><a href=\"CppInt.htm\">int</a></b>&gt; w;<br/>");
    v.push_back("&nbsp;&nbsp;<a href=\"CppCopy_if.htm\">std::copy_if</a>(v.begin(), v.end(),<br/>");
    v.push_back("&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"CppBack_inserter.htm\">std::back_inserter</a>(w),<br/>");
    v.push_back("&nbsp;&nbsp;&nbsp;&nbsp;[](<b><a href=\"CppConst.htm\">const</a></b> <b><a href=\"CppInt.htm\">int</a></b> i) { <b><a href=\"CppReturn.htm\">return</a></b> i <a href=\"CppOperatorModulus.htm\">%</a> 2 <a href=\"CppOperatorEqual.htm\">==</a> 0; } );<br/>");
    v.push_back("<br/>");
    v.push_back("&nbsp;&nbsp;<a href=\"CppComment.htm\">//</a>Check all even values are indeed copied<br/>");
    v.push_back("&nbsp;&nbsp;<a href=\"CppComment.htm\">//</a><b><a href=\"CppUsing.htm\">using</a></b> another <a href=\"Cpp11.htm\">C++11</a> <a href=\"CppInitializerList.htm\">initializer list</a><br/>");
    v.push_back("&nbsp;&nbsp;<a href=\"CppAssert.htm\">assert</a>(w <a href=\"CppOperatorEqual.htm\">==</a> <a href=\"CppVector.htm\">std::vector</a>&lt;<b><a href=\"CppInt.htm\">int</a></b>&gt;( { 0,2,4,6 } ) );<br/>");
    v.push_back("}<br/>");
    v.push_back("</code></td></tr></table>");
    v.push_back("<!-- end of the code -->");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>Prefer <a href=\"CppAlgorithm.htm\">algorithm</a> calls over hand-written loops [1][2].</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<h2><a href=\"CppReferences.htm\">References</a></h2>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<ol>");
    v.push_back("  <li><a href=\"CppBjarneStroustrup.htm\">Bjarne Stroustrup</a>. The C++ Programming Language (3rd edition). 1997. ISBN: 0-201-88954-4. Chapter 18.12.1: 'Prefer algorithms to loops.</li>");
    v.push_back("  <li><a href=\"CppScottMeyers.htm\">Scott Meyers</a>. Effective STL. ISBN: 0-201-74962-9. Item 43: 'Prefer algorithm calls over hand-written loops'</li>");
    v.push_back("</ol>");
    v.push_back("");
  }
  else if (m_page_name == "CppCounter")
  {
    v.push_back("<p><a href=\"CppCounter.htm\">Counter</a> is a <a href=\"CppClass.htm\">class</a>");
    v.push_back("for tallying.</p>");
  }
  else if (m_page_name == "CppDial")
  {
    v.push_back("<p><a href=\"CppDial.htm\">Dial</a> is a <a href=\"CppClass.htm\">class</a> for a dial.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p><a href=\"CppDial.htm\">Dial</a> is displayed by ");
    v.push_back("<a href=\"CppQtDialWidget.htm\">QtDialWidget</a> and <a href=\"CppWtDialWidget.htm\">WtDialWidget</a>.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p><a href=\"CppDial.htm\">Dial</a> is used in (among others) the <a href=\"Tools.htm\">tool</a>");
    v.push_back("<a href=\"ToolTestDial.htm\">TestDial</a>.</p>");
  }
  else if (m_page_name == "CppDialWidget")
  {
    v.push_back("<p><a href=\"CppDialWidget.htm\">DialWidget</a> is a <a href=\"CppDial.htm\">Dial</a> <a href=\"CppWidget.htm\">widget</a>.</p>");
  }
  else if (m_page_name == "CppEncranger")
  {
    v.push_back("<p><a href=\"CppEncranger.htm\">Encranger</a> is one of my own");
    v.push_back("<a href=\"CppCryptography.htm\">cryptography</a> <a href=\"CppClass.htm\">classes</a>.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p><a href=\"CppEncranger.htm\">Encranger</a> is used in, among others:</p>");
    v.push_back("<ul>");
    v.push_back("  <li><a href=\"ToolTestEncranger.htm\">TestEncranger</a></li>");
    v.push_back("  <li><a href=\"ProjectWtWebsite.htm\">ProjectWtWebsite</a></li>");
    v.push_back("</ul>");
  }
  else if (m_page_name == "CppFuzzy_equal_to")
  {
    v.push_back("<p><a href=\"CppFuzzy_equal_to.htm\">fuzzy_equal_to</a> is a <a href=\"CppPredicate.htm\">predicate</a> ");
    v.push_back("to test two <a href=\"CppDouble.htm\">doubles</a> for equality with a certain tolerance. ");
    v.push_back("A tolerance of 0.0 denotes that an exact match is requested. Note that the value of 0.0 cannot");
    v.push_back("be compared fuzzily.</p>");
  }
  else if (m_page_name == "CppHtmlPage")
  {
    v.push_back("<p><a href=\"CppHtmlPage.htm\">HtmlPage</a> is a <a href=\"CppClass.htm\">class</a>");
    v.push_back("for processing an HTML page.</p>");

  }
  else if (m_page_name == "CppIpAddress")
  {
    v.push_back("<p><a href=\"CppIpAddress.htm\">IpAddress</a> is a <a href=\"CppClass.htm\">class</a>");
    v.push_back("for containing an IP address.</p>");
  }
  else if (m_page_name == "CppLed")
  {
    v.push_back("<p><a href=\"CppLed.htm\">Led</a> is a <a href=\"CppClass.htm\">class</a> for an LED light.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p><a href=\"CppLed.htm\">Led</a> is used in the <a href=\"Tools.htm\">tool</a> <a href=\"ToolTestLed.htm\">TestLed</a>.</p>");
  }
  else if (m_page_name == "CppLedWidget")
  {
    v.push_back("<p><a href=\"CppLedWidget.htm\">LedWidget</a> is a <a href=\"CppLed.htm\">Led</a> <a href=\"CppWidget.htm\">widget</a>.</p>");
  }
  else if (m_page_name == "CppLoopReader")
  {
    v.push_back("<p><a href=\"CppLoopReader.htm\">LoopReader</a> is a");
    v.push_back("<a href=\"CppTemplateClass.htm\">template class</a> to iterate");
    v.push_back("through a <a href=\"CppContainer.htm\">container</a>. If the <a href=\"CppContainer.htm\">container</a>'s end is");
    v.push_back("reached, however, <a href=\"CppLoopReader.htm\">LoopReader</a> starts reading");
    v.push_back("from the beginning again.</p>");
  }
  else if (m_page_name == "CppManyDigitNewick")
  {
    v.push_back("<p>A <a href=\"CppNewick.htm\">Newick</a> <a href=\"CppClass.htm\">class</a>.</p>");
  }
  else if (m_page_name == "CppMultipleChoiceQuestion")
  {
    v.push_back("<p><a href=\"CppMultipleChoiceQuestion.htm\">MultipleChoiceQuestion</a> is a <a href=\"CppClass.htm\">class</a> ");
    v.push_back("for a multiple choice <a href=\"CppQuestion.htm\">question</a>.</p>");
  }
  else if (m_page_name == "CppMultipleChoiceQuestionDialog")
  {
    v.push_back("<p><a href=\"CppMultipleChoiceQuestionDialog.htm\">MultipleChoiceQuestionDialog</a> is a dialog ");
    v.push_back("for <a href=\"CppMultipleChoiceQuestion.htm\">MultipleChoiceQuestion</a>.</p>");
  }
  else if (m_page_name == "CppMultiVector")
  {
    v.push_back("<p><a href=\"CppMultiVector.htm\">MultiVector</a> is a <a href=\"CppContainer.htm\">container</a> ");
    v.push_back("<a href=\"CppClass.htm\">class</a> to store elements at indices of any dimensionality.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p><a href=\"CppMultiVector.htm\">MultiVector</a> is demonstrated/tested with the ");
    v.push_back("<a href=\"Tools.htm\">tool</a> <a href=\"ToolTestMultiVector.htm\">TestMultiVector</a>.</p>");
  }
  else if (m_page_name == "CppMusicChord")
  {
    v.push_back("<p><a href=\"CppMusicChord.htm\">MusicChord</a> is a <a href=\"CppClass.htm\">class</a> ");
    v.push_back("for a music chord.</p>");
  }
  else if (m_page_name == "CppMusicNote")
  {
    v.push_back("<p><a href=\"CppMusicNote.htm\">MusicChord</a> is a <a href=\"CppClass.htm\">class</a> ");
    v.push_back("for a music note.</p>");
  }
  else if (m_page_name == "CppMysteryMachine")
  {
    v.push_back("<p><a href=\"CppMysteryMachine.htm\">MysteryMachine</a> is a <a href=\"CppClass.htm\">class</a> to simulate");
    v.push_back("my mystery machine.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p><a href=\"CppMysteryMachine.htm\">MysteryMachine</a> is used in the  ");
    v.push_back("<a href=\"Tools.htm\">tool</a> <a href=\"ToolSimMysteryMachine.htm\">SimMysteryMachine</a>.</p>");
  }
  else if (m_page_name == "CppMysteryMachineWidget")
  {
    v.push_back("<p><a href=\"CppMysteryMachineWidget.htm\">MysteryMachineWidget</a> is a <a href=\"CppMysteryMachineWidget.htm\">MysteryMachineWidget</a> <a href=\"CppWidget.htm\">widget</a>.</p>");
  }
  else if (m_page_name == "CppNewick")
  {
    v.push_back("<p>A <a href=\"CppNewick.htm\">Newick</a> is a way to write down a phylogeny as a <a href=\"CppString.htm\">std::string</a>. This page shows how to check this <a href=\"CppString.htm\">std::string</a> and how to store a <a href=\"CppNewick.htm\">Newick</a> more efficiently.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>Because personally, I only work with <a href=\"CppNewick.htm\">Newicks</a> in the form '(((A,B),(C,D)),E)', these algorithms will so as well.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<h2><a href=\"CppNewick.htm\">Newick</a> <a href=\"CppCodeSnippets.htm\">code snippets</a></h2>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<ol>");
    v.push_back("  <li><a href=\"CppCalcComplexity.htm\">CalcComplexity</a></li>");
    v.push_back("  <li><a href=\"CppCalcNumOfCombinations.htm\">CalcNumOfCombinations</a></li>");
    v.push_back("  <li><a href=\"CppCalcNumOfSymmetries.htm\">CalcNumOfSymmetries</a></li>");
    v.push_back("  <li><a href=\"CppCheckNewick.htm\">CheckNewick</a></li>");
    v.push_back("  <li><a href=\"CppCreateInvalidNewicks.htm\">CreateInvalidNewicks</a></li>");
    v.push_back("  <li><a href=\"CppCreateValidNewicks.htm\">CreateValidNewicks</a></li>");
    v.push_back("  <li><a href=\"CppDumbNewickToString.htm\">DumbNewickToString</a></li>");
    v.push_back("  <li><a href=\"CppGetRootBranches.htm\">GetRootBranches</a></li>");
    v.push_back("  <li><a href=\"CppGetSimplerNewicks.htm\">GetSimplerNewicks</a></li>");
    v.push_back("  <li><a href=\"CppInspectInvalidNewick.htm\">InspectInvalidNewick</a></li>");
    v.push_back("  <li><a href=\"CppIsBinaryNewick.htm\">IsBinaryNewick</a></li>");
    v.push_back("  <li><a href=\"CppIsNewick.htm\">IsNewick</a></li>");
    v.push_back("  <li><a href=\"CppNewickToString.htm\">NewickToString</a></li>");
    v.push_back("  <li><a href=\"CppBinaryNewickVector.htm\">BinaryNewickVector</a></li>");
    v.push_back("  <li><a href=\"CppStringToNewick.htm\">StringToNewick</a></li>");
    v.push_back("</ol>");
  }
  else if (m_page_name == "CppNewickRavindran")
  {
    assert(!"Not allowed");
  }
  else if (m_page_name == "CppNewickVector")
  {
    v.push_back("<p><a href=\"CppNewickVector.htm\">NewickVector</a> is a <a href=\"CppNewick.htm\">Newick</a> <a href=\"CppClass.htm\">class</a>.</p>");
  }
  else if (m_page_name == "CppOpenQuestion")
  {
    v.push_back("<p><a href=\"CppOpenQuestion.htm\">OpenQuestion</a> is a <a href=\"CppClass.htm\">class</a> for an open <a href=\"CppQuestion.htm\">question</a>.</p>");
  }
  else if (m_page_name == "CppOpenQuestionDialog")
  {
    v.push_back("<p><a href=\"CppOpenQuestionDialog.htm\">OpenQuestionDialog</a> is a dialog for <a href=\"CppOpenQuestion.htm\">OpenQuestion</a>.</p>");
  }
  else if (m_page_name == "CppPrimeExpert")
  {
    v.push_back("<p><a href=\"CppPrimeExpert.htm\">PrimeExpert</a> is a <a href=\"CppClass.htm\">class</a> with only one important");
    v.push_back("<a href=\"CppMemberFunction.htm\">member function</a> called <a href=\"CppIsPrime.htm\">IsPrime</a>,");
    v.push_back("which calculates whether a number is prime.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p><a href=\"CppPrimeExpert.htm\">PrimeExpert</a> is a trade-off between the speed of");
    v.push_back("determining whether a number is prime (for multiple times) and memory consumption:");
    v.push_back("to determine whether a number is prime quicker, <a href=\"CppPrimeExpert.htm\">PrimeExpert</a>");
    v.push_back("maintains a <a href=\"CppVector.htm\">std::vector</a> of known primes (but of known primes only).</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p><a href=\"CppPrimeExpert.htm\">PrimeExpert</a> can be tested using the <a href=\"Tools.htm\">tool</a> ");
    v.push_back("<a href=\"ToolTestPrimeExpert.htm\">TestPrimeExpert</a>.</p>");
  }
  else if (m_page_name == "CppProFile" || m_page_name == "CppQtCreatorProFile")
  {
    v.push_back("<p><a href=\"CppQtCreatorProFile.htm\">QtCreatorProFile</a> is a <a href=\"CppQtProjectFile.htm\">Qt project file (.pro)</a>");
    v.push_back("<a href=\"CppClass.htm\">class</a>.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p><a href=\"CppQtCreatorProFile.htm\">QtCreatorProFile</a> is tested by the <a href=\"Tools.htm\">tool</a> ");
    v.push_back("<a href=\"ToolTestQtCreatorProFile.htm\">TestQtCreatorProFile</a>.</p>");
  }
  else if (m_page_name == "CppQtAboutDialog")
  {
    v.push_back("<p><a href=\"CppQtAboutDialog.htm\">QtAboutDialog</a> is a <a href=\"CppQt.htm\">Qt</a> dialog");
    v.push_back("<a href=\"CppClass.htm\">class</a> to display an <a href=\"CppAbout.htm\">About</a>.</p>");
  }
  else if (m_page_name == "CppQtChess")
  {
    v.push_back("<p><a href=\"CppQtChess.htm\">QtChess</a> has many <a href=\"CppQt.htm\">Qt</a> <a href=\"CppChess.htm\">chess</a> <a href=\"CppClass.htm\">classes</a></p>");
  }
  else if (m_page_name == "CppQtConnectThreeWidget")
  {
    v.push_back("<p><a href=\"CppQtConnectThreeWidget.htm\">QtConnectThreeWidget</a> is a <a href=\"CppQt.htm\">Qt</a> <a href=\"CppWidget.htm\">widget</a>");
    v.push_back("<a href=\"CppClass.htm\">class</a> for a responsive connect-three game. <a href=\"CppQtConnectThreeWidget.htm\">QtConnectThreeWidget</a> is");
    v.push_back("used in, among others, the <a href=\"Games.htm\">game</a> <a href=\"GameConnectThree.htm\">ConnectThree</a>.</p>");
  }
  else if (m_page_name == "CppQtDialWidget")
  {
    v.push_back("<p><a href=\"CppQtDialWidget.htm\">QtDialWidget</a> is a <a href=\"CppQt.htm\">Qt</a> ");
    v.push_back("<a href=\"CppClass.htm\">class</a> to display an <a href=\"CppDial.htm\">Dial</a>.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p><a href=\"CppQtDialWidget.htm\">QtDialWidget</a> is used in the <a href=\"Tools.htm\">tool</a> ");
    v.push_back("<a href=\"ToolTestDial.htm\">TestDial</a>.</p>");
  }
  else if (m_page_name == "CppQtLedDisplayWidget")
  {
    v.push_back("<p><a href=\"CppQtLedWidget.htm\">QtLedWidget</a> is a <a href=\"CppQt.htm\">Qt</a> ");
    v.push_back("<a href=\"CppClass.htm\">class</a> to display an <a href=\"CppLed.htm\">Led</a>.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p><a href=\"CppQtLedWidget.htm\">QtLedWidget</a> is used in the <a href=\"Tools.htm\">tool</a> <a href=\"ToolTestLed.htm\">TestLed</a>.</p>");
  }
  else if (m_page_name == "CppQtLedWidget")
  {
    v.push_back("<p><a href=\"CppQtLedWidget.htm\">QtLedWidget</a> is a <a href=\"CppQt.htm\">Qt</a> ");
    v.push_back("<a href=\"CppClass.htm\">class</a> to display an <a href=\"CppLed.htm\">Led</a>.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p><a href=\"CppQtLedWidget.htm\">QtLedWidget</a> is used in the <a href=\"Tools.htm\">tool</a> <a href=\"ToolTestLed.htm\">TestLed</a>.</p>");
  }
  else if (m_page_name == "CppQtMultipleChoiceQuestionDialog")
  {
    v.push_back("<p><a href=\"CppQtMultipleChoiceQuestionDialog.htm\">QtMultipleChoiceQuestionDialog</a> is a ");
    v.push_back("<a href=\"CppQt.htm\">Qt</a> dialog for <a href=\"CppMultipleChoiceQuestion.htm\">MultipleChoiceQuestion</a>.</p>");
  }
  else if (m_page_name == "CppQtMysteryMachineWidget")
  {
    v.push_back("<p><a href=\"CppQtMysteryMachineWidget.htm\">QtMysteryMachineWidget</a> is a <a href=\"CppQt.htm\">Qt</a> ");
    v.push_back("<a href=\"CppClass.htm\">class</a> to display an <a href=\"CppMysteryMachineWidget.htm\">CppMysteryMachineWidget</a>.</p>");
  }
  else if (m_page_name == "CppQtOpenQuestionDialog")
  {
    v.push_back("<p><a href=\"CppQtOpenQuestionDialog.htm\">QtOpenQuestionDialog</a> is a <a href=\"CppQt.htm\">Qt</a> dialog ");
    v.push_back("for <a href=\"CppOpenQuestionDialog.htm\">OpenQuestionDialog</a>.</p>");
  }
  else if (m_page_name == "CppQtQuadBezierArrowItem")
  {
    v.push_back("<p><a href=\"CppQtQuadBezierArrowItem.htm\">QtQuadBezierArrowItem</a> is a <a href=\"CppQGraphicsItem.htm\">QGraphicsItem</a> for displaying a arrow that has a quadratic Bezier curve as its body.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>For the math, see <a href=\"CppQGraphicsPathItemExample5.htm\">QGraphicsPathItem example 5: Bezier quadratic lines with arrow heads</a>.</p>");
  }
  else if (m_page_name == "CppQtQuestionDialog")
  {
    v.push_back("<p><a href=\"CppQtQuestionDialog.htm\">QtQuestionDialog</a> is a <a href=\"CppQt.htm\">Qt</a> dialog for");
    v.push_back("<a href=\"CppQuestionDialog.htm\">QuestionDialog</a>.</p>");
  }
  else if (m_page_name == "CppQtShapeWidget")
  {
    v.push_back("<p><a href=\"CppQtShapeWidget.htm\">QtShapeWidget</a> is a <a href=\"CppQt.htm\">Qt</a> <a href=\"CppWidget.htm\">widget</a>");
    v.push_back("<a href=\"CppClass.htm\">class</a> to display an <a href=\"CppShapeWidget.htm\">ShapeWidget</a>.</p>");
  }
  else if (m_page_name == "CppQtSprites")
  {
    v.push_back("<p><a href=\"CppQtSprites.htm\">QtSprites</a> is a <a href=\"CppClass.htm\">class</a>");
    v.push_back("containing sprites.</p>");

  }
  else if (m_page_name == "CppQtTicTacToeWidget")
  {
    v.push_back("<p><a href=\"CppQtTicTacToeWidget.htm\">QtTicTacToeWidget</a> is a <a href=\"CppQt.htm\">Qt</a> ");
    v.push_back("<a href=\"CppClass.htm\">class</a> to display the <a href=\"CppTicTacToe.htm\">TicTacToe</a> <a href=\"CppClass.htm\">class</a>.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p><a href=\"CppQtTicTacToeWidget.htm\">QtTicTacToeWidget</a> is used by:</p>");
    v.push_back("<ul>");
    v.push_back("  <li><a href=\"GameTicTacToe.htm\">(Game) TicTacToe</a></li>");
    v.push_back("  <li><a href=\"ToolTestTicTacToe.htm\">(Tool) TestTicTacToe</a></li>");
    v.push_back("</ul>");
  }
  else if (m_page_name == "CppQtToggleButtonWidget")
  {
    v.push_back("<p><a href=\"CppQtToggleButtonWidget.htm\">QtToggleButtonWidget</a> is a <a href=\"CppQt.htm\">Qt</a> <a href=\"CppWidget.htm\">widget</a>");
    v.push_back("<a href=\"CppClass.htm\">class</a> to display an <a href=\"CppToggleButtonWidget.htm\">ToggleButtonWidget</a>.</p>");
  }
  else if (m_page_name == "CppQuestion")
  {
    v.push_back("<p><a href=\"CppQuestion.htm\">Question</a> is a <a href=\"CppClass.htm\">class</a> for a question.</p>");
  }
  else if (m_page_name == "CppQuestionDialog")
  {
    v.push_back("<p><a href=\"CppQuestionDialog.htm\">QuestionDialog</a> is a dialog for <a href=\"CppQuestion.htm\">Question</a>.</p>");
  }
  else if (m_page_name == "CppRainbow")
  {
    v.push_back("<p><a href=\"CppRainbow.htm\">Rainbow</a> is a <a href=\"CppGraphics.htm\">graphics</a> <a href=\"CppClass.htm\">class</a> to create a rainbow.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<ul>");
    v.push_back("  <li><a href=\"CppRainbow.png\">View a picture of the gradient created by the Rainbow function (upper row)</a></li>");
    v.push_back("</ul>");
  }
  else if (m_page_name == "CppRandomCode")
  {
    v.push_back("<p><a href=\"CppRandomCode.htm\">RandomCode</a> is a <a href=\"CppClass.htm\">class</a>");
    v.push_back("to generate random <a href=\"Cpp.htm\">C++</a> code.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p><a href=\"CppRandomCode.htm\">RandomCode</a> is used by the <a href=\"Tools.htm\">tool</a>");
    v.push_back("<a href=\"ToolRandomCode.htm\">RandomCode</a>.</p>");
  }
  else if (m_page_name == "CppRectangle")
  {
    v.push_back("<p><a href=\"CppRectangle.htm\">Rectangle</a> is a <a href=\"CppClass.htm\">class</a> for a rectangle.</p>");
  }
  else if (m_page_name == "CppRubiksClock")
  {
    v.push_back("<p><a href=\"CppRubiksClock.htm\">RubiksClock</a> is a <a href=\"CppClass.htm\">class</a> for a Rubik's Clock.</p>");
  }
  else if (m_page_name == "CppRubiksClockWidget")
  {
    v.push_back("<p><a href=\"CppRubiksClockWidget.htm\">RubiksClockWidget</a> is a <a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">class</a> for a <a href=\"CppRubiksClock.htm\">RubiksClock</a>.</p>");
  }
  else if (m_page_name == "CppShape")
  {
    v.push_back("<p><a href=\"CppShape.htm\">Shape</a> is a <a href=\"CppClass.htm\">class</a> for a shape.</p>");
  }
  else if (m_page_name == "CppShapeWidget")
  {
    v.push_back("<p><a href=\"CppShapeWidget.htm\">ShapeWidget</a> is a <a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">class</a> for a <a href=\"CppShape.htm\">Shape</a>.</p>");
  }
  else if (m_page_name == "CppSortedBinaryNewickVector")
  {
    v.push_back("<p><a href=\"CppSortedBinaryNewickVector.htm\">SortedBinaryNewickVector</a> is a <a href=\"CppNewick.htm\">Newick</a> <a href=\"CppClass.htm\">class</a>.</p>");
  }
  else if (m_page_name == "CppStopwatch")
  {
    v.push_back("<p><a href=\"CppStopwatch.htm\">Stopwatch</a> is a <a href=\"CppClass.htm\">class</a> to do time measurements.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>The <a href=\"Tools.htm\">tool</a><a href=\"ToolTestStopwatch.htm\">TestStopwatch</a> tests and manages ");
    v.push_back("<a href=\"CppStopwatch.htm\">Stopwatch</a>.</p>");
  }
  else if (m_page_name == "CppSurvey")
  {
    v.push_back("<p><a href=\"CppSurvey.htm\">Survey</a> is a <a href=\"CppClass.htm\">class</a> for a survey.</p>");
  }
  else if (m_page_name == "CppTicTacToe")
  {
    v.push_back("<p><a href=\"CppTicTacToe.htm\">TicTacToe</a> is a <a href=\"CppClass.htm\">class</a> embodying");
    v.push_back("the game logic of Tic-Tac-Toe.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p><a href=\"CppTicTacToe.htm\">TicTacToe</a> is used by, among others:</p>");
    v.push_back("<ul>");
    v.push_back("  <li><a href=\"ProjectWtWebsite.htm\">ProjectWtWebsite</a></li>");
    v.push_back("  <li><a href=\"ToolTestTicTacToe.htm\">TestTicTacToe</a></li>");
    v.push_back("</ul>");
  }
  else if (m_page_name == "CppToggleButton")
  {
    v.push_back("<p><a href=\"CppToggleButton.htm\">ToggleButton</a> is a <a href=\"CppClass.htm\">class</a> for a toggle button.</p>");
  }
  else if (m_page_name == "CppToggleButtonWidget")
  {
    v.push_back("<p><a href=\"CppToggleButtonWidget.htm\">ToggleButtonWidget</a> is a <a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">class</a> for a <a href=\"CppToggleButton.htm\">ToggleButton</a>.</p>");
  }
  else if (m_page_name == "CppTrace")
  {
    v.push_back("<p><a href=\"CppTrace.htm\">To trace</a> something (for example, the value of a <a href=\"CppVariable.htm\">variable</a>),");
    v.push_back("denotes displaying it while <a href=\"CppDebug.htm\">debugging</a>.</p>");
  }
  else if (m_page_name == "CppTwoDigitNewick")
  {
    v.push_back("<p><a href=\"CppTwoDigitNewick.htm\">TwoDigitNewick</a> is a <a href=\"CppNewick.htm\">Newick</a> <a href=\"CppClass.htm\">class</a>.</p>");
  }
  else if (m_page_name == "CppWidget")
  {
    v.push_back("<p>A <a href=\"CppWidget.htm\">widget</a>/control is a user interface element, like a button or checkbox.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p><a href=\"CppWidget.htm\">Widget</a> is a GUI independent <a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">class</a>");
    v.push_back("and servers as a <a href=\"CppBaseClass.htm\">base class</a> for others (incomplete list):</p>");
    v.push_back("<ul>");
    v.push_back("  <li><a href=\"CppQtDialWidget.htm\">QtDialWidget</a></li>");
    v.push_back("  <li><a href=\"CppQtLedWidget.htm\">QtLedWidget</a></li>");
    v.push_back("  <li><a href=\"CppQtShapeWidget.htm\">QtShapeWidget</a></li>");
    v.push_back("  <li><a href=\"CppDialWidget.htm\">DialWidget</a></li>");
    v.push_back("  <li><a href=\"CppLedWidget.htm\">LedWidget</a></li>");
    v.push_back("  <li><a href=\"CppShapeWidget.htm\">ShapeWidget</a></li>");
    v.push_back("  <li><a href=\"CppWtDialWidget.htm\">WtDialWidget</a></li>");
    v.push_back("  <li><a href=\"CppWtLedWidget.htm\">WtLedWidget</a></li>");
    v.push_back("  <li><a href=\"CppWtShapeWidget.htm\">WtShapeWidget</a></li>");
    v.push_back("</ul>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>Similar <a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">classes</a> are ");
    v.push_back("<a href=\"CppQWidget.htm\">QWidget</a> and <a href=\"CppWWidget.htm\">Wt::WWidget</a>.</p>");
  }
  else if (m_page_name == "CppWtAboutDialog")
  {
    v.push_back("<p><a href=\"CppWtAboutDialog.htm\">WtAboutDialog</a> is a <a href=\"CppClass.htm\">class</a> for");
    v.push_back("a <a href=\"CppWt.htm\">Wt</a> dialog displaying the <a href=\"CppAbout.htm\">About</a> <a href=\"CppClass.htm\">class</a>.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p><a href=\"CppWtAboutDialog.htm\">WtAboutDialog</a> is used in nearly all my web applications.</p>");
  }
  else if (m_page_name == "CppWtAutoConfig")
  {
    v.push_back("<p><a href=\"CppWtAutoConfig.htm\">WtAutoConfig</a> is a <a href=\"CppWt.htm\">Wt</a> <a href=\"CppClass.htm\">class</a>");
    v.push_back("that allows to start a <a href=\"CppWt.htm\">Wt</a> application without the need of a user giving ");
    v.push_back("command-line parameters. It is a fine starting point for a <a href=\"CppWt.htm\">Wt</a> application.</p>");
  }
  else if (m_page_name == "CppWtBroadcastServer")
  {
    v.push_back("<p><a href=\"CppWtBroadcastServer.htm\">WtBroadcastServer</a> has been abandoned, because it served two tasks. It is split up into and replaced");
    v.push_back("by <a href=\"CppWtServerPusher.htm\">WtServerPusher</a> and <a href=\"CppWtTimedServerPusher.htm\">WtTimedServerPusher</a>.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p><a href=\"CppWtBroadcastServerClient.htm\">WtBroadcastServerClient</a> has been abandoned, because it served two tasks. It is split up into and replaced");
    v.push_back("by <a href=\"CppWtServerPusherClient.htm\">WtServerPusherClient</a> and <a href=\"CppWtTimedServerPusherClient.htm\">WtTimedServerPusherClient</a>.</p>");
  }
  else if (m_page_name == "CppWtConnectThreeWidget")
  {
    v.push_back("<p><a href=\"CppWtConnectThreeWidget.htm\">WtConnectThreeWidget</a> is a <a href=\"CppWt.htm\">Wt</a> ");
    v.push_back("<a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">class</a> to display an <a href=\"CppConnectThreeWidget.htm\">ConnectThreeWidget</a>.</p>");
  }
  else if (m_page_name == "CppWtDialWidget")
  {
    v.push_back("<p><a href=\"CppWtDialWidget.htm\">WtDialWidget</a> is a <a href=\"CppWt.htm\">Wt</a> ");
    v.push_back("<a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">class</a> to display an <a href=\"CppDialWidget.htm\">DialWidget</a>.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p><a href=\"CppWtDialWidget.htm\">WtDialWidget</a> is used in the <a href=\"Tools.htm\">tool</a> ");
    v.push_back("<a href=\"ToolTestDial.htm\">TestDial</a>.</p>");
  }
  else if (m_page_name == "CppWtGroupWidget")
  {
    v.push_back("<p><a href=\"CppWtGroupWidget.htm\">WtGroupWidget</a> is a <a href=\"CppWt.htm\">Wt</a> ");
    v.push_back("<a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">class</a> to display an <a href=\"CppGroupWidget.htm\">GroupWidget</a>.</p>");
  }
  else if (m_page_name == "CppWtLedDisplayWidget")
  {
    v.push_back("<p><a href=\"CppWtLedDisplayWidget.htm\">WtLedDisplayWidget</a> is a <a href=\"CppWt.htm\">Wt</a> ");
    v.push_back("<a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">class</a> to display an <a href=\"CppLedWidget.htm\">CppLedWidget</a>.</p>");
  }
  else if (m_page_name == "CppWtLedWidget")
  {
    v.push_back("<p><a href=\"CppWtLedWidget.htm\">WtLedWidget</a> is a <a href=\"CppWt.htm\">Wt</a> ");
    v.push_back("<a href=\"CppClass.htm\">class</a> to display an <a href=\"CppLed.htm\">Led</a>.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p><a href=\"CppWtLedWidget.htm\">WtLedWidget</a> is used in the <a href=\"Tools.htm\">tool</a> ");
    v.push_back("<a href=\"ToolTestLed.htm\">TestLed</a>.</p>");
  }
  else if (m_page_name == "CppWtMultipleChoiceQuestionDialog")
  {
    v.push_back("<p><a href=\"CppWtMultipleChoiceQuestionDialog.htm\">WtMultipleChoiceQuestionDialog</a> is a <a href=\"CppWt.htm\">Wt</a> dialog ");
    v.push_back("for <a href=\"CppMultipleChoiceQuestion.htm\">MultipleChoiceQuestion</a>.</p>");
  }
  else if (m_page_name == "CppWtMysteryMachineWidget")
  {
    v.push_back("<p><a href=\"CppWtMysteryMachineWidget.htm\">WtMysteryMachineWidget</a> is a <a href=\"CppWt.htm\">Wt</a> ");
    v.push_back("<a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">class</a> to display an <a href=\"CppMysteryMachineWidget.htm\">MysteryMachineWidget</a>.</p>");
  }
  else if (m_page_name == "CppWtOpenQuestionDialog")
  {
    v.push_back("<p><a href=\"CppWtOpenQuestionDialog.htm\">WtOpenQuestionDialog</a> is a <a href=\"CppWt.htm\">Wt</a> dialog ");
    v.push_back("for <a href=\"CppOpenQuestionDialog.htm\">OpenQuestionDialog</a>.</p>");
  }
  else if (m_page_name == "CppWtQuestionDialog")
  {
    v.push_back("<p><a href=\"CppWtQuestionDialog.htm\">WtQuestionDialog</a> is a <a href=\"CppWt.htm\">Wt</a> dialog ");
    v.push_back("for <a href=\"CppQuestionDialog.htm\">QuestionDialog</a>.</p>");
  }
  else if (m_page_name == "CppWtRubiksClockWidget")
  {
    v.push_back("<p><a href=\"CppWtRubiksClockWidget.htm\">WtRubiksClockWidget</a> is a <a href=\"CppWt.htm\">Wt</a> ");
    v.push_back("<a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">class</a> to display an <a href=\"CppRubiksClockWidget.htm\">RubiksClockWidget</a>.</p>");
  }
  else if (m_page_name == "CppWtSafeTimer")
  {
    v.push_back("<p><a href=\"CppWtSafeTimer.htm\">WtSafeTimer</a> is a <a href=\"CppForwardDeclaration.htm\">forward-declaration</a>-safe ");
    v.push_back("<a href=\"CppWTimer.htm\">Wt::WTimer</a>.</p>");
  }
  else if (m_page_name == "CppWtSelectFileDialog")
  {
    v.push_back("<p><a href=\"CppWtSelectFileDialog.htm\">WtSelectFileDialog</a> is a <a href=\"CppWt.htm\">Wt</a> ");
    v.push_back("<a href=\"CppClass.htm\">class</a> to let a user select a file from the server. To let a user select a file from his/her");
    v.push_back("computer, the <a href=\"CppWFileUpload.htm\">Wt::WFileUpload</a> <a href=\"CppClass.htm\">class</a> might be convenient.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p><a href=\"ToolTestSelectFileDialog.htm\">TestSelectFileDialog</a> is a <a href=\"Tools.htm\">tool</a> to test ");
    v.push_back("the <a href=\"CppWtSelectFileDialog.htm\">WtSelectFileDialog</a> <a href=\"CppClass.htm\">class</a>.</p>");
  }
  else if (m_page_name == "CppWtServerPusher")
  {
    v.push_back("<p><a href=\"CppWtShapeGroupWidget.htm\">WtShapeGroupWidget</a> is a <a href=\"CppWt.htm\">Wt</a> ");
    v.push_back("<a href=\"CppClass.htm\">class</a> used for notifying all clients from different IP addresses.</p>");
  }
  else if (m_page_name == "CppWtShapeGroupWidget")
  {
    v.push_back("<p><a href=\"CppWtShapeGroupWidget.htm\">WtShapeGroupWidget</a> is a <a href=\"CppWt.htm\">Wt</a> ");
    v.push_back("<a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">class</a> to display an <a href=\"CppShapeGroupWidget.htm\">ShapeGroupWidget</a>.</p>");
  }
  else if (m_page_name == "CppWtShapeWidget")
  {
    v.push_back("<p><a href=\"CppWtShapeWidget.htm\">WtShapeWidget</a> is a <a href=\"CppWt.htm\">Wt</a> ");
    v.push_back("<a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">class</a> to display an <a href=\"CppShapeWidget.htm\">ShapeWidget</a>.</p>");
  }
  else if (m_page_name == "CppWtTicTacToeWidget")
  {
    v.push_back("<p><a href=\"CppWtTicTacToeWidget.htm\">WtTicTacToeWidget</a> is a <a href=\"CppWt.htm\">Wt</a> ");
    v.push_back("<a href=\"CppClass.htm\">class</a> to display the <a href=\"CppTicTacToe.htm\">TicTacToe</a> <a href=\"CppClass.htm\">class</a>.</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p><a href=\"CppWtTicTacToeWidget.htm\">WtTicTacToeWidget</a> is used by:</p>");
    v.push_back("<ul>");
    v.push_back("  <li><a href=\"GameTicTacToe.htm\">(Game) TicTacToe</a></li>");
    v.push_back("  <li><a href=\"ToolTestTicTacToe.htm\">(Tool) TestTicTacToe</a></li>");
    v.push_back("</ul>");
  }
  else if (m_page_name == "CppWtTimedServerPusher")
  {
    v.push_back("<p><a href=\"CppWtShapeGroupWidget.htm\">WtShapeGroupWidget</a> is a <a href=\"CppWt.htm\">Wt</a> ");
    v.push_back("<a href=\"CppClass.htm\">class</a> used for notifying all clients from different IP addresses.</p>");
  }
  else if (m_page_name == "CppWtToggleButtonWidget")
  {
    v.push_back("<p><a href=\"CppWtToggleButtonWidget.htm\">WtToggleButtonWidget</a> is a <a href=\"CppWt.htm\">Wt</a> ");
    v.push_back("<a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">class</a> to display an <a href=\"CppToggleButtonWidget.htm\">ToggleButtonWidget</a>.</p>");
  }
  else if (m_page_name == "CppWtWidgetsWidget")
  {
    v.push_back("<p><a href=\"CppWtWidgetsWidget.htm\">WtWidgetsWidget</a> is a <a href=\"CppWt.htm\">Wt</a> ");
    v.push_back("<a href=\"CppWidget.htm\">widget</a> <a href=\"CppClass.htm\">class</a> to display an <a href=\"CppWidgetsWidget.htm\">WidgetsWidget</a>.</p>");
  }
  else if (m_page_name == "ToolCodeToHtml")
  {
    v.push_back("<p><a href=\"ToolCodeToHtml.htm\">ToolCodeToHtml</a> source code.</p>");
  }
  else
  {
    v.push_back("<!-- No CodeToHtmlInfo about this class with page name " + m_page_name + "-->");
  }
  if (!v.empty())
  {
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
    v.push_back("<p>&nbsp;</p>");
  }
  return v;
}

} //~namespace CodeToHtml

