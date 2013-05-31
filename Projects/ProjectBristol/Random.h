/*
 *  Random.h
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Tue May 24 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 *  Obtained from Sander van Doorn
 *
 *
 */
#ifndef __SANDER_RANDOM_H
#define __SANDER_RANDOM_H

#include <stdlib.h>
#include <math.h>

double uniform();
double gasdev();
void setSeed(const int&);
double normal(const double&,const double&);
int randomNumber(const int&);
int rando(const int&);

#endif //#ifndef __SANDER_RANDOM_H