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
#include "timeseries.h"
//---------------------------------------------------------------------------
void getMeanAndStdErrorEndPoint(const std::vector<TimeSeries>& timeSeries, TimePoint& mean, TimePoint& stdError)
{
  assert(mean.isNull()==true);
  assert(stdError.isNull()==true);

  //Only set: biasA, biasB, fractionMixedPairs

  const unsigned int nTimeSeries = timeSeries.size();
  for (unsigned i=0; i<nTimeSeries; ++i)
  {
    //Get the index of the final index
    const unsigned int time = timeSeries[i].timePoints.size() - 1;
    mean += timeSeries[i].timePoints[time];
  }
  mean/=nTimeSeries;
}
//---------------------------------------------------------------------------
void getMeanAndStdErrorTimeSeries(
  const std::vector<TimeSeries>& timeSeries,
  TimeSeries& mean,
  TimeSeries& /*stdError*/)
{
  assert(mean.isNull()==true);
  mean = timeSeries[0];
  const unsigned int nTimeSeries = timeSeries.size();
  for (unsigned i=1; i<nTimeSeries; ++i)
  {
    //Get the index of the final index
    mean += timeSeries[i];
  }
  mean/=nTimeSeries;
}
//---------------------------------------------------------------------------
