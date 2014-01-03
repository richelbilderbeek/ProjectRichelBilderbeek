xcopy /y constant\polyMeshCube\*.* constant\polyMesh\*.* 
blockMesh
xcopy /y triSurface\*.* constant\triSurface\*.*
copy snappyHexMeshDict system\snappyHexMeshDict
snappyHexMesh
xcopy /y 2\polyMesh\*.* constant\polyMesh\*.*
sed -i "s/_patch0//" constant/polyMesh\boundary
parafoam