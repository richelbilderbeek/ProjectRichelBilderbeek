//
//  Gnuplot - a C++ class interface with Gnuplot
//
//
//  Created by Richel Bilderbeek on Fri Jun 10 2005.
//  Open source.
//
//  Richel Bilderbeek
//  Vinkenstraat 54b
//  9713 TJ Groningen
//  The Netherlands
//  (0031)-(0)50-3115529
//  E-mail: richelbilderbeek@fastmail.fm
//  
//  Feel free to contact me when having made additional functionality or
//  have outsmarted me on this interface
// 
//

#ifndef __GNUPLOT_H
#define __GNUPLOT_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <assert.h>

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

///Fiund out more terminal types using 'set terminal' in Gnuplot
enum GnuplotTerminal
{
	terminalX11,
	terminalAqua
};

struct WindowData
{
	std::vector<std::string> tempFileName;
};

class Gnuplot
{
	private:
	FILE * mGnuPipe;
	std::string mTerminal;
	std::string mStyle;
	std::vector<WindowData> mWindowData;
	unsigned int mCurrentWindowNumber;
	const unsigned int mMaxCommandSize;
	static unsigned int mTempFileNumber;

	void setLineStyles();
	std::string readFileName() const;
	std::string createTempFileName();
	void createTempFile(const std::string&, const std::vector<double>&);
	void createTempFile(const std::string&, const std::vector<double>&, const std::vector<double>&);
	void createTempFile(const std::string&, const std::vector<double>&, const std::vector<double>&, const std::vector<double>&);
	void plotTempFile2D(const std::string&, const std::string&);
	void plotTempFile3D(const std::string&, const std::string&);

	void dot(const std::string& debugString = ".") const;
	
	public:
	Gnuplot();
	~Gnuplot();

	void execute(const std::string&) const;

	void addWindow(const unsigned int& nWindows = 1);
	void changeWindow(const unsigned int&);
	
	void setTerminal(const GnuplotTerminal&);
	void setStyle(const GnuplotStyle&);
	void setYlabel(const std::string&);
	void setXlabel(const std::string&);

	void plot(const std::string &, const std::string& title = "y");
	void plot(const std::vector<double>&, const std::string& title = "y");
	void plot(const std::vector<double>&, const std::vector<double>&, const std::string& title = "data");
	void plot(const std::vector<double>&, const std::vector<double>&, const std::vector<double>&, const std::string& title = "z");

	void emptyPlot();

	//Helper functions
	std::string itoa(const int&) const;
	std::string ftoa(const double&) const;
	bool fileExists(const std::string& fileName) const;

	
};

#endif


