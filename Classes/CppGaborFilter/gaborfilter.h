//---------------------------------------------------------------------------
/*
GaborFilter, Gabor filter class
Copyright (C) 2011-2015 Richel Bilderbeek

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
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/checked_delete.hpp>

#include <boost/signals2.hpp>
#pragma GCC diagnostic pop

namespace ribi {

///GaborFilter manages a Gabor filter
struct GaborFilter
{
  GaborFilter(
    const double angle     = 0.0,
    const double frequency = 1.0,
    const double sigma     = 1.0);
  GaborFilter(const GaborFilter&) = delete;
  GaborFilter& operator=(const GaborFilter&) = delete;

  ///Signal emitted when a value of the Gabor filter changes
  mutable boost::signals2::signal<void ()> m_signal_changed;

  ///Get the GaborFilter its angle
  double GetAngle() const noexcept { return m_angle;  }

  ///Get the GaborFilter its frequency
  double GetFrequency() const noexcept { return m_frequency;  }

  double GetMax() const noexcept { return 1.0; }

  ///Get the GaborFilter its sigma
  double GetSigma() const noexcept { return m_sigma;  }


  ///The Gabor funtion
  static double GaborFunction(
    const double x, const double y,
    const double angle, const double frequency,
    const double sigma);

  ///The Gabor funtion
  double GaborFunction(
    const double x, const double y) const;

  ///Set the GaborFilter its angle
  void SetAngle(const double angle) noexcept;

  ///Set the GaborFilter its frequency
  void SetFrequency(const double frequency);

  ///Set the GaborFilter its sigma
  void SetSigma(const double sigma);

  ///Set the GaborFilter its sigma to
  double SuggestSigma(const double width, const double height) const;

  private:
  virtual ~GaborFilter() noexcept {}
  friend void boost::checked_delete<>(GaborFilter*);
  friend void boost::checked_delete<>(const GaborFilter*);

  ///Angle of the filter in radians
  double m_angle;

  ///The GaborFilter its frequency
  double m_frequency;

  ///The GaborFilter its sigma
  double m_sigma;

  public:
  ///Obtain this class its version
  static std::string GetVersion() noexcept;

  ///Obtain this class its version history
  static std::vector<std::string> GetVersionHistory() noexcept;
};

std::ostream& operator<<(std::ostream& os, const GaborFilter& g) noexcept;

} //~namespace ribi

#endif // GABORFILTER_H
