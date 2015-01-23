import QtQuick 2.2
import QtQuick.Window 2.0

Rectangle {
    id: window
    width: Screen.width
    height: Screen.height - 52

    property bool connecting: false

    Concept{
        borderWidth: 10
        x: (window.width / 2) - (width / 2)
        y: (window.height / 2) - (height / 2)
    }

    Button{
        id: quitButton
        buttonText: "Quit"
        onButtonOnClicked: {
            Qt.quit();
        }
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
    }

    Button{
        id: createConcept
        buttonText: "Create New\nConcept"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        onButtonOnClicked: {
            var component = Qt.createComponent("Concept.qml")
            if(component.status === Component.Ready)
            {
                var newConcept = component.createObject(window)
            }
        }
    }

    Button{
        id: connect
        buttonText: "Connect two concepts"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        onButtonOnClicked: {
            connecting = true
            canvasMArea.visible = true
        }
    }

    MouseArea{
        id:canvasMArea
        visible: false
        anchors.fill: window
        opacity: 100

        property bool firstClick: false
        property bool secondClick: false
        property real startPointX
        property real startPointY
        property real endPointX
        property real endPointY

        onPressed: {
            if(connecting)
            {
                startPointX = mouseX
                startPointY = mouseY
                console.log("press and hold")
            }
        }
        onReleased: {
            if(connecting)
            {
                endPointX = mouseX
                endPointY = mouseY
                var component = Qt.createComponent("QuadBezierCurve.qml")
                if(component.status === Component.Ready)
                {
                    console.log("entered!!")
                    component.createObject(window,
                                           {canvasAreaH:window.height,
                                            canvasAreaW:window.width,
                                            startPointX: startPointX,
                                            startPointY: startPointY,
                                            endPointX: endPointX,
                                            endPointY:endPointY})
                    connecting = false
                    visible = false
                }
            }
        }
    }
}

