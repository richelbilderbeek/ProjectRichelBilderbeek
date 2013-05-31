/*
 *  MeasurementsTable.h
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Tue Jun 07 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */

///Structure for storing measurements. 
///
///Is plotted by functions in HelperFunctions.h

#ifndef __MEASUREMENTS_TABLE_H
#define __MEASUREMENTS_TABLE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Enumerations.h"
#include "HelperFunctions.h"

class MeasurementsTable
{
	public:
	std::vector<double> mPopSize;
	std::vector<double> mNoffspring;
	std::vector<double> mResources;
	std::vector<double> mMeanBodySize;
	std::vector<double> mStdDevBodySize;
	std::vector<double> mMeanReserves;	
	std::vector<double> mStdDevReserves;
	std::vector<double> mMeanChanceToDie;
	std::vector<double> mStdDevChanceToDie;
	std::vector<double> mMeanFoodIntake;
	std::vector<double> mStdDevFoodIntake;
	//Plus
	std::vector<double> mPopSizeJuvenile;
	std::vector<double> mPopSizeAdult;
	std::vector<double> mMeanBodySizeJuvenile;
	std::vector<double> mMeanBodySizeAdult;
	std::vector<double> mMeanReservesJuvenile;
	std::vector<double> mMeanReservesAdult;
	std::vector<double> mMeanChanceToDieJuvenile;
	std::vector<double> mMeanChanceToDieAdult;
	std::vector<double> mMeanFoodIntakeJuvenile;
	std::vector<double> mMeanFoodIntakeAdult;
	//Plus plus
	std::vector<double> mMeanAllocation;
	std::vector<double> mMeanFractionBiomassPerOffspringInitial;
	std::vector<double> mMeanFractionBiomassPerOffspring;
	//public:
	void showYearLegend() const;
	void showYear(const unsigned int&) const;
	void showYearHorizontal(const unsigned int&) const;
	void saveToSingleFile(const std::string&) const;
	void saveToMultipleFiles(const std::string&) const;
	//void vectorToFile(const std::vector<double>&, const std::string&) const;
	//void vectorToFile(const std::string&, const std::vector<double>&, const std::string&, const std::vector<double>&,const std::string&) const;

	void addVectorToFile(const std::string&, const std::vector<double>&, std::ofstream&) const;

};

void plotMeasurementsTable(std::vector<MeasurementsTable>&);
void drawConclusions(const MeasurementsTable&,std::vector<EnumConclusion>&) ;
void interpretMeasurementsTables(const std::vector<MeasurementsTable>& table);

#endif
