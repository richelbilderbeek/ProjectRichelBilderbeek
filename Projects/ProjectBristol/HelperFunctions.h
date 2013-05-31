/*
 *  HelperFunctions.h
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Tue May 24 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */
//----------------------------------------------------------------------------------
#ifndef __HELPER_FUNCTIONS_H
#define __HELPER_FUNCTIONS_H

//#define NDOT

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "gnuplot.h"
#include "MeasurementsTable.h"
#include "Enumerations.h"

//----------------------------------------------------------------------------------
///Structs for upper and lower case functions
struct ToUpper
{
	ToUpper(std::locale const& l) : loc(l) {;}
	char operator() (char c) const  { return std::toupper(c,loc); }
	private:
	std::locale const& loc;
};
//----------------------------------------------------------------------------------
struct ToLower
{
	ToLower(std::locale const& l) : loc(l) {;}
	char operator() (char c) const  { return std::tolower(c,loc); }
	private:
	std::locale const& loc;
};
//----------------------------------------------------------------------------------
template <typename T> T min(const T&, const T&);
template <typename T> T min(const T&, const T&, const T&);
template <typename T> T min(const T&, const T&, const T&, const T&);
template <typename T> T min(const T&, const T&, const T&, const T&, const T&);
template <typename T> T min(const T&, const T&, const T&, const T&, const T&, const T&);
template <typename T> T min(const T&, const T&, const T&, const T&, const T&, const T&, const T&);
template <typename T> T min(const T&, const T&, const T&, const T&, const T&, const T&, const T&, const T&);
template <typename T> T min(const T&, const T&, const T&, const T&, const T&, const T&, const T&, const T&, const T&);
template <typename T> T min(const T&, const T&, const T&, const T&, const T&, const T&, const T&, const T&, const T&, const T&);


//Statistics
template <class T> bool SafeMeanAndStdDev(const T *, const int&, double &, double &);
bool SafeMeanAndStdDev(const std::vector<double>&, double &, double &);
bool SafeMean(const std::vector<double>&, double &);
void SafeMeanSplit(const double&, std::vector<double>&, double& , double&);
void SafeMeanSplit(const std::vector<bool>&, std::vector<double>&, double& , double&);
void countSplit(const double&, std::vector<double>&, int&, int&);

//Conversions
std::string itoa(const int&);
std::string ftoa(const double&);
bool isDouble(const std::string&, double&);
bool isInt(const std::string&, int&);
std::string stringToLower(std::string myString);
std::string stringToUpper(std::string myString);

//File I/O
void copyFile(const std::string&, const std::string&);
bool fileExists(const std::string&);
std::string stripExtension(const std::string&);
std::string getExtension(const std::string&);
std::vector<std::string> fileToVector(const std::string&);

void vectorToFile(const std::vector<double>&, 
                  const std::string&, const int& startIndex = 0);
void vectorToFile(const std::string&, const std::vector<double>&, 
                  const std::string&, const std::vector<double>&,
                  const std::string&, const int& startIndex = 0);
void vectorToFile(const std::string&, const std::vector<double>&, 
                  const std::string&, const std::vector<double>&,
                  const std::string&, const std::vector<double>&,
                  const std::string&, const int& startIndex = 0);
void vectorToFile(const std::string&, const std::vector<double>&, 
                  const std::string&, const std::vector<double>&,
                  const std::string&, const std::vector<double>&,
                  const std::string&, const std::vector<double>&,
                  const std::string&, const int& startIndex = 0);
void vectorToFile(const std::string&, const std::vector<double>&, 
                  const std::string&, const std::vector<double>&,
                  const std::string&, const std::vector<double>&,
                  const std::string&, const std::vector<double>&,
                  const std::string&, const std::vector<double>&,
                  const std::string&, const int& startIndex = 0);
void vectorToFile(const std::string&, const std::vector<double>&, 
                  const std::string&, const std::vector<double>&,
                  const std::string&, const std::vector<double>&,
                  const std::string&, const std::vector<double>&,
                  const std::string&, const std::vector<double>&,
                  const std::string&, const std::vector<double>&,
                  const std::string&, const int& startIndex = 0);
void vectorToFile(const std::string&, const std::vector<double>&, 
                  const std::string&, const std::vector<double>&,
                  const std::string&, const std::vector<double>&,
                  const std::string&, const std::vector<double>&,
                  const std::string&, const std::vector<double>&,
                  const std::string&, const std::vector<double>&,
                  const std::string&, const std::vector<double>&,
                  const std::string&, const int& startIndex = 0);

//Automatic code generation
void autoEnum(const std::string&, const std::string&, const std::string&, std::vector<std::string>&);

//Misc
std::string indexToPlasticity(const int&);
void coutVector(const std::vector<std::string>&);
template <typename T> void coutVector(const std::vector<T>& myVector);

#endif //#ifndef __HELPER_FUNCTIONS_H

