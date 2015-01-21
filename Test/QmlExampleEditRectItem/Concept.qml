import QtQuick 2.2

Item{
    id: concept

    height: border.height
    width: border.width

    //properties for border
    property int borderWidth: 100
    property string borderColor: "black"

    //properties for textAreaMargin
    property string backColor2: "white"
    property int textMarginWidth: 10

    //propeties for textArea
    property string backColor1: "white"

    //properties for text
    property int textSize

    //signals
    signal exited()

    Rectangle{
        id: border
        height: textAreaMargin.height + concept.borderWidth
        width: textAreaMargin.width + concept.borderWidth
        color: borderColor

        onHeightChanged: {
            if(height < textAreaMargin.height + 2)
            {
                height = textAreaMargin.height + 2
            }
        }
        onWidthChanged: {
            if(width < textAreaMargin.width + 2)
            {
                width = textAreaMargin.width + 2
            }
        }

        //resize topLeftCorner
        Rectangle{
            id: topLeftCornerArea
            anchors.fill: topLeftCorner
            color: "white"
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
            onEntered: topLeftCornerArea.color = "light black"
            onExited: topLeftCornerArea.color = "white"
        }

        //resize bottomLeftCorner
        Rectangle{
            id: bottomLeftCornerArea
            anchors.fill: bottomLeftCorner
            color: "white"
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
            onEntered: bottomLeftCornerArea.color = "light black"
            onExited: bottomLeftCornerArea.color = "white"
        }

        //resize topRightCorner
        Rectangle{
            id: topRightCornerArea
            anchors.fill: topRightCorner
            color: "white"
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
            onEntered: topRightCornerArea.color = "light black"
            onExited: topRightCornerArea.color = "white"
        }

        //resize bottomRightCorner
        Rectangle{
            id: bottomRightCornerArea
            anchors.fill: bottomRightCorner
            color: "white"
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
            onEntered: bottomRightCornerArea.color = "light black"
            onExited: bottomRightCornerArea.color = "white"
        }
    }
    Rectangle{
        id:textAreaMargin
        height: textArea.height + concept.textMarginWidth
        width: textArea.width + concept.textMarginWidth
        color: "white"
        anchors.centerIn: border
    }
    Rectangle{
        id: textArea
        height: text.contentHeight
        width: text.contentWidth
        color: "white"
        anchors.centerIn: textAreaMargin
    }
    MouseArea{
        id:conceptArea
        anchors.fill: border
        hoverEnabled: true
        onEntered: borderColor = "silver"
        onExited: borderColor = "black"
    }
    TextInput{
        id: text
        text: "Click here to edit text..."
        font.pixelSize: concept.textSize
        anchors.centerIn: textArea
        onTextChanged: {
            border.height = textAreaMargin.height + concept.borderWidth
            border.width = textAreaMargin.width + concept.borderWidth
        }
    }

}
