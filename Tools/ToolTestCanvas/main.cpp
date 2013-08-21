//---------------------------------------------------------------------------
/*
Canvas, ASCII art painting surface class
Copyright (C) 2008-2013  Richel Bilderbeek

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
// From http://www.richelbilderbeek.nl/CppCanvas.htm
//---------------------------------------------------------------------------

#include <iostream>
#include <string>
#include "canvas.h"

void ShowLicence()
{
  std::cout
    << std::string(79,'*') << std::endl
    << "Canvas, ASCII art painting surface class" << std::endl
    << "Copyright (C) 2008-2013 Richel Bilderbeek" << std::endl
    << std::endl
    << "This program is free software: you can redistribute it and/or modify"
      << std::endl
    << "it under the terms of the GNU General Public License as published by"
      << std::endl
    << "the Free Software Foundation, either version 3 of the License, or"
      << std::endl
    << "(at your option) any later version." << std::endl
    << std::endl
    << "This program is distributed in the hope that it will be useful,"
      << std::endl
    << "but WITHOUT ANY WARRANTY; without even the implied warranty of"
      << std::endl
    << "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the"
      << std::endl
    << "GNU General Public License for more details." << std::endl
    << "You should have received a copy of the GNU General Public License"
      << std::endl
    << "along with this program.If not, see <http://www.gnu.org/licenses/>."
      << std::endl
    << std::endl
    << std::string(79,'*') << std::endl
    << "From http://www.richelbilderbeek.nl" << std::endl
    << std::string(79,'*') << std::endl;
}

int main()
{
  //Specify the dimensions of the canvas equal to the screen
  //Coordinat (0,0) is the top-left coordinat
  //Coordinat (79,23) is the bottom-right coordinat
  const int maxx = 49;
  const int maxy = 23;
  Canvas c( maxx,maxy);

  //Draw smiley to Canvas

  //Determine and calculate dimensions and coordinats of smiley
  const double maxxD = static_cast<double>(maxx);
  const double maxyD = static_cast<double>(maxy);
  const double midX        = 0.50 * maxxD;
  const double midY        = 0.50 * maxyD;
  const double headRay     = 0.50 * maxyD;
  const double eyeLeftX    = 0.50 * maxxD - (0.35 * headRay) ;
  const double eyeLeftY    = 0.50 * maxyD - (0.25 * headRay) ;
  const double eyeRightX   = 0.50 * maxxD + (0.35 * headRay) ;
  const double eyeRightY   = 0.50 * maxyD - (0.25 * headRay) ;
  const double eyeRay      = 0.30 * headRay;
  const double mouthLeftX  = 0.50 * maxxD - (0.7 * headRay) ;
  const double mouthMidX   = 0.50 * maxxD;
  const double mouthRightX = 0.50 * maxxD + (0.7 * headRay) ;
  const double mouthLeftY  = 0.50 * maxyD + (0.2 * headRay) ;
  const double mouthMidY   = 0.50 * maxyD + (0.7 * headRay) ;
  const double mouthRightY = 0.50 * maxyD + (0.2 * headRay) ;
  //Draw the image on Canvas
  c.DrawCircle(midX, midY, headRay);
  c.DrawCircle(eyeLeftX, eyeLeftY, eyeRay);
  c.DrawDot(eyeLeftX, eyeLeftY);
  c.DrawCircle(eyeRightX, eyeRightY, eyeRay);
  c.DrawDot(eyeRightX, eyeRightY);
  c.DrawLine(mouthLeftX, mouthLeftY, mouthMidX, mouthMidY);
  c.DrawLine(mouthMidX, mouthMidY, mouthRightX, mouthRightY);
  c.DrawLine(mouthRightX, mouthRightY, mouthLeftX, mouthLeftY);
  //Display the image
  c.Cout();
  ShowLicence();
  {
    //Ask user for input
    std::string temp;
    std::getline(std::cin,temp);
  }
}
