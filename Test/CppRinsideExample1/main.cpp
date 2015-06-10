// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4;  tab-width: 8; -*-
//
// Qt usage example for RInside, inspired by the standard 'density
// sliders' example for other GUI toolkits
//
// Copyright (C) 2011  Dirk Eddelbuettel and Romain Francois


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wextra"
#include <QApplication>
#include "qtdensity.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  RInside R(argc, argv);  		// create an embedded R instance
  QApplication app(argc, argv);
  QtDensity qtdensity(R);		// pass R inst. by reference
  return app.exec();
}
