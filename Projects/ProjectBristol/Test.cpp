/*
 *  Test.cpp
 *  Sim4
 *
 *  Created by Robert Payne on Thu Jun 09 2005.
 *  Copyright (c) 2005 __MyCompanyName__. All rights reserved.
 *
 */

#include "Test.h"
//----------------------------------------------------------------------------------
void testGnuPlot3D()
{
	const int nPoints = 10;
	std::vector<double> x,y,z;
	
	for (int i=0; i<nPoints; ++i)
	{
		const double xD = static_cast<double>(i); 
		for(int j=0; j<nPoints; ++j)
		{
			const double yD = static_cast<double>(j); 
			const double zD = cos(xD)+sin(yD);
			x.push_back(xD);
			y.push_back(yD);
			z.push_back(zD);
			std::cout << xD << '\t' << yD << '\t' << zD << std::endl;
		}
	}

	Gnuplot myPlot;
	//myPlot.cmd("set terminal x11");
	//myPlot.cmd("set terminal aqua");

	//myPlot.cmd("set pm3d");
	//myPlot.cmd("set palette color mode RGB");
	//myPlot.set_style("lines");
	
	myPlot.plot(x,y,z,"Test");
	sleep(5);
	std::cout << "Testing done. Press key to quit\n";
	std::string nothing; std::cin >> nothing;
}
//----------------------------------------------------------------------------------
void testGnuPlotWindows()
{
	Gnuplot myPlot;
	for (unsigned int i=0; i<10; ++i)
	{
		setSeed(i);
		myPlot.changeWindow(i);
		std::vector<double> data1(1000);
		std::vector<double> data2(1000);
		const double iD = static_cast<double>(i);
		for (unsigned int j=0; j<1000; ++j)
		{
			const double jD = static_cast<double>(j);
			data1[j]= cos(jD/(2.0+iD));
			data2[j]= sin(jD/(3.0+iD));
			//data1[j]= uniform();// + cos(static_cast<double>(j)/10.0);
			//data2[j]= uniform();// * cos(static_cast<double>(j)/20.0);
		}
		myPlot.plot(data1);
		myPlot.plot(data2);
	}
	
	/*Gnuplot myPlot1, myPlot2;
	const unsigned int datasetSize = 100;
	std::vector<double>dataset(datasetSize);
	for(unsigned int i=0; i<datasetSize; ++i)
	{
		const double iD = static_cast<double>(i);
		dataset[i] = cos(iD/10.0);
	}
	myPlot1.execute("set terminal aqua 1");
	myPlot1.plot(dataset);
	sleep(1);

	for(unsigned int i=0; i<datasetSize; ++i)
	{
		const double iD = static_cast<double>(i);
		dataset[i]=0.01*iD*sin(iD/100.0);
	}

	myPlot2.execute("set terminal aqua 2");
	myPlot2.plot(dataset);
	sleep(1);*/
	
	
}
//----------------------------------------------------------------------------------
void demoGnuplot()
{
	Gnuplot myPlot;

	std::vector<double> data1(1000);
	std::vector<double> data2(1000);
	for (unsigned int j=0; j<1000; ++j)
	{
		const double jD = static_cast<double>(j);
		data1[j]= sin(jD/100.0);
		data2[j]= sin(jD/100.0);
	}

	for (unsigned int i=0; i<10; ++i)
	{
		setSeed(i);
		myPlot.changeWindow(i);
		const double iD = static_cast<double>(i);
		for (unsigned int j=0; j<1000; ++j)
		{
			const double jD = static_cast<double>(j);
			data1[j]*= sin(jD/(20.0-iD));
			data2[j]*= sin(jD/(21.0-iD));
		}
		myPlot.plot(data1);
		myPlot.plot(data2);
	}
}
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

