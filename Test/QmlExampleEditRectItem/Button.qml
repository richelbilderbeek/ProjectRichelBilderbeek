import QtQuick 2.2

Item{
    id: button

    width: buttonArea.width
    height: buttonArea.height

    property string buttonColor: "grey"
    property int textMargin: 10

    property string buttonText: "Button text"

    signal buttonOnClicked

    Rectangle {
        id: buttonArea
        color: button.buttonColor
        radius: 4
        height: textButton.contentHeight + button.textMargin
        width: textButton.contentWidth + button.textMargin
    }
    Text {
        id: textButton
        text: button.buttonText
        font.pointSize: 20
        color: "black"
        horizontalAlignment: Text.Center
        verticalAlignment: Text.Center
        anchors.centerIn: buttonArea
    }
    MouseArea {
        anchors.fill: buttonArea
        onClicked: {
            buttonOnClicked()
        }
    }
}
