/*
 *  HelperFunctions.cpp
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Tue May 24 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */
//----------------------------------------------------------------------------------
#include "HelperFunctions.h"
//----------------------------------------------------------------------------------
//void dot(const std::string& debugMessage)
//{
//	#ifndef NDOT
//	std::cout << debugMessage << std::endl;
//	#endif
//}
//----------------------------------------------------------------------------------
//void cout(const std::string& outputMessage)
//{
//	std::cout << outputMessage << std::endl;
//}
//----------------------------------------------------------------------------------
template <typename T> T min(const T& a, const T& b)
{
  return (a<b?a:b);
}
//----------------------------------------------------------------------------------
template <typename T> T min(const T& a, const T& b, const T& c)
{
  const T temp = min(a,b);
  return (temp<c? temp:c);
}
//----------------------------------------------------------------------------------
template <typename T> T min(const T& a, const T& b, const T& c, const T& d)
{
  const T temp = min(a,b,c);
  return (temp<d? temp:d);
}
//----------------------------------------------------------------------------------
template <typename T> T min(const T& a, const T& b, const T& c, const T& d, const T& e)
{
  const T temp = min(a,b,c,d);
  return (temp<e? temp:e);
}
//----------------------------------------------------------------------------------
template <typename T> T min(const T& a, const T& b, const T& c, const T& d, const T& e, const T& f)
{
  const T temp = min(a,b,c,d,e);
  return (temp<f? temp:f);
}
//----------------------------------------------------------------------------------
template <typename T> T min(const T& a, const T& b, const T& c, const T& d, const T& e, const T& f, const T& g)
{
  const T temp = min(a,b,c,d,e,f);
  return (temp<g? temp:g);
}
//----------------------------------------------------------------------------------
template <typename T> T min(const T& a, const T& b, const T& c, const T& d, const T& e, const T& f, const T& g, const T& h)
{
  const T temp = min(a,b,c,d,e,f,g);
  return (temp<h? temp:h);
}
//----------------------------------------------------------------------------------
template <typename T> T min(const T& a, const T& b, const T& c, const T& d, const T& e, const T& f, const T& g, const T& h, const T& i)
{
  const T temp = min(a,b,c,d,e,f,g,h);
  return (temp<i? temp:i);
}
//----------------------------------------------------------------------------------
template <typename T> T min(const T& a, const T& b, const T& c, const T& d, const T& e, const T& f, const T& g, const T& h, const T& i, const T& j)
{
  const T temp = min(a,b,c,d,e,f,g,h,i);
  return (temp<j? temp:j);
}
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
/// Determines the mean and standard deviation of an array
/// Returns whether successfull
template <class T>
bool SafeMeanAndStdDev(const T * pArray, const int& arraysize, double &rMean, double &rStdDev)
{
	if (arraysize>1)
	{
		double Sum=0.0, SumSquared=0.0;
		for (int counter=0;counter<arraysize;++counter)
		{
			Sum+=pArray[counter];
			SumSquared+=(pArray[counter]*pArray[counter]);
		}//Next counter
		rMean=(Sum/arraysize);
		//Safe part:
		double numerator=((arraysize*SumSquared)-(Sum*Sum));
		if (numerator<0) {numerator=0;}
		rStdDev=sqrt(numerator/(arraysize*(arraysize-1)));
		return true;
	}
	else
	{
		rMean = 0.0; 
		rStdDev = 0.0;
		cout("Arraysize must be larger then 1!");
		return false;
	}
}
//----------------------------------------------------------------------------------
/// Determines the mean and standard deviation of a vector
/// Returns whether successfull
bool SafeMeanAndStdDev(const std::vector<double>& pArray, double &rMean, double &rStdDev)
{
	const unsigned int arraysize = pArray.size();
	const double arraysizeD = static_cast<double>(arraysize);
	if (arraysize<2)
	{
		rMean = 0.0;
		rStdDev = 0.0;
		std::cout << "Arraysize must be larger then 1!" << std::endl;
		return false;
	}
	
	double Sum=0.0, SumSquared=0.0;
	for (unsigned int counter=0;counter<arraysize;++counter)
	{
		Sum+=pArray[counter];
		SumSquared+=(pArray[counter]*pArray[counter]);
	}
	rMean=(Sum/arraysize);
	//Safe part:
	double numerator=((arraysizeD*SumSquared)-(Sum*Sum));
	if (numerator<0.0) {numerator=0.0;}
	rStdDev=sqrt(numerator/(arraysizeD*(arraysizeD-1.0)));
	return true;
}
//----------------------------------------------------------------------------------
/// Determines the mean and standard deviation of a vector
/// Returns whether successfull
bool SafeMean(const std::vector<double>& pArray, double & rMean)
{
	const unsigned int arraysize = pArray.size();
	if (arraysize<2)
	{
		std::cout << "Arraysize must be larger then 1!" << std::endl;
		rMean=0.0;
		return false;
	}
	double Sum=0.0;
	for (unsigned int counter=0;counter<arraysize;++counter)
	{
		Sum+=pArray[counter];
	}
	rMean=(Sum/arraysize);
	return true;

}
//----------------------------------------------------------------------------------
void SafeMeanSplit(const double& splitValue, std::vector<double>& table, double & rMeanTraitJuvenile, double& rMeanTraitAdult)
{
	const unsigned int arraysize = table.size();
	if (arraysize<=1)
	{
		rMeanTraitJuvenile = 0.0;
		rMeanTraitAdult    = 0.0;
		std::cout << "Arraysize must be larger then 1!" << std::endl;
		return;
	}

	double sumJuvenile=0.0, sumAdult=0.0;
	int nJuveniles=0, nAdults=0;
	for (unsigned int i=0; i<arraysize; ++i)
	{
		const double value = table[i];
		if (value<splitValue)
		{
			++nJuveniles;
			sumJuvenile+=value;
		}
		else
		{
			++nAdults;
			sumAdult+=value;
		}
	}
	if (nJuveniles==0) rMeanTraitJuvenile=0.0;
	else rMeanTraitJuvenile = sumJuvenile/static_cast<double>(nJuveniles);
	if (nAdults==0) rMeanTraitAdult=splitValue;
	else rMeanTraitAdult = sumAdult/static_cast<double>(nAdults);
	assert(rMeanTraitJuvenile<=splitValue);
	assert(rMeanTraitAdult>=splitValue);
}
//----------------------------------------------------------------------------------
///Calculates the mean traitValues for juveniles and adults
void SafeMeanSplit(const std::vector<bool>& isAdultTable, std::vector<double>& table, double & rMeanTraitJuvenile, double& rMeanTraitAdult)
{
	const unsigned int arraysize = table.size();
	if (arraysize<=1)
	{
		rMeanTraitJuvenile = 0.0;
		rMeanTraitAdult    = 0.0;
		//std::cout << "Arraysize must be larger then 1!" << std::endl;
		return;
	}

	double sumJuvenile=0.0, sumAdult=0.0;
	int nJuveniles=0, nAdults=0;
	for (unsigned int i=0; i<arraysize; ++i)
	{
		const double value = table[i];
		if (isAdultTable[i]==false)
		{
			++nJuveniles;
			sumJuvenile+=value;
		}
		else
		{
			++nAdults;
			sumAdult+=value;
		}
	}
	if (nJuveniles==0) rMeanTraitJuvenile=0.0;
	else rMeanTraitJuvenile = sumJuvenile/static_cast<double>(nJuveniles);
	if (nAdults==0) rMeanTraitAdult=0.0;
	else rMeanTraitAdult = sumAdult/static_cast<double>(nAdults);
}
//----------------------------------------------------------------------------------
///Counts the occurrence of juveniles with traitValues having values lower then splitValue
///and adults with traitValues having 
void countSplit(const double& splitValue, std::vector<double>& table, int& rCountJuvenile, int& rCountAdult)
{
	const unsigned int size = table.size();
	rCountJuvenile=0;
	rCountAdult = 0;
	for (unsigned int i=0; i<size; ++i)
	{
		if (table[i]<splitValue) ++rCountJuvenile;
		else ++rCountAdult;
	}
}
//----------------------------------------------------------------------------------
///Converts an integer to a string.
std::string itoa(const int& x)
{
	std::ostringstream o;
	if (!(o << x)) return "ERROR";
	return o.str();
}
//----------------------------------------------------------------------------------
///Converts a double to a string.
std::string ftoa(const double& x)
 {
	std::ostringstream o;
	if (!(o << x)) return "ERROR";
	return o.str();
 }
//----------------------------------------------------------------------------------
///Checks whether a std::string can be converted to an integer.
///Returns true if possible, also returning this integer by referencing.
///Returns false otherwise, setting the referenced integer to zero.
bool isInt(const std::string& s, int& rInt)
 {
	std::istringstream i(s);
	if (!(i >> rInt))
		{ rInt = 0; return false; }
	return true;
}
//----------------------------------------------------------------------------------
///Checks whether a std::string can be converted to a double.
///Returns true if possible, also returning this double by referencing.
///Returns false otherwise, setting the referenced double to zero.
bool isDouble(const std::string& s, double& rDouble)
 {
	std::istringstream i(s);
	if (!(i >> rDouble)) 
		{ rDouble = 0.0; return false; }
	return true;
}
//----------------------------------------------------------------------------------
std::string stringToUpper(std::string myString)
{
	static ToUpper up(std::locale::classic());
	std::transform(myString.begin(), myString.end(), myString.begin(), up);
	return myString;
}
//----------------------------------------------------------------------------------
std::string stringToLower(std::string myString)
{
	static ToLower down(std::locale::classic());
	std::transform(myString.begin(), myString.end(), myString.begin(), down);
	return myString;
}
//----------------------------------------------------------------------------------
void copyFile(const std::string& fileNameFrom, const std::string& fileNameTo)
{
	assert(fileExists(fileNameFrom));
	std::ifstream in (fileNameFrom.c_str());
	std::ofstream out(fileNameTo.c_str());
	out << in.rdbuf(); 
	out.close();
	in.close();
}
//----------------------------------------------------------------------------------
///Checks if a file exists. 
bool fileExists(const std::string& fileName)
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
///Removes the '.txt' or other extensions of a fileName.
///Actually, it returns the fileName's part before the first dot encountered.
///When no dot is encountered, it returns the entire fileName.
std::string stripExtension(const std::string& fileName)
{
	const unsigned int length = fileName.length();
	for (unsigned int i=0; i<length; ++i)
	{
		if (fileName[i]=='.') 
		{
			return fileName.substr(0,i);
		}
	}
	return fileName;
}
//----------------------------------------------------------------------------------
///Gets the '.txt' or other extensions of a fileName.
///Actually, it returns the fileName's part after the first dot encountered.
///When no dot is encountered, it returns the entire fileName.
std::string getExtension(const std::string& fileName)
{
	const unsigned int length = fileName.length();
	for (unsigned int i=0; i<length; ++i)
	{
		if (fileName[i]=='.') 
		{
			return fileName.substr(i+1,length);
		}
	}
	return fileName;
}
//----------------------------------------------------------------------------------
///Example program to use autoEnum:
///  std::vector<std::string> enumValues;
///  std::string fileName = "/Volumes/RichelDrive/EnumSigma.cpp";
///  std::string enumName = "EnumSigma";
///  std::string variableName = "enumSigma";
///  enumValues.push_back("enumSigmaZero");
///  enumValues.push_back("enumSigmaUniform");
///  autoEnum(fileName, enumName, variableName, enumValues);
///
void autoEnum(const std::string& fileName, const std::string& enumName, 
	const std::string& variableName, std::vector<std::string>& enumValues)
{
	//Open file
	std::ofstream file(fileName.c_str());
	assert(file.is_open()==true);
	//Enumeration
	file << "//----------------------------------------------------------------------------------" << '\n';
	file << "enum " << enumName << '\n';
	file << "{" << '\n';
	for (unsigned int i=0; i<enumValues.size(); ++i)
	{
		file << '\t' << enumValues[i] << ( (i<enumValues.size()-1) ? ",\n" : "\n" );
	}
	file << "};" << '\n';
	//Headers
	file << "//----------------------------------------------------------------------------------" << '\n';
	file << "std::string " << variableName << "toString(const " << enumName << "&);" << '\n';
	file << enumName << " stringTo" << enumName << "(const std::string&);" << '\n';
	//Implementation
	file << "//----------------------------------------------------------------------------------" << '\n';
	file << "std::string " << variableName 
		 << "toString(const " << enumName << "& " 
		 << variableName << ")" << '\n';
	file << "{" << '\n';
	file << '\t' << "switch(" << variableName << ")" << '\n';
	file << '\t' << "{" << '\n';
	for (unsigned int i=0; i<enumValues.size(); ++i)
	{
		file << '\t' << '\t' << "case " << enumValues[i] << ": return \"" << enumValues[i] << "\";" << '\n' ;
	}
	file << '\t' << "}" << '\n';
	file << '\t' << "return \"ERROR in 'std::string " << variableName 
		 << "ToString(const " << enumName << "& " 
		 << variableName << ")'\";" << '\n';
	file << "}" << '\n';
	file << "//----------------------------------------------------------------------------------" << '\n';
	file << enumName << " stringTo" << enumName << "(const std::string& myString)" << '\n';
	file << "{" << '\n';
	for (unsigned int i=0; i<enumValues.size(); ++i)
	file << '\t' << "if (myString==\"" << enumValues[i] << "\") return " << enumValues[i] << ";" << '\n';
	file << '\t' << "std::cout << \"ERROR in '"<< enumName 
		<< " StringTo" << enumName << "(const std::string& myString)'\" << std::endl;" << '\n';
	file << '\t' << "exit(1);" << '\n';
	file << "}" << '\n';
	file << "//----------------------------------------------------------------------------------" << '\n';
	//Close file
	file.close();
}
//----------------------------------------------------------------------------------
std::vector<std::string> fileToVector(const std::string& fileName)
{
	assert(fileExists(fileName)==true);
	std::vector<std::string> myVector;
	
	std::ifstream in (fileName.c_str());
	std::string myString;
	for (int i=0; !in.eof(); ++i)
	{
		in >> myString;
		myVector.push_back(myString);
		//std::cout << i << " : " << myString << std::endl;
	}
	return myVector;
	
}
//----------------------------------------------------------------------------------
//One vector
void vectorToFile(const std::vector<double>& myVector, 
	const std::string& fileName, const int& startIndex)
{
	std::ofstream file(fileName.c_str());
	assert(file.is_open()==true);
	const unsigned int size = myVector.size();
	for (unsigned int i=startIndex; i<size; ++i)
	{
		file << myVector[i] << '\n';
	}
	file.close();
}
//----------------------------------------------------------------------------------
//Two vectors
void vectorToFile(
    const std::string& name1, const std::vector<double>& myVector1, 
    const std::string& name2, const std::vector<double>& myVector2,
	const std::string& fileName, const int& startIndex)
{
	std::ofstream file(fileName.c_str());
	assert(file.is_open()==true);
	file <<  name1 << " " << name2 << '\n';
	const unsigned int size = ( myVector1.size() < myVector2.size() ? myVector1.size() : myVector2.size());
	for (unsigned int i=startIndex; i<size; ++i)
	{
		file <<  myVector1[i] << " " << myVector2[i] << '\n';
	}
	file.close();
}
//----------------------------------------------------------------------------------
//Three vectors
void vectorToFile(
    const std::string& name1, const std::vector<double>& myVector1, 
    const std::string& name2, const std::vector<double>& myVector2,
    const std::string& name3, const std::vector<double>& myVector3,
	const std::string& fileName, const int& startIndex)
{
	std::ofstream file(fileName.c_str());
	assert(file.is_open()==true);
	file <<  name1 << " " << name2 << " " << name3 << '\n';
	const unsigned int size = min(myVector1.size(),myVector2.size(),myVector3.size());
	for (unsigned int i=startIndex; i<size; ++i)
	{
		file <<  myVector1[i] << " " << myVector2[i] << " " << myVector3[i] <<'\n';
	}
	file.close();
}
//----------------------------------------------------------------------------------
void vectorToFile(
    const std::string& name1, const std::vector<double>& myVector1, 
    const std::string& name2, const std::vector<double>& myVector2,
    const std::string& name3, const std::vector<double>& myVector3,
    const std::string& name4, const std::vector<double>& myVector4,
	const std::string& fileName, const int& startIndex)
{
	std::ofstream file(fileName.c_str());
	assert(file.is_open()==true);
	file <<  name1 << " " << name2 << " " << name3 << " " << name4 << '\n';
	const unsigned int size = min(myVector1.size(),myVector2.size(),myVector3.size(),myVector4.size());
	for (unsigned int i=startIndex; i<size; ++i)
	{
		file <<  myVector1[i] << " " << myVector2[i] << " " << myVector3[i] << " " << myVector4[i] << '\n';
	}
	file.close();
}
//----------------------------------------------------------------------------------
void vectorToFile(
    const std::string& name1, const std::vector<double>& myVector1, 
    const std::string& name2, const std::vector<double>& myVector2,
    const std::string& name3, const std::vector<double>& myVector3,
    const std::string& name4, const std::vector<double>& myVector4,
    const std::string& name5, const std::vector<double>& myVector5,
	const std::string& fileName, const int& startIndex)
{
	std::ofstream file(fileName.c_str());
	assert(file.is_open()==true);
	file <<  name1 << " " << name2 << " " << name3 << " " << name4 << " " << name5 << '\n';
	const unsigned int size = min(myVector1.size(),myVector2.size(),myVector3.size(),myVector4.size(),myVector5.size());
	for (unsigned int i=startIndex; i<size; ++i)
	{
		file <<  myVector1[i] << " " << myVector2[i] << " " << myVector3[i] << " " << myVector4[i] << " " << myVector5[i] << '\n';
	}
	file.close();
}
//----------------------------------------------------------------------------------
void vectorToFile(
    const std::string& name1, const std::vector<double>& myVector1, 
    const std::string& name2, const std::vector<double>& myVector2,
    const std::string& name3, const std::vector<double>& myVector3,
    const std::string& name4, const std::vector<double>& myVector4,
    const std::string& name5, const std::vector<double>& myVector5,
    const std::string& name6, const std::vector<double>& myVector6,
	const std::string& fileName, const int& startIndex)
{
	std::ofstream file(fileName.c_str());
	assert(file.is_open()==true);
	file <<  name1 << " " << name2 << " " << name3 << " " << name4 << " " << name5 << " " << name6 << '\n';
	const unsigned int size = min(myVector1.size(),myVector2.size(),myVector3.size(),myVector4.size(),myVector5.size(),myVector6.size());
	for (unsigned int i=startIndex; i<size; ++i)
	{
		file <<  myVector1[i] << " " << myVector2[i] << " " << myVector3[i] << " " << myVector4[i] << " " << myVector5[i] << " " << myVector6[i] << '\n';
	}
	file.close();
}
//----------------------------------------------------------------------------------
void vectorToFile(
    const std::string& name1, const std::vector<double>& myVector1, 
    const std::string& name2, const std::vector<double>& myVector2,
    const std::string& name3, const std::vector<double>& myVector3,
    const std::string& name4, const std::vector<double>& myVector4,
    const std::string& name5, const std::vector<double>& myVector5,
    const std::string& name6, const std::vector<double>& myVector6,
    const std::string& name7, const std::vector<double>& myVector7,
	const std::string& fileName, const int& startIndex)
{
	std::ofstream file(fileName.c_str());
	assert(file.is_open()==true);
	file <<  name1 << " " << name2 << " " << name3 << " " << name4 << " " << name5 << " " << name6 << " " << name7 << '\n';
	const unsigned int size = min(myVector1.size(),myVector2.size(),myVector3.size(),myVector4.size(),myVector5.size(),myVector6.size(),myVector7.size());
	for (unsigned int i=startIndex; i<size; ++i)
	{
		file <<  myVector1[i] << " " << myVector2[i] << " " << myVector3[i] << " " << myVector4[i] << " " << myVector5[i] << " " << myVector6[i] << " " << myVector7[i] << '\n';
	}
	file.close();
}
//----------------------------------------------------------------------------------
void vectorToFile(
    const std::string& name1, const std::vector<double>& myVector1, 
    const std::string& name2, const std::vector<double>& myVector2,
    const std::string& name3, const std::vector<double>& myVector3,
    const std::string& name4, const std::vector<double>& myVector4,
    const std::string& name5, const std::vector<double>& myVector5,
    const std::string& name6, const std::vector<double>& myVector6,
    const std::string& name7, const std::vector<double>& myVector7,
    const std::string& name8, const std::vector<double>& myVector8,
	const std::string& fileName, const int& startIndex)
{
	std::ofstream file(fileName.c_str());
	assert(file.is_open()==true);
	file <<  name1 << " " << name2 << " " << name3 << " " << name4 << " " << name5 << " " << name6 << " " << name7 << " " << name8 << '\n';
	const unsigned int size = min(myVector1.size(),myVector2.size(),myVector3.size(),myVector4.size(),myVector5.size(),myVector6.size(),myVector7.size(),myVector8.size());
	for (unsigned int i=startIndex; i<size; ++i)
	{
		file <<  myVector1[i] << " " << myVector2[i] << " " << myVector3[i] << " " << myVector4[i] << " " << myVector5[i] << " " << myVector6[i] << " " << myVector7[i] << " " << myVector8[i] << '\n';
	}
	file.close();
}
//----------------------------------------------------------------------------------
void coutVector(const std::vector<std::string>& myVector)
{
  const unsigned int size = myVector.size();
  for (unsigned int i=0; i<size; ++i) std::cout << i << " : " << myVector[i] << std::endl;
}
//----------------------------------------------------------------------------------
template <typename T> void coutVector(const std::vector<T>& myVector)
{
  const unsigned int size = myVector.size();
  for (unsigned int i=0; i<size; ++i) std::cout << i << " : " << myVector[i] << std::endl;
}
//----------------------------------------------------------------------------------
std::string indexToPlasticity(const int& index)
{
	if (index>1) return "(P,"+itoa(index)+")";
	return "(NP,"+itoa(index)+")";
}
//----------------------------------------------------------------------------------

