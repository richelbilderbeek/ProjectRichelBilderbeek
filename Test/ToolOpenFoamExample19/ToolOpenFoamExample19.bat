xcopy /y constant\polyMeshCube\*.* constant\polyMesh\*.* 
blockMesh
surfaceFeatureExtract -includedAngle 150 constant/triSurface/mymesh.stl mymeshfeatures
snappyHexMesh
xcopy /y 2\polyMesh\*.* constant\polyMesh\*.*
parafoam

