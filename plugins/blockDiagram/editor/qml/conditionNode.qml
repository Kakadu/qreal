import QtQuick 1.1

/// @todo: add line into qml library
Rectangle {
	width: 60
	height: 60
	color: "transparent"

	Rectangle {
		width: 42
		height: 42
		border.width: 1
		color: "white"
		anchors.centerIn: parent
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.top: parent.top
		anchors.bottom: parent.bottom
		transform: Rotation { origin.x: 21; origin.y: 21; axis { x: 0; y: 0; z: 1 } angle: 45 }
	}
}