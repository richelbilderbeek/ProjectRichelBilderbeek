//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("UnitFormMain.cpp", FormMain);
USEFORM("UnitFormSprites.cpp", FormSprites);
USEFORM("UnitFormMenu.cpp", FormMenu);
USEFORM("UnitFormAbout.cpp", FormAbout);
USEFORM("UnitFormWhatsNew.cpp", FormWhatsNew);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  try
  {
     Application->Initialize();
     Application->Title = "PokeVolley";
     Application->CreateForm(__classid(TFormMenu), &FormMenu);
                 Application->CreateForm(__classid(TFormSprites), &FormSprites);
                 Application->Run();
  }
  catch (Exception &exception)
  {
     Application->ShowException(&exception);
  }
  catch (...)
  {
     try
     {
       throw Exception("");
     }
     catch (Exception &exception)
     {
       Application->ShowException(&exception);
     }
  }
  return 0;
}
//---------------------------------------------------------------------------
