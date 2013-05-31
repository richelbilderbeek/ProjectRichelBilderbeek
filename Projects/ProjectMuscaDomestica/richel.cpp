#include "richel.h"

//---------------------------------------------------------------------------
/*
  Project Musca Domestica, simulation in which sex-ratio can evolve
  Copyright (C) 2009  Richl Bilderbeek

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------

//Check if this header file not already is included
#ifndef RICHELISCOOL
#define RICHELISCOOL

//Check if math.h needs to be included
#ifndef __MATH_H
#include <math.h>
#endif

//////////////////////////////////////////////////////////////////////////////////////////
//
// Richl's header file
//
// Version 1.023
// Date of last version: 30-11-2003
//
// Version 1.001 comment: 27-05-2003
// Version 1.002 comment: 16-06-2003
// Version 1.003 comment: 17-06-2003
// Version 1.004 comment: 18-06-2003
// Version 1.005 comment: 19-06-2003
// Version 1.006 comment: 20-06-2003
// Version 1.007 comment: 23-06-2003
// Version 1.008 comment: 11-07-2003
// Version 1.009 comment: 24-07-2003
// Version 1.010 comment: 25-07-2003
// Version 1.011 comment: 26-07-2003
// Version 1.012 comment: 28-07-2003
// Version 1.013 comment: 29-07-2003
// Version 1.014 comment: 22-09-2003
// Version 1.015 comment: 27-09-2003
// Version 1.016 comment: 02-10-2003
// Version 1.017 comment: 03-10-2003
// Version 1.018 comment: 06-10-2003
// Version 1.019 comment: 13-10-2003
// Version 1.020 comment: 21-10-2003
// Version 1.021 comment: 22-10-2003
// Version 1.022 comment: 09-11-2003
// Version 1.023 comment: 30-11-2003
//
// Date of creation of functions now in use:
//
// 27-05-2003: asc (char)
// 27-05-2003: Mobius
// 27-05-2003: angle
// 27-05-2003: nullen
// 27-05-2003: DoubleToString
// 27-05-2003: BoolToInt
// 27-05-2003: BoolToText
// 27-05-2003: Rmutate
// 27-05-2003: mutate
// 14-06-2003: (T) SafeMeanAndStdDev
// 14-06-2003: (T) EmptyArray
// 14-06-2003: (T) FillArray
// 16-06-2003: (T) TotalSum
// 16-06-2003: IntArrayToString
// 16-06-2003: DoubleArrayToString
// 16-06-2003: (T) FillArrayRandom
// 16-06-2003: (T) HistogramCategory
// 16-06-2003: (T) HistogramTransfer
// 16-06-2003: (T) Histogram
// 17-06-2003: RandomBool
// 17-06-2003: (T) swap
// 17-06-2003: (T) swapsort
// 17-06-2003: IntPointerArrayToString (integers only)
// 17-06-2003: MakeArrayPointers (integers only)
// 17-06-2003: SortAddresses (integers only)
// 17-06-2003: IntAdressesToString (integers only)
// 17-06-2003: FillAddressessRandom (integers only)
// 18-06-2003: MakeArrayLogisticGrowth
// 18-06-2003: AddNoiseDouble
// 18-06-2003: (T) DiffArray
// 19-06-2003: (T) abs
// 19-06-2003: (T) IsPositive
// 19-06-2003: (T) IsNegative
// 20-06-2003: (T) FindStart (replaces FindStartPoint) (version 2)
// 23-06-2003: (T) SafeMeanAndStdDev++
// 23-06-2003: (T) FindExtremes
// 11-07-2003: ShowArray (double AND integers)
// 24-07-2003: asc (String)
// 25-07-2003: ExtractRGB
// 25-07-2003: Rainbow
// 26-07-2003: (T) CutOff
// 26-07-2003: PlusMinus
// 26-07-2003: (T) Mobius
// 28-07-2003:  Adjecent4
// 29-07-2003: (T) Distance
// 22-09-2003: ShowArray(char)
// 22-09-2003: CharArrayToString
// 22-09-2003: ShowArray(unsigned char)
// 22-09-2003: UnsignedCharArrayToString
// 27-09-2003: EulerIntegrate
// 02-10-2003: Coin
// 03-10-2003: FillArray++
// 03-10-2003: (T)Fill2DArray
// 03-10-2003: Show2DArray
// 06-10-2003: RelDistance
// 06-10-2003: EmptyBitmap
// 06-10-2003: EulerIntegrate++
// 13-10-2003: added multi-platform compatibility
// 13-10-2003: (T,C) ShowArray
// 17-10-2003: Dot
// 19-10-2003: Morpher
// 19-10-2003: AutoMorpher
// 20-10-2003: (C) Dot
// 21-10-2003: the definition RICHELISCOOL added
// 21-10-2003: only includes math.h when not already included
// 21-10-2003: FillBitmap
// 09-11-2003: FindArrayMax(T)
// 09-11-2003: FindArrayMin(T)
// 30-11-2003: EmptyChart
//
// (T) denotes Template function
// (C) denotes Console function
// ++ denotes an improvement of the function
//
// Life of replaced functions, from birth to replacement:
//
// 27-05-2003 to 14-06-2003: SafeMeanAndStdDevDouble
// 27-05-2003 to 14-06-2003: SafeMeanAndStdDevInt
// 17-06-2003 to 17-06-2003: swapsortInt
// 19-06-2003 to 20-06-2003: (T) FindStartPoint
// 14-06-2003 to 23-06-2004: (T) SafeMeanAndStdDev (didn't check if arraysize was bigger then one
//
// FAQ's:
//
// Q: What are template functions?
// A: These are functions in which you can use more then one nametype as function arguments.
//    This means, that at first I had the functions SafeMeanAndStdDevInt and SafeMeanAndStdDevDouble,
//    for each type of array one function. Now, there is the function SafeMeanAndStdDev in which
//    you can find the StdDev and Mean of each type of array! The T in the function means Template,
//    which can be seen as a joker for int, double, etc.
//
// Q: How do I use SortAdresses? One of the function arguments is called
//    'int * * arraypointerpointer', what does that mean?
// A: It means that you have to give the first address of an array of pointers. This array of
//    of pointers have to point to the values you want to sort. This is necessary for sorting
//    an array of a class.
//
// Q: How do I use EulerIntegrate?
// A: first declare a function like:
//    double MyFunction(double x) { return (sin(x));}
//    Put the address of the function in EulerIntegrate (by just typing its name)
//    EulerIntegrate(resolution,min,max,MyFunction)
//
// Q: what is the difference between 'template <typename T>' and 'template <class T>'?
// A: the latter probably has higher functionality, but the first also gets the job
//    properly done. In my oldes functions I used the first and later on the second
//    way more often.
//
//  Q: What is the difference between AnsiString and String?
//  A: None. String is typedef-ed as an AnsiString. In the beginning, I only knew AnsiString.
//
////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
T abs(T value)
 {
 T solution=value;
 if (solution<0.0) solution-=(solution+solution);
 return (solution);
 }//End of: T abs


void AddNoiseDouble(double * arraypointer, int arraysize, double amplitude)
 {
 int counter; for (counter=0;counter<arraysize;counter++)
   {
   (*arraypointer)+= ( ((random(10000)/10000.0)*(2*amplitude))-amplitude );
   arraypointer++;
   }
 }//End of: void AddNoiseDouble



void Adjecent4(int x1, int y1, int &x2, int& y2)
  {
  //Finds an adjecent square (x2,y2) next to (x1,y1) in 4 directions
  switch(random(4))
    {
    case 0 : y2=y1-1; x2=x1; break;
    case 1 : x2=x1-1; y2=y1; break;
    case 2 : y2=y1+1; x2=x1; break;
    case 3 : x2=x1-1; y2=y1; break;
    }//End of: switch (random(4))
  }//End of: void Adjecent4


double angle(double deltaX, double deltaY)
  {
  double solution;
  if ((deltaX==0) && (deltaY==0)) {solution=0.0;}
  if ((deltaX==0) && (deltaY<0)) {solution=0.0;}
  if ((deltaX==0) && (deltaY>0)) {solution=M_PI;}
  if ((deltaX>0) && (deltaY==0)) {solution=M_PI_2;}
  if ((deltaX<0) && (deltaY==0)) {solution=(3.0*M_PI_2);}
  if ((deltaX>0) && (deltaY<0)) {solution=(0.0-atan(deltaX/deltaY));}
  if ((deltaX>0) && (deltaY>0)) {solution=(M_PI-atan(deltaX/deltaY));}
  if ((deltaX<0) && (deltaY>0)) {solution=(M_PI-atan(deltaX/deltaY));}
  if ((deltaX<0) && (deltaY<0)) {solution=((2*M_PI)-atan(deltaX/deltaY));}
  return(solution);
  }//End of: double angle


int asc(char letter)
  {
  return static_cast<int>(letter);
  }//End of: int asc


int BoolToInt(bool getal)
  {
  // Converts TRUE to 1 and FALSE to 0
  int uitkomst=0;
  if (getal==true) {uitkomst=1;}
  return (uitkomst);
  }//End of: BoolToInt

template <class T>
void CutOff(T& value, T min, T max)
  {
  if (value>max) {value=max;}
  if (value<min) {value=min;}
  }//End of: void CutOff

template <class T>
void CutOff(T& value1, T& value2, T min, T max)
  {
  if (value1>max) {value1=max;}
  if (value1<min) {value1=min;}
  if (value2>max) {value2=max;}
  if (value2<min) {value2=min;}
  }//End of: void CutOff

template <class T>
void CutOff(T& value1, T& value2, T& value3, T min, T max)
  {
  if (value1>max) {value1=max;}
  if (value1<min) {value1=min;}
  if (value2>max) {value2=max;}
  if (value2<min) {value2=min;}
  if (value3>max) {value3=max;}
  if (value3<min) {value3=min;}
  }//End of: void CutOff


template <typename T>
void DiffArray(T * arraypointer, int arraysize, T * otherarraypointer, T * differencearraypointer)
 {
 int counter; for (counter=0; counter<arraysize; counter++)
   {
   (*differencearraypointer)=(*arraypointer)-(*otherarraypointer);
   differencearraypointer++;
   arraypointer++;
   otherarraypointer++;
   }
 }//End of: void DiffArray



template <class T>
inline double Distance(T x1, T y1, T x2, T y2)
  {
  return  (sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1))));
  }//End of: Distance




template <typename T>
void EmptyArray(T *arraypointer, int arraysize)
  {
  int counter;
  for (counter=0;counter<arraysize;counter++)
    {
    *arraypointer=0;
    arraypointer++;
    }
  }//End of void EmptyArray


double EulerIntegrate(double resolution,double minimum, double maximum,double Function(double nothing))
  {
  double surface=0.0;
  double counter; for (counter=minimum; counter<maximum ;counter+=((maximum-minimum)/resolution))
    {
    surface+=Function(counter)*((maximum-minimum)/resolution);
    }//Next counter
  return(surface);
  }//End of: double EulerIntegrate






void FillAddressessRandom(int * * arraypointerspointer, int arraypointersize)
  {
  int counter;
  for (counter=0;counter<arraypointersize;counter++)
    {
    * * arraypointerspointer=random(100);
    arraypointerspointer++;
    }
  }//End of: FillAdressessRandom


template <typename T>
void FillArray(T *arraypointer, int arraysize, T filling)
  {
  int counter;
  for (counter=0;counter<arraysize;counter++)
    {
    *arraypointer=filling;
    arraypointer++;
    }
  }//End of: void FillArray

template <class T, class X>
void FillArray(T *arraypointer, int arraysize, T AnyFunction(X))
  {
  int counter;
  for (counter=0;counter<arraysize;counter++)
    {
    //*arraypointer=AnyFunction(counter);
    //arraypointer++;
    arraypointer[counter]=AnyFunction(counter);
    }
  }//End of: void FillArray

template <class T>
T FindArrayMax(T * array,int arraysize)
  {
  T maximum=array[0];
  int counter; for (counter=1; counter<arraysize ;counter++)
    {
    if (array[counter]>maximum) maximum=array[counter];
    }//Next counter
  return (maximum);
  }

template <class T>
T FindArrayMin(T * array,int arraysize)
  {
  T minimum=array[0];
  int counter; for (counter=1; counter<arraysize ;counter++)
    {
    if (array[counter]<minimum) minimum=array[counter];
    }//Next counter
  return (maximum);
  }


template <typename T>
void FillArrayRandom(T * arraypointer, int arraysize, T maxrandomnumber, T resolution)
  {
  //Resultion equals 1 for integers!
  int counter;
  for (counter=0;counter<N;counter++)
    {
    *arraypointer=(random(maxrandomnumber*resolution)/resolution);
    arraypointer++;
    }
  }//End of: FillArrayRandom


template <typename T>
int FindExtremes(T * arraypointer, int arraysize, T &minimum, T &maximum)
  {
  minimum=(*arraypointer);
  maximum=(*arraypointer);
  arraypointer++;
  int counter; for (counter=1;counter<arraysize;counter++)
    {
    if ( (*arraypointer)>maximum) {maximum=(*arraypointer);}
    if ( (*arraypointer)<minimum) {minimum=(*arraypointer);}
    arraypointer++;
    }
  return (1);
  }//End of: int FindExtremes



template <typename T>
int FindStart(T * arraypointer, int arraysize, T threshold)
  {
  int solution=-1;
  bool signfirst, signother;
  if (((*arraypointer)-threshold)>=0.0) {signfirst=true;} else {signfirst=false;}
  arraypointer++;
  int counter; for (counter=1;counter<arraysize;counter++)
    {
    if (((*arraypointer)-threshold)>=0.0) {signother=true;} else {signother=false;}
    arraypointer++;
    if (signother!=signfirst) {solution=counter; break;}
    }
  return solution;
  }//End of: int FindStart


template <typename T>
void Histogram(T *datasetarraypointer, int datasetarraysize, int *resultsarraypointer, int resultsarraysize, T maxnumber)
  {
  EmptyArray(resultsarraypointer,resultsarraysize);
  HistogramTransfer(datasetarraypointer,datasetarraysize,resultsarraypointer,resultsarraysize, maxnumber);
  }//End of: void Histogram


template <typename T>
inline int HistogramCategory(T number, int categories, T maxnumber)
  {
  return (number*categories/maxnumber);
  }//End of: void HistogramCategory


template <typename T>
void HistogramTransfer(T * datasetarraypointer, int datasetsize, int * resultsarraypointer,int resultsarraysize, T maxnumber)
  {
  int counter;
  for (counter=0;counter<datasetsize;counter++)
    {
    (*(resultsarraypointer+(HistogramCategory( (*datasetarraypointer) ,resultsarraysize ,maxnumber)   )))++;
    datasetarraypointer++;
    }
  }//End of: void HistogramTransfer






template <typename T>
bool IsNegative(T value)
  {
  bool solution=true;
  if (value>0.0) {solution=false;}
  return (solution);
  }//End of: bool IsNegative


template <typename T>
bool IsPositive(T value)
  {
  bool solution=true;
  if (value<0.0) {solution=false;}
  return (solution);
  }//End of: bool IsPositive


void MakeArrayLogisticGrowth(double * arraypointer, int arraysize,
                             double populationsize,
                             double intrinsic_growth_rate,
                             double carrying_capacity)
 {
 //Population size = initial population size
 (*arraypointer)=populationsize;
 int counter; for (counter=0;counter<arraysize;counter++)
   {
   *arraypointer=populationsize;
   arraypointer++;
   populationsize+=((intrinsic_growth_rate*populationsize)*(1-(populationsize/carrying_capacity)));
   }
 *arraypointer=populationsize;
 }//End of: void MakeArrayLogisticGrowth



void MakeArrayPointers(int * arraypointer, int arraysize, int * * pointerarraypointer)
  {
  int counter;for (counter=0;counter<arraysize;counter++)
    {
    (*pointerarraypointer) =& (*arraypointer);
    pointerarraypointer++;
    arraypointer++;
    }
  }//End of: void MakeArrayPointers



template <class T>
void Mobius(T &number,T min, T max)
  {
  if (number>max) {number-=(max+min);}
  if (number<min) {number+=(max-min);}
  }//End of: void Mobius


double mutate(const double getal,double delta,double minimum, double maximum)
  {
  // double getal e [0,1], double delta e [0, small value <<1 ]
  double solution=getal;
  double randomnumber=((random(2000001)/1000000.0)-1.0); // e [-1,1]
  double mutation=(randomnumber*delta); // e [-delta,delta]
  solution+=mutation;
  if (solution<minimum) {solution=minimum;}
  if (solution>maximum) {solution=maximum;}
  return(solution);
  }//End of: double mutate




template <class T>
inline void PlusMinus(T & value)
  {
  value+=(random(3)-1);
  }//End of: void PlusMinus


template <class T>
void PlusMinus(T& value1, T& value2)
  {
  value1+=(std::random(3)-1);
  value2+=(std::random(3)-1);
  }//End of: void PlusMinus


template <class T>
void PlusMinus(T& value1, T& value2, T& value3)
  {
  value1+=(random(3)-1);
  value2+=(random(3)-1);
  value3+=(random(3)-1);
  }//End of: void PlusMinus


/*int Rainbow(double value)
 {
 //input value e [0,1] for rainbow from red to violet
 //use values e [1.0,1.2] to make rainbow cyclic (from violet to red)
 int R=0,G=0,B=0, solution=-1;
 if (value>=0.0 && value<=0.2) {R=255; G=((value/0.2)*255);}
 if (value>=0.2 && value<=0.4) {G=255; R=(((0.4-value)/0.2)*255);}
 if (value>=0.4 && value<=0.6) {G=255; B=(((value-0.4)/0.2)*255);}
 if (value>=0.6 && value<=0.8) {B=255; G=(((0.8-value)/0.2)*255);}
 if (value>=0.8 && value<=1.0) {B=255; R=(((value-0.8)/0.2)*255);}
 if (value>=1.0 && value<=1.2) {R=255; B=(((1.2-value)/0.2)*255);}
 solution=(B*65536)+(G*256)+R;
 return(solution);
 }//End of: int Rainbow*/

TColor Rainbow(double value)
 {
 //input value e [0,1] for rainbow from red to violet
 //use values e [1.0,1.2] to make rainbow cyclic (from violet to red)
 int R=0,G=0,B=0;
 if (value>=0.0 && value<=0.2) {R=255; G=((value/0.2)*255);}
 if (value>=0.2 && value<=0.4) {G=255; R=(((0.4-value)/0.2)*255);}
 if (value>=0.4 && value<=0.6) {G=255; B=(((value-0.4)/0.2)*255);}
 if (value>=0.6 && value<=0.8) {B=255; G=(((0.8-value)/0.2)*255);}
 if (value>=0.8 && value<=1.0) {B=255; R=(((value-0.8)/0.2)*255);}
 if (value>=1.0 && value<=1.2) {R=255; B=(((1.2-value)/0.2)*255);}
 TColor solution=(TColor)RGB(R,G,B);
 return(solution);
 }//End of: int Rainbow


bool RandomBool(void)
  {
  bool solution=false;
  if (random(2)==1) solution=true;
  return (solution);
  }//End of: bool RandomBool



void Rmutate(double &getal,double delta,double minimum, double maximum)
  {
  //Uses referencing
  // double getal e [0,1], double delta e [0, small value <<1 ]
  double randomnumber=((random(2000001)/1000000.0)-1.0); // e [-1,1]
  double mutation=(randomnumber*delta); // e [-delta,delta]
  getal+=mutation;
  if (getal<minimum) {getal=minimum;}
  if (getal>maximum) {getal=maximum;}
  }//End of: void Rmutate

//Replaced at 24 June 2003
//template <typename T>
//void SafeMeanAndStdDev(T *arraypointer, int arraysize, double &Mean, double &StdDev)
//  {
//  double X=0.0, XSquared=0.0;
//  int counter; for (counter=0;counter<arraysize;counter++)
//    {
//    X+=*arraypointer;
//    XSquared+=((*arraypointer)*(*arraypointer));
//    arraypointer++;
//    }//Next counter
//  Mean=(X/arraysize);
//  //Safe part:
//  double numerator=((arraysize*XSquared)-(X*X));
//  if (numerator<0) {numerator=0;}
//  StdDev=sqrt(numerator/(arraysize*(arraysize-1)));
//  }//End of: void SafeMeanAndStdDev

template <class T>
int SafeMeanAndStdDev(T *arraypointer, int arraysize, double &Mean, double &StdDev)
 {
 if (arraysize>1)
   {
   double X=0.0, XSquared=0.0;
   int counter; for (counter=0;counter<arraysize;counter++)
     {
     X+=*arraypointer;
     XSquared+=((*arraypointer)*(*arraypointer));
     arraypointer++;
     }//Next counter
   Mean=(X/arraysize);
   //Safe part:
   double numerator=((arraysize*XSquared)-(X*X));
   if (numerator<0) {numerator=0;}
   StdDev=sqrt(numerator/(arraysize*(arraysize-1)));
   return(1);
   }
 else
   {
   ShowMessage("Arraysize must be larger then 1!");
   return (0);
   }
 }//End of: void SafeMeanAndStdDev



template <typename T>
void swap(T &number1, T &number2)
  {
  T temp=number1;
  number1=number2;
  number2=temp;
  }//End of: void swap


void SortAddresses(int * * arraypointerpointer, int arraysize)
  {
  int i,j;
  for(i=0;i<arraysize-1;i++)
    {
    int * * arraypointerpointer2=arraypointerpointer;
    for(j=i;j<arraysize;j++)
      {
      if(   * * arraypointerpointer > * * arraypointerpointer2 ) swap( * * arraypointerpointer , * * arraypointerpointer2 );
      arraypointerpointer2++;
      }
    arraypointerpointer++;
    }
  }//End of: SortAddressess


template <typename T>
void swapsort(T * arraypointer, int arraysize)
  {
  int i,j;
  for(i=0;i<arraysize-1;i++)
    {
    T * arraypointer2=arraypointer;
    for(j=i;j<arraysize;j++)
      {
      if( (*arraypointer) > (*arraypointer2) ) swap( (*arraypointer),(*arraypointer2) );
      arraypointer2++;
      }
    arraypointer++;
    }
  }//End of: void swapsort


template <typename T>
T TotalSum(T * arraypointer, int arraysize)
  {
  T solution=0;
  int counter;
  for (counter=0;counter<arraysize; counter++)
    {
    solution+=*arraypointer;
    arraypointer++;
    }
  return(solution);
  }//End of: TotalSum


bool Coin(void)
  {
  if (random(2)==1) {return (false);}
  else {return (true);}
  }//End of: bool Coin(void)



template <class T>
void Fill2DArray(T * * array, int maxx, int maxy, T MyFunction(int,int))
  {
  int x, y,counter;
  for (y=0; y<maxy; y++)
    {
    for (x=0; x<maxx; x++)
      {
      array[x][y]=MyFunction(x,y);
      }//Next x
    }//Next y
  }

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//  THE FUNCTIONS USING COUT                                                 //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#ifdef __STD_IOSTREAM__

void Show2DArray(int * * array, int maxx, int maxy)
  {
  int x,y;
  for (y=0; y<maxy; y++)
    {
    for (x=0; x<maxx; x++)
      {
      cout << x << " , " << y << " : " << array[x][y] << endl;
      }//Next x
    }//Next y
  }

string BoolToText(bool getal)
  {
  // Converts TRUE to 1 and FALSE to 0
  string uitkomst="FALSE";
  if (getal==true) {uitkomst="TRUE";}
  return (uitkomst);
  }//End of BoolToText

template <class T>
void ShowArray(T * array, int arraysize, int collumns)
  {
  int counter; for (counter=0;counter<arraysize;counter++)
    {
    cout << counter << " : " << array[counter];
    if (counter%collumns==0 && counter!=0) {cout << "\n";} else { cout << "\t";}
    }
  }//End of: string IntArrayToString

void Dot(int messagenumber, bool wait)
  {
  cout << "DOT : " << messagenumber << endl;
  if (wait==true) getchar();
  }

void Dot(void)
  {
  cout << "." << endl;
  }

void Dot(bool wait)
  {
  cout << "." << endl;
  if (wait==true) getchar();
  }

//End of: #ifdef __STD_IOSTREAM__
#endif

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//  THE FUNCTIONS USING THE VCL                                              //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#ifdef VCL_H
int asc(String letter)
  {
  return(static_cast<int> (letter[1]) );
  }//End of: int asc

AnsiString BoolToText(bool getal)
  {
  // Converts TRUE to 1 and FALSE to 0
  AnsiString uitkomst="FALSE";
  if (getal==true) {uitkomst="TRUE";}
  return (uitkomst);
  }//End of BoolToText

String CharArrayToString(char * arraypointer, int arraysize)
  {
  AnsiString solution="";
  int counter;
  for (counter=0;counter<arraysize;counter++)
    {
    solution+=IntToStr(counter)+":"+(*arraypointer);
    arraypointer++;
    if (counter%20==0 && counter!=0) {solution+="\n";} else {solution+="    ";}
    }
  return(solution);
  }//End of: String CharArrayToString

inline int IntegerLength(int getal) {return (IntToStr(getal).Length()); }

AnsiString DoubleToString(double value)
  {
  // You can also typecast! E.g. ShowMessage("Hello"+(String)value);
  //
  //ANY double can be put into this function
  //For <-1,0> the maximum length of the string is 11 (a minus, a number, a comma, eight decimals)
  //For [0,1> the maximum length of the string is 10 (a zero, a comma, eight decimals)
  //For [1,10] the maximum length of the string is 10 (a first decimal, a comma, eight decimals)
  //For [10,-> the maximum length of the string is 19 (ten decimal, a comma, eight decimals)
  AnsiString solution="";
  if (value<0) {solution="-"; value*=(-1);}
  int shitbeforethecomma=value;
  solution+=IntToStr(shitbeforethecomma);
  solution+=".";
  double shitbehindthecomma=value-shitbeforethecomma;
  int intshitbehindthecomma=(shitbehindthecomma*100000000); //IntPower(10,8)
  switch (IntegerLength(intshitbehindthecomma))
    {
    case 8 : break;
    case 7 : solution+="0"; break;
    case 6 : solution+="00"; break;
    case 5 : solution+="000"; break;
    case 4 : solution+="0000"; break;
    case 3 : solution+="00000"; break;
    case 2 : solution+="000000"; break;
    case 1 : solution+="0000000"; break;
    case 0 : solution+="00000000"; break;
    } //End of Switch statement
  solution+=IntToStr(intshitbehindthecomma);
  return (solution);
  }//End of: String DoubleToString


AnsiString DoubleArrayToString(double * arraypointer, int arraysize)
  {
  AnsiString solution="";
  int counter;
  for (counter=0;counter<arraysize;counter++)
    {
    solution+=IntToStr(counter)+":"+DoubleToString(*arraypointer);
    if (counter%5==0 && counter!=0) {solution+="\n";} else {solution+="    ";}
    arraypointer++;
    }
  return(solution);
  }//End of: AnsiString DoubleArrayToString

void ExtractRGB(int colorvalue, int &R, int &G, int &B)
   {
//   int getal1=colorvalue%(256*256);
//   R=getal1%256;
//   G=(getal1-R)/256;
//   B=(colorvalue-R-G)/65536;
   R=GetRValue(colorvalue);
   G=GetGValue(colorvalue);
   B=GetBValue(colorvalue);
   }//End of:

AnsiString IntAdressesToString(int * * arraypointerspointer , int arraypointersize)
  {
  //Show indi.age with pointers
  //int * * pointerpointer = &arraypointers[0];
  AnsiString solution="";
  int counter;
  for (counter=0;counter<arraypointersize;counter++)
    {
    solution+=IntToStr(counter)
            +":"
            +IntToStr(* * arraypointerspointer);
    if (counter%10==0 && counter!=0) {solution+="\n";} else {solution+="    ";}
    arraypointerspointer++;
    }
  return (solution);
  }//End of: AnsiString IntAdressesToString



AnsiString IntPointerArrayToString(int ** pointerarray, int pointerarraysize)
  {
  AnsiString solution="";
  int counter;
  for (counter=0; counter<pointerarraysize; counter++)
    {
    solution+=IntToStr(**pointerarray)+" ";
    *pointerarray++;
    }
  return (solution);
  }//End of: IntPointerArratToString

AnsiString IntArrayToString(int * arraypointer, int arraysize)
  {
  AnsiString solution="";
  int counter;
  for (counter=0;counter<arraysize;counter++)
    {
    solution+=IntToStr(counter)+":"+IntToStr(*arraypointer);
    if (counter%10==0 && counter!=0) {solution+="\n";} else {solution+="    ";}
    arraypointer++;
    }
  return(solution);
  }//End of: AnsiString IntArrayToString

AnsiString nullen (int aantal)
  {
  // Returns an AnsiString containg [aantal] zeroes
  // aantal e [0,->>
  AnsiString uitkomst="";
  int counter; for (counter=0;counter<aantal;counter++)
  {  uitkomst+="0";  }
  return (uitkomst);
  }//End of: AnsiString nullen


void ShowArray(double * arraypointer, int arraysize)
  { ShowMessage(DoubleArrayToString(arraypointer,arraysize));}//End of: void ShowArray

void ShowArray(int * arraypointer, int arraysize)
  { ShowMessage(IntArrayToString(arraypointer,arraysize));}//End of: void ShowArray

void ShowArray(char * arraypointer, int arraysize)
  { ShowMessage(CharArrayToString(arraypointer,arraysize));}//End of: void ShowArray

String UnsignedCharArrayToString(unsigned char * arraypointer, int arraysize)
  {
  AnsiString solution="";
  int counter;
  for (counter=0;counter<arraysize;counter++)
    {
    solution+=IntToStr(counter)+":"+(*arraypointer);
    arraypointer++;
    if (counter%20==0 && counter!=0) {solution+="\n";} else {solution+="    ";}
    }
  return(solution);
  }//End of: String UnsignedCharArrayToString

void ShowArray(unsigned char * arraypointer, int arraysize)
  { ShowMessage(UnsignedCharArrayToString(arraypointer,arraysize));}//End of: void ShowArray


void EmptyBitmap(TImage * MyImage)
  {
  int y,x;
  unsigned char * MyLine;
  for (y=0; y<MyImage->Height; y++)
    {
    MyLine=(unsigned char *) MyImage->Picture->Bitmap->ScanLine[y];
    for (x=0; x<MyImage->Width; x++)
      {
      MyLine[x*3]=0;
      MyLine[x*3+1]=0;
      MyLine[x*3+2]=0;
      }//next x
    }//next y
  }//End of: void EmptyBitmap

void FillBitmap(TImage * MyImage, unsigned char red, unsigned char green, unsigned char blue)
  {
  int y,x;
  unsigned char * MyLine;
  for (y=0; y<MyImage->Height; y++)
    {
    MyLine=(unsigned char *) MyImage->Picture->Bitmap->ScanLine[y];
    for (x=0; x<MyImage->Width; x++)
      {
      MyLine[x*3]=blue;
      MyLine[x*3+1]=green;
      MyLine[x*3+2]=red;
      }//next x
    }//next y
  }//End of: void FillBitmap


void Dot(int messagenumber)
  {
  OutputDebugString((IntToStr(messagenumber)).c_str());
  }

void Dot(String MyMessage)
  {
  OutputDebugString(MyMessage.c_str());
  }

void Morpher(TImage * Image1, TImage * Image2, TImage * ImageResult, double morph)
  {
  int y,x;
  unsigned char * MyLine1;
  unsigned char * MyLine2;
  unsigned char * MyLineResult;
  for (y=0; y<ImageResult->Height; y++)
    {
    MyLine1=(unsigned char *) Image1->Picture->Bitmap->ScanLine[y];
    MyLine2=(unsigned char *) Image2->Picture->Bitmap->ScanLine[y];
    MyLineResult=(unsigned char *) ImageResult->Picture->Bitmap->ScanLine[y];
    for (x=0; x<ImageResult->Width; x++)
      {
      MyLineResult[x*3]= morph*(double)MyLine1[x*3]+ (1.0-morph)*(double)MyLine2[x*3];
      MyLineResult[x*3+1]= morph*(double)MyLine1[x*3+1]+ (1.0-morph)*(double)MyLine2[x*3+1];
      MyLineResult[x*3+2]= morph*(double)MyLine1[x*3+2]+ (1.0-morph)*(double)MyLine2[x*3+2];
      }//next x
    }//next y
  }

void AutoMorpher(TImage * Image1,TImage * Image2,TImage * ImageResult)
  {
  //Image1->Tag = time
  //Image2->Tag = maxtime
  //ImageResult->Tag = morphstep
  double morph=(double)Image1->Tag/(double)Image2->Tag;
  if (ImageResult->Tag==0) Image1->Tag++;
  if (ImageResult->Tag==1) Image1->Tag--;
  if (Image1->Tag==Image2->Tag+1) ImageResult->Tag=1;
  if (Image1->Tag==-1) ImageResult->Tag=0;
  int y,x;
  unsigned char * MyLine1;
  unsigned char * MyLine2;
  unsigned char * MyLineResult;
  for (y=0; y<ImageResult->Height; y++)
    {
    MyLine1=(unsigned char *) Image1->Picture->Bitmap->ScanLine[y];
    MyLine2=(unsigned char *) Image2->Picture->Bitmap->ScanLine[y];
    MyLineResult=(unsigned char *) ImageResult->Picture->Bitmap->ScanLine[y];
    for (x=0; x<ImageResult->Width; x++)
      {
      MyLineResult[x*3]= morph*(double)MyLine1[x*3]+ (1.0-morph)*(double)MyLine2[x*3];
      MyLineResult[x*3+1]= morph*(double)MyLine1[x*3+1]+ (1.0-morph)*(double)MyLine2[x*3+1];
      MyLineResult[x*3+2]= morph*(double)MyLine1[x*3+2]+ (1.0-morph)*(double)MyLine2[x*3+2];
      }//next x
    }//next y
  }

template <class T>
inline double RelDistance(T x1, T y1, T x2, T y2, double MaxDistance)
  {
  return  ( sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)))/MaxDistance);
  }//End of: Distance


#ifdef ChartHPP
void EmptyChart(TChart * AnyChart)
  {
  int counter; for (counter=0; counter<AnyChart->SeriesCount() ;counter++)
    {
    AnyChart->Series[counter]->Clear();
    }//Next counter
  }
//End of: #ifdef ChartHPP
#endif

//End of: #ifdef VCL_H
#endif

//End of: #ifndef RICHELISCOOL
#endif
