#include <QApplication>
#include "qtmutualismbreakdownermenudialog.h"
#include "poisoningfunction.h"
#include "sulfideconsumptionfunction.h"
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

//Sulfide production:
// URL: http://www.marinebio.net/marinescience/04benthon/dsimg/dscuc.jpg
// by Genny Anderon

//Diffusion:
//  URL: http://en.wikipedia.org/wiki/Diffusion#/media/File:Blausen_0315_Diffusion.png
//  By BruceBlaus

//Sulfide detoxification:
//  Article name: The structure of Aquifex aeolicus sulfide:quinone oxidoreductase, a basis to understand sulfide detoxification and respiration
//  URL: http://www.pnas.org/content/106/24/9625/F6.expansion.html
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QtMutualismBreakdownerTimePlotDialog();
  QtMutualismBreakdownerEquilibriumDialog();
  #ifndef NDEBUG
  ribi::units::Test();
  #endif
  InvertedExponentialPoisoning();
  Parameters();
  ribi::QtMutualismBreakdownerMenuDialog w;
  w.show();
  return a.exec();
}
