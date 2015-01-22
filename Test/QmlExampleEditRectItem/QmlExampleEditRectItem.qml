import QtQuick 2.2
import QtQuick.Window 2.0

Rectangle {
    id: window
    width: Screen.width
    height: Screen.height - 52

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
            console.log("Signal received!!")
            var component = Qt.createComponent("Concept.qml")
            if(component.status === Component.Ready){
                var newConcept = component.createObject(window);
            }
        }
    }
}

