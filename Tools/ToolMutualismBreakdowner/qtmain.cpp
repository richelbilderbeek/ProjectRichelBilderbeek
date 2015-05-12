#include <QApplication>
#include "qtmutualismbreakdownermenudialog.h"
#include "poisoningfunction.h"
#include "loripesconsumptionfunction.h"
#include "parameters.h"
#include "units.h"
#include "qtmutualismbreakdownerequilibriumdialog.h"
#include "qtmutualismbreakdownertimeplotdialog.h"

//Loripes lacteus
//  Images from http://www.idscaro.net/sci/01_coll/plates/bival/pl_lucinidae_1.htm
//  LoripesLactaus1.jpg and LoripesLactaus1.jpg:
//    Loripes lacteus (Linnaeus, 1758)
//    North Sea to Mauritania, Madeira to Mediterranean
//    Corsica 18mm
//  LoripesLactaus3.jpg and LoripesLactaus4.jpg:
//    Loripes lacteus (Linnaeus, 1758)
//    North Sea to Mauritania, Madeira to Mediterranean
//    NE. Italy 15-19mm
//Loripes lucinalis
//  Image by Joop Trausel and Frans Slieker
//  Image from http://eol.org/data_objects/32015683
//Zostera noltii
//  Images from http://flora.nhm-wien.ac.at/Seiten-Arten/Zostera-noltii.htm
//Equlibrium photo
//  Image from NIOZ, from http://www.nioz.nl/files/afdelingen/MEE/Seagrass6.jpg
//  The image was at the side of http://www.nioz.nl/nieuws-detail/biobouwers-structureren-het-voedselweb-in-intergetijde-kustgebieden

/*

2015-05-12:

              GROWTH WITH STRESS       POISONING

                      N                      b*e^(a*N)
dN/dt = N * ( r*(1 - ---) ) - d ) - (1 - ------------- )*m*N*S
                      K                  1 + b*e^(a*N)



dS/dt = bN - gS - vNS - cLS      = Sulfide production - Diffusion - Detoxification by SG - Consumption by Loripes



2015-05-11:

            GROWTH             POISONING

                  N              b*e^(a*N)
dN/dt = r*N*(1 - ---) - (1 - ------------- )*m*N*S
                  K          1 - b*e^(a*N)



        SULFIDE       EXTERNAL  DIFFUSION     DETOXIFICATION
        PRODUCTION    SULFIDE
                      INPUT

dS/dt =    b*N      +  theta   -    g*S    -       c*N*S

*/

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QtMutualismBreakdownerTimePlotDialog();
  QtMutualismBreakdownerEquilibriumDialog();
  ribi::units::Test();
  InvertedExponentialPoisoning();
  InvertedExponentialConsumption();
  Parameters();
  ribi::QtMutualismBreakdownerMenuDialog w;
  w.show();
  return a.exec();
}
