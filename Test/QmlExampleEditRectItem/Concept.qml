import QtQuick 2.2

Item{
    id: concept

    height: border.height
    width: border.width
    z: +1

    //properties for border
    property int borderWidth: 10
    property string borderColor: "black"
    property string focusColor: "cyan"

    //properties for textAreaMargin
    property string backColor2: parent.color
    property int textMarginWidth: 10

    //propeties for textArea
    property string backColor1: parent.color

    //properties for text
    property int textSize

    Rectangle{
        id: border
        height: textAreaMargin.height + concept.borderWidth
        width: textAreaMargin.width + concept.borderWidth

        property bool cursorVisible: false

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

        //border color
        color: {
            if(text.cursorVisible){
                return focusColor
            }
            else{
                return borderColor
            }
        }

        //resize topLeftCorner
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
    Rectangle{
        id:textAreaMargin
        height: textArea.height + concept.textMarginWidth
        width: textArea.width + concept.textMarginWidth
        color: backColor2
        anchors.centerIn: border
    }
    Rectangle{
        id: textArea
        height: text.contentHeight
        width: text.contentWidth
        color: backColor1
        anchors.centerIn: textAreaMargin
    }
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
            var oldParentX = concept.parent.x + oldMouseX
            var oldParentY = concept.parent.y + oldMouseY
            if(pressed){
                concept.x += mouseX - oldMouseX
                concept.y += mouseY - oldMouseY
            }
        }
    }
    TextInput{
        id: text
        text: "New concept..."
        font.pixelSize: concept.textSize
        anchors.centerIn: textArea
        onTextChanged: {
            border.height = textAreaMargin.height + concept.borderWidth
            border.width = textAreaMargin.width + concept.borderWidth
        }
    }
}
