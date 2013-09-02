//---------------------------------------------------------------------------
/*
GaborFilter, Gabor filter class
Copyright (C) 2011 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppGaborFilter.htm
//---------------------------------------------------------------------------
#ifndef GABORFILTER_H
#define GABORFILTER_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/checked_delete.hpp>
#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>
#pragma GCC diagnostic pop

///GaborFilter manages a Gabor filter
struct GaborFilter : public boost::noncopyable
{
  GaborFilter(
    const double angle     = 0.0,
    const double frequency = 1.0,
    const double sigma     = 1.0);

  ///Signal emitted when a value of the Gabor filter changes
  mutable boost::signals2::signal<void ()> m_signal_changed;

  ///Get the GaborFilter its angle
  double GetAngle()  const { return m_angle;  }

  ///Get the GaborFilter its frequency
  double GetFrequency()  const { return m_frequency;  }

  double GetMax() const { return 1.0; }

  ///Get the GaborFilter its sigma
  double GetSigma()  const { return m_sigma;  }


  ///The Gabor funtion
  static double GaborFunction(
    const double x, const double y,
    const double angle, const double frequency,
    const double sigma);

  ///The Gabor funtion
  double GaborFunction(
    const double x, const double y) const;

  ///Set the GaborFilter its angle
  void SetAngle(const double angle);

  ///Set the GaborFilter its frequency
  void SetFrequency(const double frequency);

  ///Set the GaborFilter its sigma
  void SetSigma(const double sigma);

  ///Set the GaborFilter its sigma to
  double SuggestSigma(const double width, const double height) const;

  private:
  ///GaborFilter can only be deleted by Boost smart pointers
  virtual ~GaborFilter() {}
  ///GaborFilter can only be deleted by Boost smart pointers
  //Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
  friend void boost::checked_delete<>(GaborFilter*);

  ///Angle of the filter in radians
  double m_angle;

  ///The GaborFilter its frequency
  double m_frequency;

  ///The GaborFilter its sigma
  double m_sigma;

  public:
  ///Obtain this class its version
  static const std::string GetVersion();

  ///Obtain this class its version history
  static const std::vector<std::string> GetVersionHistory();
};

std::ostream& operator<<(std::ostream& os, const GaborFilter& g);

#endif // GABORFILTER_H
