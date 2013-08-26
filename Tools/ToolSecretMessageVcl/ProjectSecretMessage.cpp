//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("UnitFormSecretMessage.cpp", FormSecretMessage);
USEFORM("UnitFormCreateSecret.cpp", FormCreateSecret);
USEFORM("UnitFormExtractSecret.cpp", FormExtractSecret);
USEFORM("UnitFormAbout.cpp", FormAbout);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  try
  {
     Application->Initialize();
     Application->Title = "Secret Message";
     Application->CreateForm(__classid(TFormSecretMessage), &FormSecretMessage);
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
