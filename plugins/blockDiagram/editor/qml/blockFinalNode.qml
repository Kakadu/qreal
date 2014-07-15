import QtQuick 1.1
import CustomComponents 1.0

Rectangle {
    width: 30
    height: 30
    color: "transparent"
    Ellipse {
        x: parent.width / 2
        y: parent.height / 2
        width: parent.width
        height: parent.height
        color: "white"
        border.color: "black"
        border.width: 1
        Ellipse {
            x: parent.parent.width / 2
            y: parent.parent.height / 2
            width: 2 * parent.width / 3
            height: 2 * parent.height / 3
            color: "black"
        }
    }
}
