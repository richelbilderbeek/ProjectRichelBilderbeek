import QtQuick 2.2
import QtQuick.Window 2.0

Rectangle {
    id: area
    height: Screen.height - 27
    width: Screen.width


    //startPoint
    Rectangle{
        id: startingPoint
        x: 100
        y: 100
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
        width: 10
        height: 10
        x: 500
        y: 500
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
        x: 130
        y: 200
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
        anchors.fill: area
        onPaint:{
            var ctx = getContext('2d')
            ctx.clearRect(0, 0, canvas.width, canvas.height)
            ctx.strokeStyle = Qt.rgba(1, 1000, 0, 1);
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
