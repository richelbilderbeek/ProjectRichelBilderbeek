#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>

int main(int argc, char *argv[])
{
  std::stringstream cmd;
  cmd
    << R"(C:\cfd\blueCFD-SingleCore-2.1\OpenFOAM-2.1\etc\batchrc.bat "WM_COMPILER=mingw-w32" "WM_PRECISION_OPTION=DP" "WM_MPLIB=""")"
    // Changing to drive D is important...
    << " && D: "
    // ...although this also indicates the drive
    << R"( && cd D:\Projects\Test\ToolOpenFoamErrorOpenCellsFoundCorrected)"
    << " & checkMesh"
  ;
  std::clog << "cmd: " << cmd.str() << std::endl;
  std::system(cmd.str().c_str());
}


#ifdef SCREEN_OUTPUT //Screen output:

cmd: C:\cfd\blueCFD-SingleCore-2.1\OpenFOAM-2.1\etc\batchrc.bat "WM_COMPILER=min
gw-w32" "WM_PRECISION_OPTION=DP" "WM_MPLIB=""" && D:  && cd D:\Projects\Test\Too
lOpenFoamErrorOpenCellsFoundCorrected & checkMesh
/*---------------------------------------------------------------------------*\
| =========                 |                                                 |
| \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |
|  \\    /   O peration     | Version:  2.1                                   |
|   \\  /    A nd           | Web:      www.OpenFOAM.org                      |
|    \\/     M anipulation  |                                                 |
\*---------------------------------------------------------------------------*/
/*   Windows 32 and 64 bit porting by blueCAPE: http://www.bluecape.com.pt   *\
|  Based on Windows porting (2.0.x v4) by Symscape: http://www.symscape.com   |
\*---------------------------------------------------------------------------*/
Build  : 2.1-88b2f2ae3a0b
Exec   : checkMesh
Date   : Mar 21 2014
Time   : 08:51:31
Host   : "AIRBEAR-W7-I5"
PID    : 4064
Case   : D:/Projects/Test/ToolOpenFoamErrorOpenCellsFoundCorrected
nProcs : 1
SigFpe : Enabling floating point exception trapping (FOAM_SIGFPE).
fileModificationChecking : Monitoring run-time modified files using timeStampMas
ter
allowSystemOperations : Allowing user-supplied system call operations

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
Create time

Create polyMesh for time = 0

Time = 0

Mesh stats
    points:           8
    internal points:  0
    faces:            9
    internal faces:   0
    cells:            2
    boundary patches: 6
    point zones:      0
    face zones:       0
    cell zones:       0

Overall number of cells of each type:
    hexahedra:     0
    prisms:        1
    wedges:        0
    pyramids:      0
    tet wedges:    1
    tetrahedra:    0
    polyhedra:     0

Checking topology...
    Boundary definition OK.
    Cell to face addressing OK.
    Point usage OK.
    Upper triangular ordering OK.
    Face vertices OK.
   *Number of regions: 2
    The mesh has multiple regions which are not connected by any face.
  <<Writing region information to "0/cellToRegion"

Checking patch topology for multiply connected surfaces ...
    Patch               Faces    Points   Surface topology
    back                1        4        ok (non-closed singly connected)
    bottom              2        4        ok (non-closed singly connected)
    front               1        4        ok (non-closed singly connected)
    left                1        4        ok (non-closed singly connected)
    right               1        4        ok (non-closed singly connected)
    top                 2        4        ok (non-closed singly connected)

Checking geometry...
    Overall domain bounding box (-1 -1 0) (1 1 1)
    Mesh (non-empty, non-wedge) directions (1 1 1)
    Mesh (non-empty) directions (1 1 1)
 ***Boundary openness (0 0.171573 0) possible hole in boundary description.
 ***Open cells found, max cell openness: 1, number of open cells 1
  <<Writing 1 non closed cells to set nonClosedCells
    Minimum face area = 1. Maximum face area = 2.  Face area magnitudes OK.
    Min volume = 0.722222. Max volume = 1.  Total volume = 1.72222.  Cell volume
s OK.
    Non-orthogonality check OK.
    Face pyramids OK.
    Max skewness = 0.421474 OK.
    Coupled point location match (average 0) OK.

Failed 2 mesh checks.

Time = 1

Mesh stats
    points:           8
    internal points:  0
    faces:            8
    internal faces:   0
    cells:            2
    boundary patches: 6
    point zones:      0
    face zones:       0
    cell zones:       0

Overall number of cells of each type:
    hexahedra:     0
    prisms:        0
    wedges:        0
    pyramids:      0
    tet wedges:    0
    tetrahedra:    0
    polyhedra:     2

Checking topology...
    Boundary definition OK.
    Cell to face addressing OK.
    Point usage OK.
    Upper triangular ordering OK.
    Face vertices OK.
   *Number of regions: 2
    The mesh has multiple regions which are not connected by any face.
  <<Writing region information to "1/cellToRegion"

Checking patch topology for multiply connected surfaces ...
    Patch               Faces    Points   Surface topology
    back                1        4        ok (non-closed singly connected)
    bottom              2        4        ok (non-closed singly connected)
    front               1        4        ok (non-closed singly connected)
    left                1        4        ok (non-closed singly connected)
    right               1        4        ok (non-closed singly connected)
    top                 2        6        ok (non-closed singly connected)

Checking geometry...
    Overall domain bounding box (-1 -1 0) (1 1 1)
    Mesh (non-empty, non-wedge) directions (1 1 1)
    Mesh (non-empty) directions (1 1 1)
    Boundary openness (-2.28837e-018 -1.83069e-017 0) OK.
    Max cell openness = 5.55112e-017 OK.
    Max aspect ratio = 2 OK.
    Minimum face area = 1. Maximum face area = 2.23607.  Face area magnitudes OK
.
    Min volume = 0.731939. Max volume = 0.731939.  Total volume = 1.46388.  Cell
 volumes OK.
    Non-orthogonality check OK.
    Face pyramids OK.
    Max skewness = 0.34936 OK.
    Coupled point location match (average 0) OK.

Mesh OK.

End

Press <RETURN> to close this window...

#endif
