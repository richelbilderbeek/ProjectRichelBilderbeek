//
//  Gnuplot - a C++ class interface with Gnuplot
//  V4.0
//
//  Created by Richel Bilderbeek on Fri Jun 10 2005.
//  Open source.
//
//  Richel Bilderbeek
//  Website: http://www.richelbilderbeek.nl
//
//  V4.0: 19th March 2008: Conformized code
//  V3.0: 23th September 2006: Implemented suggestion by Christoph Schmalz.
//                             According to Christoph it should work under Windows now.
//                             Made the code 100% Standard C++.
//  V2.0: 12th September 2005: Got program to compile under Windows environment.
//                             Program is found NOT to run under Windows.
//                             Somebody has an idea how to open Gnuplot.exe ???
//  V1.0: 10th June 2005: first version developed on Macintosh
//
//
//  This class functions well at a Macintosh. Under Windows, the pipe to the
//  Gnuplot executable (either MS-DOS or Windows executable) will not open.
//  If you have an idea to solve this, please E-mail me.
//
//
//  Feel free to contact me when:
//  - YOU can get the program to run under Windows (and normally it wouldn't)
//  - you encounter a compile error
//  - you have made additional functionality
//  - you have outsmarted me on this interface.
//

#ifndef __GNUPLOT_H
#define __GNUPLOT_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>
#include <ctime>
#include <cassert>

enum GnuplotStyle
{
  styleLines,
  stylePoints,
  styleLinespoints,
  styleImpulses,
  styleDots,
  styleSteps,
  styleErrorbars,
  styleBoxes,
  styleBoxerrorbars,
};

enum GnuplotTerminal
{
  terminalX11,
  terminalAqua
};

struct WindowData
{
  std::vector<std::string> tempFileName;
};

struct Gnuplot
{
  Gnuplot();
  ~Gnuplot();

  void Execute(const std::string&) const;

  void AddWindow(const int nWindows = 1);
  void ChangeWindow(const int);

  void SetTerminal(const GnuplotTerminal&);
  void SetStyle(const GnuplotStyle&);
  void SetYlabel(const std::string&);
  void SetXlabel(const std::string&);

  void Plot(const std::string &, const std::string& title = "y");
  void Plot(const std::vector<double>&, const std::string& title = "y");
  void Plot(const std::vector<double>&, const std::vector<double>&, const std::string& title = "data");
  void Plot(const std::vector<double>&, const std::vector<double>&, const std::vector<double>&, const std::string& title = "z");

  void EmptyPlot();

  //Helper functions
  void Sleep(const double) const;
  const std::string Itoa(const int) const;
  const std::string Ftoa(const double) const;
  const bool FileExists(const std::string& fileName) const;

  private:
  std::FILE * mGnuPipe;
  std::string mTerminal;
  std::string mStyle;
  std::vector<WindowData> mWindowData;
  int mCurrentWindowNumber;
  static int mTempFileNumber;

  void SetLineStyles();
  const std::string ReadFileName() const;
  const std::string CreateTempFileName();
  void CreateTempFile(const std::string&, const std::vector<double>&);
  void CreateTempFile(const std::string&, const std::vector<double>&, const std::vector<double>&);
  void CreateTempFile(const std::string&, const std::vector<double>&, const std::vector<double>&, const std::vector<double>&);
  void PlotTempFile2D(const std::string&, const std::string&);
  void PlotTempFile3D(const std::string&, const std::string&);
  void Dot(const std::string& debugString = ".") const;
};

#endif


