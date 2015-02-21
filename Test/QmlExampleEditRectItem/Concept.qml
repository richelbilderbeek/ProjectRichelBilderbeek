/*
This file contains the code for a box with text.
This can be edited by the user.
The border of the box can be expanded.
It uses three QML elements:
 1. Rectangle
 2. MouseArea
 3. TextInput
*/

import QtQuick 2.2

Item{
    id: concept

    height: border.height
    width: border.width

    //Properties of the box borders
    property int borderWidth: 10
    property string borderColor: "black"
    property string focusColor: "cyan"

    //properties for the area surrounding the text: textAreaMargin
    property string backColor2: "white"
    property int textMarginWidth: 10

    //Propeties of the area under the text: textArea
    property string backColor1: "white"

    //Properties of the text
    property int textSize

    //This Rectangle creates the border of the box
    Rectangle{
        id: border
        height: textAreaMargin.height + (concept.borderWidth * 2)
        width: textAreaMargin.width + (concept.borderWidth * 2)

        property bool cursorVisible: false

        //Border color
        color: {
            if(text.cursorVisible){
                return focusColor
            }
            else{
                return borderColor
            }
        }

        //The border has to adapt to text edit or shrinking events
        onHeightChanged: {
            if(height < textAreaMargin.height + 2)
            {
                PropertyChanges
                height = textAreaMargin.height + 2
            }
        }
        onWidthChanged: {
            if(width < textAreaMargin.width + 2)
            {
                PropertyChanges
                width = textAreaMargin.width + 2
            }
        }
    }
    //The textAreaMargin overlaps the textArea and includes margins for the text
    Rectangle{
        id:textAreaMargin
        height: textArea.height + concept.textMarginWidth
        width: textArea.width + concept.textMarginWidth
        color: backColor2
        anchors.centerIn: border
    }

    //The textArea is the area covered by the text
    Rectangle{
        id: textArea
        height: text.contentHeight
        width: text.contentWidth
        color: backColor1
        anchors.centerIn: textAreaMargin
    }

    //The MouseArea allows to handle mouse event on the box
    MouseArea{
        id:conceptArea

        property int oldMouseX
        property int oldMouseY

        anchors.fill: border

        onPressed: {
            oldMouseX = mouseX
            oldMouseY = mouseY
        }
        onPositionChanged: {
            if(pressed){
                concept.x += mouseX - oldMouseX
                concept.y += mouseY - oldMouseY
            }
        }
    }

    //The text properties
    TextInput{
        id: text
        text: "New concept..."
        font.pixelSize: concept.textSize
        anchors.centerIn: textArea
        onTextChanged: {
            border.height = textAreaMargin.height + (concept.borderWidth * 2)
            border.width = textAreaMargin.width + (concept.borderWidth * 2)
        }
    }

    //Resize topLeftCorner
    Rectangle{
        id: topLeftCornerArea
        anchors.fill: topLeftCorner
        visible: false
        color: borderColor
    }
    MouseArea{
        property real oldMouseX

        id: topLeftCorner
        height: 5
        width: 5
        anchors.left: parent.left
        anchors.leftMargin: -width
        anchors.top: parent.top
        anchors.topMargin: -height

        onPressed: {
            oldMouseX = mouseX
        }
        onPositionChanged: {
            if(pressed){
                border.width = border.width + (oldMouseX - mouseX)
                border.height = border.height + (oldMouseX - mouseX)
                concept.borderWidth = border.width - textAreaMargin.width
            }
        }
        hoverEnabled: true
        onEntered: topLeftCornerArea.visible = true
        onExited: topLeftCornerArea.visible = false
    }

    //resize bottomLeftCorner
    Rectangle{
        id: bottomLeftCornerArea
        anchors.fill: bottomLeftCorner
        visible: false
        color: borderColor
    }
    MouseArea{
        property real oldMouseX

        id: bottomLeftCorner
        height: 5
        width: 5
        anchors.left: parent.left
        anchors.leftMargin: -width
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -height

        onPressed: {
            oldMouseX = mouseX
        }
        onPositionChanged: {
            if(pressed){
                border.width = border.width + (oldMouseX - mouseX)
                border.height = border.height + (oldMouseX - mouseX)
                concept.borderWidth = border.width - textAreaMargin.width
            }
        }
        hoverEnabled: true
        onEntered: bottomLeftCornerArea.visible = true
        onExited: bottomLeftCornerArea.visible = false
    }

    //resize topRightCorner
    Rectangle{
        id: topRightCornerArea
        anchors.fill: topRightCorner
        visible: false
        color: borderColor
    }
    MouseArea{
        property real oldMouseY

        id: topRightCorner
        height: 5
        width: 5
        anchors.right: parent.right
        anchors.rightMargin: -width
        anchors.top: parent.top
        anchors.topMargin: -height

        onPressed: {
            oldMouseY = mouseY
        }
        onPositionChanged: {
            if(pressed){
                border.width = border.width + (oldMouseY - mouseY)
                border.height = border.height + (oldMouseY - mouseY)
                concept.borderWidth = border.width - textAreaMargin.width
            }
        }
        hoverEnabled: true
        onEntered: topRightCornerArea.visible = true
        onExited: topRightCornerArea.visible = false
    }

    //resize bottomRightCorner
    Rectangle{
        id: bottomRightCornerArea
        anchors.fill: bottomRightCorner
        visible: false
        color: borderColor
    }
    MouseArea{
        property real oldMouseY

        id: bottomRightCorner
        height: 5
        width: 5
        anchors.right: parent.right
        anchors.rightMargin: -width
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -height

        onPressed: {
            oldMouseY = mouseY
        }
        onPositionChanged: {
            if(pressed){
                border.width = border.width + (mouseY - oldMouseY)
                border.height = border.height + (mouseY - oldMouseY)
                concept.borderWidth = border.width - textAreaMargin.width
            }
        }
        hoverEnabled: true
        onEntered: bottomRightCornerArea.visible = true
        onExited: bottomRightCornerArea.visible = false
    }
}
