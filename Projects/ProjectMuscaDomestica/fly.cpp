//---------------------------------------------------------------------------
/*
  Project Musca Domestica, simulation in which sex-ratio can evolve
  Copyright (C) 2009  Richl Bilderbeek

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
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#include "fly.h"
//---------------------------------------------------------------------------
void InitFPop(void)
{
//Assumes both FPop and NFFlyOnIsland are both empty
unsigned int Female;
//Fly fly;
for(Female=0;Female<NIslands*MaxFPopSize;Female++)
  {
  //Create a nice -in genetico- female fly
  FPop[Female].sex=female;
  FPop[Female].SLocus[0]=0.0001+(Uniform()*0.9998);
  FPop[Female].SLocus[1]=0.0001+(Uniform()*0.9998);
  FPop[Female].Mated=false;
  }//next Female
}

void InitMPop(void)
{
unsigned int Male;
for(Male=0;Male<NIslands*MaxMPopSize;Male++)
  {
  //Create a nice -in genetico- male fly
  MPop[Male].sex=male;
  MPop[Male].SLocus[0]=0.0001+(Uniform()*0.9998);
  MPop[Male].SLocus[1]=0.0001+(Uniform()*0.9998);
  }   //next Male
}

void CountGenome(const Fly & AnyFly)
{
SLocusCounter+=((AnyFly.SLocus[0]+AnyFly.SLocus[1])/2.0);
}



Fly CreateOffspringFather(const Fly & Mother,const Fly & Father)
{ //Father in control
assert(Mother.sex==female);
assert(Father.sex==male);
Fly FlyKiddo;
FlyKiddo.SLocus[0]=Mother.SLocus[RandomNumber(2)];
FlyKiddo.SLocus[1]=Father.SLocus[RandomNumber(2)];
//if (Coin()==true) swap(FlyKiddo.SLocus[0],FlyKiddo.SLocus[1]);
double ChanceOffspringIsMale = (Father.SLocus[0]+Father.SLocus[1])/2.0;
if (Uniform() < ChanceOffspringIsMale)
 { FlyKiddo.sex=male; }
else
 {
 FlyKiddo.sex=female;
 FlyKiddo.Mated=false;
 }

return(FlyKiddo);

}

Fly CreateOffspringMother(const Fly & Mother,const Fly & Father)
{
assert(Mother.sex==female);
assert(Father.sex==male);
Fly FlyKiddo;
FlyKiddo.SLocus[0]=Mother.SLocus[RandomNumber(2)];
FlyKiddo.SLocus[1]=Father.SLocus[RandomNumber(2)];
//if (Coin()==true) swap(FlyKiddo.SLocus[0],FlyKiddo.SLocus[1]);
double ChanceOffspringIsMale = (Mother.SLocus[0]+Mother.SLocus[1])/2.0;
if (Uniform() < ChanceOffspringIsMale)
 { FlyKiddo.sex=male; }
else
 {
 FlyKiddo.sex=female;
 FlyKiddo.Mated=false;
 }

return(FlyKiddo);

}

Fly CreateOffspringBoth(const Fly & Mother,const Fly & Father)
{
assert(Mother.sex==female);
assert(Father.sex==male);
Fly FlyKiddo;
FlyKiddo.SLocus[0]=Mother.SLocus[RandomNumber(2)];
FlyKiddo.SLocus[1]=Father.SLocus[RandomNumber(2)];
//if (Coin()==true) swap(FlyKiddo.SLocus[0],FlyKiddo.SLocus[1]);
double ChanceOffspringIsMale = (Mother.SLocus[0]+Mother.SLocus[1]+Father.SLocus[0]+Father.SLocus[1])/4.0;
if (Uniform() < ChanceOffspringIsMale)
 { FlyKiddo.sex=male; }
else
 {
 FlyKiddo.sex=female;
 FlyKiddo.Mated=false;
 }

return(FlyKiddo);

}

Fly CreateOffspringZygote(const Fly & Mother,const Fly & Father)
{
assert(Mother.sex==female);
assert(Father.sex==male);
Fly FlyKiddo;
FlyKiddo.SLocus[0]=Mother.SLocus[RandomNumber(2)];
FlyKiddo.SLocus[1]=Father.SLocus[RandomNumber(2)];
//if (Coin()==true) swap(FlyKiddo.SLocus[0],FlyKiddo.SLocus[1]);
double ChanceOffspringIsMale = (FlyKiddo.SLocus[0]+FlyKiddo.SLocus[1])/2.0;
if (Uniform() < ChanceOffspringIsMale)
 { FlyKiddo.sex=male; }
else
 {
 FlyKiddo.sex=female;
 FlyKiddo.Mated=false;
 }

return(FlyKiddo);

}







