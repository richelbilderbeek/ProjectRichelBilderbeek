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
//----------------------------------------------------------------------------------
#include "Gnuplot.h"
//----------------------------------------------------------------------------------
//#define EXTENSIVE_LOG
//----------------------------------------------------------------------------------
unsigned int Gnuplot::mTempFileNumber = 0;
//----------------------------------------------------------------------------------
Gnuplot::Gnuplot() :
	mGnuPipe(NULL),
	mTerminal("X11"),
	mStyle("lines"),
	mCurrentWindowNumber(0),
	mMaxCommandSize(4096)
{
	const std::string fileName = readFileName();
	if (fileExists(fileName)==false)
	{
		std::cout << "\nGnuplot location was not found"
			<< "\nTherefore, change the line in 'GnuplotLocation.txt"
			<< "\nto your Gnuplot location.\n";
		exit(1);
	}
    mGnuPipe = popen((fileName+" -persist").c_str(),"w");
    if (mGnuPipe==NULL) assert(!"Couldn't open connection to gnuplot");
	setLineStyles();
	addWindow();
	changeWindow(0);
}
//----------------------------------------------------------------------------------
///This reads the location of Gnuplot from the config file called GnuplotLocation.txt
///If it cannot find this file, it is created with a default value
std::string Gnuplot::readFileName() const
{
	const std::string fileName = "GnuplotLocation.txt";
	std::string returnFileName;
	if (fileExists(fileName)==true)
	{
		std::ifstream file(fileName.c_str());
		assert(file.is_open()==true);
		file >> returnFileName;
		file.close();
	}
	else
	{
		std::ofstream file(fileName.c_str());
		assert(file.is_open()==true);
		returnFileName ="/sw/bin/gnuplot";
		file << returnFileName << '\n';
		file.close();
	}
	return returnFileName;
}
//----------------------------------------------------------------------------------
Gnuplot::~Gnuplot()
{
	const unsigned int nWindows = mWindowData.size();
	for(unsigned i=0; i<nWindows; ++i)
	{
		mCurrentWindowNumber = i;
		emptyPlot();
	}
	
    if (pclose(mGnuPipe) == -1) assert(!"Problem closing communication to Gnuplot");
}
//----------------------------------------------------------------------------------
void Gnuplot::emptyPlot()
{     
	const unsigned int nPlots = mWindowData[mCurrentWindowNumber].tempFileName.size();
	for (unsigned int i=0; i<nPlots; ++i)
	{
		dot("Removing file: " + mWindowData[mCurrentWindowNumber].tempFileName[i]);
		remove(mWindowData[mCurrentWindowNumber].tempFileName[i].c_str());
	}
}
//----------------------------------------------------------------------------------
///Fiund out more terminal types using 'set terminal' in Gnuplot
void Gnuplot::setTerminal(const GnuplotTerminal& terminal)
{
	switch(terminal)
	{
		case terminalAqua : mTerminal = "aqua"; break;
		case terminalX11  : mTerminal = "x11" ; break;
		default: assert(!"Unknown GnuplotTerminal");
	}
}
//----------------------------------------------------------------------------------
void Gnuplot::setStyle(const GnuplotStyle& style)
{
	switch(style)
	{
		case styleLines        : mStyle = "lines"; break;
		case stylePoints       : mStyle = "points"; break;
		case styleLinespoints  : mStyle = "linespoints"; break;
		case styleImpulses     : mStyle = "impulses"; break;
		case styleDots         : mStyle = "dots"; break;
		case styleSteps        : mStyle = "steps"; break;
		case styleErrorbars    : mStyle = "errorbars"; break;
		case styleBoxes        : mStyle = "boxes"; break;
		case styleBoxerrorbars : mStyle = "boxerrorbars"; break;
		default: assert(!"Unknown GnuplotStyle"); 
	}
}
//----------------------------------------------------------------------------------
void Gnuplot::execute(const std::string& cmdstr) const
{
	dot("Command sent to Gnuplot: " + static_cast<std::string>(cmdstr));
    fputs((cmdstr+"\n").c_str(),mGnuPipe);
    fflush(mGnuPipe);
	usleep(150000);
}
//----------------------------------------------------------------------------------
void Gnuplot::setYlabel(const std::string& label)
{
    const std::string command = "set ylabel \""+label+"\"";
    execute(command.c_str());
}
//----------------------------------------------------------------------------------
void Gnuplot::setXlabel(const std::string& label)
{
    const std::string command = "set xlabel \""+label+"\"";
    execute(command.c_str());
}
//----------------------------------------------------------------------------------
///Change to plotting windows to 'windowNumber'. If this window number is beyond
///the amount of windows created, a new window will be created and that window
///will be set as the plotting window
void Gnuplot::changeWindow(const unsigned int& windowNumber)
{
	if (windowNumber==mCurrentWindowNumber) return;
	if (windowNumber>=mWindowData.size()) 
	{
		addWindow();
		mCurrentWindowNumber = mWindowData.size()-1;
	}
	else
	{
		mCurrentWindowNumber=windowNumber;
	}
	const std::string myCommand = "set terminal "+mTerminal+" "+itoa(mCurrentWindowNumber+1);
	execute(myCommand.c_str());
}
//----------------------------------------------------------------------------------
///Creates an extra 'nWindows' display windows. 
void Gnuplot::addWindow(const unsigned int& nWindows)
{
	for (unsigned int i=0; i<nWindows; ++i)
	{
		WindowData temp;
		mWindowData.push_back(temp);
	}
}
//----------------------------------------------------------------------------------
void Gnuplot::plot(const std::string &equation, const std::string &title)
{
    std::string myCommand;
    if (mWindowData[mCurrentWindowNumber].tempFileName.size() > 0)
		myCommand = "replot " + equation + " title \"" + title + "\" with " + mStyle;
    else
		myCommand = "plot " + equation + " title \"" + title + "\" with " + mStyle;

	execute(myCommand.c_str());
}
//----------------------------------------------------------------------------------
void Gnuplot::plot(const std::vector<double>& x, const std::string &title)
{
	const std::string tempFileName = createTempFileName();
	createTempFile(tempFileName,x);
	plotTempFile2D(tempFileName,title);
}
//----------------------------------------------------------------------------------
void Gnuplot::plot(const std::vector<double>& x, const std::vector<double>& y, const std::string &title)
{
	const std::string tempFileName = createTempFileName();
	createTempFile(tempFileName,x,y);
	plotTempFile2D(tempFileName,title);
}
//----------------------------------------------------------------------------------
void Gnuplot::plot(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& z, const std::string &title)
{
	const std::string tempFileName = createTempFileName();
   	createTempFile(tempFileName,x,y,z);
	plotTempFile3D(tempFileName,title);
}
//----------------------------------------------------------------------------------
void Gnuplot::plotTempFile2D(const std::string& tempFileName, const std::string& title)
{
    std::string myCommand;
	const unsigned int nSerie = mWindowData[mCurrentWindowNumber].tempFileName.size();
	//Linestyles are nice, but don't work on my terminal...
	///if (nSerie>12) std::cout << "MAKE MORE LINESTYLES!!!" << std::endl;
    //if ( nSerie== 0)
	//	myCommand = "plot \"" + tempFileName + "\" ls "+itoa(nSerie)+" title \"" + title + "\" with " + mStyle;
    //else
	//	myCommand = "replot \"" + tempFileName + "\" ls "+itoa(nSerie)+" title \"" + title + "\" with " + mStyle;
	
    if ( nSerie== 0)
		myCommand = "plot \"" + tempFileName + "\" title \"" + title + "\" with " + mStyle;
    else
		myCommand = "replot \"" + tempFileName + "\" title \"" + title + "\" with " + mStyle;

    execute(myCommand.c_str());
	usleep(500000);
    mWindowData[mCurrentWindowNumber].tempFileName.push_back(tempFileName);

}
//----------------------------------------------------------------------------------
void Gnuplot::plotTempFile3D(const std::string& tempFileName, const std::string& title)
{
	//Does not work on my computer. Should be something like this...
	execute("set pm3d");
    std::string myCommand;
   if (mWindowData[mCurrentWindowNumber].tempFileName.size() == 0)
		myCommand = "splot \"" + tempFileName + "\" title \"" + title + "\" with pm3d palette";
    else
		myCommand = "replot \"" + tempFileName + "\" title \"" + title + "\" with pm3d palette";

    execute(myCommand.c_str());
	usleep(500000);
    mWindowData[mCurrentWindowNumber].tempFileName.push_back(tempFileName);
}
//----------------------------------------------------------------------------------
std::string Gnuplot::createTempFileName()
{
	++mTempFileNumber;
	const std::string tempFileName = "GnuplotTemp"+itoa(mTempFileNumber);
	dot("Created temp file '" + tempFileName);
	return(tempFileName);
}
//----------------------------------------------------------------------------------
void Gnuplot::createTempFile(const std::string& tempFileName, const std::vector<double>& x)
{
	std::ofstream file(tempFileName.c_str());
	assert(file.is_open()==true);
	const unsigned int size = x.size();
    for (unsigned int i = 0; i < size; i++) file << x[i] << std::endl;
    file.close();
	
}
//----------------------------------------------------------------------------------
void Gnuplot::createTempFile(const std::string& tempFileName, const std::vector<double>& x, const std::vector<double>& y)
{
	assert(x.size()==y.size());

	std::ofstream file(tempFileName.c_str());
	assert(file.is_open()==true);
	const unsigned int size = x.size();
    for (unsigned int i = 0; i < size; i++) file << x[i] << " " << y[i] << std::endl;
    file.close();
}
//----------------------------------------------------------------------------------
void Gnuplot::createTempFile(const std::string& tempFileName, const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& z)
{
	assert(x.size()==y.size());
	assert(y.size()==z.size());

	std::ofstream file(tempFileName.c_str());
	assert(file.is_open()==true);
	const unsigned int size = x.size();
    for (unsigned int i = 0; i < size; i++) file << x[i] << " " << y[i] << " " << z[i] << std::endl;
    file.close();
}
//----------------------------------------------------------------------------------
void Gnuplot::setLineStyles()
{
	//Does not work on all terminals. Like mine... :-(
	//execute("set style line  1 lt pal frac 0.0 lw 2");
	//execute("set style line  2 lt pal frac 0.0 lw 4");
	//execute("set style line  3 lt pal frac 0.2 lw 2");
	//execute("set style line  4 lt pal frac 0.2 lw 4");
	//execute("set style line  5 lt pal frac 0.4 lw 2");
	//execute("set style line  6 lt pal frac 0.4 lw 4");
	//execute("set style line  7 lt pal frac 0.6 lw 2");
	//execute("set style line  8 lt pal frac 0.6 lw 4");
	//execute("set style line  9 lt pal frac 0.8 lw 2");
	//execute("set style line 10 lt pal frac 0.8 lw 4");
	//execute("set style line 11 lt pal frac 1.0 lw 2");
	//execute("set style line 12 lt pal frac 1.0 lw 4");
}
//----------------------------------------------------------------------------------
///Logging when in developmental phase
void Gnuplot::dot(const std::string& debugString) const
{
	#ifdef EXTENSIVE_LOG
	std::cout << "DOT: " << debugString << std::endl;
	#endif
}
//----------------------------------------------------------------------------------
///Converts an integer to a string
std::string Gnuplot::itoa(const int& number) const
{
	std::ostringstream o;
	if (!(o << number)) { assert(!"ERROR in itoa"); exit(1); }
	return o.str();
}
//----------------------------------------------------------------------------------
///Converts a double to a string
std::string Gnuplot::ftoa(const double& number) const
{
	std::ostringstream o;
	if (!(o << number)) { assert(!"ERROR in ftoa"); exit(1); }
	return o.str();
}
//----------------------------------------------------------------------------------
///Checks if a file exists
bool Gnuplot::fileExists(const std::string& fileName) const
{
	std::fstream fin;
	fin.open(fileName.c_str(),std::ios::in);
	if( fin.is_open() )
	{
		fin.close();
		return true;
	}
	fin.close();
	return false;
}
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
