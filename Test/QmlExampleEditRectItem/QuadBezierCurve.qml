/*
This is a file to quadratic Bezier curve.
It uses three elements:
 1. Rectangle
 2. MouseArea
 3. Canvas
Three points are used to draw the quadratic Bezier curve:
 a. starting point, where the curve originates
 b. ending point, where the curve ends
 c. control point. This allows to bend the line,
    which connects the starting and the ending point
*/

import QtQuick 2.2

Item {
    id: quadBezierCurve
    property int canvasAreaH
    property int canvasAreaW
    property real startPointX
    property real startPointY
    property real endPointX
    property real endPointY

    //The point where the curve starts
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
    //The MouseArea allows the starting point to be moved around
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

    //The point where the curve ends
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
    //The MouseArea allows the starting point to be moved around
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

    //The control point
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
    //The MouseArea can be used to bend the straight line,
    //connecting the starting point to the ending point
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

    //The canvas is created and the curve is actually drawn
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
