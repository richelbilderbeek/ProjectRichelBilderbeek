#include "nextgeneration.h"

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
void NextGenerationFemales(vector <Fly> & MPop, vector <Fly> & FPop,
                    vector <Fly> & MOffPop, vector <Fly> & FOffPop,
                    int MaxMales, int MaxFemales)
{
//We know that on all islands, there are MaxDsex and MaxNDsex
//Also in the offspring, there will be MaxDsex and MaxNDsex flies on each island
//If we assume large family size, we can go off all spots on all islands for both sexes
//The nondispers' parents are from the same island, the dispersers' sex parents are from
//another island. This is the trick we gonna use...
//The vectors of the offspring are size 0, so we only use pushback commands...
assert(FPop.size()==MaxFemales*NIslands);
assert(MPop.size()==MaxMales*NIslands);
assert(FOffPop.size()==MaxFemales*NIslands);
assert(MOffPop.size()==MaxMales*NIslands);
unsigned int OurIsland;
int FemaleSpot, MaleSpot, RandomIsland, RandomMother, RandomFather;
int IndexMother, IndexFather;
Fly FlyKiddo;

for (OurIsland=0; OurIsland<NIslands ;OurIsland++)
  {
  //Dispersing sex->females, take parents from random island
  for (FemaleSpot=0; FemaleSpot<MaxFemales ;FemaleSpot++)
    {
    //Throw away all offspring of non dispersing sex->males
    do
      {
      RandomIsland=RandomNumber(NIslands);
      RandomMother=RandomNumber(MaxFemales);
      IndexMother=(RandomIsland*MaxFemales)+RandomMother;
      if (FPop[IndexMother].Mated==false)
        {//She is a virgin
        RandomFather=RandomNumber(MaxMales);
        IndexFather=(RandomIsland*MaxMales)+RandomFather;
        FPop[IndexMother].Mated=true;
        FPop[IndexMother].IndexPartner=IndexFather;
        }
        else
        {//She mates again with the prince on the white horse
        IndexFather=FPop[IndexMother].IndexPartner;
        }
      FlyKiddo=CreateOffspring(FPop[IndexMother],MPop[IndexFather]);
      }
    while
     (FlyKiddo.sex==male);
    //OK, the female kiddo is born, put her in the vector
    CountGenome(FlyKiddo);
    FOffPop[(OurIsland*MaxFemales)+FemaleSpot]=FlyKiddo;
    }//Next FemaleSpot

  //Non-dispersing sex->males, take parents from same island
  for (MaleSpot=0; MaleSpot<MaxMales ;MaleSpot++)
    {
    //Throw away all offspring of dispersing sex->females
    do
      {
      RandomMother=RandomNumber(MaxFemales);
      IndexMother=(OurIsland*MaxFemales)+RandomMother;
      if (FPop[IndexMother].Mated==false)
        {//She is a virgin
        RandomFather=RandomNumber(MaxMales);
        IndexFather=(OurIsland*MaxMales)+RandomFather;
        FPop[IndexMother].Mated=true;
        FPop[IndexMother].IndexPartner=IndexFather;
        }
      else
        {//She mates again with the prince on the white horse
        IndexFather=FPop[IndexMother].IndexPartner;
        }
      FlyKiddo=CreateOffspring(FPop[IndexMother],MPop[IndexFather]);
      }
    while
     (FlyKiddo.sex==female);
    //OK, the male kiddo is born, give him its spot in the vector
    CountGenome(FlyKiddo);
    MOffPop[(OurIsland*MaxMales)+MaleSpot]=FlyKiddo;
    }//Next MaleSpot
  }//Next OurIsland
}

///////////////////////////////////////////////////////////////////////////////////////////////
//
// MALES DISPERSE
//
///////////////////////////////////////////////////////////////////////////////////////////////
void NextGenerationMales(vector <Fly> & MPop, vector <Fly> & FPop,
                    vector <Fly> & MOffPop, vector <Fly> & FOffPop,
                    int MaxMales, int MaxFemales)
{
//We know that on all islands, there are MaxDsex and MaxNDsex
//Also in the offspring, there will be MaxDsex and MaxNDsex flies on each island
//If we assume large family size, we can go off all spots on all islands for both sexes
//The nondispers' parents are from the same island, the dispersers' sex parents are from
//another island. This is the trick we gonna use...
//The vectors of the offspring are size 0, so we only use pushback commands...
assert(MPop.size()==MaxMales*NIslands);
assert(FPop.size()==MaxMales*NIslands);
assert(MOffPop.size()==MaxMales*NIslands);
assert(FOffPop.size()==MaxMales*NIslands);
unsigned int OurIsland;
int MaleSpot, FemaleSpot, RandomIsland, RandomFather, RandomMother;
int IndexFather, IndexMother;
Fly FlyKiddo;

for (OurIsland=0; OurIsland<NIslands ;OurIsland++)
  {
  //Dispersing sex, take parents from random island
  for (MaleSpot=0; MaleSpot<MaxMales ;MaleSpot++)
    {
    //Throw away all offspring of non dispersing sex
    do
      {
      RandomIsland=RandomNumber(NIslands);
      RandomMother=RandomNumber(MaxFemales);
      IndexMother=(RandomIsland*MaxFemales)+RandomMother;
      if (FPop[IndexMother].Mated==false)
        {//She is a virgin
        RandomFather=RandomNumber(MaxMales);
        IndexFather=(RandomIsland*MaxMales)+RandomFather;
        FPop[IndexMother].Mated=true;
        FPop[IndexMother].IndexPartner=IndexFather;
        }
        else
        {//She mates again with the prince on the white horse
        IndexFather=FPop[IndexMother].IndexPartner;
        }
      FlyKiddo=CreateOffspring(FPop[IndexMother],MPop[IndexFather]);
      }
    while
     (FlyKiddo.sex==female);
    //OK, the male kiddo is born, give him its spot in the vector
    CountGenome(FlyKiddo);
    MOffPop[(OurIsland*MaxMales)+MaleSpot]=FlyKiddo;
    }//Next MaleSpot

  //Non-dispersing sex, take parents from same island
  for (FemaleSpot=0; FemaleSpot<MaxFemales ;FemaleSpot++)
    {
    //Throw away all offspring of dispersing sex
    do
      {
      RandomMother=RandomNumber(MaxFemales);
      IndexMother=(OurIsland*MaxFemales)+RandomMother;
      if (FPop[IndexMother].Mated==false)
        {//She is a virgin
        RandomFather=RandomNumber(MaxMales);
        IndexFather=(OurIsland*MaxMales)+RandomFather;
        FPop[IndexMother].Mated=true;
        FPop[IndexMother].IndexPartner=IndexFather;
        }
      else
        {
        IndexFather=FPop[IndexMother].IndexPartner;
        }
      FlyKiddo=CreateOffspring(FPop[IndexMother],MPop[IndexFather]);
      }
    while
     (FlyKiddo.sex==male);
    //OK, the female kiddo is born, give her a spot in the vector
    CountGenome(FlyKiddo);
    FOffPop[(OurIsland*MaxFemales)+FemaleSpot]=FlyKiddo;
    }//Next FemaleSpot
  }//Next OurIsland
}




///////////////////////////////////////////////////////////////////////////////////////////////
//
// BOTH SEXES DISPERSE
//
///////////////////////////////////////////////////////////////////////////////////////////////
void NextGenerationBoth(vector <Fly> & MPop, vector <Fly> & FPop,
                    vector <Fly> & MOffPop, vector <Fly> & FOffPop,
                    int MaxMales, int MaxFemales)
{
assert(MPop.size()==MaxMales*NIslands);
assert(FPop.size()==MaxFemales*NIslands);
assert(MOffPop.size()==MaxMales*NIslands);
assert(FOffPop.size()==MaxFemales*NIslands);
//We know that on all islands, there are MaxDsex and MaxNDsex
//Also in the offspring, there will be MaxDsex and MaxNDsex flies on each island
//If we assume large family size, we can go off all spots on all islands for both sexes
//The nondispers' parents are from the same island, the dispersers' sex parents are from
//another island. This is the trick we gonna use...
//The vectors of the offspring are size 0, so we only use pushback commands...

unsigned int OurIsland;
int MaleSpot, FemaleSpot, RandomIsland, RandomFather, RandomMother;
int IndexFather, IndexMother;
Fly FlyKiddo;

for (OurIsland=0; OurIsland<NIslands ;OurIsland++)
  {
  //Males, take parents from random island
  for (MaleSpot=0; MaleSpot<MaxMales ;MaleSpot++)
    {
    //Throw away all offspring of non dispersing sex
    do
      {
      RandomIsland=RandomNumber(NIslands);
      RandomMother=RandomNumber(MaxFemales);
      IndexMother=(RandomIsland*MaxFemales)+RandomMother;
      assert(IndexMother<MaxFemales*NIslands);
      if (FPop[IndexMother].Mated==false)
        {//She is a virgin
        RandomFather=RandomNumber(MaxMales);
        IndexFather=(RandomIsland*MaxMales)+RandomFather;
        assert(IndexFather<MaxMales*NIslands);
        FPop[IndexMother].Mated=true;
        FPop[IndexMother].IndexPartner=IndexFather;
        }
        else
        {//She mates again with the prince on the white horse
        IndexFather=FPop[IndexMother].IndexPartner;
        assert(IndexFather<MaxMales*NIslands);
        }
      FlyKiddo=CreateOffspring(FPop[IndexMother],MPop[IndexFather]);
      }
    while
     (FlyKiddo.sex==female);
    //OK, the kiddo is born, give him its spot in the vector
    CountGenome(FlyKiddo);
    assert(FlyKiddo.sex==male);
    MOffPop[(OurIsland*MaxMales)+MaleSpot]=FlyKiddo;
    }//Next MaleSpot

  //Females, take parents from random island
  for (FemaleSpot=0; FemaleSpot<MaxFemales ;FemaleSpot++)
    {
    //Throw away all offspring of non dispersing sex
    do
      {
      RandomIsland=RandomNumber(NIslands);
      RandomMother=RandomNumber(MaxFemales);
      IndexMother=(RandomIsland*MaxFemales)+RandomMother;
      assert(IndexMother<MaxFemales*NIslands);
      if (FPop[IndexMother].Mated==false)
        {//She is a virgin
        RandomFather=RandomNumber(MaxMales);
        IndexFather=(RandomIsland*MaxMales)+RandomFather;
        assert(IndexFather<MaxMales*NIslands);
        FPop[IndexMother].Mated=true;
        FPop[IndexMother].IndexPartner=IndexFather;
        }
        else
        {//She mates again with the prince on the white horse
        IndexFather=FPop[IndexMother].IndexPartner;
        assert(IndexFather<MaxMales*NIslands);
        }
      FlyKiddo=CreateOffspring(FPop[IndexMother],MPop[IndexFather]);
      }
    while
     (FlyKiddo.sex==male);
    //OK, the kiddo is born, give him its spot in the vector
    CountGenome(FlyKiddo);
    assert(FlyKiddo.sex==female);
    FOffPop[(OurIsland*MaxFemales)+FemaleSpot]=FlyKiddo;
    }//Next FemaleSpot
  }//Next OurIsland
}//End of: void NextGeneration


