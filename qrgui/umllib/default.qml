import QtQuick 1.1

Rectangle {
    Text {
        color: "red"
        text: qsTr("An error occured while \nloading this element`s view. \nPlease check everything \nand try again.")
        horizontalAlignment: Text.AlignHCenter
        font.weight: Font.Bold
    }
}
