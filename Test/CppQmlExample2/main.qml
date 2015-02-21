import QtQuick 2.2
import QtQuick.Window 2.1

Window {
    visible: true
    width: 360
    height: 360

<<<<<<< HEAD
=======
    QmlCaesarCipher {

    }


>>>>>>> c99017a2d230e590727b21cc2d7426112c8072b8
    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }
}
