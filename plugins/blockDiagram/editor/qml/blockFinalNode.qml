import QtQuick 1.1

/// @todo: Add ellipse into qml library
Rectangle {
    width: 30
    height: 30
    border.width: 1
    radius: width * 0.5
    color: "white"

    Rectangle {
		width: parent.width * 2 / 3.0
		height: parent.height * 2 / 3.0
        radius: width * 0.5
        anchors.centerIn: parent
        color: "black"
    }
}
