//---------------------------------------------------------------------------
#include <vcl.h> //For precompiled header
#pragma hdrstop

#include <cassert>
#include "UnitController.h"
//---------------------------------------------------------------------------
Dial::Dial(const double position)
{
  SetPosition(position);
}
//---------------------------------------------------------------------------
void Dial::SetPosition(const double position)
{
  if      (mPosition < this->GetMinPosition())
  {
    mPosition = this->GetMinPosition();
  }
  else if (mPosition > this->GetMaxPosition())
  {
    mPosition = this->GetMaxPosition();
  }
  else
  {
    mPosition = position;
  }
}
//---------------------------------------------------------------------------
const double Dial::GetRelPosition() const
{
  const double relPosition = (this->GetPosition() - this->GetMinPosition())
    / (this->GetMaxPosition() - this->GetMinPosition());
  assert(relPosition >= 0.0);
  assert(relPosition <= 1.0);
  return relPosition;
}
//---------------------------------------------------------------------------
Fader::Fader(const double position)
{
  SetPosition(position);
}
//---------------------------------------------------------------------------
void Fader::SetPosition(const double position)
{
  if      (mPosition < this->GetMinPosition())
  {
    mPosition = this->GetMinPosition();
  }
  else if (mPosition > this->GetMaxPosition())
  {
    mPosition = this->GetMaxPosition();
  }
  else
  {
    mPosition = position;
  }
}
//---------------------------------------------------------------------------
const double Fader::GetRelPosition() const
{
  const double relPosition = (this->GetPosition() - this->GetMinPosition())
    / (this->GetMaxPosition() - this->GetMinPosition());
  assert(relPosition >= 0.0);
  assert(relPosition <= 1.0);
  return relPosition;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
