/*
This file contains the information to add Button to any GUI in QtQuick.
It is made of three QML elements:
 1. Rectangle: button visible features (background color, shape,...)
 2. Text: fixed button text
 3. MouseArea: allows to handle mouse events. By default only works for clicks.
*/

import QtQuick 2.2

Item{
    id: button

    width: buttonArea.width
    height: buttonArea.height

    //Properties of the Rectangle
    property string buttonColor: "grey"
    property int textMargin: 10

    //Properties of the Text
    property string buttonText: "Button text"
    property string buttonTextColor: "black"

    //Signals sent from the button
    signal buttonOnClicked

    //The Rectangle which contains the text
    Rectangle {
        id: buttonArea
        color: button.buttonColor
        radius: 4
        height: textButton.contentHeight + button.textMargin
        width: textButton.contentWidth + button.textMargin
    }
    //The Text displayed by the Button
    Text {
        id: textButton
        text: button.buttonText
        font.pointSize: 20
        color: button.buttonTextColor
        horizontalAlignment: Text.Center
        verticalAlignment: Text.Center
        anchors.centerIn: buttonArea
    }
    //The MouseArea, corresponding to the Rectangle area,
    //allows to process mouse events.
    MouseArea {
        anchors.fill: buttonArea
        onClicked: {
            buttonOnClicked()
        }
    }
}
