xcopy /y constant\polyMeshCube\*.* constant\polyMesh\*.* 
blockMesh
//surfaceFeatureExtract -includedAngle 150 constant/triSurface/mymesh.stl mymeshfeatures
snappyHexMesh
xcopy /y 1\polyMesh\*.* constant\polyMesh\*.*
parafoam

