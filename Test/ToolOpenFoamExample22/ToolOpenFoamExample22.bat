xcopy /y constant\polyMeshCube\*.* constant\polyMesh\*.* 
blockMesh
xcopy /y triSurface\*.* constant\triSurface\*.*
copy snappyHexMeshDict system\snappyHexMeshDict
copy ToolOpenFoamExample22.stl constant\triSurface\ToolOpenFoamExample22.stl
surfaceFeatureExtract -includedAngle 150 constant/triSurface/ToolOpenFoamExample22.stl mymeshfeatures
snappyHexMesh
xcopy /y 2\polyMesh\*.* constant\polyMesh\*.*
//sed -i "s/_patch0//" constant/polyMesh\boundary
parafoam


