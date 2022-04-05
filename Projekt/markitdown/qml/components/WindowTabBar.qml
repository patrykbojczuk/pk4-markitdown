import QtQuick
import QtQuick.Controls
import "qrc:/"

Rectangle {
    height: 40
    color: Constants.lighterBackgroundColor
    radius: Constants.windowRadius
    border.color: "transparent"

    property bool isMaximized: false

    Rectangle {
        // Hides bottom radius
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        height: Constants.windowRadius
        color: Constants.lighterBackgroundColor
    }

    Row {
        id: appButtons
        width: 54
        height: 14
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 12
        topPadding: 1
        rightPadding: 1
        bottomPadding: 1
        leftPadding: 1
        spacing: 8

        WindowButton {
            id: closeButton
            width: 12
            height: 12
            color: "#00000000"
            borderColor: Constants.backgroundColor
            iconUrl: Constants.closeIcon
        }
        WindowButton {
            id: minimizeButton
            width: 12
            height: 12
            color: "#00000000"
            borderColor: Constants.backgroundColor
            iconUrl: Constants.minimizeIcon
        }
        WindowButton {
            id: resizeButton
            width: 12
            height: 12
            color: "#00000000"
            borderColor: Constants.backgroundColor
            iconUrl: isMaximized ? Constants.demaximizeIcon : Constants.maximizeIcon
        }
    }
}


