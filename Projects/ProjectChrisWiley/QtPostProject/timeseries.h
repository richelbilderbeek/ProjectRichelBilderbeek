//---------------------------------------------------------------------------
/*
  The Chris Wiley Project, simulation on mixed-pair mating
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
#ifndef TIMESERIES_H
#define TIMESERIES_H
//---------------------------------------------------------------------------
#include <vector>
#include <assert.h>
#include "timepoint.h"
//---------------------------------------------------------------------------
class TimeSeries
{
  public:
  std::vector<TimePoint> timePoints;
  bool isNull() const
  {
    if (timePoints.size()>0) return false;
    return true;
  }

  void operator+=(const TimeSeries& timeSeries) //For taking the average of multiple timepoints
  {
    const unsigned int nTimePoints = timePoints.size();
    assert(timeSeries.timePoints.size()==nTimePoints);
    for (unsigned i=0; i<nTimePoints; ++i)
    {
      timePoints[i]+=timeSeries.timePoints[i];
    }
  }
  void operator/=(const unsigned int& valueInt) //For taking the average of multiple timepoints
  {
    const unsigned int nTimePoints = timePoints.size();
    for (unsigned i=0; i<nTimePoints; ++i)
    {
      timePoints[i]/=valueInt;
    }
  }
};
//---------------------------------------------------------------------------
void getMeanAndStdErrorEndPoint(const std::vector<TimeSeries>& timeSeries, TimePoint& mean, TimePoint& stdError);
void getMeanAndStdErrorTimeSeries(const std::vector<TimeSeries>& timeSeries, TimeSeries& mean, TimeSeries& stdError);
//TimeSeries getAverageTimeSeries(const std::vector<TimeSeries>& timeSeries);
//TimePoint getAverageEndTimePoint(const std::vector<TimeSeries>& timeSeries);
//---------------------------------------------------------------------------
#endif // TIMESERIES_H
