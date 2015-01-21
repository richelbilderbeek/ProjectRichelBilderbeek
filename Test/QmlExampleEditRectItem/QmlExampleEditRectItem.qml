import QtQuick 2.2

Rectangle {
    id: rectangle1
    width: 1366
    height: 717

    Concept{
        anchors.centerIn: parent
    }

    Button{
        id: quitButton
        buttonText: "Quit"
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
    }
}

