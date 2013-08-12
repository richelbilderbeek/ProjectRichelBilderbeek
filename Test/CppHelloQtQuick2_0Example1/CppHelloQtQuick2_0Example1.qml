import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0

ApplicationWindow {
    title: qsTr("Hello World")
    width: 640
    height: 480

    Button {
        id: top_button
        text: qsTr("Hello World")
        y: 100
    }

    Button {
        text: qsTr("Hello World again")
        y: top_button.y + 100
    }
}
