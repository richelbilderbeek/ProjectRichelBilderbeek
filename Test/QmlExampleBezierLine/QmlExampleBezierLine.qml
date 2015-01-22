import QtQuick 2.2

Rectangle {
    id: rect;
    width: 450;
    height:800;
    PathView {
        id: conrPaV;
        anchors.fill: parent;
        model: 900;
        delegate: Rectangle {
            id: dot;
            width: 1; height: 1;
            color: "red";
        }

        path: Path {
            id: ph;
            startX: 0.0; startY: conrPaV.height/2.0;
            PathQuad {
                x: 40.0; y: conrPaV.height/2.0;
                controlX: 20.0; controlY: ph.startY -60.0;
            }
            PathQuad {
                x: 80.0; y: conrPaV.height/2.0;
                controlX: 60.0; controlY: ph.startY +60.0;
            }
        }
    }
}
