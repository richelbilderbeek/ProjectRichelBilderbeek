//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <vector>
#include "UnitFormSprites.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSprites *FormSprites;
//---------------------------------------------------------------------------
__fastcall TFormSprites::TFormSprites(TComponent* Owner)
  : TForm(Owner)
{
  //Set transparencies of some Images right
  {
    std::vector<TImage*> images;
    images.push_back(ImagePlug220Connected);
    images.push_back(ImagePlug220ConnectedSelected);
    images.push_back(ImageJackMaleConnected);
    images.push_back(ImageJackMaleConnectedSelected);
    images.push_back(ImageEuroFemaleConnected);
    images.push_back(ImageEuroFemaleConnectedSelected);

    const std::vector<TImage*>::iterator j = images.end();
    for (std::vector<TImage*>::iterator i = images.begin(); i!=j; ++i)
    {
      (*i)->Picture->Bitmap->TransparentColor = clLime;
      (*i)->Picture->Bitmap->Transparent = true;
    }
  }
}
//---------------------------------------------------------------------------

