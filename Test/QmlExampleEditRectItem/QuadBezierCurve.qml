import QtQuick 2.2

Item {
    id: quadBezierCurve
    property int canvasAreaH
    property int canvasAreaW
    property real startPointX
    property real startPointY
    property real endPointX
    property real endPointY


    Rectangle{
        id: startingPoint
        x: startPointX
        y: startPointY
        width: 10
        height: 10
        color: "black"
        onXChanged: {
            canvas.requestPaint()
        }
        onYChanged: {
            canvas.requestPaint()
        }
    }
    MouseArea{
        id:startingPointMArea
        anchors.fill: startingPoint

        property real oldMouseX
        property real oldMouseY

        onPressed: {
            oldMouseX = mouseX
            oldMouseY = mouseY
        }
        onPositionChanged: {
            if(pressed)
            {
                startingPoint.x += mouseX - oldMouseX
                startingPoint.y += mouseY - oldMouseY
            }
        }
    }

    //endPoint
    Rectangle{
        id: endPoint
        x: endPointX
        y: endPointY
        width: 10
        height: 10
        color: "grey"
        onXChanged: {
            canvas.requestPaint()
        }
        onYChanged: {
            canvas.requestPaint()
        }
    }
    MouseArea{
        id:endPointMArea
        anchors.fill: endPoint

        property real oldMouseX
        property real oldMouseY

        onPressed: {
            oldMouseX = mouseX
            oldMouseY = mouseY
        }
        onPositionChanged: {
            if(pressed)
            {
                endPoint.x += mouseX - oldMouseX
                endPoint.y += mouseY - oldMouseY
            }
        }
    }

    //controlPoint
    Rectangle{
        id: controlPoint
        width: 10
        height: 10
        x: (startPointX + endPointX) / 2
        y: (startPointY + endPointY) / 2
        color: "dark blue"
        onXChanged: {
            canvas.requestPaint()
        }
        onYChanged: {
            canvas.requestPaint()
        }
    }
    MouseArea{
        id:controlPointMArea
        anchors.fill: controlPoint

        property real oldMouseX
        property real oldMouseY

        onPressed: {
            oldMouseX = mouseX
            oldMouseY = mouseY
        }
        onPositionChanged: {
            if(pressed)
            {
                controlPoint.x += mouseX - oldMouseX
                controlPoint.y += mouseY - oldMouseY
            }
        }
    }

    //drawing section
    Canvas {
        id:canvas
        height: canvasAreaH
        width: canvasAreaW

        onPaint:{
            var ctx = getContext('2d')
            ctx.clearRect(0, 0, canvas.width, canvas.height)
            ctx.strokeStyle = Qt.rgba(0,0,0,1);
            ctx.lineWidth = 10;
            ctx.beginPath();
            ctx.moveTo(startingPoint.x, startingPoint.y);//start point
            ctx.quadraticCurveTo(controlPoint.x,
                                 controlPoint.y,
                                 endPoint.x,
                                 endPoint.y
                                 );
            ctx.stroke();
        }
    }
}
